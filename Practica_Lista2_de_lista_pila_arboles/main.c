#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct  //Registro
{
    int id;
    char nombreProducto[80];
    char marca[50];
    float precio;
    char tipo[50];
} RegProducto;

typedef struct
{
    int id;
    char nombreProducto[80];
    char marca[50];
    float precio;
} Producto;

typedef struct //Lista Simple
{
    Producto p;
    struct nodoProducto *sig;
} nodoProducto;

typedef struct //Lista doble
{
    char tipo[50];
    nodoProducto *listaProductos;
    struct nodo2tipo *anterior;
    struct nodo2Tipo *siguiente;
} nodo2Tipo;

typedef struct
{
    float precio;
    struct Pila *sig;
}Pila;

typedef struct
{
    Producto producto;
    struct Arbol *izquierdo;
    struct Arbol *derecho;
}Arbol;

Producto crearProducto(int id,char nombreProducto[80],char marca[50],float precio);

nodoProducto *inicNodoProd();
nodoProducto *crearNodoProductos(Producto p);
nodoProducto *insertarProdOrdenado(nodoProducto *lista,nodoProducto *nuevo);
nodoProducto *insertarProdOrdenadoRec(nodoProducto *lista, nodoProducto *nuevo);
nodoProducto *buscarProducto(nodoProducto *lista,char nombreProducto[80]);
nodoProducto *buscar(nodo2Tipo *lista,char nombreProducto[80]);
int borrarNodoProducto(nodoProducto **lista,char nombreABorrar[80]);
int borrar(nodo2Tipo **lista,char nombreProducto[80]);
nodoProducto *borraListaProducto(nodoProducto *lista);
nodoProducto *agregarAlFinal(nodoProducto *lista,nodoProducto *nuevo);
void mostrarProducto(nodoProducto *producto);
void mostrarListaProducto(nodoProducto *lista);

nodo2Tipo *inicNodo2Tipo();
nodo2Tipo *crearNodo2Tipo(char tipo[50]);
nodo2Tipo *agregarOrdenadoN2(nodo2Tipo *lista,nodo2Tipo *nuevo);
nodo2Tipo *agregarOrdenadoN2Rec(nodo2Tipo *lista,nodo2Tipo *nuevo);
nodo2Tipo *buscarTipo(nodo2Tipo *lista,char nombreTipo[50]);
nodo2Tipo *borrarTipo(nodo2Tipo *lista,char nombreTipo[50]);
nodo2Tipo *borrarListaTipo(nodo2Tipo *lista);
void mostrarListaTipo(nodo2Tipo *lista);
nodo2Tipo *pasarALDDL(nodo2Tipo *lista,char nombreArchivo[80]);

Pila *apilar(Pila *pila,float precio);
Pila *desapilar(Pila **pila);
int pilaVacia(Pila *pila);
float tope(Pila *pila);
Pila *inicPila();
Pila *pilaNueva(float precio);
void mostrarPila(Pila *pila);
void pasarAPila(nodo2Tipo *lista,Pila **pila,float valorLimite);

Arbol *inicArbol();
Arbol *crearNodoArbol(Producto p);
Arbol *insertarOrdenadoArbol(Arbol *arbol,Arbol *nodoArbol);
void *mostrarArbol(Arbol *arbol);
void pasarAArbol(nodo2Tipo *lista,Arbol **arbol,char nombreProducto[80]);

int menu();

