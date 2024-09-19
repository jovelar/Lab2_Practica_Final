#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombreCanal[40];
    char rubro[30];
    int cantSuscriptores;
    int cantVistasSemestre;
}stYoutuber;

typedef struct
{
    char rubro[30];
}stRubro;

typedef struct
{
    int id;
    char nombreCanal[40];
    int cantSuscriptores;
    int cantVistasSemestre;
}stYoutubers;

typedef struct
{
    stYoutubers youtubers;
    struct nodoArbol *izq;
    struct nodoArbol *der;
}nodoArbol;

typedef struct
{
    stRubro rubro;
    nodoArbol *arbol;
}celdaRubro;

typedef struct
{
    stYoutuber youtuber;
    struct nodo2 *ante;
    struct nodo2 *sig;
}nodo2;

//Punto 1
//{
nodoArbol *inicArbol();
nodoArbol *crearNodoArbol(int id, char nombreCanal[40],int cantSuscriptores,int cantVistasSemestre);
nodoArbol *insertarOrdRec(nodoArbol *arbol,nodoArbol *nuevo);

celdaRubro crearCeldaRubro(char rubro[40]);
int buscarRubro(celdaRubro arreglo[],char nombreRubro[40],int validos);

void pasarAADA(celdaRubro arreglo[],char nombreArchivo[40],int *validos);
void punto1(char nombreArchivo[40], celdaRubro arreglo[], int *validos);
//}

//Punto 2
//{
void mostrarYT(stYoutubers p);
void mostrarArbolYT(nodoArbol *arbol);
void mostrarRubro(stRubro p);
void mostrarArreglo(celdaRubro arreglo[],int validos);
void punto2(celdaRubro arreglo[],int validos);
//}

//Punto 3
//{
int sumaVistas(nodoArbol *arbol,int sumatoria);
stRubro rubroMasPopular(celdaRubro arreglo[], int validos);
void punto3(celdaRubro arreglo[], int validos);
//}

//Punto 4
//{
int sumaSi(nodoArbol *arbol, int sumatoria,int *cumple, int base);
int promedio(celdaRubro arreglo[], int validos,int base);
void punto4(celdaRubro arreglo[], int validos);
//}

//Punto 5
//{
nodo2 *inicNodo2();
nodo2 *crearNodo2(int id, char nombreCanal[40],char rubro[40], int subs, int visSem);
nodo2 *insertarOrdNodo2(nodo2 *lista, nodo2 *nuevo);
nodo2 *pasarAListaN2(celdaRubro arreglo[], int validos);
void pasarAANodo2(nodoArbol *arbol,nodo2 **lista,char rubro[40]);
nodo2 *mostrarNodo2(nodo2 *lista);
void punto5(celdaRubro arreglo[], int validos, nodo2 **lista);
//}

int main()
{
    celdaRubro arreglo[500];
    int validos=0;
    char nombreArchivo[]="archivoYoutubers.bin";
    nodo2 *lista=inicNodo2();
    punto1(nombreArchivo,arreglo,&validos);
    punto2(arreglo,validos);
    punto3(arreglo,validos);
    punto4(arreglo,validos);
    nodo2 *listaDoble=inicNodo2();
    punto5(arreglo,validos,&listaDoble);
    return 0;
}

//Punto 1
//{
nodoArbol *inicArbol()
{
    return NULL;
}
nodoArbol *crearNodoArbol(int id, char nombreCanal[40],int cantSuscriptores,int cantVistasSemestre)
{
    nodoArbol *nuevo=(nodoArbol*)malloc(sizeof(nodoArbol));
    stYoutubers nuevoYT;
    strcpy(nuevoYT.nombreCanal,nombreCanal);
    nuevoYT.cantSuscriptores=cantSuscriptores;
    nuevoYT.cantVistasSemestre=cantVistasSemestre;
    nuevo->youtubers=nuevoYT;
    nuevo->der=NULL;
    nuevo->izq=NULL;

    return nuevo;
}
nodoArbol *insertarOrdRec(nodoArbol *arbol,nodoArbol *nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(strcmpi(arbol->youtubers.nombreCanal,nuevo->youtubers.nombreCanal)>0)
        {
            arbol->der=insertarOrdRec(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertarOrdRec(arbol->izq,nuevo);
        }
    }
    return arbol;
}

