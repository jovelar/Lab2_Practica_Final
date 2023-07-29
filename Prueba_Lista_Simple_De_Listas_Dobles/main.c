#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char palabra[50];
    int dato;
}DatoNodoLS;

typedef struct
{
    DatoNodoLS datoNodoLS;
    struct NodoLS *siguiente;
}NodoLS;

typedef struct
{
    char frase[50];
    int numero;
}DatoNodoD;

typedef struct
{
    DatoNodoD datoNodoD;
    struct NodoLD *nodoslD;
}NodoLD;


////////FUNCIONES LISTA SIMPLE////////
NodoLD *inicLD();
NodoLD *nuevo(NodoLS *lista,NodoLS *nuevo);
NodoLD *insertarOrdenado(NodoLS lista,NodoLS *nuevo);
NodoLD *insertarAlPrincipio();
NodoLD *insertarAlFinal();
NodoLD *buscar(NodoLD *lista);
NodoLD *borrar(NodoLD *lista,char palabraABuscar[50]);

////////FUNCIONES LISTA DOBLE////////


int main()
{
    printf("Hello world!\n");
    return 0;
}
