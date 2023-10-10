package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

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

	result := make([]string, 0)

	i, j := 0, 0

	for i < len(lines1) && j < len(lines2) {
		if lines1[i] == lines2[j] {
			result = append(result, "  "+lines1[i])
			i++
			j++
		} else {
			foundDiff := false
			for x := i + 1; x < len(lines1); x++ {
				if lines1[x] == lines2[j] {
					for y := i; y < x; y++ {
						result = append(result, "< "+lines1[y])
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
							result = append(result, "> "+lines2[y])
						}
						j = x
						foundDiff = true
						break
					}
				}
			}

			if !foundDiff {
				result = append(result, "< "+lines1[i])
				result = append(result, "> "+lines2[j])
				i++
				j++
			}
		}
	}

	for i < len(lines1) {
		result = append(result, "< "+lines1[i])
		i++
	}

	for j < len(lines2) {
		result = append(result, "> "+lines2[j])
		j++
	}

	fmt.Println("result")
	for _, line := range result {
		fmt.Println(line)
	}
}
