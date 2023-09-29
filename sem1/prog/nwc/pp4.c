#include <stdio.h>
#include <stdlib.h>

//52

int main( int argc, char *argv[] ) {
	int N; // Количество поездок
	int k; // Штук в блоке
	int p1; // Стоимость одного талона
	int p2; // Cтоимость блока

	scanf( "%i %i %i %i", &N, &k, &p1, &p2 );

	if ( k == 1 )
		p1 = p2;

	int sum1 = N * p1;

	while ( N%k != 0 ){
		N++;
	}

	int sum2 = ( N / k ) * p2;
	
	printf( "Наименьшая сумма: %i\n", ( sum1 > sum2 )?sum2:sum1 );
	
	return 0;
}