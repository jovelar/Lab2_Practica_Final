#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombreCanal[40];
    char rubro[30];
    int cantSubscriptores;
    int cantVisitasSemestre;
}stYoutuber;

typedef struct
{
    char rubro[30];
    struct stYoutubers *youtubers;
}stRubro;

typedef struct
{
    int id;
    char nombreCanal[40];
    int cantSubscriptores;
    int cantVisitasSemestre;
    struct stYoutubers *izquierda;
    struct stYoutubers *derecha;
}stYoutubers;

typedef struct
{
    stYoutuber youtuber;
    struct nodo2 *anterior;
    struct nodo2 *siguiente;
}nodo2;

//Punto 1

void pasarAReg(char nombreArchivoEntrada[40],char nombreArchivoSalida[40]);

stRubro crearRubro(char rubro[30]);
int buscarRubro(stRubro arregloRubro[],int validos,char rubro[40]);

void inicYoutubers(stYoutubers *arbol);
stYoutubers *crearYoutuber(int id,char nombreCanal[40],int canSubscriptores,int cantVisitas);
stYoutubers *agregarOrdenado(stYoutubers *arbol,stYoutubers *nuevo);

void pasarADA(stRubro rubo[],char nombreArchivo[40],int *validos);

//Punto 2

void mostrarTodo(stRubro rubros[],int validos);
void mostrarRubro(stRubro rubros);
void mostrarYoutubers(stYoutubers p);
void mostrarYoutubersRec(stYoutubers *arbol);

//Punto 3

int sumatoriaVisitasRec(stYoutubers *arbol);
int posRubroMasVisitado(stRubro rubros[], int validos);
void rubroMasPopular(stRubro rubros[], int validos);

//Punto 4

int sumaSiLimiteRec(stYoutubers *arbol,int limite, int *yt);
void promedioLimite(stRubro rubros[], int validos, int limite);

//Punto 5

nodo2 *iniciNodo2(nodo2 *nodo);
nodo2 *crearNuevoNodo2(int id,char nombreCanal[25],char rubro[25],int cantVisitas,int cantSuscriptores);
nodo2 *agregarOrdenadoNodo2(nodo2 *lista, nodo2 *nuevo);
void mostrarNodo2(nodo2 *nodo);
void mostrarListaNodo2(nodo2 *lista);

void pasarRec(stYoutubers *arbol,nodo2 **lista,char rubroCanal[25]);
nodo2 *pasarAListaN2(stRubro rubros[], int validos, nodo2 *lista);

//PRUEBA
nodo2 *agregarAlFinal(nodo2 *lista, nodo2 *nuevo);

void ejercicio1(stRubro rubro[],int *validos,char nombreArchivo[40]);
void ejercicio2(stRubro rubros[], int validos);
void ejercicio3(stRubro rubros[], int validos);
void ejercicio4(stRubro rubros[],int validos);
void ejercicio5(stRubro rubros[], int validos, nodo2 **lista);


int main()
{
    char nombreArchivo[40]="archivoYoutubers.bin";
    stRubro rubros[200];
    int validos=0;

    nodo2 *listaDoble=iniciNodo2(listaDoble);
    //pasarAReg(nombreArchivo,"registro_youtubers.csv");
    ejercicio1(rubros,&validos,nombreArchivo);
    ejercicio2(rubros,validos);
    ejercicio3(rubros,validos);
    ejercicio4(rubros,validos);

    ejercicio5(rubros,validos,&listaDoble);
    system("pause");
    mostrarListaNodo2(listaDoble);

    return 0;
}

//Punto 1
stRubro crearRubro(char rubro[30])
{
    stRubro nuevo;
    strcpy(nuevo.rubro,rubro);
    nuevo.youtubers=NULL;
    return nuevo;
}

void pasarAReg(char nombreArchivoEntrada[40],char nombreArchivoSalida[40])
{
    FILE *archivoFuente=fopen(nombreArchivoEntrada,"rb");
    if(archivoFuente)
    {
        FILE *archivoSalida=fopen(nombreArchivoSalida,"wb");
        stYoutuber buffer;
        fprintf(archivoSalida,"ID;RUBRO;CANAL;SUBS;VISITAS\n");
        while(fread(&buffer,sizeof(stYoutuber),1,archivoFuente)>0)
        {
            fprintf(archivoSalida,"%i;%s;%s;%i;%i\n",buffer.id,buffer.rubro,buffer.nombreCanal,buffer.cantSubscriptores,buffer.cantVisitasSemestre);
        }
        fclose(archivoSalida);
        fclose(archivoFuente);
    }
}

