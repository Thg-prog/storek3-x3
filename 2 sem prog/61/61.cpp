#include <iostream>
#include "number.h"
#include <string>
#include <fstream>

int main()
{
    std::ifstream in("in.txt");
    int a1, a2;
    in >> a1 >> a2;
    std::string num1, num2;
    in >> num1;
    in >> num2;
    in.close();

    Number n1(num1, a1);
    Number n2(num2, a2);

    std::ofstream out("out.txt");
    if (n1 < n2) out << -1;
    else if (n1 > n2) out << 1;
    else out << 0;
    out.close();
}
