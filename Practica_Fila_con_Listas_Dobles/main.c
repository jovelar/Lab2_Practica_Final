#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dato;
    char palabra[20];
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;

typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

nodo2 *inicLista();
nodo2 *crearNodo2(int dato, char palabra[20]);
nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo);
nodo2 *borrarPrimero(nodo2 *lista);
nodo2 *buscar(nodo2 *lista,int dato);
void mostrarLista(lista);

void inicFila(Fila *fila);
void encolar(Fila *fila,nodo2 *nuevo);
void desencolar(Fila *fila);
nodo2 *desencolar2(Fila *fila);
void mostrarFila(Fila *fila);

int menu();

int main()
{
    int opcion=0;
    Fila fila;
    inicFila(&fila);
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
        case 27://SALIR
            printf("\nSALIENDO!");
            break;

            case 49:;
                int dato;
                char palabra[20];
                printf("\nIngrese el dato a cargar: ");
                scanf("%d",&dato);
                printf("\nIngrese la palabra a cargar: ");
                fflush(stdin);
                gets(palabra);
                nodo2 *nuevo=crearNodo2(dato,palabra);
                encolar(&fila,nuevo);
                printf("\nCargado!");
                break;

            case 50:;
                nodo2 *retirado=(nodo2*)malloc(sizeof(nodo2));
                retirado=inicLista;

                retirado=desencolar2(&fila);

                if(retirado)
                {
                    printf("\nSe retiro el nodo %i| %s",retirado->dato,retirado->palabra);
                }
                else
                {
                    printf("\nLa lista esta vacia!");
                }
                free(retirado);
                break;

            case 51:
                mostrarFila(&fila);
                break;

            case 52:;
                int dato2;
                printf("Ingrese el dato a buscar: ");
                scanf("%d",&dato2);
                nodo2 *busqueda=NULL;
                busqueda=buscar(fila.primero,dato2);

                if(busqueda)
                {
                    printf("\nSe encontro el nodo %i %s",busqueda->dato,busqueda->palabra);
                }
                else
                {
                    printf("\nNo se encontro el dato");
                }

                break;

            default:
                printf("\nOpcion invalida!");
                break;
        }
    }
    return 0;
}

nodo2 *inicLista()
{
    return NULL;
}
nodo2 *crearNodo2(int dato, char palabra[20])
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;
    strcpy(nuevo->palabra,palabra);
    nuevo->dato=dato;
    return nuevo;
}

nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo)
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

nodo2 *borrarPrimero(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *sig=lista->siguiente;
        free(lista);
        lista=sig;
    }
    return lista;
}

nodo2 *buscar(nodo2 *lista,int dato)
{
    nodo2 *resultado=inicLista();
    if(lista)
    {
        if(lista->dato==dato)
        {
            resultado=lista;
        }
        else
        {
            nodo2 *iterador=lista;
            while(iterador && !resultado)
            {
                if(iterador->dato==dato)
                {
                    resultado=iterador;
                }
                iterador=iterador->siguiente;
            }
        }
    }
    return resultado;
}

void mostrarLista(lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            printf("\n %i %s",iterador->dato,iterador->palabra);
        }
        iterador=iterador->siguiente;
    }
}

void inicFila(Fila *fila)
{
    fila->primero=inicLista();
    fila->ultimo=inicLista();
}

void encolar(Fila *fila,nodo2 *nuevo)
{
    fila->ultimo=agregarAlFinal(fila->ultimo,nuevo);
    if(!fila->primero)
    {
        fila->primero=fila->ultimo;
    }
    fila->ultimo=nuevo;
}

void desencolar(Fila *fila)
{
    if(fila)
    {
        if(fila->primero==fila->ultimo)
        {
            fila->primero=borrarPrimero(fila->primero);
            fila->primero=NULL;
            fila->ultimo=NULL;
        }
        else
        {
            fila->primero=borrarPrimero(fila->primero);
        }
    }
}

nodo2 *desencolar2(Fila *fila)
{
    nodo2 *desencolado=(nodo2*)malloc(sizeof(nodo2));
    desencolado->anterior=NULL;
    desencolado->siguiente=NULL;
    desencolado->dato=0;
    strcpy(desencolado->palabra,"");

    if(fila->primero)
    {
        if(fila->primero==fila->ultimo)
        {
            //SE COPIA INTEGRAMENTE EL NODO
            desencolado->dato=fila->primero->dato;
            strcpy(desencolado->palabra,fila->primero->palabra);
            desencolado->anterior=fila->primero->anterior;
            desencolado->siguiente=fila->primero->siguiente;

            fila->primero=borrarPrimero(fila->primero);

            fila->primero=NULL;
            fila->ultimo=NULL;
        }
        else
        {
            //SE COPIA INTEGRAMENTE EL NODO
            desencolado->dato=fila->primero->dato;
            strcpy(desencolado->palabra,fila->primero->palabra);
            desencolado->anterior=fila->primero->anterior;
            desencolado->siguiente=fila->primero->siguiente;

            fila->primero=borrarPrimero(fila->primero);
        }
    }
    return desencolado;
}

void mostrarFila(Fila *fila)
{
    if(fila)
    {
        mostrarLista(fila->primero);
    }
    else
    {
        printf("\nLa fila esta vacia!");
    }
}


int menu()
{
    printf("\n 1- Encolar");
    printf("\n 2- Desencolar");
    printf("\n 3- Mostrar");
    printf("\n 4- Buscar");
    printf("\n\n ESC - SALIR");
    int opcion;
    opcion=getch();
}

