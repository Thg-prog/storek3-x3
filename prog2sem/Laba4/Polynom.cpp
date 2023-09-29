#include <iostream>
#include <string>
#include "Polynom.h"

Polynom::Polynom() {
    coef = new double[1];
    coef[0] = 0;
    len = 0;
}

/*
Polynom::Polynom(std::initializer_list<int> coef)
{
    this->len = coef.size() - 1;
    this->coef = new double[this->len + 1];
    for(int i = 0; i <= this->len; i++){
        this->coef[i] = *(coef.begin()+i);
    }
}*/

Polynom::Polynom(std::initializer_list<double> coef)
{
    this->len = coef.size() - 1;
    this->coef = new double[this->len + 1];
    for(int i = 0; i <= this->len; i++){
        this->coef[i] = *(coef.begin()+i);
    }
}

Polynom::~Polynom(){
    delete[] coef;
}

Polynom::Polynom(const Polynom& t) : len(t.len){
    this->coef = new double[len + 1];
    memcpy(this->coef, t.coef, sizeof(float) * (len + 1));
}

Polynom::Polynom(Polynom&& t) noexcept : coef(t.coef), len(t.len){
    t.coef = nullptr;
    t.len = 0;
}


Polynom::Polynom(float* coef, int len){
    this->coef = new double[len + 1];
    for (int i = 0; i <= len; i++) {
        this->coef[i] = coef[i];
    }
    this->len = len;
}

Polynom::Polynom(double* coef, int len) {
    this->coef = new double[len + 1];
    for (int i = 0; i <= len; i++) {
        this->coef[i] = (float)coef[i];
    }
    this->len = len;
}

/*Polynom::~Polynom() {
    delete[] coef;
}*/

Polynom Polynom::operator=( const Polynom& t) {
    if(this->coef != NULL)delete[] this->coef;
    this->coef = new double[t.len + 1];
    for (int i = 0; i <= t.len; i++) {
        this->coef[i] = t.coef[i];
    }
    this->len = t.len;
    return *this;
}

Polynom Polynom::operator=(Polynom&& t) noexcept{
    if(this->coef != NULL)delete[] this->coef;
    this->coef = new double[t.len + 1];
    for (int i = 0; i <= t.len; i++) {
        this->coef[i] = t.coef[i];
    }
    this->len = t.len;
    t.coef = nullptr;
    t.len = 0;
    return *this;
}

bool operator==(const Polynom& t1, const Polynom& t2) {
    if (t1.len != t2.len)return 0;
    for (int i = 0; i <= t1.len; i++) {
        if ((t1.coef[i] != t2.coef[i])) {
            return 0;
        }
    }
    return 1;
}

float Polynom::count(int x) const{
    float result = 0;
    for(int i = 0; i<=this->len; i++){
        result += this->coef[i] * (x ^ i);
    }
    return result;
}



bool operator!=(const Polynom& t1, const Polynom& t2) {
    return !(t1 == t2);
}


Polynom operator+( const Polynom &t1, const Polynom& t2) {
    Polynom temp1;
    Polynom temp2;
    if (t1.len > t2.len)
    {
        temp1 = t1;
        temp2 = t2;
    }else 
    {
        temp1 = t2;
        temp2 = t1;
    }
    for (int i = 0; i <= temp2.len; i++)
    {
        temp1.coef[i] += temp2.coef[i];
    }
    return temp1;
}

Polynom operator-(const Polynom& t1, const Polynom& t2) {
    Polynom temp1;
    Polynom temp2;
    if (t1.len > t2.len)
    {
        temp1 = t1;
        temp2 = -t2;
    }
    else
    {
        temp1 = -t2;
        temp2 = t1;
    }
    for (int i = 0; i <= temp2.len; i++)
    {
        temp1.coef[i] += temp2.coef[i];
        
        //if (temp1.coef[i] != 0)temp1.len = i - 1;
    }
    return temp1;
}
Polynom operator-(const Polynom& t1) {
    Polynom temp;
    temp = t1;
    for (int i = 0; i <= temp.len; i++)temp.coef[i] *= -1;
    return temp;
}

Polynom operator*(const Polynom& t1, const Polynom& t2) {
    int maxlen = t1.len + t2.len + 1;
    Polynom result;
    delete result.coef;
    std::cout << "T1: "<<t1 << " T2: " << t2 << "Maxlen: " << t1.len << " " << t2.len<<std::endl ;
    result.len = maxlen - 1;
    result.coef = new double[maxlen + 1];
    for (int i = 0; i < maxlen; i++)result.coef[i] = 0;
    for (int i = 0; i <= t1.len; i++) {
        for (int j = 0; j <= t2.len; j++) {
            result.coef[j + i] += (t1.coef[i] * t2.coef[j]);
        }
    }
    std::cout << "Result: " << result << std::endl;
    return result;
}


