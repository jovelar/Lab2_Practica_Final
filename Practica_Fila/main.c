#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dato;
    char palabra[30];
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;

typedef struct
{
    nodo2 *primero;
    nodo2 *ultimo;
}Fila;

nodo2 *iniciLista();
nodo2 *crearNodo2(int dato);
nodo2 *borrarPrimero(nodo2 *lista);
nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo);
nodo2 *buscarNodo(nodo2 *lista, int dato);

void inicFila(Fila *fila);
void mostrarLista(nodo2 *lista);
void mostrarListaRec(nodo2 *lista);
void encolar(Fila *fila, nodo2 *nuevo);
void desencolar(Fila *fila); //NO DEVUELVE NADA, SOLO ELIMINA

nodo2 *desencolar2(Fila *fila); //DEVUELVE EL NODO2 QUE SE RETIRA

void mostrarFila(Fila *fila);

int menu();

int main()
{
    Fila fila;
    inicFila(&fila);

    int opcion=0;
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
        case 27: //ESC
            printf("\Saliendo!");
            break;

        case 49:// 1- AGREGAR UN NODO A LA FILA
            printf("\n Ingrese un dato a cargar: ");
            int valor;
            scanf("%d",&valor);
            nodo2 *nuevo=crearNodo2(valor);
            encolar(&fila,nuevo);

            printf("\n Agregado!");
            break;

        case 50:;//2- REMOVER UN ELEMENTO DE LA FILA
            //desencolar(&fila); //DESENCOLA SIN DEVOLVER EL NODO RETIRADO
            nodo2 *desencolado=desencolar2(&fila);
            if(desencolado)
            {
                printf("\n Se elimino el nodo %i \n",desencolado->dato);
            }
            free(desencolado);
            break;

        case 51:// 3- MOSTRAR LA FILA
            //mostrarFila(&fila);
            mostrarListaRec(fila.primero);
            break;

        default:
            printf("\n Opcion invalida! ");
            break;
        }
    }
    return 0;
}

nodo2 *iniciLista()
{
    return NULL;
}
nodo2 *crearNodo2(int dato)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;
    nuevo->dato=dato;

    return nuevo;
}

nodo2 *borrarPrimero(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *seg=lista->siguiente;
        free(lista);
        lista=seg;
    }
    return lista;
}

/*
nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        lista->siguiente=nuevo;
        nuevo->anterior=lista;
    }
    return nuevo;
}
*/

nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo2 *iterador=lista;
        while(iterador->siguiente)
        {
            iterador=iterador->siguiente;
        }

        iterador->siguiente=nuevo;
        nuevo->anterior=iterador;
    }
    return lista;
}

nodo2 *buscarNodo(nodo2 *lista, int dato)
{
    nodo2 *resultado;
    if(lista)
    {
        if(lista->dato==dato)
        {
            resultado=lista;
        }
        else
        {
            nodo2 *iterador=lista;
            while(iterador && !resultado)
            {
                if(iterador->dato==dato)
                {
                    resultado=iterador;
                }
                iterador=iterador->siguiente;
            }
        }
    }
    return resultado;
}

void inicFila(Fila *fila)
{
    fila->primero=iniciLista();
    fila->ultimo=iniciLista();
}

void mostrarLista(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            printf("         \n %x| %i | %s |%x \n",iterador->anterior,iterador->dato,iterador->palabra,iterador->siguiente);
            iterador=iterador->siguiente;
        }
    }
    else
    {
        printf("\n la lista esta vacia! ");
    }
}

void encolar(Fila *fila, nodo2 *nuevo)
{
    fila->ultimo=agregarAlFinal(fila->ultimo,nuevo);
    if(fila->primero==NULL)
    {
        fila->primero=fila->ultimo;
    }
    fila->ultimo=nuevo;
}

void desencolar(Fila *fila)
{
    if(fila->primero)
    {
        if(fila->primero==fila->ultimo)
        {
            printf("\n Se eleminara! %i \n",fila->primero->dato);
            free(fila->primero);
            fila->primero=NULL;
            fila->ultimo=NULL;
        }
        else
        {
            printf("\n Se eleminara! %i \n",fila->primero->dato);
            fila->primero=borrarPrimero(fila->primero);
        }
    }
}

nodo2 *desencolar2(Fila *fila)
{
    nodo2 *desencolado=(nodo2*)malloc(sizeof(nodo2));
    if(fila->primero)
    {
        if(fila->primero==fila->ultimo)
        {
            printf("\n Se eleminara! %i \n",fila->primero->dato);
            *desencolado=*fila->primero; //COPIA EL CONTENIDO DE UN PUNTERO EN OTRO
            free(fila->primero);        //DADO QUE FREE() HABILITA A QUE EL SECTOR
            fila->primero=NULL;         //DE MEMORIA PUEDA SER SOBREESCRITO
            fila->ultimo=NULL;
        }
        else
        {
            printf("\n Se eleminara! %i \n",fila->primero->dato);

             *desencolado=*fila->primero;

            fila->primero=borrarPrimero(fila->primero);

        }
    }
    return desencolado;
}

void mostrarFila(Fila *fila)
{
    if(fila)
    {
        mostrarLista(fila->primero);
    }
    else
    {
        printf("\n la lista esta vacia!");
    }
}

void mostrarListaRec(nodo2 *lista)
{
    if(lista)
    {
        printf("\n %i | %s ",lista->dato,lista->palabra);
        mostrarListaRec(lista->siguiente);
    }
}

int menu()
{
    int seleccion;
    printf("\n 1- Agregar elementos a la fila ");
    printf("\n 2- Retirar elementos de la fila");
    printf("\n 3- Mostrar la fila");
    printf("\n \n ESC - SALIR");

    seleccion=getch();
}
