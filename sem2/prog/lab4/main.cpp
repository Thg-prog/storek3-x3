#include "polynomial.h"

int main() {
    Polynom a( "-1x^6-x^2+3x^4+x^1" );
    Polynom b( "-1x^1+x^3" );

    cout << a << endl;
    cout << b << endl;

    cout << a + b << endl;
    cout << b + a << endl;
    cout << a - b << endl;
    cout << b - a << endl;
    return 0;
}
