#ifndef ADL_C
#define ADL_C
#include <stdio.h>
#include <string.h>

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    int idMateria;
}registroArchivo;

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
}notaAlumno;

typedef struct _nodo
{
    notaAlumno dato;
    struct _nodo *siguiente;
} nodo;

typedef struct
{
    int idMateria;
    char materia[40];
    nodo * listaDeNotas;
}celda;

celda crearCeldaMateria(int idMateria, char materia[40]);
int insertarCelda(celda listaDeMaterias[],int validos,celda nuevaCelda);
int buscarCeldaMateria(celda listaMaterias[],char nombreMateria[40],int validos);
nodo *crearNodo(notaAlumno nuevaNota);
nodo *insertarAlPrincipio(nodo *lista,nodo *nuevo, notaAlumno notaAlumnoNueva);
int pasarDeArchivoToADL(celda materias[],int materiasValidas,char nombreArchivo[30]);
int validaNotaAprobada(nodo *nota, int valorLimite);
void pasarDeADLToArchivoDeAprobados(celda listaADL[],int validos, char archivoSalida[40]);


void escribirAArchivo(char nombreArchivo[40],registroArchivo registroNuevo);

#endif ADL_C


