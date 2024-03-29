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

typedef struct NodoArbol
{
    stRegistroDisfraz registroDisfraz;
    struct NodoArbol *izq;
    struct NodoArbol *der;
}NodoArbol;

///////////////PUNTO 1//////////////////////////////////
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

///////////////PUNTO 2//////////////////////////////////
void mostrarLDLInvertido(NodoSucursal *listaSucursal);
void mostrarSucursal(stSucursal dato);
void mostrarDisfrazes(NodoDisfraz *listaDisfraz);
void mostrarDizfraz(stDisfraz dato);

void pasarRegistrosACSV(char nombreArchivo[25]);

///////////////PUNTO 3//////////////////////////////////
NodoArbol *inicArbol();
NodoArbol *nuevoNodoArbol(int idSucursal,char nombreSucursal[25],char nombreDizfraz[25],char generoDisfraz[25],int stocDisfraz);
NodoArbol *insertarOrdenadoArbol(NodoArbol *arbol,NodoArbol *nodo);
NodoArbol *pasarADLAArbol(NodoSucursal *listaSucursal);

///////////////PUNTO 4//////////////////////////////////

void mostrarArbolAscendente(NodoArbol *arbol);

///////////////PUNTO 5//////////////////////////////////

NodoArbol *buscarPorNombYGen(NodoArbol *arbol,char nombreDisfraz[],char genero[]);


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
        case 50:;
            NodoSucursal *listaDeListasP2=inicSucursal();
            listaDeListasP2=pasarArchivoALDL("archivoRegistrosDisfraces.bin");
            mostrarLDLInvertido(listaDeListasP2);
            break;
        case 51:;
            NodoSucursal *listaDeListasP3=inicSucursal();
            listaDeListasP3=pasarArchivoALDL("archivoRegistrosDisfraces.bin");
            NodoArbol *nuevoArbol=inicArbol();
            nuevoArbol=pasarADLAArbol(listaDeListasP3);
            mostrarArbolAscendente(nuevoArbol);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 52:;
            NodoSucursal *listaDeListasP4=inicSucursal();
            listaDeListasP4=pasarArchivoALDL("archivoRegistrosDisfraces.bin");
            NodoArbol *nuevoArbol2=inicArbol();
            nuevoArbol2=pasarADLAArbol(listaDeListasP4);
            printf("\n\n");
            mostrarArbolAscendente(nuevoArbol2);
            printf("\nIngrese el nombre del disfraz a buscar: ");
            fflush(stdin);
            char nombreDisfraz[25];
            gets(&nombreDisfraz);
            printf("\nIngrese el genero del disfra a buscar :");
            char generoDisfraz[25];
            scanf("%s",&generoDisfraz);
            NodoArbol *resultadoBusqueda=buscarPorNombYGen(nuevoArbol2,nombreDisfraz,generoDisfraz);

            if(resultadoBusqueda==NULL)
            {
                printf("La lista esta vacia!");
            }
            else
            {
                printf("\n%s|%s|%s",resultadoBusqueda->registroDisfraz.nombreDisfraz,resultadoBusqueda->registroDisfraz.generoDisfraz,resultadoBusqueda->registroDisfraz.nombreSucursal);
            }
            printf("\n\n");

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
    printf("1-Pasar lista a Lista de Listas (y mostrar propio\n"); //MUESTRA CON FUNCION MOSTRAR PROPIA
    printf("2-Mostrar LDL (segun consigna) \n"); //MUESTRA SEGUN CONSIGNA
    printf("3-Mostrar Arbol\n");
    printf("4-Buscar Disfraz por nombre y tipo\n");
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
    NodoSucursal *aux=listaSucursal;
    if(aux!=NULL)
    {
        while(aux!=NULL)
        {
            if(strcasecmp(aux->sucursal.nombreSucursal,nombreSucursal)==0)
            {
                resultante=aux;
            }
            aux=aux->sig;
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
        //if(strcmp(listaDisfraz->disfraz.nombreDisfraz,nuevoDisfraz->disfraz.nombreDisfraz)>0)
        if(strcasecmp(listaDisfraz->disfraz.nombreDisfraz,nuevoDisfraz->disfraz.nombreDisfraz)>=0)
        {
            nuevoDisfraz->sig=listaDisfraz;
            listaDisfraz=nuevoDisfraz;
        }
        else
        {
            NodoDisfraz *ante;
            NodoDisfraz *aux=listaDisfraz;
            //while(aux!=NULL && strcmp(aux->disfraz.nombreDisfraz,nuevoDisfraz->disfraz.nombreDisfraz)<0)
            while(aux!=NULL && strcasecmp(aux->disfraz.nombreDisfraz,nuevoDisfraz->disfraz.nombreDisfraz)<=0)
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

///////////////PUNTO 2//////////////////////////////////
void mostrarLDLInvertido(NodoSucursal *listaSucursal)
{
    if(listaSucursal!=NULL)
    {
        NodoSucursal *aux=listaSucursal;
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        while(aux!=NULL)
        {
            mostrarSucursal(aux->sucursal);
            mostrarDisfrazes(aux->disFrazes);

            aux=aux->ante;
        }
    }
    else
    {
        printf("\nLalista de sucursales esta vacia!\n");
    }
}
void mostrarSucursal(stSucursal dato)
{
    puts ("\n************************************** SUCURSAL ****************************************\n");
    printf ("\nId de la Sucursal..: %d \n", dato.idSucursal);
    printf("\nNombre de la Sucursal: :%s \n", dato.nombreSucursal);
    puts ("\n*********************************************************************************************\n");
}
void mostrarDisfrazes(NodoDisfraz *listaDisfraz)
{
    if(listaDisfraz!=NULL)
    {
        NodoDisfraz *aux=listaDisfraz;
        while(aux!=NULL)
        {
            mostrarDizfraz(aux->disfraz);
            aux=aux->sig;
        }
    }
    else
    {
        printf("\nLa lista de disfrazes esta vacia!\n");
    }
}
void mostrarDizfraz(stDisfraz dato)
{
    puts ("\n-----------------------------------------------------------------------------------------\n");
    printf("\nNombre del disfraz........................: %s \n ", dato.nombreDisfraz);
    printf("\Genero al que pertenece.................: %s \n ", dato.generoDisfraz);
    printf("\nStock del disfraz............................: %d \n", dato.stockDisfraz);
    puts ("\n------------------------------------------------------------------------------------------\n");
}

///////////////PUNTO 3//////////////////////////////////
NodoArbol *inicArbol()
{
    return NULL;
}
NodoArbol *nuevoNodoArbol(int idSucursal,char nombreSucursal[25],char nombreDizfraz[25],char generoDisfraz[25],int stockDisfraz)
{
    NodoArbol *nuevo=(NodoArbol*)malloc(sizeof(NodoArbol));
    nuevo->registroDisfraz.idSucursal=idSucursal;
    strcpy(nuevo->registroDisfraz.nombreSucursal,nombreSucursal);
    strcpy(nuevo->registroDisfraz.nombreDisfraz,nombreDizfraz);
    strcpy(nuevo->registroDisfraz.generoDisfraz,generoDisfraz);
    nuevo->registroDisfraz.stockDisfraz=stockDisfraz;
    nuevo->izq=NULL;
    nuevo->der=NULL;
    return nuevo;
}

NodoArbol *insertarOrdenadoArbol(NodoArbol *arbol,NodoArbol *nodo)
{
    if(arbol==NULL)
    {
        arbol=nodo;
    }
    else
    {
        if(strcasecmp(nodo->registroDisfraz.nombreDisfraz,arbol->registroDisfraz.nombreDisfraz)>=0)
        {
            arbol->der=insertarOrdenadoArbol(arbol->der,nodo);
        }
        else
        {
            arbol->izq=insertarOrdenadoArbol(arbol->izq,nodo);
        }
    }
    return arbol;
}

NodoArbol *pasarADLAArbol(NodoSucursal *listaSucursal)
{
    NodoArbol *arbol=inicArbol();
    if(listaSucursal!=NULL)
    {
        NodoSucursal *aux=listaSucursal;
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        while(aux!=NULL)
        {
            NodoDisfraz *aux2=aux->disFrazes;

            while(aux2!=NULL)
            {
                NodoArbol *nuevo=nuevoNodoArbol(aux->sucursal.idSucursal,aux->sucursal.nombreSucursal,aux2->disfraz.nombreDisfraz,aux2->disfraz.generoDisfraz,aux2->disfraz.stockDisfraz);
                arbol=insertarOrdenadoArbol(arbol,nuevo);
                aux2=aux2->sig;
            }
            aux=aux->ante;
        }
    }
    return arbol;
}

///////////////PUNTO 4//////////////////////////////////

void mostrarArbolAscendente(NodoArbol *arbol) //INORDER
{
    if(arbol!=NULL)
    {
        mostrarArbolAscendente(arbol->izq);
        printf("\n%-17s|%-20s|%-15s",arbol->registroDisfraz.nombreDisfraz,arbol->registroDisfraz.generoDisfraz,arbol->registroDisfraz.nombreSucursal);
        mostrarArbolAscendente(arbol->der);
    }
}

///////////////PUNTO 5//////////////////////////////////

NodoArbol *buscarPorNombYGen(NodoArbol *arbol,char nombreDisfraz[],char genero[])
{
    NodoArbol *resultado=inicArbol();
    if(arbol!=NULL)
    {

        if(strcasecmp(arbol->registroDisfraz.nombreDisfraz,nombreDisfraz)==0)
        {
            if(strcasecmp(arbol->registroDisfraz.generoDisfraz,genero)==0)
            {
                resultado=arbol;
            }
        }
        else
        {
            if(strcasecmp(nombreDisfraz,arbol->registroDisfraz.nombreDisfraz)>=0)
            {
                resultado=buscarPorNombYGen(arbol->der,nombreDisfraz,genero);
            }
            else
            {
                resultado=buscarPorNombYGen(arbol->izq,nombreDisfraz,genero);
            }
        }
    }
    return resultado;
}
