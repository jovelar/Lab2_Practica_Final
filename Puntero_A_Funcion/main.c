#include <stdio.h>
#include <stdlib.h>

int suma(int a,int b);

int main()
{
    int (*punteroAFuncion)(int,int)=&suma;

    printf("\nla suma es de %i ",punteroAFuncion(4,5));
    return 0;
}

int suma(int a,int b)
{
    return a+b;
}
