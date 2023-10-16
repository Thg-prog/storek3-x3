package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"sort"
	"strings"
)

type Difference struct {
	Type  string
	Start int
	End   int
	Text  string
}

type DifferenceBlock struct {
	StartLineNumber int
	EndLineNumber   int
}

var (
	ignoreWhitespace bool
	ignoreCase       bool
)

func main() {
	flag.BoolVar(&ignoreWhitespace, "b", false, "Игнорировать пробельные символы")
	flag.BoolVar(&ignoreCase, "i", false, "Игнорировать регистр букв")
	flag.Parse()
	ln := len(flag.Args())

	if ln != 2 {
		fmt.Println("Использование: программа файл1 файл2")
		return
	}
	file1Name := flag.Arg(0)
	file2Name := flag.Arg(1)

	file1, err1 := ioutil.ReadFile(file1Name)
	if err1 != nil {
		fmt.Printf("Ошибка при чтении файла %s: %v\n", file1Name, err1)
		return
	}

	file2, err2 := ioutil.ReadFile(file2Name)
	if err2 != nil {
		fmt.Printf("Ошибка при чтении файла %s: %v\n", file2Name, err2)
		return
	}

	lines1 := strings.Split(string(file1), "\n")
	lines2 := strings.Split(string(file2), "\n")

	differences, blocks := compareLines(lines1, lines2)

	printDifferences(differences, blocks)
}

func compareLines(lines1, lines2 []string) ([]Difference, []DifferenceBlock) {
	differences := make([]Difference, 0)
	blocks := make([]DifferenceBlock, 0)
	currentBlock := DifferenceBlock{}
	lineNumber1, lineNumber2 := 1, 1

	i, j := 0, 0

	for i < len(lines1) && j < len(lines2) {
		line1 := lines1[i]
		line2 := lines2[j]

		if ignoreCase {
			line1 = strings.ToLower(line1)
			line2 = strings.ToLower(line2)
		}

		if ignoreWhitespace {
			line1 = strings.ReplaceAll(line1, " ", "")
			line2 = strings.ReplaceAll(line2, " ", "")
			line1 = strings.ReplaceAll(line1, "\t", "")
			line2 = strings.ReplaceAll(line2, "\t", "")
		}

		if line1 == line2 {
			i++
			j++
			lineNumber1++
			lineNumber2++
		} else {
			foundDiff := false
			for x := i + 1; x < len(lines1); x++ {
				tempLine1 := lines1[x]

				if ignoreCase {
					tempLine1 = strings.ToLower(tempLine1)
				}

				if ignoreWhitespace {
					tempLine1 = strings.ReplaceAll(tempLine1, " ", "")
					tempLine1 = strings.ReplaceAll(tempLine1, "\t", "")
				}

				if tempLine1 == line2 {
					for y := i; y < x; y++ {
						differences = append(differences, Difference{Type: "<", Start: lineNumber1, End: lineNumber1, Text: lines1[y]})
						lineNumber1++
					}
					i = x
					foundDiff = true
					break
				}
			}

			if !foundDiff {
				for x := j + 1; x < len(lines2); x++ {
					tempLine2 := lines2[x]

					if ignoreCase {
						tempLine2 = strings.ToLower(tempLine2)
					}

					if ignoreWhitespace {
						tempLine2 = strings.ReplaceAll(tempLine2, " ", "")
						tempLine2 = strings.ReplaceAll(tempLine2, "\t", "")
					}

					if tempLine2 == line1 {
						for y := j; y < x; y++ {
							differences = append(differences, Difference{Type: ">", Start: lineNumber2, End: lineNumber2, Text: lines2[y]})
							lineNumber2++
						}
						j = x
						foundDiff = true
						break
					}
				}
			}

			if !foundDiff {
				diffCount := 0
				for c := 0; c < len(line1) && c < len(line2); c++ {
					if line1[c] != line2[c] {
						diffCount++
					}
				}
				// Проверяем, не превышает ли количество различных символов половину длины строки
				if diffCount <= len(line1)/2 {
					if currentBlock.StartLineNumber == 0 {
						currentBlock.StartLineNumber = lineNumber1
					}
					currentBlock.EndLineNumber = lineNumber1
					differences = append(differences, Difference{Type: "c", Start: lineNumber1, End: lineNumber2, Text: line1})
					differences = append(differences, Difference{Type: "c", Start: lineNumber1, End: lineNumber2, Text: line2})
					i++
					j++
					lineNumber1++
					lineNumber2++
				} else {
					if currentBlock.StartLineNumber == 0 {
						currentBlock.StartLineNumber = lineNumber1
					}
					currentBlock.EndLineNumber = lineNumber1
					differences = append(differences, Difference{Type: "<", Start: lineNumber1, End: lineNumber1, Text: line1})
					differences = append(differences, Difference{Type: ">", Start: lineNumber2, End: lineNumber2, Text: line2})
					i++
					j++
					lineNumber1++
					lineNumber2++
				}
			}
		}
	}

	if currentBlock.StartLineNumber > 0 {
		blocks = append(blocks, currentBlock)
	}

	for i < len(lines1) {
		line1 := lines1[i]

		if ignoreCase {
			line1 = strings.ToLower(line1)
		}

		if ignoreWhitespace {
			line1 = strings.ReplaceAll(line1, " ", "")
			line1 = strings.ReplaceAll(line1, "\t", "")
		}

		differences = append(differences, Difference{Type: "<", Start: lineNumber1, End: lineNumber1, Text: line1})
		i++
		lineNumber1++
	}

	for j < len(lines2) {
		line2 := lines2[j]

		if ignoreCase {
			line2 = strings.ToLower(line2)
		}

		if ignoreWhitespace {
			line2 = strings.ReplaceAll(line2, " ", "")
			line2 = strings.ReplaceAll(line2, "\t", "")
		}

		differences = append(differences, Difference{Type: ">", Start: lineNumber2, End: lineNumber2, Text: line2})
		j++
		lineNumber2++
	}

	sort.Slice(differences, func(i, j int) bool {
		return differences[i].Start < differences[j].Start
	})

	return differences, blocks
}

