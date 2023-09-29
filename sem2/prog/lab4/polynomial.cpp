#include <cstring>
#include <cassert>
using namespace std;

Polynom::Polynom( int power ) {
    pwr = power;
    x = new double[ pwr ];
}

int find_max( string poly ) {
    int max = 0;
    string ind;
    string s = poly;
    while ( s.size() != 0 ) {
        if ( s[ 0 ] >= '0' && s[ 0 ] <= '9' ) {
            ind += s[ 0 ];
        }

        if ( s[ 0 ] == '+' || s[ 0 ] == '-' || s.size() == 0 ) {
            if ( ind.size() != 0 ) { 
                if ( max < stoi( ind ) ) {
                    max = stoi( ind );
                    ind = "";
                }
            }
        }

        s.erase( 0, 1 );
    }
    
    if ( ind.size() != 0 ) { 
        if ( max < stoi( ind ) ) {
            max = stoi( ind );
            ind = "";
        }
    }
    
    return max;
}

int find_number( int i, int& ind, string poly ) {
    string num;
    string ind_c;
    string s = poly.substr( ( i > 0 ? i + 1 : i ), poly.size() );
    bool comp = false;
    while ( s.size() != 0 ) {
        if ( s[ 0 ] != 'x' && comp == false ) {
            num += s[ 0 ];
        } else {
            comp = true;

            if ( s[ 0 ] == '+' || s[ 0 ] == '-' ) {
                break;
            }

            ind_c += s[ 0 ];
        }
        
        s.erase( 0, 1 );
    }
    
    ind = stoi( ind_c.substr( 2, ind_c.size() ) );
    if ( num[ 0 ] == '-' ) {
        num.erase( 0, 1 );
        return stoi( num );
    } else if ( num.size() == 0 ) {
        return 1;
    } else {
        return stoi( num );
    }
}

Polynom::Polynom( string poly ) : Polynom( find_max( poly ) + 1 ) {
    for ( int i = 0; i < poly.size(); i++ ) {
        if ( i == 0 || poly[ i ] == '+' || poly[ i ] == '-' ) {
            int ind = 0;
            int n = find_number( i, ind, poly );

            x[ ind ] = ( poly[ i ] == '-' ? -n : n );
        }
    }
}

Polynom::Polynom( double coff[], size_t size ) : Polynom( size ) {
    for ( int i = 0; i < size; i++ ) {
        x[ i ] = coff[ i ];
    }
}

Polynom::Polynom( float coff[], size_t size ) : Polynom( size ) {
    for ( int i = 0; i < size; i++ ) {
        x[ i ] = coff[ i ];
    }
}

Polynom::Polynom( std::initializer_list<double> args ) : Polynom( args.size() ) {
    auto c = args.begin();
    for ( int i = 0; i<args.size(); i++ ) {
        x[ i ] = *c;
        ++c;
    }
}

Polynom::Polynom( const Polynom& poly ) : Polynom( poly.x, poly.pwr ) {};
Polynom::Polynom( Polynom&& poly ) noexcept {   
    copy( poly.x, poly.x+poly.pwr, x );
};

Polynom::~Polynom() {
    delete[] x;
}
Polynom::Polynom() : Polynom( 0 ) {};

double Polynom::calculate( double a ) const {
    double sum = 0;
    double res;

    for ( int i = pwr - 1; i!=-1; i-- ) {
        res = a;

        for ( int j = 1; j < i; j++ ) {
            res *= a;   
        }
        
        if ( i == 0 ) {
            sum += x[ i ];
        } else {
            sum += x[ i ] * res;
        }
    }

    return sum;
}

double Polynom::operator[] ( int indx ) const {
    return x[ indx ];
}

double& Polynom::operator[] ( int indx ) {
    if ( indx + 1 > pwr ) {
        double* b = new double[ indx + 1 ];
        copy( x, x+pwr, b );

        delete[] x;
        x = b;
        pwr = indx + 1;

        return x[ indx ];
    } else {
        return x[ indx ];
    }
}

double& Polynom::at ( int indx ) {
    if ( indx < 0 || indx >= pwr ) {
        throw out_of_range( "Index out of range" );
    }

    return x[ indx ]; 
}

