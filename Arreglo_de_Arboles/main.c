#include <stdio.h>
#include <stdlib.h>

typedef struct nodoArbol
{
    int dato;
    struct nodoArbol *izq;
    struct nodoArbol *der;

}nodoArbol;

typedef struct celda
{
    char nombreCelda[20];
    int validos;

}

int main()
{
    printf("Hello world!\n");
    return 0;
}
