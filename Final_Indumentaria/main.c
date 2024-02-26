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



typedef struct //Nodos lista simple
{
    stProducto producto;
    struct nodoProd *siguiente;
}nodoProd;

typedef struct //Celda
{
    stSucursal sucursal;
    nodoProd *productos;
}celdaSucursal;

stProducto crearSTProducto(char nombreProducto[25],char deporte[25],int stockProducto);
nodoProd *crearNodoProd(char nombreProducto[25],char deporte[25],int stockProducto);
nodoProd *agregarProd(nodoProd *lista,nodoProd *producto);
int buscarSucursal(celdaSucursal sucursales[],int idSucursal,int validos);
stSucursal nuevoSTSucursal(int idSucursal,char nombreSucursal[25]);
celdaSucursal crearSucursal(stSucursal sucursal);

void pasarACelda(celdaSucursal celdas[],Fila fila,int validos);

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
void ejercicio3(celdaSucursal celdas[],Fila fila,int validos);
//void pasarACSV(char archivoOrigen[40],char archivoDestino[40]);

int main()
{
    Fila nuevaFila;
    inicFila(&nuevaFila);
    celdaSucursal celdas[200];
    int validos=0;
    char nombreArchivo[50]="archivoRegistrosIndumentaria.bin";
    ejercicio1(&nuevaFila,nombreArchivo);
    ejercicio2(nuevaFila);
    ejercicio3(celdas,nuevaFila,validos);



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
        printf ("\nId de la Sucursal: %d \n", dato.idSucursal);
        printf("\nNombre de la Sucursal: ..:%s \n", dato.nombreSucursal);
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

stProducto crearSTProducto(char nombreProducto[25],char deporte[25],int stockProducto)
{
    stProducto nuevoProducto;
    strcpy(&nuevoProducto.nombreProducto,nombreProducto);
    strcpy(&nuevoProducto.deporte,deporte);
    nuevoProducto.stockProducto=stockProducto;
    return nuevoProducto;
}

nodoProd *crearNodoProd(char nombreProducto[25],char deporte[25],int stockProducto)
{
    nodoProd *nuevoNodoProd=(nodoProd*)malloc(sizeof(nodoProd));
    nuevoNodoProd->producto=crearSTProducto(nombreProducto,deporte,stockProducto);

    return nuevoNodoProd;
}

nodoProd *agregarProd(nodoProd *lista,nodoProd *producto)
{
    if(!lista)
    {
        lista=producto;
    }
    else
    {
        nodoProd *iterador=lista;
        nodoProd *anterior=iterador;
        while(iterador)
        {
            anterior=iterador;
            iterador=iterador->siguiente;
        }
        anterior->siguiente=producto;
    }
    return lista;
}

int buscarSucursal(celdaSucursal sucursales[],int idSucursal,int validos)
{
    int ubicacion=-1; //-1 PARA DETERMINAR QUE NO SE ENCUENTRA EN NINGUNA PARTE
    int contador=0;
    while(ubicacion==-1 && contador<=validos)
    {
        if(sucursales[contador].sucursal.idSucursal==idSucursal)
        {
            ubicacion=contador;
        }
        contador++;
    }
    return ubicacion;
}


stSucursal nuevoSTSucursal(int idSucursal,char nombreSucursal[25])
{
    stSucursal nuevoSTSucursal;
    nuevoSTSucursal.idSucursal=idSucursal;
    strcpy(&nuevoSTSucursal.nombreSucursal,nombreSucursal);
    return nuevoSTSucursal;
}

celdaSucursal crearSucursal(stSucursal sucursal)
{
    celdaSucursal nuevaCelda;
    nuevaCelda.sucursal.idSucursal=sucursal.idSucursal;
    strcpy(&nuevaCelda.sucursal.nombreSucursal,sucursal.nombreSucursal);
    nuevaCelda.productos=NULL;
    return nuevaCelda;
}

void pasarACelda(celdaSucursal celdas[],Fila fila,int validos)
{
    int contador=0;
    int ubicacion=-1;
    nodo2 *listaSucursales=fila.primero;

    while(listaSucursales)
    {
        ubicacion=buscarSucursal(celdas,listaSucursales->idSucursal,validos);
        while(ubicacion==-1 && contador<=validos)
        {
            if(celdas[contador].sucursal.idSucursal==listaSucursales->idSucursal)
            {
                ubicacion=contador;
            }
        }
        if(ubicacion==-1)//SI NO EXISTE LA SUCURSAL
        {
            stSucursal sucursal=nuevoSTSucursal(listaSucursales->idSucursal,listaSucursales->nombreSucursal);
            celdaSucursal nuevaSucursal=crearSucursal(sucursal);
            celdas[validos]=nuevaSucursal;
        }
        else //SI ENCUENTRA LA SUCURSAL
        {
            stProducto nuevoProducto=crearSTProducto(listaSucursales->nombreProducto,listaSucursales->deporte,listaSucursales->stockProducto);
            nodoProd *nuevoNodoProd=nuevoNodoProd=crearNodoProd(listaSucursales->nombreProducto,listaSucursales->deporte,listaSucursales->stockProducto);
            celdas[ubicacion].productos=agregarProd(celdas[validos].productos,nuevoNodoProd);
        }
        ubicacion=-1;
        validos++;
        listaSucursales=listaSucursales->siguiente;

    }
}

void ejercicio3(celdaSucursal celdas[],Fila fila,int validos)
{
    pasarACelda(celdas,fila,validos);
}
