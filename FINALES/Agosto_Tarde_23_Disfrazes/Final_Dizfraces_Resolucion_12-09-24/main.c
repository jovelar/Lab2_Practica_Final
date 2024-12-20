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
    stDisfraz *listaDisfraces;
    struct nodoSucursal *ante;
    struct nodoSucursal *sig;
}nodoSucursal;

typedef struct
{
    stDisfraz disfras;
    struct nodoDisfraz *sig;
}nodoDisfraz;

typedef struct
{
    stRegistroDisfraz registroDisfraz;
    struct nodoArbol *izq;
    struct nodoArbol *der;
}nodoArbol;

stSucursal crearSTSuc(int idSucursal,char nombreSucursal[25]);
stDisfraz crearSTdisfraz(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz);

nodoSucursal *inicSucursal();
nodoSucursal *crearNodoSuc(int idSucural,char nombreSucursal[25]);
nodoSucursal *buscarSucursal(nodoSucursal *lista, char nombreSucursal[25]);
nodoSucursal *insertarOrdenado(nodoSucursal *lista,nodoSucursal *nuevo);

nodoDisfraz *inicDisfraz();
nodoDisfraz *crearNodoDiz(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz);
nodoDisfraz *insertarOrdenadoDisfraz(nodoDisfraz *lista,nodoDisfraz *nuevo);

nodoSucursal *pasaraLDL(char nombreArchivo[40]);

void mostrarDisfraz(stDisfraz dato);
void mostrarListaDisfraz(nodoDisfraz *lista);
void mostrarSucursal(stSucursal dato);
void mostrarListaSuc(nodoSucursal *lista);

nodoArbol *inicArbol();
nodoArbol *crearArbol(int idSucursal, char nombreSucursal[25],char nombreDisfraz[25],char generoDisfraz[25], int stockDisfraz);
nodoArbol *insertarOrdNombRec(nodoArbol *arbol, nodoArbol *nuevo);
nodoArbol *mostrarArbolRec(nodoArbol *arbol);

nodoArbol *pasarAArbol(nodoSucursal *lista);

void *buscar(nodoArbol *arbol,char nombreDisfraz[25], char generoDisfraz[25]);

void punto1(nodoSucursal **lista,char nombreArchivo[40]);
void punto2(nodoSucursal *lista);
void punto3(nodoSucursal *lista, nodoArbol **arbol);
void punto4(nodoArbol *arbol);
void punto5(nodoArbol *arbol);

int main()
{
    nodoSucursal *listaSucursales=inicSucursal();
    char nombreArchivo[]="archivoRegistrosDisfraces.bin";

    punto1(&listaSucursales,nombreArchivo);
    punto2(listaSucursales);

    nodoArbol *arbol=inicArbol();
    punto3(listaSucursales,&arbol);
    punto4(arbol);
    punto5(arbol);

    return 0;
}


//Punto 1
//{

stSucursal crearSTSuc(int idSucursal,char nombreSucursal[25])
{
    stSucursal nuevo;
    strcpy(nuevo.nombreSucursal,nombreSucursal);
    nuevo.idSucursal=idSucursal;
    return nuevo;
}

stDisfraz crearSTdisfraz(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz)
{
    stDisfraz nuevo;
    strcpy(nuevo.generoDisfraz,generoDisfraz);
    strcpy(nuevo.nombreDisfraz,nombreDisfraz);
    nuevo.stockDisfraz=stockDisfraz;
    return nuevo;
}

nodoSucursal *inicSucursal()
{
    return NULL;
}


nodoSucursal *crearNodoSuc(int idSucural,char nombreSucursal[25])
{
    nodoSucursal *nuevo=(nodoSucursal*)malloc(sizeof(nodoSucursal));
    stSucursal sucursal=crearSTSuc(idSucural,nombreSucursal);
    nuevo->sucursal=sucursal;
    nuevo->ante=NULL;
    nuevo->sig=NULL;
    nuevo->listaDisfraces=NULL;
    return nuevo;
}

