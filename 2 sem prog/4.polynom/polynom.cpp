#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include "polynom.h"


Polynom::Polynom() {
	ar = new double[1];
	n = 1;
	ar[0] = 0;
}

Polynom::Polynom(const Polynom& p) {
	n = p.n;
	ar = new double[n];
	for (int i = 0; i < n; i++) {
		ar[i] = p.ar[i];
	}
}

Polynom::Polynom(Polynom&& p) {
	n = p.n;
	ar = new double[n];
	for (int i = 0; i < n; i++) {
		ar[i] = p.ar[i];
	}
	delete[] p.ar;
	p.ar = nullptr;
}

Polynom::Polynom(int _n, double* _ar) {
	n = _n;
	ar = new double[n];
	for (int i = 0; i < n; i++) {
		ar[i] = _ar[i];
	}
}

Polynom::Polynom(int _n, float* _ar) {
	n = _n;
	ar = new double[n];
	for (int i = 0; i < n; i++) {
		ar[i] = static_cast<double>(_ar[i]);
	}
}

Polynom::Polynom(std::initializer_list<double> list) {
	n = list.size();
	ar = new double[n];
	int i = 0;
	for (const double* p = list.begin(); p != list.end(); p++) {
		ar[i] = *p;
		i++;
	}
}

double Polynom::calculate(double x) const {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += ar[i] * pow(x, i);
	}
	return sum;
}

double Polynom::operator[] (int i) const {
	return ar[i];
}

double& Polynom::operator[] (int i) {
	if (i >= n) {
		double* _ar = new double[i + 1];
		for (int j = 0; j < n; j++) {
			_ar[j] = ar[j];
		}
		for (int j = n; j < i + 1; j++) {
			_ar[j] = 0;
		}
		delete[] ar;
		ar = new double[i + 1];
		for (int j = 0; j < i + 1; j++) {
			ar[j] = _ar[j];
		}
		n = i + 1;
		delete[] _ar;
	}
	return ar[i];
}

double Polynom::at(int i) const {
	if (i < 0 || i > n-1) throw std::out_of_range("This index is out of range!");
	return ar[i];
}

Polynom Polynom::operator-() const {
	Polynom p(*this);
	for (int i = 0; i < n; i++) p[i] *= -1;
	return p;
}

Polynom Polynom::operator+(const Polynom& p) const {
	Polynom returnP;
	returnP += *this;
	returnP += p;
	return returnP;
}

Polynom Polynom::operator-(const Polynom& p) const {
	Polynom returnP = *this;
	returnP -= p;
	return returnP;
}

Polynom Polynom::operator*(const Polynom& p) const {
	Polynom returnP = *this;
	returnP *= p;
	return returnP;
}

Polynom Polynom::operator/(const Polynom& p) const {
	Polynom returnP = *this;
	returnP /= p;
	return returnP;
}

Polynom Polynom::operator%(const Polynom& p) const {
	Polynom returnP = *this;
	returnP %= p;
	return returnP;
}

Polynom& Polynom::operator=(const Polynom& p) {
	if (this != &p) {
		if (p.n != n) {
			n = p.n;
			delete[] ar;
			ar = new double[n];
		}
		for (int i = 0; i < n; i++) {
			ar[i] = p.ar[i];
		}
	}
	return *this;
}

Polynom& Polynom::operator=(Polynom&& p) {
	if (this != &p) {
		ar = p.ar;
		n = p.n;
	}
	p.ar = nullptr;
	return *this;
}

Polynom& Polynom::operator+=(const Polynom& p) {
	int first_n, second_n;
	if (p.n > n) {
		first_n = p.n;
		second_n = n;
	}
	else {
		first_n = n;
		second_n = p.n;
	}
	double* _ar = new double[first_n];
	for (int i = 0; i < second_n; i++) {
		_ar[i] = ar[i] + p.ar[i];
	} 
	for (int i = second_n; i < first_n; i++) {
		if (p.n > n)
			_ar[i] = p.ar[i];
		else 
			_ar[i] = ar[i];
	}
	delete[] ar;
	n = first_n;
	ar = new double[first_n];
	for (int i = 0; i < first_n; i++) {
		ar[i] = _ar[i];
	}
	delete[] _ar;
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& p) {
	int first_n, second_n;
	if (p.n > n) {
		first_n = p.n;
		second_n = n;
	}
	else {
		first_n = n;
		second_n = p.n;
	}
	double* _ar = new double[first_n];
	for (int i = 0; i < second_n; i++) {
		_ar[i] = ar[i] - p.ar[i];
	}
	for (int i = second_n; i < first_n; i++) {
		if (p.n > n)
			_ar[i] = -p.ar[i];
		else
			_ar[i] = ar[i];
	}
	delete[] ar;
	n = first_n;
	ar = new double[first_n];
	for (int i = 0; i < first_n; i++) {
		ar[i] = _ar[i];
	}
	delete[] _ar;
	return *this;
}

