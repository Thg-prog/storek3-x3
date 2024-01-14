#include <iostream>
#include "fraction.hpp"
#include <cmath>

Fraction::Fraction(): numerator(1), denominator(1) {}

Fraction::Fraction(int number): numerator(number), denominator(1) {}

Fraction::Fraction(double number) {
    std::string str = std::to_string(number);
    char first = str[0];
    int ind = str.find('.');
    str = str.substr(ind + 1);
    int _numerator = std::stoi(str);
    size_t count = 0;
    while (count < str.size() && _numerator % 10 == 0) {
        _numerator /= 10;
        count++;
    }
    int degree = pow(10, std::to_string(_numerator).size());
    int integer = static_cast<int>(number);
    numerator = degree * abs(integer) + _numerator;
    if (first == '-') numerator *= -1;
    denominator = degree;
    cut();
}

Fraction::Fraction(const Fraction& fr) {
    numerator = fr.numerator;
    denominator = fr.denominator;
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }
}

Fraction::Fraction(Fraction&& fr) {
    numerator = fr.numerator;
    denominator = fr.denominator;
    fr.numerator = 1;
    fr.denominator = 1;
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }
}

Fraction::Fraction(int num, int den) {
    if (den != 0) {
        numerator = num;
        denominator = den;
    }
    else {
        numerator = 1;
        denominator = 1;
    }
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }
}

