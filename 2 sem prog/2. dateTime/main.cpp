#define _CRT_SECURE_NO_WARNINGS

#include "datetime.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
	std::string temp = "D/M/Y h:m:s"; 
	std::string s;
	Date d;
	d.day = 33;
	d.month = 3;
	d.year = 123;
	Time t;
	t.hour = 3;
	t.minute = 59;
	t.second = 6;
	DateTime dt1(d, t);
	s = dt1.convert(temp);
	std::cout << s << std::endl;
	DateTime dt2;
	dt2.setMonth(33);
	s = dt2.convert(temp);
	std::cout << s << std::endl;
	DateTime current = DateTime::getCurrentDateTime();
	s = current.convert(temp);
	std::cout << s << std::endl;
	DateTime dt3(DateTime::getDateTime(s, temp));
	dt3.addSecs(123);
	s = dt3.convert(temp);
	std::cout << s << std::endl;
	DateTime dt4;
	dt4.setDate(current.getDate());
	dt4.setTime(current.getTime());
	current.addDays(30);
	Date dd = current.getDate();
	std::cout << dd.year << " " << dd.month << " " << dd.day << std::endl;
	std::cout << dt4.daysTo(dd) << std::endl;

	return 0;
}
