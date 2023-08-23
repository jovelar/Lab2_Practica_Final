#include "PilaFila.h"
#include <stdio.h>

Pila *inicPila()
{
    return NULL;
}

int pilaVacia(Pila *pila)
{
    int vacia=0;
    if(pila==NULL)
    {
        vacia=1;
    }
    return vacia;
}

Pila *apilar(Pila *pila, int dato)
{
    Pila *nuevo=(Pila*)malloc(sizeof(Pila));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;

    if(pila==NULL)
    {
        pila=nuevo;
    }
    else
    {
        Pila *aux=pila;
        while(aux->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
    }
    return pila;
}

int tope(Pila *pila)
{
    return pila->dato;
}

Pila * leer(Pila *pila)
{
    int dato;
    printf("\nIngrese un numero entero para cargar a la pila: ");
    scanf("%d",&dato);
    pila=apilar(pila,dato);
    return pila;
}

int *desapilar(Pila *pila)
{
    int dato=0;
    if(pila!=NULL)
    {

        if(pila->siguiente==NULL) //SI ES EL UNICO NODO
        {
            int dato=pila->dato;
            free(pila);
            pila=NULL;
        }
        else
        {
            Pila *aux=pila;
            Pila *ante=aux;
            while(aux->siguiente!=NULL)
            {
                ante=aux;
                aux=aux->siguiente;
            }
            dato=aux->dato;
            free(aux);
            ante->siguiente=NULL;
        }
    }
    return dato;
}

void mostrarPila(Pila *pila)
{
    if(pila!=NULL)
    {
        Pila *temp=inicPila();
        Pila *aux=pila;

        while(aux!=NULL)
        {
            temp=apilar(temp,aux->dato);
            aux=aux->siguiente;
        }
        printf("\n=============\n");
        printf("\n==TOPE=======\n");
        printf("\n=============\n");
        while(temp!=NULL)
        {
            printf("%i\n",temp->dato);
            temp=temp->siguiente;
        }
        printf("\n=============\n");
        printf("\n==BASE=======\n");
        printf("\n=============\n");
    }
    else
    {
        printf("\nLa pila esta vacia!\n");
    }
}
