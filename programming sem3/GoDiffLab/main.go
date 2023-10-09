package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strings"

	"github.com/pmezard/go-difflib/difflib"
)

func main() {
	ignoreWhitespace := flag.Bool("b", false, "Игнорировать пробельные символы")
	ignoreCase := flag.Bool("i", false, "Игнорировать регистр букв")
	flag.Parse()

	args := flag.Args()
	if len(args) != 2 {
		fmt.Println("Использование: main.go [-b] [-i] original.txt new.txt")
		return
	}

	originalFileName := args[0]
	newFileName := args[1]

	originalLines, err := readLines(originalFileName)
	if err != nil {
		fmt.Println("Ошибка при чтении файла original.txt:", err)
		return
	}

	newLines, err := readLines(newFileName)
	if err != nil {
		fmt.Println("Ошибка при чтении файла new.txt:", err)
		return
	}

	diffs := diffText(originalLines, newLines, *ignoreWhitespace, *ignoreCase)

	for _, diff := range diffs {
		fmt.Println(diff)
	}
}

func readLines(fileName string) ([]string, error) {
	file, err := os.Open(fileName)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines, scanner.Err()
}

func diffText(original, new []string, ignoreWhitespace, ignoreCase bool) []string {
	if ignoreWhitespace {
		original = removeWhitespace(original)
		new = removeWhitespace(new)
	}

	if ignoreCase {
		original = toLowercase(original)
		new = toLowercase(new)
	}

	diff := difflib.UnifiedDiff{
		A:        difflib.SplitLines(strings.Join(original, "\n")),
		B:        difflib.SplitLines(strings.Join(new, "\n")),
		Context:  1,
		FromFile: "original.txt",
		FromDate: "",
		ToFile:   "new.txt",
		ToDate:   "",
	}

	text, _ := difflib.GetUnifiedDiffString(diff)

	return strings.Split(text, "\n")
}

func removeWhitespace(lines []string) []string {
	var result []string
	for _, line := range lines {
		line = strings.TrimSpace(line)
		if line != "" {
			result = append(result, line)
		}
	}
	return result
}

func toLowercase(lines []string) []string {
	var result []string
	for _, line := range lines {
		result = append(result, strings.ToLower(line))
	}
	return result
}
