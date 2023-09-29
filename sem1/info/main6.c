#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void dsort( float *A, int size ){
	if ( size > 1 ){
		float min;
		int rev = 1;
		int m = size;

		while ( rev == 1 ){
			rev = 0;
			m--;
			for ( int i = 0; i<m; i++ ) {
				if ( A[ i ] > A[ i + 1 ] ){
					min = A[ i ];
					A[ i ] = A[ i + 1 ];
					A[ i + 1 ] = min;
					rev = 1;
				}
			}
		}
	} else {
		printf( "Массив не нуждается в сортировке" );
	}
}

float* init_massive( int s ){
	float* A;
	A = ( float* )malloc( s * sizeof( float ) );

	for ( int i = 0; i<s; i++ ){
		printf( "A[ %i ]: ", i );
		scanf( "%f", &A[ i ] );
		//A[ i ] = rand()%1000;
	}

	return A;
}

/* сравнение целых */
int comp ( const void *i, const void *j ) {
	return *( float* )i - *( float* )j;
}


float *mcpy( float* arr, int size ){
	float *new;
	new = ( float* )malloc( size * sizeof( float ) );

	for ( int i = 0; i<size; i++ ){
		new[ i ] = arr[ i ];
	}

	return new;
}

int main( int argc, char *argv[] ) {
	int size = 0;
	float* A;
	float *B;

	while ( size <= 0 ) {
		printf( "Введите размер массива: " );
		scanf( "%i", &size );
	}

	A =	init_massive( size );
	B = mcpy( A, size );

	clock_t CurTime;
	clock_t CurTime2;

	printf("DSORT\n");

	for ( int i = 0; i<size; i++ ){
		printf( "%i = %f\n", i, A[ i ] );
	}

	CurTime = clock();
	dsort( A, size );
	CurTime = clock() - CurTime;
	CurTime = ( double )CurTime / CLOCKS_PER_SEC;

	printf("\n");

	for ( int i = 0; i<size; i++ ){
		printf( "%i = %f\n", i, A[ i ] );
	}

	printf( "dsort %d\n", CurTime );

	printf( "QSORT\n" );

	for ( int i = 0; i<size; i++ ){
		printf( "%i = %f\n", i, B[ i ] );
	}

	printf( "\n" );

	CurTime2 = clock();
	qsort( B, size, sizeof( float ), comp );
	CurTime2 = clock() - CurTime2;
	CurTime2 = ( double )CurTime2 / CLOCKS_PER_SEC;

	for ( int i = 0; i<size; i++ ){
		printf( "%i = %f\n", i, B[ i ] );
	}

	printf( "dsort %d qsort %d\n", CurTime, CurTime2 );

	free( A );
	free( B );

	return 0;
}

