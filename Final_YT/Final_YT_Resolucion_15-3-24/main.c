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
void mostrarYoutubersRec(stYoutubers *arbol);

void ejercicio1(stRubro rubro[],int *validos,char nombreArchivo[40]);
void ejercicio2(stRubro rubros[], int validos);
void ejercicio3();
void ejercicio4();
void ejercicio5();

int main()
{
    char nombreArchivo[40]="archivoYoutubers.bin";
    stRubro rubros[200];
    int validos=0;

    //pasarAReg(nombreArchivo,"registro_youtubers.csv");
    ejercicio1(rubros,&validos,nombreArchivo);
    ejercicio2(rubros,validos);

    printf("Hello world!\n");
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
void mostrarRubro(stRubro rubros)
{
    printf("\n*************************");
    printf("\n RUBRO %s ",rubros.rubro);
    printf("\n*************************");
}

void mostrarYoutubersRec(stYoutubers *arbol)
{
    if(arbol)
    {
        mostrarYoutubersRec(arbol->izquierda);
        printf("\nID: %i",arbol->id);
        printf("\nCANAL: %s",arbol->nombreCanal);
        printf("\nCant Susbs: %i",arbol->cantSubscriptores);
        printf("\nCant Visitas Sem: %i",arbol->cantVisitasSemestre);
        mostrarYoutubersRec(arbol->derecha);
    }
}

void ejercicio2(stRubro rubros[], int validos)
{
    mostrarTodo(rubros,validos);
}
