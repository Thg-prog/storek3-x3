#include <stdio.h>
#include <stdlib.h>

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

typedef struct mas_size {
	float *mas;
	int size;
} mas_size;

mas_size init_massive(){
	mas_size A;
	printf( "Введите размер массива: " );
	scanf( "%i", &A.size );
	A.mas = ( float* )malloc( A.size * sizeof( float ) );

	for ( int i = 0; i<A.size; i++ ){
		printf( "Введите A[ %i ]: ", i );
		scanf( "%f", &A.mas[ i ] );
	}
	
	return A;
}

int main( int argc, char *argv[] ) {
	mas_size A = init_massive();
	
	if ( A.size >= 1 ){
		float X;
		printf( "Введите X: " );
		scanf( "%f", &X );

		int need_i = -1;
		int i = 0;
		while ( i<=A.size && need_i == -1 ) {
			if ( A.mas[ i ] == X ){
				need_i = i;
			}

			i++;
		}

		printf( "%i", need_i ); 
	}

	free( A.mas );

	return 0;
}
