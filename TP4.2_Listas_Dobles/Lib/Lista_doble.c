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
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        Nodo2 *aux;
        aux=buscarUltimo(lista);
        aux->siguiente=nuevoNodo;
        nuevoNodo->anterior=aux;
    }
    return lista;
}

Nodo2 *buscarUltimo(Nodo2 *lista)
{
    Nodo2 *auxiliar=auxiliar=lista;

        while(auxiliar->siguiente!=NULL)
        {
            auxiliar=auxiliar->siguiente;
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
            Nodo2 *ante=lista;
            Nodo2 *seg=lista->siguiente;
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
        Nodo2 *seg; //VARIABLE SEGUIDORA, ES COMO UNA AUXILIAR
        if(lista->dato==dato) //SI ENCUENTRA EL DATO EN EL PRIMER NODO
        {
            Nodo2 *aux=lista;
            lista=lista->siguiente;
            if(lista!=NULL)
            {
                lista->anterior=NULL;
            }
            free(aux);
        }
        else
        {
            seg=lista;
            while((seg!=NULL)&&(seg->dato!=dato))
            {
                seg=seg->siguiente;
            }
            if(seg!=NULL)
            {
                Nodo2 *ante=seg->anterior;
                ante->siguiente=seg->siguiente;
                if(seg->siguiente) //SI NO ESTA VACIO/SI HAY ALGO
                {
                    Nodo2 *siguiente=seg->siguiente;
                    siguiente->anterior=ante;
                }
                free(seg);
            }
        }
    }
    return lista;
}

int capicaRecursivoDoble(Nodo2 *seg, Nodo2 *rev,int resultado)
{
    if(seg!=rev)
    {
        if(seg->dato==rev->dato)
        {
            resultado=capicaRecursivoDoble(seg->siguiente,rev->anterior,resultado);
        }
        else
        {
            resultado=0;
        }
    }
    else
    {
        resultado=1;
    }
    return resultado;
}
