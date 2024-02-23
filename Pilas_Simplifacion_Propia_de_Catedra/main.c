#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *dato;
    int posicionTope;
}Pila;

void inicPila(Pila *pila);
void apilar(Pila *pila,int dato);
int desapilar(Pila *pila);
int tope(Pila *pila);
int pilaVacia(Pila *pila);
void leer(Pila *pila);

void mostrarPila(Pila *pila);

int menu()
{
    int opcion=0;
    printf("\n1-Apilar un valor: ");
    printf("\n2-Desapilar");
    printf("\n3-Mostrar tope");
    printf("\n4-Verificar si la pila esta vacia");
    printf("\n\nESC- salir ");
    opcion=getch();
}

int main()
{

    Pila pila;
    inicPila(&pila);

    int opcionMenu=0;
    while(opcionMenu!=27)
    {
        opcionMenu=menu();

        switch(opcionMenu)
        {
        case 27:
            printf("\nSaliendo!");
            break;

        case 49:
            leer(&pila);
            break;

        case 50:
            desapilar(&pila);
            break;

        case 51:;
            int valorTope=tope(&pila);
            printf("\ %i",valorTope);
            break;

        case 52:;
            int estado=pilaVacia(&pila);
            if(estado==1)
            {
                printf("\nLa pila no esta vacia");
            }
            else
            {
                printf("\nLa Pila esta vacia!");
            }
            break;

        case 53:

            break;

        default:
            printf("\nOpcion Invalida!");
            break;

        }
    }

    return 0;
}

void inicPila(Pila *pila)
{
    pila->dato=(int*)malloc(4*(sizeof(int)));
    pila->posicionTope=0;
}

void apilar(Pila *pila,int dato)
{
    if(pila->posicionTope<4)
    {
        int tope=pila->posicionTope;
        pila->dato[tope]=dato;
        pila->posicionTope=pila->posicionTope+1;
        printf("\nApilado!");
    }
    else
        printf("\nLa pila esta llena!");
}

int desapilar(Pila *pila)
{
    int valor=-1;
    if(pila->posicionTope!=0)
    {
        valor=pila->dato[pila->posicionTope-1];
        pila->posicionTope--;
    }
    else
    {
        printf("\nLa lista esta vacia!");
    }
    return valor;
}

int tope(Pila *pila)
{
    return pila->dato[pila->posicionTope- 1];
}

int pilaVacia(Pila *pila)
{
    int estado=1;
    if(pila->posicionTope==0)
    {
        printf("\nLa pila esta vacia!");
        estado=0;
    }
    return estado;
}

void leer(Pila *pila)
{
    int valor=0;
    printf("\nIngrese el valor a cargar: ");
    scanf("%d",&valor);
    apilar(pila,valor);
}
