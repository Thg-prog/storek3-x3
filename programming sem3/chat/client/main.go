package main

import (
	"bufio"
	"errors"
	"flag"
	"fmt"
	"io"
	"net"
	"os"
	"strconv"
	"strings"
	"sync"
	// "time"

	"github.com/gdamore/tcell/v2"
	"github.com/rivo/tview"
)

func main() {
	host := flag.String("h", "localhost", "Адрес для подключения")
	port := flag.Uint64("p", 3333, "Порт для подключения")
	flag.Parse()

	serverAddr := *host + ":" + strconv.FormatUint(*port, 10)
	tcpAddr, err := net.ResolveTCPAddr("tcp", serverAddr)
	if err != nil {
		fmt.Println("Couldn't resolve TCP address: ", err.Error())
		os.Exit(1)
	}

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		fmt.Println("Couldn't dial TCP: ", err.Error())
		os.Exit(1)
	}
	defer conn.Close()

	// Creating TCP client wrapper
	reader := bufio.NewReader(conn)
	client := &ChatClient{conn: conn, reader: reader, ackLock: &sync.Mutex{}}

	// Creating widgets for chat application
	tview.Styles = tview.Theme{
		PrimitiveBackgroundColor:    tcell.ColorBlack,
		ContrastBackgroundColor:     tcell.ColorBlack,
		MoreContrastBackgroundColor: tcell.ColorBlack,
		BorderColor:                 tcell.ColorWhite,
		TitleColor:                  tcell.ColorWhite,
		GraphicsColor:               tcell.ColorWhite,
		PrimaryTextColor:            tcell.ColorWhite,
		SecondaryTextColor:          tcell.ColorYellow,
		TertiaryTextColor:           tcell.ColorGreen,
		InverseTextColor:            tcell.ColorBlue,
		ContrastSecondaryTextColor:  tcell.ColorNavy,
	}

	var app *ChatApplication
	pages := tview.NewPages()

	// Main screen
	messageField := tview.NewInputField().
		SetLabel(">> ").
		SetPlaceholder("Сообщение...").
		SetDoneFunc(func(key tcell.Key) {
			app.sendMessage()
		})
	messageField.SetInputCapture(func(event *tcell.EventKey) *tcell.EventKey {
		switch event.Key() {
		case tcell.KeyUp:
			app.scroll(-1)
			return nil
		case tcell.KeyDown:
			app.scroll(1)
			return nil
		default:
			return event
		}
	})
	historyArea := tview.NewTextView().
		SetWordWrap(true)
	mainPage := tview.NewFlex().
		SetDirection(tview.FlexRow).
		AddItem(messageField, 1, 0, true).
		AddItem(historyArea, 0, 1, false)
	pages.AddPage("main", mainPage, true, true)

	// Initializing chat application
	app = &ChatApplication{
		client: client,
		app:    tview.NewApplication().SetRoot(pages, true),
		root:   pages,

		messageField: messageField,
		historyArea:  historyArea,
	}

	// Loop for ACK messages
	// go (func() {
	// 	for {
	// 		// Lock for ACK
	// 		app.client.ackLock.Lock()
	// 		app.client.ackEnabled = true

	// 		// Reading
	// 		ack, err := app.client.read()
	// 		if err != nil {
	// 			switch err.(type) {
	// 			case *ReadInvalidMessageError:
	// 			default:
	// 				os.Exit(1)
	// 			}
	// 		} else {
	// 			_, message, _ := strings.Cut(ack, " ")
	// 			fullMessage := fmt.Sprintf("%s: %s", app.openedChat, message)
	// 			app.addMessageToHistory(fullMessage)
	// 		}

	// 		// Unlock for ACK
	// 		app.client.ackEnabled = false
	// 		app.client.ackLock.Unlock()
	// 		time.Sleep(1 * time.Second)
	// 	}
	// })()

	// Run the application
	app.app.Run()
}

type ChatApplication struct {
	client *ChatClient

	app  *tview.Application
	root *tview.Pages

	authorizedAs string
	messageField *tview.InputField
	openedChat   string
	chatHistory  []string
	historyArea  *tview.TextView
}

func (app *ChatApplication) loadAck() {
	for len(app.client.ackBuffer) != 0 {
		ack := app.client.ackBuffer[0]
		_, message, _ := strings.Cut(ack, " ")
		fullMessage := fmt.Sprintf("%s: %s", app.openedChat, message)
		app.addMessageToHistory(fullMessage)
		app.client.ackBuffer = app.client.ackBuffer[1:]
	}
}

func (app *ChatApplication) openResultModal(text string) {
	const modalID = "result-modal"
	modal := tview.NewModal().
		SetText(text).
		AddButtons([]string{"OK"}).
		SetDoneFunc(func(buttonIndex int, buttonLabel string) {
			app.root.HidePage(modalID).RemovePage(modalID)
		})
	app.root.AddPage(modalID, modal, false, true)
}

