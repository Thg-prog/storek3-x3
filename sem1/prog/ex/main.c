#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for ( int i = 0; i < N; i++ ){
//  ГЛАВНАЯ ДИАГОНАЛЬ
//  A[ i ][ i ]
//}

// for ( int i = 0; i < N; i++ ){
//    for ( int j = 0; i <= i; j++ ){
//      ПОД ГЛАВНОЙ
//      A[ i ][ j ]
//    }
//}

// for ( int i = 0; i < N; i++ ){
//  A[ i ][ N - 1 - i ]
//}

// МАССИВЫ (ВЕЩЕСТВЕННЫЕ)
float* init_massive_f( int s ){
	float* A;
	A = ( float* )malloc( s * sizeof( float ) );

	for ( int i = 0; i<s; i++ ){
		printf( "A[ %i ]: ", i );
		scanf( "%f", &A[ i ] );
	}

	return A;
}

// МАССИВЫ (ЦЕЛОЧИСЛЕННЫЕ)
int* init_massive( int s ){
	int* A;
	A = ( int* )malloc( s * sizeof( int ) );

	for ( int i = 0; i<s; i++ ){
		printf( "A[ %i ]: ", i );
		scanf( "%i", &A[ i ] );
	}

	return A;
}

// ВЫВОД МАССИВА (ВЕЩЕСТВЕННЫЕ)
void print_massive_f( float* A, int size ){
    for ( int i = 0; i<size; i++ ){
		printf( "%i = %.03f\n", i, A[ i ] );
	}
}

// ВЫВОД МАССИВА (ЦЕЛОЧИСЛЕННЫЕ)
void print_massive( int* A, int size ){
    for ( int i = 0; i<size; i++ ){
		printf( "%i = %i\n", i, A[ i ] );
	}
}

// МАТРИЦЫ (ВЕЩЕСТВЕННЫЕ)
float** init_matrix_f( int s, int j ){
	float** A;
    A = ( float** )malloc( s * sizeof( float* ) );

    for ( int i = 0; i<s; i++ ){
        A[ i ] = ( float* )malloc( j * sizeof( float ) );
    }

	return A;
}

// МАТРИЦЫ (ЦЕЛОЧИСЛЕННЫЕ)
int** init_matrix( int ln, int cl ){
	int** A;
    A = ( int** )malloc( ln * sizeof( int* ) );

    for ( int i = 0; i<ln; i++ ){
        A[ i ] = ( int* )malloc( cl * sizeof( int ) );
    }

	return A;
}

// ВВОД МАТРИЦ (ВЕЩЕСТВЕННЫЕ)
void scan_matrix_f( float** A, int ln, int cl ){
    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
		    printf( "A[ %i ][ %i ]: ", i, j );
		    scanf( "%f", &A[ i ][ j ] );
        }
	}
}

// ВВОД МАТРИЦ (ЦЕЛОЧИСЛЕННЫЕ)
void scan_matrix( int** A, int ln, int cl ){
    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
		    printf( "A[ %i ][ %i ]: ", i, j );
		    scanf( "%i", &A[ i ][ j ] );
        }
	}
}

// ВЫВОД МАТРИЦ (ВЕЩЕСТВЕННЫЕ)
void print_matrix_f( float** A, int ln, int cl ){
    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
            printf( "%2.2f\t", A[ i ][ j ] );
        }
        printf( "\n" );
    }
}

// ВЫВОД МАТРИЦ (ЦЕЛОЧИСЛЕННЫЕ)
void print_matrix( int** A, int ln, int cl ){
    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
            printf( "%i\t", A[ i ][ j ] );
        }
        printf( "\n" );
    }
}

// ФУНКЦИИ ВЕЩЕСТВЕННЫЕ (func_f)
// ЦЕЛОЧИСЛЕННЫЕ БЕЗ ПОДЧЕРКИВАНИЙ
int main( int argc, char *argv[] ) {
    int s_lines = 0; 
    int s_cols = 0;
	float** A;
    int max;

    while ( s_lines <= 1 ) {
		printf( "Введите размер строк: " );
		scanf( "%i", &s_lines );
	}

    while ( s_cols <= 1 ) {
		printf( "Введите размер столбцов: " );
		scanf( "%i", &s_cols );
    }

    A = init_matrix_f( s_lines, s_cols );
    scan_matrix_f( A, s_lines, s_cols );
    print_matrix_f( A, s_lines, s_cols );
    
    int max_col, col;
    for ( int i = 0; i<s_cols; i++ ){
        max_col = 0;
        for ( int j = 0; j<s_lines; j++ ){
            if ( A[ j ][ i ] > 0 ){
                max_col++;
            }
        }
        
        if ( max_col > max ){
            max = max_col;
            col = i;
        }
    }

    if ( max == 0 ){
        printf( "Положительных чисел в массиве нет\n" );
    } else {
        printf( "Количество положительных: %i\nВ столбце: %i\n", max, col );
    }

    for ( int i = 0; i<s_lines; i++ ){
        free( A[ i ] );
    }

    free( A );


    return 0;
}