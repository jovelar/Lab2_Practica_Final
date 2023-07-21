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
    printf("|TOPE");
    while(aux!=NULL)
    {
        printf(" %i |",pila->valor);
        aux=aux->anterior;
    }

}
void borrarPila(Pila *pila)
{
    Pila *aux;
    while(aux!=NULL);
    {
        aux=pila;
        pila=pila->anterior;
        free(aux);
    }
    free(pila);
}

Pila *borrarMenoresAX(Pila *pila, int numeroLimite)
{
    Pila *anterior;
    Pila *aux=pila;
    Pila *original=pila;
    while(aux!=NULL)
    {
        if(pila->valor<numeroLimite)
        {
            anterior=aux;
            if(pila->valor==tope(pila))
            {
                anterior=aux;
                aux=aux->anterior;
                original=aux;
                free(anterior);
            }
            else
            {
                anterior->anterior=aux->anterior;
                free(aux);
                aux=anterior->anterior;
            }
        }
        aux=aux->anterior;
    }
    return original;
}
