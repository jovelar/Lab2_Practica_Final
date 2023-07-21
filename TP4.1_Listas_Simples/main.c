#include <stdio.h>
#include <stdlib.h>
#include "Lib/lista_simple.h"
#include <time.h>
#include "Lib/pila_con_lista_simple.h"


int menuPilas();

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
                system("cls");

            break;

            case 50:; //[2]

                nodo *listaACargar2=inicializar();
                listaACargar2=pasarArchivoAListaOrdenado(nombreArchivo);
                mostrarLista(listaACargar2);
                printf("\n datos cargados de forma ordenada de menor a mayor \n");
                system("pause");
                free(listaACargar2);
                system("cls");

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
                nodo *lista=generarListaAleatoria(3,0,30);
                nodo *lista2=generarListaAleatoria(3,10,30);
                nodo *listaResult=NULL;
                printf("\n Lista 1: \n"),
                mostrarListaNumerada(lista,6);
                printf("\n Lista 2: \n");
                mostrarListaNumerada(lista2,6);

                printf("\n Lista Resultante \n");
                listaResult=intercalarListas(lista,lista2);
                mostrarListaNumerada(listaResult,6);
                free(lista);
                free(lista2);
                free(listaResult);
                system("pause");
                system("cls");
                break;

            case 53:;
                nodo *lista1=generarListaAleatoria(4,1,20);
                mostrarListaNumerada(lista1,6);
                nodo *lista22=invertirLista(lista1);
                mostrarListaNumerada(lista22,6);
                system("pause");
                free(lista1);
                free(lista2);
                break;

            case 54:;
                Pila *pila=init();
                int opcX=10;
                while(opcX!=27)
                {
                    opcX=menuPilas();
                    switch(opcX)
                    {
                    case 49:;
                        int numero=60;
                        while(numero!=00)
                        {
                            printf("\nIngrese un numero entero a cargar en la pila, 00 para salir: ");
                            scanf("%i",&numero);
                            if(numero!=00)
                            {
                                if(numero%2==0)
                                {
                                    pila=apilar(pila,numero);
                                }
                                else
                                {
                                    printf("\nEl numero no es par!\n");
                                }
                            }

                        }
                        break;
                    case 50:
                        mostrarPila(pila);
                        system("pause");
                        break;
                    case 51:
                        printf("\n pila original \n");
                        mostrarPila(pila);
                        pila=borrarMenoresAX(pila,10);
                        mostrarPila(pila);
                        system("pause");
                        borrarPila(pila);
                        break;
                    default:
                        printf(" \n Opcion invalida! \n");
                        break;
                    }
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
    printf("3- Mostrar lista \n");
    printf("4- Intercalar de forma ordenada 2 listas \n");
    printf("5- Invertir Lista reordenando punteros \n");
    printf("6- Pilas \n");
    printf("ESC- para salir \n");
    fflush(stdin);
    opc=getch();
    return opc;
}

nodo *menuIngresar()
{

}

int menuPilas()
{
    int opc;
    printf("\n1- Ingresar valores \n");
    printf("2- Mostrar toda la pila \n");
    printf("3- Borrar elementos menores a 10");
    printf("\nESC para salir: ");
    opc=getch();
    return opc;
}
