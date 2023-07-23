#include "Lista_doble.h"
#include <stdlib.h>
#include <stdio.h>
Nodo2 *inicLista()
{
    return NULL;
}

Nodo2 *crearNodo(int dato)
{
    Nodo2 *aux=(Nodo2*)malloc(sizeof(Nodo2));
    aux->dato=dato;
    aux->anterior=NULL;
    aux->siguiente=NULL;
    return aux;
}

Nodo2 *agregarAlPio(Nodo2 *lista, Nodo2 *nuevoNodo)
{
    nuevoNodo->siguiente=lista;

    if(lista!=NULL)
    {
        lista->anterior=nuevoNodo;
    }
    return nuevoNodo;
}

Nodo2 *agregarAlFinal(Nodo2 *lista, Nodo2 *nuevoNodo)
{
    Nodo2 *ultimo=NULL;
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        ultimo=buscarUltimo(lista);
        ultimo->siguiente=nuevoNodo;
        nuevoNodo->anterior=ultimo;
    }
    return lista;
}

Nodo2 *buscarUltimo(Nodo2 *lista)
{
    Nodo2 *auxiliar=lista;
    if(lista!=NULL)
    {
        while(auxiliar->siguiente!=NULL)
        {
            auxiliar=auxiliar->siguiente;
        }
    }
    return auxiliar;
}

Nodo2 *insertarNodo(Nodo2 *lista, Nodo2 *nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if(nuevoNodo->dato<lista->dato)
        {
            lista=agregarAlPio(lista,nuevoNodo);
        }
        else
        {
            Nodo2 *seg=lista->siguiente;
            Nodo2 *ante=lista;
            while(seg!=NULL && nuevoNodo->dato>seg->dato)
            {
                ante=seg;
                seg=seg->siguiente;
            }
            ante->siguiente=nuevoNodo;
            nuevoNodo->anterior=ante;
            nuevoNodo->siguiente=seg;
            if(seg!=NULL)
            {
                seg->anterior=nuevoNodo;
            }
        }

    }
    return lista;
}

Nodo2 *borrarNodoDoble(Nodo2 *lista, int dato)
{
    if(lista!=NULL)
    {
        Nodo2 *anterior=lista;
        Nodo2 *auxiliar=lista;
        Nodo2 *proximo;

        while(auxiliar!=NULL)
        {
            if(lista->dato==dato)
            {
                anterior->siguiente=auxiliar->siguiente;
                proximo=auxiliar->siguiente;
                proximo->anterior=anterior;
                free(auxiliar);
            }
            anterior=auxiliar;
            auxiliar=auxiliar->siguiente;
        }
    }
    else
    {
        printf("La lista esta vacia! \n");
    }
}
