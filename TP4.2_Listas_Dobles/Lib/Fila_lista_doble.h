#ifndef FILA_LISTA_DOBLE_H_INCLUDED
#define FILA_LISTA_DOBLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Lista_doble.h"

typedef Nodo2 Fila; //se crea un tipo nuevo basado en otro existente

Fila *agregar(Fila *fila,Fila *nuevo);
Fila *extraer(Fila *fila,int dato);




Fila *mostrar(Fila *fila);
Fila *leer(Fila *fila);
Fila *primero(Fila *fila);
int filaVacia(Fila *fila);



#endif // FILA_LISTA_DOBLE_H_INCLUDED
