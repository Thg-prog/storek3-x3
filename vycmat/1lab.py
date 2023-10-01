import math


class MyMath:
    def __init__(self):
        self.eps = 0.000001
        self.__iteration_count_ln = 0
        self.__iteration_count_sin = 0
        self.__iteration_count_cos = 0

    def get_ln_iteration_count(self):
        return self.__iteration_count_ln

    def get_sin_iteration_count(self):
        return self.__iteration_count_sin

    def get_cos_iteration_count(self):
        return self.__iteration_count_cos

    def __get_exp(self, x):
        if abs(x) > 1:
            return (self.__get_exp(x / 2))**2
        exp_item = 1.0
        result = 1.0
        n = 0
        while abs(exp_item) > self.eps:
            exp_item *= x / (n + 1)
            result += exp_item
            n += 1
        return result

    def __get_ln_value(self, x, start, end):
        self.__iteration_count_ln += 1
        middle = math.ceil((start + end) / 2)
        try:
            exp_value_middle = math.floor(self.__get_exp(middle))
        except OverflowError:
            return self.__get_ln_value(x, start, math.ceil(middle/2))
        exp_value_middle_plus = math.floor(self.__get_exp(middle + 1))
        if abs(x - exp_value_middle_plus) < abs(x - exp_value_middle) and exp_value_middle < x < exp_value_middle_plus:
            return middle + 1
        elif exp_value_middle > x:
            return self.__get_ln_value(x, start, middle-1)
        elif x > exp_value_middle_plus:
            return self.__get_ln_value(x, middle+1, end)
        return middle

    def get_ln(self, x):
        first_part = 0
        if x < 1:
            return -self.get_ln(1/x)
        elif x == 1:
            return 0
        elif x >= math.e:
            start = 0
            if round(x) < 100000:
                degree = math.ceil(math.sqrt(x/2))
            else:
                degree = 40
            end = math.ceil(degree)
            first_part = self.__get_ln_value(x, start, end)
            val = self.__get_exp(first_part)
            x /= val
        item = (x - 1) / (x + 1)
        n = 0
        result = item
        while abs(item) > self.eps:
            self.__iteration_count_ln += 1
            item *= (2 * n + 1) * (x - 1) ** 2 / ((2 * n + 3) * (x + 1) ** 2)
            result += item
            n += 1
        return 2 * result + first_part

    def get_sin(self, x):
        x %= 2 * math.pi
        if x > math.pi:
            x -= math.pi
            x *= -1
        if x > math.pi / 2:
            x = math.pi - x
        sin_item = x
        result = 0
        n = 0
        while abs(sin_item) > self.eps:
            self.__iteration_count_sin += 1
            result += sin_item
            sin_item *= -x**2 / ((2*n + 3) * (2*n + 2))
            n += 1
        return result

    def get_cos(self, x):
        x %= 2 * math.pi
        if x > 3 * math.pi / 2:
            x -= 2 * math.pi
        cos_item = 1
        result = 0
        n = 0
        while abs(cos_item) > self.eps:
            self.__iteration_count_cos += 1
            result += cos_item
            cos_item *= -x**2 / ((2 * n + 2) * (2 * n + 1))
            n += 1
        return result


def main():
    my_math = MyMath()
    print("ln(4x^2 + 1) * sin(7x + 1) * cos(2x) = ?")
    x = float(input('Введите значение x: '))
    print("Предполагаемый результат:", math.log(4*x**2 + 1) * math.sin(7*x + 1) * math.cos(2*x))
    print("Полученный результат:", my_math.get_ln(4*x**2 + 1) * my_math.get_sin(7*x + 1) * my_math.get_cos(2*x))
    print("Количества итераций:")
    print("ln(4x^2 + 1): ", my_math.get_ln_iteration_count())
    print("sin(7x + 1): ", my_math.get_sin_iteration_count())
    print("cos(2x): ", my_math.get_cos_iteration_count())


if __name__ == '__main__':
    main()
