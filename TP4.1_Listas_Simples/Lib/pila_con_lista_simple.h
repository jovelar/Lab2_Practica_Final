#ifndef PILA_CON_LISTA_SIMPLE_H_INCLUDED
#define PILA_CON_LISTA_SIMPLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int valor;
    struct Pila *anterior;
}Pila;

int pilaVacia(Pila *Pila);
Pila *init();
Pila *apilar(Pila *pila, int datoNuevo);
Pila *desapilar(Pila *pila);
int tope(Pila *pila);
void mostrarPila(Pila *pila);
void borrarPila(Pila *pila);
Pila *borrarMenoresAX(Pila *pila, int numeroLimite);


#endif // PILA_CON_LISTA_SIMPLE_H_INCLUDED
