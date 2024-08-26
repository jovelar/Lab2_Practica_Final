#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
//#include "util\util.h"


typedef struct
{
    char provincia[30];
    char partido[30];//FDT,FIT,UCR,JXC
    int cant_votos;
}RecuentoVotos;

typedef struct
{
    char partido[30];
    int cant_votos;
    struct nodoPartido *sig;
}nodoPartido;

typedef struct
{
    char provincia[30];
    nodoPartido *partido;
    struct nodoProvincia *sig;
}nodoProvincia;

nodoPartido *inicNodoPartido();
nodoPartido *nuevoPartido(char partido[30],int cant_votos);
nodoPartido *agregarPartido(nodoPartido *listaPartido,nodoPartido *nuevoPartido);

nodoProvincia *inicNodoProvincia();
nodoProvincia *nuevaProvincia(char provincia[30]);
nodoProvincia *buscarProvincia(nodoProvincia *lista, char partido[30]);
nodoProvincia *insertarProvincia(nodoProvincia *lista, nodoProvincia *nuevaprovincia);

nodoProvincia pasarAlDL(char nombreArchivo[30]);

void ejercicio1(nodoProvincia **lista);

int main()
{
    return 0;
}

nodoPartido *inicNodoPartido()
{
    return NULL;
}
nodoPartido *nuevoPartido(char partido[30,int cant_votos])
{
    nodoPartido *nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    strcpy(nuevo->partido,partido);
    nuevo->cant_votos=0;

    return nuevo;
}
nodoPartido *agregarPartido(nodoPartido *listaPartido,nodoPartido *nuevoPartido)
{
    if(!listaPartido)
    {
        listaPartido=nuevoPartido;
    }
    else
    {
        if(!listaPartido->sig)
        {
            listaPartido->sig=nuevoPartido;
        }
        else
        {

        }
    }
}

nodoProvincia *inicNodoProvincia();
nodoProvincia *nuevaProvincia(char provincia[30]);
nodoProvincia *buscarProvincia(nodoProvincia *lista, char partido[30]);
nodoProvincia *insertarProvincia(nodoProvincia *lista, nodoProvincia *nuevaprovincia);

nodoProvincia pasarAlDL(char nombreArchivo[30]);

void ejercicio1(nodoProvincia **lista);
