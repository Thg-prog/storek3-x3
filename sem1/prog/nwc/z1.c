#include <stdio.h>
#include <stdlib.h>

/*
  Задача:
  Дана матрица, среди отрицательных элементов найти максимальный, среди положительных минимальный и поменять их местами.
  Теория:
  Структуры (struct), перечисления (enum), объединения (union) ООП в С

*/

typedef struct mt_id {
    int ln;
    int cl;
} mt_id;

void scan_matrix( float** A, int ln, int cl ){
    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
		    printf( "A[ %i ][ %i ]: ", i, j );
		    scanf( "%f", &A[ i ][ j ] );
        }
	}
}

float** init_matrix( int s, int j ){
	float** A = ( float** )malloc( s * sizeof( float* ) );
    for ( int i = 0; i<s; i++ ){
        A[ i ] = ( float* )malloc( j * sizeof( float ) );
    }

	return A;
}

mt_id search_min( float** A, int ln, int cl ){
    mt_id id;
    id.ln = 0;
    id.cl = 0;
    float m = A[ 0 ][ 0 ];

    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
            if ( m <= 0 || ( A[ i ][ j ] > 0 && A[ i ][ j ] < m ) ) {
                m = A[ i ][ j ];
                id.ln = i;
                id.cl = j;
            }
        }
    }

    if ( m < 0 ){
        return ( mt_id ){ -1, -1 };
    }

    return id;
}

mt_id search_max( float** A, int ln, int cl ){
    mt_id id;
    id.ln = 0;
    id.cl = 0;
    float m = A[ 0 ][ 0 ];

    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
            if ( m >= 0 || ( A[ i ][ j ] < 0 && A[ i ][ j ] > m ) ) {
                m = A[ i ][ j ];
                id.ln = i;
                id.cl = j;
            }
        }
    }

    if ( m > 0 ){
        return ( mt_id ){ -1, -1 };
    }

    return id;
}

void printm_f( float** A, int ln, int cl ){
    for ( int i = 0; i<ln; i++ ){
        for ( int j = 0; j<cl; j++ ){
            printf( "%2.2f\t", A[ i ][ j ] );
        }
        printf( "\n" );
    }
}

int main( int argc, char *argv[] ) {
    int lines = 0;
    int colums = 0;
    float** A;

    while ( lines <= 0 ) {
		printf( "Введите размер строк: " );
		scanf( "%i", &lines );
	}

    while ( colums <= 0 ) {
		printf( "Введите размер столбцов: " );
		scanf( "%i", &colums );
	}

    A = init_matrix( lines, colums );
    scan_matrix( A, lines, colums );
    
    printf( "\n" );
    printm_f( A, lines, colums );

    mt_id ida = search_max( A, lines, colums );
    mt_id idb = search_min( A, lines, colums );

    if ( ida.ln > -1 && ida.cl > -1 && idb.ln > -1 && idb.cl > -1 ){
        printf( "\n" );    
        printf( "MAX ( среди отриц. L: %i, C: %i ): %2.f\n", ida.ln, ida.cl, A[ ida.ln ][ ida.cl ] );
        printf( "MIN ( среди полож. L: %i, C: %i ): %2.f\n", idb.ln, idb.cl, A[ idb.ln ][ idb.cl ] );
        printf( "\n" );

        float rev = A[ ida.ln ][ ida.cl ];
        A[ ida.ln ][ ida.cl ] = A[ idb.ln ][ idb.cl ];
        A[ idb.ln ][ idb.cl ] = rev;
        
        printm_f( A, lines, colums );
    } else {
        printf( "Не найдены отрицательные или минимальные значения в матрице\n" );
    }
        
    for ( int i = 0; i<lines; i++ ){
        free( A[ i ] );
    }

    free( A );


    return 0;
}