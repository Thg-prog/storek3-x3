package main

import (
	"fmt"
	"math"
)

const eps = 0.000001

func f(x float64) float64 {
	return math.Pow(x, 2) + 3*x - 5
}

func df(x float64) float64 {
	return (2*x + 2) * math.Cos(math.Pow(x, 2)+2*x+1)
}

func halfDevision(a, b float64) float64 {
	aY := f(a)
	for b-a > eps {
		сX := (a + b) / 2
		cY := f(сX)
		if aY*cY >= 0 {
			a = сX
			aY = cY
		} else {
			b = сX
		}
	}
	return (a + b) / 2
}

func tangenNewton(x float64) float64 {
	x_k := x
	x_k1 := x_k - (f(x) / df(x))
	for math.Abs(x_k1-x_k) > eps {
		x_k = x_k1
		x_k1 = x_k - (f(x_k) / df(x_k))
	}
	return x_k1
}

func main() {
	fmt.Println(halfDevision(0, 10))
	fmt.Println(tangenNewton(1000))
}
