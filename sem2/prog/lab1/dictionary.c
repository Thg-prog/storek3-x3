#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

keyvalue_t* keyvalue_find( dictionary_t A, char* key ) {
    keyvalue_t* find_key;
    int find = 0;
    for ( int i = 0; i<A.i; i++ ){
        if ( !strcmp( A.list[ i ].key, key ) ){
            find_key = &A.list[ i ];
            find = 1;
            break;
        }
    }

    if ( find == 0 ){
        return NULL;
    } else { 
        return find_key;
    }
}

// Копирование элемента ( создание нового, который наследует значение старого )
// key_0: ключ для нового, key_1: ключ от старого
void keyvalue_copy( keyvalue_t* key_0, keyvalue_t* key_1 ) {
    key_1->size = key_0->size;
    key_1->type = key_0->type;
    
    free( key_1->value );
    key_1->value = malloc( key_0->size );
    memcpy( key_1->value, key_0->value, key_0->size );
    key_1->value = key_0->value;

    free( key_1->key );
    key_1->key = malloc( sizeof( char* ) );
    memcpy( key_1->key, key_0->key, sizeof( char* ) );
    key_1->key = key_0->key;
}

keyvalue_t* keyvalue_create( size_t size, char* key, void* val, int type ) {
    keyvalue_t* new_key;

    new_key = ( keyvalue_t* )malloc( sizeof( keyvalue_t ) );
    new_key->size = size;
    
    new_key->key = ( char* )malloc( sizeof( char* ) );
    new_key->value = malloc( size );

    memcpy( new_key->key, key, sizeof( char* ) );
    memcpy( new_key->value, val, size );

    new_key->type = type;

    return new_key;
}

// Удаляет keyvalue_t из dictionary_t
void keyvalue_rem( dictionary_t* A, int ind ) {
    if ( A->i >= 1 ){
        memmove( A->list+ind, A->list+1, A->size );
        A->i--;
        A->size -= sizeof( keyvalue_t );

        printf( "MEM! %i\n", A->size );
        keyvalue_t* list = A->list;
        A->list = realloc( list, A->size );
    }
}


void keyvalue_print( keyvalue_t a ) {
    printf( "%i\n", a.value );
}

// Сравнивает значения у двух keyvalue_t
int keyvalue_compare( keyvalue_t* k_a, keyvalue_t* k_b ) {
    int v;

    if ( k_a->type == 0 ){
        if ( k_a->value == k_b->value ){
            v = 0;
        } else if ( k_a->value > k_b->value ){
            v = 1;
        } else if ( k_a->value < k_b->value ){
            v = -1;
        }
    } else if ( k_a->type == 1 ){
        v = !strcmp( k_a->key, k_b->key );
    }

    return v;
}

// Выводит в консоль все keyvalue_t в dictionary_t
void dictionary_print( dictionary_t* A ) {
    printf( "{\n" );
    for ( int i = 0; i<A->i; i++ ){
        int type = A->list[ i ].type;

        if ( type == 0 ) {
            printf( "\t%s - %i\n", A->list[ i ].key, *( int* )A->list[ i ].value );
        } else if ( type == 1 ) {
            printf( "\t%s - %f\n", A->list[ i ].key, *( float* )A->list[ i ].value );
        } else if ( type == 2 ) {
            printf( "\t%s - %c\n", A->list[ i ].key, *( char* )A->list[ i ].value );
        } else if ( type == 3 ) {
            printf( "\t%s - %s\n", A->list[ i ].key, A->list[ i ].value );
        }
    }
    printf( "}\n" );
}

// Создает dictionary_t
dictionary_t* dictionary_init() {
    dictionary_t* dict;

    dict = ( dictionary_t* )malloc( sizeof( dictionary_t ) );
    dict->size = 0;
    dict->i = 0;

    return dict;
}

// Уничтожает dictionary_t
void dictionary_remove( dictionary_t* A ) {
    for ( int i = 0; i < A->i; i++ ){
        keyvalue_rem( A, i );
    }
    free( A->list );
}

// Добавляет keyvalue_t в dictionary_t с проверкой на уникальность ключа
void dictionary_add( dictionary_t* A, keyvalue_t* new_key ) {
    int can = 1;
    if ( A->i > 0 ){
        for ( int i = 0; i<A->i; i++ ){
            if ( !strcmp( A->list[ i ].key, new_key->key ) ) {
                can = 0;
            }
        }
    }

    if ( can != 0 ){
        if ( A->i >= 0 ){
            A->size += sizeof( keyvalue_t );
            printf( "MEMORY = %i\n", A->size );
            A->list = realloc( A->list, A->size );
        }

        A->list[ A->i ] = *new_key;
        A->i++;
    }
}