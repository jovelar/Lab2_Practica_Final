#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Para la función sleep

sem_t semaforo1,semaforo2,semaforo3;

void funcion1()
{
    sem_wait(&semaforo1);
    printf("Ejecutando F1 \n");
    sem_post(&semaforo2);
    sleep(1500);
    pthread_exit(0);
}

void funcion2()
{
    sem_wait(&semaforo2);
    printf("Ejecutando F2 \n");
    sem_post(&semaforo3);
    sleep(1500);
    pthread_exit(0);
}

void funcion3()
{
    sem_wait(&semaforo3);
    printf("Ejecutando F3 \n");
    sem_post(&semaforo1);
    sleep(1500);

    pthread_exit(0);
}

int main()
{
    pthread_t hilo1,hilo2,hilo3; // Crea los manejadores de los hilos

    sem_init(&semaforo1,0,1); //Inicializa los 3 semaforos
    sem_init(&semaforo2,0,0);
    sem_init(&semaforo3,0,0);

    pthread_create(&hilo1,NULL,&funcion1,0);
    pthread_create(&hilo2,NULL,&funcion2,0);
    pthread_create(&hilo3,NULL,&funcion3,0);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);
    pthread_join(hilo3,NULL);


    sem_destroy(&semaforo1);
    sem_destroy(&semaforo2);
    sem_destroy(&semaforo3);
    return 0;
}
