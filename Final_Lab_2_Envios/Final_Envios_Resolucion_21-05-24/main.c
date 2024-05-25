#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char origen[30];
    char destino[30];
    char tipo[30]; //aereo, ferrocarril
    float costo;
    int tiempoViaje;
}registroEnvios;

typedef struct
{
    char nombre[30];
    float costo;
    int tiempoViaje;
    struct nodoDestino *sig;
}nodoDestino;

typedef struct
{
    char nombre[30];
    nodoDestino *destinosAereos;
    nodoDestino *destinosFerro;
    struct nodoOrigen *sig;
}nodoOrigen;

//EJERCICIO 1
nodoDestino *iniciDest();
nodoDestino *crearNDestino(char nombre[30],float costo,int tiempoDestino);
nodoDestino *agregarNDfinal(nodoDestino *lista,nodoDestino *nuevo);

nodoOrigen *iniicOrigen();
nodoOrigen *crearNOrigen(char nombre[30]);
nodoOrigen *agregarNOOrdREC(nodoOrigen *lista,nodoOrigen *nuevo);
nodoOrigen *buscarOrig(nodoOrigen *lista,char nombreOrigen[30]);
nodoOrigen *pasarALDL(char nombreArchivo[30]);

void ejercicio1(nodoOrigen **lista,char nombreArchivo[30]);

void mostrarLista(nodoOrigen *lista);


//EJERCICIO 2
float promedioRecursivo(nodoOrigen *lista,char origen[50],float sumatoria,int elementos);
float promRecLista(nodoDestino *lista,int tiempo,int contador);

float promedioIT(nodoOrigen *lista,char origen[30]);
float promedioRec2(nodoOrigen *lista,char origen[30],float tiempos,int elementos);
void ejercicio2(nodoOrigen *lista,char origen[30]);

int main()
{
    nodoOrigen *lista=NULL;
    char nombreArchivo[30]="registroEnvios.bin";
    ejercicio1(&lista,nombreArchivo);
    ejercicio2(lista,"caba");
    return 0;
}

//EJERCICIO 1
nodoDestino *iniciDest()
{
    return NULL;
}

nodoDestino *crearNDestino(char nombre[30],float costo,int tiempoDestino)
{
    nodoDestino *nuevo=(nodoDestino*)malloc(sizeof(nodoDestino));
    strcpy(nuevo->nombre,nombre);
    nuevo->costo=costo;
    nuevo->tiempoViaje=tiempoDestino;
    nuevo->sig=NULL;
    return nuevo;
}
nodoDestino *agregarNDfinal(nodoDestino *lista,nodoDestino *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodoDestino *iterador=lista;
        while(iterador->sig!=NULL)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }
    return lista;
}

nodoOrigen *iniicOrigen()
{
    return NULL;
}

nodoOrigen *crearNOrigen(char nombre[30])
{
    nodoOrigen *nuevo=(nodoOrigen*)malloc(sizeof(nodoOrigen));
    strcpy(nuevo->nombre,nombre);
    nuevo->destinosAereos=NULL;
    nuevo->destinosFerro=NULL;
    nuevo->sig=NULL;
    return nuevo;
}

nodoOrigen *agregarNOOrdREC(nodoOrigen *lista,nodoOrigen *nuevo)
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
            lista->sig=agregarNOOrdREC(lista->sig,nuevo);
        }
    }

    return lista;
}

nodoOrigen *buscarOrig(nodoOrigen *lista,char nombreOrigen[30])
{
    nodoOrigen *posicion=NULL;

    if(lista)
    {
        nodoOrigen *iterador=lista;
        while(iterador && !posicion)
        {
            if(strcmpi(iterador->nombre,nombreOrigen)==0)
            {
                posicion=iterador;
            }
            iterador=iterador->sig;
        }
    }
    return posicion;
}