celdaRubro crearCeldaRubro(char rubro[40])
{
    celdaRubro nuevo;
    stRubro nuevoRubro;
    strcpy(nuevoRubro.rubro,rubro);
    nuevo.rubro=nuevoRubro;
    nuevo.arbol=NULL;

    return nuevo;
}

int buscarRubro(celdaRubro arreglo[],char nombreRubro[40],int validos)
{
    int posicion=-1;
    int contador=0;
    while(contador<validos && posicion==-1)
    {
        if(strcmpi(arreglo[contador].rubro.rubro,nombreRubro)==0)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

void pasarAADA(celdaRubro arreglo[],char nombreArchivo[40],int *validos)
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stYoutuber buffer;
        while(fread(&buffer,sizeof(stYoutuber),1,archivo)>0)
        {
            nodoArbol *nuevo=crearNodoArbol(buffer.id,buffer.nombreCanal,buffer.cantSuscriptores,buffer.cantVistasSemestre);
            int posRubro=buscarRubro(arreglo,buffer.rubro,*validos);
            if(posRubro==-1)
            {
                celdaRubro nuevoRubro=crearCeldaRubro(buffer.rubro);
                arreglo[*validos]=nuevoRubro;
                posRubro=*validos;
                (*validos)++;
            }
            arreglo[posRubro].arbol=insertarOrdRec(arreglo[posRubro].arbol,nuevo);
        }
        fclose(archivo);
    }
}

void punto1(char nombreArchivo[40], celdaRubro arreglo[], int *validos)
{
    pasarAADA(arreglo,nombreArchivo,validos);
}
//}

//Punto 2
//{
void mostrarYT(stYoutubers p)
{
    printf("\n --------------------------------- YOUTUBER  -------------------------------------\n");
     printf("Id del Youtuber..............................................................: %d ",p.id);
     printf("\nNombre del Canal.......................................................: %s ",p.nombreCanal);
     printf("\nCantidad de Suscriptores en miles.............................: %d ",p.cantSuscriptores);
     printf("\nCantidad  de  vistas  del  semestre  en  miles……….:  %d  \n",p.cantVistasSemestre);
}

void mostrarArbolYT(nodoArbol *arbol)
{
    if(arbol)
    {
        mostrarArbolYT(arbol->izq);
        mostrarYT(arbol->youtubers);
        mostrarArbolYT(arbol->der);
    }
}

void mostrarRubro(stRubro p)
{
    printf("\n ***************************** RUBRO  ******************************* \n");
    printf("\n ………………………..........%s…………………………. ",p.rubro);
    printf("\n ************************************************************************ \n");
}
void mostrarArreglo(celdaRubro arreglo[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarRubro(arreglo[x].rubro);
        mostrarArbolYT(arreglo[x].arbol);
    }
}

void punto2(celdaRubro arreglo[],int validos)
{
    mostrarArreglo(arreglo,validos);
}
//}

//Punto 3
//{
int sumaVistas(nodoArbol *arbol,int sumatoria)
{
    if(arbol)
    {
        sumatoria=sumaVistas(arbol->izq,sumatoria);
        sumatoria=+ arbol->youtubers.cantVistasSemestre;
        sumatoria=sumaVistas(arbol->der,sumatoria);
    }
    return sumatoria;
}
stRubro rubroMasPopular(celdaRubro arreglo[], int validos)
{
    int maximo=0;
    int contador=0;
    stRubro rubroPopular;

    for(int x=0;x<validos;x++)
    {
        contador=sumaVistas(arreglo[x].arbol,0);
        if(contador>maximo)
        {
            maximo=contador;
            rubroPopular=arreglo[x].rubro;
        }
    }
    return rubroPopular;
}
void punto3(celdaRubro arreglo[], int validos)
{
    stRubro popular=rubroMasPopular(arreglo,validos);
    printf("El rubro mas popular es %s \n",popular.rubro);
}
//}

//Punto 4
//{

/*
int sumaSi(nodoArbol *arbol, int sumatoria,int cumple, int base)
{
    if(arbol)
    {
        sumatoria=sumaSi(arbol->izq,sumatoria,cumple,base);
        if(arbol->youtubers.cantSuscriptores>base)
        {

            sumatoria+= arbol->youtubers.cantSuscriptores;
            cumple++;
            printf("SUMANDO! sumatoria: %i cumple: %i \n",sumatoria,cumple);
        }
        sumatoria=sumaSi(arbol->der,sumatoria,cumple,base);
    }
    if(sumatoria>0 && cumple>0 &&!arbol)
    {
        sumatoria=sumatoria/cumple;
    }
    return sumatoria;
}


*/

