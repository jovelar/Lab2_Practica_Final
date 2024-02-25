#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stRegistro;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;


typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;


typedef struct{
    int idSucursal;
    char nombreSucursal[25];
}stSucursal;

typedef struct{
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
}stProducto;



typedef struct
{
    stProducto producto;
    struct nodoProd *siguiente;
}nodoProd;

typedef struct
{
    stSucursal sucursal;
    nodoProd *productos;
}celdaSucursal;

int buscarSucursal(celdaSucursal sucursales[],int idSucursal);
stSucursal nuevoSTSucursal(int idSucursal,char nombreSucursal[25]);
celdaSucursal crearSucursal(stSucursal sucursal);


Fila pasarAFila(char nombreArchivo[20]);

nodo2 *inicNodo2();
nodo2 *crearNodo2(int idSucursal, char nombreSucursal[20],char nombreProducto[20],char deporte[25],int stockProducto);
nodo2 *agregarAlFinal(nodo2 *lista,nodo2 *nuevo);
void mostrarNodo2(nodo2 *nodo);
void mostrarNodo2Rec(nodo2 *nodo);
void mostrarDato(nodo2 dato);
void inicFila(Fila *fila);

void encolar(Fila *fila, nodo2 *nuevo);
void mostrarFila(Fila fila);

void ejercicio1(Fila *fila,char nombreArchivo[20]);
void ejercicio2(Fila fila);

//void pasarACSV(char archivoOrigen[40],char archivoDestino[40]);

int main()
{
    Fila nuevaFila;
    inicFila(&nuevaFila);
    char nombreArchivo[50]="archivoRegistrosIndumentaria.bin";
    ejercicio1(&nuevaFila,nombreArchivo);
    ejercicio2(nuevaFila);



    return 0;
}

nodo2 *inicNodo2()
{
    return NULL;
}
nodo2 *crearNodo2(int idSucursal, char nombreSucursal[20],char nombreProducto[20],char deporte[25],int stockProducto)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->idSucursal=idSucursal;
    strcpy(nuevo->nombreSucursal,nombreSucursal);
    strcpy(nuevo->nombreProducto,nombreProducto);
    strcpy(nuevo->deporte,deporte);
    nuevo->stockProducto=stockProducto;
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;

    return nuevo;
}

Fila pasarAFila(char nombreArchivo[20])
{
    Fila cargado;
    inicFila(&cargado);
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        nodo2 *nuevo;
        stRegistro buffer;
        while(fread(&buffer,sizeof(stRegistro),1,archivo)>0)
        {
            nuevo=crearNodo2(buffer.idSucursal,buffer.nombreSucursal,buffer.nombreProducto,buffer.deporte,buffer.stockProducto);
            encolar(&cargado,nuevo);
        }
        fclose(archivo);
    }
    else
        printf("\n el archivo no existe/no se pudo abrir ");

    return cargado;
}

nodo2 *agregarAlFinal(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        lista->siguiente=nuevo;
        nuevo->anterior=lista;
    }
    return nuevo;
}

void mostrarNodo2Rec(nodo2 *nodo)
{
    if(nodo)
    {
        mostrarDato(*nodo);
        mostrarNodo2Rec(nodo->siguiente);
    }
}

void mostrarDato(nodo2 dato)
{
        puts ("\n**********************************************************************************\n");
        printf ("\nId de la Sucursal……………………: %d \n", dato.idSucursal);
        printf("\nNombre de la Sucursal: ………….….:%s \n", dato.nombreSucursal);
        printf("\nNombre del Producto........................: %s \n ", dato.nombreProducto);
        printf("\nDeporte al que pertenece.................: %s \n ", dato.deporte);
        printf("\nStock del producto............................: %d \n", dato.stockProducto);
        puts ("\n**********************************************************************************\n");
}


void inicFila(Fila *fila)
{
    fila->primero=inicNodo2();
    fila->ultimo=inicNodo2();
}

void encolar(Fila *fila, nodo2 *nuevo)
{
    fila->ultimo=agregarAlFinal(fila->ultimo,nuevo);
    if(!fila->primero)
    {
        fila->primero=fila->ultimo;
    }
}


void ejercicio1(Fila *fila,char nombreArchivo[20])
{
    *fila=pasarAFila(nombreArchivo);
}

void ejercicio2(Fila fila)
{
    mostrarNodo2Rec(fila.primero);
}

/*void pasarACSV(char archivoOrigen[40],char archivoDestino[40])
{
    FILE *aOrigen=fopen(archivoOrigen,"rb");
    {
        if(aOrigen)
        {
            FILE *aDestino=fopen(archivoDestino,"wb");

            stRegistro buffer;

            while(fread(&buffer,sizeof(stRegistro),1,aOrigen)>0)
            {
                fprintf(aDestino,"%i;%s;%s;%s;%i\n",buffer.idSucursal,buffer.nombreSucursal,buffer.nombreProducto,buffer.deporte,buffer.stockProducto);
            }
            fclose(aDestino);
            fclose(aOrigen);
        }
    }
}
*/
