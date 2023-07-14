#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib/utilidades.h"
#include "Lib/ADL.h"
#include <windows.h>



int main()
{
    char archivoRegistros[40]="RegistroAlumnos.bin";
    char archivoRegistrosAprobados[40]="RegistroAprobados.bin";
    celda materiasADL[10];
    int materiasValidas=0;

    int opc=0;

    while(opc!=54)
    {
        opc=menu();
        switch(opc)
        {
            case 49:
                materiasValidas=pasarDeArchivoToADL(materiasADL,materiasValidas,archivoRegistros);
                printf("Se cargo el archivo al Arreglo De Listas! \n");
                system("pause");
                system("cls");
            break;

            case 50:
                mostrarListaCompleta(materiasADL,materiasValidas);
                system("pause");
                system("cls");
            break;

            case 51:
                pasarDeADLToArchivoDeAprobados(materiasADL,materiasValidas,archivoRegistrosAprobados);
                printf("Se genero el archivo %s \n",archivoRegistrosAprobados);
                system("pause");
                system("cls");
            break;

            case 52:
                mostrarRegistroAprobados(archivoRegistrosAprobados);
                system("pause");
                system("cls");
            break;

            case 53:
                generarArchivoRegistros(archivoRegistros);
                printf("Se regenero el archivo %s \n",archivoRegistros);
                purgarArchivo(archivoRegistrosAprobados);
                system("pause");
                system("cls");
            break;

            case 54:
            break;

            default:
                printf("Opcion invalida!, Solo numeros del 1 al 6");
                Sleep(3000);
                system("cls");
            break;

        }
    }
    return 0;
}

int menu()
{
    int opc;
    printf("1-Pasar registro alumnos a Arreglo De Listas \n");
    printf("2-Mostrar Arreglo de Listas \n");
    printf("3-Pasar alumnos aprobados de Arreglo De Listas a archivo \n");
    printf("4-Mostrar archivo de registro de aprobados \n");
    printf("5-Regenerar archivo de registros y eliminar archivo de aprobados \n");
    printf("6-Salir \n");
    opc=getch();

    return opc;
}

