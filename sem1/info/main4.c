#include <stdio.h>
#include <stdlib.h>

typedef struct mas_size {
	float *mas;
	int size;
} mas_size;

mas_size init_massive(){
	mas_size A;
	printf( "Vvedite razmer massiva: " );
	scanf( "%i", &A.size );
	if ( A.size > 1 ){
		A.mas = ( float* )malloc( A.size * sizeof( float ) );

		for ( int i = 0; i<A.size; i++ ){
			printf( "Vvdeite A[ %i ]: ", i );
			scanf( "%f", &A.mas[ i ] );
		}
	
		return A;
	}
}

int main( int argc, char *argv[] ) {
	mas_size A = init_massive();
	
	if ( A.size >= 1 ){
		float X;
		printf( "Vvedite X: " );
		scanf( "%f", &X );

		int left = 0;
        int right = A.size - 1;
        int need = 0;

        while ( left <= right ){
            need = ( left + right ) / 2;
            if ( A.mas[ need ] < X ){
                left = need + 1;
            } else if ( A.mas[ need ] > X ){
                right = need - 1;
            } else {
                printf( "%i", need );
                break;
            }
        }
	}

    free( A.mas );

	return 0;
}
