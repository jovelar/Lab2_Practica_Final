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
typedef struct Deporte
{
    char nombreDeporte[50];
    int idDeporte;
    float valorCuota;
}Deporte;

typedef struct ListaDeporte
{
    Deporte deporte;
    struct ListaSocio *socios;
    struct ListaDeporte *sig;
}ListaDeporte;
////////////////////////////////////

////////ESTRUCTURA SECUNDARIA////////
typedef struct Socio
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    int edad;
}Socio;

typedef struct ListaSocio
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
ListaDeporte *buscarUltimoLS(ListaDeporte *lista);
ListaDeporte *agregar(ListaDeporte *lista, ListaDeporte *nuevoDeporte);

/////////LISTA SECUNDARIA (LISTAS DOBLE)/////
ListaSocio *inicSocio();
ListaSocio *nuevoSocio(int idSocio,char nya[50],int ultimaCuotaPaga,int edad);
int buscaSocio(ListaSocio *lista,int idSocio);

ListaSocio *agregarAlPrincipioLD(ListaSocio *lista,ListaSocio *nuevo);
ListaSocio *agregarAlFinalLD(ListaSocio *lista,ListaSocio *nuevo);
ListaSocio *buscarUltimoLD(ListaSocio *lista);


ListaSocio *agregarOrdenado();
////////////////////////////////////////////

////////FUNCIONES VARIAS////////
void agregarManual(ListaDeporte *listaDeporte);
void mostrarTodo(ListaDeporte *listaDeporte);

void mostrarDeporte(ListaDeporte *nodoDeporte);
void mostrarListaDeporte(ListaDeporte *lista);
void mostrarSocio(ListaSocio *nodoSocio);
void mostrarListaSocio(ListaSocio *lista);

