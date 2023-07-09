#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int nota;
    char nombre[40];

}nota;

typedef struct
{
    char nombreMateria[20];
    nota notaAlumno;
}nodo;



int main()
{
    prueba_nodo_en_nodo_puntero();
}

void prueba_nodo_en_nodo_puntero()
{
    nodo *nuevoNodo=(nodo*)malloc(sizeof(nodo));
    strcpy(nuevoNodo->nombreMateria,"Materia de Prueba");

    nota nuevaNota=(nota){4,"Ignacio"};
    nuevoNodo->notaAlumno=nuevaNota;

    mostrarNotaEnNodoPuntero(nuevoNodo);

    free(nuevoNodo);
    return 0;
}

void mostrarNotaEnNodoPuntero(nodo *nodoPuntero)
{
    printf("MATERIA: %s, NOTA: %i, NOMBRE: %s",nodoPuntero->nombreMateria,nodoPuntero->notaAlumno.nota,nodoPuntero->notaAlumno.nombre);
}
