#include <iostream>
#include "number.h"
#include <string>

Number::Number() {
	num = "0";
	ss = 10;
}

Number::Number(const Number& n) {
	num = n.num;
	ss = n.ss;
}

Number::Number(Number&& n) {
	num = n.num;
	ss = n.ss;
	n.ss = 10;
	n.num = "0";
}

Number::Number(std::string s, int _ss) {
	if (isTrue(s, _ss)) {
		num = s;
		ss = _ss;
	}
}

int Number::translateToDec() const {
	if (ss == 10) return std::stoi(num);
	int dec = 0;
 	for (int i = 0; i < num.size(); i++) {
		dec += fromLetters(num[i])*pow(ss, num.size()-i-1);
	}
	return dec;
}

int Number::fromLetters(char ch) {
	std::string str = "0123456789abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < str.size(); i++) {
		if (tolower(ch) == str[i]) return i;
	}
	return -1;
}

bool Number::isTrue(std::string s, int _ss) {
	for (int i = 0; i < s.size(); i++) {
		if (fromLetters(s[i]) >= _ss) {
			return false;
		}
	}
	return true;
}

bool Number::operator>(const Number& n) const {
	int first = translateToDec();
	int second = n.translateToDec();
	return first > second;
}

bool Number::operator>=(const Number& n) const {
	int first = translateToDec();
	int second = n.translateToDec();
	return first >= second;
}

bool Number::operator<(const Number& n) const {
	int first = translateToDec();
	int second = n.translateToDec();
	return first < second;
}

bool Number::operator<=(const Number& n) const {
	int first = translateToDec();
	int second = n.translateToDec();
	return first <= second;
}

bool Number::operator==(const Number& n) const {
	int first = translateToDec();
	int second = n.translateToDec();
	return first == second;
}

bool Number::operator!=(const Number& n) const {
	int first = translateToDec();
	int second = n.translateToDec();
	return first != second;
}