func (app *ChatApplication) openErrorModal(text string) {
	const modalID = "error-modal"
	modal := tview.NewModal().
		SetText(text).
		AddButtons([]string{"OK"}).
		SetDoneFunc(func(buttonIndex int, buttonLabel string) {
			app.root.HidePage(modalID).RemovePage(modalID)
		})
	app.root.AddPage(modalID, modal, false, true)
}

func (app *ChatApplication) renderHistoryArea() {
	reversedHistory := reverse(app.chatHistory)
	history := strings.Join(reversedHistory, "\n")
	app.historyArea.SetText(history)
}

func (app *ChatApplication) scroll(step int) {
	row, _ := app.historyArea.GetScrollOffset()
	app.historyArea.ScrollTo(row+step, 0)
}

func reverse[T any](slice []T) []T {
	reversed := make([]T, len(slice))

	length := len(slice)
	for i := 0; i < length; i++ {
		reversed[i] = slice[length-i-1]
	}

	return reversed
}

func (app *ChatApplication) addMessageToHistory(message string) {
	// Adding message to history
	app.chatHistory = append(app.chatHistory, message)

	// Rerendering history area
	app.renderHistoryArea()
}

func (app *ChatApplication) sendMessage() {
	// app.loadAck()
	message := app.messageField.GetText()
	if message == "" {
		return
	}
	app.messageField.SetText("")

	if strings.HasPrefix(message, "/") {
		app.executeCommand(message)
		return
	}

	// If no chat is opened -> printing error
	if app.openedChat == "" {
		app.openErrorModal("No chat is opened")
		return
	}

	// Sending message
	err := app.client.sendMessageRequest(message)
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}

	// Adding message to history
	historyMessage := fmt.Sprintf("%s: %s", app.authorizedAs, message)
	app.addMessageToHistory(historyMessage)
}

func (app *ChatApplication) executeCommand(message string) {
	fullCommand := message[1:]
	command, arguments, _ := strings.Cut(fullCommand, " ")

	switch command {
	case "quit":
		app.app.Stop()
	case "auth":
		app.executeAuthCommand(arguments)
	case "register":
		app.executeRegisterCommand(arguments)
	case "users":
		app.executeUsersCommand(arguments)
	case "online":
		app.executeOnlineCommand(arguments)
	case "open":
		app.executeOpenCommand(arguments)
	default:
		app.openErrorModal("Unknown command: " + fullCommand)
	}
}

func (app *ChatApplication) executeAuthCommand(arguments string) {
	login, password, found := strings.Cut(arguments, " ")
	if !found {
		app.openErrorModal("Invalid amount of arguments for\n/auth")
		return
	}

	err := app.client.authRequest(login, password)
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}

	app.authorizedAs = login
	app.openResultModal("Authentication successful")
}

func (app *ChatApplication) executeRegisterCommand(arguments string) {
	login, password, found := strings.Cut(arguments, " ")
	if !found {
		app.openErrorModal("Invalid amount of arguments for\n/register")
		return
	}

	err := app.client.registerRequest(login, password)
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}

	app.executeAuthCommand(arguments)
}

func (app *ChatApplication) executeUsersCommand(arguments string) {
	users, err := app.client.usersRequest()
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}

	usersStr := strings.Join(users, "\n")
	app.openResultModal("All users:\n" + usersStr)
}

func (app *ChatApplication) executeOnlineCommand(arguments string) {
	onlineUsers, err := app.client.onlineRequest()
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}

	onlineUsersStr := strings.Join(onlineUsers, "\n")
	app.openResultModal("Online users:\n" + onlineUsersStr)
}

func (app *ChatApplication) executeOpenCommand(arguments string) {
	userID, _, _ := strings.Cut(arguments, " ")
	if userID == "" {
		app.openErrorModal("Invalid amount of arguments for\n/open")
		return
	}

	err := app.client.openChatRequest(userID)
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}
	app.openedChat = userID

	history, err := app.client.historyRequest()
	if err != nil {
		app.openErrorModal(err.Error())
		return
	}

	// Rerendering history area
	app.chatHistory = history
	app.renderHistoryArea()
}

type ChatClient struct {
	conn   *net.TCPConn
	reader *bufio.Reader

	ackEnabled bool
	ackLock    *sync.Mutex

	generalBuffer []string
	ackBuffer     []string
}

func (client *ChatClient) read() (string, error) {
	// Checking if we have something in buffers
	if client.ackEnabled && len(client.ackBuffer) != 0 {
		response := client.ackBuffer[0]
		client.ackBuffer = client.ackBuffer[1:]
		return response, nil
	} else if !client.ackEnabled && len(client.generalBuffer) != 0 {
		response := client.generalBuffer[0]
		client.generalBuffer = client.generalBuffer[1:]
		return response, nil
	}

	// Reading some data from server
	bytes, err := client.reader.ReadBytes(byte('\000'))
	if err != nil {
		if err == io.EOF {
			fmt.Println("Lost connection to server")
			os.Exit(1)
		}

		// If couldn't read something -> returning error
		return "", err
	}

	if len(bytes) == 0 {
		// If response is empty, this is also bad
		return "", errors.New("Response is empty")
	}

	// Parsing data
	response := string(bytes[:len(bytes)-1])
	isAck := strings.HasPrefix(response, "ack")
	if isAck && !client.ackEnabled {
		// Pushing ack message to buffer and returning that we got wrong type
		client.ackBuffer = append(client.ackBuffer, response)
		return "", &ReadInvalidMessageError{}
	} else if !isAck && client.ackEnabled {
		// Pushing general message to buffer and returning that we got wrong type
		client.generalBuffer = append(client.generalBuffer, response)
		return "", &ReadInvalidMessageError{}
	}

	// As we found message that we needed -> returning it
	return response, nil
}

