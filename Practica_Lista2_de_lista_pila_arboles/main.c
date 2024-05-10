#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct  //Registro
{
    int id;
    char nombreProducto[80];
    char marca[50];
    float precio;
    char tipo[50];
}RegProducto;

typedef struct
{
    int id;
    char nombreProducto[80];
    char marca[50];
    float precio;
}Producto;

typedef struct //Lista Simple
{
    Producto p;
    struct nodoProducto *sig;
}nodoProducto;

typedef struct //Lista doble
{
    char tipo[50];
    nodoProducto *listaProductos;
    struct nodo2tipo *anterior;
    struct nodo2Tipo *siguiente;
}nodo2Tipo;

Producto crearProducto(int id,char nombreProducto[80],char marca[50],float precio);

nodoProducto *inicNodoProd();
nodoProducto *crearNodoProductos(Producto p);
nodoProducto *insertarProdOrdenado(nodoProducto *lista,nodoProducto *nuevo);
nodoProducto *insertarProdOrdenadoRec(nodoProducto *lista, nodoProducto *nuevo);
nodoProducto *buscarProducto(nodoProducto *lista,char nombreProducto[80]);
int *borrarNodoProducto(nodoProducto *lista,char nombreABorrar[80]);
void *borraListaProducto(nodoProducto *lista);
void mostrarProducto(nodoProducto *producto);

nodo2Tipo *inicNodo2Tipo();
nodo2Tipo *crearNodo2Tipo(char tipo[50]);
nodo2Tipo *agregarOrdenadoN2(nodo2Tipo *lista,nodo2Tipo *nuevo);
nodo2Tipo *agregarOrdenadoN2Rec(nodo2Tipo *lista,nodo2Tipo *nuevo);
nodo2Tipo *buscarTipo(nodo2Tipo *lista,char nombreTipo[50]);
nodo2Tipo *borrarTipo(nodo2Tipo *lista,char nombreTipo[50]);
nodo2Tipo *borrarListaTipo(nodo2Tipo *lista);
void mostrarListaTipo(nodo2Tipo *lista);





int main()
{
    int opcion;
    nodo2Tipo *lista=inicNodo2Tipo();
    do
    {

    }while(opcion!=88 && opcion!=120);
    return 0;
}

Producto crearProducto(int id,char nombreProducto[80],char marca[50],float precio)
{
    Producto nuevo;
    nuevo.id=id;
    strcpy(nuevo.marca,marca);
    strcpy(nuevo.nombreProducto,nombreProducto);
    nuevo.precio=precio;
    return nuevo;
}

nodoProducto *inicNodoProd()
{
    return NULL;
}

nodoProducto *crearNodoProductos(Producto p)
{
    nodoProducto *nuevo=(nodoProducto*)malloc(sizeof(nodoProducto));
    nuevo->p=p;
    return nuevo;
}

nodoProducto *insertarProdOrdenado(nodoProducto *lista,nodoProducto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->p.nombreProducto,nuevo->p.nombreProducto)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodoProducto *iterador=lista;
            nodoProducto *ante=lista;
            while(iterador!=NULL)
            {
                if(strcmpi(lista->p.nombreProducto,nuevo->p.nombreProducto)>0)
                {
                    ante->sig=nuevo;
                    nuevo->sig=iterador;
                }
            }
        }
    }
    return lista;
}
nodoProducto *insertarProdOrdenadoRec(nodoProducto *lista, nodoProducto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->p.nombreProducto,nuevo->p.nombreProducto)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarProdOrdenadoRec(lista->sig,nuevo);
        }
    }

    return lista;
}

nodoProducto *buscarProducto(nodoProducto *lista,char nombreProducto[80])
{
    nodoProducto *resultado=NULL;
    if(lista)
    {
        if(strcmpi(lista->p.nombreProducto,nombreProducto)==0)
        {
            resultado=lista;
        }
        else
        {
            nodoProducto *iterador=lista;
            while(iterador && resultado==NULL)
            {
                if(strcmpi(iterador->p.nombreProducto,nombreProducto)==0)
                {
                    resultado=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }
    return resultado;
}

int *borrarNodoProducto(nodoProducto *lista,char nombreABorrar[80])
{
    int borrado=0;
    if(lista)
    {
        if(strcmpi(lista->p.nombreProducto,nombreABorrar)==0)
        {
            nodoProducto *TEMP=lista;
            free(lista);
            lista=TEMP;
            borrado=1;
        }
        else
        {
            nodoProducto *iterador=lista;
            nodoProducto *ante=lista;
            while(iterador && borrado==0)
            {
                if(strcmpi(iterador->p.nombreProducto,nombreABorrar)==0)
                {
                    ante->sig=iterador->sig;
                    free(iterador);
                    borrado=1;
                }
                iterador=iterador->sig;
            }
        }
    }
    return borrado;
}

void *borraListaProducto(nodoProducto *lista)
{
    if(lista)
    {
        nodoProducto *aux;
        while(aux)
        {
            aux=lista->sig;
            free(lista);
            lista=aux;
        }
    }
}

void mostrarProducto(nodoProducto *producto);

nodo2Tipo *inicNodo2Tipo()
{
    return NULL;
}
nodo2Tipo *crearNodo2Tipo(char tipo[50]);
nodo2Tipo *agregarOrdenadoN2(nodo2Tipo *lista,nodo2Tipo *nuevo);
nodo2Tipo *agregarOrdenadoN2Rec(nodo2Tipo *lista,nodo2Tipo *nuevo);
nodo2Tipo *buscarTipo(nodo2Tipo *lista,char nombreTipo[50]);
nodo2Tipo *borrarTipo(nodo2Tipo *lista,char nombreTipo[50]);
nodo2Tipo *borrarListaTipo(nodo2Tipo *lista);
void mostrarListaTipo(nodo2Tipo *lista);
