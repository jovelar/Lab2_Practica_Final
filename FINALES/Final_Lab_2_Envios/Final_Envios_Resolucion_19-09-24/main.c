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

typedef struct
{
    int cantDestinosAereos;
    char ciudadOrigen[30];
    float costoPromedio;
    float tiempoPromedioAereo;
}destinosAereos;

typedef struct
{
    int cantDestinosFerro;
    char ciudadOrigen[30];
    float costoPromedioFerro;
    float tiempoPromedioFerro;
}destinosFerro;

typedef struct Pila
{
    int tiempoViaje;
    struct Pila *sig;
}Pila;

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

void mostrarListaDest(nodoDestino *lista);
void mostrarListaOrigen(nodoOrigen *lista);

void punto1(char nombreArchivo[50], nodoOrigen **lista);
//}

//Punto 2
//{
float promedioDARec(nodoOrigen *lista,nodoDestino *destinos,char nombre[30],int sumatoria,int contador);
void punto2(nodoOrigen *lista);
//}

//Punto 3
//{
destinosAereos crearDAereo(nodoDestino *destinoA,char origen[30]);
destinosFerro crearDFerro(nodoDestino *destinoF,char origen[30]);
void pasarA2A(nodoOrigen *listaOrigen,char archivoAereo[30],char archivoFerro[30]);
void punto3(nodoOrigen *lista,char archivoAereos[30],char archivoFerro[30]);
//}

//Punto 4
//{
Pila *inicPila();
Pila *apilar(Pila *pila,int dato);
int desapilar(Pila **pila);
int tope(Pila *pila);
int pilaVacia(Pila *pila);
Pila *pilaNueva(int dato);
void mostrarPila(Pila *pila);
//}

//Punto 5
//{
void exportarAPila(nodoOrigen **lista,Pila **pila);
void punto5(nodoOrigen **lista,Pila **pila);
nodoOrigen *borrarNodo(nodoOrigen *lista,nodoOrigen *nodoABorrar);
//}

//EXT (no forman parte del Final
//{
void borrarDestino(nodoDestino **listaDestino);
void borrarOrigen(nodoOrigen **listaOrigen);
void borrarPila(Pila **pila);
//}

