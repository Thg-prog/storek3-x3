package main

import (
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

func main() {
	file1, err1 := ioutil.ReadFile("1.txt")
	if err1 != nil {
		fmt.Println("Ошибка при чтении файла 1.txt:", err1)
		return
	}

	file2, err2 := ioutil.ReadFile("2.txt")
	if err2 != nil {
		fmt.Println("Ошибка при чтении файла 2.txt:", err2)
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
		if lines1[i] == lines2[j] {
			i++
			j++
			lineNumber1++
			lineNumber2++
		} else {
			foundDiff := false
			for x := i + 1; x < len(lines1); x++ {
				if lines1[x] == lines2[j] {
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
					if lines2[x] == lines1[i] {
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
				if currentBlock.StartLineNumber == 0 {
					currentBlock.StartLineNumber = lineNumber1
				}
				currentBlock.EndLineNumber = lineNumber1
				differences = append(differences, Difference{Type: "<", Start: lineNumber1, End: lineNumber1, Text: lines1[i]})
				differences = append(differences, Difference{Type: ">", Start: lineNumber2, End: lineNumber2, Text: lines2[j]})
				i++
				j++
				lineNumber1++
				lineNumber2++
			}
		}
	}

	if currentBlock.StartLineNumber > 0 {
		blocks = append(blocks, currentBlock)
	}

	for i < len(lines1) {
		differences = append(differences, Difference{Type: "<", Start: lineNumber1, End: lineNumber1, Text: lines1[i]})
		i++
		lineNumber1++
	}

	for j < len(lines2) {
		differences = append(differences, Difference{Type: ">", Start: lineNumber2, End: lineNumber2, Text: lines2[j]})
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
				fmt.Printf("%d a %d,%d\n", differences[startIndex].Start, differences[startIndex].Start, differences[endIndex-1].End)
			}
			for j := startIndex; j < endIndex; j++ {
				fmt.Printf("%d %s %s\n", differences[j].Start, differences[j].Type, differences[j].Text)
			}
			i = endIndex
		} else if differences[i].Type == "<" {
			startIndex := i
			endIndex := i
			for endIndex < len(differences) && differences[endIndex].Type == "<" {
				endIndex++
			}
			blocks = append(blocks, DifferenceBlock{StartLineNumber: differences[startIndex].Start, EndLineNumber: differences[endIndex-1].End})
			fmt.Printf("%d d %d,%d\n", differences[startIndex].Start, differences[startIndex].Start, differences[endIndex-1].End)
			for j := startIndex; j < endIndex; j++ {
				fmt.Printf("%d %s %s\n", differences[j].Start, differences[j].Type, differences[j].Text)
			}
			i = endIndex
		} else {
			fmt.Printf("%d %s %s\n", differences[i].Start, differences[i].Type, differences[i].Text)
			i++
		}
	}
}
