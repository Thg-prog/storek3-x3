package main

import (
	"database/sql"
	"fmt"
	"net"
	"strings"
	"time"

	_ "github.com/mattn/go-sqlite3"
)

type user struct {
	id       int
	name     string
	password string
}

type message struct {
	id       int
	message  string
	fromUser string
	toUser   string
	date     string
}

func getUsersTable() []user {
	db, err := sql.Open("sqlite3", "../chat.db")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	rows, err := db.Query("SELECT id, name, password FROM users")
	if err != nil {
		panic(err)
	}
	defer rows.Close()
	users := []user{}
	for rows.Next() {
		u := user{}
		err := rows.Scan(&u.id, &u.name, &u.password)
		if err != nil {
			fmt.Println(err)
			continue
		}
		users = append(users, u)
	}
	return users
}

func insertIntoUsersTable(name string, password string) {
	db, err := sql.Open("sqlite3", "../chat.db")
	if err != nil {
		panic(err)
	}
	defer db.Close()

	stmt, err := db.Prepare("INSERT INTO users(name, password) VALUES (?, ?)")
	if err != nil {
		fmt.Println("Error preparing statement:", err)
		return
	}
	defer stmt.Close()

	_, err = stmt.Exec(name, password)
	if err != nil {
		fmt.Println("Error inserting record:", err)
		return
	}

	fmt.Println("Record added successfully")
}

func deleteUser(name string) {
	db, err := sql.Open("sqlite3", "../chat.db")
	if err != nil {
		panic(err)
	}
	defer db.Close()

	_, err = db.Exec("DELETE FROM users WHERE name=?", name)
	if err != nil {
		fmt.Println("Error inserting record:", err)
		return
	}
	fmt.Println("Record deleted successfully")
}

func getMessagesTable(fromUser string, toUser string) []message {
	db, err := sql.Open("sqlite3", "../chat.db")
	if err != nil {
		panic(err)
	}
	defer db.Close()
	rows, err := db.Query("SELECT id, message, fromUser, toUser, date FROM messages WHERE (fromUser = ? AND toUser = ?) OR (toUser = ? AND fromUser = ?)", fromUser, toUser, fromUser, toUser)
	if err != nil {
		panic(err)
	}
	defer rows.Close()
	messages := []message{}
	for rows.Next() {
		m := message{}
		err := rows.Scan(&m.id, &m.message, &m.fromUser, &m.toUser, &m.date)
		if err != nil {
			fmt.Println(err)
			continue
		}
		messages = append(messages, m)
	}
	return messages
}

func insertIntoMessagesTable(message string, fromUser string, toUser string, date string) {
	db, err := sql.Open("sqlite3", "../chat.db")
	if err != nil {
		panic(err)
	}
	defer db.Close()

	stmt, err := db.Prepare("INSERT INTO messages(message, fromUser, toUser, date) VALUES (?, ?, ?, ?)")
	if err != nil {
		fmt.Println("Error preparing statement:", err)
		return
	}
	defer stmt.Close()

	_, err = stmt.Exec(message, fromUser, toUser, date)
	if err != nil {
		fmt.Println("Error inserting record:", err)
		return
	}

	fmt.Println("Record added successfully")
}

func handleConnection(conn net.Conn) {
	defer conn.Close()
	for {
		input := make([]byte, (1024))
		n, err := conn.Read(input)
		if n == 0 || err != nil {
			fmt.Println("Read error:", err)
			break
		}
		source := strings.Split(string(input[0:n]), "\n")
		users := getUsersTable()
		param1 := source[1]
		param2 := source[2]
		if source[0] == "reg" {
			flag := false
			str := ""
			for _, u := range users {
				str += u.name + "\n"
				if u.name == param1 {
					flag = true
				}
			}
			if !flag {
				insertIntoUsersTable(param1, param2)
				conn.Write([]byte("yes\n" + str))
			} else {
				conn.Write([]byte("no"))
			}
		} else if source[0] == "auth" {
			flag := false
			str := ""
			for _, u := range users {
				str += u.name + "\n"
				if u.name == param1 && u.password == param2 {
					flag = true
				}
			}
			if flag {
				conn.Write([]byte("yes\n" + str))
			} else {
				conn.Write([]byte("no"))
			}
		} else if source[0] == "del" {
			deleteUser(param1)
		} else if source[0] == "getMessages" {
			messages := getMessagesTable(param1, param2)
			str := ""
			for _, m := range messages {
				str += m.fromUser + "(" + m.date + "): " + m.message + "\n"
			}
			conn.Write([]byte("getMessages\n" + str))
		} else if source[0] == "insertMessages" {
			date := time.Now().String()
			user_date := strings.Split(date, " ")
			string_date := user_date[0] + " " + strings.Split(user_date[1], ".")[0]
			insertIntoMessagesTable(source[3], param1, param2, string_date)
		} else if source[0] == "getUserList" {
			str := ""
			for _, u := range users {
				str += u.name + "\n"
			}
			conn.Write([]byte("getUserList\n" + str))
		}
	}
}

func main() {
	listener, err := net.Listen("tcp", "127.0.0.1:4545")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer listener.Close()
	fmt.Println("Server is listening...")
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println(err)
			conn.Close()
			continue
		}
		go handleConnection(conn)
	}
}
