#pragma once

#include <iostream>
#include <string>

class Number {
	int ss;
	std::string num;
	static int fromLetters(char ch);
public:
	Number();
	Number(const Number& n);
	Number(Number&& n);
	Number(std::string s, int _ss);
	int translateToDec() const;
	static bool isTrue(std::string s, int _ss);
	void setSS(int _ss);
	void setNumber(std::string s);
	void set(std::string s, int _ss);
	bool operator>(const Number& n) const;
	bool operator>=(const Number& n) const;
	bool operator<(const Number& n) const;
	bool operator<=(const Number& n) const;
	bool operator==(const Number& n) const;
	bool operator!=(const Number& n) const;
};

inline void Number::setSS(int _ss) {
	if (isTrue(num, _ss)) ss = _ss;
}

inline void Number::setNumber(std::string s) {
	if (isTrue(s, ss)) num = s;
}

inline void Number::set(std::string s, int _ss) {
	if (isTrue(s, _ss)) {
		num = s;
		ss = _ss;
	}
}
