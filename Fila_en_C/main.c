#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int numero;
    char palabra[40];
}Dato;

typedef struct Nodo2
{
    struct Nodo2 *anterior;
    struct Nodo2 *siguiente;
    Dato dato;
}Nodo2;

typedef struct
{
     struct Nodo2 *inicio;
     struct Nodo2 *fin;
}Fila;

Nodo2 *inicNodo2()
{
    return NULL;
}

void inicFila(Fila *fila)
{
    fila->inicio=inicNodo2();
    fila->fin=inicNodo2();
}

void mostrarFila(Fila *fila)
{
    if(fila->inicio!=NULL)
    {
        printf("\n\n");
        Nodo2 *aux=fila->inicio;
        while(aux!=NULL)
        {
            printf("%i|%s\n",aux->dato.numero,aux->dato.palabra);
            aux=aux->siguiente;
        }
    }
    else
    {
        printf("\nLa fila esta vacia!\n");
    }
}

Nodo2 *agregarAlFinal(Nodo2 *lista, Nodo2 *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        Nodo2 *iterador=lista;
        while(iterador->siguiente)
        {
            iterador=iterador->siguiente;
        }
        iterador->siguiente=nuevo;
        nuevo->anterior=lista;
    }
    return lista;
}

void insertarEnFila(Fila *fila, Nodo2 *nuevo)
{
    if(fila->fin==NULL)
    {
        fila->fin=nuevo;
        fila->inicio=fila->fin;
    }
    else
    {
        fila->inicio=agregarAlFinal(fila->inicio,nuevo);
        fila->fin=nuevo;
    }
}

Nodo2 *buscarNodoPorPalabra(Fila *fila,char palabra[])
{
    int nodo1=1;
    Nodo2 *resultado=NULL;
    if(fila->inicio!=NULL)
    {
        Nodo2 *aux=fila->inicio;
        while(aux!=NULL && resultado==NULL)
        {
            if(strcmp(palabra,aux->dato.palabra)==0)
            {
                resultado=aux;
            }
            aux=aux->siguiente;
            nodo1++;
        }
    }
    return resultado;
}



int menu()
{
    int opcion;
    printf("\n1-Cargar datos a la fila\n");
    printf("2-Mostrar la fila\n");
    printf("3-Buscar elemento por palabra\n");
    printf("4-Borrar elemento por palabra\n");
    printf("\n\nESC-Salir: ");
    opcion=getch();
}

Nodo2 *nuevoNodo2(int numero, char palabra[])
{
    Nodo2 *nuevo=(Nodo2*)malloc(sizeof(Nodo2));
    nuevo->dato.numero=numero;
    strcpy(nuevo->dato.palabra,palabra);
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;
    return nuevo;
}

void mostrarNodo(Nodo2 *nodo)
{
    if(nodo!=NULL)
    {
        printf("\n%i|%s\n",nodo->dato.numero,nodo->dato.palabra);
    }
    else
    {
        printf("\nLa lista esta vacia!\n");
    }
}


Nodo2 *extraer(Fila *fila)
{
    Nodo2 *extraido=NULL;

    if(fila->inicio!=NULL)
    {
        extraido=fila->inicio;    //Al ser FIFO extra desde el inicio de la fila
        extraido->siguiente==NULL; //Desvincula el nodo extraido de la lista (opcional)
        fila->inicio=fila->inicio->siguiente;
        {
            if(!fila->inicio)    //Si el inicio esta vacio, el ultimo puntero tambien
            {
                fila->fin=NULL;
            }
        }
        //la memoria del nodo extraido se debe liberar por fuera de la funcion
    }
    return extraido;
}

int main()
{
    Fila nuevaFila;
    inicFila(&nuevaFila);

    int opcion=0;
    while(opcion!=27)
    {
        opcion=menu();
        switch(opcion)
        {
        case 27:

            break;

        case 49:;
            int dato=69;
            while(dato!=-1)
            {
                printf("\n");
                printf("Ingrese un numero para cargar (-1 para cancelar y salir): ");
                scanf("%d",&dato);
                if(dato!=-1)
                {
                    char palabra[30];
                    printf("Ingrese una palabra para ingresar ");
                    scanf("%s",palabra);
                    Nodo2 *nuevo=nuevoNodo2(dato,palabra);
                    insertarEnFila(&nuevaFila,nuevo);
                }
            }
            break;
        case 50:
            mostrarFila(&nuevaFila);
            break;
        case 51:
            printf("\nIngrese la palabra a buscar: ");
            char palabra[50];
            scanf("%s",palabra);
            Nodo2 *resultado=buscarNodoPorPalabra(&nuevaFila,palabra);
            mostrarNodo(resultado);

            break;
        case 52:;
            Nodo2 *extraido=NULL;
            extraido=extraer(&nuevaFila);
            if(extraido!=NULL)
            {
                printf("\nSe extrajo %i|%s\n",extraido->dato.numero,extraido->dato.palabra);
            }
            else
            {
                printf("\nLa lista esta vacia!\n");
            }

            break;
        default:

            printf("\nOpcion invalida!\n");
            break;
        }
    }
    return 0;
}
