#ifndef PILAFILASIMPLE_H_INCLUDED
#define PILAFILASIMPLE_H_INCLUDED
#endif // PILAFILA_H_INCLUDED

typedef struct
{
    int dato;
    struct Pila *siguiente;
}Pila;

Pila *inicPila();
Pila *apilar(Pila *pila, int dato);
int tope(Pila *pila);
int pilaVacia(Pila *pila);
Pila * leer(Pila *pila);
int desapilar(Pila **pila);
void mostrarPila(Pila *pila);
