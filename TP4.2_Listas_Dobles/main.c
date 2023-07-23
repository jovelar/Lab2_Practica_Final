#include <stdio.h>
#include <stdlib.h>
#include "Lib/Lista_doble.h"
#include "Lib/Utilidades.h"

int main()
{
    int opc=0;
    while(opc!=27)
    {
        opc=menu();
        switch(opc)
        {
        case 49:;
            Nodo2 *listaGenerada=generarListaAleatoria(5,1,50);
            mostrarListaDoble(listaGenerada,4);
            system("pause");
            system("cls");
            break;

        default:
            printf("\ Opcion Invalida!");
            break;
        }
    }
    printf("Hello world!\n");
    return 0;
}

int menu()
{
    printf("1- Borrar un nodo en lista doble. \n");

    int opc=getch();
    return opc;
}
