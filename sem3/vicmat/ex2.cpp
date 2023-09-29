#include<iostream>
#include<cmath>
using namespace std;

class matrix { 
	private:
		int x;
		int y;
	public:
		double** arr;
		matrix( int _x, int _y ) { 
			x = _x;
			y = _y;

			arr = new double*[ x ];
			for ( int i = 0; i<x; i++ ) { 
				arr[ i ] = new double[ y ];
			}
		}

		matrix( int _x, matrix other ) { 
			x = other.x - 1;
			y = other.y - 1;

			arr = new double*[ x ];
			for ( int i = 0; i<x; i++ ) { 
				arr[ i ] = new double[ y ];
			}
			
			_x++;
			int _i = 0;
			int _j = 0;
			for ( int i = 1; i<other.x; i++ ) {
				for ( int j = _x; j<other.y+_x-1; j++ ) {
					arr[ i - 1 ][ ( j - 1 ) % y ] = other.arr[ i % other.x ][ j % other.y ];
					_j++;
				}
				_j = 0;
				_i++;
			}
		}
		

		// 1  2   3   4
		// 5  6   7   8
		// 9  10  11  12
		// 13 14  15  16

		double det2( int _j ) {
			double ret = 0;
			int l = _j;
			int _i = 0;
			_i++; 
			_j++;
			_i %= x;
			_j %= x;
			

			if ( x > 3 ) {
				if ( int i = 0; i < x-3; i++ ) {
					matrix x3( l, *this );
					cout << x3 << endl;
					cout << pow( -1, 1 + l ) << " * " << arr[ 0 ][ l ] << " * " << x3.det3( ) << endl;
					ret += pow( -1, 1 + l+1 ) * arr[ 0 ][ l ] * x3.det3( );
					cout << ret << endl;
					return ret;
				}
			} else { 
				ret += arr[ _i ][ _j ] * arr[ ( _i + 1 ) % x ][ ( _j + 1 ) % x ] - arr[ ( _i + 1 ) % x ][ _j ] * arr[ _i ][ (  _j + 1 ) % x ];  
				ret *= arr[ 0 ][ l ];
			}

			return ret;
		}

		double det3( ) {
			double ret = 0;
			for ( int i = 0; i<x; i++ ) { 
				ret += det2( i );
			}
			
			return ret;
		}

		friend std::ostream& operator<< ( std::ostream &out, matrix &a );	
};

std::ostream& operator<< ( std::ostream &out, matrix &a ) { 
	for ( int i = 0; i<a.x; i++ ) {
		for ( int j = 0; j<a.y; j++ ) {
			cout << a.arr[ i ][ j ] << " "; 
		}

		cout << endl;
	}

	return out;
}


int main( ) {
	int x;
	int y;
	cin >> x >> y;
	matrix m( x, y );
	for ( int i = 0; i<x; i++ ) {
		for ( int j = 0; j<y; j++ ) {
			cout << "I( " << i << ")" << " J( " << j << "):";
			cin >> m.arr[ i ][ j ];
		}
	
	}
	cout << m << endl;
	cout << m.det3( );
	return 0;
}


