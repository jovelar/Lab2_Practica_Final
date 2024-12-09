#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

#define MAX_ITERACIONES 7 //Limite de bucles

//**********************************************************
//
// 3 hilos comparten un mismo semaforo
//
//**********************************************************

sem_t semaforo;

void  *programa1();
void  *programa2();
void  *programa3();

int main()
{
    pthread_t hilo1;
    pthread_t hilo2;
    pthread_t hilo3;

    sem_init(&semaforo,0,1); //Inicializar el semaforo

    pthread_create(&hilo1,0,&programa1,0);
    pthread_create(&hilo2,0,&programa2,0);
    pthread_create(&hilo3,0,&programa3,0);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);
    pthread_join(hilo3,NULL);

    sem_destroy(&semaforo); //Destruye el semaforo y libera recursos.
    return 0;
}

void *programa1()
{
    sem_wait(&semaforo);
    int contador=0;
    while(contador<MAX_ITERACIONES)
    {
        printf("Ejecutando programa 1, %i\n",contador);
        contador++;
    }
    sem_post(&semaforo);
}

void *programa2()
{
    sem_wait(&semaforo);
    int contador=0;
    while(contador<MAX_ITERACIONES)
    {
        printf("Ejecutando programa 2, %i\n",contador);
        contador++;
    }
    sem_post(&semaforo);
}

void *programa3()
{
    sem_wait(&semaforo);
    int contador=0;
    while(contador<MAX_ITERACIONES)
    {
        printf("Ejecutando programa 3, %i\n",contador);
        contador++;
    }
    sem_post(&semaforo);
}
