#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int dato;
    struct nodo *siguiente;
}nodo;

nodo *inicializar();
nodo *crearNodo(int dato);
nodo *insertarAlPrincipio(nodo *lista,nodo *nuevo);
nodo *insertarAlFinal(nodo *lista,nodo *nuevo);
nodo *insertarOrdenado(nodo *lista,nodo *nuevo);
nodo *buscarNodo(nodo *lista,int datoABuscar);
void *borrarNodo(nodo *lista, int dato);
void mostrarLista(nodo *lista);

nodo *pasarArchivoALista(char nombreArchivo[30]);
nodo *pasarArchivoAListaOrdenado(char nombreArchivo[30]);

int buscarEnListaOrdenada(nodo *lista, int dato);
int buscarEnListaDesordenada(nodo *lista,int dato);
void generarArchivoRegistros(char nombreArchivo[30]);
int numeroRND(int limiteMinimo, int limiteMaximo);
#endif // LISTA_SIMPLE_H
