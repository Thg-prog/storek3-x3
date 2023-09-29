#include <iostream>
#include <cstring>
using namespace std;

class Polynom {
    private:
        double* x;
        int pwr;
        Polynom( int power );
    public:
        Polynom( string poly );
        Polynom( double coff[], size_t size );
        Polynom( float coff[], size_t size );
        Polynom( std::initializer_list<double> args );
        Polynom();

        Polynom( const Polynom& poly );
        Polynom( Polynom&& poly ) noexcept;

        ~Polynom();

        double calculate( double a ) const;

        double operator[] ( int indx ) const;
        double& operator[] ( int indx );
        double& at ( int indx );

        Polynom operator- () const;
        
        Polynom operator+ ( const Polynom& other ) const;
        Polynom operator- ( const Polynom& other ) const;
        Polynom operator* ( const Polynom& other ) const;
        Polynom operator/ ( const Polynom& other ) const;
        Polynom operator% ( const Polynom& other ) const;
        
        Polynom& operator+= ( const Polynom& other );
        Polynom& operator-= ( const Polynom& other );
        Polynom& operator*= ( const Polynom& other );
        Polynom& operator/= ( const Polynom& other );
        Polynom& operator%= ( const Polynom& other );
        
        bool operator== ( const Polynom& other ) const;
        bool operator!= ( const Polynom& other ) const;
        
        Polynom& operator= ( const Polynom& other );
        Polynom& operator= ( Polynom&& other ) noexcept;
        
        friend std::ostream& operator<< ( std::ostream &out, const Polynom &poly );
        
        explicit operator std::string() const;
};

#include "polynomial.cpp"