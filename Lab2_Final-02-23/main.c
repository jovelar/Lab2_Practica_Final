#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
 char origen[30];
 char destino[30];
 char tipo[30];//�aereo�,�ferrocarril�
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
nodoOrigen *buscar(nodoOrigen *lista, char nombreOrigen[]);

nodoOrigen *pasarALDL(char nombreArchivo[]);

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
        if(strcasecmp(nuevo->nombre,lista->nombre)<0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarOrdenadoRec(lista->sig,nuevo);
        }
    }
    return lista;
}

nodoOrigen *buscar(nodoOrigen *lista, char nombreOrigen[])
{
    nodoDestino *resultado=NULL;
    if(lista!NULL)
    {
        nodoDestino *aux=lista;
        while(aux!=NULL && resultado==null)
        {
            if(strcasecmp(lista->nombre,nombreOrigen)==0)
            {
                resultado=aux;
            }
        }
    }
    return resultado;
}

nodoOrigen *pasarALDL(char nombreArchivo[])
{
    nodoOrigen *nuevaLista=inicOrigen();
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroEnvios buffer;
        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            nodoDestino *nuevo=nuevoDestino(buffer.destino,buffer.costo,buffer.tiempoViaje);

            nodoOrigen *posicionAInsertar=buscar(nodoOrigen *nuevaLista,buffer.origen);

            if(posicionAInsertar==NULL)
            {
                nodoOrigen *nuevo=nuevoOrigen(buffer.origen);
                nuevaLista=insertarOrdenadoRec(nuevaLista,nuevo);
                posicionAInsertar=nuevo;
            }
            if()
        }
    }
    else
    {
        printf("El archivo no se pudo abrir/ encontrar");
    }
}

void mostrarListaOrigen(nodoOrigen *lista)
{
    if(lista!=NULL)
    {
        nodoOrigen *aux=lista;
        while(aux!=NULL)
        {
            printf("\nOrigen: %s\n",aux->nombre);
            printf("\nMostrando Destinos Aereos\n");
            mostrarListaDestino(aux->destinosAereos);
            printf("\nMostrando Destinos Ferrocarril\n");
            mostrarListaDestino(aux->destinosFerro);

            aux=aux->sig;
        }
    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}
void mostrarListaDestino(nodoDestino *lista)
{
    if(lista!=NULL)
    {
        nodoDestino *aux=lista;
        while(aux!=NULL)
        {
            printf("N: %s|$ : %.2f|T: %i\n",aux->nombre,aux->costo,aux->tiempoViaje);
            aux=aux->sig;
        }
    }
    else
    {
        printf("\No hay destinos!");
    }
}
