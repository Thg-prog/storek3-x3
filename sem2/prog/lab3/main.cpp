#include "frac_lib.cpp"

using namespace std;
int main( int argc, char *argv[] ) {
    Fraction a = Fraction( 4, 2 );
    cout << a << endl;

    Fraction b = 3.14_frc;
    cout << b << endl;

    a = Fraction( 5, 2 );

    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    cout << a << " / " << b << " = " << a / b << endl;

    cout << endl;

    cout << a << " + " << 2 << " = " << a + 2 << endl;
    cout << a << " - " << 2 << " = " << a - 2 << endl;
    cout << a << " * " << 2 << " = " << a * 2 << endl;
    cout << a << " / " << 2 << " = " << a / 2 << endl;

    cout << a << " + " << 2 << " = " << 2 + a << endl;
    cout << a << " - " << 2 << " = " << 2 - a << endl;
    cout << a << " * " << 2 << " = " << 2 * a << endl;
    cout << a << " / " << 2 << " = " << a / a << endl;

    cout << a << " + " << +b << " = " << -a << endl;
    cout << a << " - " << +b << " = " << ---a << endl;

    double c = 2.24;
    cout << endl;
    cout << a << " + " << c << " ( " << tofrac( c ) << " )" << " = " << a + c << endl;
    cout << a << " - " << c << " ( " << tofrac( c ) << " )" << " = " << a - c << endl;
    cout << a << " * " << c << " ( " << tofrac( c ) << " )" << " = " << a * c << endl;
    cout << a << " / " << c << " ( " << tofrac( c ) << " )" << " = " << a / c << endl;

    Fraction v = Fraction( 2, 5 );
    cin >> v;
    cout << v << endl;

    a+=a += b;
    cout << a << endl;
    b *= a;
    cout << b << endl;
    a /= b;
    cout << a << endl;
    b -= a;
    cout << b << endl;

    +v;
    cout << -v << endl;

    Fraction vz = Fraction( 2, 4 );
    cout << ( 2.25 == vz );

    return 0;
}