func (client *ChatClient) readCorrect() (string, error) {
	// Reading until needed type of message is passed
	for {
		response, err := client.read()
		if err != nil {
			switch err.(type) {
			case *ReadInvalidMessageError:
				// We got invalid message, so continuing
				continue
			default:
				// We got some bad error, returning it
				return "", err
			}
		}

		return response, nil
	}
}

func (client *ChatClient) readN(count int) ([]string, error) {
	var result []string

	for i := 0; i < count; i++ {
		response, err := client.readCorrect()
		if err != nil {
			return nil, err
		}

		result = append(result, response)
	}

	return result, nil
}

func (client *ChatClient) send(command string) error {
	// Appending zero to the end if needed
	if !strings.HasSuffix(command, "\000") {
		command += "\000"
	}

	// Converting string to bytes
	bytes := []byte(command)

	// Sending bytes
	_, err := client.conn.Write(bytes)

	return err
}

func (client *ChatClient) authRequest(login, password string) error {
	// Formatting request as needed
	request := fmt.Sprintf("auth %s %s", login, password)

	// Sending request to server
	client.send(request)

	// client.ackLock.Lock()
	// defer client.ackLock.Unlock()

	// Fetching result from server
	result, err := client.readCorrect()
	if err != nil {
		return err
	}

	// If result is not success -> returning error
	if result != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return err
		}

		return errors.New(error)
	}

	return nil
}

func (client *ChatClient) registerRequest(login, password string) error {
	// Formatting request as needed
	request := fmt.Sprintf("register %s %s", login, password)

	// Sending request to server
	client.send(request)

	// Fetching result from server
	result, err := client.readCorrect()
	if err != nil {
		return err
	}

	// If result is not success -> returning error
	if result != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return err
		}

		return errors.New(error)
	}

	return nil
}

func (client *ChatClient) usersRequest() ([]string, error) {
	// Sending request to server
	client.send("users")

	// Fetching result from server
	usersResponse, err := client.readCorrect()
	if err != nil {
		return nil, err
	}

	if usersResponse != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return nil, err
		}

		return nil, errors.New(error)
	}

	// Fetching count of users
	usersCountStr, err := client.readCorrect()
	if err != nil {
		return nil, err
	}

	usersCount, err := strconv.Atoi(usersCountStr)
	if err != nil {
		return nil, err
	}

	// Fetching users
	return client.readN(usersCount)
}

func (client *ChatClient) onlineRequest() ([]string, error) {
	// Sending request to server
	client.send("online")

	// Fetching result from server
	onlineResponse, err := client.readCorrect()
	if err != nil {
		return nil, err
	}

	if onlineResponse != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return nil, err
		}

		return nil, errors.New(error)
	}

	// Fetching count of online users
	onlineCountStr, err := client.readCorrect()
	if err != nil {
		return nil, err
	}

	onlineCount, err := strconv.Atoi(onlineCountStr)
	if err != nil {
		return nil, err
	}

	// Fetching online users
	return client.readN(onlineCount)
}

func (client *ChatClient) openChatRequest(user string) error {
	// Formatting request as needed
	request := fmt.Sprintf("open_chat %s", user)

	// Sending request to server
	client.send(request)

	// Fetching result from server
	result, err := client.readCorrect()
	if err != nil {
		return err
	}

	// If result is not success -> returning error
	if result != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return err
		}

		return errors.New(error)
	}

	return nil
}

func (client *ChatClient) sendMessageRequest(message string) error {
	// Formatting request as needed
	request := fmt.Sprintf("send_message %s", message)

	// Sending request to server
	client.send(request)

	// Fetching result from server
	result, err := client.readCorrect()
	if err != nil {
		return err
	}

	// If result is not success -> returning error
	if result != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return err
		}

		return errors.New(error)
	}

	return nil
}

func (client *ChatClient) historyRequest() ([]string, error) {
	// Sending request to server
	client.send("history")

	// Fetching result from server
	historyResponse, err := client.readCorrect()
	if err != nil {
		return nil, err
	}

	if historyResponse != "Success" {
		error, err := client.readCorrect()
		if err != nil {
			return nil, err
		}

		return nil, errors.New(error)
	}

	// Fetching count of history messages
	historyCountStr, err := client.readCorrect()
	if err != nil {
		return nil, err
	}

	historyCount, err := strconv.Atoi(historyCountStr)
	if err != nil {
		return nil, err
	}

	// Fetching history users
	return client.readN(historyCount)
}

type ReadInvalidMessageError struct{}

func (e *ReadInvalidMessageError) Error() string {
	return "Got invalid message type while reading"
}