int sumaSi(nodoArbol *arbol, int sumatoria,int *cumple, int base)
{
    if(arbol)
    {
        sumatoria=sumaSi(arbol->izq,sumatoria,cumple,base);
        if(arbol->youtubers.cantVistasSemestre>=base)
        {
            sumatoria+= arbol->youtubers.cantVistasSemestre;
            (*cumple)++;
        }
        sumatoria=sumaSi(arbol->der,sumatoria,cumple,base);
    }
    return sumatoria;
}

int promedio(celdaRubro arreglo[], int validos,int base)
{
    int recuento=0;
    int sumatoria=0;
    int cumple=0; //Suma los que cumplen con la condicion
    for(int x=0;x<validos;x++)
    {
        sumatoria=sumaSi(arreglo[x].arbol,sumatoria,&cumple,base);
        recuento+= sumatoria;
        sumatoria=0;
    }
    return recuento/cumple;
}

void punto4(celdaRubro arreglo[], int validos)
{
    int base;
    printf("Ingrese el valor minimo de visitas: ");
    scanf("%d",&base);
    int prom=promedio(arreglo,validos,base);
    printf("El promedio es de %i \n",prom);
}
//}

//Punto 5
//{
nodo2 *inicNodo2()
{
    return NULL;
}

nodo2 *crearNodo2(int id, char nombreCanal[40],char rubro[40], int subs, int visSem)
{
    stYoutuber nuevoYT;
    nuevoYT.id=id;
    strcpy(nuevoYT.nombreCanal,nombreCanal);
    strcpy(nuevoYT.rubro,rubro);
    nuevoYT.cantSuscriptores=subs;
    nuevoYT.cantVistasSemestre=visSem;

    nodo2 *nuevoNodo2=(nodo2*)malloc(sizeof(nodo2));
    nuevoNodo2->youtuber=nuevoYT;
    nuevoNodo2->ante=NULL;
    nuevoNodo2->sig=NULL;

    return nuevoNodo2;
}

nodo2 *insertarOrdNodo2(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->youtuber.nombreCanal,nuevo->youtuber.nombreCanal)>=0)
        {
            nuevo->sig=lista;
            lista->ante=nuevo;
            lista=nuevo;
        }
        else
        {
            nodo2 *ante=NULL;
            nodo2 *iterador=lista;
            while(iterador && strcmpi(iterador->youtuber.nombreCanal,nuevo->youtuber.nombreCanal)<=0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->ante=ante;
            nuevo->sig=iterador;
            if(iterador)
            {
                iterador->ante=nuevo;
            }
        }
    }
    return lista;
}

nodo2 *pasarAListaN2(celdaRubro arreglo[], int validos)
{
    nodo2 *lista=inicNodo2();
    for(int x=0;x<validos;x++)
    {
        pasarAANodo2(arreglo[x].arbol,&lista,arreglo[x].rubro.rubro);
    }
    return lista;
}
void pasarAANodo2(nodoArbol *arbol,nodo2 **lista,char rubro[40])
{
    if(arbol)
    {
        pasarAANodo2(arbol->izq,lista,rubro);
        nodo2 *nuevo=crearNodo2(arbol->youtubers.id,arbol->youtubers.nombreCanal,rubro,arbol->youtubers.cantSuscriptores,arbol->youtubers.cantVistasSemestre);
        *lista=insertarOrdNodo2(*lista,nuevo);
        pasarAANodo2(arbol->der,lista,rubro);
    }
}
nodo2 *mostrarNodo2(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            printf("ID: %-2i NOMBRE: %-20s GENERO: %-15s SUBS: %-7i VIS.SEM: %i \n",iterador->youtuber.id,
                   iterador->youtuber.nombreCanal,iterador->youtuber.rubro,
                   iterador->youtuber.cantSuscriptores,
                   iterador->youtuber.cantVistasSemestre);
            iterador=iterador->sig;
        }
    }
}

void punto5(celdaRubro arreglo[], int validos, nodo2 **lista)
{
    *lista=pasarAListaN2(arreglo,validos);
    mostrarNodo2(*lista);
}
//}
