#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
void *codigo_funcionl(void *arg)
{
    sem_wait(&mutex);
    printf("Soy el hilo %d", pthread_self());
    //pthread_exit(0);
    sem_post(&mutex);
}


int main(void)
{
    pthread_t hiloA, hiloB, hiloc;
    sem_init (&mutex,0,1) ;

    pthread_create(&hiloA, NULL,codigo_funcionl,NULL);
    pthread_create(&hiloB, NULL,codigo_funcionl,NULL);
    pthread_create(&hiloc, NULL,codigo_funcionl,NULL);

    pthread_join(hiloA, NULL);
    pthread_join(hiloB, NULL);
    pthread_join(hiloc, NULL);
}
