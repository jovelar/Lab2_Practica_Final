#include <stdio.h>
#include <stdlib.h>
#include "lib/Fila.h"

int menu()
{
    int opc;

    printf("\n1- Agregar a la fila (encolar) \n");
    printf("2- Retirar el primero (desencolar) \n");
    printf("3- Mostrar el primero \n");
    printf("4- Mostrar la fila \n");
    printf("\n5- SALIR");
    opc=getch();
    return opc;
}

int main()
{
    Fila fila;
    inicFila(&fila);
    int opciones;
    do
    {
        opciones=menu();
        switch(opciones)
        {
        case 49:;
            int nuevoValor;
            char nuevaPalabra[50];
            printf("\nIngrese el numero: ");
            scanf("%d",&nuevoValor);
            printf("\nIngrese la palabra: ");
            fflush(stdin);
            gets(nuevaPalabra);
            nodo2 *nuevoNodo=crearNodo2(nuevaPalabra,nuevoValor);
            encolar(&fila,nuevoNodo);
            printf("\nAgregado!\n");

            break;

        case 50:
            if(fila.primero)
            {
                nodo2 *desencolado=desencolar(&fila);
                printf("\n Se retiro el nodo %i %s \n",desencolado->numero,desencolado->palabra);
                free(desencolado);
            }
            else
            {
                printf("\n La fila esta vacia!\n");
            }
            break;

        case 51:
            if(fila.primero)
            {
                mostrarPrimero(&fila);
            }
            else
            {
                printf("\nFila vacia!");
            }
            break;

        case 52:
            mostrarFila(&fila);
            break;

            case 53:
                printf("\nSALIENDO!\n");
            break;

            default:
                printf("\nOPCION INVALIDA! SOLO numeros del 1 al 5! \n");
            break;
        }

    }while(opciones!=53);
    return 0;
}
