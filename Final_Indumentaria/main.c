#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stRegistro;

typedef struct
{
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;


typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;


int main()
{

    return 0;
}
