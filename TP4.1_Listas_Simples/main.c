#include <stdio.h>
#include <stdlib.h>
#include "Lib/lista_simple.h"

int main()
{
    nodo *lista;
    int opc=0;
    while(opc!=27)
    {
        switch(opc)
        {
            case 49:
            break;

            case 50:
            break;

            case 51:
            break;

            case 27:
            break;

            default:
                printf("Opcion Invalida!, solo numeros del 1 al 4 y ESC \n");
            break;

        }
    }
    free(lista);
}

int menu()
{
    int opc=0;
    printf("1- Pasar registros archivo a lista enlazada \n");
    printf("2-Borrar nodo \n");
    printf("3-Mostrar lista \n");
    printf("ESC- para salir \n");
    return opc;
}

nodo *menuIngresar()
{
}
