#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX 49

typedef struct
{
  int arreglo[50];
  int tope; ///representa la ultima posicion cargada del arreglo
}Pila;


///acciones
void apilar(Pila*,int dato);
int desapilar(Pila*);
int tope(Pila);
void inicPila(Pila*);
int pilavacia(Pila);
void mostrar(Pila);



#endif // PILA_H_INCLUDED
