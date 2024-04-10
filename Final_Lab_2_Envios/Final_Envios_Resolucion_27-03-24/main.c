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

typedef struct nodoDestino
{
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

//Punto 1

void pasarACVC(char nombreArchivo[40]);

nodoOrigen *inicOrigen();
nodoOrigen *crearNodoOrigen(char nombre[30]);
nodoOrigen *agregarOrdenadoRec(nodoOrigen *lista,nodoOrigen *nuevo);

nodoDestino *crearNodoDestino(char nombre[30],float costo,int tiempoViaje);
nodoDestino *inicDestino();
nodoDestino *agregarOrdenado(nodoDestino *lista, nodoDestino *nuevo);

nodoOrigen *pasarALDL(char nombreArchivo[40]);
nodoOrigen *buscarOrigen(char nombreOrigen[30],nodoOrigen *listaOrigen);

void mostrarNDestino(nodoDestino *nodo);

void mostrarNOrigen(nodoOrigen *nodo);
void mostrarNodosDestino(nodoDestino *lista);
void mostrarTodo(nodoOrigen *lista);

void ejercicio1(char nombreArchivo[50],nodoOrigen **lista);

//Punto 2

float promedioRecursivo(nodoOrigen *lista,char origen[50],float sumatoria,int elementos);

//punto 3

void pasarAListasSeparadas(nodoOrigen *lista);


void ejercicio2(nodoOrigen *lista);
void ejercicio3();
void ejercicio4();
void ejercicio5();




int main()
{
    nodoOrigen *lista=NULL;
    char nombreArchivo[50]="registroEnvios.bin";
    ejercicio1(nombreArchivo,&lista);
    ejercicio2(lista);
    //pasarACVC("registroEnvios.bin");
    return 0;
}

//Punto 1

nodoOrigen *inicOrigen()
{
    return NULL;
}

nodoOrigen *crearNodoOrigen(char nombre[30])
{
    nodoOrigen *nuevo=(nodoOrigen*)malloc(sizeof(nodoOrigen));
    strcpy(nuevo->nombre,nombre);
    nuevo->destinosAereos=NULL;
    nuevo->destinosFerro=NULL;
    nuevo->sig=NULL;
    return nuevo;
}

nodoDestino *agregarOrdenado(nodoDestino *lista, nodoDestino *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->nombre,nuevo->nombre)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodoDestino *iterador=lista;
            nodoDestino *ante;
            while(iterador && strcmpi(iterador->nombre,nuevo->nombre)<0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            if(!iterador)
            {
                ante->sig=nuevo;
            }
            else
            {
                ante->sig=nuevo;
                nuevo->sig=iterador;
            }
        }
    }
    return lista;
}

nodoOrigen *agregarOrdenadoRec(nodoOrigen *lista,nodoOrigen *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->nombre,nuevo->nombre)<0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=agregarOrdenadoRec(lista->sig,nuevo);
        }
    }
    return lista;
}

nodoDestino *crearNodoDestino(char nombre[30],float costo,int tiempoViaje)
{
    nodoDestino *nuevo=(nodoDestino*)malloc(sizeof(nodoDestino));
    strcpy(nuevo->nombre,nombre);
    nuevo->costo=costo;
    nuevo->tiempoViaje=tiempoViaje;
    nuevo->sig=NULL;

    return nuevo;
}

nodoDestino *inicDestino()
{
    return NULL;
}


nodoOrigen *pasarALDL(char nombreArchivo[40])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    nodoOrigen *listaDeLista=NULL;
    if(archivo)
    {
        registroEnvios buffer;
        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            nodoDestino *nuevo=crearNodoDestino(buffer.destino,buffer.costo,buffer.tiempoViaje);
            nodoOrigen *posicionInsertar=buscarOrigen(buffer.origen,listaDeLista);
            if(!posicionInsertar)
            {
                nodoOrigen *nuevoOrigen=crearNodoOrigen(buffer.origen);
                listaDeLista=agregarOrdenadoRec(listaDeLista,nuevoOrigen);
                posicionInsertar=nuevoOrigen;
            }
            if(strcmpi(buffer.tipo,"aereo")==0)
            {
                posicionInsertar->destinosAereos=agregarOrdenado(posicionInsertar->destinosAereos,nuevo);
            }
            else
            {
                posicionInsertar->destinosFerro=agregarOrdenado(posicionInsertar->destinosFerro,nuevo);
            }
        }
        fclose(archivo);
    }
    return listaDeLista;
}

