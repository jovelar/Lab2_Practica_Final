//DEFINICIONES DE FILA Y LISTA DOBLE EN EL MISMO ARCHIVO

#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct
{
    struct nodo2 *primero;
    struct nodo2 *ultimo;

}Fila;

typedef struct
{
    char palabra[50];
    int numero;
    struct nodo2 *ante;
    struct nodo2 *sig;
}nodo2;

void inicFila(Fila *fila);
void encolar(Fila *fila, nodo2 *nuevo);
nodo2 *desencolar(Fila *fila);
void mostrarFila(Fila *fila);
void mostrarPrimero(Fila *fila);

nodo2 *crearNodo2(char palabra[30],int numero);
nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo);
nodo2 *borrarPrimero(nodo2 *lista);
void mostrar(nodo2 *nodo);
void mostrarFila(Fila *fila);

#endif // FILA_H_INCLUDED
