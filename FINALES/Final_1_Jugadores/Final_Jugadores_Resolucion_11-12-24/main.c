#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idRegistro;
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase;
    char puestoJugador[30];
    char nombreEquipo[30];
    int puntosGanados;
}stRegistroJugador;

typedef struct
{
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase;
    char puestoJugador[30];
}stJugador;

typedef struct
{
    stJugador j;
    struct nodoListaJugador *sig;
}nodoListaJugador;

typedef struct
{
    int idEquipo;
    char nombreEquipo[30];
    int puntosGanados;
}stEquipo;

typedef struct
{
    stEquipo e;
    nodoListaJugador *listaJugadores;
}arregloEquipo;

//Punto 1
//{
nodoListaJugador *inicLista();
nodoListaJugador *nuevoJugador(int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30]);
nodoListaJugador *insertarJugRec(nodoListaJugador *lista, nodoListaJugador *nuevo);
//}

//Punto 2
//{
int buscarEquipo(arregloEquipo equipos[],int validos,char nombreEquipo[30]);
arregloEquipo nuevoEquipo(int id, char nombre, int puntos);
void altaJugador(arregloEquipo equipos[],char nombreEquipo[30],int *validos,int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30]);
void alta(arregloEquipo arreglo[],int *validos);
//}

//Punto 3
//{
int pasarAADL(char nombreArchivo[30]);
void punto3(char nombreArchivo[30],int *validos);
//}
int main()
{
    return 0;
}

//Punto 1
//{
nodoListaJugador *inicLista()
{
    return NULL;
}

nodoListaJugador *nuevoJugador(int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30])
{
    nodoListaJugador *nuevo=(nodoListaJugador*)malloc(sizeof(nodoListaJugador));
    nuevo->j.nroJugador=nroJugador;
    strcpy(nuevo->j.nombreJugador,nombre);
    strcpy(nuevo->j.apellidoJugador,apellido);
    nuevo->j.clase=clase;
    strcpy(nuevo->j.puestoJugador,puesto);
    nuevo->sig=NULL;
    return nuevo;
}
nodoListaJugador *insertarJugRec(nodoListaJugador *lista, nodoListaJugador *nuevo)
{
    if(lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->j.apellidoJugador,nuevo->j.apellidoJugador)>=0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarJugRec(lista->sig,nuevo);
        }
    }
    return lista;
}
//}

//Punto 2
//{
int buscarEquipo(arregloEquipo equipos[],int validos,char nombreEquipo[30])
{
    int posicion=-1;
    int contador=0;
    while(contador<validos && posicion==-1)
    {
        if(strcmpi(equipos[contador].e.nombreEquipo,nombreEquipo)==0)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

arregloEquipo nuevoEquipo(int id, char nombre, int puntos)
{
    arregloEquipo nuevo;
    nuevo.e.idEquipo=id;
    strcpy(nuevo.e.nombreEquipo,nombre);
    nuevo.e.puntosGanados=puntos;
    nuevo.listaJugadores=NULL;
    return nuevo;
}

void altaJugador(arregloEquipo equipos[],char nombreEquipo[30],int *validos,int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30])
{
    nodoListaJugador *nuevo=nuevoJugador(nroJugador,nombre,apellido,clase,puesto);
    int posicion=buscarEquipo(equipos,*validos,nombreEquipo);
    if(posicion==-1)
    {
        arregloEquipo nuevoEq=nuevoEquipo(*validos,nombreEquipo,0);
        posicion=validos;
        equipos[posicion]=nuevoEq;
        (*validos)++;
    }
    equipos[posicion].listaJugadores=insertarJugRec(equipos[posicion].listaJugadores,nuevo);
}

void alta(arregloEquipo arreglo[],int *validos)
{
    char nombre[30];
    char apellido[30];
    char puesto[30];
    int nro;
    int clase;
    char nombreEquipo[30];

    printf("Ingrese el equipo del jugador: ");
    gets(nombreEquipo);
    printf("Ingrese el apellido: ");
    gets(apellido);
    printf("Ingrese el nombre: ");
    gets(apellido);
    printf("Ingrese el puesto: ");
    gets(puesto);
    printf("Ingrese clase: ");
    scanf("%d",&clase);
    printf("Ingrese el nro del jugador: ");
    scanf("%d",&nro);
    altaJugador(arreglo,nombreEquipo,validos,nro,nombre,apellido,clase,puesto);
}
//}

//Punto 3
//{
int pasarAADL(char nombreArchivo[30])
{
    int validos=0;
    FILE *archivo=fopen(archivo,"rb");
    if(archivo)
    {
        stRegistroJugador buffer;
        while(fread(&buffer,sizeof(stRegistroJugador),1,archivo)>0)
        {
            nodoListaJugador *nuevo=nuevoJugador(buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador);
            int posicion=buscarEquipo
        }
        fclose(archivo);
    }
    return validos;
}
void punto3(char nombreArchivo[30],int *validos);
//}
