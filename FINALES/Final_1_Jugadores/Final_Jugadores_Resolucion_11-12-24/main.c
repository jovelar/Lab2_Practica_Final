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
arregloEquipo nuevoEquipo(int id, char nombre[30], int puntos);
void altaJugador(arregloEquipo equipos[],char nombreEquipo[30],int *validos,int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30]);
void alta(arregloEquipo arreglo[],int *validos);
//}

//Punto 3
//{
int pasarAADL(arregloEquipo arreglo[],char nombreArchivo[30],int validos);
void punto3(arregloEquipo arreglo[],char nombreArchivo[30],int *validos);
//}

//Punto 4
//{
void mostrarJugador(stJugador jugador);
void mostrarLista(nodoListaJugador *lista);
void mostrarEquipo(stEquipo equipo);
void mostrarTodo(arregloEquipo arreglo[],int validos);
void punto4(arregloEquipo arreglo[],int validos);
//}

//Punto 5
//{
int buscarJugador(char apellido[30],char nombre[30],char equipo[30],arregloEquipo arreglo[],int validos);
void punto5(arregloEquipo arreglo[],int validos);
//}


int main()
{
    arregloEquipo equipo[200];
    int validos=0;
    char nombreArchivo[]="registroJugador.dat";

    punto3(equipo,nombreArchivo,&validos);
    punto4(equipo,validos);
    punto5(equipo,validos);
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
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        printf("\n %s %s \n",lista->j.apellidoJugador,nuevo->j.apellidoJugador);
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

arregloEquipo nuevoEquipo(int id, char nombre[30], int puntos)
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
int pasarAADL(arregloEquipo arreglo[],char nombreArchivo[30],int validos)
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroJugador buffer;
        while(fread(&buffer,sizeof(stRegistroJugador),1,archivo)>0)
        {
            nodoListaJugador *nuevo=nuevoJugador(buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador);
            int posicion=buscarEquipo(arreglo,validos,buffer.nombreEquipo);
            if(posicion==-1)
            {
                arregloEquipo nuevoEq=nuevoEquipo(buffer.idRegistro,buffer.nombreEquipo,0);
                arreglo[validos]=nuevoEq;
                posicion=validos;
                validos++;
            }
            arreglo[posicion].listaJugadores=insertarJugRec(arreglo[posicion].listaJugadores,nuevo);
        }
        fclose(archivo);
    }
    return validos;
}
void punto3(arregloEquipo arreglo[],char nombreArchivo[30],int *validos)
{
    *validos=pasarAADL(arreglo,nombreArchivo,*validos);
}
//}

//Punto 4
//{
void mostrarJugador(stJugador jugador)
{
    printf("Apellido: %s, Nombre: %s, Nro: %i, Clase: %i, Puesto: %s \n",jugador.apellidoJugador,jugador.nombreJugador,jugador.nroJugador,jugador.clase,jugador.puestoJugador);
}
void mostrarLista(nodoListaJugador *lista)
{
    if(lista)
    {
        nodoListaJugador *aux=lista;
        while(aux)
        {
            mostrarJugador(aux->j);
            aux=aux->sig;
        }
    }
    else
    {
        printf("Lista jugadores vacia!");
    }
}

void mostrarEquipo(stEquipo equipo)
{
    printf("******* ID: %i EQUIPO: %s PUNTOS: %i ******* \n",equipo.idEquipo,equipo.nombreEquipo,equipo.puntosGanados);
}

void mostrarTodo(arregloEquipo arreglo[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarEquipo(arreglo[x].e);
        mostrarLista(arreglo[x].listaJugadores);
    }
}
void punto4(arregloEquipo arreglo[],int validos)
{
    mostrarTodo(arreglo,validos);
}
//}

//Punto 5
//{
int buscarJugador(char apellido[30],char nombre[30],char equipo[30],arregloEquipo arreglo[],int validos)
{
    int numero=-1;
    int posEquipo=buscarEquipo(arreglo,validos,equipo);
    if(posEquipo!=-1)
    {
        nodoListaJugador *aux=arreglo[posEquipo].listaJugadores;

        while(aux && numero==-1)
        {
            if(strcmpi(aux->j.apellidoJugador,apellido)==0 && strcmpi(aux->j.nombreJugador,nombre)==0)
            {
                numero=aux->j.nroJugador;
            }
            aux=aux->sig;
        }
    }
    return numero;
}
void punto5(arregloEquipo arreglo[],int validos)
{
    char equipo[30];
    char nombre[30];
    char apellido[30];
    int numero;

    printf("Ingrese el equipo: ");
    gets(equipo);
    printf("ingrese el apellido: ");
    gets(apellido);
    printf("Ingrese el nombre: ");
    gets(nombre);

    numero=buscarJugador(apellido,nombre,equipo,arreglo,validos);

    printf("\n\n\t Numero: %i ",numero);
}
//}
