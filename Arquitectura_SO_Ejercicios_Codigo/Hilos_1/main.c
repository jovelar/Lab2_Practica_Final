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
void funcionHilo(void* punteroParam)
{
    stParametros *parametros;
    parametros=(stParametros*)punteroParam; //SE CASTEA EL PUNTERO VOID A stPARAMETROS

    printf("ID del hilo %i\n",pthread_self());
    for(int z=0;z<parametros->limite;z++)
    {
        printf("HILO: %c VALOR: %i \n",parametros->letra,z);
    }
    printf("Hilo %c finalizado!, saliendo \n",parametros->letra);
    //pthread_exit(NULL);
}

int main()
{
    pthread_t hilo1,hilo2,hilo3;  //MANEJADORES DE LOS HILOS

    //ESTRUCTURAS PARA PASAR PARAMETROS A funcionHilo()
    stParametros paramHilo1=(stParametros){45,'A'};
    stParametros paramHilo2=(stParametros){10,'B'};
    stParametros paramHilo3=(stParametros){999,'C'};

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

    if((estadoHilo1 && estadoHilo2 && estadoHilo3) == 0) //SOLO EJECUTA SI SE CREAN LOS 3 HILOS CON EXITO
    {
        pthread_join(hilo1,NULL);
        pthread_join(hilo2,NULL);
        pthread_join(hilo3,NULL);
    }

    return 0;
}
