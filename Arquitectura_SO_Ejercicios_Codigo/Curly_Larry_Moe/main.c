#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAXIT 6 //PARA EVITAR QUE ITERE DE FORMA INFINITA Y SE PUEDAN APRECIAR RESULTADOS ORDENADOS DESDE EL PRINCIPIO

sem_t semCurly, semLarry, semMoe;


void curly()
{
    int a=0;
    while(a < MAXIT)
    {
        sem_wait(&semCurly);
        int x=99;
        x=x+1;
        printf("%i\n",x);
        sem_post(&semMoe);
        a++;
    }
    pthread_exit(NULL);
}

void larry()
{
    int a=0;
    while(a < MAXIT)
    {
        sem_wait(&semLarry);
        int x=400;
        x=400/2;
        printf("%i\n",x);
        sem_post(&semCurly);
        a++;
    }
    pthread_exit(NULL);
}

void moe()
{
    int a=0;
    while(a < MAXIT)
    {
        sem_wait(&semMoe);
        int x=150;
        x=150*2;
        printf("%i\n",x);
        sem_post(&semLarry);
        a++;
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t hiloCurly,hilolarry,hiloMoe;
    sem_init(&semCurly,0,0);
    sem_init(&semLarry,0,1);
    sem_init(&semMoe,0,0);

    pthread_create(&hiloCurly,NULL,&curly,NULL);
    pthread_create(&hilolarry,NULL,&larry,NULL);
    pthread_create(&hiloMoe,NULL,&moe,NULL);

    pthread_join(hiloCurly,NULL);
    pthread_join(hilolarry,NULL);
    pthread_join(hiloMoe,NULL);


    sem_destroy(&semCurly);
    sem_destroy(&semLarry);
    sem_destroy(&semMoe);

    return 0;
}
