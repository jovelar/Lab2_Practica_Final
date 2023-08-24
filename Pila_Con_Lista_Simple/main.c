#include <stdio.h>
#include <stdlib.h>
#include "Lib/PilaListaSimple.h"

int menu();
int main()
{
    int opcion=0;
    Pila *pila=inicPila();
    while(opcion!=27)
    {
        opcion=menu();

        switch(opcion)
        {
            case 27:
                break;

            case 49:
                pila=leer(pila);
                printf("\nDato cargado!\n");
                break;

            case 50:
                mostrarPila(pila);
                break;

            case 51:;
                int dato=desapilar(&pila);
                printf("\nSe removio el dato %i \n",dato);
                break;

            default:
                printf("\nOpcion invalida!\n");
                break;
        }
    }
    return 0;
}

int menu()
{
    int opcion=0;
    printf("\n1-Cargar datos a la pila");
    printf("\n2-Mostrar toda la pila \n");
    printf("\n3-Desapilar pila de la pila \n");
    printf("\n \n");
    printf("\n\nESC- SALIR: ");
    opcion=getch();
}
