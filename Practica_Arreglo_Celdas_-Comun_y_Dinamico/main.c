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

}CeldaDinamica;

//void agregarACD(CeldaDinamica *celda,int dato, char palabra[20],int *validos, int *tMax);
void agregarACD(CeldaDinamica **celda, int dato, char palabra[20], int *validos, int *tMax);
CeldaDinamica mostrarCD(CeldaDinamica *celda, int validos);

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
    int validos=0;
    int tMax=4;
    CeldaDinamica *celdaDin;
    celdaDin=(CeldaDinamica*)malloc(sizeof(CeldaDinamica)*4);

    int opcion=0;
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
            case 27:
                printf("\nSaliendo!");
            break;

            case 49:;
                int dato;
                char palabra[20];
                printf("\n Ingrese un entero: ");
                scanf("%d",&dato);
                printf("\n");
                printf("\n Ingrese una palabra de 20 letra: ");
                fflush(stdin);
                gets(palabra);
                agregarACD(celdaDin,dato,palabra,&validos,&tMax);

                break;

            case 50:
                break;

            default:
                printf("\nOpcion invalida!");
                break;
        }
    }
    free(celdaDin);
    return 0;
}

void agregarACD(CeldaDinamica **celda,int dato, char palabra[20],int *validos, int *tMax)
{
    if(*validos == *tMax+1)
    {
        celda=(CeldaDinamica*)realloc(celda,sizeof(CeldaDinamica)*(*tMax+10));
    }
    *tMax=*tMax+10;
    validos++;
    celda[validos].dato=dato;
    strcpy((*celda[*validos]).palabra,palabra);
    system("pause");
}


CeldaDinamica mostrarCD(CeldaDinamica *celda, int validos)
{
    for(int x=0;x<validos;x++)
    {
        printf("\n %i | %s ",celda[x].dato,celda[x].palabra);
    }
}
