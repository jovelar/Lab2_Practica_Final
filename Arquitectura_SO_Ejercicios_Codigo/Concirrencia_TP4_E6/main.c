#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semA,semB,semC;

void procA()
{
    sem_wait(&semA);
    printf("Proceso A!\n");
    sem_post(&semC);
    pthread_exit(NULL);
}

void procB()
{
    sem_wait(&semB);
    printf("Proceso B!\n");
    sem_post(&semA);
    sem_post(&semA);
    pthread_exit(NULL);
}

void procC()
{
    sem_wait(&semB);
    sem_wait(&semC);
    printf("Proceso C!\n");
    sem_post(&semB);
    pthread_exit(NULL);
}

void finalizado()
{
    pthread_t hiloA,hiloB,hiloC;

    sem_init(&semA,0,0);
    sem_init(&semB,0,2);
    sem_init(&semC,0,0);

    pthread_create(&hiloA,NULL,&procA,NULL);
    pthread_create(&hiloB,NULL,&procB,NULL);
    pthread_create(&hiloC,NULL,&procC,NULL);

    pthread_join(hiloA,NULL);
    pthread_join(hiloB,NULL);
    pthread_join(hiloC,NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);

    printf("\n Fin de Finalizado!\n");

}

void interbloqueo()
{
    pthread_t hiloA,hiloB,hiloC;

    sem_init(&semA,0,0);
    sem_init(&semB,0,0);
    sem_init(&semC,0,2);

    pthread_create(&hiloA,NULL,&procA,NULL);
    pthread_create(&hiloB,NULL,&procB,NULL);
    pthread_create(&hiloC,NULL,&procC,NULL);

    pthread_join(hiloA,NULL);
    pthread_join(hiloB,NULL);
    pthread_join(hiloC,NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    printf("\n Fin de interbloqueo!\n"); //No llega nunca realmente
}

int main()
{
    finalizado();
    interbloqueo();
    return 0;
}
