#include <iostream>
#include <string>
#include "fraction.hpp"
#include "fraction.cpp"

int main()
{
    Fraction fr(3.4);
    Fraction fr2(0.5);
    const Fraction frc(-1, -2);
    bool b = fr == 3.4;
    std::cout << b << " " << frc + fr2 << " " << frc - fr2 << " " << frc * fr2 << " " << frc / fr2 << " " << std::endl;
    std::cout << Fraction(-1, -2) + fr2 << " " << Fraction(-1, -2) - fr2 << " " << Fraction(-1, -2) * fr2 << " " << Fraction(-1, -2) / fr2 << " " << std::endl;
    std::cout << fr + fr2 << " " << fr - fr2 << " " << fr * fr2 << " " << fr / fr2 << " " << std::endl;
    std::cout << 1 + fr2 << " " << 1 - fr2 << " " << 1 * fr2 << " " << 1 / fr2 << " " << std::endl;
    std::cout << -fr + 2 << " " << fr - 2 << " " << fr * 2 << " " << fr / 2.7 << " " << std::endl;
    fr += fr2;
    std::cout << fr << " " << std::endl;
    fr++;
    --fr2;
    std::cout << fr << " " << fr2 << " " << std::endl;
    b = fr == fr2;
    std::cout << b << " " << (double)fr2 << " " << (std::string)fr << " " << std::endl;
    fr = -fr;
    std::cout << fr << " " << std::endl;
}