#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
}stRegistroDisfraz;

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
}stSucursal;

typedef struct
{
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
}stDisfraz;

typedef struct
{
    stSucursal sucursal;
    stSucursal *ante;
    stSucursal *sig;
    struct nodo *listaDisfraz;
}nodo2;

typedef struct
{
    stDisfraz disfraz;
    stDisfraz *sig;
}nodo;

typedef struct
{
    stRegistroDisfraz registro;
    struct Arbol *izq;
    struct Arbol *der;
}Arbol;

//Punto 1
//{
nodo2 *inicNodo2();
nodo2 *buscarN2(nodo2 *lista,char nombreSucursal[25]);
nodo2 *insertarOrdenadoN2(nodo2 *lista,nodo2 *nuevo);
nodo2 *crearNodo2(int idSucursal,char nombreSucursal[25]);

nodo *inicNodo();
nodo *crearNodo(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz);
nodo *insertarOrdenadoN(nodo *lista,nodo *nuevo);

nodo2 *pasarALDL(char nombreArchivo[25]);

void punto1(char nombreArchivo[25],nodo2 **lista);
//}

//Punto2
//{
void mostrarSucursal(stSucursal dato);
void mostrarLista(nodo2 *lista);
void mostrarDisfraz(stDisfraz dato);
void mostrarListaDis(nodo *lista);

void punto2(nodo2 *lista);
//}

//Punto3
//{
Arbol *inicArbol();
Arbol *crearArbol(int idSucursal,char nombreSucursal[25],char nombreDisfraz[25],char generoDisfraz[25],int stock);
Arbol *insertarOrdArbol(Arbol *arbol,Arbol *nuevo);
Arbol *pasarAArbol(Arbol *arbol,nodo2 *lista);
void punto3(Arbol **arbol,nodo2 *lista);
//}

//Punto4
//{
void mostrarSTReg(stRegistroDisfraz registro);
void mostrarArbol(Arbol *arbol);
void punto4(Arbol *arbol);
//}

//Punto 5
//{
void buscarDisfraz(Arbol *arbol,char nombre[25],char genero[25]);
void punto5(Arbol *arbol);
//}

int main()
{
    nodo2 *lista=inicNodo2();
    char nombreArchivo[]="archivoRegistrosDisfraces.bin";
    punto1(nombreArchivo,&lista);
    punto2(lista);
    Arbol *arbol=inicArbol();
    punto3(&arbol,lista);
    punto4(arbol);
    punto5(arbol);
    return 0;
}

//Punto 1
//{
nodo2 *inicNodo2()
{
    return NULL;
}

nodo2 *buscarN2(nodo2 *lista,char nombreSucursal[25])
{
    nodo2 *lugar=NULL;
    if(lista)
    {
        nodo2 *aux=lista;
        while(aux && !lugar)
        {
            if(strcmpi(aux->sucursal.nombreSucursal,nombreSucursal)==0)
            {
                lugar=aux;
            }
            aux=aux->sig;
        }
    }
    return lugar;
}
nodo2 *insertarOrdenadoN2(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->sucursal.nombreSucursal,nuevo->sucursal.nombreSucursal)>0)
        {
            nuevo->sig=lista;
            lista->ante=nuevo;
            lista=nuevo;
        }
        else
        {
            nodo2 *aux=lista;
            nodo2 *ante;
            while(aux && strcmpi(aux->sucursal.nombreSucursal,nuevo->sucursal.nombreSucursal)<0)
            {
                ante=aux;
                aux=aux->sig;
            }
            ante->sig=nuevo;
            nuevo->ante=ante;
            nuevo->sig=aux;
            if(aux)
            {
                aux->ante=nuevo;
            }

        }
    }
    return lista;
}

nodo2 *crearNodo2(int idSucursal,char nombreSucursal[25])
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->ante=NULL;
    nuevo->sig=NULL;
    nuevo->sucursal.idSucursal=idSucursal;
    strcpy(nuevo->sucursal.nombreSucursal,nombreSucursal);
    nuevo->listaDisfraz=NULL;
    return nuevo;
}

nodo *inicNodo()
{
    return NULL;
}

nodo *crearNodo(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz)
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->sig=NULL;
    strcpy(nuevo->disfraz.nombreDisfraz,nombreDisfraz);
    strcpy(nuevo->disfraz.generoDisfraz,generoDisfraz);
    nuevo->disfraz.stockDisfraz=stockDisfraz;

    return nuevo;
}

nodo *insertarOrdenadoN(nodo *lista,nodo *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->disfraz.nombreDisfraz,nuevo->disfraz.nombreDisfraz)>=0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodo *aux=lista;
            nodo *ante;
            while(aux && strcmpi(aux->disfraz.nombreDisfraz,nuevo->disfraz.nombreDisfraz)<=0)
            {
                ante=aux;
                aux=aux->sig;
            }
            ante->sig=nuevo;
            nuevo->sig=aux;
        }
    }
    return lista;
}