nodoSucursal *buscarSucursal(nodoSucursal *lista, char nombreSucursal[25])
{
    nodoSucursal *posicion=NULL;
    if(lista)
    {
        if(strcmpi(lista->sucursal.nombreSucursal,nombreSucursal)==0)
        {
            posicion=lista;
        }
        else
        {
            nodoSucursal *iterador=lista;
            while(iterador && !posicion)
            {
                if(strcmpi(iterador->sucursal.nombreSucursal,nombreSucursal)==0)
                {
                    posicion=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }
    return  posicion;
}


nodoSucursal *insertarOrdenado(nodoSucursal *lista,nodoSucursal *nuevo)
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
            nodoSucursal *ante=NULL;
            nodoSucursal *iterador=lista;
            while(iterador && strcmpi(iterador->sucursal.nombreSucursal,nuevo->sucursal.nombreSucursal)<0)
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


nodoDisfraz *inicDisfraz()
{
    return NULL;
}
nodoDisfraz *crearNodoDiz(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz)
{
    nodoDisfraz *nuevo=(nodoDisfraz*)malloc(sizeof(nodoDisfraz));
    stDisfraz disfras=crearSTdisfraz(nombreDisfraz,generoDisfraz,stockDisfraz);
    nuevo->disfras=disfras;
    nuevo->sig=NULL;
    return nuevo;
}

nodoDisfraz *insertarOrdenadoDisfraz(nodoDisfraz *lista,nodoDisfraz *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->disfras.nombreDisfraz,nuevo->disfras.nombreDisfraz)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodoDisfraz *ante=NULL;
            nodoDisfraz *iterador=lista;
            while(iterador && strcmpi(iterador->disfras.nombreDisfraz,nuevo->disfras.nombreDisfraz)<=0) //Lleva = por que si encuentra el mismo nombre el bucle se bloquea
            {
                //printf("D.Lista: %s D.Comp: %s Valor COMP: %i\n",iterador->disfras.nombreDisfraz,nuevo->disfras.nombreDisfraz,strcmpi(iterador->disfras.nombreDisfraz,nuevo->disfras.nombreDisfraz));
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->sig=iterador;
        }
    }
    return lista;
}

nodoSucursal *pasaraLDL(char nombreArchivo[40])
{
    nodoSucursal *resultante=inicSucursal();
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroDisfraz buffer;
        while(fread(&buffer,sizeof(stRegistroDisfraz),1,archivo)>0)
        {
            nodoDisfraz *nuevoDisfraz=crearNodoDiz(buffer.nombreDisfraz,buffer.generoDisfraz,buffer.stockDisfraz);
            nodoSucursal *posicion=buscarSucursal(resultante,buffer.nombreSucursal);
            if(!posicion)
            {
                nodoSucursal *nuevaSucursal=crearNodoSuc(buffer.idSucursal,buffer.nombreSucursal);
                resultante=insertarOrdenado(resultante,nuevaSucursal);
                posicion=nuevaSucursal;
            }
            posicion->listaDisfraces=insertarOrdenadoDisfraz(posicion->listaDisfraces,nuevoDisfraz);
        }
    }
    return resultante;
}

void punto1(nodoSucursal **lista,char nombreArchivo[40])
{
    *lista=pasaraLDL(nombreArchivo);
}

//}

