#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dato;
    char palabra[20];
}CeldaComun;

typedef struct
{
    int dato;
    char palabra[20];
    int validos;
    int tMaximo;
}CeldaDinamica;

void agregarACD(CeldaDinamica *celda,int dato, char palabra[20]);
CeldaDinamica mostrarCD(CeldaDinamica *celda);

int menu()
{
    int opcion;
    printf("\n 1- Agregar al arreglo dinamico ");
    printf("\n 2- Mostrar arreglo dinamico ");
    printf("\n ESC - SALIR ");
    opcion=getch();
    return opcion;
}


int main()
{
    int opcion=0;
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
            case 27:
                prinf("\nSaliendo!");
            break;

            case 49:;
                int dato;
                char palabra[20];
                printf("\n Ingrese un entero: ");
                scanf("%d",&dato);
                printf("\n")
                break;

        }
    }
    return 0;
}

void agregarACD(CeldaDinamica *celda,int dato, char palabra[20])
{
    if(celda->tMaximo<celda->tMaximo+1) //SI ESTA LLEGANDO AL MAXIMO LO REDIMENSIONA UN 30% MAS
    {
        celda=(CeldaDinamica*)realloc(celda,sizeof(CeldaDinamica)*(celda->tMaximo*1.3));
    }
    celda->validos=celda->validos+1;

    celda[celda->validos].dato=dato;
    strcpy(celda[celda->validos].palabra,palabra);
}

CeldaDinamica mostrarCD(CeldaDinamica *celda)
{
    for(int x=0;x<=celda->tMaximo;x++)
    {
        printf("\n %i | %s",celda[x].dato,celda[x].palabra);
    }
}