func printDifferences(differences []Difference, blocks []DifferenceBlock) {
	fmt.Println("Результат сравнения:")
	insideChangeBlock := false // Новая переменная
	comparedStart := 0
	comparedEnd := 0

	for i := 0; i < len(differences); {
		if differences[i].Type == ">" {
			startIndex := i
			endIndex := i
			for endIndex < len(differences) && differences[endIndex].Type == ">" {
				endIndex++
			}
			blocks = append(blocks, DifferenceBlock{StartLineNumber: differences[startIndex].Start, EndLineNumber: differences[endIndex-1].End})
			if differences[startIndex].Start == 1 {
				fmt.Printf("%d a %d,%d\n", differences[startIndex].Start-1, differences[startIndex].Start, differences[endIndex-1].End)
			} else {
				fmt.Printf("%d a %d,%d\n", differences[startIndex].Start-1, differences[startIndex].Start, differences[endIndex-1].End)
			}
			for j := startIndex; j < endIndex; j++ {
				fmt.Printf("%s %s\n", differences[j].Type, differences[j].Text)
			}
			i = endIndex
			insideChangeBlock = false // Сбрасываем флаг блока изменений
		} else if differences[i].Type == "<" {
			startIndex := i
			endIndex := i
			for endIndex < len(differences) && differences[endIndex].Type == "<" {
				endIndex++
			}
			blocks = append(blocks, DifferenceBlock{StartLineNumber: differences[startIndex].Start, EndLineNumber: differences[endIndex-1].End})
			fmt.Printf("%d d %d,%d\n", differences[startIndex].Start, differences[startIndex].Start, differences[endIndex-1].End)
			for j := startIndex; j < endIndex; j++ {
				fmt.Printf("%s %s\n", differences[j].Type, differences[j].Text)
			}
			i = endIndex
			insideChangeBlock = false // Сбрасываем флаг блока изменений
		} else if differences[i].Type == "c" {
			startIndex := i
			endIndex := i
			for endIndex < len(differences) && differences[endIndex].Type == "c" {
				endIndex++
			}
			blocks = append(blocks, DifferenceBlock{StartLineNumber: differences[startIndex].Start, EndLineNumber: differences[endIndex-1].End})
			fmt.Printf("%d c %d\n", differences[startIndex].Start, differences[endIndex-1].End)

			// Включаем флаг блока изменений
			insideChangeBlock = true
			comparedStart = differences[startIndex].Start
			comparedEnd = differences[endIndex-1].End
			for j := startIndex; j < endIndex; j++ {
				if j == startIndex {
					fmt.Printf("< %s \n", differences[j].Text)
				} else {
					fmt.Printf("> %s \n", differences[j].Text)
				}

				if j < endIndex-1 {
					fmt.Println("---")
				}
			}
			i = endIndex
		} else {
			fmt.Printf("%d %s %s\n", differences[i].Start, differences[i].Type, differences[i].Text)
			i++
			insideChangeBlock = false // Сбрасываем флаг блока изменений
		}

		// Пропускаем удаленные строки, если внутри блока изменений
		for i < len(differences) && insideChangeBlock && differences[i].Type == "<" && differences[i].Start > comparedStart && differences[i].End < comparedEnd+2 {
			i++
		}
		insideChangeBlock = false
	}
}
