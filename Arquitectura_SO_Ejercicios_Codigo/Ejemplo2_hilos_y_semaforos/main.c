#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo1;
sem_t semaforo2;
sem_t semaforo3;

void *proceso1();
void *proceso2();
void *proceso3();

void funcion123(int numero);
void funcion321(int numero);
void funcion132(int numero);

int main()
{
    return 0;
}


void *proceso1(void *numero)
{
    int valor=*(int*)numero;
    sem_wait(&semaforo1);
    while(valor<110)
    {
        valor=valor*3;
        valor=valor-10;
    }
    sem_post(&semaforo1);
}

void *proceso2(void *numero)
{
    sem_wait(&semaforo2);
    int valor=*(int*)numero;
    while(valor<110)
    {
        valor=valor/2;
        valor=valor*4;
    }
    sem_post(&semaforo2);
}

void *proceso3(void *numero)
{
    sem_wait(&semaforo3);
    int valor=*(int*)numero;
    while(valor<110)
    {
        valor=valor-(valor/2);
        valor=valor*3;
    }
    sem_post(&semaforo3);
}

void funcion123(int numero)
{
    pthread_t proc1,proc2,proc3;
    sem_init(&semaforo1,0,1);
    sem_init(&semaforo2,0,0);
    sem_init(&semaforo3,0,0);

    pthread_create(&proc1,NULL,&proceso1,&numero);
    pthread_create(&proc2,NULL,&proceso2,&numero);
    pthread_create(&proc3,NULL,&proceso3,&numero);

    pthread_join(proc1,NULL);
    pthread_join(proc2,NULL);
    pthread_join(proc3,NULL);

    sem_destroy(&semaforo1);
    sem_destroy(&semaforo2);
    sem_destroy(&semaforo3);
}
void funcion321(int numero)
{
    pthread_t proc1,proc2,proc3;
    sem_init(&semaforo1,0,0);
    sem_init(&semaforo2,0,0);
    sem_init(&semaforo3,0,1);

    pthread_create(&proc1,NULL,&proceso1,&numero);
    pthread_create(&proc2,NULL,&proceso2,&numero);
    pthread_create(&proc3,NULL,&proceso3,&numero);

    pthread_join(proc1,NULL);
    pthread_join(proc2,NULL);
    pthread_join(proc3,NULL);

    sem_destroy(&semaforo1);
    sem_destroy(&semaforo2);
    sem_destroy(&semaforo3);
}
void funcion132(int numero)
{

}