int buscarRubro(stRubro arregloRubro[],int validos,char rubro[40])
{
    int posicion=-1;
    int contador=0;

    while(contador<validos  && posicion==-1)
    {
        if(strcmpi(arregloRubro[contador].rubro,rubro)==0)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

void inicYoutubers(stYoutubers *arbol)
{
    arbol->izquierda=NULL;
    arbol->derecha=NULL;
}

stYoutubers *crearYoutuber(int id,char nombreCanal[40],int cantSubscriptores,int cantVisitas)
{
    stYoutubers *nuevoYT=(stYoutubers*)malloc(sizeof(stYoutubers));
    nuevoYT->id=id;
    strcpy(nuevoYT->nombreCanal,nombreCanal);
    nuevoYT->cantSubscriptores=cantSubscriptores;
    nuevoYT->cantVisitasSemestre=cantVisitas;
    nuevoYT->izquierda=NULL;
    nuevoYT->derecha=NULL;
    return nuevoYT;
}

stYoutubers *agregarOrdenado(stYoutubers *arbol,stYoutubers *nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(strcmpi(arbol->nombreCanal,nuevo->nombreCanal)<0)
        {
            arbol->derecha=agregarOrdenado(arbol->derecha,nuevo);
        }
        else
        {
            arbol->izquierda=agregarOrdenado(arbol->izquierda,nuevo);
        }
    }
    return arbol;
}

void pasarADA(stRubro rubro[],char nombreArchivo[40],int *validos)
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stYoutuber buffer;
        while(fread(&buffer,sizeof(stYoutuber),1,archivo)>0)
        {
            stYoutubers *nuevoYoutuber=crearYoutuber(buffer.id,buffer.nombreCanal,buffer.cantSubscriptores,buffer.cantVisitasSemestre);
            int posicion=buscarRubro(rubro,*validos,buffer.rubro);
            if(posicion==-1)
            {
                stRubro nuevoRubro=crearRubro(buffer.rubro);
                rubro[*validos]=nuevoRubro;
                posicion=*validos;
                (*validos)++;
            }
            rubro[posicion].youtubers=agregarOrdenado(rubro[posicion].youtubers,nuevoYoutuber);
        }
        fclose(archivo);
    }
}

void ejercicio1(stRubro rubro[],int *validos,char nombreArchivo[40])
{
    pasarADA(rubro,nombreArchivo,validos);
}

//Punto 2

void mostrarTodo(stRubro rubros[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarRubro(rubros[x]);
        mostrarYoutubersRec(rubros[x].youtubers);
    }
}
void mostrarRubro(stRubro p)
{
    printf("\n ***************************** RUBRO  ******************************* \n");
    printf("\n ................%s............. ",p.rubro);
    printf("\n ************************************************************************ \n");
}

void mostrarYoutubers(stYoutubers p)
{
        printf("\n --------------------------------- YOUTUBER  -------------------------------------\n");
        printf("Id del Youtuber..............................................................: %d ",p.id);
        printf("\nNombre del Canal.......................................................: %s ",p.nombreCanal);
        printf("\nCantidad de Suscriptores en miles.............................: %d ",p.cantSubscriptores);
        printf("\nCantidad  de  vistas  del  semestre  en  miles……….:  %d  \n",p.cantVisitasSemestre);
}

void mostrarYoutubersRec(stYoutubers *arbol)
{
    if(arbol)
    {
        mostrarYoutubersRec(arbol->izquierda);
        mostrarYoutubers(*arbol);
        mostrarYoutubersRec(arbol->derecha);
    }
}

void ejercicio2(stRubro rubros[], int validos)
{
    mostrarTodo(rubros,validos);
}

int sumatoriaVisitasRec(stYoutubers *arbol)
{
    int sumatoria=0;
    if(arbol)
    {
        sumatoria+=arbol->cantVisitasSemestre;
        sumatoria+=sumatoriaVisitasRec(arbol->izquierda);
        sumatoria+=sumatoriaVisitasRec(arbol->derecha);
    }
    return sumatoria;
}

int posRubroMasVisitado(stRubro rubros[], int validos)
{
    int posicionMayor=0;
    int maximo=0;
    int contador=0;

    for(int x=0;x<validos;x++)
    {
            contador=sumatoriaVisitasRec(rubros[x].youtubers);
            //printf("\nRubro: %s | sumatoria: %i",rubros[x].rubro,contador);
            if(contador>maximo)
            {
                posicionMayor=x;
                maximo=contador;
            }
            contador=0;
    }

    return posicionMayor;
}

void rubroMasPopular(stRubro rubros[], int validos)
{
    int posMasPopular=posRubroMasVisitado(rubros,validos);
    printf("\nEl rubro mas popular es %s ",rubros[posMasPopular].rubro);
}

void ejercicio3(stRubro rubros[], int validos)
{
    rubroMasPopular(rubros,validos);
}

//Punto 4

