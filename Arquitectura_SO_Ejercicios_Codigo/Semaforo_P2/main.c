#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Para la función sleep

sem_t semaforo1,semaforo2,semaforo3; //Semaforos globales

void funcion1()
{
    sem_wait(&semaforo1);      //Ingrese a SC y bloquea semaforo 1
    printf("Ejecutando F1 \n");
    sem_post(&semaforo2);      //Sale de SC y desbloquea semaforo 2
    sleep(3);
    printf("Saliendo de F1 \n");
    pthread_exit(NULL);
}

void funcion2()
{
    sem_wait(&semaforo2);       //Ingrese a SC y bloquea semaforo 2
    printf("Ejecutando F2 \n");
    sem_post(&semaforo3);       //Sale de SC y habilita el semaforo 3
    sleep(3);
    printf("Saliendo de F2 \n");
    pthread_exit(NULL);
}

void funcion3()
{
    sem_wait(&semaforo3);       //Ingrese a SC y bloquea semaforo 3
    printf("Ejecutando F3 \n");
    sem_post(&semaforo1);       //Sale de SC y habilita el semaforo 1
    sleep(3);
    printf("Saliendo de F3 \n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t hilo1,hilo2,hilo3;            //Crea los identificadores de los hilos

    sem_init(&semaforo1,0,1);               //Inicializa los 3 semaforos S1=1 Habilitado, Comienza en S1
    sem_init(&semaforo2,0,0);               //                           S2=0 Bloqueado
    sem_init(&semaforo3,0,0);               //                           S3=0 Bloqueadi

    pthread_create(&hilo1,NULL,&funcion1,0); //Crea los hilos
    pthread_create(&hilo2,NULL,&funcion2,0);
    pthread_create(&hilo3,NULL,&funcion3,0);

    pthread_join(hilo1,NULL);               //Sincroniza los hilos con el hilo principal
    pthread_join(hilo2,NULL);               //y esperan a que terminen antes de continuar
    pthread_join(hilo3,NULL);


    sem_destroy(&semaforo1);                //Elimina los semaforos
    sem_destroy(&semaforo2);
    sem_destroy(&semaforo3);
    return 0;
}
