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
nodo *insertarAlFinalRec(nodo *lista, nodo *nuevo);
nodo *insertarOrdenadoRec(nodo *lista, nodo*nuevo);
nodo *mostrarListaRec(nodo *lista);
nodo *mostrarInvertidoRec(nodo *lista);
nodo *mostrarPosParRec(nodo *lista, int pos);
nodo *borrarNodoRec(nodo *lista, char palabra[30]);
nodo *invertirListaRec(nodo *lista, nodo *resultante);
void eliminarListaRec(nodo **lista);
int *sumarElementosListaRec(nodo *lista,int sumatoria);

void crearListaCargada(nodo **lista);

void punto1(nodo *lista);
void punto2(nodo *lista);
void punto3(nodo *lista);
void punto4(nodo **lista);
void punto5(nodo **lista);
void punto6(nodo **lista);

int main()
{
    printf("Hello world!\n");
    return 0;
}

nodo *inicNodo()
{
    return NULL;
}

nodo *crearNodo(int dato, char palabra[30])
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    strcpy(nuevo->palabra,palabra);
    nuevo->sig=NULL;
    return nuevo;
}

nodo *insertarAlFinalRec(nodo *lista, nodo *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        lista->sig=insertarAlFinalRec(lista->sig,nuevo);
    }
    return lista;
}

nodo *insertarOrdenadoRec(nodo *lista, nodo*nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->palabra,nuevo->palabra)<0)
        {
            nuevo->sig=lista;
        }
        else
        {
            lista=insertarOrdenadoRec(lista->sig,nuevo);
        }
    }
    return lista;
}

nodo *mostrarListaRec(nodo *lista)
{
    if(lista)
    {
        printf("%s %i \n");
        mostrarListaRec(lista->sig);
    }
}

nodo *mostrarInvertidoRec(nodo *lista)
{

}

nodo *mostrarPosParRec(nodo *lista, int pos)
{
    if(lista)
    {
        if(pos%2==0)
        {
            printf("%s %i \n");
        }
        pos++;
        mostrarPosParRec(lista->sig,pos);
    }
}

nodo *borrarNodoRec(nodo *lista, char palabra[30])
{
    if(lista)
    {
        if(strcmpi(lista->palabra,palabra)==0)
        {
            nodo *aux=lista->sig;
            free(lista);
            lista=aux;
        }
        else
        {
            lista=borrarNodoRec(lista->sig,palabra);
        }
    }
    return lista;
}

nodo *invertirListaRec(nodo *lista, nodo *resultante)
{
    if(lista)
    {
        nodo *aux=lista->sig;
        lista->sig=resultante;
        resultante=lista;
        resultante=invertirListaRec(aux,resultante);
    }
    return resultante;
}

void eliminarListaRec(nodo **lista)
{
    if(*lista)
    {
        nodo *aux=(*lista)->sig;
        free(*lista);
        eliminarListaRec(&aux);
    }
}

int *sumarElementosListaRec(nodo *lista,int sumatoria)
{
    if(lista)
    {
        sumatoria=sumarElementosListaRec(lista->sig,sumatoria+lista->dato);
    }
    return sumatoria;
}

void crearListaCargada(nodo **lista)
{
    nodo *nuevo1=crearNodo(10,"Papas Fritas");
    nodo *nuevo2=crearNodo(20,"Chocolate negro");
    nodo *nuevo3=crearNodo(30,"Cerveza");
    nodo *nuevo4=crearNodo(40,"Frutas");
    nodo *nuevo5=crearNodo(50,"Panceta");
    nodo *nuevo6=crearNodo(60,"Fideos");
    nodo *nuevo7=crearNodo(70,"Helado");
    *lista=insertarAlFinalRec(*lista,nuevo1);
    *lista=insertarAlFinalRec(*lista,nuevo2);
    *lista=insertarAlFinalRec(*lista,nuevo3);
    *lista=insertarAlFinalRec(*lista,nuevo4);
    *lista=insertarAlFinalRec(*lista,nuevo5);
    *lista=insertarAlFinalRec(*lista,nuevo6);
    *lista=insertarAlFinalRec(*lista,nuevo7);
}

void punto1(nodo *lista);
void punto2(nodo *lista);
void punto3(nodo *lista);
void punto4(nodo **lista);
void punto5(nodo **lista);
void punto6(nodo **lista);