//PUNTO 2
//{
void mostrarDisfraz(stDisfraz dato)
{
    puts ("\n-----------------------------------------------------------------------------------------\n");
    printf("\nNombre del disfraz........................: %s \n ", dato. nombreDisfraz);
    printf("\Genero al que pertenece.................: %s \n ", dato. generoDisfraz);
    printf("\nStock del disfraz............................: %d \n", dato. stockDisfraz);
    puts ("\n------------------------------------------------------------------------------------------\n");
}
void mostrarListaDisfraz(nodoDisfraz *lista)
{
    if(lista)
    {
        nodoDisfraz *iterador=lista;
        while(iterador)
        {
            mostrarDisfraz(iterador->disfras);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("La lista esta vacia!\n");
    }
}

void mostrarSucursal(stSucursal dato)
{
    puts ("\n************************************** SUCURSAL ****************************************\n");
    printf ("\nId de la Sucursal..: %d \n", dato.idSucursal);
    printf("\nNombre de la Sucursal: :%s \n", dato.nombreSucursal);
    puts ("\n*********************************************************************************************\n");
}
void mostrarListaSuc(nodoSucursal *lista)
{
    if(lista)
    {
        nodoSucursal *iterador=lista;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        while(iterador)
        {
            mostrarSucursal(iterador->sucursal);
            mostrarListaDisfraz(iterador->listaDisfraces);
            iterador=iterador->ante;
        }
    }
    else
    {
        printf("La lista de sucursales esta vacia!");
    }
}

void punto2(nodoSucursal *lista)
{
    mostrarListaSuc(lista);
}
//}

//Punto 3
//{
nodoArbol *inicArbol()
{
    return NULL;
}
nodoArbol *crearArbol(int idSucursal, char nombreSucursal[25],char nombreDisfraz[25],char generoDisfraz[25], int stockDisfraz)
{
    nodoArbol *nuevo=(nodoArbol*)malloc(sizeof(nodoArbol));
    stRegistroDisfraz nuevoSTR;
    strcpy(nuevoSTR.nombreDisfraz,nombreDisfraz);
    strcpy(nuevoSTR.generoDisfraz,generoDisfraz);
    strcpy(nuevoSTR.nombreSucursal,nombreSucursal);
    nuevoSTR.idSucursal=idSucursal;
    nuevoSTR.stockDisfraz=stockDisfraz;
    nuevo->registroDisfraz=nuevoSTR;
    nuevo->izq=NULL;
    nuevo->der=NULL;

    return nuevo;
}

nodoArbol *insertarOrdNombRec(nodoArbol *arbol, nodoArbol *nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(strcmpi(arbol->registroDisfraz.nombreDisfraz,nuevo->registroDisfraz.nombreDisfraz)<=0)
        {
            arbol->der=insertarOrdNombRec(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertarOrdNombRec(arbol->izq,nuevo);
        }
    }
}


nodoArbol *pasarAArbol(nodoSucursal *lista)
{
    nodoArbol *arbol=inicArbol();
    if(lista)
    {
        nodoSucursal *iterador=lista;
        while(iterador)
        {
            nodoDisfraz *itDisfraz=iterador->listaDisfraces;
            while(itDisfraz)
            {
                nodoArbol *nuevoArbol=crearArbol(iterador->sucursal.idSucursal,iterador->sucursal.nombreSucursal,itDisfraz->disfras.nombreDisfraz,itDisfraz->disfras.generoDisfraz,itDisfraz->disfras.stockDisfraz);
                arbol=insertarOrdNombRec(arbol,nuevoArbol);
                itDisfraz=itDisfraz->sig;
            }
            iterador=iterador->sig;
        }
    }
    return arbol;
}

void punto3(nodoSucursal *lista, nodoArbol **arbol)
{
    *arbol=pasarAArbol(lista);
}
//}
//Punto 4
//{
nodoArbol *mostrarArbolRec(nodoArbol *arbol)
{
    if(arbol)
    {
        mostrarArbolRec(arbol->izq);
        printf("SUCURSAL: %s DISFRAZ: %s GENERO: %s STOCK:%i \n",arbol->registroDisfraz.nombreSucursal,arbol->registroDisfraz.nombreDisfraz,arbol->registroDisfraz.generoDisfraz,arbol->registroDisfraz.stockDisfraz);
        mostrarArbolRec(arbol->der);
    }
}
void punto4(nodoArbol *arbol)
{
    mostrarArbolRec(arbol);
}
//}

//Punto 5
//{
void *buscar(nodoArbol *arbol, char nombreDisfraz[25], char generoDisfraz[25])
{
    if(arbol)
    {
        buscar(arbol->izq,nombreDisfraz,generoDisfraz);
        if(strcmpi(arbol->registroDisfraz.nombreDisfraz,nombreDisfraz)==0)
        {
            if(strcmpi(arbol->registroDisfraz.generoDisfraz,generoDisfraz)==0)
            {
                printf("SUCURSAL: %s DISFRAZ: %s GENERO: %s STOCK: %i\n",arbol->registroDisfraz.nombreSucursal,arbol->registroDisfraz.nombreDisfraz,arbol->registroDisfraz.generoDisfraz,arbol->registroDisfraz.stockDisfraz);
            }
        }
        buscar(arbol->der,nombreDisfraz,generoDisfraz);
    }
}
void punto5(nodoArbol *arbol)
{
    char nombreDis[2];
    char genero[25];
    printf("Ingrese el nombre del disfraz a buscar: ");
    gets(nombreDis);
    fflush(stdin);
    printf("Ingrese el genero: ");
    gets(genero);
    buscar(arbol,nombreDis,genero);
}
//}
