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
    struct Disfraz *listaDisfraces;
    struct Sucursal *ante;
    struct Sucursal *sig;
}Sucursal;

typedef struct
{
    stDisfraz disfraz;
    struct Disfraz *sig;
}Disfraz;

typedef struct
{
    stRegistroDisfraz disfraz;
    struct Arbol *izq;
    struct Arbol *der;
}Arbol;

//Punto 1
//{
Disfraz *crearDisfraz(char nombre[25],char genero[25],int stock);
Disfraz *agregarOrdenadoDiz(Disfraz *lista, Disfraz *nuevo);

Sucursal *crearSucursal(int idSucursal, char nombre[25]);
Sucursal *buscarSucursal(Sucursal *lista,char nombre[25]);
Sucursal *agregarOrdenadoSuc(Sucursal *lista,Sucursal *nuevo);

Sucursal *pasaraLDL(char nombreArchivo[25]);
void punto1(Sucursal **lista,char nombreArchivo[50]);
//}

//Punto 2
//{
void mostrarInvListaSuc(Sucursal *listaSuc);
void mostrarListaDis(Disfraz *listaDis);
void mostrarSuc(stSucursal dato);
void mostrarDis(stDisfraz dato);
void punto2(Sucursal *lista);
//}

//Punto 3
//{
Arbol *crearArbol(int idSuc,char nombreSuc[25],char nombreDiz[25],char genero[25], int stock);
Arbol *agregarOrd(Arbol *arbol,Arbol *nuevo);
Arbol *pasarAArbol(Arbol *arbol,Sucursal *lista);
void punto3(Arbol **arbol,Sucursal *lista);
//}

//Punto 4
//{
void mostrarArbol(Arbol *arbol);
void punto4(Arbol *arbol);
//}

//Punto 5
//{
void buscarDisfrazArbol(Arbol *arbol, char nombre[25],char genero[25]);
void punto5(Arbol *arbol);
//}
int main()
{
    Sucursal *lista=NULL;
    char nombreArchivo[50]="archivoRegistrosDisfraces.bin";
    punto1(&lista,nombreArchivo);
    punto2(lista);
    Arbol *arbol=NULL;
    punto3(&arbol,lista);
    punto4(arbol);
    punto5(arbol);

    return 0;
}

//Punto 1
//{
Disfraz *crearDisfraz(char nombre[25],char genero[25],int stock)
{
    Disfraz *nuevo=(Disfraz*)malloc(sizeof(Disfraz));
    strcpy(nuevo->disfraz.nombreDisfraz,nombre);
    strcpy(nuevo->disfraz.generoDisfraz,genero);
    nuevo->disfraz.stockDisfraz=stock;
    nuevo->sig=NULL;
    return nuevo;
}

Disfraz *agregarOrdenadoDiz(Disfraz *lista, Disfraz *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->disfraz.nombreDisfraz,nuevo->disfraz.nombreDisfraz)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            Disfraz *ante;
            Disfraz *iterador=lista;
            while(iterador && strcmpi(iterador->disfraz.nombreDisfraz,nuevo->disfraz.nombreDisfraz)<=0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->sig=iterador;
        }
    }
    return lista;
}

Sucursal *crearSucursal(int idSucursal, char nombre[25])
{
    Sucursal *nuevo=(Sucursal*)malloc(sizeof(Sucursal));
    nuevo->sucursal.idSucursal=idSucursal;
    strcpy(nuevo->sucursal.nombreSucursal,nombre);
    nuevo->listaDisfraces=NULL;
    nuevo->ante=NULL;
    nuevo->sig=NULL;

    return nuevo;
}

Sucursal *buscarSucursal(Sucursal *lista,char nombre[25])
{
    Sucursal *posicion=NULL;
    if(lista)
    {
            Sucursal *iterador=lista;
            while(iterador && !posicion)
            {
                if(strcmpi(iterador->sucursal.nombreSucursal,nombre)==0)
                {
                    posicion=iterador;
                }
                iterador=iterador->sig;
            }
    }
    return posicion;
}
Sucursal *agregarOrdenadoSuc(Sucursal *lista,Sucursal *nuevo)
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
            Sucursal *ante;
            Sucursal *iterador=lista;
            while(iterador && strcmpi(iterador->sucursal.nombreSucursal,nuevo->sucursal.nombreSucursal)<=0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->ante=ante;
            nuevo->sig=iterador;
            if(iterador)
            {
                iterador->ante=nuevo;
            }
        }
    }
    return lista;
}

Sucursal *pasaraLDL(char nombreArchivo[50])
{
    Sucursal *listaResultante=NULL;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroDisfraz buffer;
        while(fread(&buffer,sizeof(stRegistroDisfraz),1,archivo)>0)
        {
            Disfraz *nuevo=crearDisfraz(buffer.nombreDisfraz,buffer.generoDisfraz,buffer.stockDisfraz);
            Sucursal *posicion=buscarSucursal(listaResultante,buffer.nombreSucursal);
            if(!posicion)
            {
                Sucursal *nuevaSucursal=crearSucursal(buffer.idSucursal,buffer.nombreSucursal);
                listaResultante=agregarOrdenadoSuc(listaResultante,nuevaSucursal);
                posicion=nuevaSucursal;
            }
            posicion->listaDisfraces=agregarOrdenadoDiz(posicion->listaDisfraces,nuevo);
        }
        fclose(archivo);
    }
    return listaResultante;
}
void punto1(Sucursal **lista,char nombreArchivo[25])
{
    *lista=pasaraLDL(nombreArchivo);
}
//}