nodoOrigen *pasarALDL(char nombreArchivo[30])
{
    nodoOrigen *resultante=NULL;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroEnvios buffer;
        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            nodoDestino *nuevo=crearNDestino(buffer.destino,buffer.costo,buffer.tiempoViaje);
            nodoOrigen *posicion=buscarOrig(resultante,buffer.origen);
            if(!posicion)
            {
                nodoOrigen *nuevoOr=crearNOrigen(buffer.origen);
                resultante=agregarNOOrdREC(resultante,nuevoOr);
                posicion=nuevoOr;
            }
            if(strcmpi(buffer.tipo,"aereo")==0)
            {
                posicion->destinosAereos=agregarNDfinal(posicion->destinosAereos,nuevo);
            }
            else
            {
                posicion->destinosFerro=agregarNDfinal(posicion->destinosFerro,nuevo);
            }
        }
        fclose(archivo);
    }
    return resultante;
}

void ejercicio1(nodoOrigen **lista,char nombreArchivo[30])
{
    *lista=pasarALDL(nombreArchivo);
    mostrarLista(*lista);
}

void mostrarLista(nodoOrigen *lista)
{
    int contador=0;
    if(lista)
    {
        nodoOrigen *aux=lista;
        while(aux)
        {
            printf("******* %s *******\n",aux->nombre);
            nodoDestino *aux2=aux->destinosAereos;
            nodoDestino *aux3=aux->destinosFerro;

            printf("XXXXXXXX AEREOS XXXXXXX\n");
            while(aux2)
            {
                printf(" %s %0.2f \n",aux2->nombre,aux2->costo);
                aux2=aux2->sig;
            }

            printf("XXXXXXX FERRO XXXXXXX\n");
            while(aux3)
            {
                printf(" %s %0.2f \n",aux3->nombre,aux3->costo);
                aux3=aux3->sig;
            }
            aux=aux->sig;
        }
    }
}

float promRecLista(nodoDestino *lista,int tiempo,int contador)
{
    float total=0.0;
    if(!lista)
    {
        if(tiempo!=0 && contador!=0)
        {
            total=(float)tiempo/contador;
        }
    }
    else
    {
        tiempo+=lista->tiempoViaje;
        contador++;

        total=promRecLista(lista->sig,tiempo,contador);
    }
    return total;
}


float promedioRecursivo(nodoOrigen *lista,char origen[50],float sumatoria,int elementos)
{
    if(lista)
    {
        if(strcmp(lista->nombre,origen)==0)
        {
            nodoDestino *aux=lista->destinosAereos;
            while(aux)
            {
                sumatoria+=aux->tiempoViaje;
                elementos++;
                aux=aux->sig;
            }
        }
        sumatoria=promedioRecursivo(lista->sig,origen,sumatoria,elementos);
    }
    return sumatoria;
}

float promedioIT(nodoOrigen *lista,char origen[30])
{
    float total=0;
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
                    total+=it->tiempoViaje;
                    contador++;
                    it=it->sig;
                }
                total=total/contador;
            }
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("lista vacia!");
    }
    return total;
}

float promedioRec2(nodoOrigen *lista,char origen[30],float tiempos,int elementos)
{
    float resultado=0;
    if(lista)
    {
        if(tiempos!=0 && elementos!=0)
        {
            resultado=tiempos/elementos;
        }
    }
    else
    {
        if(strcmpi(lista->nombre,origen)==0)
        {
            nodoDestino *aux=lista->destinosAereos;
            while(aux)
            {
                tiempos+=aux->tiempoViaje;
                elementos++;
                aux=aux->sig;
            }
        }
        else
        {
            resultado=promedioRec2(lista->sig,origen,tiempos,elementos);
        }
    }
    return resultado;
}

void ejercicio2(nodoOrigen *lista,char origen[30])
{

    //float promedio=promedioRecursivo(lista,origen,0,0);
    float promedio=promedioRec2(lista,origen,0,0);
    //float promedio=promedioIT(lista,origen);
    printf("\n\npromedio viaje: %0.2f \n\n",promedio);
}
