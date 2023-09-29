#include <string.h>

#include "dictionary.c"

void keytodict( dictionary_t* A, size_t size, char* key, void* val, int type ) {
    keyvalue_t* new_key = keyvalue_create( size, key, val, type );
    dictionary_add( A, new_key );
}

int main( int argc, char *argv[] ) {
    dictionary_t* dict = dictionary_init(); // Словарь для примера использования.
    dictionary_t* acts = dictionary_init(); // Словарь для main.

    keytodict( acts, sizeof( char* )*2, "0", "Выйти", 3 );
    keytodict( acts, sizeof( char* )*4, "1", "Добавить элемент", 3 );
    keytodict( acts, sizeof( char* )*4, "2", "Убрать элемент", 3 );
    keytodict( acts, sizeof( char* )*5, "3", "Скопировать элемент", 3 );
    keytodict( acts, sizeof( char* )*4, "4", "Сравнить элементы", 3 );
    keytodict( acts, sizeof( char* )*4, "5", "Найти элемент", 3 );
    keytodict( acts, sizeof( char* )*4, "6", "Печатать элементы", 3 );

    int act;
    char* key;
    char* key2;

    int i_val;
    void* val;

    while ( 1 ){
        for ( int i = 0; i<acts->size; i++ ){
            printf( "%s - %s\n", acts->list[ i ].key, acts->list[ i ].value );
        }
        
        printf( "Введите операцию: " );
        scanf( "%i", &act );

        if ( act == 0 ){
            dictionary_remove( dict );
            break;
        } else if ( act == 1 ){
            int t;

            printf( "Введите [%i] ключ: ", dict->size );
            scanf( "%s", &key );

            printf( "0 - int\n1 - float\n2 - char\n3 - char*\nВведите тип: " );
            scanf( "%i", &t );

            printf( "Введите значение: " );

            if ( t == 0 ){
                scanf( "%i", &val );
                keytodict( dict, sizeof( int ), key, &val, t );
            } else if ( t == 1 ){
                scanf( "%f", &val );
                keytodict( dict, sizeof( float ), key, &val, t );
            } else if ( t == 2 ){
                scanf( "%c", &val );
                keytodict( dict, sizeof( char ), key, &val, t );
            } else {
                scanf( "%s", &val );
                keytodict( dict, sizeof( char* ), key, &val, t );
            }
        } else if ( act == 2 ){
            printf( "Введите индекс: " );
            scanf( "%i", &i_val );

            keyvalue_rem( dict, i_val );
        } else if ( act == 3 ){
            printf( "Введите [%i] ключ: ", dict->size );
            scanf( "%s", &key );

            keyvalue_t* key_1 = keyvalue_find( *dict, key );
            if ( key_1 != NULL ) {

                printf( "Введите ключ для копирования: " );
                scanf( "%s", &key2 );

                keyvalue_t* key_2 = keyvalue_create( sizeof( char* ), key2, &key_1->value, key_1->type );

                keyvalue_copy( key_1, key_2 );
                memcpy( key_2->key, &key2, sizeof( char* ) );
                dictionary_add( dict, key_2 );
            }
        } else if ( act == 4 ){
            printf( "Введите 1 ключ: " );
            scanf( "%s", &key );

            printf( "Введите 2 ключ: " );
            scanf( "%s", &key2 );

            //printf( "%i\n", keyvalue_compare( *dict, key, key2 ) );
        } else if ( act == 5 ){
            printf( "Введите [%i] ключ: ", dict->size );
            scanf( "%s", &key );

            printf( "%i\n", keyvalue_find( *dict, key ) );            
        } else if ( act == 6 ){
            dictionary_print( dict );
        }
    }
}