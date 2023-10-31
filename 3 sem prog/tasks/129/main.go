package main
import (
"fmt"
"math"
"os"
"strings"
"io/ioutil"
"strconv"
)

func getTextFromFile(filename string) (int, error) {
	file, err := os.Open(filename)
    if err != nil {
        return 0, err
    }
    defer file.Close()
    content, err := ioutil.ReadAll(file)
    if err != nil {
        return 0, err
    }
	values := strings.Split(string(content), " ")
	n, err1 := strconv.Atoi(values[0])
	if err1 != nil {
		return 0, err1
	}
    return n, nil
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

func reverse(s string) (result string) {
	for _,v := range s {
	  result = string(v) + result
	}
	return 
  }

func toBinarySystem(number int) string {
	result := ""
	for number > 0 {
		result += strconv.Itoa(number % 2)
		number /= 2
	}
	return reverse(result)
}

func toDecSystem(number string) (result int) {
	for i, char := range number {
		value, _ := strconv.Atoi(string(char))
		result += int(math.Pow(2, float64(len(number)-i-1))) * value
	}
	return
}

func getMax(number string) int {
	ar := []int {}
	for i := 0; i < len(number); i++ {
		if len(number) > 1 {
			number = string(number[len(number)-1]) + string(number[:len(number)-1])
		}
		ar = append(ar, toDecSystem(number))
	}
	max := ar[0]
	for i := 1; i < len(ar); i++ {
		if ar[i] > max {
			max = ar[i]
		}
	}
	return max
}

func main() {
	value, err := getTextFromFile("in.txt")
	if err != nil {
        fmt.Println(err)
        return
    }
	number := toBinarySystem(value)
	result := getMax(number)
	writeInfoIntoFile(result, "out.txt")
}