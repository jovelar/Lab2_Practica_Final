#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dato;
    char palabra[30];
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;

typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

nodo2 *inicializar();
nodo2 *agregarAlFinal(nodo2 *lista,nodo2 *nuevo);
nodo2 *sacarPrimero(nodo2 *lista);

Fila encolar(Fila fila, nodo2 *nuevo);
Fila desencolar(Fila fila);

int menu();

int main()
{
    printf("Hello world!\n");
    return 0;
}

nodo2 *inicializar()
{
    return NULL;
}

nodo2 *agregarAlFinal(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {

    }
}
nodo2 *sacarPrimero(nodo2 *lista);

Fila encolar(Fila fila, nodo2 *nuevo);
Fila desencolar(Fila fila);

int menu();
