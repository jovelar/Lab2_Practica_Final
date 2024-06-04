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
} registroEnvios;

typedef struct
{
    char nombre[30];
    float costo;
    int tiempoViaje;
    struct nodoDestino *sig;
} nodoDestino;

typedef struct
{
    char nombre[30];
    nodoDestino *destinosAereos;
    nodoDestino *destinosFerro;
    struct nodoOrigen *sig;
} nodoOrigen;

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

void mostrarlistDestinos(nodoDestino *lista);


//EJERCICIO 2
float promedioRecursivo(nodoOrigen *lista,nodoDestino *destinoAereo,char origen[30],float tiempo,int contador);
float promRecLista(nodoDestino *lista,float tiempo,int contador);

float promedioIT(nodoOrigen *lista,char origen[30]);
float promedioRec2(nodoOrigen *lista,nodoDestino *destinoAereo,char origen[30],float tiempo,int contador);
void ejercicio2(nodoOrigen *lista,char origen[30]);

//EJERCICIO 3

typedef struct
{
    int cantDestinosAereos;
    char ciudadOrigen[30];
    float costoPromedioAereo;
    float tiempoPromedioAereo;
} destinosAereos;

typedef struct
{
    int cantDestinosFerro;
    char ciudadOrigen[30];
    float costoPromedioFerro;
    float tiempoPromedioFerro;
} destinosFerro;

int cuentaDestinos(nodoDestino *lista);
float costoPromedio(nodoDestino *lista);
float tiempoPromedio(nodoDestino *lista);
destinosAereos *crearNuevoAereo(int cantDestinos,char origen[30],float costoPromedio,float tiempoPromedio);
destinosFerro *crearNuevoFerro(int cantDestinos,char origen[30],float costoPromedio,float tiempoPromedio);
void persistirA2(nodoOrigen *lista, char archivoDAereos[50],char archivosDFerro[50]);
void ejercicio3(nodoOrigen *lista, char archivoAviones[30],char archivosFerro[30]);

//SOLO DE PRUEBA
void mostrarDAereo(char nombreArchivo[30]);
void mostrarDFerro(char nombreArchivo[30]);

typedef struct
{
    int tiempoViaje;
    struct Pila *sig;
}Pila;

Pila *inicPila();
Pila *apilar(Pila *pila,int tiempoNuevo);
int desapilar(Pila **pila);
int tope(Pila *pila);
int pilaVacia(Pila *pila);
void mostrarPila(Pila *pila);

//EJERCICIO 4

void extraerAPila(nodoOrigen **origen,Pila *pila, int tiempoLimite);
void ejercicio4(nodoOrigen **origen, Pila **pila);

int main()
{
    nodoOrigen *lista=NULL;
    char nombreArchivo[30]="registroEnvios.bin";
    ejercicio1(&lista,nombreArchivo);
    ejercicio2(lista,"ROSARIO");
    ejercicio3(lista,"aviones.bin","trenes.bin");
    printf("\n ####### AVIONES #######\n");
    mostrarDAereo("aviones.bin");
    printf("\n@@@@@@@ TRENES @@@@@@@");
    mostrarDFerro("trenes.bin");
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

void mostrarlistDestinos(nodoDestino *lista)
{
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            printf("\n %s %i \n",iterador->nombre,iterador->tiempoViaje);
            iterador=iterador->sig;
        }
    }
}


float promedioRecursivo(nodoOrigen *lista,nodoDestino *destinoAereo,char origen[30],float tiempo,int contador)
{
    float total=0.0;

    if(!destinoAereo)
    {
        if(tiempo>0 && contador>0)
        {
            total=tiempo/contador;
        }
    }
    else
    {
        if(strcmpi(lista->nombre,origen)==0 && destinoAereo)
        {
            tiempo+=destinoAereo->tiempoViaje;
            contador++;
            total=promedioRecursivo(lista,destinoAereo->sig,origen,tiempo,contador);
        }
        else
        {
            if(lista->sig)
            {
                nodoOrigen *aux=lista->sig;
                total=promedioRecursivo(aux,aux->destinosAereos,origen,tiempo,contador);
            }
        }
    }
    return total;
}

void ejercicio2(nodoOrigen *lista,char origen[30])
{
    printf("\n CIUDAD: %s \n",origen);
    float promedio=promedioRecursivo(lista,lista->destinosAereos,origen,0,0);
    printf("\n Promedio %0.2f \n",promedio);
}

int cuentaDestinos(nodoDestino *lista)
{
    int cantidad=0;
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            cantidad++;
            iterador=iterador->sig;
        }
    }

    return cantidad;
}

float costoPromedio(nodoDestino *lista)
{
    float promedio=0;
    int cantidad=0;
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            promedio+=iterador->costo;
            cantidad++;
            iterador=iterador->sig;
        }
        promedio=promedio/cantidad;
    }
    return promedio;
}

float tiempoPromedio(nodoDestino *lista)
{
    float promedio=0;
    int cantidad=0;
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            promedio+=iterador->tiempoViaje;
            cantidad++;
            iterador=iterador->sig;
        }
        promedio=promedio/cantidad;
    }
    return promedio;
}

