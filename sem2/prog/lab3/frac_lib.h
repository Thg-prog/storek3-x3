#include <iostream>
#include <numeric>
#include <cmath>

class Fraction {
    public:
        int x, y;
        
        Fraction( double x );
        Fraction( int _x=0, int _y=1);
        Fraction( const Fraction&& frac );
        Fraction( Fraction&& frac );

        // Перегрузка оператора вывода
        friend std::ostream& operator<< ( std::ostream &out, const Fraction &frac );
        friend std::istream& operator>> ( std::istream &in, Fraction &frac );

        Fraction operator++ () const;
        Fraction operator-- () const;
        Fraction operator-() const;
        Fraction operator+() const;
        
        // Перегрузка арифметических операторов.
        Fraction operator+ ( const Fraction& other ) const;
        Fraction operator- ( const Fraction& other ) const;
        Fraction operator* ( const Fraction& other ) const;
        Fraction operator/ ( const Fraction& other ) const;

        Fraction operator+ ( const int& other ) const;
        Fraction operator- ( const int& other ) const;
        Fraction operator* ( const int& other ) const;
        Fraction operator/ ( const int& other ) const;

        Fraction operator+ ( const double& other ) const;
        Fraction operator- ( const double& other ) const;
        Fraction operator* ( const double& other ) const;
        Fraction operator/ ( const double& other ) const;

        // Перегрузка операторов сравнения.
        bool operator== ( const Fraction& other ) const;
        bool operator!= ( const Fraction& other ) const;
        bool operator> ( const Fraction& other ) const;
        bool operator< ( const Fraction& other ) const;
        bool operator>= ( const Fraction& other ) const;
        bool operator<= ( const Fraction& other ) const;

        // Перегрузка оператора присваивания
        Fraction& operator= ( const Fraction& other );
        Fraction& operator+= ( const Fraction& other );
        Fraction& operator-= ( const Fraction& other );
        Fraction& operator*= ( const Fraction& other );
        Fraction& operator/= ( const Fraction& other );

        friend Fraction operator+( const Fraction& left, const Fraction& right );

        // Приведение типов в float 
        explicit operator float() const;
        explicit operator double() const;
        explicit operator std::string() const;
};

Fraction operator+( const int left, const Fraction& right );
Fraction operator-( const int left, const Fraction& right );
Fraction operator*( const int left, const Fraction& right );
Fraction operator/( const int left, const Fraction& right );

Fraction operator"" _frc( long double value );
Fraction tofrac( long double value );