Polynom& Polynom::operator*=(const Polynom& p) {
	int new_n = n + p.n - 1;
	int _n, second_n;
	if (n > p.n) {
		_n = p.n;
		second_n = n;
	}
	else {
		_n = n;
		second_n = p.n;
	}
	double* _ar = new double[new_n];
	for (int i = 0; i < new_n; i++) {
		_ar[i] = 0;
	}
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < second_n; j++) {
			if (n > p.n) _ar[i + j] += ar[j] * p.ar[i];
			else _ar[i + j] += ar[i] * p.ar[j];
			
		}
	}
	delete[] ar;
	n = new_n;
	ar = new double[new_n];
	for (int i = 0; i < new_n; i++) {
		ar[i] = _ar[i];
	}
	delete[] _ar;
	return *this;
}

Polynom& Polynom::operator/=(const Polynom& p) {
	if (n > p.n) {
		int new_n = n - p.n + 1;
		double* _ar = new double[new_n];
		int _n = p.n;
		for (int i = 0; i < new_n; i++) {
			_ar[i] = 0;
		}
		int j = new_n - 1;
		for (int i = n - 1; i >= p.n-1; i--) {
			_ar[j] = ar[i] / p.ar[p.n - 1];
			for (int x = p.n-1; x >= 0 ; x--) {
				ar[j+x] -= _ar[j] * p.ar[x];
			}
			j--;
		}
		delete[] ar;
		n = new_n;
		ar = new double[new_n];
		for (int i = 0; i < new_n; i++) {
			ar[i] = _ar[i];
		}
		delete[] _ar;
		return *this;
	}
	n = 1;
	*ar = 0;
	return *this;
}

Polynom& Polynom::operator%=(const Polynom& p) {
	if (n > p.n) {
		int new_n = n - p.n + 1;
		double* _ar = new double[new_n];
		int _n = p.n;
		for (int i = 0; i < new_n; i++) {
			_ar[i] = 0;
		}
		int j = new_n - 1;
		for (int i = n - 1; i >= p.n - 1; i--) {
			_ar[j] = ar[i] / p.ar[p.n - 1];
			for (int x = p.n - 1; x >= 0; x--) {
				ar[j + x] -= _ar[j] * p.ar[x];
			}
			j--;
		}
		n = n - p.n;
		delete[] _ar;
		return *this;
	}
	*this = p - *this;
	return *this;
}

bool Polynom::operator==(const Polynom& p) const {
	if (n == p.n) {
		for (int i = 0; i < n; i++) {
			if (ar[i] != p.ar[i]) return false;
		}
		return true;
	}
	return false;
}

bool Polynom::operator!=(const Polynom& p) const {
	if (n == p.n) {
		for (int i = 0; i < n; i++) {
			if (ar[i] != p.ar[i]) return true;
		}
		return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& out, const Polynom& p) {
	std::string s = (std::string)p;
	out << s;
	return out;
}

Polynom::operator std::string() const {
	std::string s;
	std::string add;
	char sign;
	if (ar[n - 1] < 0) s += '-';
	for (int i = n - 1; i > 0; i--) {
		if (ar[i - 1] > 0)
			sign = '+';
		else
			sign = '-';
		if (ar[i] != 0) {
			add = std::to_string(abs(ar[i])) + 'x' + '^' + std::to_string(i);
			if (ar[i-1] != 0)
				add += sign;
			if (i == 1) {
				add = std::to_string(abs(ar[i])) + 'x';
				if (ar[0] != 0)
					add += sign;
			}
			s += add;
		}
		else {
			if (ar[i - 1] != 0) {
				s += sign;
			}
		}
	}
	if (ar[0] != 0) s += std::to_string(abs(ar[0]));
	if (s.size() == 0) s += '0';
	return s;
}

Polynom::~Polynom() {
	delete[] ar;
}