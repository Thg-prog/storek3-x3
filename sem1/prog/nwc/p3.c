#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#ifdef WIN32
    #include <Windows.h>
    #define Sleep(X) Sleep(X)
#else
    #include <unistd.h>
    #define Sleep(X) sleep(X)
#endif

#define FS 5
pthread_mutex_t mutex;

typedef struct fsdata {
    int id;
    int time_eat;
    int time_think;
    pthread_mutex_t* forks;
} fsdata;
 
void *thfunc( void* id ){
    fsdata* phi = ( fsdata* ) id;
    
    int err;
    int task_no;

    pthread_mutex_t* forks = phi->forks;
    int teat = phi->time_eat;
    int tthink = phi->time_think;
    
    int p_left = phi->id;
    int p_right = (phi->id+1)%FS;

    //printf( "Философ №%i; Левая - %i; Правая - %i\n", phi->id, p_left, p_right );

    do {        
        pthread_mutex_lock( &forks[ p_left ] );
        pthread_mutex_lock( &forks[ p_right ] );
        
        printf( "%i -- started\n", p_left );
        
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

        printf( "%i finished\n", p_left );

        pthread_mutex_unlock( &forks[ p_right ] );
        pthread_mutex_unlock( &forks[ p_left ] );

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
    fsdata* edata = ( fsdata* )malloc( FS * sizeof( fsdata ) );

    pthread_mutex_t forks_table[ FS ];

    int err;

    for ( int i = 0; i < FS; i++ ) {
        pthread_mutex_init( &forks_table[ i ], NULL );
    }

    for ( int i = 0; i < FS; i++ ){
        edata[ i ].id = i;
        edata[ i ].forks = forks_table;//?
        edata[ i ].time_eat = rand()%6;
        edata[ i ].time_think = rand()%7;
    }

    for ( int i = 0; i < FS; i++ )
        err = pthread_create( &threads[ i ], NULL, thfunc, &edata[ i ] );

    for ( int i = 0; i < FS; i++ )
        err = pthread_join( threads[ i ], NULL );

    pthread_mutex_destroy( &mutex );

    free( edata );
    free( threads );
    

    return 0;
}  