package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

func isPrime(n int) bool {
	if n <= 1 {
		return false
	}
	if n <= 3 {
		return true
	}
	if n%2 == 0 || n%3 == 0 {
		return false
	}

	i := 5
	for i*i <= n {
		if n%i == 0 || n%(i+2) == 0 {
			return false
		}
		i += 6
	}
	return true
}

func primes(a, b int) []int {
	var primeNumbers []int
	for i := a; i <= b; i++ {
		if isPrime(i) {
			primeNumbers = append(primeNumbers, i)
		}
	}
	return primeNumbers
}

func main() {
	n, m := 1, 100000
	inputFileName := "/Users/anton/Documents/storek3-x3/programming sem3/task124ThreeNumbers/input.txt"
	outputFileName := "/Users/anton/Documents/storek3-x3/programming sem3/task124ThreeNumbers/output.txt"

	data, err := ioutil.ReadFile(inputFileName)
	if err != nil {
		log.Fatalf("Ошибка при чтении файла ввода: %v", err)
	}

	values := strings.Fields(string(data))
	if len(values) != 2 {
		log.Fatalf("Файл ввода должен содержать два числа, разделенных пробелом.")
	}

	n, err = strconv.Atoi(values[0])
	if err != nil {
		log.Fatalf("Ошибка при преобразовании первого числа: %v", err)
	}

	m, err = strconv.Atoi(values[1])
	if err != nil {
		log.Fatalf("Ошибка при преобразовании второго числа: %v", err)
	}

	pr := primes(n, m)
	pair := make([][2]int, 0)
	for i := 0; i <= int(math.Sqrt(float64(m/2))); i++ {
		pair = append(pair, [2]int{i * i, (i + 1) * (i + 1)})
	}

	cnt := 0
	for _, elem := range pair {
		for _, p := range pr {
			a := elem[0] * p
			b := elem[1] * p
			if a >= n && b <= m {
				cnt++
			}
		}
	}
	outputFile, err := os.Create(outputFileName)
	if err != nil {
		log.Fatalf("Ошибка при создании файла вывода: %v", err)
	}
	defer outputFile.Close()

	_, err = fmt.Fprintf(outputFile, "%d \n", cnt)
	if err != nil {
		log.Fatalf("Ошибка при записи в файл вывода: %v", err)
	}
	fmt.Println(cnt)
}
