#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int dato;
    struct stNodoDoble * siguiente;
    struct stNodoDoble * anterior;

}stNodoDoble;

typedef struct
{
    struct stNodoDoble * primero;
    struct stNodoDoble * ultimo;
    int contador;

}stFila;

typedef struct
{
    struct stNodoDoble *

}stFila


         ------------------               PROTOTIPADO                ----------------------           **/
stNodoDoble * iniciarNodoDoble()
{
    return NULL;
}

stFila * iniciarFila( stFila * fila)
{
    fila->primero = iniciarNodoDoble();
    fila->ultimo = iniciarNodoDoble();
    fila->contador = 0;
    return fila;
}










int main()
{
    stFila * filaElementos = iniciarFila(&filaElementos);

    printf("%d",filaElementos->contador);

}






















