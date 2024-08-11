#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int x;

sem_t semA,semB;

void funcionA()
{
    sem_wait(&semA);
    x=199;
    x=x+1;
    printf("%i\n",x);
    sem_post(&semB);
    pthread_exit(NULL);
}

void funcionB()
{
    sem_wait(&semB);
    x=500;
    x=x/10;
    printf("%i\n",x);
    sem_post(&semA);
    pthread_exit(NULL);
}

void puntoA()
{
    pthread_t hiloA,hiloB;
    sem_init(&semA,0,1);
    sem_init(&semB,0,0);
    pthread_create(&hiloA,NULL,&funcionA,NULL);
    pthread_create(&hiloB,NULL,&funcionB,NULL);

    pthread_join(hiloA,NULL);
    pthread_join(hiloB,NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
}

void puntoB()
{
    pthread_t hiloA,hiloB;
    sem_init(&semA,0,0);
    sem_init(&semB,0,1);
    pthread_create(&hiloA,NULL,&funcionA,NULL);
    pthread_create(&hiloB,NULL,&funcionB,NULL);

    pthread_join(hiloA,NULL);
    pthread_join(hiloB,NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
}

int main()
{
    puntoA();
    puntoB();
    return 0;
}
