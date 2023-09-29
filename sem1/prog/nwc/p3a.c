#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

#define FS 5
pthread_mutex_t mutex;

typedef struct fsdata {
    int id;
    pthread_mutex_t* forks;
    int* forks_is_locked;
} fsdata;

void *consoleprint( void* tab ){
	int* forks = ( int* ) tab;

	while ( 1 ){
		sleep( 0.1 );
		system( "clear" );
		printf( "Laboratory #3 - Philosophers\n\n" );
		for ( int i = 0; i<FS; i++ ){
			if ( forks[ i ] == 1 ){
				printf( "Philosopher [ %i ] is eating\n", i );
			} else {
				printf( "Philosopher [ %i ] is thinking\n", i );
			}
		}
	}
}

void *thfunc( void* id ){
    fsdata* phi = ( fsdata* ) id;

    int err;
    int task_no;

    pthread_mutex_t* forks = phi->forks;
    int* locked = phi->forks_is_locked;


    int p_left = phi->id;
    int p_right = (phi->id+1)%FS;

    do {
    	//pthread_mutex_lock( &mutex );
        pthread_mutex_lock( &forks[ p_left ] );
        pthread_mutex_lock( &forks[ p_right ] );

        locked[ p_left ] = 1;
        
        if ( p_left == 0 ){
            sleep( 3 );
        } else if ( p_left == 1 ){
            sleep( 2 );
        } else if ( p_left == 2 ){
            sleep( 7 );
        } else if ( p_left == 3 ){
            sleep( 3 );
        } else if ( p_left == 4 ){
            sleep( 4 );
        }

		//pthread_mutex_unlock( &mutex );
        pthread_mutex_unlock( &forks[ p_right ] );
        pthread_mutex_unlock( &forks[ p_left ] );

        locked[ p_left ] = 0;

        if ( p_left == 0 ){
            sleep( 1 );
        } else if ( p_left == 1 ){
            sleep( 3 );
        } else if ( p_left == 2 ){
            sleep( 2 );
        } else if ( p_left == 3 ){
            sleep( 4 );
        } else if ( p_left == 4 ){
            sleep( 6 );
        }
    } while( 1 );

    return 0;
}

int main( int argc, char *argv[] ) {
    pthread_t* threads = ( pthread_t* )malloc( FS * sizeof( pthread_t ) );
    pthread_t printcon;
    fsdata* edata = ( fsdata* )malloc( FS * sizeof( fsdata ) );

	int forks_is_locked[ FS ] = { 0, 0, 0, 0, 0 };
    pthread_mutex_t forks_table[ FS ];
    pthread_mutex_t printc;

    int err;

    for ( int i = 0; i < FS; i++ ) {
        pthread_mutex_init( &forks_table[ i ], NULL );
    }

    pthread_mutex_init( &printc, NULL );

    for ( int i = 0; i < FS; i++ ){
        edata[ i ].id = i;
        edata[ i ].forks = forks_table;
        edata[ i ].forks_is_locked = forks_is_locked;
    }

    for ( int i = 0; i < FS; i++ )
       	pthread_create( &threads[ i ], NULL, thfunc, &edata[ i ] );

	pthread_create( &printcon, NULL, consoleprint, &forks_is_locked );

    for ( int i = 0; i < FS; i++ )
        pthread_join( threads[ i ], NULL );

    pthread_join( printcon, NULL );

    pthread_mutex_destroy( &mutex );

    free( edata );
    free( threads );


    return 0;
}
