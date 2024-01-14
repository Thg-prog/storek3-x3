#pragma once
#include <string>
#include <initializer_list>

class Polynom {
	double* ar;
	int n;
public:
	Polynom();
	Polynom(const Polynom& p);
	Polynom(Polynom&& p);
	Polynom(int _n, double* _ar);
	Polynom(int _n, float* _ar);
	Polynom(std::initializer_list<double> list);
	double calculate(double x) const;
	double operator[](int i) const;
	double& operator[] (int i);
	double at(int i) const;
	Polynom operator-() const;
	Polynom operator+(const Polynom& p) const;
	Polynom operator-(const Polynom& p) const;
	Polynom operator*(const Polynom& p) const;
	Polynom operator/(const Polynom& p) const;
	Polynom operator%(const Polynom& p) const;
	bool operator==(const Polynom& p) const;
	bool operator!=(const Polynom& p) const;
	Polynom& operator=(const Polynom& p);
	Polynom& operator=(Polynom&& p);
	Polynom& operator+=(const Polynom& p);
	Polynom& operator-=(const Polynom& p);
	Polynom& operator*=(const Polynom& p);
	Polynom& operator/=(const Polynom& p);
	Polynom& operator%=(const Polynom& p);
	friend std::ostream& operator<<(std::ostream& out, const Polynom& p);
	operator std::string() const;
	~Polynom();
};

