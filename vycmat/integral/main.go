package main
import (
	"fmt"
	"math"
)

func f(x float64) float64 {
	return math.Sin(math.Pow(x, 2) + 2*x + 1)
}

func getStrapezoidal(a float64, b float64, n int) float64 {
    delta := (b - a) / float64(n)
    res := (f(a) + f(b)) / 2
    for i := 1; i < n; i++ {
        res += f(a + float64(i)*delta)
	}
    return res * delta
}

func getSRectangle(a float64, b float64, n int) float64 {
    delta := (b - a) / float64(n)
    res := 0.0
    for i := 0; i < n; i++ {
        res += f(a + float64(i)*delta)
	}
    return res * delta
}

func rectangleMethod(a float64, b float64) float64 {
    n := 2
    s := getSRectangle(a, b, n)
    n *= 2
    s_next := getSRectangle(a, b, n)
    for math.Abs(s_next - s) >= 0.000001 {
        n *= 2
        s = getSRectangle(a, b, n)
        n *= 2
        s_next = getSRectangle(a, b, n)
	}
    return s_next
}

func strapezoidalMethod(a float64, b float64) float64 {
    n := 2
    s := getStrapezoidal(a, b, n)
    n *= 2
    s_next := getStrapezoidal(a, b, n)
    for math.Abs(s_next - s) >= 0.000001 {
        n *= 2
        s = getStrapezoidal(a, b, n)
        n *= 2
        s_next = getStrapezoidal(a, b, n)
	}
    return s_next
}
 
func simpsonMethod(a float64, b float64) float64 {
    n := 1000
    delta := (b - a) / float64(n)
    res := 0.0
    for i := 1; i < n; i+=2 {
        res += delta * (f(a + float64(i-1)*delta) + 4 * f(a + float64(i)*delta) + f(a + float64(i+1)*delta)) / 3
	}
    return res
}

func main() {
	a := float64(1)
	b := float64(15)
	value1 := rectangleMethod(a, b)
    value2 := strapezoidalMethod(a, b)
    value3 := simpsonMethod(a, b)
    fmt.Println("Метод прямоугольников:", value1)
	fmt.Println("Метод трапеций:", value2) 
	fmt.Println("Метод Симпсона:", value3)
}