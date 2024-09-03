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

typedef struct
{
    char provincia[30];
    int votos_totales;
}VotosProvincia;

typedef struct
{
    VotosProvincia votos;
    struct VotosXProvincia *ante;
    struct VotosXProvincia *sig;
}VotosXProvincia;

//Punto 1
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


//Punto 2
VotosXProvincia *inicVXP();
VotosProvincia *crearVP(char provincia[30],int votos);
VotosXProvincia *crearVXP(VotosProvincia *VotosProvincia);
VotosXProvincia *pasarAVXPRec(VotosXProvincia *listaVXP,nodoProvincia *provincias,nodoPartido *partidos,int votos);
void ejercicio2(nodoProvincia *listaProv,VotosXProvincia **listaVXP);
void mostrarVP(VotosProvincia vp);
void mostrarVXP(VotosXProvincia *vxp);
void mostrarLista2(VotosXProvincia *lista);

//Punto 3
VotosXProvincia *buscar(VotosXProvincia *lista,char nombreProvincia[30]);
VotosXProvincia *borrar(VotosXProvincia *lista,char nombreProvincia[30]);
void ejercicio3(VotosXProvincia **lista,char nombreProvincia[30]);

int main()
{

    char nombreArchivo[]="votos.bin";
    nodoProvincia *lista=inicNodoProvincia();
    ejercicio1(&lista,nombreArchivo);

    VotosXProvincia *listaVXP=NULL;
    ejercicio2(lista,&listaVXP);
    ejercicio3(&listaVXP,"Tucuman");

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

//Punto 2

VotosXProvincia *inicVXP()
{
    return NULL;
}
VotosProvincia *crearVP(char provincia[30],int votos)
{
    VotosProvincia *nuevo=(VotosProvincia*)malloc(sizeof(VotosProvincia));
    strcpy(nuevo->provincia,provincia);
    nuevo->votos_totales=votos;
    return nuevo;
}

VotosXProvincia *crearVXP(VotosProvincia *votosProvincia)
{
    VotosXProvincia *nuevo=(VotosXProvincia*)malloc(sizeof(VotosXProvincia));
    nuevo->votos=*votosProvincia;
    nuevo->ante=NULL;
    nuevo->sig=NULL;
    return nuevo;
}

VotosXProvincia *pasarAVXPRec(VotosXProvincia *listaVXP,nodoProvincia *provincias,nodoPartido *partidos,int votos)
{
    if(provincias)
    {
        if(partidos)
        {
            listaVXP=pasarAVXPRec(listaVXP,provincias,partidos->sig,votos + partidos->cant_votos);
        }
        else
        {
            VotosProvincia *nuevoVotos=(VotosProvincia*)malloc(sizeof(VotosProvincia));
            nuevoVotos->votos_totales=votos;
            strcpy(nuevoVotos->provincia,provincias->provincia);
            VotosXProvincia *nuevo=(VotosXProvincia*)malloc(sizeof(VotosXProvincia));
            nuevo->votos=*nuevoVotos;
            nuevo->ante=listaVXP;
            nuevo->sig=NULL;

            listaVXP=nuevo;

            if(provincias->sig)
            {
                provincias=provincias->sig;
                listaVXP->sig=pasarAVXPRec(listaVXP,provincias,provincias->partido,0);
            }
        }

    }
    return listaVXP;
}

void mostrarVP(VotosProvincia vp)
{
    printf("Provincia %s Votos %i \n",vp.provincia,vp.votos_totales);
}

void mostrarVXP(VotosXProvincia *vxp)
{
    if(vxp)
    {
        VotosXProvincia *iterador=vxp;
        while(iterador)
        {
            mostrarVP(iterador->votos);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("La lista esta vacia!\n");
    }
}

void mostrarVXPRev(VotosXProvincia *vxp)
{
    if(vxp)
    {
        VotosXProvincia *ultimo=vxp;
        while(ultimo->sig)
        {
            ultimo=ultimo->sig;
        }
        while(ultimo)
        {
            mostrarVP(ultimo->votos);
            ultimo=ultimo->ante;
        }
    }
}

void ejercicio2(nodoProvincia *listaProv,VotosXProvincia **listaVXP)
{
    printf("Ejercicio 2: \n\n");
    *listaVXP=pasarAVXPRec(*listaVXP,listaProv,listaProv->partido,0);
    mostrarVXP(*listaVXP);
}

//Punto 3
VotosXProvincia *buscar(VotosXProvincia *lista,char nombreProvincia[30])
{
    VotosXProvincia *posicion=NULL;

    if(lista)
    {
        if(strcmpi(lista->votos.provincia,nombreProvincia)==0)
        {
            posicion=lista;
        }
        else
        {
            VotosXProvincia *iterador=lista;
            while(iterador && !posicion)
            {
                if(strcmpi(iterador->votos.provincia,nombreProvincia)==0)
                {
                    posicion=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }

    return posicion;
}

VotosXProvincia *borrar(VotosXProvincia *lista, char nombreProvincia[30])
{
    if(lista)
    {
        VotosXProvincia *posicion=buscar(lista, nombreProvincia);
        if(posicion)
        {
            if(!posicion->ante) //SI ES EL PRIMERO DE LA LISTA
            {
                VotosXProvincia *aux=lista->sig;
                aux->ante=NULL;
                free(lista);
                lista=aux; //Se debe sobreescribir el puntero inicial, por eso la desreferenciacion
            }
            else if(!posicion->sig) //SI ES EL ULTIMO DE LA LISTA
            {
                VotosXProvincia *aux=posicion->ante;
                aux->sig=NULL;
                free(posicion);
            }
            else
            {
                VotosXProvincia *anterior=posicion->ante;
                VotosXProvincia *siguiente=posicion->sig;
                anterior->sig=posicion->sig;
                siguiente->ante=posicion->ante;
                free(posicion);
            }
        }
    }
    return lista;
}
void ejercicio3(VotosXProvincia **lista,char nombreProvincia[30])
{
    printf("Ejercicio 3: \n\n");
    *lista=borrar(*lista,nombreProvincia);
    mostrarVXP(*lista);
}
