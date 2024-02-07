#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dato;
    struct nodo * siguiente;
}nodo;

int menu();
nodo *inicializar();
nodo *crearNuevoNodo(int dato);
nodo *agregarOrdenado(nodo *lista, nodo *nuevo);
nodo *agregarAlPrincipio(nodo *lista, nodo *nuevo);
nodo *agregarAlFinal(nodo *lista, nodo*nuevo);
nodo *borrarBuscando(nodo *lista, int dato);
nodo *borrarAlPrincipio(nodo *lista);
nodo *borrarAlFinal(nodo *lista);
void *mostrarLista(nodo *lista);
int buscarNumero(nodo *lista, int numero);




int main()
{
    int opcion=0;
    while(opcion!=57)
    {
        opcion=menu();
        switch(opcion)
        {
            case 49:
                break;
            case 50:
                break;
            case 51:
                break;
            case 52:
                break;
            case 53:
                break;
            case 54:
                break;
            case 55:
                break;
            case 56:
                break;
            case 57:
                break;

            default:
                printf("opcion invalida! \n");
            break;
        }
    }
    return 0;
}

int menu()
{
    int opcion;
    printf("1- Agregar ordenado a la lista \n");
    printf("2- Agregar datos al principio de la lista \n");
    printf("3- Agregar datos al final de la lista \n");
    printf("4- Borrar buscando un dato \n");
    printf("5- Borrar desde el principio \n");
    printf("6- Borrar desde el final \n");
    printf("7- Mostrar la lista \n");
    printf("8- Buscar un numero \n");
    printf("9- SALIR: \n");
    opcion=getch();
    return opcion;
}

nodo *inicializar()
{
    return NULL;
}

nodo *crearNuevoNodo(int dato)
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;
    return nuevo;
}

nodo *agregarOrdenado(nodo *lista, nodo *nuevo)
{
    if (lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(lista->dato>nuevo->dato)  //SI ES EL PRIMER NODO
        {
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else //SI NO ES EL PRIMERO LO BUSCA
        {
            nodo *anterior;
            nodo *iterador=lista;
            while(iterador!=NULL)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            if(iterador==NULL)//SI ES EL ULTIMO
            {
                anterior->siguiente=nuevo;
            }
            else
            {
                anterior->siguiente=nuevo;
                nuevo->siguiente=iterador;
            }

        }
    }
    return lista;
}

nodo *agregarAlPrincipio(nodo *lista, nodo *nuevo);
nodo *agregarAlFinal(nodo *lista, nodo*nuevo);
nodo *borrarBuscando(nodo *lista, int dato);
nodo *borrarAlPrincipio(nodo *lista);
nodo *borrarAlFinal(nodo *lista);
void *mostrarLista(nodo *lista);
int buscarNumero(nodo *lista, int numero);

