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
    stRegistro dato;
    struct nodo2 *siguiente;
    struct nodo2 *anterior;
}nodo2;

typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

//Ejercicio 1

nodo2 *inicNodo2();
stRegistro nuevoRegistro(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto);
nodo2 *nuevoNodo2(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto);
nodo2 *agregarFinalNodo2(nodo2 *lista,nodo2 *nuevo);
void pasarAFila(Fila *fila,char nombreArchivo[50]);
void inicFila(Fila *fila);
void encolar(Fila *fila,nodo2 *nuevo);
void ejercicio1(Fila *fila,char nombreArchivo[25]);


//Ejercicio 2
void mostrarFilaRec(Fila *fila);
void ejercicio2(Fila *fila);

//Ejercicio3
typedef struct
{
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
    struct stProducto *sig;
}stProducto;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    stProducto *listaProducto;
}stSucursal;

//arreglo
stSucursal crearSucursal(int idSucursal,char nombreSucursal[25]);
int buscarSucursal(stSucursal arreglo[],int validos,char nombreSucursal[25]);


//Lista
stProducto *inicLista();
stProducto *crearProducto(char nombreProducto[25],char deporte[25],int stockProducto);
stProducto *agregarOrdenado(stProducto *lista,stProducto *nuevo);

void pasarAADL(Fila *fila,stSucursal arreglo[],int *validos);

void mostrarProducto(stProducto *producto);
void mostrarLista(stProducto *lista);
void mostrarArreglo(stSucursal arreglo[],int validos);

void ejercicio3(Fila *fila,stSucursal arreglo[], int *validos);

//Ejercicio4
void mostrarProducto(stProducto *producto);
void mostrarLista(stProducto *lista);
void mostrarArreglo(stSucursal arreglo[],int validos);
void ejercicio4(stSucursal arreglo[],int validos);

//Ejercicio5
int buscarStockRecursivo(stProducto *lista,int sumatoria, char producto[25],char deporte[25]);
void ejercicio5(stSucursal arreglo[],int validos);


int main()
{
    Fila fila;
    stSucursal arreglo[1000];
    int validos=0;
    inicFila(&fila);
    char nombreArchivo[]="archivoRegistrosIndumentaria.bin";

    ejercicio1(&fila,nombreArchivo);
    ejercicio2(&fila);
    ejercicio3(&fila,arreglo,&validos);
    ejercicio4(arreglo,validos);
    ejercicio5(arreglo,validos);
    return 0;
}

//Ejercicio 1

nodo2 *inicNodo2()
{
    return NULL;
}

stRegistro nuevoRegistro(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto)
{
    stRegistro nuevo;
    nuevo.idSucursal=idSucursal;
    strcpy(&nuevo.nombreSucursal,nombreSucursal);
    strcpy(&nuevo.nombreProducto,nombreProducto);
    strcpy(&nuevo.deporte,deporte);
    nuevo.stockProducto=stockProducto;

    return nuevo;
}

nodo2 *nuevoNodo2(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->dato=nuevoRegistro(idSucursal,nombreSucursal,nombreProducto,deporte,stockProducto);
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodo2 *agregarFinalNodo2(nodo2 *lista,nodo2 *nuevo)
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

void pasarAFila(Fila *fila,char nombreArchivo[50])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistro buffer;
        while(fread(&buffer,sizeof(stRegistro),1,archivo)>0)
        {
            nodo2 *nuevo=nuevoNodo2(buffer.idSucursal,buffer.nombreSucursal,buffer.nombreProducto,buffer.deporte,buffer.stockProducto);
            encolar(fila,nuevo);
        }
        fclose(archivo);
    }
}

void inicFila(Fila *fila)
{
    fila->primero=NULL;
    fila->ultimo=NULL;
}

void encolar(Fila *fila,nodo2 *nuevo)
{
    if(!fila->primero)
    {
        fila->primero=nuevo;
        fila->ultimo=nuevo;
    }
    else
    {
        fila->primero=agregarFinalNodo2(fila->primero,nuevo);
        fila->ultimo=nuevo;
    }
}

void ejercicio1(Fila *fila,char nombreArchivo[25])
{
    pasarAFila(fila,nombreArchivo);
}

//Ejercicio2
void mostrarFilaRec(Fila *fila)
{
    if(fila->primero)
    {
        stRegistro dato=fila->primero->dato;
        puts ("\n**********************************************************************************\n");
        printf ("\nId de la Sucursal……………………: %d \n", dato.idSucursal);
        printf("\nNombre de la Sucursal: ………….….:%s \n", dato.nombreSucursal);
        printf("\nNombre del Producto........................: %s \n ", dato.nombreProducto);
        printf("\nDeporte al que pertenece.................: %s \n ", dato.deporte);
        printf("\nStock del producto............................: %d \n", dato.stockProducto);
        puts ("\n**********************************************************************************\n");

        Fila filaAux;             //Fila auxiliar para recorrer sin alterar la original
        nodo2 *aux=fila->primero; //nodo doble auxiliar para iterar sin alterar la original
        aux=aux->siguiente;       //se avanza a la siguiente posicion del nodo primero de la fila
        filaAux.primero=aux;
        mostrarFilaRec(&filaAux);
    }
}