void Fraction::set(int num, int den) {
    if (den != 0) {
        numerator = num;
        denominator = den;
        if (denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
    }
    else {
        numerator = 1;
        denominator = 1;
    }
}

void Fraction::cut() {
    int number = abs(numerator);
    if (abs(denominator) < abs(numerator)) number = abs(denominator);
    int del = 1;
    for (int i = 1; i <= abs(denominator); i++) {
        if (abs(denominator) % i == 0 && abs(numerator) % i == 0)
            del = i;
    }
    denominator /= del;
    numerator /= del;
}

std::istream& operator>>(std::istream& in, Fraction& fr) {
    char ch;
    int numerator, denominator;
    in >> numerator >> ch >> denominator;
    fr.set(numerator, denominator);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fr) {
    int num = fr.numerator;
    int den = fr.denominator;
    if (num == 0)
        out << 0;
    else if (den == 1)
        out << num;
    else
        out << num << "/" << den;
    return out;
}

Fraction& Fraction::operator+=(const Fraction& fr) {
    int num = numerator * fr.denominator + fr.numerator * denominator;
    int den = denominator * fr.denominator;
    numerator = num;
    denominator = den;
    cut();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& fr) {
    int num = numerator * fr.denominator - fr.numerator * denominator;
    int den = denominator * fr.denominator;
    numerator = num;
    denominator = den;
    cut();
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& fr) {
    numerator *= fr.numerator;
    denominator *= fr.denominator;
    cut();
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& fr) {
    numerator *= fr.denominator;
    denominator *= abs(fr.numerator);
    if (fr.numerator < 0) {
        numerator *= -1;
    }
    cut();
    return *this;
}

Fraction& Fraction::operator=(const Fraction& fr) {
    if (this != &fr) {
        numerator = fr.numerator;
        denominator = fr.denominator;
    }
    return *this;
}

Fraction Fraction::operator-() const {
    Fraction fr(-numerator, denominator);
    return fr;
}

Fraction operator+(const Fraction& frc, const Fraction& fr2) {
    int num = frc.numerator * fr2.denominator + fr2.numerator * frc.denominator;
    int den = frc.denominator * fr2.denominator;
    Fraction f(num, den);
    f.cut();
    return f;
}

Fraction operator-(const Fraction& frc, const Fraction& fr2) {
    int num = frc.numerator * fr2.denominator - fr2.numerator * frc.denominator;
    int den = frc.denominator * fr2.denominator;
    Fraction f(num, den);
    f.cut();
    return f;
}

Fraction operator*(const Fraction& frc, const Fraction& fr2) {
    int num = frc.numerator * fr2.numerator;
    int den = frc.denominator * fr2.denominator;
    Fraction f(num, den);
    f.cut();
    return f;
}

Fraction operator/(const Fraction& frc, const Fraction& fr2) {
    int num = frc.numerator * fr2.denominator;
    int den = frc.denominator * fr2.numerator;
    Fraction f(num, den);
    f.cut();
    return f;
}

Fraction operator+(const Fraction& frc, const double& number) {
    Fraction fr2(number);
    return frc + fr2;
}

Fraction operator-(const Fraction& frc, const double& number) {
    Fraction fr2(number);
    return frc - fr2;
}

Fraction operator*(const Fraction& frc, const double& number) {
    Fraction fr2(number);
    return frc * fr2;
}

Fraction operator/(const Fraction& frc, const double& number) {
    Fraction fr2(number);
    return frc / fr2;
}

Fraction operator+(const double& number, const Fraction& frc) {
    Fraction f(number);
    return frc + f;
}

Fraction operator-(const double& number, const Fraction& frc) {
    Fraction f(number);
    return f - frc;
}

Fraction operator*(const double& number, const Fraction& frc) {
    Fraction f(number);
    return frc * f;
}

Fraction operator/(const double& number, const Fraction& frc) {
    Fraction f(number);
    return f / frc;
}

Fraction& Fraction::operator++() {
    double num = (double)*this;
    ++num;
    Fraction fr(num);
    *this = fr;
    return *this;
}

Fraction& Fraction::operator++(int) {
    double num = (double)*this;
    num++;
    Fraction fr(num);
    *this = fr;
    return *this;
}

Fraction& Fraction::operator--() {
    double num = (double)*this;
    --num;
    Fraction fr(num);
    *this = fr;
    return *this;
}

Fraction& Fraction::operator--(int) {
    double num = (double)*this;
    num--;
    Fraction fr(num);
    *this = fr;
    return *this;
}


bool operator==(const Fraction& frc, const Fraction& fr2) {
    return frc.numerator == fr2.numerator && frc.denominator == fr2.denominator;
}

bool operator!=(const Fraction& frc, const Fraction& fr2) {
    return !(frc == fr2);
}

bool operator>(const Fraction& frc, const Fraction& fr2) {
    return frc.numerator * fr2.denominator > fr2.numerator * frc.denominator;
}

bool operator<(const Fraction& frc, const Fraction& fr2) {
    return frc.numerator * fr2.denominator < fr2.numerator * frc.denominator;
}

bool operator>=(const Fraction& frc, const Fraction& fr2) {
    return frc.numerator * fr2.denominator >= fr2.numerator * frc.denominator;
}

bool operator<=(const Fraction& frc, const Fraction& fr2) {
    return frc.numerator * fr2.denominator <= fr2.numerator * frc.denominator;
}

bool operator==(const double& number, const Fraction& fr2) {
    Fraction fr(number);
    return fr == fr2;
}

bool operator!=(const double& number, const Fraction& fr2) {
    Fraction fr(number);
    return fr != fr2;
}

bool operator>(const double& number, const Fraction& fr2) {
    Fraction fr(number);
    return fr > fr2;
}

bool operator<(const double& number, const Fraction& fr2) {
    Fraction fr(number);
    return fr < fr2;
}

bool operator>=(const double& number, const Fraction& fr2) {
    Fraction fr(number);
    return fr >= fr2;
}

bool operator<=(const double& number, const Fraction& fr2) {
    Fraction fr(number);
    return fr <= fr2;
}

bool operator==(const Fraction& fr, const double& number) {
    Fraction fr2(number);
    return fr == fr2;
}

bool operator!=(const Fraction& fr, const double& number) {
    Fraction fr2(number);
    return fr != fr2;
}

bool operator>(const Fraction& fr, const double& number) {
    Fraction fr2(number);
    return fr > fr2;
}

bool operator<(const Fraction& fr, const double& number) {
    Fraction fr2(number);
    return fr < fr2;
}

bool operator>=(const Fraction& fr, const double& number) {
    Fraction fr2(number);
    return fr <= fr2;
}

bool operator<=(const Fraction& fr, const double& number) {
    Fraction fr2(number);
    return fr <= fr2;
}

