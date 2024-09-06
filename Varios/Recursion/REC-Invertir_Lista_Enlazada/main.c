#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dato;
    char palabra[30];
    struct nodo *sig;
}nodo;

nodo *inicNodo();
nodo *crearNodo(int dato, char palabra[30]);
nodo *agregarAlFinal(nodo *lista, nodo *nuevo);
void prepararLista(nodo **lista);
void mostrarLista(nodo *lista);
void borrarLista(nodo **lista);

nodo *invertirRecursivo(nodo *lista, nodo *resultante);
nodo *invertirRecSinCrearNodosNuevos(nodo *lista, nodo *resultante);

int main()
{

    nodo *lista=inicNodo();
    prepararLista(&lista);

    printf("Lista base: \n");
    mostrarLista(lista);

    nodo *listaInvertida=inicNodo();
    listaInvertida=invertirRecursivo(lista,listaInvertida);
    printf("\nLista invertida: \n");
    mostrarLista(listaInvertida);

    nodo *listaInvertidaSCP=inicNodo();

    printf("\n Lista Invertida Sin Crear Nodos nuevos: \n");
    listaInvertidaSCP=invertirRecSinCrearNodosNuevos(lista,listaInvertidaSCP);
    mostrarLista(listaInvertidaSCP);


    borrarLista(&listaInvertida);
    borrarLista(&lista);
    borrarLista(&listaInvertidaSCP);
    return 0;
}

nodo *inicNodo()
{
    return NULL;
}

nodo *crearNodo(int dato, char palabra[20])
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    strcpy(nuevo->palabra,palabra);
    nuevo->sig=NULL;
    return nuevo;
}

nodo *agregarAlFinal(nodo *lista, nodo *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo *iterador=lista;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }
    return lista;
}

void prepararLista(nodo **lista)
{
    nodo *nodo1=crearNodo(10,"Papas Fritas");
    nodo *nodo2=crearNodo(20,"Papas Con Cheddar");
    nodo *nodo3=crearNodo(30,"Milanesita de Muzarella");
    nodo *nodo4=crearNodo(40,"Sanguche Milanesa");
    nodo *nodo5=crearNodo(50,"Milanesa a caballo");
    nodo *nodo6=crearNodo(60,"Suprema maryland");
    nodo *nodo7=crearNodo(70,"Milanesa Napolitana al Horno");

    *lista=agregarAlFinal(*lista,nodo1);
    *lista=agregarAlFinal(*lista,nodo2);
    *lista=agregarAlFinal(*lista,nodo3);
    *lista=agregarAlFinal(*lista,nodo4);
    *lista=agregarAlFinal(*lista,nodo5);
    *lista=agregarAlFinal(*lista,nodo6);
    *lista=agregarAlFinal(*lista,nodo7);
}

void mostrarLista(nodo *lista)
{
    if(lista)
    {
        nodo *iterador=lista;
        while(iterador)
        {
            printf(" %-2i %-30s \n",iterador->dato,iterador->palabra);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("Lista vacia! \n");
    }
}

void borrarLista(nodo **lista)
{
    if(*lista)
    {
        nodo *aux=*lista;
        while(aux)
        {
            aux=(*lista)->sig;
            free(*lista);
            *lista=aux;
        }
    }
}

//Invierte creando nodos nuevos y devolviendo una lista nueva.
nodo *invertirRecursivo(nodo *lista, nodo *resultante)
{
    if(lista)
    {
        nodo *nuevo=(nodo*)malloc(sizeof(nodo));
        nuevo->dato=lista->dato;
        strcpy(nuevo->palabra,lista->palabra);
        nuevo->sig=resultante;
        resultante=nuevo;
        resultante=invertirRecursivo(lista->sig,resultante);
    }
    return resultante;
}

//Invierte una lista recursivamente sin crear nodos nuevos
nodo *invertirRecSinCrearNodosNuevos(nodo *lista, nodo *resultante)
{
    if(lista)
    {
        nodo *aux=lista->sig;
        lista->sig=resultante;
        resultante=lista;
        resultante=invertirRecSinCrearNodosNuevos(aux,resultante);
    }
    return resultante;
}
