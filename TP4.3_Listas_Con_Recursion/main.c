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
void *mostrarListaRec(nodo *lista);
void *mostrarInvertidoRec(nodo *lista);
void *mostrarPosParRec(nodo *lista, int pos);
nodo *borrarNodoRec(nodo *lista, char palabra[30]);
nodo *invertirListaRec(nodo *lista, nodo *resultante);
void eliminarListaRec(nodo **lista);
int *sumarElementosListaRec(nodo *lista,int sumatoria);

//funciones auxiliares
void crearListaCargada(nodo **lista);
void crearListaCargadaOrdenada(nodo **lista);

void crearListaCargada(nodo **lista);

void punto1(nodo *lista);
void punto2(nodo *lista);
void punto3(nodo *lista);
void punto4(nodo **lista);
void punto5(nodo **lista);
void punto6(nodo **lista);

int main()
{
    //nodo *lista=inicNodo();
    nodo *listaOrdenada=inicNodo();
    //crearListaCargada(&lista);
    crearListaCargadaOrdenada(&listaOrdenada);
    //mostrarListaRec(lista);
    mostrarListaRec(listaOrdenada);
    //punto1(lista);
    //punto2(lista);
    //punto3(lista);
    //punto4(&lista);
    //punto5(&listaOrdenada);
    //mostrarListaRec(listaOrdenada);
    //mostrarListaRec(lista);
    //eliminarListaRec(lista);
    //borrarLista(&lista);
    punto6(&listaOrdenada);
    mostrarListaRec(listaOrdenada);
    borrarLista(&listaOrdenada);
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

nodo *insertarOrdenadoRec(nodo *lista, nodo *nuevo)
{
    if(lista)
    {
        if(strcmpi(lista->palabra,nuevo->palabra)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarOrdenadoRec(lista->sig,nuevo);
        }
    }
    else
    {
        lista=nuevo;
    }
    return lista;
}

void *mostrarListaRec(nodo *lista)
{
    if(lista)
    {
        printf("%s %i \n",lista->palabra,lista->dato);
        mostrarListaRec(lista->sig);
    }
}

void *mostrarInvertidoRec(nodo *lista)
{
    if(lista)
    {

    }
}

void *mostrarPosParRec(nodo *lista, int pos)
{
    if(lista)
    {
        if(pos%2==0)
        {
            printf("%s %i \n",lista->palabra,lista->dato);
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
            lista->sig=borrarNodoRec(lista->sig,palabra);
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

void borrarLista(nodo **lista)
{
    if (*lista)
    {
        nodo *aux;
        while(aux)
        {
            aux=(*lista)->sig;
            free(*lista);
            *lista=aux;
        }
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

void crearListaCargadaOrdenada(nodo **lista)
{
    nodo *nuevo1=crearNodo(10,"Papas Fritas");
    nodo *nuevo2=crearNodo(20,"Chocolate negro");
    nodo *nuevo3=crearNodo(30,"Cerveza");
    nodo *nuevo4=crearNodo(40,"Frutas");
    nodo *nuevo5=crearNodo(50,"Panceta");
    nodo *nuevo6=crearNodo(60,"Fideos");
    nodo *nuevo7=crearNodo(70,"Helado");
    *lista=insertarOrdenadoRec(*lista,nuevo1);
    *lista=insertarOrdenadoRec(*lista,nuevo2);
    *lista=insertarOrdenadoRec(*lista,nuevo3);
    *lista=insertarOrdenadoRec(*lista,nuevo4);
    *lista=insertarOrdenadoRec(*lista,nuevo5);
    *lista=insertarOrdenadoRec(*lista,nuevo6);
    *lista=insertarOrdenadoRec(*lista,nuevo7);
}
void punto1(nodo *lista)
{
    printf("Lista invertida \n");
    nodo *invertido=invertirListaRec(lista,invertido);
    mostrarListaRec(invertido);
    eliminarListaRec(&invertido);
}
void punto2(nodo *lista)
{
    int sumatoria=0;
    sumatoria=sumarElementosListaRec(lista,sumatoria);
    printf("Valor de la sumatoria: %i \n",sumatoria);
}
void punto3(nodo *lista)
{
    printf("Mostrando nodos de posicion par: \n");
    mostrarPosParRec(lista,0);
}
void punto4(nodo **lista)
{
    char palabra[30];
    printf("Inserte una palabra a eliminar de la lista:");
    gets(palabra);
    *lista=borrarNodoRec(*lista,palabra);
}
void punto5(nodo **lista)
{
    int dato;
    char palabra[30];
    printf("Ingrese un dato entero: ");
    scanf("%d",&dato);
    fflush(stdin);
    printf("\n Ingrese una palabra: ");
    gets(palabra);

    nodo *nuevo=crearNodo(dato,palabra);
    *lista=insertarOrdenadoRec(*lista,nuevo);
}
void punto6(nodo **lista)
{
    nodo *resultante=inicNodo();
    *lista=invertirListaRec(*lista,resultante);
}
