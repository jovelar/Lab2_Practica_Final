#include "PilaListaSimple.h"
#include <stdio.h>

Pila *inicPila()
{
    return NULL;
}

//DEVUELVE 1 O 0 SEGUN ESTE VACIA O NO
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

//PIDE UN DATO POR CONSOLA Y APILA
Pila * leer(Pila *pila)
{
    int dato;
    printf("\nIngrese un numero entero para cargar a la pila: ");
    scanf("%d",&dato);
    pila=apilar(pila,dato);
    return pila;
}

int desapilar(Pila **pila)
{
    //LO IDEAL SERIA ES QUE SE MANEJE CON PUNTEROS, ES DECIR, QUE LA FUNCION
    //DEVUELVA UN PUNTERO A UNA PILA "DATO", POR QUE DE ESTA MANERA SI NO HAY NINGUN
    //NODO EN LA PILA SE PUEDE DEVOLVER NULL, Y CON NULL SE PUEDE EVALUAR QUE NO HAY NADA.
    //AL FIGURAR INT EN LA FIRMA/CABECERA ESTAS OBLIGADO A DEVOLVER UN NUMERO SI O SI

    //AL INVOCAR ESTA FUNCION HAY QUE ANTEPONER ANPERSAND (&) DELANTE DEL PUNTERO A LA LISTA
    //      Pila *pila=NULL;
    //
    //EJ:   int dato=desapilar(&pila);
    //

    int dato=0;
    if((*pila)!=NULL)
    {

        if((*pila)->siguiente==NULL) //SI ES EL UNICO NODO
        {
            dato=(*pila)->dato;
            free(*pila);
            (*pila)=NULL;

        }
        else
        {
            Pila *aux=(*pila);
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
        Pila *aux=pila;
        Pila *pilaAux=NULL;

        //PRIMERO SE HACE UNA COPIA DEL ORIGINAL, DADO QUE AL
        //INVERTIR USANDO DESAPILAR SE VA A DESTRUIR

        while(aux!=NULL)
        {
            pilaAux=apilar(pilaAux,aux->dato);
            aux=aux->siguiente;
        }

        Pila *pilaAMostrar=NULL;

        //INVERTIMOS LA LISTA, DESTRUYENDO pilaAux

        while(pilaAux!=NULL)
        {
            pilaAMostrar=apilar(pilaAMostrar,desapilar(&pilaAux));
        }

        //MOSTRAMOS LA LISTA INVERTIDA

        printf("\n=============\n");
        printf("\n==TOPE=======\n");
        printf("\n=============\n");
        while(pilaAMostrar!=NULL)
        {
            printf("%i\n",pilaAMostrar->dato);
            pilaAMostrar=pilaAMostrar->siguiente;
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

