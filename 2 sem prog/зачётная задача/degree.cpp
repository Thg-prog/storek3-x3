#include <iostream>
#include <string>
#include "degree.h"
#include <corecrt_math_defines.h>

Angle::Angle(): angle(0) {}

Angle::Angle(double degree): angle(degree) {}

Angle::Angle(std::string s) {
	setDegree(s);
}

Angle::Angle(const Angle& a) {
	angle = a.angle;
}

Angle::Angle(Angle&& a) noexcept {
	angle = a.angle;
}

void Angle::setDegree(std::string s) {
	int first_find = s.find('.');
	int second_find = s.find('\'');
	int third_find = s.find("\'\'");
	double degree = std::stod(s.substr(0, first_find));
	double minute = std::stod(s.substr(first_find+1, second_find - first_find-1));
	double second = std::stod(s.substr(second_find+1, third_find - second_find-1));
	angle = degree + minute / 60.0 + second / 60.0 / 60.0;
}

void Angle::setDegree(double degree) {
	angle = degree;
}

void Angle::setRadian(double rad) {
	angle = fromRadians(rad);
}

double Angle::toRadians(double degree) {
	return degree * M_PI / 180;
}

double Angle::fromRadians(double rad) {
	return 180 * rad / M_PI;
}

std::string Angle::toString(double degree) {
	int integer_part = static_cast<int>(degree);
	double decimal_part = degree - integer_part;
	int second_integer_part = static_cast<int>(decimal_part * 60);
	double second_decimal_part = decimal_part * 60 - second_integer_part;
	double third_part = second_decimal_part * 60;
	return std::to_string(integer_part) + '.' + std::to_string(second_integer_part) + "\'" + std::to_string(third_part) + "\'\'";
}

double Angle::toMinutes(double degree) {
	return degree * 60;
}

double Angle::toSeconds(double degree) {
	return degree * 60 * 60;
}

double Angle::fromMinutes(double minutes) {
	return minutes / 60;
}

double Angle::fromSeconds(double seconds) {
	return seconds / 60 / 60;
}

Angle Angle::operator-() const {
	return Angle(-angle);
}

Angle& Angle::operator++() {
	++angle;
	return *this;
}

Angle& Angle::operator++(int) {
	angle++;
	return *this;
}

Angle& Angle::operator--() {
	--angle;
	return *this;
}

Angle& Angle::operator--(int) {
	angle--;
	return *this;
}

Angle operator+(const Angle& a1, const Angle& a2) {
	return Angle (a1.angle + a2.angle);
}

Angle operator-(const Angle& a1, const Angle& a2) {
	return Angle (a1.angle - a2.angle);
}

Angle operator*(const Angle& a1, const double& a2) {
	return Angle (a1.angle * a2);
}

Angle operator*(const double& a1, const Angle& a2) {
	return Angle (a1 * a2.angle);
}

Angle operator/(const Angle& a1, const double& a2) {
	return Angle (a1.angle / a2);
}

Angle& Angle::operator=(const Angle& a) {
	angle = a.angle;
	return *this;
}

Angle& Angle::operator+=(const Angle& a) {
	angle += a.angle;
	return *this;
}

Angle& Angle::operator-=(const Angle& a) {
	angle -= a.angle;
	return *this;
}

Angle& Angle::operator*=(const double& a) {
	angle *= a;
	return *this;
}

Angle& Angle::operator/=(const double& a) {
	angle /= a;
	return *this;
}

bool operator==(const Angle& a1, const Angle& a2) {
	return a1.angle == a2.angle;
}

bool operator!=(const Angle& a1, const Angle& a2) {
	return a1.angle != a2.angle;
}

bool operator>(const Angle& a1, const Angle& a2) {
	return a1.angle > a2.angle;
}

bool operator<(const Angle& a1, const Angle& a2) {
	return a1.angle < a2.angle;
}

bool operator>=(const Angle& a1, const Angle& a2) {
	return a1.angle >= a2.angle;
}

bool operator<=(const Angle& a1, const Angle& a2) {
	return a1.angle <= a2.angle;
}

Angle::operator std::string() const {
	return toString(angle);
}

std::istream& operator>>(std::istream& in, Angle& a) {
	in >> a.angle;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Angle& a) {
	out << a.angle;
	return out;
}

Angle operator""_deg(long double degree) {
	return Angle(static_cast<double>(degree));
}

Angle operator""_rad(long double degree) {
	return Angle::toRadians(degree);
}