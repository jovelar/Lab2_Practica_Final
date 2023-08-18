#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "file1.h"


typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
} registroArchivo;  //archivo

typedef struct
{
    int idSucursal;
    char nombreSucursal[25];
} stSucursal;   // nodo lista

typedef struct
{
    char nombreDisfraz[25];
    char generoDisfraz[25];
    int stockDisfraz;
} stDisfraz; //nodo arbol

typedef struct
{
    stDisfraz dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;

typedef struct _nodoCelda
{
    stSucursal dato;
    nodoArbol* arbol;
    struct _nodoCelda* siguiente;
} nodoCelda;

///encabezados

//1
nodoCelda* inicListaCeldas();
nodoCelda* alta(nodoCelda* lda, stDisfraz nuevoDisfraz, stSucursal nuevaSucursal);
nodoCelda* buscarNodoCelda(nodoCelda* lda, stSucursal nuevaSucursal);
nodoCelda* crearNodoCeldas(stSucursal sucursal);
nodoArbol* inicArbol();
nodoCelda* agregarAlPpioCeldas(nodoCelda* lista, nodoCelda* nuevoNodo);
nodoArbol* insertar(nodoArbol* arbol, stDisfraz dato);
nodoArbol* crearNodoArbol(stDisfraz dato);
nodoCelda* archivoALDA(char nombreArchivo[], nodoCelda* lda);

//3
int disfracesPorSucursal(nodoCelda* lda, stSucursal array[], char nombre[], char genero[],int validos);

//4
nodoArbol* nombreYgenero(nodoArbol* arbol, char nombre[], char genero[]);
stSucursal menorCantPorGenero(nodoCelda* lda, char genero[]);

//5
float procentaje(nodoCelda* lda, int id);


int main()
{
    //LDA = Lista de Arboles

    //1
    nodoCelda* LDA = inicListaCeldas();
    LDA = archivoALDA("archivoRegistrosDisfraces.bin", LDA);

    //2
    mostrarLDA(LDA);

    //3
    int dimA=5;
    stSucursal A[dimA];
    int validosA = 0;

//    printf("\n\nIngrese nombre disfraz: ");
//    char nombreBuscado[30];
//    gets(nombreBuscado);
//    printf("\n\nIngrese genero disfraz: ");
//    char generoBuscado[30];
//    gets(generoBuscado);
//    validosA = buscarDisfrazPorSucursal(LDA, A, nombreBuscado ,generoBuscado, validosA);


    validosA = disfracesPorSucursal(LDA, A, "indio","ninio", validosA);
    mostrarHallado(A, validosA);

    //4
//    printf("\n\nIngrese genero a buscar entre las sucursales: ");
//    char generoBusc[30];
//    gets(generoBusc);

    printf("\n\nLa sucursal con menos disfraces del genero es:");

    mostrarUnaSucursal(menorCantPorGenero(LDA,"hombre"));
//    mostrarSucursal(menorPorGenero(LDA,generoBusc));


    //5

//    printf("Ingrese el id de la tienda a buscar: ");
//    int idTiendaBuscado;
//    scanf("%i",&idTiendaBuscado);

//    float porcentaje = procentaje(LDA, idTiendaBuscado);
    float porcentaje = procentaje(LDA, 3);

    printf("\nporcentaje de tienda  %.2f %%\n", porcentaje);


    prueba();
    return 0;
}
///5

//5.1
float procentaje(nodoCelda* lda, int id)
{
    int total = stockTotal(lda);
    int tienda = stockSucursal(lda, id);
    float rta = (float) tienda*100 / (float) total;

    return rta;
}


//5.2
int stockTotal(nodoCelda* lda)  //calcula el stock total
{
    int suma = 0;
    if(lda)
    {
        nodoCelda* seguidora = lda; //seguridad lda

        while(seguidora)    //se avanza entre celdas por siguiente
        {
            suma = suma + sumarStockDelArbol(seguidora->arbol); //le paso el arbol
            seguidora = seguidora->siguiente;   //avanzo a siguiente celda
        }
    }
    return suma;
}


//5.3
int sumarStockDelArbol(nodoArbol* arbol){
    int suma = 0;
    if(arbol){
        suma = arbol->dato.stockDisfraz + sumarStockDelArbol(arbol->der) + sumarStockDelArbol(arbol->izq);  //tipica suma recursiva para el arbol
    }
    return suma;
}


//5.4
int stockSucursal(nodoCelda* lda, int id)
{
    int rta = 0;
    if(lda)
    {
        nodoCelda* seguidora = lda; //seguridad lda

        int flag = 0;

        while(flag == 0 && seguidora)   //chequeo que no haya flag en cada nueva celda qeu recorro
        {
            if(seguidora->dato.idSucursal == id)    //si el dato de la celda es igual al buscado
            {
                rta = sumarStockDelArbol(seguidora->arbol); //sumo stock del arbol
                flag = 1;   //corto bucle
            }
            if(flag == 0)   //si no se encuentra el id
            {
                seguidora = seguidora->siguiente;   //sigo recorriendo las celdas
            }
        }
        if(seguidora == NULL)   //formalidad
        {
            printf("\nEl ID de la sucursal que ingresaste no es correcto\n");
            rta = 0;
        }
    }
    return rta;
}







///4

//4.1
stSucursal menorCantPorGenero(nodoCelda* lda, char genero[])
{
    int cantidad = 0;
    int suma = cantidad + 10000;    //se supone que no tienen 10000 disfraces jaja
    stSucursal rta;

    if(lda)
    {
        nodoCelda* seguidora = lda; //seguridad lda
        rta = seguidora->dato;  //asigno la primer sucursal


        while(seguidora)    //como las celdas son listas
        {
            cantidad = cantGenero(seguidora->arbol, genero);    //le pasa el arbol de cada celda y el genero y devuelve la cant del genero en el arbol

            if(cantidad < suma) //si la cant es menor al minimo
            {
                rta = seguidora->dato;  //rta = sucursal
                suma = cantidad;    //nuevo minimo
            }
            seguidora = seguidora->siguiente;   //avanzo a siguiente arbol
        }
    }
    return rta;
}

//4.2
int cantGenero(nodoArbol* arbol, char genero[])
{
    int rta = 0;
    if(arbol)
    {
        if(strcmpi(arbol->dato.generoDisfraz, genero) == 0)    //si encuentra un genero buscado en arbol
        {
            rta = 1 + cantGenero(arbol->izq, genero) + cantGenero(arbol->der, genero);  //suma 1
        }
        else
        {
            rta = cantGenero(arbol->izq, genero) + cantGenero(arbol->der, genero);  //sino suma 0
        }
    }
    return rta;
}

//4.3
void mostrarUnaSucursal(stSucursal dato)
{
    printf("\n-------------------------------------\n");
    printf("\nId Sucursal: %i", dato.idSucursal);
    printf("\n   Sucursal: %s", dato.nombreSucursal);
    printf("\n-------------------------------------\n");
}



///3

//3.1
int disfracesPorSucursal(nodoCelda* lda, stSucursal A[], char nombre[], char genero[],int validos)
{
    nodoArbol* rta = NULL;

    if(lda) //si hay lda
    {
        nodoCelda* seguidora = lda; //seguridad para lda

        while(seguidora)    //porque es lista de arboles
        {
            if(seguidora->arbol)    //si en cada celda de la lista hay un arbol
            {
                rta = nombreYgenero(seguidora->arbol, nombre, genero);  //busco nombre y genero en arbol

                if(rta) //si lo encontro
                {
                    A[validos] = seguidora->dato;
                    validos ++;
                }

            }
            seguidora = seguidora->siguiente;   //avanzo sobre las celdas
            rta = NULL;
        }
    }
    return validos;
}

//3.2
nodoArbol* nombreYgenero(nodoArbol* arbol, char nombre[], char genero[])
{
    nodoArbol* rta = NULL;

    if(arbol)   //si esta primero (en la pos actual de la celda)
    {
        if(strcmpi(nombre, arbol->dato.nombreDisfraz) == 0 && strcmpi(genero, arbol->dato.generoDisfraz) == 0 && arbol->dato.stockDisfraz > 0)  //comparo parametros con arbol
        {
            rta = arbol;
        }
        else    //si no esta primero
        {
            rta = nombreYgenero(arbol->izq, nombre, genero);

            if(rta == NULL) //si recorrio la rama izq y no lo encontro
            {
                rta = nombreYgenero(arbol->der, nombre, genero);
            }
        }
    }
    return rta;
}
/*
Como esta ordenado por otro campo tengo que recorrer todo el arbol, o al menos de a ramas enteras
*/


//3.4
void mostrarHallado(stSucursal A[], int validos)
{
    int i = 0;
    while(i < validos)
    {
        hallado(A[i]);
        i++;
    }
}
/*
Por enunciado debo pasar a un arreglo y mostrar dicho arreglo en main
*/

//3.5
void hallado(stSucursal dato)
{
    printf("\n\nDisfraz encontrado en la sucursal %s de ID %i",dato.nombreSucursal,dato.idSucursal);
}




///2
//2.1
void mostrarLDA(nodoCelda* lda)
{
    if(lda)
    {
        nodoCelda* seguidora = lda; //seguridad
        while(seguidora)
        {
            mostrarUnaCelda(seguidora);
            seguidora = seguidora->siguiente;
        }
    }
    else
    {
        printf("\n lda vacia !\n");
    }
}


//2.2
void mostrarUnaCelda(nodoCelda* celda)
{
    printf("\n");
    printf("\n  ID SUCURSAL: %i\n", celda->dato.idSucursal);
    printf("Nombre sucursal: %s\n", celda->dato.nombreSucursal);
//    printf("\n arbol mostrado\n");
    inOrder(celda->arbol);
}


//2.3
void inOrder(nodoArbol* arbol)
{
    if(arbol)
    {
        inOrder(arbol->izq);
        mostrarUnDisfraz(arbol->dato);
        inOrder(arbol->der);
    }
}
/*
izq,raiz,der
Se supone que la izq es menor, luego sigue la raiz y el mas grande es el de la derecha por lo que quedarian ordenados por orden alfabetico
*/


//2.4
void mostrarUnDisfraz(stDisfraz dato)
{
    printf("\nDisfraz nombre: %s\n",dato.nombreDisfraz);
    printf("\nDisfraz genero: %s", dato.generoDisfraz);
    printf("\n         Stock: %i", dato.stockDisfraz);
}


///1

//1.1
nodoCelda* archivoALDA(char nombreArchivo[], nodoCelda* lda)
{
    FILE *archivo = fopen(nombreArchivo, "rb");

    registroArchivo nuevoRegistro;
    stDisfraz nuevoDisfraz;
    stSucursal nuevaSucursal;

    if(archivo)
    {
        while(fread(&nuevoRegistro, sizeof(registroArchivo), 1, archivo) > 0)
        {

            strcpy(nuevoDisfraz.nombreDisfraz, nuevoRegistro.nombreDisfraz);
            strcpy(nuevoDisfraz.generoDisfraz, nuevoRegistro.generoDisfraz);
            nuevoDisfraz.stockDisfraz = nuevoRegistro.stockDisfraz;


            nuevaSucursal.idSucursal = nuevoRegistro.idSucursal;
            strcpy(nuevaSucursal.nombreSucursal, nuevoRegistro.nombreSucursal);

            lda = alta(lda, nuevoDisfraz, nuevaSucursal);
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo en NULL");
    }
    return lda;
}



//1.2 alta
nodoCelda* alta(nodoCelda* lda, stDisfraz nuevoDisfraz, stSucursal nuevaSucursal)
{
    nodoCelda* rta = buscarNodoCelda(lda, nuevaSucursal);   //Chequea que no se repita la sucursal (campo por el que ordene) a la hora de agregar a la lista de arboles

    if(rta == NULL) //si no se repite
    {
        nodoCelda* nuevaCelda = crearNodoCeldas(nuevaSucursal); //crea nodo celda
        lda = agregarAlPpioCeldas(lda, nuevaCelda); //agrega al ppcio
        rta = lda;  //asigna cambios al retorno
    }
    rta->arbol = insertar(rta->arbol, nuevoDisfraz);    //inserta nodo arbol en lista de arboles (lda)

    return lda;
}


//1.3
nodoCelda* buscarNodoCelda(nodoCelda* lda, stSucursal nuevaSucursal)
{
    nodoCelda* rta = NULL;  //default
    nodoCelda* seg = lda;   //proteccion
    int flag = 0;
    int i = 0;

    while(seg && flag == 0)
    {
        if(strcmp(seg->dato.nombreSucursal, nuevaSucursal.nombreSucursal) == 0 && seg->dato.idSucursal == nuevaSucursal.idSucursal)
        {
            rta = seg;
            flag = 1;
        }
        seg = seg->siguiente;
    }
    return rta;
}


//1.4
nodoCelda* crearNodoCeldas(stSucursal sucursal)
{
    nodoCelda* aux = (nodoCelda*) malloc(sizeof(nodoCelda));
    aux->dato = sucursal;
    aux->arbol = inicArbol();
    aux->siguiente = NULL;

    return aux;
}

//1.5
nodoCelda* agregarAlPpioCeldas(nodoCelda* lista, nodoCelda* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo-> siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}


//1.6
nodoArbol* insertar(nodoArbol* arbol, stDisfraz dato)
{
    if(arbol == NULL)
    {
        arbol = crearNodoArbol(dato);
    }
    else
    {
        if((dato.nombreDisfraz, arbol->dato.nombreDisfraz) > 0)       //insertar alfabeticamnete
        {
            arbol-> der = insertar(arbol-> der, dato);
        }
        else
        {
            arbol-> izq = insertar(arbol-> izq, dato);
        }
    }
    return arbol;
}



//1.4.1
nodoArbol* inicArbol()
{
    return NULL;
}

//1.6.1
nodoArbol* crearNodoArbol(stDisfraz dato)
{
    nodoArbol* aux = malloc(sizeof(nodoArbol));

    aux-> dato = dato;
    aux-> izq = NULL;
    aux-> der = NULL;

    return aux;
}

//del main
nodoCelda* inicListaCeldas()
{
    return NULL;
}
