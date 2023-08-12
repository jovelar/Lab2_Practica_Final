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

typedef struct NodoSucursal
{
    stSucursal sucursal;
    struct NodoSucursal *ante;
    struct NodoSucursal *sig;
    struct NodoDisfraz *disFrazes;
}NodoSucursal;

typedef struct
{
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
}stDisfraz;

typedef struct NodoDisfraz
{
    stDisfraz disfraz;
    struct NodoDisfraz *sig;
}NodoDisfraz;

////////////////Lista Doble Sucursal/////////////////////
NodoSucursal *inicSucursal();
NodoSucursal *nuevoNodoSucursal(int idSucursal, char nombreSucursal[25]);
NodoSucursal *buscarSucursal(NodoSucursal *listaSucursal,char nombreSucursal[25]);
NodoSucursal *buscarUltimo(NodoSucursal *listaSucursal);
NodoSucursal *insertarAlFinal(NodoSucursal *listaSucursal,NodoSucursal *nuevaSucursal);

NodoSucursal *pasarArchivoALDL(char nombreArchivo[25]);

void mostrarLDL(NodoSucursal *listaSucursales);
void mostrarListaDisfrazes(NodoDisfraz *listaDisfrazes);


////////////////Lista Simple Disfrazes///////////////////
NodoDisfraz *inicDisfraz();
NodoDisfraz *nuevoNodoDisfraz(int stockDisfraz,char nombreDisfraz[25],char generoDisfraz[25]);
NodoDisfraz *insertarOrdenadoDisfraz(NodoDisfraz *listaDisfraz,NodoDisfraz *nuevoDisfraz);

void pasarRegistrosACSV(char nombreArchivo[25]);

int main()
{
    int opcion=0;
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
        case 27:;
            break;
        case 49:;
            NodoSucursal *listaDeListas=inicSucursal();
            listaDeListas=pasarArchivoALDL("archivoRegistrosDisfraces.bin");
            mostrarLDL(listaDeListas);
            printf("\nLista cargada!\n");
            break;
        case 50:
            break;
        case 51:
            break;
        case 52:
            pasarRegistrosACSV("archivoRegistrosDisfraces.bin");
            break;
        default:
            printf("\nOpcion Invalida!\n");
            break;
        }
    }
    return 0;
}

int menu()
{
    int opcion;
    printf("1-Pasar lista a Lista de Listas\n");
    printf("2-Pasar lista a Lista de Listas\n");
    printf("3-Pasar lista a Lista de Listas\n");
    printf("4-Pasar lista a Lista de Listas\n");
    printf("\n\nESC-Salir: ");
    opcion=getch();
    return opcion;
}

////////////////Lista Doble Sucursal/////////////////////
NodoSucursal *inicSucursal()
{
    return NULL;
}

NodoSucursal *nuevoNodoSucursal(int idSucursal, char nombreSucursal[25])
{
    NodoSucursal *nuevaSucursal=(NodoSucursal*)malloc(sizeof(NodoSucursal));
    nuevaSucursal->sucursal.idSucursal=idSucursal;
    strcpy(nuevaSucursal->sucursal.nombreSucursal,nombreSucursal);
    nuevaSucursal->ante=NULL;
    nuevaSucursal->sig=NULL;
    nuevaSucursal->disFrazes=NULL;
    return nuevaSucursal;
}

NodoSucursal *buscarSucursal(NodoSucursal *listaSucursal,char nombreSucursal[25])
{
    NodoSucursal *resultante=NULL;
    if(listaSucursal!=NULL)
    {
        while(listaSucursal!=NULL)
        {
            if(strcmp(listaSucursal->sucursal.nombreSucursal,nombreSucursal)==0)
            {
                resultante=listaSucursal;
            }
            listaSucursal=listaSucursal->sig;
        }
    }
    return resultante;
}

NodoSucursal *buscarUltimo(NodoSucursal *listaSucursal);

NodoSucursal *insertarAlFinal(NodoSucursal *listaSucursal,NodoSucursal *nuevaSucursal)
{
    if(listaSucursal==NULL)
    {
        listaSucursal=nuevaSucursal;
    }
    else
    {
        NodoSucursal *auxiliar=listaSucursal;
        while(auxiliar->sig!=NULL)
        {
            auxiliar=auxiliar->sig;
        }
        auxiliar->sig=nuevaSucursal;
        nuevaSucursal->ante=auxiliar;
    }
    return listaSucursal;
}

