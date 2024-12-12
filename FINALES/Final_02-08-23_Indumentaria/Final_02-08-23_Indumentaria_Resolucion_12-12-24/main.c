#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stRegistro;

typedef struct
{
    stRegistro reg;
    struct nodo2 *ante;
    struct nodo2 *sig;
}nodo2;

typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
}stSucursal;

typedef struct
{
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stProducto;

typedef struct
{
    stSucursal suc;
    struct producto *listaProd;
}celda;

typedef struct
{
    stProducto prod;
    struct producto *sig;
}producto;

//Punto1
//{
nodo2 *crearNodo2(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto);
nodo2 *insertarAlFinal(nodo2 *lista,nodo2 *nuevo);
void inicFila(Fila *fila);
void encolar(Fila *fila,nodo2 *nuevo);
void pasarAFILA(char nombreArchivo[50],Fila *fila);
void punto1(char nombreArchivo[25],Fila *fila);
//}

//Punto 2
//{
void mostrarRegistro(stRegistro dato);
void mostrarFilaRec(nodo2 *lista);
void punto2(Fila *fila);
//}

//Punto 3
//{
celda crearCelda(int idSucursal,char nombreSucursal[25]);
int buscarSucursal(celda arregloSuc[],int idSucursal,int validos);
int agregarSuc(celda arregloSuc[],celda nuevo,int validos);
producto *crearProducto(char nombre[25],char deporte[25],int stock);
producto *agregarOrdProd(producto *lista,producto *nuevo);
int pasarAADL(Fila *fila,celda arreglo[],int validos);
void punto3(Fila *fila,celda arreglo[],int *validos);
//}

//Punto4
//{
void mostrarProducto(stProducto prod);
void mostrarSuc(stSucursal suc);
void mostrarLista(producto *lista);
void mostrarArreglo(celda arreglo[],int validos);
void punto4(celda arreglo[],int validos);
//}

//Punto 5
//{
int stockRecursivo(producto *lista,int sumatoria,char nombre[25],char deporte[25]);
void punto5(celda arreglo[],int validos);
//}

int main()
{
    return 0;
}

//Punto1
//{
nodo2 *crearNodo2(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->reg.idSucursal=idSucursal;
    strcpy(nuevo->reg.nombreSucursal,nombreSucursal);
    strcpy(nuevo->reg.nombreProducto,nombreProducto);
    strcpy(nuevo->reg.deporte,deporte);
    nuevo->reg.stockProducto=stockProducto;
    nuevo->ante=NULL;
    nuevo->sig=NULL;
    return nuevo;
}
nodo2 *insertarAlFinal(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo2 *aux=lista;
        nodo2 *ante;
        while(aux->sig)
        {
            aux=aux->sig;
        }
        aux->sig=nuevo;
        nuevo->ante=aux;
    }
    return lista;
}

void inicFila(Fila *fila)
{
    fila->primero=NULL;
    fila->ultimo=NULL;
}

void encolar(Fila *fila,nodo2 *nuevo)
{
    fila->ultimo=insertarAlFinal(fila->ultimo,nuevo);
    if(!fila->primero)
    {
        fila->primero=fila->ultimo;
    }
}

void pasarAFILA(char nombreArchivo[50],Fila *fila)
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistro buffer;
        while(fread(&buffer,sizeof(stRegistro),1,archivo)>0)
        {
            nodo2 *nuevo=crearNodo2(buffer.idSucursal,buffer.nombreSucursal,buffer.nombreProducto,buffer.deporte,buffer.stockProducto);
            encolar(fila,nuevo);
        }
        fclose(archivo);
    }
}
void punto1(char nombreArchivo[25],Fila *fila)
{
    pasarAFILA(nombreArchivo,fila);
}
//}

//Punto 2
//{
void mostrarRegistro(stRegistro dato)
{
    puts ("\n**********************************************************************************\n");
    printf ("\nId de la Sucursal……………………: %d \n", dato.idSucursal);
    printf("\nNombre de la Sucursal: ………….….:%s \n", dato.nombreSucursal);
    printf("\nNombre del Producto........................: %s \n ", dato.nombreProducto);
    printf("\nDeporte al que pertenece.................: %s \n ", dato.deporte);
    printf("\nStock del producto............................: %d \n", dato.stockProducto);
    puts ("\n**********************************************************************************\n");
}

