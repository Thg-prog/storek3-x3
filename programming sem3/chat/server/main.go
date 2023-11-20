package main

import (
	"bufio"
	"database/sql"
	"errors"
	"flag"
	"fmt"
	"io"
	"net"
	"os"
	"strconv"
	"strings"
	"sync"

	_ "github.com/lib/pq"
)

func main() {
	port := flag.Uint64("p", 3333, "Порт, который необходимо слушать")
	flag.Parse()

	portString := strconv.FormatUint(*port, 10)

	socket, err := net.Listen("tcp", "0.0.0.0:"+portString)
	if err != nil {
		fmt.Println("Couldn't create TCP server: ", err.Error())
		os.Exit(1)
	}
	defer socket.Close()
	fmt.Println("Listening TCP connections on port " + portString)

	// Starting chat server
	db, err := createDatabase()
	if err != nil {
		fmt.Println("Couldn't create database: ", err)
		os.Exit(1)
	}

	lastUserID := 0
	onlineUsers := make(map[int]*User)
	authorizedUsers := make(map[string]int)
	openedChats := make(map[int]string)
	openedChatsID := make(map[int]int)
	server := ChatServer{db: db, lastUserID: lastUserID, onlineUsers: onlineUsers, authorizedUsers: authorizedUsers, openedChats: openedChats, openedChatsID: openedChatsID}
	server.run(socket)
	fmt.Println("ghg")
}

func createDatabase() (*sql.DB, error) {
	db, err := sql.Open("postgres", "dbname=mydb sslmode=disable host=localhost port=5432")
	if err != nil {
		return nil, err
	}

	// Creating tables
	const createUserTable = `
		CREATE TABLE IF NOT EXISTS users (
			login VARCHAR(255) NOT NULL PRIMARY KEY,
			password VARCHAR(255) NOT NULL
		)
	`
	const createChatTable = `
		CREATE TABLE IF NOT EXISTS chats (
			id SERIAL PRIMARY KEY,
			user1 VARCHAR(255) NOT NULL,
			user2 VARCHAR(255) NOT NULL,
			UNIQUE(user1, user2)
		)
	`
	const createMessageTable = `
		CREATE TABLE IF NOT EXISTS messages (
			id SERIAL PRIMARY KEY,
			chat INTEGER NOT NULL,
			sender VARCHAR(255) NOT NULL,
			message VARCHAR(255) NOT NULL
		)
	`

	// Creating tables
	if _, err := db.Exec(createUserTable); err != nil {
		return nil, err
	}
	if _, err := db.Exec(createChatTable); err != nil {
		return nil, err
	}
	if _, err := db.Exec(createMessageTable); err != nil {
		return nil, err
	}

	return db, nil
}

type User struct {
	sync.Mutex

	conn   net.Conn
	reader *bufio.Reader

	localID  int
	globalID string
}

func (user *User) isAuthorized() bool {
	return user.globalID != ""
}

type ChatServer struct {
	db *sql.DB

	lastUserID      int
	onlineUsers     map[int]*User
	authorizedUsers map[string]int

	openedChats   map[int]string
	openedChatsID map[int]int
	mu            sync.Mutex
}

func (server *ChatServer) run(socket net.Listener) {
	for {
		conn, err := socket.Accept()
		if err != nil {
			fmt.Println("Couldn't listen TCP client: ", err.Error())
			os.Exit(1)
		}

		go server.handleUser(conn, server.lastUserID)
		server.lastUserID++
	}
}

func (server *ChatServer) handleUser(conn net.Conn, localUserID int) {
	defer conn.Close()

	// Creating user
	var globalUserID string
	reader := bufio.NewReader(conn)

	user := &User{conn: conn, reader: reader, localID: localUserID, globalID: globalUserID}
	server.onlineUsers[localUserID] = user
	defer delete(server.onlineUsers, user.localID)

	for {
		// Request data is always split by NULL char
		bytes, err := user.reader.ReadBytes(byte('\000'))
		if err != nil {
			if err == io.EOF {
				break
			}

			switch err.(type) {
			case *net.OpError:
				// If getting OpError -> fetching next request to understand what's going on
				continue
			default:
				// DEBUG: printing reading error
				fmt.Println("Couldn't read data from TCP client: ", err)
			}
		}

		// If bytes is empty -> trying to read next
		if len(bytes) == 0 {
			continue
		}

		// Parsing request
		request := string(bytes[:len(bytes)-1])
		command, arguments, _ := strings.Cut(request, " ")

		switch command {
		case "auth":
			server.authHandler(user, arguments)
			defer delete(server.openedChats, user.localID)
			defer delete(server.authorizedUsers, user.globalID)
		case "register":
			server.registerHandler(user, arguments)
		case "users":
			server.listAllUsersHandler(user)
		case "online":
			server.listOnlineUsersHandler(user)
		case "open_chat":
			server.openChatHandler(user, arguments)
		case "send_message":
			server.sendMessageHandler(user, arguments)
		case "history":
			server.historyHandler(user)
		default:
			// DEBUG: printing unexpected command error
			fmt.Printf("Unexpected command from user %d: %s\n", localUserID, command)
		}
	}

	// DEBUG: printing client disconnected
	fmt.Printf("User %d disconnected\n", localUserID)
}

