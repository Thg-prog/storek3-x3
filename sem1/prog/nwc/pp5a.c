#include <stdio.h>
#include <stdlib.h>

//115

int nod( int a, int b ){
    a = abs( a );
    b = abs( b );
    
    while ( a != 0 && b != 0 ){
        if ( a > b ){
            a = a % b;
        } else {
            b = b % a;
        }
    }

    return a + b;
}

int main( int argc, char *argv[] ) {
	int N, A, B;
    printf( "N = " );
    scanf( "%i", &N );

    int m = 0;
    int n;

    if ( N > 1 ){
        for ( int i = N-1; i>0; i-- ){
            n = nod( i, ( N-i ) );
            if ( n > m ){
                m = n;
                A = i;
                B = N-i;
            }
        }
        
        printf( "NOD = %i\nA = %i\nB = %i", m, A, B );

        puts( "" );
    }

	
	return 0;
}