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
    //prueba_nodo_en_nodo_puntero();
    prueba_ordenamiento_por_seleccion();
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

void prueba_ordenamiento_por_seleccion()
{
    int numeros[]={6,8,1,2,5,6,7,5,6,4,24,0,366,1200};
    printf("\n lista original\n");
    for(int x=0;x<9;x++)
    {
        printf("%i ",numeros[x]);
    }

    int posMenor=0;
    int temp=0;
    for(int x=0;x<14;x++)
    {
        posMenor=x;
        for(int z=x+1;z<14;z++)
        {
            if(numeros[z]<=numeros[posMenor])
            {
                posMenor=z;
            }
        }
            temp=numeros[x];
            numeros[x]=numeros[posMenor];
            numeros[posMenor]=temp;
    }

    printf("\n lista ordenada \n");
    for(int x=0;x<14;x++)
    {
        printf("%i ",numeros[x]);
    }
}
