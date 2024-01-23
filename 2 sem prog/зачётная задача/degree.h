#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Angle {
	double angle;
public:
	Angle();
	Angle(double degree);
	Angle(std::string s);
	Angle(const Angle& a);
	Angle(Angle&& a) noexcept;
	void setDegree(double degree);
	void setDegree(std::string s);
	inline double getDegree() const { return angle; }
	void setRadian(double rad);
	static double toRadians(double degree);
	static double toMinutes(double degree);
	static double toSeconds(double degree);
	static double fromRadians(double rad);
	static double fromMinutes(double minutes);
	static double fromSeconds(double seconds);
	static std::string toString(double degree);
	Angle operator-() const;
	Angle& operator++();
	Angle& operator++(int);
	Angle& operator--();
	Angle& operator--(int);
	friend Angle operator+(const Angle& a1, const Angle& a2);
	friend Angle operator-(const Angle& a1, const Angle& a2);
	friend Angle operator*(const Angle& a1, const double& a2);
	friend Angle operator*(const double& a1, const Angle& a2);
	friend Angle operator/(const Angle& a1, const double& a2);
	Angle& operator=(const Angle& a);
	Angle& operator+=(const Angle& a);
	Angle& operator-=(const Angle& a);
	Angle& operator*=(const double& a);
	Angle& operator/=(const double& a);
	friend bool operator==(const Angle& a1, const Angle& a2);
	friend bool operator!=(const Angle& a1, const Angle& a2);
	friend bool operator>(const Angle& a1, const Angle& a2);
	friend bool operator<(const Angle& a1, const Angle& a2);
	friend bool operator>=(const Angle& a1, const Angle& a2);
	friend bool operator<=(const Angle& a1, const Angle& a2);
	operator std::string() const;
	friend std::istream& operator>>(std::istream& in, Angle& a);
	friend std::ostream& operator<<(std::ostream& out, const Angle& a);
};

Angle operator""_deg(long double degree);
Angle operator""_rad(long double degree);