nodoOrigen *buscarOrigen(char nombreOrigen[30],nodoOrigen *listaOrigen)
{
    nodoOrigen *resultado=NULL;

    if(listaOrigen)
    {
        nodoOrigen *iterador=listaOrigen;

        while(iterador && !resultado)
        {
            if(strcmpi(iterador->nombre,nombreOrigen)==0)
            {
                resultado=iterador;
            }
            iterador=iterador->sig;

        }
    }

    return resultado;
}

void mostrarNDestino(nodoDestino *nodo)
{
    if(nodo)
    {
        printf("%s %0.2f %i\n",nodo->nombre,nodo->costo,nodo->tiempoViaje);
    }
}

void mostrarNOrigen(nodoOrigen *nodo)
{
    if(nodo)
    {
        printf("\n %s ",nodo->nombre);
    }
}
void mostrarNodosDestino(nodoDestino *lista)
{
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            mostrarNDestino(iterador);
            iterador=iterador->sig;
        }
    }
}

void mostrarTodo(nodoOrigen *lista)
{
    if(lista)
    {
        nodoOrigen *iterador=lista;
        while(iterador)
        {
            printf("\nORIGEN: %s\n",iterador->nombre);
            printf("DESTINOS AEREOS\n\n");
            mostrarNodosDestino(iterador->destinosAereos);
            printf("\nDESTINOS FERROCARRIL\n\n");
            mostrarNodosDestino(iterador->destinosFerro);
            iterador=iterador->sig;
        }
    }
}





void ejercicio1(char nombreArchivo[50],nodoOrigen **lista)
{
    *lista=pasarALDL(nombreArchivo);
    mostrarTodo(*lista);
}

//Punto 2

float promedioRecursivo(nodoOrigen *lista,char origen[50],float sumatoria,int elementos)
{
    if(lista)
    {
        if(strcmpi(lista->nombre,origen)==0)
        {
            nodoDestino *temp=lista->destinosAereos;
            while(temp)
            {
                sumatoria+=temp->costo;
                elementos++;
                temp=temp->sig;
            }
            sumatoria=sumatoria/elementos;
        }
        sumatoria=promedioRecursivo(lista->sig,origen,sumatoria,elementos);
    }
    return sumatoria;
}

float promedioIt(nodoOrigen *lista,char origen[50])
{
    float sumatoria=0.0;
    int contador=0;
    if(lista)
    {
        nodoOrigen *iterador=lista;
        while(iterador)
        {
            if(strcmpi(iterador->nombre,origen)==0)
            {
                nodoDestino *it=iterador->destinosAereos;
                while(it)
                {
                    sumatoria+=it->costo;
                    contador++;
                    it=it->sig;
                }
            }
            iterador=iterador->sig;
        }

        if(contador>0)
        {
            sumatoria=sumatoria/contador;
        }
    }

    return sumatoria;
}



void ejercicio2(nodoOrigen *lista)
{
    printf("\nIngrese una ciudad correspondiente a un destino aereo: ");
    char destino[50];
    gets(destino);
    //float promedio=promedioIt(lista,destino);
    float promedio=promedioRecursivo(lista,destino,0.0,0);
    printf("\nEl promedio es de %0.2f ",promedio);

}

void pasarAListasSeparadas(nodoOrigen *lista)
{
    FILE *archivoDAereos=fopen("DestinosAereos.bin","wb");
    FILE *archivoFerro=fopen("DestinosFerro.bin","wb");
    nodoOrigen *iteradorO=lista;
    while(iteradorO)
    {

    }
}

void pasarACVC(char nombreArchivo[40])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        FILE *archivoSalida=fopen("registros.csv","wb");
        registroEnvios buffer;

        fprintf(archivoSalida,"ORIGEN;DESTINO;TIPO;TIEMPO;COSTO\n");

        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            fprintf(archivoSalida,"%s;%s;%s;%i;%0.2f\n",buffer.origen,buffer.destino,buffer.tipo,buffer.tiempoViaje,buffer.costo);
        }
        fclose(archivoSalida);
        fclose(archivo);

    }
}