int main()
{
    nodoOrigen *listaOrigen=inicOrigen();
    char nombreArchivo[]="registroEnvios.bin";
    punto1(nombreArchivo,&listaOrigen);
    //punto2(listaOrigen);
    Pila *pila=inicPila();
    punto5(&listaOrigen,&pila);
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

void mostrarListaDest(nodoDestino *lista)
{
    if(lista)
    {
        nodoDestino *iterador=lista;
        while(iterador)
        {
            printf("Nombre: %-20s Costo: %-6.2f T.Viaje: %i \n",iterador->nombre,iterador->costo,iterador->tiempoViaje);
            iterador=iterador->sig;
        }
    }
}

void mostrarListaOrigen(nodoOrigen *lista)
{
    if(lista)
    {
        nodoOrigen *iterador=lista;
        while(iterador)
        {
            printf("ORIGEN: %s \n",iterador->nombre);
            printf("Destinos Aereos *******\n");
            mostrarListaDest(iterador->destinosAereos);
            printf("Destinos Ferro +++++++\n");
            mostrarListaDest(iterador->destinosFerro);
            iterador=iterador->sig;
        }
    }
}

void punto1(char nombreArchivo[50], nodoOrigen **lista)
{
    *lista=pasarALDL(nombreArchivo);
    mostrarListaOrigen(*lista);
}
//}

//Punto 2
//{
float promedioDARec(nodoOrigen *lista,nodoDestino *destinos,char nombre[30],int sumatoria,int contador)
{
    if(!destinos) //Si la lista destinos esta vacia llego a su final
    {
        if(sumatoria>0 && contador>0)
        {
            sumatoria=sumatoria/(float)contador;
        }
    }
    else
    {
        if(strcmpi(lista->nombre,nombre)==0) //Si el origen es el correcto
        {
            sumatoria=sumatoria + destinos->tiempoViaje;
            sumatoria=promedioDARec(lista,destinos->sig,nombre,sumatoria,contador+1);
        }
        else if(lista->sig) //Si el origen no es el correcto y el proximo nodo de la lista de origenes no esta vacia, avanza al siguiente origen
        {
            nodoOrigen *aux=lista->sig;
            sumatoria=promedioDARec(aux,aux->destinosAereos,nombre,sumatoria,contador);
        }
    }
    return sumatoria;
}

void punto2(nodoOrigen *lista)
{
    printf("Ingrese un origen a buscar: ");
    char palabra[50];
    gets(palabra);
    float promedio=0.0;
    promedio=promedioDARec(lista,lista->destinosAereos,palabra,0,0);
    printf("El promedio es de %0.2f\n",promedio);
}
//}

//Punto 3
//{
destinosAereos crearDAereo(nodoDestino *destinoA,char origen[30])
{
    destinosAereos destino;
    if(destinoA)
    {
        int cantDestinos=0;
        float costoProm=0;
        int tiempoProm=0;
        int contador=0;

        nodoDestino *iterador=destinoA;
        while(iterador)
        {
            costoProm+=iterador->costo;
            tiempoProm+=iterador->tiempoViaje;
            cantDestinos++;
        }
        costoProm=costoProm/cantDestinos;
        tiempoProm=tiempoProm/cantDestinos;
        strcpy(destino.ciudadOrigen,origen);
        destino.cantDestinosAereos=cantDestinos;
        destino.costoPromedio=costoProm;
        destino.tiempoPromedioAereo=tiempoProm;
    }
    return destino;
}

destinosFerro crearDFerro(nodoDestino *destinoF,char origen[30])
{
    destinosFerro destino;
    if(destinoF)
    {
        int cantDestinos=0;
        float costoProm=0;
        int tiempoProm=0;
        int contador=0;

        nodoDestino *iterador=destinoF;
        while(iterador)
        {
            costoProm+=iterador->costo;
            tiempoProm+=iterador->tiempoViaje;
            cantDestinos++;
        }
        costoProm=costoProm/cantDestinos;
        tiempoProm=tiempoProm/cantDestinos;
        strcpy(destino.ciudadOrigen,origen);
        destino.cantDestinosFerro=cantDestinos;
        destino.costoPromedioFerro=costoProm;
        destino.tiempoPromedioFerro=tiempoProm;
    }
    return destino;
}
void pasarA2A(nodoOrigen *listaOrigen,char archivoAereo[30],char archivoFerro[30])
{
    if(listaOrigen)
    {
        nodoOrigen *iterador=listaOrigen;
        FILE *archivoA=fopen(archivoAereo,"wb");
        FILE *archivoF=fopen(archivoFerro,"wb");

        while(iterador)
        {
            destinosAereos bufferAero=crearDAereo(iterador->destinosAereos,iterador->nombre);
            destinosFerro bufferFerro=crearDFerro(iterador->destinosFerro,iterador->nombre);
            fwrite(&bufferAero,sizeof(destinosAereos),1,archivoA);
            fwrite(&bufferFerro,sizeof(destinosFerro),1,archivoF);
        }
        fclose(archivoA);
        fclose(archivoF);
    }
}
void punto3(nodoOrigen *lista,char archivoAereos[30],char archivoFerro[30])
{
    pasarA2A(lista,archivoAereos,archivoFerro);
}
//}

//Punto 4
//{
Pila *inicPila()
{
    return NULL;
}

Pila *apilar(Pila *pila,int dato)
{
    Pila *nueva=pilaNueva(dato);
    if(!pila)
    {
        pila=nueva;
    }
    else
    {
        nueva->sig=pila;
        pila=nueva;
    }
    return nueva;
}

int desapilar(Pila **pila)
{
    int dato=0;
    if(*pila)
    {
        Pila *aux=(*pila)->sig;
        dato=(*pila)->tiempoViaje;
        free(*pila);
        *pila=aux;
    }
    return dato;
}

int tope(Pila *pila)
{
    return pila->tiempoViaje;
}

int pilaVacia(Pila *pila)
{
    int estado=0;
    if(!pila)
    {
        estado=1;
    }
    return estado;
}

Pila *pilaNueva(int dato)
{
    Pila *nuevo=(Pila*)malloc(sizeof(Pila));
    nuevo->tiempoViaje=dato;
    nuevo->sig=NULL;

    return nuevo;
}

void mostrarPila(Pila *pila)
{
    if(pila)
    {
        Pila *iterador=pila;
        while(iterador)
        {
            printf("%i \n",iterador->tiempoViaje);
            iterador=iterador->sig;
        }
    }
}
//}

//Punto 5
//{
void exportarAPila(nodoOrigen **lista,Pila **pila)
{
    if(*lista)
    {
       nodoOrigen *iterOrigen=*lista;
       nodoOrigen *anteOrigen=NULL;
       while(iterOrigen)
       {
           nodoDestino *iterAereo=iterOrigen->destinosAereos;
           nodoDestino *anteAereo=NULL;
           while(iterAereo)
           {
               if(iterAereo->tiempoViaje<=300)
               {
                   if(!anteAereo)
                   {
                       nodoDestino *auxDestino=iterAereo->sig;
                       free(iterAereo);
                       iterOrigen->destinosAereos=auxDestino;
                       iterAereo=auxDestino;
                   }
                   else
                   {
                       anteAereo->sig=iterAereo->sig;
                       free(iterAereo);
                       iterAereo=anteAereo;
                   }
               }
               else
               {
                   anteAereo=iterAereo;
                   iterAereo=iterAereo->sig;
               }
           }
           if(!iterOrigen->destinosAereos && !iterOrigen->destinosFerro)
           {
               if(!anteOrigen)
               {
                   nodoOrigen *auxOrigen=iterOrigen->sig;
                   free(iterOrigen);
                   *lista=auxOrigen;
                   iterOrigen=auxOrigen;
               }
               else
               {
                   anteOrigen->sig=iterOrigen->sig;
                   free(iterOrigen);
                   iterOrigen=anteOrigen;
               }
           }
           anteOrigen=iterOrigen;
           iterOrigen=iterOrigen->sig;
        }
    }
}
void punto5(nodoOrigen **lista,Pila **pila)
{
    exportarAPila(lista,pila);
    mostrarPila(*pila);
    mostrarListaOrigen(*lista);
    borrarOrigen(lista);
    borrarPila(pila);
}

nodoOrigen *borrarNodo(nodoOrigen *lista,nodoOrigen *nodoABorrar)
{
    return lista;
}
//}

//EXT (no forman parte del Final
//{
void borrarDestino(nodoDestino **listaDestino)
{
    if(*listaDestino)
    {
        nodoDestino *aux=NULL;
        while(*listaDestino)
        {
            aux=(*listaDestino)->sig;
            free(*listaDestino);
            *listaDestino=aux;
        }
    }
}

void borrarOrigen(nodoOrigen **listaOrigen)
{
    if(*listaOrigen)
    {
        while(*listaOrigen)
        {
            nodoOrigen *aux=(*listaOrigen)->sig;
            borrarDestino(&((*listaOrigen)->destinosAereos));
            borrarDestino(&((*listaOrigen)->destinosFerro));
            free(*listaOrigen);
            *listaOrigen=aux;
        }
    }
}
void borrarPila(Pila **pila)
{
    if(*pila)
    {
        while(*pila)
        {
            Pila *aux=(*pila)->sig;
            free(*pila);
            *pila=aux;
        }
    }
}
//}
