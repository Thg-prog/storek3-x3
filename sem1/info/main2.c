#include <stdio.h>
#include <stdlib.h>

float* mmreplace( float *A, int size ){
	float min = A[ 0 ];
	float max = A[ 0 ];
	
	int min_i = 0;
	int max_i = 0;
	
	for ( int i = 0; i<size; i++ ){
		if ( A[ i ] < min ){
			min = A[ i ];
			min_i = i;
		}
		
		if ( A[ i ] > max ){
			max = A[ i ];
			max_i = i;
		}
	}
	
	A[ min_i ] = max;
	A[ max_i ] = min;
	
	return A;
}

int main( int argc, char *argv[] ) {
	float *A;
	int size;
		
	scanf( "%i", &size );

	if ( size >= 1 ){
		A = ( float* )malloc( size * sizeof( float ) );
		for ( int i = 0; i<size; i++ ){
			scanf( "%f", &A[ i ] );
		}
		
		printf( "\n" );
		
		A = mmreplace( A, size );
		
		for ( int i = 0; i<size; i++ ){
			printf( "%f\n", A[ i ] );
		}

		free( A );
	}
	
	return 0;
}
