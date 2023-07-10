#ifndef LISTASDOBLES_H_INCLUDED
#define LISTASDOBLES_H_INCLUDED

typedef struct {
    char nombre[30];
    int edad;
}persona;

typedef struct{
    persona dato;
    struct nodoDoble *anterior;
    struct nodoDoble *siguiente;
}nodoDoble;

nodoDoble *inicListaDoble();
nodoDoble *crearNodoDoble(persona nodoNuevo);
nodoDoble *agregarPpioDoble(nodoDoble *lista, nodoDoble *nuevoNodo);
nodoDoble *agregarFinalDoble(nodoDoble *lista, nodoDoble *nuevoNodo);
nodoDoble *buscarUltimoDoble(nodoDoble *lista);
nodoDoble *buscarUltimoDobleRecursivo(nodoDoble *lista);
nodoDoble *agregarEnOrdenDoble(nodoDoble *lista, nodoDoble *nuevoNodo);
void mostrarListaDoble(nodoDoble *lista);
void mostrarNodoDoble(persona dato);
nodoDoble *borrarPrimerNodoDoble(nodoDoble *lista);

#endif // LISTASDOBLES_H_INCLUDED
