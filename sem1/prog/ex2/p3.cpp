#include<iostream>
#include<string>
#include<math.h>
#include "p3.h"

using namespace std;

Num::Num( int _d ) : d( _d ), s( 10 ) {};

Num::Num( std::string a, int _s = 10 ) : s( _s < 2 ? 2 : _s ) {
    if ( s != 10 ) {
        int sum = 0;
        int pwr = a.size();
        for ( int i = 0; i < pwr; i++ ) {
            if ( a[ i ] - ( 'A' - 10 ) >= s ) {
                throw runtime_error( "The system number doesn't match reality" );
            };

            if ( a[ i ] >= 'A' && a[ i ] <= 'Z' ) {
                sum += ( pow( s, pwr - i - 1 ) * ( a[ i ] - ( 'A' - 10 ) ) );
            } else if ( a[ i ] >= '0' && a[ i ] <= '9' ){
                sum += ( pow( s, pwr - i - 1 ) * ( a[ i ] - '0' ) );
            }
        }

        d = sum;
    } else if ( a.size() > 0 ) {
        try {
            d = stoi( a, NULL, s );
        } catch ( const invalid_argument& n ){
            throw runtime_error( "The system number doesn't match reality" );
        }
    }
};

Num::Num() : Num( 0 ) {};

Num::Num( Num&& oth ) : s( oth.s ), n( oth.n ), d( oth.d ) {};

Num::Num( const Num& oth ) : s( oth.s ), n( oth.n ), d( oth.d ) {};

bool operator== ( const Num& ath, const Num& other ) {
    return ath.d == other.d;
}

bool operator!= ( const Num& ath, const Num& other ) {
    return !( ath == other );
}

bool operator> ( const Num& ath, const Num& other ) {
    return ath.d > other.d;
}

bool operator< ( const Num& ath, const Num& other ) {
    return ath.d < other.d;
}

bool operator>= ( const Num& ath, const Num& other ) {
    return !( ath < other );
}

bool operator<= ( const Num& ath, const Num& other ) {
    return !( ath > other );
}

Num& Num::operator= ( const Num& other ) {
    if ( this != &other ) {
        n = other.n;
        s = other.s;
        d = other.d;
    }
    
    return *this;
}

std::ostream& operator<< ( std::ostream &out, const Num &num ) {
    out << num.d;
    return out;
}

std::istream& operator>> ( std::istream &in, Num &num ) {
    in >> num.n;
    in >> num.s;

    num = Num( num.n, num.s ); // пересоздание num

    return in;
}

int main() {
    Num N1, N2;
    cin >> N1 >> N2;

    cout << "N1 (10): " << N1 << endl << "N2 (10): " << N2 << endl;    
    cout << ( N1 != N2 ? ( N1 > N2 ? ( "N1 > N2" ) : ( "N1 < N2" ) ) : ( "N1 == N2" ) ) << endl;

    Num N3;
    Num N4 = Num( 10 );
    Num N5 = N4;
    N3 = N5;
    
    cout << N3 << " " << N4;
    

    return 0;
}