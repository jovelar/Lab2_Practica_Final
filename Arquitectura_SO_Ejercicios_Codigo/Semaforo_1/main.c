#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaforo; // Declaración del semáforo

void* cambiar_luces(void* arg) {
    while (1) {
        printf("Luz verde\n");
        sleep(5); // Luz verde durante 5 segundos
        sem_post(&semaforo); // Señalar a los vehículos que pueden pasar

        printf("Luz amarilla\n");
        sleep(2); // Luz amarilla durante 2 segundos

        printf("Luz roja\n");
        sleep(5); // Luz roja durante 5 segundos
        sem_wait(&semaforo); // Los vehículos deben detenerse
    }
}

void* vehiculos(void* arg) {
    while (1) {
        sem_wait(&semaforo); // Esperar a la luz verde
        printf("Vehículo pasando\n");
        sleep(1); // Simular el paso del vehículo
        sem_post(&semaforo); // Permitir que otros vehículos pasen
    }
}

int main() {
    pthread_t hilo1, hilo2;

    // Inicialización del semáforo
    sem_init(&semaforo, 0, 0);

    // Creación de los hilos
    pthread_create(&hilo1, NULL, cambiar_luces, NULL);
    pthread_create(&hilo2, NULL, vehiculos, NULL);

    // Esperar a que los hilos terminen (en este caso, no terminarán)
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Destrucción del semáforo
    sem_destroy(&semaforo);

    return 0;
}