int main()
{
    char nombreArchivo[]="RegistroAlimentos.bin";
    int opcion;
    nodo2Tipo *lista=inicNodo2Tipo();
    Pila *pila=inicPila();
    do
    {
        opcion=menu();
        switch(opcion)
        {
        case 49:
        {
            if(!lista)
            {
                lista=pasarALDDL(lista,nombreArchivo);
                printf("\nLista cargada!\n");
            }
            else
            {
                printf("\n\nLa lista ya se encuentra cargada!\n\n");
            }
        }
        break;

        case 50:
            if(lista)
            {
                printf("\n\n\n");
                mostrarListaTipo(lista);
                printf("\n\n\n");
            }
            else
            {
                printf("\n\nLa lista esta vacia!\n\n");
            }
            break;

        case 51:
            if(lista)
            {
                printf("\nIngrese el producto a buscar: ");
                char nombreProducto[80];
                gets(nombreProducto);
                nodoProducto *resultado=buscar(lista,nombreProducto);
                if(resultado)
                {
                    mostrarProducto(resultado);
                }
                else
                {
                    printf("\nProducto no encontrado!\n");
                }
            }
            break;

        case 52:
            if(lista)
            {
                printf("\n\n Ingrese el nombre del producto a borrar: ");
                char productoABorrar[80];
                gets(productoABorrar);
                int estado=borrar(&lista,productoABorrar);
                if(estado==1)
                {
                    printf("\nProducto borrado!\n");
                }
                else
                {
                    printf("\nNo se encontro el producto\n");
                }
            }
            break;
        case 53:
            if(lista)
            {
                lista=borrarListaTipo(lista);
            }
            else
            {
                printf("\n\nla lista ya esta vacia!\n\n");
            }
            break;
        case 54:
            if(lista)
            {
                printf("\n Ingrese el valor tope: ");
                float valor;
                scanf("%f",&valor);
                pasarAPila(lista,&pila,valor);
            }
            else
            {
                printf("\n La lista esta vacia, por lo cual no se puede realizar la operacion\n");
            }

            break;
        case 55:
            if(pilaVacia(pila)==0)
            {
                mostrarPila(pila);
            }
            else
            {
                printf("\nLa pila esta vacia\n");
            }
            break;
        case 56:
            break;
        case 57:
            break;
        case 88:
            break;
        case 120:
            break;
        default:
            printf("Opcion invalido!\n");
            break;
        }

    }
    while(opcion!=88 && opcion!=120);
    return 0;
}

Producto crearProducto(int id,char nombreProducto[80],char marca[50],float precio)
{
    Producto nuevo;
    nuevo.id=id;
    strcpy(nuevo.marca,marca);
    strcpy(nuevo.nombreProducto,nombreProducto);
    nuevo.precio=precio;
    return nuevo;
}

nodoProducto *inicNodoProd()
{
    return NULL;
}

nodoProducto *crearNodoProductos(Producto p)
{
    nodoProducto *nuevo=(nodoProducto*)malloc(sizeof(nodoProducto));
    nuevo->p=p;
    nuevo->sig=NULL;
    return nuevo;
}


nodoProducto *insertarProdOrdenado(nodoProducto *lista,nodoProducto *nuevo)
{
    if(!lista) //Lista vacia
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->p.nombreProducto,nuevo->p.nombreProducto)<0) //Primero en la lista
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodoProducto *iterador=lista;
            nodoProducto *ante=lista;
            while(iterador && strcmpi(iterador->p.nombreProducto,nuevo->p.nombreProducto)>0) //Iterar hasta cumplir condicion o fin de lista
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            if(!iterador) //Si es el ultimo
            {
                ante->sig=nuevo;
            }
            else //Si es un nodo intermedio
            {
                ante->sig=nuevo;
                nuevo->sig=iterador;
            }
        }
    }
    return lista;
}

nodoProducto *insertarProdOrdenadoRec(nodoProducto *lista, nodoProducto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->p.nombreProducto,nuevo->p.nombreProducto)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarProdOrdenadoRec(lista->sig,nuevo);
        }
    }

    return lista;
}

