#include <stdio.h>
#include <stdlib.h>
//22 (no)
int isnum( int num ){
	int dels = 1;

	for ( int i = 2; i<num-1; i++ ){
		if ( ( num % i ) == 0 ) {
			dels = 0;
		}
	}

	return dels;
}

int main( int argc, char *argv[] ) {
	int i, M, N;
	scanf( "%i", &M );
	scanf( "%i", &N );

    int A1, A2;

	int c = 0;
	for ( int i = M; i<N; i++ ){
        A1 = i;
        A2 = i + 2;

        if ( isnum( A1 ) && ( isnum( A2 ) ) ){
			c++;
		}
	}

	printf( "%i", c );

	puts( "" );
	
	return 0;
}