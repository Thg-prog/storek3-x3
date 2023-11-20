package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func minInsertionsToMakeValid(s string) int {
	stack := make([]rune, 0)
	insertions := 0

	for _, char := range s {
		if char == '(' || char == '{' || char == '[' {
			stack = append(stack, char)
		} else {
			if len(stack) == 0 {
				insertions++
			} else {
				top := stack[len(stack)-1]
				if (char == ')' && top == '(') ||
					(char == '}' && top == '{') ||
					(char == ']' && top == '[') {
					stack = stack[:len(stack)-1]
				} else {
					insertions++
				}
			}
		}
	}

	insertions += len(stack)

	return insertions
}

func main() {
	filePath := "input.txt"

	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		fmt.Printf("Ошибка чтения файла: %v\n", err)
		return
	}

	s := string(data)
	minInsertions := minInsertionsToMakeValid(s)
	outputFile, err := os.Create("output.txt")
	if err != nil {
		fmt.Println("Ошибка при создании файла вывода:", err)
		return
	}
	defer outputFile.Close()

	fmt.Fprintf(outputFile, "%d\n", minInsertions)
}