// ///////////////////////////////
// Response types
// ///////////////////////////////
func (server *ChatServer) sendFailed(user *User) {
	user.conn.Write([]byte("Failed\000"))
}

func (server *ChatServer) sendSuccess(user *User) {
	user.conn.Write([]byte("Success\000"))
}

// ///////////////////////////////
// Request handlers
// ///////////////////////////////

// Authorization
func (server *ChatServer) authHandler(user *User, arguments string) {
	userID, err := authorizeUser(server.db, arguments)
	if err != nil {
		// Send client why he couldn't authorize
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		response := fmt.Sprintf("Authorization failed: %s\000", err)
		user.conn.Write([]byte(response))
		user.Unlock()

		// DEBUG: printing authorization error
		fmt.Printf("Couldn't authorize user %d: %s\n", user.localID, err.Error())
		return
	}

	if _, ok := server.authorizedUsers[userID]; ok {
		// Send client why he couldn't authorize
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("Authorization failed: account is already used\000"))
		user.Unlock()

		// DEBUG: printing authorization error
		fmt.Printf("Couldn't authorize user %d: user already logged in\n", user.localID)
		return
	}

	// Setting userID
	user.globalID = userID

	// Allocating data for user
	server.authorizedUsers[user.globalID] = user.localID
	server.openedChats[user.localID] = ""

	// Sending authorization success to client
	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	user.Unlock()

	// DEBUG: printing client authorized
	fmt.Printf("User %d authorized: it is %s\n", user.localID, user.globalID)
}

func authorizeUser(db *sql.DB, arguments string) (userID string, err error) {
	// Parsing login and password from arguments
	login, password, found := strings.Cut(arguments, " ")
	if !found {
		err = errors.New("Couldn't parse arguments")
		return
	}

	// Checking user credentials for validness
	success := checkUserCredentials(db, login, password)
	if !success {
		err = errors.New("User credentials are invalid")
		return
	}

	// If we are here -> user passed credentials check
	userID = login
	return
}

func checkUserCredentials(db *sql.DB, login, password string) bool {
	row, _ := db.Query("SELECT * from users WHERE login=$1 AND password=$2", login, password)

	var _login, _password string
	i := 0
	for row.Next() {
		i++
		if err := row.Scan(&_login, &_password); err != nil {
			if err == sql.ErrNoRows {
				return false
			}

			fmt.Println("Error with DB happened: ", err)
			os.Exit(1)
		}
	}
	if i == 1 {
		return true
	}
	return false
}

// Register
func (server *ChatServer) registerHandler(user *User, arguments string) {
	err := registerUser(server.db, arguments)
	if err != nil {
		// Send client why he couldn't authorize
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		response := fmt.Sprintf("Registration failed: %s\000", err)
		user.conn.Write([]byte(response))
		user.Unlock()

		// DEBUG: printing authorization error
		fmt.Printf("Couldn't register user %d: %s\n", user.localID, err.Error())
		return
	}

	// // If user is registered -> authorizing
	// server.authHandler(user, arguments)
	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	user.Unlock()
}

func registerUser(db *sql.DB, arguments string) error {
	// Parsing login and password from arguments
	login, password, found := strings.Cut(arguments, " ")
	if !found {
		return errors.New("Couldn't parse arguments")
	}

	// Checking user login is already used
	registered := checkLoginRegistered(db, login)
	if registered {
		return errors.New("User is already registered")
	}

	// Registering user
	_, err := db.Exec("INSERT INTO users VALUES ($1, $2)", login, password)
	if !(err == nil) {
		fmt.Println("Error with DB happened: ", err)
		fmt.Println(login, password)
		os.Exit(1)
	}

	return nil
}

func checkLoginRegistered(db *sql.DB, login string) bool {
	const search_sql = `SELECT password from users WHERE login=$1`
	row, _ := db.Query(search_sql, login)

	var _password string
	for row.Next() {
		err := row.Scan(&_password)
		if err != nil {
			if err == sql.ErrNoRows {
				return false
			}

			fmt.Println("Error with DB happened: ", err)
			os.Exit(1)
		}
	}

	return true
}

// List users
func (server *ChatServer) listAllUsersHandler(user *User) {
	// Check if user is authorized
	if !user.isAuthorized() {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You are not authorized\000"))
		user.Unlock()
		return
	}

	// Collecting users info
	// TODO: wait until database is configured

	// Sending users
	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	user.conn.Write([]byte("0\000"))
	user.Unlock()
}

func (server *ChatServer) listOnlineUsersHandler(user *User) {
	// Check if user is authorized
	if !user.isAuthorized() {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You are not authorized\000"))
		user.Unlock()
		return
	}

	// Collecting online users into
	response := strconv.Itoa(len(server.authorizedUsers)) + "\000"
	for userID := range server.authorizedUsers {
		response += userID + "\000"
	}

	// Sending online users
	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	user.conn.Write([]byte(response))
	user.Unlock()
}

