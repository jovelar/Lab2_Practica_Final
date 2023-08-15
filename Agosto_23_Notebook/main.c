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


///////Lista Doble Sucursales////////////
typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
}stSucursal;

typedef struct Nodo2
{
    stSucursal sucursal;
    struct Nodo2 *anterior;
    struct Nodo2 *siguiente;
    struct Nodo *disfrazes;
}Nodo2;

Nodo2 *inicN2();
Nodo2 *nuevaSucursal(int idSucursal,char nombreSucursal[25]);
Nodo2 *buscarSucursal(Nodo2 *listaSucursal,char nombreSucursal[]);
Nodo2 *insertarSucAlFinal(Nodo2 *lista, Nodo2 *nuevo);
Nodo2 *pasarArchivoALDL(char nombreArchivo[25]);

void mostrarLDL(Nodo2 *lista);

////////Lista Simple Disfrazes///////////
typedef struct
{
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
}stDisfraz;

typedef struct Nodo
{
    stDisfraz disfraz;
    struct Nodo *siguiente;
}Nodo;

Nodo *inic();
Nodo *nuevoDisfraz(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz);
Nodo *insertarOrdenado(Nodo *lista,Nodo *nuevo);
Nodo *insertarAlPrincipio(Nodo *lista,Nodo *nuevo);
Nodo *insertarAlFinal(Nodo *lista,Nodo *nuevo);
void mostrarLista(Nodo *lista);



int main()
{
    int opcion=0;
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
        case 27:
            break;

        case 49:;
            Nodo2 *listaSucursales=inicN2();
            listaSucursales=pasarArchivoALDL("archivoRegistrosDisfraces.bin");
            mostrarLDL(listaSucursales);
            system("pause");

            break;

        case 50:
            break;

        case 51:
            break;

        case 52:
            break;

        case 53:
            break;

        case 54:
            break;

        default:
            printf("Opcion invalida!");
            break;
        }
    }

    return 0;
}

int menu()
{
    int opciones;
    printf("1- Pasar archivo registros a LDL\n");
    printf("2- \n");
    printf("3- \n");
    printf("4- \n");
    printf("5- \n");
    printf("6- \n");
    printf("\n\nESC- SALIR ");
    opciones=getch();
    return opciones;
}

///////Lista Doble Sucursales////////////

Nodo2 *inicN2()
{
    return NULL;
}
Nodo2 *nuevaSucursal(int idSucursal,char nombreSucursal[25])
{
    Nodo2 *nuevo=(Nodo2*)malloc(sizeof(Nodo2));
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;
    nuevo->disfrazes=NULL;
    nuevo->sucursal.idSucursal=idSucursal;
    strcpy(nuevo->sucursal.nombreSucursal,nombreSucursal);
    return nuevo;
}

Nodo2 *buscarSucursal(Nodo2 *listaSucursal,char nombreSucursalX[])
{
    Nodo2 *resultado=NULL;
    if(listaSucursal)
    {
        Nodo2 *aux=listaSucursal;
        while(aux!=NULL)
        {
            if(strcmp(aux->sucursal.nombreSucursal,nombreSucursalX)==0)
            {
                resultado=aux;
            }
            aux=aux->siguiente;
        }
    }
    return resultado;
}
Nodo2 *insertarDisfrazAlFinal(Nodo2 *lista,Nodo2 *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        Nodo2 *aux=lista;
        while(aux->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
        nuevo->anterior=aux;
        nuevo->siguiente=NULL;
    }
    return lista;
}

Nodo2 *insertarSucAlFinal(Nodo2 *lista, Nodo2 *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        Nodo2 *aux=lista;
        while(aux->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
        nuevo->anterior=aux;
    }
    return lista;
}

Nodo2 *pasarArchivoALDL(char nombreArchivo[25])
{
    Nodo2 *listaNueva=inicN2();
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroDisfraz buffer;
        while(fread(&buffer,sizeof(stRegistroDisfraz),1,archivo)>0)
        {
            Nodo *nuevoDisf=nuevoDisfraz(buffer.nombreDisfraz,buffer.generoDisfraz,buffer.stockDisfraz);
            Nodo2 *sucursal=buscarSucursal(listaNueva,buffer.nombreSucursal);
            if(sucursal==NULL)
            {
                Nodo2 *nuevaSuc=nuevaSucursal(buffer.idSucursal,buffer.nombreSucursal);
                sucursal=nuevaSuc; //GUARDA EL PUNTERO PARA PODER INSERTAR EL DISFRAZ
                listaNueva=insertarSucAlFinal(listaNueva,nuevaSuc);
            }
            sucursal->disfrazes=insertarOrdenado(listaNueva->disfrazes,nuevoDisf);
        }
    }
    else
    {
        printf("\nEl archivo no se pudo abrir/no existe!\n");
    }
}

void mostrarLDL(Nodo2 *lista)
{
    if(lista!=NULL)
    {
        Nodo2 *aux=lista;
        while(aux!=NULL)
        {
            printf("\n========================\n");
            printf("\n===%i|%s======\n",aux->sucursal.idSucursal,aux->sucursal.nombreSucursal);
            printf("\n========================\n");
            mostrarLista(aux->disfrazes);
            aux=aux->siguiente;
        }
    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}
////////Lista Simple Disfrazes///////////

Nodo *inic()
{
    return NULL;
}

Nodo *nuevoDisfraz(char nombreDisfraz[25],char generoDisfraz[25],int stockDisfraz)
{
    Nodo *nuevoDisfraz=(Nodo*)malloc(sizeof(Nodo));
    nuevoDisfraz->disfraz.stockDisfraz=stockDisfraz;
    strcpy(nuevoDisfraz->disfraz.nombreDisfraz,nombreDisfraz);
    strcpy(nuevoDisfraz->disfraz.generoDisfraz,generoDisfraz);
    nuevoDisfraz->siguiente=NULL;
    return nuevoDisfraz;
}

Nodo *insertarOrdenado(Nodo *lista,Nodo *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(strcpy(nuevo->disfraz.nombreDisfraz,lista->disfraz.nombreDisfraz)>0) //SI ES EL PRIMERO
        {
            lista=insertarAlPrincipio(lista,nuevo);
        }
        else
        {
            Nodo *ante=lista;
            Nodo *aux=lista->siguiente;
            while(aux!=NULL && strcmp(aux->disfraz.nombreDisfraz,nuevo->disfraz.nombreDisfraz)<0)
            {
                ante=aux;
                aux=aux->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->siguiente=aux;
        }
    }
    return lista;
}

Nodo *insertarAlPrincipio(Nodo *lista,Nodo *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;

}
Nodo *insertarAlFinal(Nodo *lista,Nodo *nuevo);


void mostrarLista(Nodo *lista)
{
    if(lista!=NULL)
    {
        Nodo *aux=lista;
        while(aux!=NULL)
        {
            printf("%s;%s;%i| ",aux->disfraz.nombreDisfraz,aux->disfraz.generoDisfraz,aux->disfraz.stockDisfraz);
            aux=aux->siguiente;
        }
    }
    else
    {
        printf("\nLa lista de disfrazes esta vacia!\n");
    }
}
