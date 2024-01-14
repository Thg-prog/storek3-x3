#include <iostream>
#include "polynom.h"

int main()
{
    double ar[3];
    ar[0] = 1;
    ar[1] = 0;
    ar[2] = 2;
    Polynom p(3, ar);
    std::cout << p.calculate(2) << " " << p[2] << std::endl;
    std::cout << p << std::endl;
    Polynom p1(p);
    p1[0] *= -1;
    p1[100] = 12;
    std::cout << -p1 << std::endl;
    std::cout << p1 - p << std::endl;
    Polynom p2{ 2, 5, 6 };
    std::cout << p2 * Polynom{ 3, 1 } << std::endl;
    p2 = p1;
    std::cout << p2 << std::endl;
    std::cout << Polynom{ 2, 3, 4 } + Polynom{5, 7, 9} << std::endl;
    std::cout << Polynom { -30, 3, -1, -1, 2 } / Polynom{ 2, 1 } << std::endl;
    std::cout << Polynom{ 5, -7, 2, -3, 2 } % Polynom{1, -3, 1} << std::endl;
}