nodoProducto *buscarProducto(nodoProducto *lista,char nombreProducto[80])
{
    nodoProducto *resultado=NULL;
    if(lista)
    {
        if(strcmpi(lista->p.nombreProducto,nombreProducto)==0)
        {
            resultado=lista;
        }
        else
        {
            nodoProducto *iterador=lista;
            while(iterador && resultado==NULL)
            {
                if(strcmpi(iterador->p.nombreProducto,nombreProducto)==0)
                {
                    resultado=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }
    return resultado;
}

nodoProducto *buscar(nodo2Tipo *lista,char nombreProducto[80])
{
    nodoProducto *resultado=NULL;
    if(lista)
    {
        nodo2Tipo *iterador=lista;
        while(iterador && !resultado)
        {
            resultado=buscarProducto(iterador->listaProductos,nombreProducto);
            iterador=iterador->siguiente;
        }
    }
    return resultado;
}

int borrarNodoProducto(nodoProducto **lista,char nombreABorrar[80])
{
    int borrado=0;
    if(lista)
    {
        if(strcmpi((*lista)->p.nombreProducto,nombreABorrar)==0)
        {
            nodoProducto *TEMP=(*lista)->sig;
            free((*lista));
            (*lista)=TEMP;
            borrado=1;
        }
        else
        {
            nodoProducto *iterador=(*lista);
            nodoProducto *ante=iterador;
            while(iterador && borrado==0)
            {
                if(strcmpi(iterador->p.nombreProducto,nombreABorrar)==0)
                {
                    ante->sig=iterador->sig;
                    free(iterador);
                    borrado=1;
                }
                ante=iterador;
                iterador=iterador->sig;
            }
        }
    }
    return borrado;
}

int borrar(nodo2Tipo **lista,char nombreProducto[80])
{
    int estado=0;
    if(lista)
    {
        nodo2Tipo *iterador=(*lista);
        while(iterador && estado==0)
        {
            if(borrarNodoProducto(&iterador->listaProductos,nombreProducto)==1)
            {
                estado=1;
            }
            iterador=iterador->siguiente;
        }

    }
    return estado;
}
nodoProducto *borraListaProducto(nodoProducto *lista)
{
    if(lista)
    {
        nodoProducto *aux;
        while(aux)
        {
            aux=lista->sig;
            free(lista);
            lista=aux;
        }
    }
    return lista;
}

nodoProducto *agregarAlFinal(nodoProducto *lista,nodoProducto *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
        lista->sig=NULL;
    }
    else
    {
        nodoProducto *iterador=lista;
        while(iterador->sig!=NULL)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }

    return lista;
}
void mostrarProducto(nodoProducto *producto)
{
    printf("%-2i %-30s %-30s %0.2f\n",producto->p.id,producto->p.marca,producto->p.nombreProducto,producto->p.precio);
}

void mostrarListaProducto(nodoProducto *lista)
{
    if(lista)
    {
        nodoProducto *iterador=lista;
        while(iterador)
        {
            mostrarProducto(iterador);
            iterador=iterador->sig;
        }
    }
}

nodo2Tipo *inicNodo2Tipo()
{
    return NULL;
}

nodo2Tipo *crearNodo2Tipo(char tipo[50])
{
    nodo2Tipo *nuevo=(nodo2Tipo*)malloc(sizeof(nodo2Tipo));
    strcpy(nuevo->tipo,tipo);
    nuevo->anterior=NULL;
    nuevo->listaProductos=NULL;
    nuevo->siguiente=NULL;
    return nuevo;
}


nodo2Tipo *agregarOrdenadoN2(nodo2Tipo *lista,nodo2Tipo *nuevo)
{
    if(!lista) //Si esta vacio
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->tipo,nuevo->tipo)>0) //Si esta en el primer lugar de la lista
        {
            nuevo->siguiente=lista;
            lista->anterior=nuevo;
            lista=nuevo;
        }
        else
        {
            nodo2Tipo *iterador=lista;
            nodo2Tipo *ante=iterador;
            while(iterador && strcmpi(iterador->tipo,nuevo->tipo)<=0)
            {
                ante=iterador;
                iterador=iterador->siguiente;
            }
            if(!iterador)  //Si es el ultimo nodo
            {
                ante->siguiente=nuevo;
                nuevo->anterior=ante;
            }
            else  //Si es un nodo intermedio
            {
                ante->siguiente=nuevo;
                nuevo->anterior=ante;

                nuevo->siguiente=iterador;
                iterador->anterior=nuevo;
            }
        }
    }
    return lista;
}

