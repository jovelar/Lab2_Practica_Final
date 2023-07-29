#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idSocio;
    char nya[50];
    int UltimaCuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char NombreDeporte[50];
}stClub;

////////ESTRUCTURA PRINCIPAL////////
typedef struct
{
    char nombreDeporte[50];
    int idDeporte;
    float valorCuota;
}Deporte;

typedef struct
{
    Deporte deporte;
    struct ListaDeporte *sig;
}ListaDeporte;
////////////////////////////////////

////////ESTRUCTURA SECUNDARIA////////
typedef struct
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    int edad;
}Socio;

typedef struct
{
    Socio socio;
    struct ListaSocio *ante;
    struct ListaSocio *sig;
}ListaSocio;
////////////////////////////////////

////////LECTURA DE REGISTROS////////
ListaDeporte *pasarRegistrosALDL(char nombreArchivo[50]);
////////////////////////////////////

////////LISTA PRINCIPAL (LISTA SIMPLE)////////
ListaDeporte *inicDepo();
ListaDeporte *nuevoDeporte(int idDeporte,char nombreDeporte[50],float valorCuota);
//int buscarDeporte(ListaDeporte *lista,char nombreDeporte[50]);
ListaDeporte *buscarDeporte(ListaDeporte *lista, char nombreDeporte[50]);
ListaDeporte *agregar(ListaDeporte *lista, ListaDeporte *nuevoDeporte);

/////////LISTA SECUNDARIA (LISTAS DOBLE)/////
ListaSocio *inicSocio();
ListaSocio *nuevoSocio(int idSocio,char nya[50],int ultimaCuotaPaga,int edad);
int buscaSocio(ListaSocio *lista,int idSocio);
ListaSocio *agregarOrdenado();
////////////////////////////////////////////

////////FUNCIONES VARIAS////////
void agregarManual(ListaDeporte *listaDeporte);
void mostrarTodo(ListaDeporte *listaDeporte);
void listarDeporteMasPopular(ListaDeporte *listaDeporte);
void volcarADosArchivos(char nombreArchivoUno[50],char nombreArchivoDos[50]);
////////////////////////////////
int main()
{
    int opc=0;
    while(opc!=27)
    {
        switch(opc)
        {
        case 27:
            break;
        case 49:
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
            printf("\nOpcion invalida, Solo digitos del 1 al 6 y ESC\n");
            break;
        }
    }
    return 0;
}

int menu()
{
    int opcionMenu=0;
    printf("1- Cargar registros a LDL\n"); //49
    printf("2- Alta Manual de Socios\n");   //50
    printf("3- Listar todo");               //51
    printf("4- Listar Deporte con mayor cantidad de socios y sus integrantes\n"); //52
    printf("5- Volcar lista en 2 archivos\n");  //53
    printf("6- Listar socios deudores\n\n");    //54
    printf("ESC- SALIR : ");                    //27
    opcionMenu=getch();
    return opcionMenu;
}


////////LECTURA DE REGISTROS////////
ListaDeporte *pasarRegistrosALDL(char nombreArchivo[50])
{
    ListaDeporte *listaDeportes=inicDepo();
    FILE *archivo=fopen(nombreArchivo,"r");
    if(archivo)
    {
        stClub buffer;
        while(fread(&buffer,sizeof(stClub),1,archivo)>0)
        {
            //SE CREA PRIMERO EL NODO ALUMNO
            ListaSocio *nuevo=nuevoSocio(buffer.idSocio,buffer.nya,buffer.UltimaCuotaPaga,buffer.edad);
            //SE BUSCA EN QUE DEPORTE CORRESPONDE, SI NO EXISTE SE CREA
            ListaDeporte *posicionDeporte=buscarDeporte(listaDeportes,buffer.NombreDeporte);
            if(listaDeportes!=NULL)
            {
                listaDeportes->
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("\Error, no se encuentra el archivo de registros!");
    }
    return listaDeportes;
}
////////////////////////////////////

////////LISTA PRINCIPAL (LISTA SIMPLE)////////
ListaDeporte *inicDepo()
{
    return NULL;
}
ListaDeporte *nuevoDeporte(int idDeporte,char nombreDeporte[50],float valorCuota)
{
    ListaDeporte *nuevo=(ListaDeporte*)malloc(sizeof(ListaDeporte));
    nuevo->deporte.idDeporte=idDeporte;
    strcpy(nuevo->deporte.nombreDeporte,nombreDeporte);
    nuevo->deporte.valorCuota=valorCuota;
    nuevo->sig=NULL;
    return nuevo;
}

/*int buscarDeporte(ListaDeporte *lista,char nombreDeporte[50])
{
    int encontrado=0;
    ListaDeporte *aux=lista;
    if(aux!=NULL)
    {
        while(aux!=NULL)
        {
            if(strcmp(aux->deporte.nombreDeporte,nombreDeporte)==0)
            {
                encontrado=1;
            }
            aux=aux->sig;
        }
    }
    return encontrado;
}
*/
ListaDeporte *buscarDeporte(ListaDeporte *lista, char nombreDeporte[50])
{
    ListaDeporte *resultado=inicDepo();
    if(lista!=NULL)
    {
        ListaDeporte *aux=lista;
        while(aux!=NULL)
        {
            if(strcmp(aux->deporte.nombreDeporte,nombreDeporte)==0)
            {
                resultado=aux;
            }
            aux=aux->sig;
        }
    }
    return resultado;
}
ListaDeporte *agregar(ListaDeporte *lista, ListaDeporte *nuevoDeporte)
{
    ListaDeporte *aux=lista;
    if(aux==NULL)
    {
        lista=nuevoDeporte;
    }
    else
    {
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        aux->sig=nuevoDeporte;
    }
    return lista;
}

/////////LISTA SECUNDARIA (LISTAS DOBLE)/////
ListaSocio *inicSocio()
{
    return NULL;
}

ListaSocio *nuevoSocio(int idSocio,char nya[50],int ultimaCuotaPaga,int edad)
{
    ListaSocio *nuevo=(ListaSocio*)malloc(sizeof(ListaSocio));
    strcpy(nuevo->socio.nya,nya);
    nuevo->socio.idSocio=idSocio;
    nuevo->socio.edad=edad;
    nuevo->socio.ultimaCuotaPaga=ultimaCuotaPaga;
    return nuevo;
}

int buscaSocio(ListaSocio *lista,int idSocio)
{
    ListaSocio aux=lista;
    int encontrado=0;
    if(aux!=NULL)
    {
        while(aux!=NULL)
        {
            if(aux->socio.idSocio==idSocio)
            {
                encontrado=1;
            }
            aux=aux->sig;
        }
    }
    return encontrado;
}

ListaSocio *agregarOrdenado(ListaSocio *lista,ListaSocio *nuevo)
{
    ListaSocio aux=lista;
    if(aux==NULL)
    {
        lista=nuevo;
    }
    else
    {
        while((strcmp(aux->socio.nya,nuevo->socio.nya)>0)&&aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        ListaSocio *anterior=aux->ante;
        anterior->sig=nuevo;
        nuevo->ante=anterior;
        nuevo->sig=aux;
        aux->ante=nuevo;
    }
    return lista;
}
////////////////////////////////////////////

////////FUNCIONES VARIAS////////
void agregarManual(ListaDeporte *listaDeporte);
void mostrarTodo(ListaDeporte *listaDeporte);
void listarDeporteMasPopular(ListaDeporte *listaDeporte);
void volcarADosArchivos(char nombreArchivoUno[50],char nombreArchivoDos[50]);
////////////////////////////////