NodoSucursal *pasarArchivoALDL(char nombreArchivo[25])
{
    NodoSucursal *listaDeListas=inicSucursal();
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroDisfraz buffer;
        while(fread(&buffer,sizeof(stRegistroDisfraz),1,archivo)>0)
        {
            NodoDisfraz *nuevo=nuevoNodoDisfraz(buffer.stockDisfraz,buffer.nombreDisfraz,buffer.generoDisfraz);
            NodoSucursal *busqueda=buscarSucursal(listaDeListas,buffer.nombreSucursal);
            if(busqueda==NULL)
            {
                NodoSucursal *nuevaSucursal=nuevoNodoSucursal(buffer.idSucursal,buffer.nombreSucursal);
                listaDeListas=insertarAlFinal(listaDeListas,nuevaSucursal);
                busqueda=nuevaSucursal;
            }
            busqueda->disFrazes=insertarOrdenadoDisfraz(busqueda->disFrazes,nuevo);
        }
    }
    else
    {
        printf("\nEL archivo no existe!\n");
    }
    return listaDeListas;
}

void mostrarLDL(NodoSucursal *listaSucursales)
{
    if(listaSucursales!=NULL)
    {
        NodoSucursal *aux=listaSucursales;
        while(aux!=NULL)
        {
            printf("\n");
            printf("====================\n");
            printf("==%i;%s==\n",aux->sucursal.idSucursal,aux->sucursal.nombreSucursal);
            printf("====================\n");
            printf("\n");
            mostrarListaDisfrazes(aux->disFrazes);
            aux=aux->sig;
        }
    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}
void mostrarListaDisfrazes(NodoDisfraz *listaDisfrazes)
{
    NodoDisfraz *aux=listaDisfrazes;
    if(aux!=NULL)
    {
        while(aux!=NULL)
        {
            printf("%s;%s;%i\n",aux->disfraz.generoDisfraz,aux->disfraz.nombreDisfraz,aux->disfraz.stockDisfraz);
            aux=aux->sig;
        }
    }
    else
    {
        printf("\nLa lista de disfrazes esta vacia!\n");
        system("pause");
    }
}

////////////////Lista Simple Disfrazes///////////////////
NodoDisfraz *inicDisfraz()
{
    return NULL;
}
NodoDisfraz *nuevoNodoDisfraz(int stockDisfraz,char nombreDisfraz[25],char generoDisfraz[25])
{
    NodoDisfraz *nuevoNodo=(NodoDisfraz*)malloc(sizeof(NodoDisfraz));
    nuevoNodo->disfraz.stockDisfraz=stockDisfraz;
    strcpy(nuevoNodo->disfraz.nombreDisfraz,nombreDisfraz);
    strcpy(nuevoNodo->disfraz.generoDisfraz,generoDisfraz);
    nuevoNodo->sig=NULL;
    return nuevoNodo;
}

NodoDisfraz *insertarOrdenadoDisfraz(NodoDisfraz *listaDisfraz,NodoDisfraz *nuevoDisfraz)
{
    if(listaDisfraz==NULL)
    {
        listaDisfraz=nuevoDisfraz;
    }
    else
    {
        if(strcmp(listaDisfraz->disfraz.nombreDisfraz,nuevoDisfraz->disfraz.nombreDisfraz)>0)
        {
            nuevoDisfraz->sig=listaDisfraz;
            listaDisfraz=nuevoDisfraz;
        }
        else
        {
            NodoDisfraz *ante;
            NodoDisfraz *aux=listaDisfraz;
            while(aux!=NULL && strcmp(aux->disfraz.nombreDisfraz,nuevoDisfraz->disfraz.nombreDisfraz)<0)
            {
                ante=aux;
                aux=aux->sig;
            }
            if(aux==NULL)
            {
                ante->sig=nuevoDisfraz;
            }
            else
            {
                ante->sig=nuevoDisfraz;
                nuevoDisfraz->sig=aux;
            }
        }
    }
    return listaDisfraz;
}

void pasarRegistrosACSV(char nombreArchivo[25])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        char nombreAResultante[]="registros-resultantes.csv";
        FILE *archivoResultante=fopen(nombreAResultante,"wb");
        stRegistroDisfraz buffer;
        while(fread(&buffer,sizeof(stRegistroDisfraz),1,archivo))
        {
            fprintf(archivoResultante,"%i;%s;%s;%s;%i\n",buffer.idSucursal,buffer.nombreSucursal,buffer.nombreDisfraz,buffer.generoDisfraz,buffer.stockDisfraz);
        }
        fclose(archivoResultante);
        fclose(archivo);
    }
    else
    {
        printf("\n El archivo no existe/no se pudo abrir! \n");
    }
}