nodo2Tipo *agregarOrdenadoN2Rec(nodo2Tipo *lista,nodo2Tipo *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->tipo,nuevo->tipo))
        {
            nuevo->anterior=lista->anterior;
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else
        {
            lista->siguiente=agregarOrdenadoN2Rec(lista->siguiente,nuevo);
        }
    }

    return lista;
}

nodo2Tipo *buscarTipo(nodo2Tipo *lista,char nombreTipo[50])
{
    nodo2Tipo *resultado=NULL;
    if(lista)
    {
        if(strcmpi(lista->tipo,nombreTipo)==0)
        {
            resultado=lista;
        }
        else
        {
            nodo2Tipo *iterador=lista;
            while(iterador && !resultado)
            {
                if(strcmpi(iterador->tipo,nombreTipo)==0)
                {
                    resultado=iterador;
                }
                iterador=iterador->siguiente;
            }
        }
    }
    return resultado;
}

nodo2Tipo *borrarTipo(nodo2Tipo *lista,char nombreTipo[50])
{
    if(lista)
    {
        nodo2Tipo *aBorrar=buscarTipo(lista,nombreTipo);
        if(aBorrar)
        {
            if(!aBorrar->anterior) //Si es el primero
            {
                nodo2Tipo *temp=lista->siguiente;
                free(lista);
                lista=temp;
                lista->anterior=NULL;
            }
            else
            {
                if(!aBorrar->siguiente) //Si es el ultimo
                {
                    nodo2Tipo *temp=aBorrar->anterior;
                    free(aBorrar);
                    temp->siguiente=NULL;
                }
                else  //Si se encuentra entre 2 nodos
                {
                    nodo2Tipo *ante=aBorrar->anterior;
                    nodo2Tipo *sig=aBorrar->siguiente;
                    free(aBorrar);
                    ante->siguiente=sig;
                    sig->anterior=ante;
                }
            }
        }
    }
    return lista;
}

nodo2Tipo *borrarListaTipo(nodo2Tipo *lista)
{
    if(lista)
    {
        nodo2Tipo *temp;
        while(lista)
        {
            lista->listaProductos=borraListaProducto(lista->listaProductos);
            temp=lista->siguiente;
            free(lista);
            lista=temp;
        }
    }
    return lista;
}

void mostrarListaTipo(nodo2Tipo *lista)
{
    if(lista)
    {
        nodo2Tipo *iterador=lista;
        while(iterador)
        {
            printf("\n\n*******%s*******\n\n",iterador->tipo);
            mostrarListaProducto(iterador->listaProductos);
            iterador=iterador->siguiente;
        }
    }
}


nodo2Tipo *pasarALDDL(nodo2Tipo *lista,char nombreArchivo[80])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        RegProducto buffer;
        while(fread(&buffer,sizeof(RegProducto),1,archivo)>0)
        {
            Producto p=crearProducto(buffer.id,buffer.nombreProducto,buffer.marca,buffer.precio);
            nodoProducto *nuevo=crearNodoProductos(p);
            nodo2Tipo *posTipo=buscarTipo(lista,buffer.tipo);
            if(!posTipo)
            {
                nodo2Tipo *nuevoT=crearNodo2Tipo(buffer.tipo);
                posTipo=nuevoT;
                lista=agregarOrdenadoN2(lista,nuevoT);
            }
            posTipo->listaProductos=insertarProdOrdenado(posTipo->listaProductos,nuevo);
        }
        fclose(archivo);
    }
    else
    {
        printf("Archivo no encontrado\n");
    }
    return lista;
}



Pila *pilaNueva(float precio)
{
    Pila *nuevo=(Pila*)malloc(sizeof(Pila));
    nuevo->precio=precio;
    nuevo->sig=NULL;
    return nuevo;
}

Pila *apilar(Pila *pila,float precio)
{
    Pila *nuevo=pilaNueva(precio);
    if(!pila)
    {
        pila=nuevo;
    }
    else
    {
        nuevo->sig=pila;
        pila=nuevo;
    }
    return pila;
}

