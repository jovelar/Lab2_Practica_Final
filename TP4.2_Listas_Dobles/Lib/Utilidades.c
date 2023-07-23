#include "Utilidades.h"

int numeroRND(int limiteMinimo, int limiteMaximo)
{
    return limiteMinimo+ rand()%limiteMaximo;
}

Nodo2 *generarListaAleatoria(int cantidadNodos,int numeroBase,int numeroTope)
{
    Nodo2 *resultante=inicLista();
    int contadorNodos=0;
    while(contadorNodos!=cantidadNodos)
    {
        int dato=numeroRND(numeroBase,numeroTope);
        Nodo2 *nuevo=crearNodo(dato);
        resultante=agregarAlFinal(resultante,nuevo);
        contadorNodos++;
    }
    return resultante;
}

void mostrarListaDoble(Nodo2 *lista, int nodosPorLinea)
{
    Nodo2 *aux=lista;
    int nodos=0;
    while(aux->siguiente!=NULL)
    {
        if(nodos==nodosPorLinea)
        {
            printf("\n");
            nodos=0;
        }
        mostrarNodoDoble(aux);
        aux=aux->siguiente;
        nodos++;
    }

}
void mostrarNodoDoble(Nodo2 *nodoDoble)
{
    printf("%i |");
}
