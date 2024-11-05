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
    char puestoJugador[30]; //Delantero-Medio-Defensor-Arquero
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
    int idEquipo; //Se debe generar
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
nodoListaJugador *crearNodo(int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30]);
nodoListaJugador *insertarOrdRec(nodoListaJugador *lista,nodoListaJugador *nuevo);
//}

//Punto 2
//{
int buscarEquipo(arregloEquipo arreglo[],char nombreEquipo[30],int validos);
void crearEquipo(arregloEquipo arreglo[], int *validos,char nombre[30],int puntos);
void altaJugador(arregloEquipo arreglo[],int *validos);
//}

//Punto 3
//{
int pasarAADL(arregloEquipo arreglo[],char nombreArchivo[50]);
void punto3(arregloEquipo arreglo[],char nombreArchivo[50],int *validos);
//}

//Punto 4
//{
void mostrarADL(arregloEquipo arreglo[],int validos);
void mostrarEquipo(stEquipo equipo);
void mostrarJugador(stJugador jugador);
void mostrarJugadores(nodoListaJugador *lista);
void punto4(arregloEquipo arreglo[],int validos);
//}

// Punto 5
//{
int nroJugador(arregloEquipo arreglo[], int validos,char equipo[30],char apellido[30],char nombre[30]);
void punto5(arregloEquipo arreglo[], int validos);
//}
int main()
{
    arregloEquipo arreglo[500];
    int validos=0;
    char archivo[50]="registroJugador.dat";
    punto3(arreglo,archivo,&validos);
    punto4(arreglo,validos);
    punto5(arreglo,validos);
    return 0;
}


//Punto 1
//{
nodoListaJugador *inicLista()
{
    return NULL;
}
nodoListaJugador *crearNodo(int nroJugador,char nombre[30],char apellido[30],int clase,char puesto[30])
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
nodoListaJugador *insertarOrdRec(nodoListaJugador *lista,nodoListaJugador *nuevo)
{
    if(!lista)
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
            lista->sig=insertarOrdRec(lista->sig,nuevo);
        }
    }
    return lista;
}
//}

//Punto 2
//{
int buscarEquipo(arregloEquipo arreglo[],char nombreEquipo[30],int validos)
{
    int posicion=-1;
    int contador=0;
    while(posicion==-1 && contador<validos)
    {
        if(strcmpi(arreglo[contador].e.nombreEquipo,nombreEquipo)==0)
        {
            posicion=contador;
        }
        contador++;
    }
    return posicion;
}

void crearEquipo(arregloEquipo arreglo[], int *validos,char nombre[30],int puntos)
{
    arregloEquipo nuevo;
    strcpy(nuevo.e.nombreEquipo,nombre);
    nuevo.e.idEquipo=*validos;
    nuevo.e.puntosGanados,puntos;
    nuevo.listaJugadores=NULL;
    arreglo[*validos]=nuevo;
    (*validos)++;
    return nuevo;
}

void altaJugador(arregloEquipo arreglo[],int *validos)
{
    char equipo[30];
    char nombre[30];
    char apellido[30];
    char posicion[30];
    int clase;
    int nro;

    printf("Ingrese el Apellido: ");
    gets(apellido);
    printf("Ingrese el nombre: ");
    gets(nombre);
    printf("Ingrese la posicion: ");
    gets(posicion);
    printf("Ingrese el anio de nacimiento: ");
    scanf("%d",&clase);

    int posEquipo=buscarEquipo(arreglo,equipo,*validos);

    stJugador *nuevoJugador=crearNodo(nro,nombre,apellido,clase,posicion);

    if(posEquipo==-1)
    {
        crearEquipo(arreglo,*validos,nombre,0);
        posEquipo=*validos;
    }
    arreglo[posEquipo].listaJugadores=insertarOrdRec(arreglo[posEquipo].listaJugadores,nuevoJugador);
}
//}

//Punto 3
//{

int pasarAADL(arregloEquipo arreglo[],char nombreArchivo[50])
{
    int validos=0;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroJugador buffer;
        while(fread(&buffer,sizeof(stRegistroJugador),1,archivo)>0)
        {
            nodoListaJugador *nuevoJugador=crearNodo(buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador);
            int posicion=buscarEquipo(arreglo,buffer.nombreEquipo,validos);
            if(posicion==-1)
            {
                crearEquipo(arreglo,&validos,buffer.nombreEquipo,buffer.puntosGanados);
                posicion=validos;
            }
            arreglo[posicion].listaJugadores=insertarOrdRec(arreglo[posicion].listaJugadores,nuevoJugador);
        }
        fclose(archivo);
    }
    return validos;
}
void punto3(arregloEquipo arreglo[],char nombreArchivo[50],int *validos)
{
    *validos=pasarAADL(arreglo,nombreArchivo);
}

//}

//Punto 4
//{
void mostrarADL(arregloEquipo arreglo[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarEquipo(arreglo[x].e);
        mostrarJugadores(arreglo[x].listaJugadores);
    }
}

void mostrarEquipo(stEquipo equipo)
{
    printf("\n\n******* EQUIPO: %s PUNTOS: %i ******* \n",equipo.nombreEquipo,equipo.puntosGanados);
}

void mostrarJugador(stJugador jugador)
{
    printf("Apellido: %-10s Nombre: %-10s Puesto: %-10s Nro: %2i Clase :i \n",jugador.apellidoJugador,jugador.nombreJugador,jugador.puestoJugador,jugador.nroJugador,jugador.clase);
}
void mostrarJugadores(nodoListaJugador *lista)
{
    if(lista)
    {
        nodoListaJugador *iterador=lista;
        while(iterador)
        {
            mostrarJugador(iterador->j);
            iterador=iterador->sig;
        }
    }
}
void punto4(arregloEquipo arreglo[],int validos)
{
    mostrarADL(arreglo,validos);
}
//}

// Punto 5
//{
int nroJugador(arregloEquipo arreglo[], int validos,char equipo[30],char apellido[30],char nombre[30])
{
    int numero=0;
    int posEquipo=buscarEquipo(arreglo,equipo,validos);
    if(posEquipo!=-1)
    {
        nodoListaJugador *iterador=arreglo[posEquipo].listaJugadores;
        while(iterador && numero==0)
        {
            if(strcmpi(iterador->j.apellidoJugador,apellido)==0)
            {
                numero=iterador->j.nroJugador;
            }
            iterador=iterador->sig;
        }
    }
    return numero;
}
void punto5(arregloEquipo arreglo[], int validos)
{
    char equipo[50];
    char nombre[50];
    char apellido[50];

    printf("Ingrese un nombre: ");
    gets(nombre);
    printf("Ingrese el apellido: ");
    gets(apellido);
    printf("Ingrese el equipo: ");
    gets(equipo);

    int numero=nroJugador(arreglo,validos,equipo,apellido,nombre);
    if(numero==0)
    {
        printf("No encontrado! \n");
    }
    else
    {
        printf("NUMERO: %i \n",numero);
    }
}
//}
