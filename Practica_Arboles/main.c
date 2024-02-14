#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dato;
    struct nodoArbol *izquierdo;
    struct nodoArbol *derecho;
}nodoArbol;

nodoArbol *inicialiar();
nodoArbol *nuevoNodo(int dato);
nodoArbol *agregar(nodoArbol *arbol, nodoArbol *nuevo);
void preOrder(nodoArbol *arbol);
void inOrder(nodoArbol *arbol);
void postOrder(nodoArbol *arbol);
nodoArbol *buscar(nodoArbol *lista, int valor);
int menu();


nodoArbol *inicialiar()
{
    return NULL;
}


int main()
{
    nodoArbol *arbol=inicialiar();
    int opc=0;
    while(opc!=27)
    {
        opc=menu();
        switch(opc)
        {
            case 27: //SALIDA
                printf("\n Saliendo!");
                break;

            case 49:; //1- AGREGAR
                int valor;
                printf("Ingrese el valor a mostrar: ");
                scanf("%d",&valor);
                nodoArbol *nuevo=nuevoNodo(valor);
                arbol=agregar(arbol,nuevo);

                break;

            case 50: //2- Mostrar PreOder
                preOrder(arbol);
                system("pause");
                break;

            case 51: //3- Mostrar InOrder
                inOrder(arbol);
                system("pause");
                break;

            case 52: //4- Mostrar PostOrder
                postOrder(arbol);
                system("pause");
                break;

            case 53:;
                int datoABuscar;
                printf("\nIngrese el valor que se desea buscar: ");
                scanf("%d",&datoABuscar);
                nodoArbol *nodoABuscar=buscar(arbol,datoABuscar);
                if(nodoABuscar)
                {
                    printf("\nEncontrado!. DIR: %x| VALOR: %i",nodoABuscar,nodoABuscar->dato);
                }
                else
                {
                    printf("\n No se encontro el nodo!");
                }
                system("pause");
                break;


            default:
                printf("\n Opcion Invalida! \n");
                break;
        }
    }
    return 0;
}

nodoArbol *nuevoNodo(int dato)
{
    nodoArbol *nuevo=(nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->dato=dato;
    nuevo->izquierdo=NULL;
    nuevo->derecho=NULL;
    return nuevo;
}

nodoArbol *agregar(nodoArbol *arbol, nodoArbol *nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(nuevo->dato > arbol->dato)
        {
            arbol->derecho=agregar(arbol->derecho,nuevo);
        }
        else
        {
            arbol->izquierdo=agregar(arbol->izquierdo,nuevo);
        }
    }
    return arbol;
}

void preOrder(nodoArbol *arbol)
{
    if(arbol)
    {
        printf("%i \n",arbol->dato);
        preOrder(arbol->izquierdo);
        preOrder(arbol->derecho);
    }
}

void inOrder(nodoArbol *arbol)
{
    if(arbol)
    {
        inOrder(arbol->izquierdo);
        printf("%i \n",arbol->dato);
        inOrder(arbol->derecho);
    }
}

void postOrder(nodoArbol *arbol)
{
    if(arbol)
    {
        postOrder(arbol->izquierdo);
        postOrder(arbol->derecho);
        printf("%i \n",arbol->dato);
    }
}

nodoArbol *buscar(nodoArbol *arbol, int valor)
{
    nodoArbol *resultado=NULL;
    if(arbol)
    {
        if(arbol->dato==valor)
        {
            resultado=arbol;
        }
        else
        {
            if(valor>arbol->dato)
            {
                resultado=buscar(arbol->derecho,valor);
            }
            else
            {
                resultado=buscar(arbol->izquierdo,valor);
            }
        }
    }
    return resultado;
}

int menu()
{
    system("cls");
    printf("1- Agregar nodo al arbol \n");
    printf("2- Mostrar el arbol PreORder \n");
    printf("3- Mostrar el arbol InOrder \n");
    printf("4- Mostrar el arbol PostORder \n");
    printf("5- Buscar un nodo según un dato \n");
    printf("ESC- Salir \n");
    int opcion;
    opcion=getch();
    return opcion;
}
