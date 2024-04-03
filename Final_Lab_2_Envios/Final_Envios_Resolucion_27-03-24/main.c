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

typedef struct nodoDestino
{
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

//Punto 1

nodoOrigen *inicOrigen();
nodoOrigen *crearNodoOrigen(char nombre[30]);
nodoOrigen *agregarOrdenadoRec(nodoOrigen *lista,nodoOrigen *nuevo);

nodoDestino *crearNodoDestino(char nombre[30],float costo,int tiempoViaje);
nodoDestino *inicDestino();
nodoDestino *agregarOrdenado(nodoDestino *lista, nodoDestino *nuevo);

void pasarALDL(char nombreArchivo[40],nodoOrigen *listaDeLista);
nodoOrigen *buscarOrigen(char nombreOrigen[30],nodoOrigen *listaOrigen);

void mostrarNDestino(nodoDestino *nodo);

void mostrarNOrigen(nodoOrigen *nodo);
void mostrarNodosDestino(nodoDestino *lista);
void mostrarTodo(nodoOrigen *lista);


int main()
{
    printf("Hello world!\n");
    return 0;
}

//Punto 1

nodoOrigen *inicOrigen()
{
    return NULL;
}

nodoOrigen *crearNodoOrigen(char nombre[30])
{
    nodoOrigen *nuevo=(nodoOrigen*)malloc(sizeof(nodoOrigen));
    strcpy(nuevo->nombre,nombre);
    nuevo->destinosAereos=NULL;
    nuevo->destinosFerro=NULL;
    nuevo->sig=NULL;
    return nuevo;
}

nodoOrigen *agregarOrdenadoRec(nodoOrigen *lista,nodoOrigen *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->nombre,nuevo->nombre)<0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=agregarOrdenadoRec(lista->sig,nuevo);
        }
    }
    return lista;
}

nodoDestino *crearNodoDestino(char nombre[30],float costo,int tiempoViaje)
{
    nodoDestino *nuevo=(nodoDestino*)malloc(sizeof(nodoDestino));
    strcpy(nuevo->nombre,nombre);
    nuevo->costo=costo;
    nuevo->tiempoViaje=tiempoViaje;
    nuevo->sig=NULL;

    return nuevo;
}

nodoDestino *inicDestino()
{
    return NULL;
}

nodoDestino *agregarOrdenado(nodoDestino *lista, nodoDestino *nuevo);

void pasarALDL(char nombreArchivo[40],nodoOrigen *listaDeLista)
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroEnvios buffer;
        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            nodoDestino *nuevo=crearNodoDestino(buffer.destino,buffer.costo,buffer.tiempoViaje);
        }
        fclose(archivo);
    }
}

nodoOrigen *buscarOrigen(char nombreOrigen[30],nodoOrigen *listaOrigen)
{
    nodoOrigen *resultado=NULL;

    if(listaOrigen)
    {
        nodoOrigen *iterador=listaOrigen;

        while(iterador && !resultado)
        {
            if(strcmpi(iterador->nombre,nombreOrigen)==0)
            {
                resultado=iterador;
            }
            iterador=iterador->sig;
        }
    }

    return resultado;
}

void mostrarNDestino(nodoDestino *nodo)
{
    if(nodo)
    {
        printf("%s %0.2f %i\n",nodo->nombre,nodo->costo,nodo->tiempoViaje);
    }
}

void mostrarNOrigen(nodoOrigen *nodo)
{
    if(nodo)
    {
        printf("\n %s ",nodo->nombre);
    }
}
void mostrarNodosDestino(nodoDestino *lista)
{
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            mostrarNDestino(iterador);
            iterador=iterador->sig;
        }
    }
}

void mostrarTodo(nodoOrigen *lista)
{
    if(lista)
    {
        nodoOrigen *iterador=lista;
        while(iterador)
        {
            printf("ORIGEN: %s\n",iterador->nombre);
            printf("DESTINOS AEREOS\n");
            mostrarNDestino(iterador->destinosAereos);
            printf("DESTINOS FERROCARRIL\n");
            mostrarNodosDestino(iterador->destinosFerro);
            iterador=iterador->sig;
        }
    }
}
