#include "Fila.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void inicFila(Fila *fila)
{
    fila->primero=NULL;
    fila->ultimo=NULL;
}

void encolar(Fila *fila, nodo2 *nuevo)
{
    if(!fila->primero)
    {
        fila->primero=nuevo;
        fila->ultimo=nuevo;
    }
    else
    {
        fila->ultimo=agregarAlFinal(fila->ultimo,nuevo);
    }
}

nodo2 *desencolar(Fila *fila)
{
    nodo2 *aux=fila->primero;
    fila->primero=aux->sig; //usa el puntero auxiliar para avanzar
    if(!fila->primero)
    {
        fila->ultimo=fila->primero;
    }
    return aux;
}
void mostrarFila(Fila *fila);
void mostrarPrimero(Fila *fila);

nodo2 *crearNodo2(char palabra[30],int numero)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    strcpy(nuevo->palabra,palabra);
    nuevo->numero=numero;
    nuevo->ante=NULL;
    nuevo->sig=NULL;

    return nuevo;
}

nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo2 *iterador=lista;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
        nuevo->ante=iterador;
    }
    return lista;
}

nodo2 *borrarPrimero(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *aux=lista;
        lista=lista->sig;
        if(lista)
        {
            lista->ante=NULL;
        }
        free(aux);
    }
    return lista;
}
void mostrar(nodo2 *nodo)
{
    if(nodo)
    {
        printf(" %s %i \n",nodo->palabra,nodo->numero);
    }
}


void mostrarFila(Fila *fila)
{
    if(fila->primero)
    {
        nodo2 *iterador=fila->primero;
        while(iterador)
        {
            mostrar(iterador);
            iterador=iterador->sig;
        }
    }
}

void mostrarPrimero(Fila *fila)
{
    if(fila->primero)
    {
        mostrar(fila->primero);
    }
}
