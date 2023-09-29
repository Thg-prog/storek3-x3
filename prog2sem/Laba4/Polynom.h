
//
// Created by 1 on 16.03.2023.
//
#ifndef LABA4_polynom_H
#define LABA4_polynom_H
#include <iostream>


class ElemException//std::outofrange
{
public:
    ElemException(std::string message) : message{ message } {}
    std::string getMessage() const { return message; }
private:
    std::string message;
};

class Polynom {
private:
    void exception(int i);
    static Polynom del(const Polynom& t1,const  Polynom& t2, int choose);
    double* coef;// double
    int len;
public:
    Polynom();//+
    //Polynom(std::initializer_list<int> coef);//-
    Polynom(std::initializer_list<double> coef);
    Polynom(float* coef, int len);
    Polynom(double* coef, int len);
    ~Polynom();
    Polynom(const Polynom& t);
    Polynom(Polynom&& t)noexcept;
    Polynom operator=(const  Polynom& t);
    Polynom operator=(Polynom&& t)noexcept;

    friend bool operator==(const Polynom& t1, const Polynom& t2);
    friend bool operator!=(const Polynom& t1, const Polynom& t2);
    
    friend Polynom operator+(const Polynom& t1, const Polynom& t2);//const&
    friend Polynom operator+(const Polynom& t1);
    friend Polynom operator-(const Polynom& t1, const Polynom& t2);
    friend Polynom operator-(const Polynom& t1);
    friend Polynom operator*(const Polynom& t1, const Polynom& t2);
    friend Polynom operator/(const Polynom& t1, const  Polynom& t2);
    friend Polynom operator%(const Polynom& t1,const Polynom &t2);
    Polynom operator+=(const Polynom& t);
    Polynom operator-=(const Polynom& t);
    Polynom operator/=(const Polynom& t);
    Polynom operator*=( const Polynom& t);
    Polynom operator%=(const Polynom &t);
    // %=
    operator std::string() const;
    float count(int x) const;
    double operator[](int i) const;
    double& operator[](int i);
    double& at(int i);
    friend std::ostream& operator << (std::ostream &out, const Polynom& t);
};




#endif //LABA4_polynom_H
