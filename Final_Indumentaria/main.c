#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stRegistro;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;


typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

Fila pasarAFila(char nombreArchivo[20]);

nodo2 *inicNodo2();
nodo2 *crearNodo2(int idSucursal, char nombreSucursal[20],char nombreProducto[20],char deporte[25],int stockProducto);
nodo2 *agregarAlFinal(nodo2 *lista,nodo2 *nuevo);
void mostrarNodo2(nodo2 *nodo);

void inicFila(Fila *fila);

void encolar(Fila *fila, nodo2 *nuevo);
void mostrarFila(Fila *fila);

void ejercicio1(Fila *fila,char nombreArchivo[20]);

int main()
{
    Fila nuevaFila;
    inicFila(&nuevaFila);
    char nombreArchivo[50]="archivoRegistrosIndumentaria.bin";
    ejercicio1(&nuevaFila,nombreArchivo);
    mostrarFila(&nuevaFila);

    return 0;
}

nodo2 *inicNodo2()
{
    return NULL;
}
nodo2 *crearNodo2(int idSucursal, char nombreSucursal[20],char nombreProducto[20],char deporte[25],int stockProducto)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->idSucursal=idSucursal;
    strcpy(nuevo->nombreSucursal,nombreSucursal);
    strcpy(nuevo->nombreProducto,nombreProducto);
    strcpy(nuevo->deporte,deporte);
    nuevo->stockProducto=stockProducto;
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;

    return nuevo;
}

Fila pasarAFila(char nombreArchivo[20])
{
    Fila cargado;
    inicFila(&cargado);
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        nodo2 *nuevo;
        stRegistro buffer;
        while(fread(&buffer,sizeof(stRegistro),1,archivo)>0)
        {
            nuevo=crearNodo2(buffer.idSucursal,buffer.nombreSucursal,buffer.nombreProducto,buffer.deporte,buffer.stockProducto);
            encolar(&cargado,nuevo);
        }
        fclose(archivo);
    }
    else
        printf("\n el archivo no existe/no se pudo abrir ");

    return cargado;
}

nodo2 *agregarAlFinal(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        lista->siguiente=nuevo;
        nuevo->anterior=lista;
    }
    return nuevo;
}

void mostrarNodo2(nodo2 *nodo)
{
    if(nodo)
    {
        nodo2 dato=*nodo;
        puts ("\n**********************************************************************************\n");
        printf ("\nId de la Sucursal: %d \n", dato.idSucursal);
        printf("\nNombre de la Sucursal: ..:%s \n", dato.nombreSucursal);
        printf("\nNombre del Producto........................: %s \n ", dato.nombreProducto);
        printf("\nDeporte al que pertenece.................: %s \n ", dato.deporte);
        printf("\nStock del producto............................: %d \n", dato.stockProducto);
        puts ("\n**********************************************************************************\n");
    }
}

void inicFila(Fila *fila)
{
    fila->primero=inicNodo2();
    fila->ultimo=inicNodo2();
}

void encolar(Fila *fila, nodo2 *nuevo)
{
    fila->ultimo=agregarAlFinal(fila->ultimo,nuevo);
    if(!fila->primero)
    {
        fila->primero=fila->ultimo;
    }
}

void mostrarFila(Fila *fila)
{
    if(fila)
    {
        if(fila->primero)
        {
        mostrarFila(fila->primero);
        mostrarFila(fila->primero->siguiente);
        }
    }

}

void ejercicio1(Fila *fila,char nombreArchivo[20])
{
    *fila=pasarAFila(nombreArchivo);
}

