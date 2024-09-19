#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char origen[30];
    char destino[30];
    char tipo[30]; //aereo, ferrocarril
    float costo;
    int tiempoEnvio;
}registroEnvios;

typedef struct nodoDestino
{
    char nombre[30];
    float costo;
    int tiempoViaje;
    struct nodoDestino *sig;
}nodoDestino;

typedef struct nodoOrigen
{
    char nombre[30];
    nodoDestino *destinosAereos;
    nodoDestino *destinosFerro;
    struct nodoOrigen *sig;
}nodoOrigen;

//Punto 1
//{
nodoOrigen *inicOrigen();
nodoOrigen *crearOrigen(char nombre[30]);
nodoOrigen *insertarOrdenadoREC(nodoOrigen *lista, nodoOrigen *nuevo);
nodoOrigen *buscarOrigen(nodoOrigen *lista, char nombreOrigen[30]);

nodoDestino *inicDestino();
nodoDestino *crearDestino(char nombre[30],float costo,int tiempoViaje);
nodoDestino *insertarAlFinal(nodoDestino *lista,nodoDestino *nuevo);

nodoOrigen *pasarALDL(char nombreArchivo[50]);

void punto1(char nombreArchivo[50], nodoOrigen **lista);
//}


//Punto 2
//{
float promedioDARec(nodoOrigen *lista,nodoDestino *destinos,char nombre[30],int sumatoria,int contador);
void punto2(nodoOrigen *lista);
//}

int main()
{
    nodoOrigen *listaOrigen=inicOrigen();
    char nombreArchivo[]="registroEnvios.bin";
    punto1(nombreArchivo,&listaOrigen);
    punto2(listaOrigen);
    return 0;
}



//Punto 1
//{
nodoOrigen *inicOrigen()
{
    return NULL;
}

nodoOrigen *crearOrigen(char nombre[30])
{
    nodoOrigen *nuevo=(nodoOrigen*)malloc(sizeof(nodoOrigen));
    strcpy(nuevo->nombre,nombre);
    nuevo->destinosAereos=NULL;
    nuevo->destinosFerro=NULL;
    nuevo->sig=NULL;

    return nuevo;
}
nodoOrigen *insertarOrdenadoREC(nodoOrigen *lista, nodoOrigen *nuevo)
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
            nodoOrigen *ante=NULL;
            nodoOrigen *iterador=lista;

            while(iterador && strcmpi(iterador->nombre,nuevo->nombre)>0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->sig=iterador;
        }
    }
    return lista;
}

nodoOrigen *buscarOrigen(nodoOrigen *lista, char nombreOrigen[30])
{
    nodoOrigen *ubicacion=NULL;
    if(lista)
    {
        if(strcmpi(lista->nombre,nombreOrigen)==0)
        {
            ubicacion=lista;
        }
        else
        {
            nodoOrigen *iterador=lista;
            while(iterador && !ubicacion)
            {
                if(strcmpi(iterador->nombre,nombreOrigen)==0)
                {
                    ubicacion=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }
    return ubicacion;
}

nodoDestino *inicDestino()
{
    return NULL;
}

nodoDestino *crearDestino(char nombre[30],float costo,int tiempoViaje)
{
    nodoDestino *nuevo=(nodoDestino*)malloc(sizeof(nodoDestino));
    strcpy(nuevo->nombre,nombre);
    nuevo->costo=costo;
    nuevo->tiempoViaje=tiempoViaje;
    nuevo->sig=NULL;

    return nuevo;
}

nodoDestino *insertarAlFinal(nodoDestino *lista,nodoDestino *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodoDestino *iterador=lista;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }
    return lista;
}

nodoOrigen *pasarALDL(char nombreArchivo[50])
{
    nodoOrigen *listaOrigen=inicOrigen();
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroEnvios buffer;
        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            nodoDestino *nuevoDestino=crearDestino(buffer.destino,buffer.costo,buffer.tiempoEnvio);
            nodoOrigen *posicion=buscarOrigen(listaOrigen,buffer.origen);
            if(!posicion)
            {
                nodoOrigen *nuevoOrigen=crearOrigen(buffer.origen);
                listaOrigen=insertarOrdenadoREC(listaOrigen,nuevoOrigen);
                posicion=nuevoOrigen;
            }
            if(strcmpi(buffer.tipo,"aereo")==0)
            {
                posicion->destinosAereos=insertarAlFinal(posicion->destinosAereos,nuevoDestino);
            }
            else
            {
                posicion->destinosFerro=insertarAlFinal(posicion->destinosFerro,nuevoDestino);
            }
        }
        fclose(archivo);
    }
    return listaOrigen;
}

void punto1(char nombreArchivo[50], nodoOrigen **lista)
{
    *lista=pasarALDL(nombreArchivo);
}
//}

//Punto 2
//{
float promedioDARec(nodoOrigen *lista,nodoDestino *destinos,char nombre[30],int sumatoria,int contador)
{
    if(!lista)
    {
        if(sumatoria>0 && contador>0)
        {
            sumatoria=sumatoria/contador;
        }
    }
    else
    {
        if(strcmpi(lista->nombre,nombre)==0)
        {
            sumatoria+=destinos->tiempoViaje;
            contador++;
            sumatoria=promedioDARec(lista,destinos->sig,nombre,sumatoria,contador);
        }
        else
        {
            nodoOrigen *aux=lista->sig;
            sumatoria=promedioDARec(aux,aux->destinosAereos,nombre,sumatoria,contador);
        }
    }
    return sumatoria;
}

void punto2(nodoOrigen *lista)
{
    printf("Ingrese un origen a buscar");
    char palabra[50];
    gets(palabra);
    float promedio=0.0;
    promedio=promedioDARec(lista,lista->destinosAereos,palabra,0,0);
    printf("El promedio es de %0.2f\n",promedio);
}
//}
