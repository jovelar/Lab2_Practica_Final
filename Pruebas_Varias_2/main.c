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
    /*
    int numero=10;
    int numero2=15;

    sumar(&numero,&numero2);

    Celda celdas[40];
    cambiarValorCelda(celdas,0,45,"mayonesa");
    printf("\n %i | %s ",celdas[0].dato,celdas[0].palabra);
    */

    char p1[40]="Abecedario Universal";
    char p2[40]="Jungla de cristal";
    char p3[40]="Balas de Uranio";
    char p4[40]="Usando las zapatillas";

    printf("\nP1 y P3 = %i",strcmp(p1,p3));
    printf("\nP1 y P2 = %i",strcmp(p1,p2));
    printf("\nP2 y P3 = %i",strcmp(p2,p3));
    printf("\nP1 y P4 = %i",strcmp(p1,p4));
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
