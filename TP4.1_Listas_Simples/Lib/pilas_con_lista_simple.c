#include "pila_con_lista_simple.h"
int pilaVacia(Pila *pila)
{
    int estado=0;
    if(pila!=NULL)
    {
        estado=1;
    }
    return estado;
}
Pila *init()
{
    return NULL;
}
Pila *apilar(Pila *pila, int datoNuevo) //PUSH
{
    Pila *nuevo=(Pila*)malloc(sizeof(Pila));
    nuevo->valor=datoNuevo;
    if(pila==NULL)
    {
        nuevo->anterior=NULL;
        pila=nuevo;
    }
    else
    {
        nuevo->anterior=pila;
        pila=nuevo;
    }
    return pila;
}

Pila *desapilar(Pila *pila) //POP
{
    Pila *aRetirar;
    aRetirar=pila;
    pila=pila->anterior;
    return aRetirar;
}

int tope(Pila *pila)
{
    return pila->valor;
}

void mostrarPila(Pila *pila)
{
    Pila *aux=pila;
    printf("\n|TOPE|");
    while(aux!=NULL)
    {
        printf(" %i |",aux->valor);
        aux=aux->anterior;
    }
    printf("BASE|\n");
}
void borrarPila(Pila *pila)
{
    Pila *auxiliar=pila;
    Pila *eliminar;

    while(auxiliar!=NULL)
    {
        eliminar=auxiliar;
        auxiliar=auxiliar->anterior;
        free(eliminar);
    }
}

Pila *borrarMenoresAX(Pila *pila, int numeroLimite)
{
    Pila *eliminar;
    Pila *anterior=pila;
    Pila *auxiliar=pila;
    if(auxiliar->valor<numeroLimite) //SI EL ELEMENTO TOPE DE LA PILA ES MENOR A 10
    {
        eliminar=auxiliar;
        auxiliar=auxiliar->anterior;
        free(eliminar);
    }
    while(auxiliar!=NULL)
    {
        if(auxiliar->valor<=numeroLimite)
        {
            eliminar=auxiliar;       //INDICA EL NODO A ELIMINAR
            anterior->anterior=auxiliar->anterior; //VINCULA EL ANTERIOR CON EL
            free(eliminar);  //ELIMINA LA PILA     //SIGUIENTE DE LA PILA A ELIMINAR
            auxiliar=anterior; //VINCULA EL ANTERIOR COMO EL ULTIMO ELEMENTO DE LA PILA
        }
        anterior=auxiliar;
        auxiliar=auxiliar->anterior;
    }

    return pila;
}
