#include <stdio.h>
#include <stdlib.h>
#include "Lib/lista_simple.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    char nombreArchivo[40]="Registros.bin";

    int opc=0;
    while(opc!=27)
    {
        fflush(stdin);
        opc=menu();
        switch(opc)
        {
            case 49:; //; PARA EMPTY STATEMENT, NO SE PUEDE DECLARAR VARIABLES DESPUES DE UN LABEL

                nodo *listaACargar=inicializar();
                listaACargar=pasarArchivoALista(nombreArchivo);
                mostrarLista(listaACargar);
                printf("\n datos cargados tal cual estaban en el archivo \n");
                system("pause");
                free(listaACargar);

            break;

            case 50:;

                nodo *listaACargar2=inicializar();
                listaACargar2=pasarArchivoAListaOrdenado(nombreArchivo);
                mostrarLista(listaACargar2);
                printf("\n datos cargados de forma ordenada de menor a mayor \n");
                system("pause");
                free(listaACargar2);

            break;

            case 51:
                system("cls");
                printf("1- lista desordenada \n");\
                printf("2- Lista ordenada");
                do
                {
                    int opc=getch();
                    if(opc>49 && opc<50)
                    {
                        printf("Opcion invalida, solo  [1] o [2]");
                    }
                }while(opc!=49 && opc!=50);

                    if(opc==49)
                    {
                        printf("");
                    }
                    else
                    {

                    }

            break;

            case 27:
            break;

            default:
                printf("Opcion Invalida!, solo numeros del 1 al 4 y ESC \n");
            break;

        }
    }

}

int menu()
{
    int opc=0;
    printf("1- Pasar registros archivo a lista enlazada \n");
    printf("2- Pasar registros archivo a lista enlazada de forma ordenada \n");
    printf("3-Mostrar lista \n");
    printf("ESC- para salir \n");
    fflush(stdin);
    opc=getch();
    return opc;
}

nodo *menuIngresar()
{
}
