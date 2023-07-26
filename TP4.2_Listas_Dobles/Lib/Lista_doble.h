#ifndef LISTA_DOBLE_H_INCLUDED
#define LISTA_DOBLE_H_INCLUDED

typedef struct
{
    int dato;
    struct Nodo2 *siguiente;
    struct Nodo2 *anterior;
}Nodo2;

Nodo2 *inicLista();
Nodo2 *crearNodo(int dato);
Nodo2 *agregarAlPio(Nodo2 *lista, Nodo2 *nuevoNodo);
Nodo2 *agregarAlFinal(Nodo2 *lista, Nodo2 *nuevoNodo);
Nodo2 *buscarUltimo(Nodo2 *lista);
Nodo2 *insertarNodo(Nodo2 *lista, Nodo2 *nuevoNodo);
Nodo2 *borrarNodoDoble(Nodo2 *lista, int dato);

int capicaRecursivoDoble(Nodo2 *seg, Nodo2 *rev,int resultado);
Nodo2 *eliminarNodoDelMedio(Nodo2 *lista);
 ////////PARA FILAS////////
 Nodo2 *borrarPrimero(Nodo2 *lista)
 {
     Nodo2 *aBorrar=lista;
     if(lista!=NULL)
     {
         lista=lista->siguiente;
         if(lista!=NULL)
         {
             lista->anterior=NULL;
         }
         free(aBorrar);
     }
     return lista;
 }
 //////////////////////////
#endif // LISTA_DOBLE_H_INCLUDED
