#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//ESTRUCTURA PARA PASAR PARAMETROS A LA FUNCION DEL HILO

typedef struct
{
    int limite;
    char letra;
}stParametros;

//LOS PARAMETROS SE TRANSFIEREN MEDIANTE UN PUNTERO VOID
void *funcionHilo(void* punteroParam)
{
    stParametros *parametros;
    parametros=(stParametros*)punteroParam; //SE CASTEA EL PUNTERO VOID A stPARAMETROS

    printf("ID del hilo %i\n",pthread_self()); //pthead_self() muestra el ID del hilo

    int *resultado=(int*)malloc(sizeof(int));   //resultado se almacena en heap, para que no se pierda al
                                                 //terminar la funcion.
    for(int z=0;z<parametros->limite;z++)
    {
        printf("HILO: %c VALOR: %i \n",parametros->letra,z);
        *resultado=z;
    }
    printf("Hilo %c finalizado!, saliendo \n",parametros->letra);

    pthread_exit((void*)resultado); //Si se necesitan devolver valores, se debe devolver como puntero generico (VOID *)
}

int main()
{
    pthread_t hilo1,hilo2,hilo3;  //MANEJADORES DE LOS HILOS

    //ESTRUCTURAS PARA PASAR PARAMETROS A funcionHilo()
    stParametros paramHilo1=(stParametros){10,'A'};
    stParametros paramHilo2=(stParametros){50,'B'};
    stParametros paramHilo3=(stParametros){30,'C'};

    //PTHREAD_CREATE DEVUELVE 0 SI SE CREARON CON EXITO
    int estadoHilo1,estadoHilo2,estadoHilo3;

    //PARAMTEROS DE PTHREAD_CREATE
    //&hilo, puntero del manejador del hilo
    //NULL, en el segundo parametro se definen caracteristicas del hilo, como prioridad,comportamiento, planificacion
    //dejandolo como NULL es la opcion por defecto
    //&funcionHilo(), puntero a la funcion que se va a ejecutar dentro del hilo
    //(void*)&paramHilo direccion de memoria (puntero tambien) del struct de parametros casteado a VOID
    estadoHilo1=pthread_create(&hilo1,NULL,&funcionHilo,(void*)&paramHilo1);
    estadoHilo2=pthread_create(&hilo2,NULL,&funcionHilo,(void*)&paramHilo2);
    estadoHilo3=pthread_create(&hilo3,NULL,&funcionHilo,(void*)&paramHilo3);

    void *resultadoHilo1,*resultadoHilo2,*resultadoHilo3;

    if((estadoHilo1 && estadoHilo2 && estadoHilo3) == 0) //SOLO EJECUTA SI SE CREAN LOS 3 HILOS CON EXITO
    {
        pthread_join(hilo1,&resultadoHilo1);  //hilo1= manejador del hilo
        pthread_join(hilo2,&resultadoHilo2);  //&resultadoHilo2, puntero donde se recibe el resultado de la funcion
        pthread_join(hilo3,&resultadoHilo3);  //dettro del hilo, es un puntero void doble void**

        printf("Resultado Hilo 1: %i \n",*(int*)resultadoHilo1); //Se castea el puntero void a (int*)y se desreferencia
        printf("Resultado Hilo 2: %i \n",*(int*)resultadoHilo2); //con * para acceder al que apunta el puntero
        printf("Resultado Hilo 3: %i \n",*(int*)resultadoHilo3);

        free(resultadoHilo1);
        free(resultadoHilo2);
        free(resultadoHilo3);
    }

    return 0;
}
