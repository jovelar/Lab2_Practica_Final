#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dato;
    struct nodo * siguiente;
}nodo;

int menu();
nodo *inicializar();
nodo *crearNuevoNodo(int dato);
nodo *agregarOrdenado(nodo *lista, nodo *nuevo);
nodo *agregarAlPrincipio(nodo *lista, nodo *nuevo);
nodo *agregarAlFinal(nodo *lista, nodo*nuevo);
nodo *borrarBuscando(nodo *lista, int dato);
nodo *borrarAlPrincipio(nodo *lista);
nodo *borrarAlFinal(nodo *lista);
void *mostrarLista(nodo *lista);
nodo *buscarNodo(nodo *lista, int numero);
void *borrarTodaLaLista(nodo *lista);




int main()
{
    int opcion=0;
    nodo *lista=inicializar();
    while(opcion!=57 && opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
            case 49: //AGREGAR ORDENADO
                system("cls");
                int dato;
                printf("Ingrese un numero :");
                scanf("%d",&dato);
                nodo *nuevo=crearNuevoNodo(dato);
                lista=agregarOrdenado(lista,nuevo);
                printf("Numero Agregado! \n");
                system("pause");
                break;

            case 50: // AGREGAR AL PRINCIPIO
                system("cls");
                int dato2;
                printf("Ingrese un numero :");
                scanf("%d",&dato2);
                nodo *nuevo2=crearNuevoNodo(dato2);
                lista=agregarAlPrincipio(lista,nuevo2);
                printf("Numero Agregado! \n");
                system("pause");
                break;

            case 51: // AGREGAR AL FINAL
                system("cls");
                int dato3;
                printf("Ingrese un numero :");
                scanf("%d",&dato3);
                nodo *nuevo3=crearNuevoNodo(dato3);
                lista=agregarAlFinal(lista,nuevo3);
                printf("Numero Agregado! \n");
                system("pause");
                break;

            case 52: // BORRAR BUSCANDO UN DATO
                system("cls");
                int dato4;
                printf("Ingrese un numero :");
                scanf("%d",&dato4);
                lista=borrarBuscando(lista,dato4);
                break;

            case 53: //BORRAR EL PRIMERO
                lista=borrarAlPrincipio(lista);
                break;

            case 54: //BORRAR EL ULTIMO
                lista=borrarAlFinal(lista);
                break;

            case 55: //MOSTRAR LA LISTA
                mostrarLista(lista);
                system("pause");
                break;

            case 56: //BUSCAR UN DATO
                break;

            case 57: //SALIR
                printf("\n SALIENDO! \n");
                break;

            default:
                printf("opcion invalida! \n");
            break;
        }
        system("cls");
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
    printf("9- SALIR: \n");
    opcion=getch();
    return opcion;
}

nodo *inicializar()
{
    return NULL;
}

nodo *crearNuevoNodo(int dato)
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;
    return nuevo;
}

nodo *agregarOrdenado(nodo *lista, nodo *nuevo)
{
    if (lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(lista->dato>nuevo->dato)  //SI ES EL PRIMER NODO
        {
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else //SI NO ES EL PRIMERO LO BUSCA
        {
            nodo *anterior;
            nodo *iterador=lista;
            while(iterador!=NULL && iterador->dato < nuevo->dato)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            if(iterador==NULL)//SI ES EL ULTIMO
            {
                anterior->siguiente=nuevo;
            }
            else
            {
                anterior->siguiente=nuevo;
                nuevo->siguiente=iterador;
            }

        }
    }
    return lista;
}

nodo *agregarAlPrincipio(nodo *lista, nodo *nuevo)
{
    if(lista)
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    else
    {
        lista=nuevo;
    }
    return lista;
}

nodo *agregarAlFinal(nodo *lista, nodo*nuevo)
{
    if(lista) //SI NO ESTA VACIA
    {
        if(lista->siguiente==NULL)//SI HAY UN SOLO NODO EN LA LISTA
        {
            lista->siguiente=nuevo;
        }
        else //SE DEBE RECORRER HASTA EL FINAL
        {
            nodo *iterador=lista;
            nodo *anterior=iterador;
            {
                while(iterador)
                {
                    anterior=iterador;
                    iterador=iterador->siguiente;
                }
            }
            anterior->siguiente=nuevo;
        }
    }
    else //SI LA LISTA ESTA VACIA
    {
        lista=nuevo;
    }
    return lista;
}
nodo *borrarBuscando(nodo *lista, int dato)
{
    if(lista!=NULL && lista->dato==dato) //SI LA LISTA NO ESTA VACIA Y ESTA EN EL PRIMERO
    {
        nodo *nodoABorrar=lista;
        lista=lista->siguiente;
        free(nodoABorrar);
    }
    else
    {
        nodo *iterador=lista;
        nodo *anterior=iterador;
        while(iterador!=NULL && iterador->dato!=dato)
        {
            anterior=iterador;
            iterador=iterador->siguiente;
        }
        if(iterador!=NULL) //SI NO LLEGO AL FINAL QUIERE DECIR QUE LO ENCONTRO
        {
            anterior->siguiente=iterador->siguiente;
            free(iterador);
        }

    }
    return lista;
}

nodo *borrarAlPrincipio(nodo *lista)
{
    if(lista)
    {
        if(lista->siguiente=NULL) //SI SOLO HAY UN NODO
        {
            free(lista);
            lista=NULL;
        }
        else
        {
            nodo *aEliminar=lista;
            lista=lista->siguiente;
            free(aEliminar);
        }
    }
    return lista;
}

nodo *borrarAlFinal(nodo *lista)
{
    if(lista)
    {
        if(lista->siguiente==NULL) //SI ES EL PRIMERO
        {
            free(lista);
            lista=NULL;
        }
        else
        {
            nodo *iterador=lista;
            nodo *anterior=iterador;
            while(iterador)
            {
                anterior=iterador;
                iterador=iterador->siguiente;
            }
            anterior->siguiente=NULL;
            free(iterador);
        }
    }
    return lista;
}
void *mostrarLista(nodo *lista)
{
    if(lista)
    {
        nodo *iterador=lista;
        int contador=1;
        while(iterador)
        {
            printf("Nodo %i: Valor %i \n",contador,iterador->dato);
            contador++;
            iterador=iterador->siguiente;
        }
    }
    else
    {
        printf("La lista esta vacia!");
    }
}

nodo *buscarNodo(nodo *lista, int numero)
{
    nodo *resultado=NULL;
    {
        if(lista)
        {
            if(lista->dato==numero) //SI ESTA EN LA PRIMERA POSICION
            {
                resultado=lista;
            }
            else
            {
                nodo *iterador=lista;
                while(iterador!=NULL &&  resultado==NULL)
                {
                    if(iterador->dato==numero)
                    {
                        resultado=iterador;
                    }
                    iterador=iterador->siguiente;
                }
            }
        }
    }
    return resultado;
}
void *borrarTodaLaLista(nodo *lista)
{
    if(lista)
    {
        if(lista->siguiente==NULL)
        {
            free(lista);
        }
        else
        {
            nodo *anterior=lista;
            lista=lista->siguiente;
            while(lista)
            {
                anterior=lista;
                lista=lista->siguiente;
                free(anterior);
            }
        }
    }
    else
    {
        printf("La lista ya esta vacia! \n");
    }
}
