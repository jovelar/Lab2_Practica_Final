#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Para la función sleep

// Función que será ejecutada por el primer hilo
void* hilo1_funcion(void* arg) {
    sem_t *semaforos = (sem_t *)arg;
    sem_t *semaforo1 = &semaforos[0];
    sem_t *semaforo2 = &semaforos[1];

    for (int i = 0; i < 5; i++) {
        sem_wait(semaforo1); // Esperar a que el semáforo 1 esté disponible

        // Sección crítica del primer hilo
        printf("Hilo 1 ejecutando iteración %d\n", i);
        sleep(1); // Simula algún trabajo

        sem_post(semaforo2); // Señalar al semáforo 2 que puede continuar
    }
    return NULL;
}

// Función que será ejecutada por el segundo hilo
void* hilo2_funcion(void* arg) {
    sem_t *semaforos = (sem_t *)arg;
    sem_t *semaforo1 = &semaforos[0];
    sem_t *semaforo2 = &semaforos[1];

    for (int i = 0; i < 5; i++) {
        sem_wait(semaforo2); // Esperar a que el semáforo 2 esté disponible

        // Sección crítica del segundo hilo
        printf("Hilo 2 ejecutando iteración %d\n", i);
        sleep(1); // Simula algún trabajo

        sem_post(semaforo1); // Señalar al semáforo 1 que puede continuar
    }
    return NULL;
}

int main() {
    pthread_t hilo1, hilo2;
    sem_t semaforos[2];

    // Inicializar los semáforos
    if (sem_init(&semaforos[0], 0, 1) != 0 || sem_init(&semaforos[1], 0, 0) != 0) {
        perror("Error al inicializar los semáforos");
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

    // Destruir los semáforos
    if (sem_destroy(&semaforos[0]) != 0 || sem_destroy(&semaforos[1]) != 0) {
        perror("Error al destruir los semáforos");
        exit(EXIT_FAILURE);
    }

    return 0;
}
