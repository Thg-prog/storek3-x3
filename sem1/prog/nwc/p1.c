#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char *argv[] ) {  
    if ( argc == 1 ){
        puts( "Ввод не соответствует командам, используйте -h (--help)" );
        return 0;
    }

    if ( strcmp( argv[ 1 ], "-h" ) == 0 || ( strcmp( argv[ 1 ], "--help" ) == 0 ) ){
        puts( "Labolatory work #1  / Parametrs\
\n-h (--help) все возможные команды\
\n-t (--table) выдает в табличном виде размеры всех простых типов языка\
\n-c (--calc) арифметическое выражение расчитывает простое арифметическое выражение вида число операция число (числа целые и вещественные)\
\n  Флаги для параметра -c\
\n  -x (--hex) ответ в 16-ричной формате\
\n  -i (--int) входные числа целые");
    } else if ( argc > 1 ){
        if ( strcmp( argv[ 1 ], "-t" ) == 0 || ( strcmp( argv[ 1 ], "--table" ) == 0 ) ){
            printf( "%13s | %3s", "type", "size" );
            puts( "\n------------------------" );
            for ( int i = 0; i < 9; i++ ){
                switch ( i ){
                    case 1:
                        printf( "%13s | %6s\n", "char", "1 Byte" );
                        break;
                    case 2:
                        printf( "%13s | %6s\n", "short int", "2 Byte" );
                        break;
                    case 3:
                        printf( "%13s | %6s\n", "int", "4 Byte" );
                        break;
                    case 4:
                        printf( "%13s | %6s\n", "long int", "4 Byte" );
                        break;
                    case 5:
                        printf( "%13s | %6s\n", "long long int", "8 Byte" );
                        break;
                    case 6:
                        printf( "%13s | %6s\n", "char *", "4 Byte" );
                        break;
                    case 7:
                        printf( "%13s | %6s\n", "float", "4 Byte" );
                        break;
                    case 8:
                        printf( "%13s | %6s\n", "double", "8 Byte"  );
                        break;
                }
            }
        } else if ( strcmp( argv[ 1 ], "-c" ) == 0 || ( strcmp( argv[ 1 ], "--calc" ) == 0 ) ){
            int tx = 0;
            int ti = 0; 

            if ( strcmp( argv[ 2 ], "-i" ) == 0 || ( strcmp( argv[ 2 ], "--int" ) == 0 ) ){
                ti = 1;
            }

            if ( ( strcmp( argv[ 3 ], "-x" ) == 0 || ( strcmp( argv[ 3 ], "--hex" ) == 0 ) ) && ti == 1 ){
                tx = 1;
            }

            double x = atof( argv[ argc - 3 ] );
            double y = atof( argv[ argc - 1 ] );

            int xi = atoi( argv[ argc - 3 ] );
            int yi = atoi( argv[ argc - 1 ] );

            if ( strcmp( argv[ argc - 2 ], "+" ) == 0 ){ 
                if ( ti && !tx ) {
                    printf( "%d %s %d = %d", xi, argv[ argc - 2 ], yi, xi + yi );
                } else if ( tx ){
                    printf( "%d %s %d = %X", xi, argv[ argc - 2 ], yi, xi + yi );
                } else
                    printf( "%f %s %f = %f", x, argv[ argc - 2 ], y, x + y );
            } else if ( strcmp( argv[ argc - 2 ], "+" ) == 0 ){ 
                if ( ti && !tx ) {
                    printf( "%d %s %d = %d", xi, argv[ argc - 2 ], yi, xi - yi );
                } else if ( tx ){
                    printf( "%d %s %d = %X", xi, argv[ argc - 2 ], yi, xi - yi );
                } else
                    printf( "%f %s %f = %f", x, argv[ argc - 2 ], y, x - y );
            } else if ( strcmp( argv[ argc - 2 ], "*" ) == 0 ){ 
                puts( "a" );
                if ( ti && !tx ) {
                    printf( "%d %s %d = %d", xi, argv[ argc - 2 ], yi, xi * yi );
                } else if ( tx ){
                    printf( "%d %s %d = %X", xi, argv[ argc - 2 ], yi, xi * yi );
                } else
                    printf( "%f %s %f = %f", x, argv[ argc - 2 ], y, x * y );
            } else if ( strcmp( argv[ argc - 2 ], "/" ) == 0 ){ 
                if ( yi == 0 || y == 0 ) {
                    puts( "На ноль делить нельзя" );
                    return 0;
                }

                if ( ti && !tx ) {
                    printf( "%d %s %d = %d", xi, argv[ argc - 2 ], yi, xi / yi );
                } else if ( tx ){
                    printf( "%d %s %d = %X", xi, argv[ argc - 2 ], yi, xi / yi );
                } else
                    printf( "%f %s %f = %f", x, argv[ argc - 2 ], y, x / y );
            }
        }
    }

    puts( "" ); // процентик в терминале ??

    return 0;
}  