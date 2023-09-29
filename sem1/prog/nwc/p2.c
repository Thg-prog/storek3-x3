#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
    Разработать программу для сбора статистики файла.
    Обрабатывать следующие флаги командной строки:
    a) -w (--word) выдать количество слов в заданном файле (разделители пробельные
символы)
    b) --en выдать таблицу которая содержит количество и частоту встреч латинских букв
        b1) -- ir – игнорировать регист букв (для флагов —en)
    d) --all (флаг по умолчанию) выдать таблицу которая содержит количество и частоту
встреч всех ASCII символов
    
*/

void printtaball( FILE *fi ){
    int tab[ 256 ] = { 0 };
    int lfreq[ 256 ] = { 0 };
    
    int x, lx, id;
    int freq = 1;

    while ( 1 ) {
        x = fgetc( fi );
        
        if( feof( fi ) ){
            break;
        }
  
        if ( x >= 0 && x <= 256 ){
            id = x;
            tab[ id ]++;

            if ( lx == id ){
                freq++;
            }

            if ( lfreq[ lx ] < freq ){
                lfreq[ lx ] = freq;
            } 
                
                
            if ( lx != id ){
                freq = 1;
            }     

            lx = id;
        }
    }

    printf( "| sym |  num  |  freq  |\n");
    for ( int i = 0; i < 256; i++ ){
        if ( tab[ i ] > 0 ){
            printf( "| %-6c|  %-5i | %-5i |\n", i, tab[ i ], lfreq[ i ] );
        }
    }
}

void printtablat( FILE *fi, int reg ){
    int tab[ 52 ] = { 0 };
    int lfreq[ 52 ] = { 0 };

    int x, lx, id;
    int freq = 1;

    while ( 1 ) {
        x = fgetc( fi );
        
        if( feof( fi ) ){
            break;
        }

        if ( x >= 65 && x <= 122 ){ // A( 65 - 90 ) a( 97 - 122 )
            id = ( reg == 1 )?( ( x >= 97 )?( x - 97 ):( x - 65 ) ):( ( x >= 97 )?( x - 97 ):( x - 65 + 26 ) );
            tab[ id ]++;

            if ( lx == id ){
                freq++;
            }

            if ( lfreq[ lx ] < freq ){
                lfreq[ lx ] = freq;
            } 
            
            
            if ( lx != id ){
                freq = 1;
            }       

            lx = id;
        }
    }

    printf( "| sym |  num  |  freq  |\n");
    for ( int i = 0; i < 52; i++ ){
        if ( tab[ i ] > 0 ){
            printf( "| %-4c|  %-5i | %-5i |\n", ( reg == 0 )?( ( i >= 26 )?( i + 65 - 26 ):( i + 97 ) ):( ( i >= 26 )?( i + 65 ):( i + 97 ) ), tab[ i ], lfreq[ i ] );
        }
    }
}

int getwords( FILE *fi ){
    int words = 0;
    int bch, ch;
    while ( ( ch = fgetc( fi ) ) != EOF ) {
        if ( ( ch != ' ' && ch != '\n' ) && ( bch == ' ' || bch == '\n' ) ){
            words++;
        }

        bch = ch;
    }

    if ( ch == EOF ) {
        words++;
    }

    return words;
}

void help( void ){
    printf( "Usage: lab2 [file] [params]\n\
-w [--word] показывает количество слов в файле\n\
--en [params] выдает таблицу с латинскими символами\n\
    --ir игнорирует регистр\n\n\
--all выводит таблицу со всеми ASCII символами в файле\n" );
}

int main( int argc, char *argv[] ) {  
    FILE *fi;
    fi = fopen( argv[ 1 ], "rt" );

    if ( fi == NULL )  {
        help();
        return -1;
    }

    if ( argc > 2 ) {
        if ( strcmp( argv[ 2 ], "-w" ) == 0 || strcmp( argv[ 2 ], "--word" ) == 0 ){
            printf( " Words: %i", getwords( fi ) );
        } else if ( strcmp( argv[ 2 ], "--en" ) == 0 ){
            printtablat( fi, ( argc > 3 && strcmp( argv[ 3 ], "--ir" ) == 0 )?1:0 );
        } else if ( strcmp( argv[ 2 ], "--all" ) == 0 ){
            printtaball( fi );
        } else {
            help();
            //return -1;
        }
    } else {
        help();
        //return -1;
    }

    fclose( fi );
    
    puts( "" ); // процентик в терминале ??

    return 0;
}  