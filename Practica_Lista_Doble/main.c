#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dato;
    struct nodo2 *siguiente;
    struct nodo2 *anterior;
}nodo2;

int menu();
nodo2 *inicializar();
nodo2 *crearNuevoNodo(int dato);
nodo2 *agregarOrdenado(nodo2 *lista, nodo2 *nuevo);
nodo2 *agregarAlPrincipio(nodo2 *lista, nodo2 *nuevo);
nodo2 *agregarAlFinal(nodo2 *lista, nodo2*nuevo);
nodo2 *borrarBuscando(nodo2 *lista, int dato);
nodo2 *borrarAlPrincipio(nodo2 *lista);
nodo2 *borrarAlFinal(nodo2 *lista);
void *mostrarLista(nodo2 *lista);
nodo2 *buscarNodo(nodo2 *lista, int numero);
void *borrarTodaLaLista(nodo2 *lista);


int main()
{
    int opc;
    nodo2 *lista=inicializar();
    while(opc!=27)
    {
        opc=menu();
        switch(opc)
        {
        case 49:;//1- Agregar ordenado
            int numero;
            printf("Ingrese un numero para cargar: ");
            scanf("%d",&numero);
            nodo2 *nuevoNodo=crearNuevoNodo(numero);
            lista=agregarOrdenado(lista,nuevoNodo);
            break;

        case 50://2
            break;
        case 51://3
            break;
        case 52://4
            break;
        case 55://7
            mostrarLista(lista);
            break;
        case 56://8
            break;
        case 57://9
            break;
        case 120://X SALIR
            break;
        default:
            printf("\n \t Opcion Invalida! \n");
            break;

        }

    }
    return 0;
}

int menu()
{
    int opcion;
    printf("1- Agregar ordenado a la lista \n");
    printf("2- Agregar datos al principio de la lista \n");
    printf("3- Agregar datos al final de la lista \n");
    printf("4- Borrar buscando un dato \n");
    printf("5- Borrar desde el principio \n");
    printf("6- Borrar desde el final \n");
    printf("7- Mostrar la lista \n");
    printf("8- Buscar un numero \n");
    printf("9- Borrar toda la lista \n");
    printf("x- Salir \n");
    opcion=getch();
    return opcion;
}

nodo2 *inicializar()
{
    return NULL;
}

nodo2 *crearNuevoNodo(int dato)
{
    nodo2 *nuevoNodo=(nodo2*)malloc(sizeof(nodo2));
    nuevoNodo->dato=dato;
    nuevoNodo->anterior=NULL;
    nuevoNodo->siguiente=NULL;

    return nuevoNodo;
}

nodo2 *agregarOrdenado(nodo2 *lista, nodo2 *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(lista->dato>nuevo->dato) //SI ESTA EN LA PRIMER POSICION.
        {
            nuevo->siguiente=lista;
            lista->anterior=nuevo;
            lista=nuevo;
        }
        else
        {
            nodo2 *iterador=lista;
            nodo2 *anterior=iterador;
            while(iterador!=NULL && nuevo->dato > iterador->dato)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            if(iterador==NULL)
            {
                anterior->siguiente=nuevo;
                nuevo->anterior=anterior;
            }
            else
            {
                anterior->siguiente=nuevo;
                nuevo->anterior=anterior;

                nuevo->siguiente=iterador;
                iterador->anterior=nuevo;
            }
        }
    }

    return lista;
}

nodo2 *agregarAlPrincipio(nodo2 *lista, nodo2 *nuevo);
nodo2 *agregarAlFinal(nodo2 *lista, nodo2*nuevo);
nodo2 *borrarBuscando(nodo2 *lista, int dato);
nodo2 *borrarAlPrincipio(nodo2 *lista);
nodo2 *borrarAlFinal(nodo2 *lista);
void *mostrarLista(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        int contador=0;
        while(iterador)
        {
            printf("Posicion: %i | Valor: %i \n",contador,iterador->dato);
            iterador=iterador->siguiente;
            contador++;
        }
    }
}
nodo2 *buscarNodo(nodo2 *lista, int numero);
void *borrarTodaLaLista(nodo2 *lista);
