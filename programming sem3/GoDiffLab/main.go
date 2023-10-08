package main

import (
	"bufio"
	"fmt"
	"os"
	_ "strings"

	"github.com/pmezard/go-difflib/difflib"
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
	addedStrings := make([]string, 0)
	deletedStrings := make([]string, 0)
	modifiedStrings := make([]string, 0)

	fmt.Println("0a1,", lineNumber-1)

	scanner2 := bufio.NewScanner(file2)
	for scanner2.Scan() {
		line := scanner2.Text()
		if _, exists := linesMap[line]; !exists {
			addedStrings = append(addedStrings, fmt.Sprintf(">%s\n", line))
		}
		delete(linesMap, line)

		// Сравниваем строки с помощью difflib
		diff := difflib.UnifiedDiff{
			A:        difflib.SplitLines(line),
			B:        difflib.SplitLines(line),
			FromFile: "File1",
			ToFile:   "File2",
			Context:  0,
		}
		textDiff, _ := difflib.GetUnifiedDiffString(diff)
		if textDiff != "" {
			modifiedStrings = append(modifiedStrings, textDiff)
		}
	}

	for deletedLine, lineNum := range linesMap {
		deletedStrings = append(deletedStrings, fmt.Sprintf("<%s в строке %d\n", deletedLine, lineNum))
	}

	for _, str := range addedStrings {
		fmt.Print(str)
	}

	for _, str := range modifiedStrings {
		fmt.Print(str)
	}

	for _, str := range deletedStrings {
		fmt.Print(str)
	}

	if err := scanner1.Err(); err != nil {
		fmt.Println("Ошибка при чтении файла 1:", err)
	}

	if err := scanner2.Err(); err != nil {
		fmt.Println("Ошибка при чтении файла 2:", err)
	}
}
