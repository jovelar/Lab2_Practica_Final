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

        case 50:;//2- AGREGAR DATOS AL PRINCIPIO
            int numero2;
            printf("\n Ingrese un numero a cargar: ");
            scanf("%d",&numero2);
            nodo2 *nuevoNodo2=crearNuevoNodo(numero2);
            break;

        case 51:;//3- AGREGAR DATOS AL FINAL
            int numero3;
            printf("\n Ingrese un numero para cargar al final: ");
            scanf("%d",&numero3);
            nodo2 *nuevoNodo3=crearNuevoNodo(numero3);
            break;

        case 52:;//4- BORRAR BUSCANDO UN NODO
            int numero4;
            printf("\n Ingrese el numero a borrar: ");
            scanf("%d",&numero4);
            lista=borrarBuscando(lista,numero4);
            break;

        case 53:; //5- BORRAR DESDE EL PRINCIPIO
            lista=borrarAlPrincipio(lista);
            break;

        case 54: //6- BORRAR DESDE EL FINAL
            lista=borrarAlFinal(lista);
            break;

        case 55://7- MOSTRAR LA LISTA
            mostrarLista(lista);
            break;

        case 56://8- BUSCAR UN NUMERO
            break;

        case 57://9- BORRAR TODA LA LISTA
            borrarTodaLaLista(lista);
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

nodo2 *agregarAlPrincipio(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista->anterior=nuevo;
    }

    return lista;
}

nodo2 *agregarAlFinal(nodo2 *lista, nodo2*nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(lista->siguiente=NULL)
        {
            lista->siguiente=nuevo;
            nuevo->anterior=lista;
        }
        else
        {
            nodo2 *iterador=lista;
            nodo2 *anterior=iterador;
            while(iterador)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            anterior->siguiente=nuevo;
            nuevo->anterior=anterior;
        }
    }
    return lista;
}

nodo2 *borrarBuscando(nodo2 *lista, int dato)
{
    if(lista)
    {
        nodo2 *temp;
        if(lista->dato==dato)
        {
            temp=lista->siguiente;
            free(lista);
            lista=temp;
        }
        else
        {
            nodo2 *iterador=lista;
            nodo2 *anterior=iterador;
            while(iterador && dato != iterador->dato)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            if(iterador)
            {
                if(dato==iterador->dato)
                {
                    nodo2 *siguiente=iterador->siguiente;
                    anterior->siguiente=siguiente;
                    siguiente->anterior=anterior;
                    free(iterador);
                }
            }

        }
    }
    return lista;
}

nodo2 *borrarAlPrincipio(nodo2 *lista)
{
    if(lista)
    {
        if(lista->siguiente=NULL)
        {
            free(lista);
            lista=NULL;
        }
        else
        {
            nodo2 *temp=lista->siguiente;
            free(lista);
            lista=temp;
        }
    }
    return lista;
}

nodo2 *borrarAlFinal(nodo2 *lista)
{
    if(lista)
    {
        if(lista->siguiente=NULL)
        {
            nodo2 *temp=lista->siguiente;
            free(lista);
            lista=temp;
        }
        else
        {
            nodo2 *iterador=lista;
            nodo2 *anterior=iterador;
            while(iterador)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            anterior->siguiente=iterador->siguiente;
            free(iterador);
        }
    }
}

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
void *borrarTodaLaLista(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *sig;
        while(lista)
        {
            sig=lista->siguiente;
            free(lista);
            lista=sig;
        }
    }
}