destinosAereos *crearNuevoAereo(int cantDestinos,char origen[30],float costoPromedio,float tiempoPromedio)
{
    destinosAereos *nuevo=(destinosAereos*)malloc(sizeof(destinosAereos));
    nuevo->cantDestinosAereos=cantDestinos;
    strcpy(nuevo->ciudadOrigen,origen);
    nuevo->costoPromedioAereo=costoPromedio;
    nuevo->tiempoPromedioAereo=tiempoPromedio;

    return nuevo;
}

destinosFerro *crearNuevoFerro(int cantDestinos,char origen[30],float costoPromedio,float tiempoPromedio)
{
    destinosFerro *nuevo=(destinosFerro*)malloc(sizeof(destinosFerro));
    nuevo->cantDestinosFerro=cantDestinos;
    strcpy(nuevo->ciudadOrigen,origen);
    nuevo->costoPromedioFerro=costoPromedio;
    nuevo->tiempoPromedioFerro=tiempoPromedio;

    return nuevo;
}

void persistirA2(nodoOrigen *lista, char archivoDAereos[50],char archivosDFerro[50])
{
    if(lista)
    {
        nodoOrigen *iterador=lista;

        FILE *archivoAereo=fopen(archivoDAereos,"wb");
        if(archivoAereo)
        {
            FILE *archivoFerro=fopen(archivosDFerro,"wb");
            if(archivoFerro)
            {
                while(iterador)
                {
                    destinosAereos *auxAereo;
                    int cantDestino=cuentaDestinos(iterador->destinosAereos);
                    float costoProm=costoPromedio(iterador->destinosAereos);
                    float tiempoProm=tiempoPromedio(iterador->destinosAereos);

                    auxAereo=crearNuevoFerro(cantDestino,iterador->nombre,costoProm,tiempoProm);
                    fwrite(auxAereo,sizeof(destinosAereos),1,archivoAereo);

                    destinosFerro *auxFerro;
                    cantDestino=cuentaDestinos(iterador->destinosFerro);
                    costoProm=costoPromedio(iterador->destinosFerro);
                    tiempoProm=tiempoPromedio(iterador->destinosFerro);
                    auxFerro=crearNuevoFerro(cantDestino,iterador->nombre,costoProm,tiempoProm);

                    fwrite(auxFerro,sizeof(destinosFerro),1,archivoFerro);

                    iterador=iterador->sig;

                }
                fclose(archivoFerro);
            }
            fclose(archivoAereo);
        }
    }
}

void ejercicio3(nodoOrigen *lista, char archivoAviones[30],char archivosFerro[30])
{
    persistirA2(lista,archivoAviones,archivosFerro);
}

void mostrarDAereo(char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        destinosAereos buffer;
        while(fread(&buffer,sizeof(destinosAereos),1,archivo)>0)
        {
            printf("\n ORIGEN: %s CANT: %i COSTO.PROM: %0.2f TIEMPO.PROM: %0.2f \n",buffer.ciudadOrigen,buffer.cantDestinosAereos,buffer.costoPromedioAereo,buffer.tiempoPromedioAereo);
        }
        fclose(archivo);
    }
}
void mostrarDFerro(char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        destinosFerro buffer;
        while(fread(&buffer,sizeof(destinosFerro),1,archivo)>0)
        {
            printf("\n ORIGEN: %s CANT: %i COSTO.PROM: %0.2f TIEMPO.PROM: %0.2f \n",buffer.ciudadOrigen,buffer.cantDestinosFerro,buffer.costoPromedioFerro,buffer.tiempoPromedioFerro);
        }
        fclose(archivo);
    }
}

Pila *inicPila()
{
    return NULL;
}

Pila *apilar(Pila *pila,int tiempoNuevo)
{
    Pila *nuevo=(Pila*)malloc(sizeof(Pila));
    pila->tiempoViaje=tiempoNuevo;
    pila->sig=NULL;

    if(!pila)
    {
        pila=nuevo;
    }
    else
    {
        nuevo->sig=pila;
        pila=nuevo;
    }
    return pila;
}

int desapilar(Pila **pila)
{
    int valorRetorno=0;

    if(*pila)
    {
        Pila *aux=(*pila)->sig;
        valorRetorno=(*pila)->tiempoViaje;
        free(*pila);
        *pila=aux;
    }
    else
    {
        printf("\nLa pila esta vacia!");
    }
}

int tope(Pila *pila)
{
    return pila->tiempoViaje;
}

int pilaVacia(Pila *pila)
{
    return (pila==NULL) ? 1 : 0;
}

void mostrarPila(Pila *pila)
{
    if(pila)
    {
        Pila *iterador=pila;
        printf("\nTOPE\n");
        while(iterador)
        {
            printf("\n %i ",iterador->tiempoViaje);
            iterador=iterador->sig;
        }
        printf("\n BASE");
    }
}

//EJERCICIO 4

void extraerAPila(nodoOrigen **origen,Pila *pila, int tiempoLimite)
{
    if(lista)
    {
        nodoOrigen *iterador=lista;
        nodoOrigen *ante=NULL;
        while(iterador)
        {
            nodoDestino *iterAereo=iterador->destinosAereos;
            nodoDestino *anteAereo=NULL;
            while(iterAereo)
            {
                if(iterAereo->tiempoViaje<= tiempoLimite)
                {

                }
            }
        }
    }
}
void ejercicio4(nodoOrigen **origen, Pila **pila);
