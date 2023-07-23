#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Lista_doble.h"

int numeroRND(int limiteMinimo, int limiteMaximo);
Nodo2 *generarListaAleatoria(int cantidadNodos,int numeroBase,int numeroTope);
void mostrarListaDoble(Nodo2 *lista, int nodosPorLinea);
void mostrarNodoDoble(Nodo2 *nodoDoble);

#endif // UTILIDADES_H_INCLUDED