Polynom Polynom::operator- () const {
    Polynom a;
    for ( int i = 0; i<pwr; i++ ) {
        a[ i ] = -x[ i ];
    }

    return a;
}

Polynom Polynom::operator+ ( const Polynom& other ) const {
    Polynom nwp;
    bool a = false;
    if ( max( pwr, other.pwr ) == pwr ) {
        nwp = *this;
    } else {
        a = true;
        nwp = other;
    }

    for ( int i = 0; i < min( pwr, other.pwr ); i++ ) {
        nwp[ i ] += ( a ? x[ i ] : other[ i ] );
    }

    return nwp;
}

Polynom Polynom::operator- ( const Polynom& other ) const {
    return *this + ( -other );
}

Polynom Polynom::operator* ( const Polynom& other ) const {
    Polynom nwp;

    for ( int i = 0; i < min( other.pwr, pwr ); i++ ) {
        for ( int j = 0; j < max( other.pwr, pwr ); j++ ) {
            nwp[ i + j ] += other[ i ] * x[ j ];
        }
    }

    return nwp;
}

Polynom Polynom::operator/ ( const Polynom& other ) const {
    int max = pwr - other.pwr + 1;
    Polynom n;

    int m = max - 1;
    for ( int i = pwr - 1; i >= other.pwr - 1; i-- ) {
        // n[ m ] = x[ i ] / other[ other.pwr - 1 ];
        for ( int k = other.pwr - 1; k >= 0; k-- ) {
            // x[ m + k ] -= n[ m ] * other[ k ];
            cout << "K: " << k << " " << m << endl;
        }

        // m--;

        cout << i << endl;
    }

    return n;
}

Polynom Polynom::operator% ( const Polynom& other ) const {
    Polynom p = *this;
    p -= ( p * p / other );
    
    return p;
}

Polynom& Polynom::operator+= ( const Polynom& other ) {
    Polynom p = *this + other;
    *this = p;
    return *this;
}

Polynom& Polynom::operator-= ( const Polynom& other ) {
    Polynom p = *this - other;
    *this = p;
    return *this;
}

Polynom& Polynom::operator*= ( const Polynom& other ) {
    Polynom p = *this * other;
    *this = p;
    return *this;
}

Polynom& Polynom::operator/= ( const Polynom& other ) {
    Polynom p = *this / other;
    *this = p;
    return *this;
}

Polynom& Polynom::operator%= ( const Polynom& other ) {
    Polynom p = *this % other;
    *this = p;
    return *this;
}

bool Polynom::operator== ( const Polynom& other ) const {
    if ( pwr == other.pwr ) {
        bool a = true;
        for ( int i = 0; i < pwr; i++ ) {
            if ( x[ i ] != other.x[ i ] ) {
                a = false;
            } 
        }

        return a;
    }

    return false;
}

bool Polynom::operator!= ( const Polynom& other ) const {
    return !( *this == other );
}

Polynom& Polynom::operator= ( const Polynom& other ) {
    if ( this != &other ) {
        pwr = other.pwr;
        delete[] x;
        this->x = new double[ pwr ];
        
        for ( int i = 0; i<pwr; i ++ ) {
            x[ i ] = other.x[ i ];
        }
    }
    
    return *this;
}

Polynom& Polynom::operator= ( Polynom&& other ) noexcept {
    if ( this != &other ) {
        pwr = other.pwr;
        this->x = new double[ pwr ];
        
        for ( int i = 0; i<pwr; i ++ ) {
            x[ i ] = other.x[ i ];
        }
    }
    
    return *this;
}

std::ostream& operator<< ( std::ostream &out, const Polynom &poly ) {
    for ( int i = poly.pwr-1; i!=-1; i-- ) {
        if ( poly.x[ i ] != 0 ) {
            out << poly.x[ i ];
            
            if ( i != 0 ) {
                out << "x^";
                out << i;
            }
            
            out << " ";
        }
    }

    return out;
}

Polynom::operator std::string() const {
    std::string a;
    for ( int i = pwr-1; i!=-1; i-- ) {
        if ( x[ i ] != 0 ) {
            a += ( x[ i ] );
            
            if ( i != 0 ) {
                a += "x^";
                a += i;
            }
            
            a += " ";
        }
    }

    return a;
}


