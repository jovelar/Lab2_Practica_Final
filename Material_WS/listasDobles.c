#include <stdio.h>
#include <stdlib.h>
#include "listasDobles.h"
#include <string.h>

nodoDoble *inicListaDoble(){
    return NULL;
}

nodoDoble *crearNodoDoble(persona nodoNuevo){
    nodoDoble *aux=(nodoDoble*)malloc(sizeof(nodoDoble));
    aux->dato=nodoNuevo;
    aux->anterior=NULL;
    aux->siguiente=NULL;
    return aux;
}

nodoDoble *agregarPpioDoble(nodoDoble *lista, nodoDoble *nuevoNodo){
    nuevoNodo->siguiente=lista;
    if(lista!=NULL){
    lista->anterior=nuevoNodo;
    }
    return nuevoNodo;
}



nodoDoble *agregarFinalDoble(nodoDoble *lista, nodoDoble *nuevoNodo){

    if(lista==NULL){
        lista=nuevoNodo;
    }else{
        nodoDoble *aux=(nodoDoble*)malloc(sizeof(nodoDoble));
        aux=buscarUltimoDobleRecursivo(lista);
        aux->siguiente=nuevoNodo;
        nuevoNodo->anterior=aux;
    }
    return lista;
}

nodoDoble *buscarUltimoDoble(nodoDoble *lista){
    nodoDoble *aux=(nodoDoble*)malloc(sizeof(nodoDoble));
    aux=lista;
    while(aux->siguiente!=NULL){
        aux=aux->siguiente;
    }
    return aux;
}

nodoDoble *buscarUltimoDobleRecursivo(nodoDoble *lista){
    nodoDoble *aux=(nodoDoble*)malloc(sizeof(nodoDoble));
    if(lista==NULL){
        aux=NULL;
    }else{
    if(lista->siguiente==NULL){
        aux=lista;
    }else{
        aux=buscarUltimoDobleRecursivo(lista->siguiente);
    }
    }
    return aux;
}

nodoDoble *agregarEnOrdenDoble(nodoDoble *lista, nodoDoble *nuevoNodo){
    if(lista==NULL){
        lista=nuevoNodo;
    }else{
        if(lista->dato.edad>nuevoNodo->dato.edad){
            agregarPpioDoble(lista,nuevoNodo);
        }else{
        nodoDoble *seg=(nodoDoble*)malloc(sizeof(nodoDoble));
        nodoDoble *ante=(nodoDoble*)malloc(sizeof(nodoDoble));
        while(seg->siguiente!=NULL&&nuevoNodo->dato.edad>seg->dato.edad){
            ante=seg;
            seg=seg->siguiente;
        }
        if(seg->siguiente==NULL){
            agregarFinalDoble(seg,nuevoNodo);
        }else{
            ante->siguiente=nuevoNodo;
            nuevoNodo->anterior=ante;
            nuevoNodo->siguiente=seg;
            seg->anterior=nuevoNodo;
        }
    }
    }
    return lista;
}

void mostrarListaDoble(nodoDoble *lista){
    nodoDoble *seg=lista;
    printf("4");
    while(seg!=NULL){
        printf("5");
        mostrarNodoDoble(seg->dato);
        seg=seg->siguiente;
    }
}

void mostrarNodoDoble(persona dato){
    printf("5");
    printf("Nombre: %s\n",dato.nombre);
    printf("Edad: %d\n",dato.edad);
    puts("*------------------------------------------------*");
}

nodoDoble *borrarPrimerNodoDoble(nodoDoble *lista){
    nodoDoble *aux;
    aux=lista;
    lista=lista->siguiente;
    free(aux);
    return lista;
}


