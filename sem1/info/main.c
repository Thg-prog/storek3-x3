#include <stdio.h>
#include <stdlib.h>

int sumof( int num ){
	int sum = 0;
	
	if ( num < 0 )
 		num = abs( num );
 		
	while ( num > 0 ){
		sum = sum + ( num % 10 );
		num = num / 10;
	}
	
	return sum;
}

int main( int argc, char *argv[] ) {
	int num;
	scanf( "%i", &num );
	printf( "%i", sumof( num ) );

	puts( "" );
	
	return 0;
}