//Punto 2
//{
void mostrarInvListaSuc(Sucursal *listaSuc)
{
    if(listaSuc)
    {
        Sucursal *iterador=listaSuc;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        while(iterador)
        {
            mostrarSuc(iterador->sucursal);
            mostrarListaDis(iterador->listaDisfraces);
            iterador=iterador->ante;
        }
    }
}

void mostrarListaDis(Disfraz *listaDis)
{
    if(listaDis)
    {
        Disfraz *iterador=listaDis;
        while(iterador)
        {
            mostrarDis(iterador->disfraz);
            iterador=iterador->sig;
        }
    }
}
void mostrarSuc(stSucursal dato)
{
    puts ("\n************************************** SUCURSAL ****************************************\n");
    printf ("\nId de la Sucursal…………………………………………..: %d \n", dato.idSucursal);
    printf("\nNombre de la Sucursal: ……………………………………:%s \n", dato.nombreSucursal);
    puts ("\n*********************************************************************************************\n");
}
void mostrarDis(stDisfraz dato)
{
    puts ("\n-----------------------------------------------------------------------------------------\n");
    printf("\nNombre del disfraz........................: %s \n ", dato.nombreDisfraz);
    printf("\nGenero al que pertenece.................: %s \n ", dato.generoDisfraz);
    printf("\nStock del disfraz............................: %d \n", dato.stockDisfraz);
    puts ("\n------------------------------------------------------------------------------------------\n");
}
void punto2(Sucursal *lista)
{
    mostrarInvListaSuc(lista);
}
//}

//Punto 3
//{
Arbol *crearArbol(int idSuc,char nombreSuc[25],char nombreDiz[25],char genero[25], int stock)
{
    Arbol *nuevo=(Arbol*)malloc(sizeof(Arbol));
    nuevo->disfraz.idSucursal=idSuc;
    strcpy(nuevo->disfraz.nombreSucursal,nombreSuc);
    strcpy(nuevo->disfraz.nombreDisfraz,nombreDiz);
    strcpy(nuevo->disfraz.generoDisfraz,genero);
    nuevo->disfraz.stockDisfraz=stock;
    nuevo->der=NULL;
    nuevo->izq=NULL;

    return nuevo;
}
Arbol *agregarOrd(Arbol *arbol,Arbol *nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(strcmpi(arbol->disfraz.nombreDisfraz,nuevo->disfraz.nombreDisfraz)<=0)
        {
            arbol->izq=agregarOrd(arbol->izq,nuevo);
        }
        else
        {
            arbol->der=agregarOrd(arbol->der,nuevo);
        }
    }
    return arbol;
}
Arbol *pasarAArbol(Arbol *arbol,Sucursal *lista)
{
    if(lista)
    {
        Sucursal *iterSuc=lista;
        while(iterSuc)
        {
            Disfraz *iterDis=iterSuc->listaDisfraces;
            while(iterDis)
            {
                Arbol *nuevoNodo=crearArbol(iterSuc->sucursal.idSucursal,
                                            iterSuc->sucursal.nombreSucursal,
                                            iterDis->disfraz.nombreDisfraz,
                                            iterDis->disfraz.generoDisfraz,
                                            iterDis->disfraz.stockDisfraz);
                arbol=agregarOrd(arbol,nuevoNodo);
                iterDis=iterDis->sig;
            }
            iterSuc=iterSuc->sig;
        }
    }
    return arbol;
}
void punto3(Arbol **arbol,Sucursal *lista)
{
    *arbol=pasarAArbol(*arbol,lista);
}
//}

//Punto 4
//{
void mostrarArbol(Arbol *arbol)
{
    if(arbol)
    {
        mostrarArbol(arbol->izq);
        printf(" ID:%i SUC:%-10s DIZ:%-15s GEN:%s STOCK:%i \n",arbol->disfraz.idSucursal,
                                                        arbol->disfraz.nombreSucursal,
                                                        arbol->disfraz.nombreDisfraz,
                                                        arbol->disfraz.generoDisfraz,
                                                        arbol->disfraz.stockDisfraz);
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
void buscarDisfrazArbol(Arbol *arbol, char nombre[25],char genero[25])
{
    if(arbol)
    {
        if(strcmpi(arbol->disfraz.nombreDisfraz,nombre)==0 && strcmpi(arbol->disfraz.generoDisfraz,genero)==0)
        {
            printf(" ID:%i SUC:%s DIZ:%s GEN:%s STOCK:%i \n",arbol->disfraz.idSucursal,
                                                            arbol->disfraz.nombreSucursal,
                                                            arbol->disfraz.nombreDisfraz,
                                                            arbol->disfraz.generoDisfraz,
                                                            arbol->disfraz.stockDisfraz);
        }
        else
        {
            buscarDisfrazArbol(arbol->izq,nombre,genero);
            buscarDisfrazArbol(arbol->der,nombre,genero);
        }
    }
}
void punto5(Arbol *arbol)
{
    char nombre[25];
    char genero[25];
    printf("Ingrese el nombre del disfraz: ");
    gets(nombre);
    printf("Ingrese el genero del disfraz: ");
    gets(genero);
    buscarDisfrazArbol(arbol,nombre,genero);
}
//}
