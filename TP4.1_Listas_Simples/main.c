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
                      //[1]
                nodo *listaACargar=inicializar();
                listaACargar=pasarArchivoALista(nombreArchivo);
                mostrarLista(listaACargar);
                printf("\n datos cargados tal cual estaban en el archivo \n");
                system("pause");
                free(listaACargar);

            break;

            case 50:; //[2]

                nodo *listaACargar2=inicializar();
                listaACargar2=pasarArchivoAListaOrdenado(nombreArchivo);
                mostrarLista(listaACargar2);
                printf("\n datos cargados de forma ordenada de menor a mayor \n");
                system("pause");
                free(listaACargar2);

            break;

            case 51: //[3]
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

            case 52:; //[4]
                nodo *lista=generarListaAleatoria(4,0,30);
                printf("\n Lista Inicial \n");
                mostrarListaNumerada(lista,4);
                nodo *menor=buscarMenor(lista);
                printf(" \n El menor es :%i \n",menor->dato);
                lista=ordenarReasignando(lista);
                printf("\n lista ordenada reorganizando punteros \n");
                mostrarListaNumerada(lista,4);
                break;

            case 53:
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
    printf("4-Ordenar fila reasignando punteros \n");
    printf("5-Opcion 5 \n");
    printf("ESC- para salir \n");
    fflush(stdin);
    opc=getch();
    return opc;
}

nodo *menuIngresar()
{
}