// Chats and messages
func (server *ChatServer) openChatHandler(user *User, arguments string) {
	// Check if user is authorized
	if !user.isAuthorized() {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You are not authorized\000"))
		user.Unlock()
		return
	}

	// Parsing user ID
	userID, _, _ := strings.Cut(arguments, " ")
	if !checkLoginRegistered(server.db, userID) {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("Target user is not registered\000"))
		user.Unlock()
		return
	}

	// Fetching chat ID
	chatID := getChat(server.db, user.globalID, userID)
	if chatID == -1 {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("Can't create chat with this user\000"))
		user.Unlock()
		return
	}

	fmt.Println("Opened ", chatID)

	// Setting opened chat for user
	server.openedChats[user.localID] = userID
	server.openedChatsID[user.localID] = chatID
	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	user.Unlock()
	// DEBUG: printing that user opened chat
	fmt.Printf("User %d opened chat with %s\n", user.localID, userID)
}

func getChat(db *sql.DB, user1, user2 string) int {
	ordering := strings.Compare(user1, user2)
	switch ordering {
	case 0:
		return -1
	case 1:
		user1, user2 = user2, user1
	}

	// Checking if we have such chat
	const query_sql = `SELECT id FROM chats WHERE user1=$1 AND user2=$2`
	const getMaxID_sql = `SELECT COALESCE(MAX(id), 0) FROM chats`
	const create_sql = `INSERT INTO chats (id, user1, user2) VALUES ($1, $2, $3)`

	var id int
	row := db.QueryRow(query_sql, user1, user2)
	if err := row.Scan(&id); err != nil {
		if err == sql.ErrNoRows {
			// If no row is found, get the max id and use it for the new row
			err := db.QueryRow(getMaxID_sql).Scan(&id)
			if err != nil {
				fmt.Println("Error with DB happened: ", err)
				os.Exit(1)
			}
			id++ // Increment the id for the new row

			_, err = db.Exec(create_sql, id, user1, user2)
			if err != nil {
				fmt.Println("Error with DB happened: ", err)
				os.Exit(1)
			}
		} else {
			fmt.Println("Error with DB happened: ", err)
			os.Exit(1)
		}
	}

	return id
}

func (server *ChatServer) sendMessageHandler(user *User, message string) {
	// Check if user is authorized
	if !user.isAuthorized() {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You are not authorized\000"))
		user.Unlock()
		return
	}

	userID := server.openedChats[user.localID]
	if userID == "" {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You have no chat opened\000"))
		user.Unlock()
		return
	}

	// Saving message to database
	const create_sql = `INSERT INTO messages (id, chat, sender, message) VALUES ($1, $2, $3, $4)`
	var id int
	err := server.db.QueryRow("SELECT COALESCE(MAX(id), 0) FROM messages").Scan(&id)
	if err != nil {
		fmt.Println("Error with DB happened: ", err)
		os.Exit(1)
	}
	id++ // Increment the id for the new message

	_, err = server.db.Exec(create_sql, id, server.openedChatsID[user.localID], user.globalID, message)
	if err != nil {
		fmt.Println("Error with DB happened: ", err)
		os.Exit(1)
	}

	// Replying with success to user
	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	user.Unlock()

	// Sending message to user, if he is online
	if id, ok := server.authorizedUsers[userID]; ok {
		otherUser := server.onlineUsers[id]

		// Locking user to have no intersection in responses
		otherUser.Lock()
		notification := fmt.Sprintf("ack %s", message)
		server.onlineUsers[id].conn.Write([]byte(notification))
		otherUser.Unlock()
	}
}

func (server *ChatServer) historyHandler(user *User) {
	// Check if user is authorized
	if !user.isAuthorized() {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You are not authorized\000"))
		user.Unlock()
		return
	}

	userID := server.openedChats[user.localID]
	if userID == "" {
		// Locking user to have no intersection in responses
		user.Lock()
		server.sendFailed(user)
		user.conn.Write([]byte("You have no chat opened\000"))
		user.Unlock()
		return
	}

	const query_sql = `SELECT id, sender, message FROM messages WHERE chat=$1 ORDER BY id ASC`

	// Loading history from database
	var history []string
	rows, err := server.db.Query(query_sql, server.openedChatsID[user.localID])
	if err != nil {
		fmt.Println("Error with DB happened: ", err)
		os.Exit(1)
	}

	for rows.Next() {
		var id int
		var sender, message string
		err = rows.Scan(&id, &sender, &message)
		if err != nil {
			fmt.Println("Error with DB happened: ", err)
			os.Exit(1)
		}

		history = append(history, fmt.Sprintf("%s: %s", sender, message))
	}

	// Locking user to have no intersection in responses
	user.Lock()
	server.sendSuccess(user)
	historyLength := strconv.Itoa(len(history)) + "\000"
	user.conn.Write([]byte(historyLength))

	if len(history) != 0 {
		historyStr := strings.Join(history, "\000") + "\000"
		user.conn.Write([]byte(historyStr))
	}

	user.Unlock()
}
