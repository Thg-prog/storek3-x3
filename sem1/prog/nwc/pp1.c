#include <stdio.h>
#include <stdlib.h>
//17
int sumofq( int num ){
	int sum = 0;
	
	if ( num < 0 )
 		num = abs( num );
 		
	while ( num > 0 ){
		sum = sum + ( ( num % 10 ) * ( num % 10 ) );
		num = num / 10;
	}
	
	return sum;
}

int main( int argc, char *argv[] ) {
	int N, K;
	scanf( "%i", &N );
	scanf( "%i", &K );

	for ( int i = 0; i<K; i++ ){
		N = sumofq( N );
	}

	printf( "%i", N );

	puts( "" );
	
	return 0;
}