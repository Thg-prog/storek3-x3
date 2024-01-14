package main

import (
	"fmt"
	"net"
	"strings"
	"time"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
)

func choose(conn net.Conn, myWindow fyne.Window) {
	enter_button := widget.NewButton("Войти", func() {
		authorization(conn, myWindow)
	})
	registration_button := widget.NewButton("Зарегистрироваться", func() {
		registration(conn, myWindow)
	})
	myWindow.SetContent(container.NewCenter(container.NewVBox(enter_button, registration_button)))
}

func authorization(conn net.Conn, myWindow fyne.Window) {
	nameEntry := widget.NewEntry()
	passwordEntry := widget.NewPasswordEntry()
	label := widget.NewLabel("Неправильный логин или пароль!!!")
	label.Hide()
	form := widget.NewForm(
		widget.NewFormItem("Имя пользователя", nameEntry),
		widget.NewFormItem("Пароль", passwordEntry),
		widget.NewFormItem("", label),
	)
	form.SubmitText = "Войти"
	form.CancelText = "Закрыть"
	form.OnSubmit = func() {
		label.Hide()
		fmt.Fprintf(conn, "auth"+"\n"+nameEntry.Text+"\n"+passwordEntry.Text+"\n")
		message := readInfo(conn)
		if message[0] == "no" {
			label.Show()
		} else {
			listOfUsers(nameEntry.Text, message[1:len(message)-1], conn, myWindow)
		}
	}
	form.OnCancel = func() {
		myWindow.Close()
	}
	myWindow.SetContent(container.NewCenter(container.NewVBox(form)))
}

func readInfo(conn net.Conn) []string {
	buff := make([]byte, 1024)
	n, _ := conn.Read(buff)
	message := strings.Split(string(buff[0:n]), "\n")
	return message
}

func registration(conn net.Conn, myWindow fyne.Window) {
	nameEntry := widget.NewEntry()
	passwordEntry := widget.NewPasswordEntry()
	label := widget.NewLabel("Данный пользователь уже существует!!!")
	label.Hide()
	form := widget.NewForm(
		widget.NewFormItem("Имя пользователя", nameEntry),
		widget.NewFormItem("Пароль", passwordEntry),
		widget.NewFormItem("", label),
	)
	form.SubmitText = "Зарегистрироваться"
	form.CancelText = "Закрыть"
	form.OnSubmit = func() {
		label.Hide()
		fmt.Fprintf(conn, "reg"+"\n"+nameEntry.Text+"\n"+passwordEntry.Text+"\n")
		message := readInfo(conn)
		if message[0] == "no" {
			label.Show()
		} else {
			listOfUsers(nameEntry.Text, message[1:len(message)-1], conn, myWindow)
		}
	}
	form.OnCancel = func() {
		myWindow.Close()
	}
	myWindow.SetContent(container.NewCenter(container.NewVBox(form)))
}

func listOfUsers(current_name string, names []string, conn net.Conn, myWindow fyne.Window) {
	id := -1
	for i := range names {
		if names[i] == current_name {
			id = i
			break
		}
	}
	if id != -1 {
		copy(names[id:], names[id+1:])
		names = names[:len(names)-1]
	}
	names = append(names, "Удалить аккаунт")
	list := widget.NewList(
		func() int {
			return len(names)
		},
		func() fyne.CanvasObject {
			return widget.NewButton("", func() {})
		},
		func(id widget.ListItemID, obj fyne.CanvasObject) {
			obj.(*widget.Button).SetText(names[id])
			obj.(*widget.Button).OnTapped = func() {
				if id == len(names)-1 {
					fmt.Fprintf(conn, "del\n"+current_name+"\n\n")
					myWindow.Close()
				} else {
					fmt.Fprintf(conn, "getMessages\n"+current_name+"\n"+names[id]+"\n")
					messages := readInfo(conn)
					if messages[0] == "getMessages" {
						listOfMessages(current_name, names[id], messages, conn, myWindow)
						names = []string{}
					}
				}
			}
		},
	)
	fmt.Fprintf(conn, "getUserList\n\n")
	names = readInfo(conn)
	if names[0] == "getUserList" {
		names = names[1 : len(names)-1]
		id = -1
		for i := range names {
			if names[i] == current_name {
				id = i
				break
			}
		}
		if id != -1 {
			copy(names[id:], names[id+1:])
			names = names[:len(names)-1]
		}
		names = append(names, "Удалить аккаунт")
	}
	list.Refresh()
	myWindow.SetContent(list)
}

func listOfMessages(current_name string, another_name string, messages []string, conn net.Conn, myWindow fyne.Window) {
	if len(messages) > 1 {
		messages = messages[:len(messages)-1]
		messages[0] = "Чат с " + another_name
	} else {
		messages = []string{}
	}
	list := widget.NewList(
		func() int {
			return len(messages)
		},
		func() fyne.CanvasObject {
			return widget.NewLabel("")
		},
		func(id widget.ListItemID, obj fyne.CanvasObject) {
			obj.(*widget.Label).SetText(messages[id])
		},
	)
	entry := widget.NewEntry()
	addButton := widget.NewButton("Отправить", func() {
		fmt.Fprintf(conn, "insertMessages\n"+current_name+"\n"+another_name+"\n"+entry.Text+"\n")
		entry.Text = ""
		entry.Refresh()
	})
	go func() {
		for {
			time.Sleep(1 * time.Millisecond)
			fmt.Fprintf(conn, "getMessages\n"+current_name+"\n"+another_name+"\n")
			messages = readInfo(conn)
			if messages[0] == "getMessages" {
				messages = messages[:len(messages)-1]
				messages[0] = "Чат с " + another_name
				list.Refresh()
			}
		}
	}()
	myWindow.SetContent(container.NewVSplit(list, container.NewVBox(entry, addButton)))
}

func main() {
	conn, err := net.Dial("tcp", "127.0.0.1:4545")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer conn.Close()
	myApp := app.New()
	myWindow := myApp.NewWindow("Чат")
	myWindow.Resize(fyne.NewSize(700, 700))
	choose(conn, myWindow)
	myWindow.ShowAndRun()
}
