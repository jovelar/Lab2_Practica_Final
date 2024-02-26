#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dato;
    char palabra[20];
}Celda;

void cambiarValorCelda(Celda celda[],int posicion,int dato,char palabra[]);

void sumar(int *n1,int *n2);
int main()
{
    int numero=10;
    int numero2=15;

    sumar(&numero,&numero2);

    Celda celdas[40];
    cambiarValorCelda(celdas,0,45,"mayonesa");
    printf("\n %i | %s ",celdas[0].dato,celdas[0].palabra);
    return 0;
}

void cambiarValorCelda(Celda celda[],int posicion,int dato,char palabra[])
{
    celda[posicion].dato=dato;
    strcpy(&celda[posicion].palabra,palabra);
}

void sumar(int *n1,int *n2)
{
    printf("\n %i ",*n1+*n2);
}
