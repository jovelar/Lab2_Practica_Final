#include <stdio.h>
#include <stdlib.h>

void sumar(int *n1,int *n2);
int main()
{
    int numero=10;
    int numero2=15;

    sumar(&numero,&numero2);

    return 0;
}

void sumar(int *n1,int *n2)
{
    printf("\n %i ",*n1+*n2);
}