Pila *desapilar(Pila **pila)
{
    Pila *retorno=NULL;
    if(pila)
    {
        retorno=pilaNueva((*pila)->precio);
        Pila *aux=(*pila)->sig;
        free(*pila);
        (*pila)=aux;
    }
    return retorno;
}

int pilaVacia(Pila *pila)
{
    return(!pila) ? 1: 0;
}

float tope(Pila *pila)
{
    float tope=0;
    if(pila)
    {
        tope=pila->precio;
    }
    return tope;
}

Pila *inicPila()
{
    return NULL;
}

void mostrarPila(Pila *pila)
{
    if(pila)
    {
        Pila *iterador=pila;
        while(iterador)
        {
            printf(" %0.2f \n",iterador->precio);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("\n La pila esta vacia!\n");
    }
}

void pasarAPila(nodo2Tipo *lista,Pila **pila,float valorLimite)
{
    if(lista)
    {
        nodo2Tipo *iteradorN2=lista;
        while(iteradorN2)
        {
            nodoProducto *iteradorProd=iteradorN2->listaProductos;
            while(iteradorProd)
            {
                if(iteradorProd->p.precio<=valorLimite)
                {
                    *pila=apilar(*pila,iteradorProd->p.precio);
                }
                iteradorProd=iteradorProd->sig;
            }
            iteradorN2=iteradorN2->siguiente;
        }
    }
}

Arbol *inicArbol()
{
    return NULL;
}

Arbol *crearNodoArbol(Producto p)
{
    Arbol *nuevo=(Arbol*)malloc(sizeof(Arbol));
    nuevo->producto=p;
    nuevo->izquierdo=NULL;
    nuevo->derecho=NULL;
    return nuevo;
}

Arbol *insertarOrdenadoArbol(Arbol *arbol,Arbol *nodoArbol)
{
    if(!arbol)
    {
        arbol=nodoArbol;
    }
    else
    {
       if(strcmpi(arbol->producto.nombreProducto,nodoArbol->producto.nombreProducto)<0)
       {
           arbol->izquierdo=insertarOrdenadoArbol(arbol->izquierdo,nodoArbol);
       }
       else
       {
           arbol->derecho=insertarOrdenadoArbol(arbol->derecho,nodoArbol);
       }
    }
    return arbol;
}

void *mostrarArbol(Arbol *arbol)
{
    if(arbol)
    {
        mostrarArbol(arbol->izquierdo);
        printf("ID: %i MARCA: %s PROD: %s PRECIO: %0.2f \n",arbol->producto.id,arbol->producto.marca,arbol->producto.nombreProducto,arbol->producto.precio);
        mostrarArbol(arbol->derecho);
    }
}

void pasarAArbol(nodo2Tipo *lista,Arbol **arbol,char nombreProducto[80])
{
    if(lista)
    {
        nodo2Tipo *iteradorTipo=lista;
        while(iteradorTipo)
        {
            nodoProducto *iteradorProducto=iteradorTipo->listaProductos;

            while(iteradorProducto)
            {
                if(strcmpi(iteradorProducto->p.marca,nombreProducto)==0)
                {
                    Arbol *nuevo=crearNodoArbol(iteradorProducto->p);
                    *arbol=insertarOrdenadoArbol(*arbol,nuevo);
                }
                iteradorProducto=iteradorProducto->sig;
            }
            iteradorTipo=iteradorTipo->siguiente;
        }
    }
}

int menu()
{
    int opcion=0;
    printf("1- Pasar registros.bin a Lista Doble de Listas\n");
    printf("2- Mostrar todo\n");
    printf("3- Buscar producto\n");
    printf("4- Borrar producto\n");
    printf("5- Borrar todas las listas\n");
    printf("6- Mover a pila los precios menores a X\n");
    printf("7- Mostrar la pila\n");
    printf("8- Mover a Arbol todos los productos de marca X\n");
    printf("9- Mostrar el arbol\n");
    printf("X- salir \n");

    opcion=getch();
    return opcion;
}
