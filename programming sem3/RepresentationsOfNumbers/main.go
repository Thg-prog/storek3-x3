package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"strconv"
)

func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	inputFileName := "input.txt"
	outputFileName := "output.txt"

	data, err := ioutil.ReadFile(inputFileName)
	if err != nil {
		log.Fatalf("Ошибка при чтении файла ввода: %v", err)
	}

	N, err := strconv.Atoi(string(data))
	if err != nil {
		log.Fatalf("Ошибка при преобразовании входных данных: %v", err)
	}

	// Ищем два наибольших натуральных числа A и B, сумма которых равна N.
	// Мы начнем с A = N - 1 и B = 1 и будем уменьшать A и увеличивать B, пока gcd(A, B) не станет максимальным.
	A := N - 1
	B := 1
	var prevGCD int = 0
	answA := 0
	answB := 0
	for A >= B {
		if gcd(A, B) > prevGCD {
			prevGCD = gcd(A, B)
			answB = B
			answA = A
		}
		A--
		B++
	}
	outputFile, err := os.Create(outputFileName)
	if err != nil {
		log.Fatalf("Ошибка при создании файла вывода: %v", err)
	}
	defer outputFile.Close()

	_, err = fmt.Fprintf(outputFile, "%d %d\n", answA, answB)
	if err != nil {
		log.Fatalf("Ошибка при записи в файл вывода: %v", err)
	}
}
