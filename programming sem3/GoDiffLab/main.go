package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	// Открываем первый файл для чтения
	file1, err := os.Open("1.txt")
	if err != nil {
		fmt.Println("Ошибка при открытии файла 1:", err)
		return
	}
	defer file1.Close()

	// Открываем второй файл для чтения
	file2, err := os.Open("2.txt")
	if err != nil {
		fmt.Println("Ошибка при открытии файла 2:", err)
		return
	}
	defer file2.Close()

	// Создаем map для хранения строк из первого файла и их номеров
	linesMap := make(map[string]int)

	// Считываем строки из первого файла и добавляем их в map
	scanner1 := bufio.NewScanner(file1)
	lineNumber := 1
	for scanner1.Scan() {
		line := scanner1.Text()
		linesMap[line] = lineNumber
		lineNumber++
	}

	// Считываем строки из второго файла и выводим их в указанном формате
	addStrings := make([]string, 0)
	fmt.Println("0a1,", lineNumber-1)

	scanner2 := bufio.NewScanner(file2)
	for scanner2.Scan() {
		line := scanner2.Text()
		if _, exists := linesMap[line]; !exists {
			addStrings = append(addStrings, fmt.Sprintf(">%s\n", line))

			//prevLineNum = lineNum
		}
	}

	for _, str := range addStrings {
		fmt.Print(str)
	}

	if err := scanner1.Err(); err != nil {
		fmt.Println("Ошибка при чтении файла 1:", err)
	}

	if err := scanner2.Err(); err != nil {
		fmt.Println("Ошибка при чтении файла 2:", err)
	}
}
