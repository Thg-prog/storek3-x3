package main
import (
"fmt"
"math"
"os"
"strings"
"io/ioutil"
"strconv"
)

func getTextFromFile(filename string) (int, int, error) {
	file, err := os.Open(filename)
    if err != nil {
        return 0, 0, err
    }
    defer file.Close()
    content, err := ioutil.ReadAll(file)
    if err != nil {
        return 0, 0, err
    }
	values := strings.Split(string(content), " ")
	n, _ := strconv.Atoi(values[0])
	m, _ := strconv.Atoi(values[1])
    return n, m, nil
}

func writeInfoIntoFile(number int, filename string) {
	file, err := os.Create(filename)
    if err != nil{
        fmt.Println("Unable to create file:", err) 
        os.Exit(1) 
    }
    defer file.Close() 
    file.WriteString(strconv.Itoa(number))
}

func isPrimeNumber(number int) bool {
	for i := 2; i <= number / 2; i++ {
		if number % i == 0 {
			return false
		}
	}
	return true
}

func getCount(n int, m int) int {
	ar := []int {}
	for i := n; i <= m; i++ {
		ar = append(ar, i)
	}
	count := 0
	for _, a := range ar {
		for _, b := range ar {
			for _, p := range ar {
				if math.Sqrt(float64(a)) - math.Sqrt(float64(b)) == math.Sqrt(float64(p)) && isPrimeNumber(p) {
					count++
				}
			}
		}
	}
	return count
}

func main() {
	n, m, err := getTextFromFile("in.txt")
	if err != nil {
        fmt.Println(err)
        return
    }
	count := getCount(n, m)
	writeInfoIntoFile(count, "out.txt")
}