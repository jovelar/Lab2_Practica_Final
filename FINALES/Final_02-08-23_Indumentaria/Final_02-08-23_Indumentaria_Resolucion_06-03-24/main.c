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
    nodo2 *inicio;
    nodo2 *fin;
}fila;


nodo2 *crearNodo2Nuevo(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto);
nodo2 *agregarAlFinal(nodo2 *fin,nodo2 *nuevo);
nodo2 *inicNodo2();

void inicFila(fila *fila);
void encolar(fila*fila,nodo2 *nuevoNodo2);
nodo2 *desencolar(fila *fila);

void pasarAFila(fila *fila,char nombreArchivo[40]);

void mostrarDato(nodo2 dato);
void mostrarDatoRec(nodo2 *lista);

//PUNTO 3

typedef struct
{
    char nombreProducto[25];
    char deporte[25];
    int stockProducto;
    struct stProducto *siguiente;
}stProducto;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    stProducto *listaProductos;
}stSucursal;

stProducto *inicProducto();
stProducto *nuevoProducto(char nombreProducto[25],char deporte[25],int stockProducto);
stProducto *agregarOrdenado(stProducto *lista, stProducto *nuevo);

stSucursal nuevaSucursal(int idSucursal,char nombreSucursal[25]);
void agregarSucursal(stSucursal sucursales[],stSucursal nuevaSuc,int validos);


void pasarAArreglo(fila *fila,stSucursal arreglo[],int *validos);
//Punto 4

void mostrarSucursal(stSucursal sucursal);
void mostrarProducto(stProducto *producto);
void mostrarListaProductos(stProducto *lista);
void mostrarADL(stSucursal arreglo[],int validos);

//Punto 5

int buscarSucursalADL(stSucursal sucursales[],int validos,char nombreSucursal[25]);

int stockRec(stProducto *listaProd,char nombreDeporte[25],char nombreProducto[25]);

//PUNTO 6 DE PRUEBA NO PERTECE AL FINAL

int stockRecTipo(stProducto *listaProductos,char nombreProducto[25]);

void ejercicio1(fila *fila,char nombreArchivo[40]);
void ejercicio2(fila *fila);
void ejercicio3(stSucursal arreglo[],fila *fila,int *validos);
void ejercicio4(stSucursal sucursales[],int validos);
void ejercicio5(stSucursal sucursales[],int validos);
void ejercicio6(stSucursal sucursales[],int validos);


int main()
{
    fila filaMain;
    inicFila(&filaMain);

    char nombreArchivo[40]="archivoRegistrosIndumentaria.bin";

    ejercicio1(&filaMain,nombreArchivo);
    ejercicio2(&filaMain);
    int validos=0;
    stSucursal arreglo[200];
    ejercicio3(arreglo,&filaMain,&validos);
    ejercicio4(arreglo,validos);
    ejercicio5(arreglo,validos);
    //ejercicio6(arreglo,validos);

    return 0;
}

nodo2 *crearNodo2Nuevo(int idSucursal,char nombreSucursal[25],char nombreProducto[25],char deporte[25],int stockProducto)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->idSucursal=idSucursal;
    strcpy(nuevo->nombreSucursal,nombreSucursal);
    strcpy(nuevo->deporte,deporte);
    strcpy(nuevo->nombreProducto,nombreProducto);
    nuevo->stockProducto=stockProducto;

    nuevo->siguiente=NULL;
    nuevo->anterior=NULL;
    return nuevo;
}

nodo2 *agregarAlFinal(nodo2 *fin,nodo2 *nuevo)
{
    if(!fin)
    {
        fin=nuevo;
    }
    else

    {
        fin->siguiente=nuevo;
        nuevo->anterior=fin;
        fin=nuevo;
    }
    return fin;
}

nodo2 *inicNodo2()
{
    return NULL;
}

void inicFila(fila *fila)
{
    fila->inicio=inicNodo2();
    fila->fin=inicNodo2();
}

