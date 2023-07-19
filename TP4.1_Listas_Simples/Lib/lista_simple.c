#include "lista_simple.h"


nodo *inicializar()
{
    return NULL;
}

nodo *crearNodo(int dato)
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;
    return nuevo;
}
nodo *insertarAlPrincipio(nodo *lista,nodo *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
        nuevo->siguiente=NULL;
    }
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}

nodo *insertarAlFinal(nodo *lista, nodo *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
        //nuevo->siguiente=NULL; //por las dudas
    }
    else
    {
        nodo *aux=lista;
        while(aux->siguiente!=NULL)
        {
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
    }
    return lista;
}

nodo *insertarOrdenado(nodo *lista, nodo *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(lista->dato >= nuevo->dato) // SI ES EL PRIMERO
        {
            printf("primero \n");
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else
        {
            nodo *auxiliar=lista;
            nodo *anterior=lista;
            while(auxiliar!=NULL && auxiliar->dato < nuevo->dato)
            {
                anterior=auxiliar;
                auxiliar=auxiliar->siguiente;
            }
            nuevo->siguiente=auxiliar;
            anterior->siguiente=nuevo;
        }

    }
    return lista;
}
nodo *buscarNodo(nodo *lista,int datoABuscar)
{
    nodo *resultadoBusqueda=NULL;
    nodo *auxiliar=lista;
    if(auxiliar!=NULL)
    {
        while(auxiliar!=NULL && resultadoBusqueda==NULL)
        {
            if(auxiliar->dato==datoABuscar)
            {
                resultadoBusqueda=auxiliar;
            }
            auxiliar=auxiliar->siguiente;
        }

    }
    else
    {
        printf("la lista esta vacia!");
    }

    return resultadoBusqueda;
}
void *borrarNodo(nodo *lista, int dato)
{
    if(lista!=NULL)
    {
        nodo *anterior=lista;
        nodo *auxiliar=lista;

        while(auxiliar!=NULL)
        {
            if(lista->dato==dato)
            {
                anterior->siguiente=auxiliar->siguiente;
                free(auxiliar);
            }
            anterior=auxiliar;
            auxiliar=auxiliar->siguiente;
        }
    }
    else
    {
        printf("La lista esta vacia! \n");
    }
}
void mostrarLista(nodo *lista)
{
    if(lista!=NULL)
    {
        nodo *auxiliar=lista;

        while(auxiliar!=NULL)
        {
            printf("NODO: %x, DATO: %i \n",&auxiliar,auxiliar->dato);
            auxiliar=auxiliar->siguiente;
        }
    }
    else
    {
        printf("La lista esta vacia! \n");
    }
}
void mostrarListaNumerada(nodo *lista, int maxItemsPorLinea)
{
    nodo *auxiliar=lista;
    int contador=0;
    int posicion=0;
    while(auxiliar!=NULL)
    {
        printf("NODO %2i : %2i P: %x |",posicion,auxiliar->dato,auxiliar);
        contador++;
        posicion++;
        if(contador==maxItemsPorLinea)
        {
            printf("\n");
            contador=0;
        }
        auxiliar=auxiliar->siguiente;
    }
    printf("\n");
}
nodo *pasarArchivoALista(char nombreArchivo[30])
{
    nodo *lista=inicializar();

    FILE *archivo=fopen(nombreArchivo,"r");

    if(archivo)
    {
        nodo buffer;
        while(fread(&buffer,sizeof(nodo),1,archivo)>0)
        {
            nodo *nuevo=crearNodo(buffer.dato);
            lista=insertarAlPrincipio(lista,nuevo);
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo no existe o no se pudo abrir!");
    }

    return lista;
}
nodo *pasarArchivoAListaOrdenado(char nombreArchivo[30])
{
    nodo *lista=inicializar();

    FILE *archivo=fopen(nombreArchivo,"r");

    if(archivo)
    {
        nodo buffer;
        while(fread(&buffer,sizeof(nodo),1,archivo)>0)
        {
            nodo *nuevo=crearNodo(buffer.dato);
            lista=insertarOrdenado(lista,nuevo);
            //lista=insertarAlPrincipio(lista,nuevo);
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo no existe o no se pudo abrir!");
    }
    return lista;
}


int buscarEnListaOrdenada(nodo *lista, int dato)
{
    int flag=0;
    if(lista!=NULL)
    {
        nodo *auxiliar=lista;
        while(auxiliar!=NULL && flag==0 && auxiliar->dato<dato)
        {
            if(lista->dato==dato)
            {
                flag=1;
            }
            auxiliar=auxiliar->siguiente;
        }
    }
    return flag;
}

int buscarEnListaDesordenada(nodo *lista,int dato)
{
    int flag=0;
    if(lista!=NULL)
    {
        nodo *auxiliar=lista;
        while(auxiliar!=NULL && flag==0)
        {
            if(dato==lista->dato)
            {
                flag=1;
            }
            auxiliar=auxiliar->siguiente;
        }
    }
    return flag;
}


nodo *intercalarListas(nodo *lista1, nodo* lista2)
{
nodo *l1=lista1;
nodo *l2=lista2;
nodo *intercalada=NULL;
nodo *aux=NULL;

while(l1!=NULL && l2!=NULL)
{
    if(aux==NULL) //si la lista esta vacia
    {
        if(l1->dato<=l2->dato)
        {
            aux=l1;
        }
        else
        {
            aux=l2;
        }
        intercalada=aux; //define el primer puntero al arreglo de la lista solucion
    }
}
}


nodo *generarListaAleatoria(int cantNodos,int limiteInferior,int limiteSuperior)
{
    //srand(time(NULL));
    int contador=0;
    nodo *listaGenerada=NULL;
    while(contador<cantNodos)
    {
        int valorAzar=numeroRND(limiteInferior,limiteSuperior);
        nodo *nuevo=(nodo*)malloc(sizeof(nodo));
        nuevo->dato=valorAzar;
        nuevo->siguiente=NULL;
        //listaGenerada=insertarAlPrincipio(listaGenerada,nuevo);
        listaGenerada=insertarAlFinal(listaGenerada,nuevo);
        contador++;
    }
    return listaGenerada;
}

void generarArchivoRegistros(char nombreArchivo[30])
{
    nodo arreglo[30];
    for(int x=0;x<30;x++)
    {
        nodo buffer;
        buffer.dato=numeroRND(1,10);
        buffer.siguiente=NULL;
        arreglo[x]=buffer;
    }
    FILE *archivo=fopen(nombreArchivo,"w");
    if(archivo)
    {
        for(int x=0; x<30;x++)
        {
            fwrite(&arreglo[x],sizeof(nodo),1,archivo);
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo no se pudo crear! \n");
    }
}

int numeroRND(int limiteMinimo, int limiteMaximo)
{
    return limiteMinimo+ rand()%limiteMaximo;
}

