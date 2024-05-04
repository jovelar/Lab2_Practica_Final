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

typedef struct {
     int cantDestinosAereos;
     char ciudadOrigen[30];
     float costoPromedioAereo;
     float tiempoPromedioAereo;
}destinosAereos;

typedef struct {
     int cantDestinosFerro;;
     char ciudadOrigen[30];
     float costoPromedioFerro;
     float tiempoPromedioFerro;
}destinosFerro;

typedef struct
{
    int dato;
    struct Pila *siguiente;
}Pila;

Pila *inicPila();
Pila *apilar(Pila *pila, int dato);
int tope(Pila *pila);
int desapilar(Pila *pila);
int pilaVacia(Pila *pila);
void leer(Pila *pila);
void mostrarPila(Pila *pila);

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
float promedioTiempoViaje(nodoOrigen *lista,nodoDestino *destino,char ubicacion[],float sumatoria,int contador);
float promedioTiempoIT(nodoOrigen *listaOrigen,char ubicacion[]);

////////PUNTO 3 ////////
void pasarLDLADosRegistros(nodoOrigen *listaDL,char archivoUno[],char archivoDos[]);

destinosAereos *resumenAereo(nodoDestino *lista,char origen[]);
destinosFerro *resumenFerro(nodoDestino *lista,char origen[]);

void mostrarBinAereo(char archivoAereo[30]);
void mostrarBinFerro(char archivoFerro[30]);

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
            nodoOrigen *listaDestinos=pasarALDL("registroEnvios.bin");
            mostrarListaOrigen(listaDestinos);
            system("pause");
            break;
        case 50:
            printf("\nIngrese el nombre de la localidad destino a buscar: ");
            char localidad[25];
            fflush(stdin);
            gets(localidad);
            fflush(stdin);
            float promedio=0;
            nodoOrigen *listaDestinos2=pasarALDL("registroEnvios.bin");
            promedio=promedioTiempoViaje(listaDestinos2,listaDestinos2->destinosAereos,localidad,0,0);
            printf("El promedio es de %f \n ",promedio);
            system("pause");
            break;
        case 51:;
            nodoOrigen *listaDestinos3=pasarALDL("registroEnvios.bin");
            pasarLDLADosRegistros(listaDestinos3,"DestinosAereos.bin","destinosFerro.bin");
            printf("\n DESTINOS AEREOS PROMEDIO\n");
            mostrarBinAereo("DestinosAereos.bin");

            printf("\n DESTINOS FERRO PROMEDIO\n");
            mostrarBinFerro("DestinosFerro.bin");
            printf("\Se pasaron los archivos a 2 registros!");
            system("pause");
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
    printf("2-Mostrar promedio aereo de la ciudad ingresada\n");
    printf("3-Pasar LDL a archivos\n");
    printf("4-\n");
    printf("5-\n");
    printf("\n\nESC- Salir :");
    int opc;
    opc=getch();
    return opc;
}

////////PUNTO 2 ////////

float promedioTiempoViaje(nodoOrigen *lista,nodoDestino *destino,char ubicacion[],float sumatoria,int contador)
{
    if(lista!=NULL)
    {
        if(strcasecmp(lista->nombre,ubicacion)==0)
        {
            if(destino!=NULL)
            {
                sumatoria=promedioTiempoViaje(lista,destino->sig,ubicacion,sumatoria + destino->tiempoViaje,contador+1);
            }
            else
            {
                sumatoria=sumatoria/contador;
            }
        }
        else
        {
            sumatoria=promedioTiempoViaje(lista->sig,lista->destinosAereos,ubicacion,sumatoria,contador);
        }
    }
    return sumatoria;
}

float promedioTiempoIT(nodoOrigen *listaOrigen,char ubicacion[])
{
    int contador=0;
    int sumatoria=0;
    if(listaOrigen!=NULL)
    {
        nodoOrigen *aux=listaOrigen;
        while(aux!=NULL && contador==0) //SI CONTADOR !=0 ES POR QUE LO ENCONTRO.
        {
            if(strcasecmp(ubicacion,aux->nombre)==0)
            {
                nodoDestino *auxAereo=aux->destinosAereos;
                while(auxAereo!=NULL)
                {
                    printf("\n%i|%i\n",sumatoria,auxAereo->tiempoViaje);
                    sumatoria=sumatoria+auxAereo->tiempoViaje;
                    contador++;
                    auxAereo=auxAereo->sig;
                }
            }
            aux=aux->sig;
        }
    }
    return (float)(sumatoria/contador);
}

////////PUNTO 3 ////////
void pasarLDLADosRegistros(nodoOrigen *listaDL,char archivoUno[],char archivoDos[])
{
    if(listaDL!=NULL)
    {
        FILE *archivo1=fopen(archivoUno,"wb");
        FILE *archivo2=fopen(archivoDos,"wb");
        nodoOrigen *auxOrigen=listaDL;
        destinosAereos *aereo=NULL;
        destinosFerro *ferro=NULL;

        while(auxOrigen!=NULL)
        {
            aereo=resumenAereo(auxOrigen->destinosAereos,auxOrigen->nombre);
            ferro=resumenFerro(auxOrigen->destinosFerro,auxOrigen->nombre);

            if(aereo!=NULL)
            {
                fwrite(aereo,sizeof(destinosAereos),1,archivo1);
            }
            if(ferro!=NULL)
            {
                fwrite(ferro,sizeof(destinosFerro),1,archivo2);
            }
            auxOrigen=auxOrigen->sig;
        }
        fclose(archivo1);
        fclose(archivo2);
    }
}

