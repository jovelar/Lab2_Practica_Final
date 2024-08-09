#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//ESTRUCTURA PARA PASAR PARAMETROS MULTIPLES A LA FUNCION DEL HILO

typedef struct
{
    int limite;
    char letra;
}stParametros;

void funcionHilo(stParametros *punteroParam)
{
    printf("ID del hilo %i\n",pthread_self()); //pthead_self() muestra el ID del hilo

    int *resultado=(int*)malloc(sizeof(int)); //para no perder el valor al finalizar
    for(int z=0;z<punteroParam->limite;z++)
    {
        printf("HILO: %c VALOR: %i \n",punteroParam->letra,z);
        *resultado=z;
    }
    printf("Hilo %c finalizado!, saliendo \n",punteroParam->letra);


    pthread_exit(resultado);
}

int main()
{
    pthread_t hilo1,hilo2,hilo3;  //MANEJADORES DE LOS HILOS

    //ESTRUCTURAS PARA PASAR PARAMETROS A funcionHilo()
    stParametros paramHilo1=(stParametros){10,'A'};
    stParametros paramHilo2=(stParametros){50,'B'};
    stParametros paramHilo3=(stParametros){30,'C'};


    int estadoHilo1,estadoHilo2,estadoHilo3;

    //PTHREAD_CREATE DEVUELVE 0 SI SE CREARON CON EXITO
    //PARAMTEROS DE PTHREAD_CREATE
    //&hilo, puntero del manejador del hilo
    //NULL, en el segundo parametro se definen caracteristicas del hilo, como prioridad,comportamiento, planificacion
    //dejandolo como NULL es la opcion por defecto
    //&funcionHilo(), puntero a la funcion que se va a ejecutar dentro del hilo
    //&paramHilo direccion de memoria (puntero tambien) del struct de parametros casteado a VOID

    estadoHilo1=pthread_create(&hilo1,NULL,&funcionHilo,&paramHilo1);
    estadoHilo2=pthread_create(&hilo2,NULL,&funcionHilo,&paramHilo2);
    estadoHilo3=pthread_create(&hilo3,NULL,&funcionHilo,&paramHilo3);

    int *resultado1,*resultado2,*resultado3; //punteros para acceder a el retorno de pthread_exit(). HEAP

    if((estadoHilo1 && estadoHilo2 && estadoHilo3) == 0) //SOLO EJECUTA SI SE CREAN LOS 3 HILOS CON EXITO
    {

        pthread_join(hilo1,&resultado1);  //hilo1= manejador del hilo, NULL= variable donde se almacene el valor de retorno de la funcion
        pthread_join(hilo2,&resultado2);  //que se va a ejecutar en el hilo, cuando no se requiere se indica NULL
        pthread_join(hilo3,&resultado3);
        printf("\n resultado 1: %i | resultado 2: %i | resultado 3: %i",*resultado1,*resultado2,*resultado3);
    }

    return 0;
}
