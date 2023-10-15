package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

type Diff struct {
	line    string
	modify  string
	linenum int
}

type DiffBlock struct {
	sign      string
	lines     []string
	StartLine int
	EndLine   int
	modify    string
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

	dif := compare(lines1, lines2)
	printDifferences(outputBuilder(dif))
}

func compare(lines1, lines2 []string) []Diff {
	differences := make([]Diff, 0)

	for i, line2 := range lines2 {
		found := false
		for o, line1 := range lines1 {
			if line1 == line2 && !isDifferent(line1, line2) {
				found = true

				lines1 = append(lines1[:o], lines1[o+1:]...)

				break
			}
		}

		if !found {
			differences = append(differences, Diff{line: line2, modify: "a", linenum: i})
		}
	}

	for i, line2 := range lines2 {
		for o, line1 := range lines1 {
			if line1 != line2 && !isDifferent(line1, line2) {
				differences = append(differences, Diff{line: line2, modify: "c", linenum: i})
				lines1 = append(lines1[:o], lines1[o+1:]...)
				break
			}
		}
	}

	for _, line1 := range lines1 {
		differences = append(differences, Diff{line: line1, modify: "d"})
	}

	/*for i := 0; i < len(lines1); i++ {
		for o := 0; o < len(lines2); o++ {
			if lines1[i] != lines2[o] && !isDifferent(lines1[i], lines2[o]) {
				differences = append(differences, Diff{line: lines2[o], modify: "c", linenum: i})
			}
		}
	}*/

	return differences
}

func getSign(mod string) string {
	if mod == "a" {
		return ">"
	} else {
		return "<"
	}
}

func outputBuilder(diff []Diff) []DiffBlock {
	var diffBlocks []DiffBlock

	if len(diff) == 0 {
		return diffBlocks
	}

	currentBlock := DiffBlock{
		sign:      "",
		lines:     make([]string, 0),
		StartLine: 0,
		EndLine:   0,
		modify:    diff[0].modify,
	}

	for i, d := range diff {
		if i == 0 {

			currentBlock.sign = getSign(d.modify)
			currentBlock.StartLine = i + 1
		}

		if currentBlock.modify != d.modify {
			currentBlock.EndLine = i
			diffBlocks = append(diffBlocks, currentBlock)
			currentBlock = DiffBlock{
				sign:      getSign(d.modify),
				lines:     make([]string, 0),
				StartLine: i + 1,
				EndLine:   0,
				modify:    d.modify,
			}
		}

		currentBlock.lines = append(currentBlock.lines, d.line)

		if i == len(diff)-1 {
			currentBlock.EndLine = i + 1
			diffBlocks = append(diffBlocks, currentBlock)
		}
	}

	return diffBlocks
}

func printDifferences(diffBlocks []DiffBlock) {
	for _, block := range diffBlocks {
		fmt.Printf("%d%s%d,%d\n", block.StartLine, block.modify, block.StartLine, block.EndLine)
		for _, line := range block.lines {
			fmt.Printf("%s%s\n", block.sign, line)
		}
	}
}

func isDifferent(line1, line2 string) bool {
	m, n := len(line1), len(line2)

	dp := make([][]int, m+1)
	for i := range dp {
		dp[i] = make([]int, n+1)
	}

	for i := 0; i <= m; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= n; j++ {
		dp[0][j] = j
	}

	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			cost := 0
			if line1[i-1] != line2[j-1] {
				cost = 1
			}
			dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+cost)
		}
	}

	return dp[m][n] > (max(m, n) / 10)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

/*func isDifferent(line1, line2 string) bool {
	line1_len, line2_len := float64(len(line1)), float64(len(line2))
	if math.Abs(line1_len-line2_len) > (math.Max(line1_len, line2_len) / 2) {
		return true
	}
	dif := 0
	for i := 0; i < int(math.Min(line1_len, line2_len)); i++ {
		if line1[i] != line2[i] {
			dif++
		}
	}
	if dif > int(math.Max(line1_len, line2_len))/2 {
		return true
	}
	return false
}*/

/*
func compare(lines1, lines2 []string) []Diff {
	i, j := 0, 0
	differences := make([]Diff, 0)
	for i < len(lines1) && j < len(lines2) {
		if lines1[i] == lines2[j] {
			i++
			j++
		} else {
			for x := i + 1; x < len(lines2); x++ {
				if lines1[i] != lines2[x] {
					if isDifferent(lines1[i], lines2[x]) {
						differences = append(differences, Diff{line: lines2[x], modify: "d", linenum: x})
					} else if !isDifferent(lines1[i], lines2[x]) && lines1[i] != lines2[x] {
						differences = append(differences, Diff{line: lines2[x], modify: "c", linenum: x})
					}
				}
				break
			}
			i++
			j++
		}
	}
	for i := 0; i < len(lines2); i++ {
		flag := false
		for o := 0; o < len(lines1); o++ {
			if isDifferent(lines2[i], lines1[o]) == true {

				flag = true

			}
		}
		if flag == true {
			differences = append(differences, Diff{line: lines2[i], modify: "a", linenum: i})
		}
	}
	return differences
}*/
