#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define PHILOSOPHERS_COUNT 5


typedef struct philosopher {
    int number;
    int time1;
    int time2;
    int time3;
} philosopher;


pthread_mutex_t wait = PTHREAD_MUTEX_INITIALIZER; // для того чтобы никто больше не смог брать вилки
pthread_mutex_t forks[PHILOSOPHERS_COUNT];


void* thread_func(void* argv) {
    philosopher* phil = (philosopher*)argv;
    while(1) {
        printf("Philosopher %d is thinking\n", phil->number);
        Sleep(phil->time1);
        pthread_mutex_lock(&wait);
        //взял вилки
        pthread_mutex_lock(&forks[phil->number-1]);
        pthread_mutex_lock(&forks[(phil->number)%PHILOSOPHERS_COUNT]);
        pthread_mutex_unlock(&wait);
        printf("Philosopher %d is eating\n", phil->number);
        Sleep(phil->time2);
        //положил вилки
        pthread_mutex_unlock(&forks[phil->number-1]);
        pthread_mutex_unlock(&forks[(phil->number)%PHILOSOPHERS_COUNT]);
        printf("Philosopher %d stopped eating\n", phil->number);
        Sleep(phil->time3);
    }
}


int main(void) {
    philosopher first = {1, 1000, 1000, 1000};
    philosopher second = {2, 1000, 1000, 1000};
    philosopher third = {3, 1000, 1000, 1000};
    philosopher fourth = {4, 1000, 1000, 1000};
    philosopher fifth = {5, 1000, 1000, 1000};

    philosopher philosophers[] = {first, second, third, fourth, fifth};

    pthread_t threads[PHILOSOPHERS_COUNT];
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_create(&threads[i], NULL, thread_func, &philosophers[i]);
    }
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&wait);
    return 0;
}