Polynom Polynom::del(const Polynom &t1, const Polynom& t2, int choose) {
    bool inAlgoritm = true;

    Polynom temp;
    Polynom ob_1;
    Polynom ob_2;
    Polynom ob_4;

    temp.len = t1.len - t2.len;
    temp.coef = new double[temp.len + 1];
    std::memset(temp.coef, 0, (temp.len + 1) * sizeof(float));

    ob_1.len = t1.len;
    ob_1.coef = new double[t1.len + 1];
    for (int i = t1.len; i >= 0; i--)
        ob_1.coef[i] = t1.coef[i];

    ob_2.len = t2.len;
    ob_2.coef = new double[t2.len + 1];
    for (int i = t2.len; i >= 0; i--)
        ob_2.coef[i] = t2.coef[i];
    ob_4.len = ob_1.len;
    ob_4.coef = new double[ob_1.len + 1];
    float mnojnik;
    int k = 0;
    int i, j;
    while (inAlgoritm)
    {
        for (int i = t2.len; i >= 0; i--)
            ob_4.coef[i] = t2.coef[i];
        if (ob_2.len < ob_1.len)
        {
            for (i = ob_1.len, j = ob_2.len; i >= 0; i--, j--)
                if (j < 0)
                    ob_4.coef[i] = 0;
                else
                    ob_4.coef[i] = ob_2.coef[j];
        }
        mnojnik = ob_1.coef[ob_1.len] / ob_4.coef[ob_1.len];
        temp.coef[temp.len - k] = mnojnik;
        k++;
        for (int i = 0; i <= ob_1.len; i++)
            ob_4.coef[i] *= mnojnik;
        for (int i = 0; i <= ob_1.len; i++)
            ob_1.coef[i] -= ob_4.coef[i];
        ob_1.len--;
        if (ob_2.len > ob_1.len) inAlgoritm = false;

    }

    if(choose == 0){
    return temp;
    } else if(choose == 1){
    return ob_1;
    }
}

Polynom operator/(const Polynom& t1, const Polynom& t2) {
    return Polynom::del(t1, t2, 0);
}

Polynom operator%(const Polynom& t1, const Polynom& t2) {
    return Polynom::del(t1, t2, 1);
}

Polynom Polynom::operator*=(const Polynom& t) {
    *this = *this * t;
    return *this;
}

Polynom Polynom::operator/=(const Polynom& t) {
   *this = *this / t;
    return *this;
}

Polynom Polynom::operator+=(const Polynom& t) {
    *this = *this + t;
    return *this;
}

Polynom Polynom::operator-=(const Polynom& t) {
    *this = *this - t;
    return *this;
}
Polynom Polynom::operator%=(const Polynom& t){
    *this = *this % t;
    return *this;
}

double& Polynom::operator[](int i) {
    if(i + 1 > this->len)
    {
        double* temp = new double[i + 1];
        for (int l = 0; l <= i; l++) {
            if (l <= len)temp[l] = this->coef[l];
            else temp[l] = 0;
        }
        delete this->coef;
        this->coef = temp;
        this->len = i - 1;
    }
    return this->coef[i];
}

double& Polynom::operator[](int i) const{
    if(i + 1 < this->len)
    {
        return coef[i];
}
}

double& Polynom::at(int i) {
    if (len > i)return this->coef[i];
    else throw ElemException{"Out of range"};
    
}

Polynom::operator std::string() const{
    std::string out;
    if(this->coef[0] != 0)out += std::to_string(this->coef[0]) + "x^" + "0";
    for(int i = 1; i <= this->len; i++){
        if(coef[i] > 0)out += "+" + std::to_string(coef[i]) + "x^" + std::to_string(i);
        else if(coef[i] < 0) out += std::to_string(coef[i]) + "x^" + std::to_string(i);
    }
    return out;
}

std::ostream& operator << (std::ostream &out, const Polynom& t)
{
    bool isEmpty = true;
    if(t.coef[0] != 0){out << t.coef[0] << "x^" << 0; isEmpty = false;}
    for(int i = 1; i <= t.len; i++){
        if(t.coef[i] > 0){out << "+" << t.coef[i] << "x^" << i;isEmpty = false;}
        else if(t.coef[i] < 0){ out << t.coef[i] << "x^" << i;isEmpty = false;}
    }
    if(isEmpty == true){out << "0";}
    return out;
}

