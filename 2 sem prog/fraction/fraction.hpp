#pragma once
#include <iostream>
#include <string>

class Fraction {
    int numerator;
    int denominator;
    void cut();
public:
    Fraction();
    Fraction(int number);
    Fraction(double number);
    Fraction(const Fraction& fr);
    Fraction(Fraction&& fr);
    Fraction(int num, int den);
    void set(int num, int den);
    friend Fraction operator+(const Fraction& fr, const Fraction& fr2);
    friend Fraction operator-(const Fraction& fr, const Fraction& fr2);
    friend Fraction operator*(const Fraction& fr, const Fraction& fr2);
    friend Fraction operator/(const Fraction& fr, const Fraction& fr2);
    friend Fraction operator+(const double& number, const Fraction& fr2);
    friend Fraction operator-(const double& number, const Fraction& fr2);
    friend Fraction operator*(const double& number, const Fraction& fr2);
    friend Fraction operator/(const double& number, const Fraction& fr2);
    friend Fraction operator+(const Fraction& fr, const double& number);
    friend Fraction operator-(const Fraction& fr, const double& number);
    friend Fraction operator*(const Fraction& fr, const double& number);
    friend Fraction operator/(const Fraction& fr, const double& number);
    Fraction& operator+=(const Fraction& fr);
    Fraction& operator-=(const Fraction& fr);
    Fraction& operator*=(const Fraction& fr);
    Fraction& operator/=(const Fraction& fr);
    Fraction& operator=(const Fraction& fr);
    Fraction operator-() const;
    Fraction& operator++();
    Fraction& operator++(int);
    Fraction& operator--();
    Fraction& operator--(int);
    friend bool operator==(const Fraction& fr, const Fraction& fr2);
    friend bool operator!=(const Fraction& fr, const Fraction& fr2);
    friend bool operator>(const Fraction& fr, const Fraction& fr2);
    friend bool operator<(const Fraction& fr, const Fraction& fr2);
    friend bool operator>=(const Fraction& fr, const Fraction& fr2);
    friend bool operator<=(const Fraction& fr, const Fraction& fr2);
    friend bool operator==(const double& number, const Fraction& fr2);
    friend bool operator!=(const double& number, const Fraction& fr2);
    friend bool operator>(const double& number, const Fraction& fr2);
    friend bool operator<(const double& number, const Fraction& fr2);
    friend bool operator>=(const double& number, const Fraction& fr2);
    friend bool operator<=(const double& number, const Fraction& fr2);
    friend bool operator==(const Fraction& fr, const double& number);
    friend bool operator!=(const Fraction& fr, const double& number);
    friend bool operator>(const Fraction& fr, const double& number);
    friend bool operator<(const Fraction& fr, const double& number);
    friend bool operator>=(const Fraction& fr, const double& number);
    friend bool operator<=(const Fraction& fr, const double& number);
    inline operator double() const;
    inline operator float() const;
    inline operator std::string() const;
    friend std::istream& operator>>(std::istream& in, Fraction& fr);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fr);
};

inline Fraction::operator double() const { 
    return (double)numerator / (double)denominator; 
}

inline Fraction::operator float() const { 
    return (float)numerator / (float)denominator; 
}

inline Fraction::operator std::string() const { 
    return std::to_string((double)*this); 
}
