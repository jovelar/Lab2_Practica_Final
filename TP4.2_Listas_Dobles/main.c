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
            printf("\n");
            mostrarListaDoble(listaGenerada,10);
            printf("Ingrese el dato a eliminar: ");
            int datoAEliminar;
            scanf("%i",&datoAEliminar);

            listaGenerada=borrarNodoDoble(listaGenerada,datoAEliminar);
            printf("\nLista Nueva\n");
            mostrarListaDoble(listaGenerada,10);

            system("pause");
            system("cls");
            break;

        case 50:;
            Nodo2 *n1=crearNodo(1);
            Nodo2 *n2=crearNodo(2);
            Nodo2 *n3=crearNodo(3);
            Nodo2 *n4=crearNodo(2);
            Nodo2 *n5=crearNodo(1);

            Nodo2 *listaN1=NULL;
            listaN1=agregarAlPio(listaN1,n1);
            listaN1=agregarAlPio(listaN1,n2);
            listaN1=agregarAlPio(listaN1,n3);
            listaN1=agregarAlPio(listaN1,n4);
            listaN1=agregarAlPio(listaN1,n5);



            printf("\nlista 1\n");
            mostrarListaDoble(listaN1,10);
            Nodo2 *ultimo=buscarUltimo(listaN1);
            int pala1=capicaRecursivoDoble(listaN1,ultimo,1);


            printf("\nCapicua?: %d \n",pala1);

            Nodo2 *listaRandom=generarListaAleatoria(5,1,10);

            Nodo2 *ultimo2=buscarUltimo(listaRandom);

            printf("\nlista 2\n");
            mostrarListaDoble(listaRandom,10);

            int pala2=capicaRecursivoDoble(listaRandom,ultimo2,1);

            printf("\nCapicua 2?: %i \n",pala2);

            system("pause");
            break;
        case 27:
            break;
        default:
            printf("\ Opcion Invalida!");
            break;
        }
    }
    return 0;
}

int menu()
{
    printf("1- Borrar un nodo en lista doble. \n");
    printf("2- Capicua Recursivo \n");
    printf("\nESC para salir");

    int opc=getch();
    return opc;
}
