#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stRegistro;

typedef struct
{
    stRegistro dato;
    struct nodo2 *siguiente;
    struct nodo2 *anterior;
}nodo2;

typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

//Ejercicio 1

nodo2 *inicNodo2();
stRegistro nuevoRegistro(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto);
nodo2 *nuevoNodo2(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto);
nodo2 *agregarFinalNodo2(nodo2 *lista,nodo2 *nuevo);

Fila *pasarAFila(Fila *fila,char nombreArchivo[50]);

void inicFila(Fila *fila);
void encolar(Fila *fila,nodo2 *nuevo);

void mostrarFilaRec(nodo2 *lista);

int main()
{
    printf("Hello world!\n");
    return 0;
}

//Ejercicio 1

nodo2 *inicNodo2()
{
    return NULL;
}

stRegistro nuevoRegistro(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto)
{
    stRegistro nuevo;
    nuevo.idSucursal=idSucursal;
    strcpy(&nuevo.nombreSucursal,nombreSucursal);
    strcpy(&nuevo.nombreProducto,nombreProducto);
    strcpy(&nuevo.deporte,deporte);
    nuevo.stockProducto=stockProducto;

    return nuevo;
}

nodo2 *nuevoNodo2(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->dato=nuevoRegistro(idSucursal,nombreSucursal,nombreProducto,deporte,stockProducto);
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodo2 *agregarFinalNodo2(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo2 *iterador=lista;
        while(iterador->siguiente)
        {
            iterador=iterador->siguiente;
        }
        iterador->siguiente=nuevo;
        nuevo->anterior=iterador;
    }
    return lista;
}

void *pasarAFila(Fila *fila,char nombreArchivo[50])
{

}

void inicFila(Fila *fila)
{
    fila->primero=NULL;
    fila->ultimo=NULL;
}

void encolar(Fila *fila,nodo2 *nuevo)
{
    fila->primero=agregarFinalNodo2(fila->primero,nuevo);
    if(!fila->ultimo)
    {
        fila->ultimo=fila->primero;
    }
}

void mostrarFilaRec(nodo2 *lista)
{
    if(lista)
    {
        stRegistro dato=lista->dato;
        puts ("\n**********************************************************************************\n");
        printf ("\nId de la Sucursal……………………: %d \n", dato.idSucursal);
        printf("\nNombre de la Sucursal: ………….….:%s \n", dato.nombreSucursal);
        printf("\nNombre del Producto........................: %s \n ", dato.nombreProducto);
        printf("\nDeporte al que pertenece.................: %s \n ", dato.deporte);
        printf("\nStock del producto............................: %d \n", dato.stockProducto);
        puts ("\n**********************************************************************************\n");
        mostrarFilaRec(lista->siguiente);
    }
}