void encolar(fila *fila,nodo2 *nuevoNodo2)
{
    fila->fin=agregarAlFinal(fila->fin,nuevoNodo2);

    if(!fila->inicio)
    {
        fila->inicio=fila->fin;
    }
    //printf("\n Ultimo cargado %i %s %s %s %i ",fila->fin->idSucursal,fila->fin->nombreSucursal,fila->fin->deporte,fila->fin->nombreProducto,fila->fin->stockProducto);
}
nodo2 *desencolar(fila *fila)
{
    nodo2 *desencolado=NULL;
    if(!fila->inicio)
    {

        desencolado=(nodo2*)malloc(sizeof(nodo2));
        desencolado->idSucursal=fila->inicio->idSucursal;
        strcpy(desencolado->nombreSucursal,fila->inicio->nombreSucursal);
        strcpy(desencolado->deporte,fila->inicio->deporte);
        strcpy(desencolado->nombreProducto,fila->inicio->nombreProducto);
        desencolado->stockProducto=fila->inicio->stockProducto;
    }
    return desencolado;
}

void pasarAFila(fila *fila,char nombreArchivo[40])
{
    if(fila)
    {
        FILE *archivo=fopen(nombreArchivo,"rb");
        if(archivo)
        {
            stRegistro buffer;

            while(fread(&buffer,sizeof(stRegistro),1,archivo)>0)
            {
                nodo2 *nuevo=crearNodo2Nuevo(buffer.idSucursal,buffer.nombreSucursal,buffer.nombreProducto,buffer.deporte,buffer.stockProducto);
                encolar(fila,nuevo);
            }
            fclose(archivo);
        }
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

void mostrarDatoRec(nodo2 *lista)
{
    if(lista)
    {
        mostrarDato(*lista);
        mostrarDatoRec(lista->siguiente);
    }
}

stProducto *inicProducto()
{
    return NULL;
}

stProducto *nuevoProducto(char nombreProducto[25],char deporte[25],int stockProducto)
{
    stProducto *nuevo=(stProducto*)malloc(sizeof(stProducto));
    strcpy(nuevo->nombreProducto,nombreProducto);
    strcpy(nuevo->deporte,deporte);
    nuevo->stockProducto=stockProducto;
    nuevo->siguiente=NULL;

    return nuevo;
}

stProducto *agregarOrdenado(stProducto *lista, stProducto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->deporte,nuevo->deporte)>0)
        {
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else
        {
            stProducto *anterior=lista;
            stProducto *iterador=lista->siguiente; //saltea el primero dado que no es el indicado
            while(iterador && strcmpi(iterador->deporte,nuevo->deporte)<0)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            if(!iterador)
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

stSucursal nuevaSucursal(int idSucursal,char nombreSucursal[25])
{
    stSucursal nuevo;

    nuevo.idSucursal=idSucursal;
    strcpy(nuevo.nombreSucursal,nombreSucursal);
    nuevo.listaProductos=NULL;

    return nuevo;
}

void agregarSucursal(stSucursal sucursales[],stSucursal nuevaSuc,int validos)
{
    sucursales[validos]=nuevaSuc;
}

int buscarSucursal(stSucursal sucursales[],int idSucursal, int validos)
{
    int posicion=-1;

    int contador=0;

    while(contador<validos && posicion==-1)
    {
        if(sucursales[contador].idSucursal==idSucursal)
        {
            posicion=contador;
        }
        contador++;
    }

    return posicion;
}

void pasarAArreglo(fila *fila,stSucursal arreglo[],int *validos)
{
    nodo2 *iterador=fila->inicio;
    int posicion;
    int leyendo=0;
    while(iterador)
    {
            stProducto *nuevoProd=nuevoProducto(iterador->nombreProducto,iterador->deporte,iterador->stockProducto);
            posicion=buscarSucursal(arreglo,iterador->idSucursal,*validos);

                if(posicion==-1)
                {
                    stSucursal nuevaSuc=nuevaSucursal(iterador->idSucursal,iterador->nombreSucursal);
                    agregarSucursal(arreglo,nuevaSuc,*validos);
                    posicion=*validos;
                    (*validos)++;
                }
                arreglo[posicion].listaProductos=agregarOrdenado(arreglo[posicion].listaProductos,nuevoProd);

            iterador=iterador->siguiente;

    }
}
void ejercicio1(fila *fila,char nombreArchivo[40])
{
    pasarAFila(fila,nombreArchivo);
}
void ejercicio2(fila *fila)
{
    mostrarDatoRec(fila->inicio);
}
void ejercicio3(stSucursal arreglo[],fila *fila,int *validos)
{
    pasarAArreglo(fila,arreglo,validos);
}

void mostrarSucursal(stSucursal sucursal)
{
    printf("\n********************************************");
    printf("\n******* SUCURSAL %s  IDSUC %i *******",sucursal.nombreSucursal,sucursal.idSucursal);
    printf("\n********************************************");
}

void mostrarProducto(stProducto *producto)
{
    printf("\n %-20s | %-20s | %-3i ",producto->deporte,producto->nombreProducto,producto->stockProducto);
}
void mostrarListaProductos(stProducto *lista)
{
    stProducto *iterador=lista;

    if(iterador)
    {
        while (iterador)
        {
            mostrarProducto(iterador);
            iterador=iterador->siguiente;
        }
    }
}

void mostrarADL(stSucursal arreglo[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarSucursal(arreglo[x]);
        mostrarListaProductos(arreglo[x].listaProductos);
    }
}

void ejercicio4(stSucursal sucursales[],int validos)
{
    mostrarADL(sucursales,validos);
}

int buscarSucursalADL(stSucursal sucursales[],int validos,char nombreSucursal[25])
{
    int posicion=-1;
    int contador=0;
    while(contador<validos &&  posicion==-1)
    {
        if(strcmp(sucursales[contador].nombreSucursal,nombreSucursal)==0)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

int stockRec(stProducto *listaProd,char nombreDeporte[25],char nombreProducto[25])
{
    int stock=0;
    if(listaProd)
    {
        if(strcmpi(listaProd->deporte,nombreDeporte)==0 && strstr(listaProd->nombreProducto,nombreProducto)!=NULL)
        {
            stock=stock+listaProd->stockProducto;
        }
        stock+= stockRec(listaProd->siguiente,nombreDeporte,nombreProducto);
    }
    return stock;
}

void ejercicio5(stSucursal sucursales[],int validos)
{
    char nombreDeporte[25];
    char nombreProducto[25];
    char nombreSucursal[25];
    int stock=0;
    printf("\nIngrese el nombre de la sucursal: ");
    scanf("%s",nombreSucursal);
    printf("\nIngrese el nombre del deporte: ");
    scanf("%s",nombreDeporte);
    printf("\nIngrese el nombre del producto: ");
    scanf("%s",nombreProducto);

    int ubicacionSuc=buscarSucursalADL(sucursales,validos,nombreSucursal);
    if(ubicacionSuc!=-1)
    {
        stock=stockRec(sucursales[ubicacionSuc].listaProductos,nombreDeporte,nombreProducto);

        printf("\n Deporte: %s | Producto: %s | Stock Sumatoria: %i",nombreDeporte,nombreProducto,stock);
    }
    else
    {
        printf("\nNo se encontro la sucursal.");
    }

}


//FUNCION DE PRUEBA SOLO PARA PROBAR RECURSIVIDAD
/*
int stockRecTipo(stProducto *listaProductos,char nombreProducto[25])
{
    int recuento=0;
    if(listaProductos)
    {
        if(strstr(listaProductos->nombreProducto,nombreProducto)!=NULL)
        {
            recuento+=listaProductos->stockProducto;
        }
        recuento+= stockRecTipo(listaProductos->siguiente,nombreProducto);
    }
    return recuento;
}


void ejercicio6(stSucursal sucursales[],int validos)
{
    char nombreProducto[25];
    char nombreSucursal[25];
    int stock=0;
    printf("\nIngrese el nombre de la sucursal: ");
    gets(nombreSucursal);
    printf("\nIngrese el nombre del producto: ");
    scanf("%s",nombreProducto);

    int ubicacionSuc=buscarSucursalADL(sucursales,validos,nombreSucursal);
    if(ubicacionSuc!=-1)
    {
        stock=stockRecTipo(sucursales[ubicacionSuc].listaProductos,nombreProducto);

        printf("\nProducto: %s | Stock Sumatoria: %i",nombreProducto,stock);
    }
    else
    {
        printf("\nNo se encontro la sucursal.");
    }

}
*/
