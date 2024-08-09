#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Para la funci�n sleep

// Funci�n que ser� ejecutada por el primer hilo
void* hilo1_funcion(void* arg) {
    sem_t *semaforos = (sem_t *)arg;
    sem_t *semaforo1 = &semaforos[0];
    sem_t *semaforo2 = &semaforos[1];

    for (int i = 0; i < 5; i++) {
        sem_wait(semaforo1); // Esperar a que el sem�foro 1 est� disponible

        // Secci�n cr�tica del primer hilo
        printf("Hilo 1 ejecutando iteraci�n %d\n", i);
        sleep(1); // Simula alg�n trabajo

        sem_post(semaforo2); // Se�alar al sem�foro 2 que puede continuar
    }
    return NULL;
}

// Funci�n que ser� ejecutada por el segundo hilo
void* hilo2_funcion(void* arg) {
    sem_t *semaforos = (sem_t *)arg;
    sem_t *semaforo1 = &semaforos[0];
    sem_t *semaforo2 = &semaforos[1];

    for (int i = 0; i < 5; i++) {
        sem_wait(semaforo2); // Esperar a que el sem�foro 2 est� disponible

        // Secci�n cr�tica del segundo hilo
        printf("Hilo 2 ejecutando iteraci�n %d\n", i);
        sleep(1); // Simula alg�n trabajo

        sem_post(semaforo1); // Se�alar al sem�foro 1 que puede continuar
    }
    return NULL;
}

int main() {
    pthread_t hilo1, hilo2;
    sem_t semaforos[2];

    // Inicializar los sem�foros
    if (sem_init(&semaforos[0], 0, 1) != 0 || sem_init(&semaforos[1], 0, 0) != 0) {
        perror("Error al inicializar los sem�foros");
        exit(EXIT_FAILURE);
    }

    // Crear los hilos
    if (pthread_create(&hilo1, NULL, hilo1_funcion, (void *)semaforos) != 0 ||
        pthread_create(&hilo2, NULL, hilo2_funcion, (void *)semaforos) != 0) {
        perror("Error al crear los hilos");
        exit(EXIT_FAILURE);
    }

    // Esperar a que los hilos terminen
    if (pthread_join(hilo1, NULL) != 0 || pthread_join(hilo2, NULL) != 0) {
        perror("Error al unir los hilos");
        exit(EXIT_FAILURE);
    }

    // Destruir los sem�foros
    if (sem_destroy(&semaforos[0]) != 0 || sem_destroy(&semaforos[1]) != 0) {
        perror("Error al destruir los sem�foros");
        exit(EXIT_FAILURE);
    }

    return 0;
}