destinosAereos *resumenAereo(nodoDestino *lista,char origen[])
{
    destinosAereos *resultante=NULL;
    if(lista!=NULL)
    {
        resultante=(destinosAereos*)malloc(sizeof(destinosAereos));
        strcpy(resultante->ciudadOrigen,origen);
        nodoDestino *aux=lista;
        while(aux!=NULL)
        {
            resultante->cantDestinosAereos+=1;
            resultante->costoPromedioAereo+=aux->costo;
            resultante->tiempoPromedioAereo+=aux->tiempoViaje;
            aux=aux->sig;
        }
        resultante->costoPromedioAereo=resultante->costoPromedioAereo/resultante->cantDestinosAereos;
        resultante->tiempoPromedioAereo=resultante->tiempoPromedioAereo/resultante->cantDestinosAereos;
    }
    return resultante;
}

destinosFerro *resumenFerro(nodoDestino *lista,char origen[])
{
    destinosFerro *resultante=NULL;
    if(lista!=NULL)
    {
        resultante=(destinosFerro*)malloc(sizeof(destinosFerro));
        strcpy(resultante->ciudadOrigen,origen);
        nodoDestino *aux=lista;
        while(aux!=NULL)
        {
            resultante->cantDestinosFerro+=1;
            resultante->costoPromedioFerro+=aux->costo;
            resultante->costoPromedioFerro+=aux->tiempoViaje;
            aux=aux->sig;
        }
        resultante->costoPromedioFerro=resultante->costoPromedioFerro/resultante->cantDestinosFerro;
        resultante->tiempoPromedioFerro=resultante->tiempoPromedioFerro/resultante->cantDestinosFerro;
    }
    return resultante;
}

void mostrarBinAereo(char archivoAereo[30])
{
    FILE *archivo=fopen(archivoAereo,"rb");
    if(archivo)
    {
        destinosAereos buffer;
        while(fread(&buffer,sizeof(destinosAereos),1,archivo))
        {
            printf("\nN:%i|Origen:%s|Prom Costo:%0.2f|Prom Tiempo:%0.2f\n",buffer.cantDestinosAereos,buffer.ciudadOrigen,buffer.costoPromedioAereo,buffer.tiempoPromedioAereo);
        }
        fclose(archivo);
    }
    else
    {
        printf("\El archivo no existe/no se puede abrir\n");
    }
}

void mostrarBinFerro(char archivoFerro[30])
{
    FILE *archivo=fopen(archivoFerro,"rb");
    if(archivo)
    {
        destinosFerro buffer;
        while(fread(&buffer,sizeof(destinosFerro),1,archivo))
        {
            printf("\nN:%i|Origen:%s|Prom Costo:%0.2f|Prom Tiempo:%0.2f\n",buffer.cantDestinosFerro,buffer.ciudadOrigen,buffer.costoPromedioFerro,buffer.tiempoPromedioFerro);
        }
        fclose(archivo);
    }
    else
    {
        printf("\El archivo no existe/no se puede abrir\n");
    }
}
void mostrarBinFerro(char archivoFerro[30]);

//NO FORMA PARTE DEL FINAL, SOLO SIRVE PARA OBTENER UNA LISTA LEIBLE PARA DEBUGGING.
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

Pila *inicPila()
{
    return NULL;
}

Pila *apilar(Pila *pila, int dato)
{
    Pila *nuevo=(Pila*)malloc(sizeof(Pila));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;

    if(pila==NULL)
    {
        pila=nuevo;
    }
    else
    {
        pila->siguiente=nuevo;
    }
    return pila;
}

int tope(Pila *pila)
{
    Pila *aux=pila;

    while(aux->siguiente!=NULL)
    {
        aux=aux->siguiente;
    }
    return aux->dato;
}

int pilaVacia(Pila *pila)
{
    int estado=0;
    if (pila==NULL)
    {
        estado=1;
    }
    return estado;
}

int desapilar(Pila *pila)
{
    int dato=0;
    if(pilaVacia(pila)==0)
    {
        Pila *aux=pila;
        Pila *anterior;

        while(aux!=NULL)
        {
            anterior=aux;
            aux=aux->siguiente;
        }
        dato=aux->dato;
        anterior->siguiente=NULL;
        free(aux);
    }
    return dato;
}


void mostrarPila(Pila *pila)
{
    if(pila!=NULL)
    {
        Pila *aux=pila;
        Pila *invertida=NULL;

        while(aux!=NULL)
        {
            apilar(invertida,aux->dato);
            aux=aux->siguiente;
        }
        while(invertida!=NULL)
        {
            printf("\n%i\n");
            invertida=invertida->siguiente;
        }
    }
}

nodoOrigen purgarAereosM3(nodoOrigen *listaOrigen)
{
    if(listaOrigen!=NULL)
    {

    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}

void extraerMenoresATres(nodoDestino *lista, Pila *pila)
{
    if(lista!=NULL)
    {
        nodoDestino *aux=lista;
        if(aux->tiempoViaje<=3)
        {
            apilar(pila,aux->tiempoViaje);
            lista=aux->sig;
            free(aux);
        }
        else
        {
            nodoDestino *ante=lista;
            aux=lista->sig;
            while(aux!=NULL)
            {
                if(aux->tiempoViaje<=3)
                {
                    apilar(pila,aux->tiempoViaje);
                    ante->sig=aux->sig;
                    free(aux);
                    aux=ante;
                }
            }
        }
    }
}