nodo2 *pasarALDL(char nombreArchivo[25])
{
    nodo2 *resultante=NULL;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroDisfraz buffer;
        while(fread(&buffer,sizeof(stRegistroDisfraz),1,archivo)>0)
        {
            nodo *nuevoDis=crearNodo(buffer.nombreDisfraz,buffer.generoDisfraz,buffer.stockDisfraz);
            nodo2 *pos=buscarN2(resultante,buffer.nombreSucursal);
            if(!pos)
            {
                nodo2 *nuevaSuc=crearNodo2(buffer.idSucursal,buffer.nombreSucursal);
                pos=nuevaSuc;
                resultante=insertarOrdenadoN2(resultante,nuevaSuc);
            }
            pos->listaDisfraz=insertarOrdenadoN(pos->listaDisfraz,nuevoDis);
        }
    }
    return resultante;
}

void punto1(char nombreArchivo[25],nodo2 **lista)
{
    *lista=pasarALDL(nombreArchivo);
}
//}

//Punto2
//{
void mostrarSucursal(stSucursal dato)
{
    puts ("\n************************************** SUCURSAL ****************************************\n");
    printf ("\nId de la Sucursal…………………………………………..: %d \n", dato.idSucursal);
    printf("\nNombre de la Sucursal: ……………………………………:%s \n", dato.nombreSucursal);
    puts ("\n*********************************************************************************************\n");
}

void mostrarLista(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            mostrarSucursal(iterador->sucursal);
            mostrarListaDis(iterador->listaDisfraz);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("Lista Vacia!");
    }
}
void mostrarDisfraz(stDisfraz dato)
{
    puts ("\n-----------------------------------------------------------------------------------------\n");
    printf("\nNombre del disfraz........................: %s \n ", dato.nombreDisfraz);
    printf("\Genero al que pertenece.................: %s \n ", dato.generoDisfraz);
    printf("\nStock del disfraz............................: %d \n",dato.stockDisfraz);
    puts ("\n------------------------------------------------------------------------------------------\n");
}
void mostrarListaDis(nodo *lista)
{
    if(lista)
    {
        nodo *iterador=lista;
        while(iterador)
        {
            mostrarDisfraz(iterador->disfraz);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("Lista disfraces vacia!");
    }
}

void punto2(nodo2 *lista)
{
    mostrarLista(lista);
}
//}

//Punto3
//{
Arbol *inicArbol()
{
    return NULL;
}

Arbol *crearArbol(int idSucursal,char nombreSucursal[25],char nombreDisfraz[25],char generoDisfraz[25],int stock)
{
    Arbol *nuevo=(Arbol*)malloc(sizeof(Arbol));

    nuevo->registro.idSucursal=idSucursal;
    strcpy(nuevo->registro.nombreSucursal,nombreSucursal);
    strcpy(nuevo->registro.nombreDisfraz,nombreDisfraz);
    strcpy(nuevo->registro.generoDisfraz,generoDisfraz);
    nuevo->registro.stockDisfraz=stock;
    nuevo->izq=NULL;
    nuevo->der=NULL;


    return nuevo;
}
Arbol *insertarOrdArbol(Arbol *arbol,Arbol *nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(strcmpi(arbol->registro.nombreDisfraz,nuevo->registro.nombreDisfraz)<=0)
        {
            arbol->der=insertarOrdArbol(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertarOrdArbol(arbol->izq,nuevo);
        }
    }
    return arbol;
}
Arbol *pasarAArbol(Arbol *arbol,nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            nodo *iterDis=iterador->listaDisfraz;
            while(iterDis)
            {
                Arbol *nuevo=crearArbol(iterador->sucursal.idSucursal,
                                        iterador->sucursal.nombreSucursal,
                                        iterDis->disfraz.nombreDisfraz,
                                        iterDis->disfraz.generoDisfraz,
                                        iterDis->disfraz.stockDisfraz);

                arbol=insertarOrdArbol(arbol,nuevo);
                iterDis=iterDis->sig;
            }
            iterador=iterador->sig;
        }
    }
    return arbol;
}
void punto3(Arbol **arbol,nodo2 *lista)
{
    *arbol=pasarAArbol(*arbol,lista);
}
//}

//Punto4
//{
void mostrarSTReg(stRegistroDisfraz registro)
{
    printf("\n ID:%-3i SUC: %-10s DIZ: %-20s GEN: %-10s STOCK: %-10i \n",registro.idSucursal,registro.nombreSucursal,registro.nombreDisfraz,registro.generoDisfraz,registro.stockDisfraz);
}

void mostrarArbol(Arbol *arbol)
{
    if(arbol)
    {
        mostrarArbol(arbol->izq);
        mostrarSTReg(arbol->registro);
        mostrarArbol(arbol->der);
    }
}

void punto4(Arbol *arbol)
{
    mostrarArbol(arbol);
}
//}

//Punto 5
//{
void buscarDisfraz(Arbol *arbol,char nombre[25],char genero[25])
{
    if(arbol)
    {
        buscarDisfraz(arbol->izq,nombre,genero);
        if(strcmpi(arbol->registro.nombreDisfraz,nombre)==0 && strcmpi(arbol->registro.generoDisfraz,genero)==0)
        {
            mostrarSTReg(arbol->registro);
        }
        buscarDisfraz(arbol->der,nombre,genero);
    }
}
void punto5(Arbol *arbol)
{
    char nombre[25];
    char genero[25];
    printf("\n ingrese el nombre del disfraz: ");
    gets(nombre);
    printf("\n Ingrese el genero del disfraz ");
    gets(genero);
    buscarDisfraz(arbol,nombre,genero);
}
//}
