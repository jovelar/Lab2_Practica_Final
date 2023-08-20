#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
 char origen[30];
 char destino[30];
 char tipo[30];//”aereo”,“ferrocarril”
 float costo;
 int tiempoViaje;
}registroEnvios;

typedef struct nodoDestino {
   char nombre[30];
   float costo;
   int tiempoViaje;
   struct nodoDestino* sig;
}nodoDestino;

typedef struct nodoOrigen
 {
   char nombre[30];
   nodoDestino* destinosAereos;
   nodoDestino* destinosFerro;
   struct nodoOrigen* sig;
}nodoOrigen;

////////PUNTO 1 ////////
nodoDestino *inicDestino();
nodoDestino *nuevoDestino(char nombre[],float costo,int tiempoViaje);
nodoDestino *insertarAlFinal(nodoDestino *lista, nodoDestino *nuevo);

nodoOrigen *inicOrigen();
nodoOrigen *nuevoOrigen(char nombre[]);
nodoOrigen *insertarOrdenadoRec(nodoOrigen *lista, nodoOrigen *nuevo);
nodoOrigen *buscar(nodoOrigen *lista, char nombreOrigen[]);

nodoOrigen *pasarALDL(char nombreArchivo[]);

void mostrarListaOrigen(nodoOrigen *lista);
void mostrarListaDestino(nodoDestino *lista);
int menu();

////////PUNTO 2 ////////
float promedioTiempoViaje(nodoDestino *lista,char ubicacion[],int sumatoria,int contador);

void pasarACSV(char nombreArchivo[]);
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
            nodoDestino *listaDestinos=pasarALDL("registroEnvios.bin");
            mostrarListaOrigen(listaDestinos);
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
        default:
            printf("\nOpcion invalida!\n");
            system("pause");
            break;
        }
    }
    //pasarACSV("registroEnvios.bin");
    return 0;
}

////////PUNTO 1 ////////
nodoDestino *inicDestino()
{
    return NULL;
}
nodoDestino *nuevoDestino(char nombre[],float costo,int tiempoViaje)
{
    nodoDestino *nuevo=(nodoDestino*)malloc(sizeof(nodoDestino));
    strcpy(nuevo->nombre,nombre);
    nuevo->costo=costo;
    nuevo->tiempoViaje=tiempoViaje;
    nuevo->sig=NULL;

    return nuevo;
}
nodoDestino *insertarAlFinal(nodoDestino *lista, nodoDestino *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoDestino *aux=lista;
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        aux->sig=nuevo;
    }

    return lista;
}

nodoOrigen *inicOrigen()
{
    return NULL;
}

nodoOrigen *nuevoOrigen(char nombre[])
{
    nodoOrigen *nuevo=(nodoOrigen*)malloc(sizeof(nodoOrigen));
    strcpy(nuevo->nombre,nombre);
    nuevo->destinosAereos=NULL;
    nuevo->destinosFerro=NULL;
    nuevo->sig=NULL;

    return nuevo;
}
nodoOrigen *insertarOrdenadoRec(nodoOrigen *lista, nodoOrigen *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmp(nuevo->nombre,lista->nombre)<0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarOrdenadoRec(lista->sig,nuevo);
        }
    }
    return lista;
}

nodoOrigen *buscar(nodoOrigen *lista, char nombreOrigen[])
{
    nodoDestino *resultado=NULL;
    if(lista!=NULL)
    {
        nodoOrigen *aux=lista;
        while(aux!=NULL && resultado==NULL)
        {
            if(strcmp(aux->nombre,nombreOrigen)==0)
            {
                resultado=aux;
            }
            aux=aux->sig;
        }
    }
    return resultado;
}

nodoOrigen *pasarALDL(char nombreArchivo[])
{
    nodoOrigen *nuevaLista=inicOrigen();
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroEnvios buffer;
        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            nodoDestino *nuevoDest=nuevoDestino(buffer.destino,buffer.costo,buffer.tiempoViaje);

            nodoOrigen *posicionAInsertar=buscar(nuevaLista,buffer.origen);

            if(posicionAInsertar==NULL)
            {
                nodoOrigen *nuevoOr=nuevoOrigen(buffer.origen);
                nuevaLista=insertarOrdenadoRec(nuevaLista,nuevoOr);
                posicionAInsertar=nuevoOr;
            }
            if(strcasecmp(buffer.tipo,"aereo")==0)
            {
                posicionAInsertar->destinosAereos=insertarAlFinal(posicionAInsertar->destinosAereos,nuevoDest);
            }
            else
            {
                posicionAInsertar->destinosFerro=insertarAlFinal(posicionAInsertar->destinosFerro,nuevoDest);
            }
        }
    }
    else
    {
        printf("El archivo no se pudo abrir/ encontrar");
    }
    return nuevaLista;
}

void mostrarListaOrigen(nodoOrigen *lista)
{
    if(lista!=NULL)
    {
        nodoOrigen *aux=lista;
        while(aux!=NULL)
        {
            printf("\nOrigen: %s\n",aux->nombre);
            printf("\nMostrando Destinos Aereos\n");
            mostrarListaDestino(aux->destinosAereos);
            printf("\nMostrando Destinos Ferrocarril\n");
            mostrarListaDestino(aux->destinosFerro);

            aux=aux->sig;
        }
    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}
void mostrarListaDestino(nodoDestino *lista)
{
    if(lista!=NULL)
    {
        nodoDestino *aux=lista;
        while(aux!=NULL)
        {
            printf("N: %s|$ : %.2f|T: %i\n",aux->nombre,aux->costo,aux->tiempoViaje);
            aux=aux->sig;
        }
    }
    else
    {
        printf("\No hay destinos!");
    }
}

int menu()
{
    system("cls");
    printf("1-Pasar registros a lista de listas\n");
    printf("2-\n");
    printf("3-\n");
    printf("4-\n");
    printf("5-\n");
    printf("\n\nESC- Salir :");
    int opc;
    opc=getch();
    return opc;
}

////////PUNTO 2 ////////
float promedioTiempoViaje(nodoDestino *lista,char ubicacion[],int sumatoria,int contador)
{
    float promedio=0;
    if(lista!=NULL)
    {
        if(strcmp(lista->nombre,ubicacion)==0)
        {

        }
    }
    return (float)sumatoria/contador;
}

void pasarACSV(char nombreArchivo[])
{

    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroEnvios buffer;
        FILE *archivoSalida=fopen("registrosCSV.csv","wb");

        while(fread(&buffer,sizeof(registroEnvios),1,archivo))
        {
            fprintf(archivoSalida,"%s;%s;%s;%0.2f;%i\n",buffer.origen,buffer.destino,buffer.tipo,buffer.costo,buffer.tiempoViaje);
        }
        fclose(archivo);
        fclose(archivoSalida);
    }
    else
    {
        printf("\nNo se pudo abrir/encontrar el archivo!\n");
    }
}