void ejercicio2(Fila *fila)
{
    mostrarFilaRec(fila);
}
//arreglo
stSucursal crearSucursal(int idSucursal,char nombreSucursal[25])
{
    stSucursal nuevo;
    nuevo.idSucursal=idSucursal;
    strcpy(&nuevo.nombreSucursal,nombreSucursal);
    nuevo.listaProducto=NULL;
    return nuevo;
}
int buscarSucursal(stSucursal arreglo[],int validos,char nombreSucursal[25])
{
    int posicion=-1;
    int contador=0;
    while(contador<validos && posicion==-1)
    {
        if(strcmpi(arreglo[contador].nombreSucursal,nombreSucursal)==0)
        {
            posicion=contador;
        }
        contador++;
    }

    return posicion;
}

//Lista
stProducto *inicLista()
{
    return NULL;
}

stProducto *crearProducto(char nombreProducto[25],char deporte[25],int stockProducto)
{
    stProducto *nuevo=(stProducto*)malloc(sizeof(stProducto));
    strcpy(nuevo->nombreProducto,nombreProducto);
    strcpy(nuevo->deporte,deporte);
    nuevo->stockProducto=stockProducto;
    nuevo->sig=NULL;
    return nuevo;
}

stProducto *agregarOrdenado(stProducto *lista,stProducto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->nombreProducto,nuevo->nombreProducto)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            stProducto *iterador=lista->sig;
            stProducto *ante=lista;
            while(iterador && strcmpi(iterador->nombreProducto,nuevo->nombreProducto)<0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            if(!iterador)
            {
                ante->sig=nuevo;
            }
            else
            {
                ante->sig=nuevo;
                nuevo->sig=iterador;
            }
        }

    }
    return lista;
}

void pasarAADL(Fila *fila,stSucursal arreglo[],int *validos)
{
    if(fila)
    {
        nodo2 *iterador=fila->primero;
        while(iterador)
        {
            stProducto *nuevoProducto=crearProducto(iterador->dato.nombreProducto,iterador->dato.deporte,iterador->dato.stockProducto);
            int posSucursal=buscarSucursal(arreglo,*validos,iterador->dato.nombreSucursal);
            if(posSucursal==-1)
            {
                stSucursal nuevaSucursal=crearSucursal(iterador->dato.idSucursal,iterador->dato.nombreSucursal);
                arreglo[*validos]=nuevaSucursal;
                posSucursal=*validos;
                (*validos)++;

            }
            arreglo[posSucursal].listaProducto=agregarOrdenado(arreglo[posSucursal].listaProducto,nuevoProducto);
            iterador=iterador->siguiente;
        }
    }
}



void ejercicio3(Fila *fila,stSucursal arreglo[], int *validos)
{
    pasarAADL(fila,arreglo,validos);
}

stProducto *agregarAlFinal(stProducto *lista, stProducto *nuevo)
{
    if(!lista)
    {
        nuevo->sig=lista;
        lista=nuevo;
    }
    else
    {
        stProducto *iterador=lista;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }
    return lista;
}

//Ejercicio4
void mostrarProducto(stProducto *producto)
{
    printf("%s %s %i\n",producto->deporte,producto->nombreProducto,producto->stockProducto);
}

void mostrarLista(stProducto *lista)
{
    if(lista)
    {
        stProducto *iterador=lista;
        while(iterador)
        {
            mostrarProducto(iterador);
            iterador=iterador->sig;
        }
    }
}

void mostrarArreglo(stSucursal arreglo[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        printf("\n ######################### %s #########################\n",arreglo[x].nombreSucursal);
        mostrarLista(arreglo[x].listaProducto);
    }
}

void ejercicio4(stSucursal arreglo[],int validos)
{
    mostrarArreglo(arreglo,validos);
}

//Ejercicio5
int buscarStockRecursivo(stProducto *lista,int sumatoria, char producto[25],char deporte[25])
{
    int stock=0;
    if(!lista)
    {
        stock=sumatoria;
    }
    else
    {
        //STRSTR busca un string dentro de otro,se puede usar para comparar 2 strings, dado que si encuentra la segunda cadena
        //en la primera, devuelve un puntero a la primer posicion donde se encuentra el string.
        if(strstr(lista->deporte,deporte)!=NULL && strstr(lista->nombreProducto,producto)!=NULL)
        {
            sumatoria+=lista->stockProducto;
        }
            stock=buscarStockRecursivo(lista->sig,sumatoria,producto,deporte);
    }
    return stock;
}
void ejercicio5(stSucursal arreglo[],int validos)
{
    char deporte[25];
    char producto[25];
    char sucursal[25];
    int stock=-1;
    printf("Ingrese la sucursal a buscar: \n");
    fflush(stdin);
    gets(sucursal);
    printf("\n Ingrese el deporte al que pertenece el producto: \n");
    fflush(stdin);    gets(deporte);
    printf("\nIngrese el nombre del producto: \n");
    fflush(stdin);
    gets(producto);

    int posicion=buscarSucursal(arreglo,validos,sucursal);
    if(posicion!=-1)
    {
        stock=buscarStockRecursivo(arreglo[posicion].listaProducto,0,producto,deporte);
        printf("\nEl stock es de: %i \n",stock);
    }
    else
    {
        printf("\n no encontrado \n");
    }
}
