#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

double E = 1.e-6;

namespace math {
    const double pi = 3.1415926535897932;

    int fact( int x ) {
        int r = 1;
        for ( int i = 1; i<=x; i++ ) {
            r = r * i;
        }

        return r;
    };


    // 1 = 0
    // 2 = 0.69
    // 3 = 1.09
    // 4 = 1.38
    double dlog( double x ) {
        double s = x - 1;
        double prev = 0;
        double prev_prev = prev;
        int i = 1;
        double xs = x;
        int f = 1;
        int si = -1;

        while ( i < 2 || abs( s - prev ) > E ) {
            if ( i > 1 ) { 
                prev_prev = prev;
                prev = s;
            }

            if ( i > 30 ) { 
                break;
            }
       		
			si *= -1;
            s += si * xs / i;

			cout << si << " * " << xs << " / " << i << " = " << s << endl;
            
			xs *= x;
            f++;
            i++;
        }

        return s;
    };

    double dsin( double x ) {
    	return 0;
	};

    double dcos( double x ) {
		if ( dsin( x ) == 1 ) { 
			return 0;
		} else {
			return sqrt( 1 - ( dsin( x ) * dsin( x ) ) );
		}
	};

    double dtan( double x ) {
        return dsin( x ) / dcos( x );
    };

    double dcan( double x ) {
        return dcos( x ) / dsin( x );
    };

}

double mathfunc( int tact, double tsum, std::string func, std::string arg ) {
    double mul = 1;
    double val = 0;

    int pos = 0;
    int epos = 0;
    int size = 5;

    pos = arg.find( "(" );
    epos = arg.find( ")" );
    
    if ( pos != std::string::npos && epos != std::string::npos ) {
        size += arg.substr( pos, epos ).size() - 1;
        val = stod( arg.substr( pos + 1, epos - 1 ) );
    }
    
    if ( arg.size() >= size ) {
        mul = stod( arg.substr( 0, arg.size() - 3 ) );
    }

    if ( func == "sin" ) {
        val = mul * ( math::dsin( val * math::pi / 180 ) );
    } else if ( func == "cos" ) {
        val = mul * ( math::dcos( val * math::pi / 180 ) );
    } else if ( func == "tan" ) {
        val = mul * ( math::dtan( val * math::pi / 180 ) );
    } else if ( func == "can" ) {
        val = mul * ( math::dcan( val * math::pi / 180 ) );
    } else if ( func == "log" ) {
        val = mul * math::dlog( val );
    } 
    
    if ( tact == 0 ) {
        tsum = val;
    } else if ( tact == 1 ) {
        tsum += val;
    } else if ( tact == 2 ) {
        tsum -= val;
    } else if ( tact == 3 ) {
        tsum *= val;
    } else if ( tact == 4 ) {
        tsum /= val;
    }

    return tsum;
}

namespace dmath { 
    const double pi = 3.1415926535897932;
	
	class frac { 
		private:
			double x;
			double y;
		public:
			frac( ) : x( 0 ), y( 1 ) { };
			frac( double _x, double _y ) : x( _x ), y( _y ) { };
			frac( int _x, int _y ) : x( _x ), y( _y ) { };

			friend std::ostream& operator<< ( std::ostream &out, const frac& _frac );	
	};	
	
	std::ostream& operator<< ( std::ostream &out, const frac& _frac ) { 
		out << _frac.x / _frac.y;
		return out;
	};

	double sin( double x ) {
   		x *= ( x < 0 ) ? -1 : 1;

		x = fmod( fabs( x ), 2*pi );

        cout << x << endl;
        if ( x > pi ) { 
            x -= pi;
        }

        if ( x > pi/2 ) {
            x = pi - x;
        }

        double s = 0;
        double prev = 0;
        int i = 1;
        double xs = x;
        int f = 1;
        int si = -1;

        while ( i < 2 || abs( s - prev ) > E ) {
            if ( i > 1 ) prev = s;
            si *= -1;

            s += ( si * xs ) / math::fact( f );
            xs *= x * x;
            f += 2;
            i++;
        }
			
		cout << "SIN: " << i << " ITERATIONS!" << endl;

        return s;

	};

	double cos( ) { 
		double ret = 0;

		return ret;
	};

	double tan( ) { 
		double ret = 0;

		return ret;
	};

	double catan( ) { 
		double ret = 0;

		return ret;
	};
	
};

int main ( int argc, char* argv[] ) {
   // // 0 +, 1 -, 2 *, 3 /
   // 
   // std::vector<std::string> all_args;

   // if ( argc > 1 ){
   //     all_args.assign( argv + 1, argv + argc );
   // }   

   // int tact = 0;
   // double tsum = 0;

   // for ( std::string arg : all_args ) {
   //     if ( arg.find( "sin" ) != std::string::npos ) {
   //         tsum = mathfunc( tact, tsum, "sin", arg );
   //     } else if ( arg.find( "cos" ) != std::string::npos ) {
   //         tsum = mathfunc( tact, tsum, "cos", arg );
   //     } else if ( arg.find( "tan" ) != std::string::npos ) {
   //         tsum = mathfunc( tact, tsum, "tan", arg );
   //     } else if ( arg.find( "can" ) != std::string::npos ) {
   //         tsum = mathfunc( tact, tsum, "can", arg );
   //     } else if ( arg.find( "log" ) != std::string::npos ) {
   //         tsum = mathfunc( tact, tsum, "log", arg );
   //     } else if ( arg.find( "+" ) != std::string::npos ) {
   //         tact = 1;
   //     } else if ( arg.find( "-" ) != std::string::npos ) {
   //         tact = 2;
   //     } else if ( arg.find( "*" ) != std::string::npos ) {
   //         tact = 3;
   //     } else if ( arg.find( "/" ) != std::string::npos ) {
   //         tact = 4;
   //     }
   // }

   // cout << fixed << tsum << endl;

   // return 0;

	dmath::frac a( 1440, 3 );	
	cout << fixed << a << endl;
   	return 0;
}
