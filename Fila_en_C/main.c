#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int numero;
    char palabra[40];
}Dato;

typedef struct
{
    struct Nodo2 *anterior;
    struct Nodo2 *siguiente;
    Dato dato;
}Nodo2;

typedef struct
{
     struct Nodo2 *inicio;
     struct Nodo2 *fin;
}Fila;

Nodo2 *inicNodo2()
{
    return NULL;
}

void inicFila(Fila *fila)
{
    fila->inicio=inicNodo2();
    fila->fin=inicNodo2();
}

Nodo2 *insertarOrdenado(Nodo2 *lista, Nodo2 *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(nuevo->dato.palabra,lista->dato.palabra)<0)
        {
            nuevo->siguiente=lista;
            lista->anterior=nuevo;
            lista=nuevo;
        }
        else
        {
            Nodo2 *aux=lista;
            Nodo2 *ante=aux;
            aux=aux->siguiente;

            while(aux->siguiente!=NULL && strcmpi(nuevo->dato.palabra,aux->dato.palabra)>0)
            {
                ante=aux;
                aux=aux->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->anterior=ante;

            if(aux==NULL)
            {
                nuevo->siguiente=NULL;
            }
            else
            {
                nuevo->siguiente=aux;
                aux->anterior=nuevo;
            }

        }
    }
    return nuevo;
}

Nodo2 *buscarUltimoNodo2(Nodo2 *lista)
{
    Nodo2 *resultado=NULL;

    if(lista!=NULL)
    {
        Nodo2 *aux=lista;
        while(lista->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
        aux=resultado;
    }
    return resultado;
}

void mostrarFila(Fila fila)
{
    if(fila.inicio!=NULL)
    {
        Nodo2 *aux=fila.inicio;
        while(aux!=NULL)
        {
            printf("%i|%s\n",aux->dato.numero,aux->dato.palabra);
            aux=aux->siguiente;
        }
    }
    else
    {
        printf("\nLa fila esta vacia!\n");
    }
}int menu()kkkklk


int main()
{
    Fila nuevo;
    inicFila(&nuevo);
    return 0;
}
