#include <iostream>
#include "Polynom.h"
using namespace std;



int main() {
    float coef[] = { 3, 0, 6 }; //3 + 3x^1 + 0x^2 + 6x^3
    double coef2[] = { 3, 2, 1}; //3 + 2x^1 + 1x^2
    const Polynom polynom(coef, 3);
    polynom[0]= 123;
    cout << polynom << endl;
    cout << polynom[0] << endl;
    //Polynom polynom2(coef2, 2);
    Polynom polynom2 = {3,2,1};
    //cout << polynom2 << endl;
    polynom2 /= polynom2;
    //cout << "2" << polynom2 << endl;
    //-polynom;
    //polynom + polynom2;
    //Polynom polynom3 = polynom - polynom;
    //cout << polynom3 << endl;;
    cout << polynom2;
    try {
        polynom2.at(1);
    }
    catch (ElemException& e) {
        cerr << e.getMessage() << endl;
    }
    
    //polynom2.output();
    return 0;
}