int sumaSiLimiteRec(stYoutubers *arbol,int limite, int *yt)
{
    int sumatoria=0;
    if(arbol)
    {
        if(arbol->cantVisitasSemestre>=limite)
        {
            sumatoria+=arbol->cantVisitasSemestre;
            (*yt)++;
        }
        sumatoria+=sumaSiLimiteRec(arbol->izquierda,limite,yt);
        sumatoria+=sumaSiLimiteRec(arbol->derecha,limite,yt);
    }

    return sumatoria;
}

void promedioLimite(stRubro rubros[], int validos, int limite)
{
    int sumatoria=0;
    int youtubers=0;
    for(int x=0;x<validos;x++)
    {
        sumatoria+=sumaSiLimiteRec(rubros[x].youtubers,limite,&youtubers);
        printf("\n%i",sumatoria);
        printf("\n yt %i",youtubers);
    }
    printf("\nEl promedio de %i youtubers con un minimo de %i visitas es de %i",youtubers,limite,sumatoria/youtubers);

}
void ejercicio4(stRubro rubros[],int validos)
{
    printf("\nInserte el valor de visitas minimo: ");
    int minimo;
    scanf("%d",&minimo);

    promedioLimite(rubros,validos,minimo);
}

nodo2 *iniciNodo2(nodo2 *nodo)
{
    return NULL;
}

nodo2 *crearNuevoNodo2(int id,char nombreCanal[25],char rubro[25],int cantVisitas,int cantSuscriptores)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));

    nuevo->youtuber.id=id;
    strcpy(nuevo->youtuber.nombreCanal,nombreCanal);
    strcpy(nuevo->youtuber.rubro,rubro);
    nuevo->youtuber.cantVisitasSemestre=cantVisitas;
    nuevo->youtuber.cantSubscriptores=cantSuscriptores;

    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodo2 *agregarOrdenadoNodo2(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->youtuber.rubro,nuevo->youtuber.rubro)>0 && strcmpi(lista->youtuber.nombreCanal,nuevo->youtuber.nombreCanal)>0)
        {
            //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         printf("\n ES EL PRIMERO! comparacion entre %s y %s = %i ",lista->youtuber.rubro,nuevo->youtuber.rubro,strcmpi(lista->youtuber.rubro,nuevo->youtuber.rubro));
            nuevo->siguiente=lista;
            lista->anterior=nuevo;
            lista=nuevo;
        }
        else
        {
            nodo2 *iterador=lista;
            nodo2 *ante=lista;

            while(iterador && strcmpi(iterador->youtuber.rubro,nuevo->youtuber.rubro)<0 && strcmpi(iterador->youtuber.nombreCanal,nuevo->youtuber.nombreCanal)>0)
            {
                printf("\nComparando con %s - %s | %s - %s",iterador->youtuber.rubro,iterador->youtuber.nombreCanal,nuevo->youtuber.rubro,nuevo->youtuber.nombreCanal);
                ante=iterador;
                iterador=iterador->siguiente;
            }
            if(!iterador)
            {
                ante->siguiente=nuevo;
                nuevo->anterior=ante;
            }
            else
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

void mostrarNodo2(nodo2 *nodo)
{
    if(nodo)
    {
        printf("\n%2i | %20s | %20s | %6i | %6i ",nodo->youtuber.id,nodo->youtuber.nombreCanal,nodo->youtuber.rubro,nodo->youtuber.cantVisitasSemestre,nodo->youtuber.cantSubscriptores);

    }
}

void mostrarListaNodo2(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            mostrarNodo2(iterador);
            iterador=iterador->siguiente;
        }
    }
    else
    {
        printf("\nLista vacia!");
    }
}

nodo2 *pasarAListaN2(stRubro rubros[], int validos, nodo2 *lista)
{

    for(int x=0;x<validos;x++)
    {
        pasarRec(rubros[x].youtubers,&lista,rubros[x].rubro);
    }
    return lista;
}

void pasarRec(stYoutubers *arbol,nodo2 **lista,char rubroCanal[25])
{
    if(arbol)
    {
        nodo2 *nuevo=crearNuevoNodo2(arbol->id,arbol->nombreCanal,rubroCanal,arbol->cantVisitasSemestre,arbol->cantSubscriptores);
        if(nuevo)
        {
            *lista=agregarOrdenadoNodo2(*lista,nuevo);
            //*lista=agregarAlFinal(*lista,nuevo);
        }
        pasarRec(arbol->izquierda,lista,rubroCanal);
        pasarRec(arbol->derecha,lista,rubroCanal);
    }
}

//PRUEBA

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

void ejercicio5(stRubro rubros[], int validos, nodo2 **lista)
{
    *lista=pasarAListaN2(rubros,validos,*lista);
}
