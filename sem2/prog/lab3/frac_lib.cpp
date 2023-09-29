#include <iostream>
#include <numeric>
#include <cmath>

#include "frac_lib.h"

Fraction::Fraction( double x ) {
    *this = tofrac( x );
};

Fraction::Fraction( int _x, int _y ) {  
    x = _x / std::gcd( _x, _y );
    y = _y / std::gcd( _x, _y );
};

Fraction::Fraction( const Fraction&& frac ) : Fraction( frac.x, frac.y ) {};
Fraction::Fraction( Fraction&& frac ) = default;

std::ostream& operator<< ( std::ostream &out, const Fraction &frac ) {
    if ( frac.y == 1 ) {
        out << frac.x;
    } else if ( frac.x == 0 ) {
        out << frac.x;
    } else {
        out << frac.x << "/" << frac.y;
    }

    return out;
};

std::istream& operator>> ( std::istream &in, Fraction &frac ) {
    in >> frac.x;
    in >> frac.y;

    frac = Fraction( frac.x, frac.y ); // сокращение дроби

    return in;
}

Fraction Fraction::operator- () const {
    return Fraction( -x, y );
}

Fraction Fraction::operator+ () const {
    return Fraction( +x, y );
}

Fraction Fraction::operator++ () const {
    return Fraction( x + 1, y );
}

Fraction Fraction::operator-- () const {
    return Fraction( x - 1, y );
}

Fraction Fraction::operator+ ( const Fraction& other ) const {
    return Fraction( x * other.y + other.x * y, other.y * y );
}

Fraction operator+( const Fraction& left, const Fraction& right ) {
    return Fraction( left.x * right.y + right.x * left.y, right.y * left.y );
}

Fraction Fraction::operator- ( const Fraction& other ) const {
    return Fraction( x * other.y - other.x * y, other.y * y );
}

Fraction Fraction::operator* ( const Fraction& other ) const {
    return Fraction( x * other.x, other.y * y );
}

Fraction Fraction::operator/ ( const Fraction& other ) const {
    return Fraction( x * other.y, other.x );
}

Fraction Fraction::operator+ ( const int& other ) const {
    return Fraction( x + other * y, y );
}

Fraction operator+ ( const int left, const Fraction& right ) {
    return Fraction( right.x + left * right.y, right.y );
}

Fraction Fraction::operator- ( const int& other ) const {
    return Fraction( x - other * y, y );
}

Fraction operator- ( const int left, const Fraction& right ) {
    return Fraction( right.x - left * right.y, right.y );
}

Fraction Fraction::operator* ( const int& other ) const {
    return Fraction( x * other, y );
}

Fraction operator* ( const int left, const Fraction& right ) {
    return Fraction( right.x * left, right.y );
}

Fraction Fraction::operator/ ( const int& other ) const {
    return Fraction( x, y * other );
}

Fraction operator/ ( const int left, const Fraction& right ) {
    return Fraction( right.x, right.y * left );
}

Fraction Fraction::operator+ ( const double& other ) const {
    return Fraction( x, y ) + tofrac( other );
}

Fraction Fraction::operator- ( const double& other ) const {
    return Fraction( x, y ) - tofrac( other );
}

Fraction Fraction::operator* ( const double& other ) const {
    return Fraction( x, y ) * tofrac( other );
}

Fraction Fraction::operator/ ( const double& other ) const {
    return Fraction( x, y ) / tofrac( other );
}

bool Fraction::operator== ( const Fraction& other ) const {
    return x == other.x && y == other.y;
}

bool Fraction::operator!= ( const Fraction& other ) const {
    return x != other.x && y != other.y;
}

bool Fraction::operator> ( const Fraction& other ) const {
    return x > other.x && y <= other.y;
}

bool Fraction::operator< ( const Fraction& other ) const {
    return x < other.x && y >= other.y;
}

bool Fraction::operator>= ( const Fraction& other ) const {
    return x >= other.x && y <= other.y;
}

bool Fraction::operator<= ( const Fraction& other ) const {
    return x <= other.x && y >= other.y;
}

Fraction& Fraction::operator= ( const Fraction& other ) {
    if ( this != &other ) {
        x = other.x;
        y = other.y;
    }
    
    return *this;
}

Fraction& Fraction::operator+= ( const Fraction& other ) {
    if ( this != &other ) {
        x = x + other.x;
        y = y + other.y;
    }
    
    return *this;
}

Fraction& Fraction::operator-= ( const Fraction& other ) {
    if ( this != &other ) {
        x = x - other.x;
        y = y - other.y;
    }
    
    return *this;
}

Fraction& Fraction::operator*= ( const Fraction& other ) {
    if ( this != &other ) {
        x = x * other.x;
        y = y * other.y;
    }
    
    return *this;
}

Fraction& Fraction::operator/= ( const Fraction& other ) {
    if ( this != &other ) {
        x = x / other.x;
        y = y / other.y;
    }
    
    return *this;
}

Fraction::operator float() const {
    return ( float )x / ( float )y;
}

Fraction::operator double() const {
    return ( double )x / ( double )y;
}

Fraction::operator std::string() const {
    return std::to_string( ( double )x / ( double )y );
}

Fraction tofrac( long double value ) {
    double intpart;
    double fracpart = std::modf( value, &intpart );

    int n, d;
    n = static_cast<int>( fracpart * 1000000 );
    d = 1000000;

    int gcd = std::gcd( n, d );
    n /= gcd;
    d /= gcd;

    n += static_cast<int>( intpart * d );
    if ( value < 0 ) {
        n *= -1;
    }
    
    return Fraction( n, d );
}

Fraction operator"" _frc( long double value ) {
    return tofrac( value );
}