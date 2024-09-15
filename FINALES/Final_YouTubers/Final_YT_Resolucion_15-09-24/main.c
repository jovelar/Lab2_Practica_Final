#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombreCanal[40];
    char rubro[30];
    int cantSuscriptores;
    int cantVistasSemestre;
}stYoutuber;

typedef struct
{
    char rubro[30];
}stRubro;

typedef struct
{
    int id;
    char nombreCanal[40];
    int cantSuscriptores;
    int cantVistasSemestre;
}stYoutubers;

typedef struct
{
    stYoutubers youtubers;
    struct nodoArbol *izq;
    struct nodoArbol *der;
}nodoArbol;

typedef struct
{
    stRubro rubro;
    nodoArbol *arbol;
}celdaRubro;

//Punto 1
//{
nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(int id, char nombreCanal[40],int cantSuscriptores,int cantVistasSemestre);
nodoArbol *insertarOrdRec(nodoArbol *arbol,nodoArbol *nuevo);

celdaRubro crearCeldaRubro(char rubro[40]);
int buscarRubro(celdaRubro arreglo[],char nombreRubro[40],int validos);

void pasarAADA(celdaRubro arreglo[],char nombreArchivo[40],int *validos);
//}

int main()
{
    return 0;
}

//Punto 1
//{
nodoArbol *inicArbol()
{
    return NULL;
}
nodoArbol *crearNodoArbol(int id, char nombreCanal[40],int cantSuscriptores,int cantVistasSemestre)
{
    nodoArbol *nuevo=(nodoArbol*)malloc(sizeof(nodoArbol));
    stYoutubers nuevoYT;
    strcpy(nuevoYT.nombreCanal,nombreCanal);
    nuevoYT.cantSuscriptores=cantSuscriptores;
    nuevoYT.cantVistasSemestre=cantVistasSemestre;
    nuevo->youtubers=nuevoYT;
    nuevo->der=NULL;
    nuevo->izq=NULL;

    return nuevo;
}
nodoArbol *insertarOrdRec(nodoArbol *arbol,nodoArbol *nuevo)
{
    if(arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(strcmpi(arbol->youtubers.nombreCanal,nuevo->youtubers.nombreCanal)<0)
        {
            arbol->der=insertarOrdRec(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertarOrdRec(arbol->izq,nuevo);
        }
    }
    return arbol;
}

celdaRubro crearCeldaRubro(char rubro[40])
{
    celdaRubro nuevo;
    stRubro nuevoRubro;
    strcpy(nuevoRubro.rubro,rubro);
    nuevo.rubro=nuevoRubro;
    nuevo.arbol=NULL;

    return nuevo;
}

int buscarRubro(celdaRubro arreglo[],char nombreRubro[40],int validos)
{
    int posicion=-1;
    int contador=0;
    while(contador<validos && posicion==-1)
    {
        if(strcmpi(arreglo[contador].rubro.rubro,nombreRubro)==0)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

void pasarAADA(celdaRubro arreglo[],char nombreArchivo[40],int *validos)
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        fclose(archivo);
    }
}
//}