void mostrarFilaRec(nodo2 *lista)
{
    if(lista)
    {
        mostrarRegistro(lista->reg);
        mostrarFilaRec(lista->sig);
    }
}

void punto2(Fila *fila)
{
    mostrarFilaRec(fila->primero);
}
//}

//Punto 3
//{
celda crearCelda(int idSucursal,char nombreSucursal[25])
{
    celda nuevo;
    nuevo.suc.idSucursal=idSucursal;
    strcpy(nuevo.suc.nombreSucursal,nombreSucursal);
    return nuevo;
}

int buscarSucursal(celda arregloSuc[],int idSucursal,int validos)
{
    int posicion=-1;
    int contador=0;
    while(contador<validos && posicion==-1)
    {
        if(arregloSuc[contador].suc.idSucursal==idSucursal)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

int agregarSuc(celda arregloSuc[],celda nuevo,int validos)
{
    arregloSuc[validos]=nuevo;
    return validos++;
}

producto *crearProducto(char nombre[25],char deporte[25],int stock)
{
    producto *nuevo=(producto*)malloc(sizeof(producto));
    strcpy(nuevo->prod.nombreProducto,nombre);
    strcpy(nuevo->prod.deporte,deporte);
    nuevo->prod.stockProducto=stock;
    nuevo->sig=NULL;

    return nuevo;
}

producto *agregarOrdProd(producto *lista,producto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        producto *ante;
        producto *iterador=lista;
        while(iterador && strcmpi(iterador->prod.nombreProducto,nuevo->prod.nombreProducto)>=0)
        {
            ante=iterador;
            iterador=iterador->sig;
        }
        ante->sig=nuevo;
        nuevo->sig=iterador;
    }
    return lista;
}

int pasarAADL(Fila *fila,celda arreglo[],int validos)
{
    nodo2 *iterador=fila->primero;
    while(iterador)
    {
        producto *nuevoProd=crearProducto(iterador->reg.nombreProducto,iterador->reg.deporte,iterador->reg.stockProducto);
        int sucursal=buscarSucursal(arreglo,iterador->reg.idSucursal,validos);
        if(sucursal==-1)
        {
            celda nuevaSuc=crearCelda(iterador->reg.idSucursal,iterador->reg.nombreSucursal);
            arreglo[validos]=nuevaSuc;
            sucursal=validos;
            validos++;
        }
        arreglo[sucursal].listaProd=agregarOrdProd(arreglo[sucursal].listaProd,nuevoProd);
        iterador=iterador->sig;
    }
    return  validos;
}
void punto3(Fila *fila,celda arreglo[],int *validos)
{
  *validos=pasarAADL(fila,arreglo,validos);
}
//}

//Punto4
//{
void mostrarProducto(stProducto prod)
{
    printf("NOMBRE: %s DEPORTE: %s STOCK: %i \n",prod.nombreProducto,prod.deporte,prod.stockProducto);
}

void mostrarSuc(stSucursal suc)
{
    printf("******** ID: %i NOMBRE SUCURSAL: %s ********\n",suc.idSucursal,suc.nombreSucursal);
}

void mostrarLista(producto *lista)
{
    if(lista)
    {
        producto *iterador=lista;
        while(iterador)
        {
            mostrarProducto(iterador->prod);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("Lista productos vacia! ");
    }
}

void mostrarArreglo(celda arreglo[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarSuc(arreglo[x].suc);
        mostrarLista(arreglo[x].listaProd);
    }
}

void punto4(celda arreglo[],int validos)
{
    mostrarArreglo(arreglo,validos);
}
//}

//Punto 5
//{
int stockRecursivo(producto *lista,int sumatoria,char nombre[25],char deporte[25])
{
    if(lista)
    {
        if(strcmpi(lista->prod.nombreProducto,nombre)==0 && strcmpi(lista->prod.deporte,deporte)==0)
        {
            sumatoria=sumatoria + lista->prod.stockProducto;
        }
        sumatoria=stockRecursivo(lista->sig,sumatoria,nombre,deporte);
    }
    return sumatoria;
}

void punto5(celda arreglo[],int validos)
{

}
//}
