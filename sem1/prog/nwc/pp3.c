#include <stdio.h>
#include <stdlib.h>
//122

void del( int *a_, int *b_ ){
    int a, b;
    int c, d;

    a = *a_;
    b = *b_;

    if ( a > b && ( ( b % a ) > 0 && ( a % ( b % a ) == 0 )) ){
        c = a / ( b % a );
        d = b / ( b % a );
    } else if ( b > a && ( ( a % b ) > 0 && ( b % ( a % b ) == 0 ) ) ){
        c = a / ( a % b );
        d = b / ( a % b );
    } else if ( a == b ) {
        c = 1;
        d = 1;
    } else {
        c = a;
        d = b;
    }

    *a_ = c;
    *b_ = d;   
}

int main( int argc, char *argv[] ) {
	int a, b;

	scanf( "%i", &a );
	scanf( "%i", &b );

    del( &a, &b );

    printf( "\n%i\n%i", a, b );

    puts( "" );
	
	return 0;
}