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

typedef struct
{
    int numero;
    struct nodo2 *siguiente;
}nodoP;

void pruebaStrcpy();

int main()
{
    //prueba_nodo_en_nodo_puntero();
    //prueba_ordenamiento_por_seleccion();
    //prueba_compara_punteros();
    pruebaStrcpy();
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

void prueba_compara_punteros()
{
    nodoP *base=(nodoP*)malloc(sizeof(nodoP));
    nodoP *base2=(nodoP*)malloc(sizeof(nodoP));
    nodoP *puntero1=base;
    nodoP *puntero2=base;

    if(puntero1==puntero2)
    {
        printf("\n Son el mismo nodo! \n");
    }
    else
    {
        printf("\n No son el mismo nodo \n");
    }

    printf("Puntero 1: %x | Puntero 2: %x",*puntero1,*puntero2);
}

void pruebaStrcpy()
{
    nota pruebaNota;
    char palabra[30]="Domingos";
    strcpy(pruebaNota.nombre,palabra);
    printf("\n%s",pruebaNota.nombre);
}
