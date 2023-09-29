#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Задача: дан массив вещественных чисел. 
С клавиатуры вводится число Х, определить находится ли это число Х в заданном массиве 
(если находится, то указать его место в массиве) с помощью поиска «перебором».
Необходимо:
1)Определить входные и выходные данные.
2)Разработать блок-схему алгоритма.
3)Реализовать алгоритм на языке С.
4)Составить тесты для проверки работоспособности алгоритма.
5)Проверить работоспособность программы на разработанных тестах.
6)Оформить отчет по лабораторной работе (см. требования к отчету).
Указание:  массив вводить с клавиатуры, 
предварительно ввести с клавиатуры количество элементов массива 
(делать проверку, чтобы количество элементов массива было больше или равно 1), 
желательно память под массив выделять динамически. Массив можно задавать как упорядоченным, 
так не неупорядоченным.*/

/*
void init_ai( float* A, int s ){
	for ( int i = 0; i<s; i++ ){
		//printf( "A[ %i ]: ", i );
		//scanf( "%f", &A[ i ] );
		A[ i ] = rand()%1000;
	}
}

int init_massive( float *A ){
	int s = 0;
	
	while ( s <= 0 ) {
		printf( "Введите размер массива: " );
		scanf( "%i", &s );
	}
	
	A = ( float* )malloc( s * sizeof( float ) );

	init_ai( A, s );

	return s;
}
*/

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

int comp (const void *, const void *);


void dsort( float *A, size_t size ){
	if ( size > 1 ){
		int imin;
		float min;

		for ( int left = 0; left<size; left++ ){
			min = A[ left ];
			imin = left;

			for ( int i = left+1; i<size; i++ ){
				if ( A[ i ] < min ){
					min = A[ i ];
					imin = i;
				}
			}

			if ( imin != left ){
 				A[ imin ] = A[ left ];
				A[ left ] = min;
			}
		}
	} else {
		printf( "Массив не нуждается в сортировке\n" );
	}
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

	printf( "QSORT\n" );

	for ( int i = 0; i<size; i++ ){
		printf( "%i = %f\n", i, B[ i ] );
	}

	printf( "\n" );

	clock_t CurTime2;
	CurTime2 = clock();
	qsort( B, size, sizeof(float), (int(*) (const void *, const void *)) comp );
	CurTime2 = clock() - CurTime2;
	CurTime2 = ( double )CurTime2 / CLOCKS_PER_SEC;

	for ( int i = 0; i<size; i++ ){
		printf( "%i = %f\n", i, B[ i ] );
	}

	printf( "qsort %d\ndsort %d\n", CurTime2, CurTime );

	free( A );
	free( B );

	return 0;
}

/* сравнение целых */
int comp (const void *i, const void *j)
{
	return *(float*)i - *(float*)j;
}