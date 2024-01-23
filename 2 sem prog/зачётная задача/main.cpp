#include <iostream>
#include <string>
#include "degree.h"

int main()
{
	Angle a("45.51\'57.6\'\'");
	Angle b;
	b.setDegree(360);
	std::cout << a.getDegree() << std::endl;
	std::cout << Angle::toString(0.866) << std::endl;
	std::cout << Angle::toRadians(30) << std::endl;
	std::cout << Angle::fromRadians(0.785) << std::endl;
	std::cout << -a << std::endl;
	++b;
	std::cout << b << std::endl;
	a--;
	std::cout << a.toMinutes(a.getDegree()) << std::endl;
	std::string s = "180.32\'343\'\'";
	std::cout << s + a << std::endl;
	Angle d(234);
	std::cout << 7 + d << std::endl;
	Angle c = a;
	std::cout << c << std::endl;
	double num = 34.87;
	bool value = c == num;
	std::cout << value << std::endl;
}