void listarDeporteMasPopular(ListaDeporte *listaDeporte);
void volcarADosArchivos(char nombreArchivoUno[50],char nombreArchivoDos[50]);
////////////////////////////////
int main()
{
    int opc=0;
    while(opc!=27)
    {
        printf("\n");
        opc=menu();
        switch(opc)
        {
        case 27:
            break;
        case 49:;
            ListaDeporte *listaDeportes=NULL;
            char archivo[]="registroClub.dat";
            listaDeportes=pasarRegistrosALDL(archivo);
            mostrarTodo(listaDeportes);
            system("pause");
            system("cls");
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
    ListaDeporte *listaDeportes=NULL;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        ListaDeporte *busqueda=inicDepo();
        stClub buffer;
        while(fread(&buffer,sizeof(stClub),1,archivo)>0)
        {
            ListaSocio *socioNuevo=nuevoSocio(buffer.idSocio,buffer.nya,buffer.UltimaCuotaPaga,buffer.edad);
            printf("\n %s \n",socioNuevo->socio.nya);
            busqueda=buscarDeporte(listaDeportes,buffer.NombreDeporte);

            if(busqueda==NULL) //SI LA LISTA ESTA VACIA O EL DEPORTE NO SE ENCUENTRA CREA EL DEPORTE Y LO AGREGA A LA LISTA
            {
                ListaDeporte *deporteNuevo=nuevoDeporte(buffer.idDeporte,buffer.NombreDeporte,buffer.valorCuota);
                listaDeportes=agregar(listaDeportes,deporteNuevo);
                ListaDeporte *ultimo=buscarUltimoLS(listaDeportes);
                busqueda=ultimo; //GUARDA EL PUNTERO DEL NUEVO NODO DEPORTE PARA INSERTAR LOS SOCIOS
                busqueda->socios=NULL;
            }
              busqueda->socios=agregarOrdenado(busqueda->socios,socioNuevo);  //AGREGA EL SOCIO EN LA LISTA DE DEPORTE, APUNTADA POR "BUSQUEDA"busq

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
ListaDeporte *buscarDeporte(ListaDeporte *lista, char nombreDeporte[50])
{
    ListaDeporte *resultado=inicDepo();
    if(lista!=NULL)
    {
        ListaDeporte *aux=lista;
        while(aux!=NULL && resultado==NULL)
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

ListaDeporte *buscarUltimoLS(ListaDeporte *lista)
{
    ListaDeporte *resultante=NULL;
    if(lista!=NULL)
    {
        ListaDeporte *aux=lista;
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        resultante=aux;
    }
    return resultante;
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
    nuevo->sig=NULL;
    nuevo->ante=NULL;
    return nuevo;
}

int buscaSocio(ListaSocio *lista,int idSocio)
{
    ListaSocio *aux=lista;
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

ListaSocio *agregarAlPrincipioLD(ListaSocio *lista,ListaSocio *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->sig=lista;
        lista->ante=nuevo;
    }

    return nuevo;
}

ListaSocio *agregarAlFinalLD(ListaSocio *lista,ListaSocio *nuevo)
{
    if(lista!=NULL)
    {
        ListaSocio *seg=lista;
        while(seg->sig)
        {
            seg=seg->sig;
        }
        seg->sig=nuevo;
        nuevo->ante=seg;
    }
    else
    {
        lista=nuevo;
    }
    return lista;
}
ListaSocio *buscarUltimoLD(ListaSocio *lista)
{
    ListaSocio *rta=lista;
    if(lista!=NULL)
    {
        while(rta->sig!=NULL)
        {
            rta=rta->sig;
        }
    }
    return rta;
}

ListaSocio *agregarOrdenado(ListaSocio *lista,ListaSocio *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmp(lista->socio.nya,nuevo->socio.nya)>0) //SI ES EL PRIMERO
        {
            lista=agregarAlPrincipioLD(lista,nuevo);
        }
        else
        {
            ListaSocio *aux=lista->sig; //BUSCO DESDE EL SEGUNDO NODO
            while(aux!=NULL && strcmp(aux->socio.nya,nuevo->socio.nya)<0)
            {
                aux=aux->sig;
            }
            if(aux==NULL) ////AL FINAL
            {
                lista=agregarAlFinalLD(lista,nuevo);
            }
            else ///EN EL MEDIO
            {
                ListaSocio *anterior=aux->ante;
                ListaSocio *siguiente=aux->sig;
                anterior->sig=nuevo;
                nuevo->ante=anterior;
                nuevo->sig=aux;
                aux->ante=nuevo;
            }

        }

    }
    return lista;
}

void mostrarListaSocio(ListaSocio *lista)
{
    if(lista!=NULL)
    {
        ListaSocio *aux=lista;
        while(aux!=NULL)
        {
            printf("%s |",aux->socio.nya);
            aux=aux->sig;
        }
    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}
////////////////////////////////////////////

////////FUNCIONES VARIAS////////
void agregarManual(ListaDeporte *listaDeporte);
void mostrarTodo(ListaDeporte *listaDeporte)
{
    int socPorLin=6;
    if(listaDeporte!=NULL)
    {
        ListaDeporte *auxiliarDeporte=listaDeporte;
        while(auxiliarDeporte!=NULL)
        {
            int contador=0;
            ListaSocio *auxiliarSocios=listaDeporte->socios;
            printf("\n");
            printf("\n %s \n",auxiliarDeporte->deporte.nombreDeporte);
            printf("\n");
            mostrarListaSocio(auxiliarDeporte->socios);
            auxiliarDeporte=auxiliarDeporte->sig;
        }

    }
    else
    {
        printf("\nLa lista esta vacia!\n");
        system("pause");
    }
}
void listarDeporteMasPopular(ListaDeporte *listaDeporte);
void volcarADosArchivos(char nombreArchivoUno[50],char nombreArchivoDos[50]);
////////////////////////////////

void registroAArchivo(char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        FILE *archivoSalida=fopen("Registros.csv","wb");
        stClub buffer;
        printf("\n");
        fprintf(archivoSalida,"idSocio;NyA;UltimaCuotaPaga;ValorCuota;idDeporte;Nombredeporte\n");
        while(fread(&buffer,sizeof(stClub),1,archivo)>0)
        {
            //printf("%i,%s,%i,%0.2f,%i,%i,%s\n",buffer.idSocio,buffer.nya,buffer.UltimaCuotaPaga,buffer.valorCuota,buffer.edad,buffer.idDeporte,buffer.NombreDeporte);
            fprintf(archivoSalida,"%i;%s;%i;%0.2f;%i;%i;%s\n",buffer.idSocio,buffer.nya,buffer.UltimaCuotaPaga,buffer.valorCuota,buffer.edad,buffer.idDeporte,buffer.NombreDeporte);
        }
        fclose(archivo);
        fclose(archivoSalida);
    }
}

void agregarManual(ListaDeporte *listaDeporte)
{
    ListaSocio *socioNuevo=inicSocio();
    printf("\nIngrese el ID del nuevo socio\n");
    scanf("%d",socioNuevo->socio.idSocio);
    printf("\nIngrese el nombre y apellido\n");
    scanf("%s",socioNuevo->socio.nya);
    printf("\Ingrese la edad\n");
    scanf("%d",socioNuevo->socio.edad);
    printf("\nIngrese la ultima cuota que pago\n");
    scanf("%d",socioNuevo->socio.ultimaCuotaPaga);
    printf("Ingrese en que deporte desea incorporarse");
    char deporte[50];
    scanf("%d",&deporte);


}
int buscarSiguienteDeporteId(ListaDeporte *deportes)
{
    int id=-1; //POR DEFECTO SI NO ENCUENTRA NADA DEVUELVE -1
    if(deportes!=NULL)
    {
        while(deportes!=NULL)
        {
            if(deportes->deporte.idDeporte>id)
            {
                id=deportes->deporte.idDeporte;
            }
        }
    }
    if(id!=-1) //SI ENCONTRO ALGO
    {
        id++; //SUMA UN DIGITO AL ID ENCONTRADO MAS GRANDE PARA EVITAR QUE SE REPITA
    }
    return id;
}
