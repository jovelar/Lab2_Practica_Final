#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
 char origen[30];
 char destino[30];
 char tipo[30];//”aereo”,“ferrocarril”
 float costo;
 int tiempoViaje;
}registroEnvios;

typedef struct nodoDestino {
   char nombre[30];
   float costo;
   int tiempoViaje;
   struct nodoDestino* sig;
}nodoDestino;

typedef struct nodoOrigen
 {
   char nombre[30];
   nodoDestino* destinosAereos;
   nodoDestino* destinosFerro;
   struct nodoOrigen* sig;
}nodoOrigen;

////////PUNTO 1 ////////
nodoDestino *inicDestino();
nodoDestino *nuevoDestino(char nombre[],float costo,int tiempoViaje);
nodoDestino *insertarAlFinal(nodoDestino *lista, nodoDestino *nuevo);

nodoOrigen *inicOrigen();
nodoOrigen *nuevoOrigen(char nombre);
nodoOrigen *insertarOrdenadoRec(nodoOrigen *lista, nodoOrigen *nuevo);

void mostrarListaOrigen(nodoOrigen *lista);
void mostrarListaDestino(nodoDestino *lista);


int main()
{
    return 0;
}

////////PUNTO 1 ////////
nodoDestino *inicDestino()
{
    return NULL;
}
nodoDestino *nuevoDestino(char nombre[],float costo,int tiempoViaje)
{
    nodoDestino *nuevo=(nodoDestino*)malloc(sizeof(nodoDestino));
    strcpy(nuevo->nombre,nombre);
    nuevo->costo=costo;
    nuevo->tiempoViaje=tiempoViaje;
    nuevo->sig=NULL;

    return nuevo;
}
nodoDestino *insertarAlFinal(nodoDestino *lista, nodoDestino *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoDestino *aux=lista;
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        aux->sig=nuevo;
    }

    return lista;
}

nodoOrigen *inicOrigen()
{
    return NULL;
}

nodoOrigen *nuevoOrigen(char nombre)
{
    nodoOrigen *nuevo=(nodoOrigen*)malloc(sizeof(nodoOrigen));
    strcpy(nuevo->nombre,nombre);
    nuevo->destinosAereos=NULL;
    nuevo->destinosFerro=NULL;

    return nuevo;
}
nodoOrigen *insertarOrdenadoRec(nodoOrigen *lista, nodoOrigen *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if()
    }
}

void mostrarListaOrigen(nodoOrigen *lista);
void mostrarListaDestino(nodoDestino *lista);
