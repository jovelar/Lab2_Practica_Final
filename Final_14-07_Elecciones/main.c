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
nodoProvincia *buscarProvincia(nodoProvincia *lista, char provincia[30]);
nodoProvincia *insertarProvinciaOrdenado(nodoProvincia *lista, nodoProvincia *nuevaprovincia);

nodoProvincia *pasarAlDL(char nombreArchivo[30]);
void mostrarVotos(nodoPartido *listaPartidos);
void mostrarTodo(nodoProvincia *listaProvincias);
void ejercicio1(nodoProvincia **lista,char nombreArchivo[30]);

int main()
{
    char nombreArchivo[]="votos.bin";
    nodoProvincia *lista=inicNodoProvincia();
    ejercicio1(&lista,nombreArchivo);
    return 0;
}

nodoPartido *inicNodoPartido()
{
    return NULL;
}
nodoPartido *nuevoPartido(char partido[30],int cant_votos)
{
    nodoPartido *nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    strcpy(nuevo->partido,partido);
    nuevo->cant_votos=cant_votos;
    nuevo->sig=NULL;

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
        nodoPartido *aux=listaPartido;
        while(aux->sig)
        {
            aux=aux->sig;
        }
        aux->sig=nuevoPartido;

    }
    return listaPartido;
}

nodoProvincia *inicNodoProvincia()
{
    return NULL;
}

nodoProvincia *nuevaProvincia(char provincia[30])
{
    nodoProvincia *nuevo=(nodoProvincia*)malloc(sizeof(nodoProvincia));
    strcpy(nuevo->provincia,provincia);
    nuevo->partido=NULL;
    nuevo->sig=NULL;

    return nuevo;
}

nodoProvincia *buscarProvincia(nodoProvincia *lista, char provincia[30])
{
    nodoProvincia *posicion=NULL;
    if(lista)
    {
        if(strcmpi(lista->provincia,provincia)==0)
        {
            posicion=lista;
        }
        else
        {
            nodoProvincia *aux=lista;
            while(aux && !posicion)
            {
                if(strcmpi(aux->provincia,provincia)==0)
                {
                    posicion=aux;
                }
                aux=aux->sig;
            }
        }
    }
    return posicion;
}

nodoProvincia *insertarProvinciaOrdenado(nodoProvincia *lista, nodoProvincia *nuevaprovincia)
{
    if(!lista)
    {
        lista=nuevaprovincia;
    }
    else
    {
        if(strcmpi(lista->provincia,nuevaprovincia->provincia)>0)
        {
            nuevaprovincia->sig=lista;
            lista=nuevaprovincia;
        }
        else
        {
            nodoProvincia *aux=lista->sig;
            nodoProvincia *ante=lista;

            while(aux && strcmpi(aux->provincia,nuevaprovincia->provincia)<0)
            {
                ante=aux;
                aux=aux->sig;
            }
            ante->sig=nuevaprovincia;
            nuevaprovincia->sig=aux;
        }
    }
    return lista;
}

nodoProvincia *pasarAlDL(char nombreArchivo[30])
{
    nodoProvincia *lista=NULL;

    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        RecuentoVotos buffer;
        while(fread(&buffer,sizeof(RecuentoVotos),1,archivo)>0)
        {
            nodoPartido *nuevoPart=nuevoPartido(buffer.partido,buffer.cant_votos);
            nodoProvincia *posicion=buscarProvincia(lista,buffer.provincia);
            if(!posicion)
            {
                nodoProvincia *nuevaProv=nuevaProvincia(buffer.provincia);
                lista=insertarProvinciaOrdenado(lista,nuevaProv);
                posicion=nuevaProv;
            }
            posicion->partido=agregarPartido(posicion->partido,nuevoPart);
        }
        fclose(archivo);
    }
    return lista;
}

void mostrarVotos(nodoPartido *listaPartidos)
{
    nodoPartido *iterador=listaPartidos;
    while(iterador)
    {
        printf("Partida: %s Votos: %i \n",iterador->partido,iterador->cant_votos);
        iterador=iterador->sig;
    }
}

void mostrarTodo(nodoProvincia *listaProvincias)
{
    nodoProvincia *iterador=listaProvincias;
    while(iterador)
    {
        printf("####### %-20s #######\n",iterador->provincia);
        mostrarVotos(iterador->partido);
        iterador=iterador->sig;
    }
}

void ejercicio1(nodoProvincia **lista,char nombreArchivo[30])
{
    *lista=pasarAlDL(nombreArchivo);
    mostrarTodo(*lista);
}
