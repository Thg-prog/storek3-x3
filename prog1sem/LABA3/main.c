#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define philosoph_count 5

//Костыли не спят!
pthread_mutex_t kostyl = PTHREAD_MUTEX_INITIALIZER;

typedef struct get_put_fork{
    pthread_mutex_t forks[philosoph_count];
} get_put_fork;

typedef struct philosopger{
    int philosopherNUM;
    int left_fork;
    int right_fork;
    int tihnk_time;
    int eat_time;
} philosoph;

typedef struct philosophers_sitting{
    philosoph *philosophers;
    get_put_fork *fork;
} philosophers_sitting;

void mutex_creater(get_put_fork *fork)
{
    for(int i = 0; i < philosoph_count; i++)
    {
        pthread_mutex_init(&fork->forks[i], NULL);
    }
}

void* philosophers_eating(void *args)
{
    philosophers_sitting *philosophersSitting = args;
    philosoph *philosoph = philosophersSitting->philosophers;
    get_put_fork *forks = philosophersSitting->fork;
    while(TRUE) {
        //printf("Philosop nomer %i nachal est'\n", philosoph->philosopherNUM);
        pthread_mutex_lock(&kostyl);
        pthread_mutex_lock(&forks->forks[philosoph->left_fork]);
        pthread_mutex_lock(&forks->forks[philosoph->right_fork]);
        pthread_mutex_unlock(&kostyl);
        Sleep(philosoph->eat_time);
        pthread_mutex_unlock(&forks->forks[philosoph->right_fork]);
        pthread_mutex_unlock(&forks->forks[philosoph->left_fork]);
        printf("Philosop nomer %i poel\n", philosoph->philosopherNUM);
        Sleep(philosoph->tihnk_time);
    }
}

int main() {
    int philosoph_sleep[philosoph_count] = {200,2000,3000,100,1};
    int philosoph_eat[philosoph_count] = {100,400,300,4000,500};
    pthread_t thread[philosoph_count];
    philosoph philosoph[philosoph_count];
    philosophers_sitting philosophersSitting[philosoph_count];
    get_put_fork fork;
    mutex_creater(&fork);
    for(int i = 0; i < philosoph_count; i++)
    {   int right_fork = 0;
        if(i == 4){
            right_fork = 0;
        }else{
            right_fork = i + 1;
        }
        philosoph[i].left_fork=i;
        philosoph[i].right_fork = right_fork;
        philosoph[i].philosopherNUM = i + 1;
        philosoph[i].eat_time = philosoph_eat[i];
        philosoph[i].tihnk_time = philosoph_sleep[i];
        philosophersSitting[i].philosophers = &philosoph[i];
        philosophersSitting[i].fork = &fork;
    }
    for(int i = 0; i < philosoph_count; i++)
    {
        pthread_create(&thread[i], NULL, philosophers_eating, &philosophersSitting[i]);
    }
    for(int i = 0; i < philosoph_count; i++)
    {
        pthread_join(thread[i], NULL);
    }
}