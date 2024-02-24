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

void agregarACD(CeldaDinamica **celda,int dato, char palabraAGuardar[20],int *validos, int *tMax);
void mostrarCD(CeldaDinamica *celda, int validos);



int menu()
{
    int opcion;
    printf("\n 1- Agregar al arreglo dinamico ");
    printf("\n 2- Mostrar arreglo dinamico ");
    printf("\n3 -Agregar al arreglo comun ");
    printf("\n4- Mostrar arreglo comun");
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
                agregarACD(&celdaDin,dato,palabra,&validos,&tMax);

                break;

            case 50:
                mostrarCD(celdaDin,validos);
                break;

            case 51:
                break;

            case 52:
                break;

            default:
                printf("\nOpcion invalida!");
                break;
        }
    }
    free(celdaDin);
    return 0;
}

void agregarACD(CeldaDinamica **celda,int dato, char palabraAGuardar[20],int *validos, int *tMax) //SE PASAN LOS PUNTEROS PARA ACTUALIZAR LOS INT SIN DEVOLVERLOS
{
    if(*validos == *tMax+1)
    {
        *celda=(CeldaDinamica*)realloc(*celda,sizeof(CeldaDinamica)*(*tMax+10));
        *tMax=*tMax+10;  //DADO QUE ES UN PUNTERO/DIR DE MEMORIA, PARA ALTERAR EL VALOR SE DEBE ANTEPONER *
    }
    (*celda)[*validos].dato=dato;   //SE DESREFERENCIA PRIMERO DADO QUE ES UN PUNTERO DOBLE (*CELDA)
    strcpy((*celda)[*validos].palabra,palabraAGuardar);
    *validos=*validos+1; //CORRE LA POSICION 1 HACIA ADELANTE PARA INSERTAR DIRECTAMENTE
}


void mostrarCD(CeldaDinamica *celda, int validos)
{
    for(int x=0;x<=validos-1;x++) //-1 DADO QUE SIEMPRE LA ULTIMA POSICION DESPUES DE INSERTAR SE CORRE 1 HACIA ADELANTE
    {                             //PERO ESTA VACIA
        printf("\n %i | %s ",celda[x].dato,celda[x].palabra);
    }
}
