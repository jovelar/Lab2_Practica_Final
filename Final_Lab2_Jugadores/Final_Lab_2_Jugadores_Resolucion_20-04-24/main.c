#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idRegistro;
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase; //ano de nacimiento
    char puestoJugador[30];//Delantero - Medio - Defensor -Arquero
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
    int idEquipo; //GENERARLO, no esta en el archivo
    char nombreEquipo;
    int puntosGanados;
}stEquipo;

typedef struct
{
    stEquipo e;
    nodoListaJugador *lista_jugadores;
}arregloEquipo;

//void pasarACsv(char nombreArchivo[30]);


//Punto 1

stJugador nuevoJugador(int nroJugador,char nombreJugador[30],char apellidoJugador[30],int clase, char puestoJugador[30]);
nodoListaJugador *inicLista();
nodoListaJugador *nuevoNodo(stJugador nuevoJugador);
nodoListaJugador *insertarRec(nodoListaJugador *lista, nodoListaJugador *nuevo);

//Punto 2
int buscarEquipo(arregloEquipo equipos[],int validos, char nombreEquipo[30]);
void agregarEquipo(arregloEquipo equipos[], int *validos,stEquipo nuevoEquipo);
stEquipo crearEquipo(int idEquipo,char nombreEquipo[30], int puntosGanados);
void agregarJugador(arregloEquipo equipos[],int posicion,nodoListaJugador *nuevoJugador);
void altaJugador(arregloEquipo equipos[],int *validos);

//Punto 3
void pasarAADL(arregloEquipo equipos[],int *validos,char nombreArchivo[30]);

//Punto 4
void mostrarJugador(stJugador jugador);
void mostrarEquipo(stEquipo equipo);
void mostrarTodo(arregloEquipo equipos[],int validos);



int main()
{
    printf("Hello world!\n");
   // pasarACsv("registroJugador.dat");
    return 0;
}

//Punto 1

stJugador nuevoJugador(int nroJugador,char nombreJugador[30],char apellidoJugador[30],int clase, char puestoJugador[30])
{
    stJugador nuevo;
    nuevo.nroJugador=nroJugador;
    strcpy(&nuevo.nombreJugador,nombreJugador);
    strcpy(&nuevo.apellidoJugador,apellidoJugador);
    nuevo.clase=clase;
    strcpy(&nuevo.puestoJugador,puestoJugador);

    return nuevo;
}
nodoListaJugador *inicLista()
{
    return NULL;
}

nodoListaJugador *nuevoNodo(stJugador nuevoJugador)
{
    nodoListaJugador *nuevo=(nodoListaJugador*)malloc(sizeof(nodoListaJugador));
    nuevo->j=nuevoJugador;
    nuevo->sig=NULL;

    return nuevo;
}

nodoListaJugador *insertarRec(nodoListaJugador *lista, nodoListaJugador *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->j.apellidoJugador,nuevo->j.apellidoJugador)<0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            lista->sig=insertarRec(lista->sig,nuevo);
        }
    }
    return lista;
}

//Punto 2
int buscarEquipo(arregloEquipo equipos[],int validos, char nombreEquipo[30])
{
    int posicion=-1;
    if(validos>=1)
    {
        int contador=0;
        while(contador<validos && posicion==-1)
        {
            if(strcmpi(equipos[contador].e.nombreEquipo,nombreEquipo)==0)
            {
                posicion=contador;
            }
            contador++;
        }
    }

    return posicion;
}

void agregarEquipo(arregloEquipo equipos[], int *validos,stEquipo nuevoEquipo)
{
    equipos[*validos].e=nuevoEquipo;
    *validos+=1;
}

stEquipo crearEquipo(int idEquipo,char nombreEquipo[30], int puntosGanados)
{
    stEquipo nuevo;
    nuevo.idEquipo=idEquipo;
    strcpy(&nuevo.nombreEquipo,nombreEquipo);
    nuevo.puntosGanados=puntosGanados;
    return nuevo;
}

void agregarJugador(arregloEquipo equipos[],int posicion,nodoListaJugador *nuevoJugador)
{
    equipos[posicion].lista_jugadores=insertarRec(equipos[posicion].lista_jugadores,nuevoJugador);
}

void altaJugador(arregloEquipo equipos[],int *validos)
{
    printf("Ingrese el nombre del jugador: ");
    char nombreJugador[30];
    gets(nombreJugador);
    printf("Ingrese el apellido del jugador: ");
    char apellidoJugador[30];
    gets(apellidoJugador);
    printf("Ingrese el numero del jugador: ");
    int numero;
    scanf("%d",&numero);
    printf("Ingrese la clase: ");
    int clase;
    scanf("%d",&clase);
    printf("Ingrese el puesto del jugador Delantero - Medio - Defensor -Arquero: ");
    char puestoJugador[30];
    gets(puestoJugador);
    printf("Ingrese el nombre del equipo:");
    char nombreEquipo[30];
    gets(nombreEquipo);

    stJugador jugadorNuevo=nuevoJugador(numero,nombreJugador,apellidoJugador,clase,puestoJugador);
    nodoListaJugador *nuevo=nuevoNodo(jugadorNuevo);

    int posicionEquipo=buscarEquipo(equipos,*validos,nombreEquipo);
    if(posicionEquipo==-1)
    {
        stEquipo nuevoEquipo=crearEquipo(validos,nombreEquipo,0);
        posicionEquipo=*validos;
    }
    agregarJugador(equipos,*validos,nuevo);
}

//Punto 3
void pasarAADL(arregloEquipo equipos[],int *validos,char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stRegistroJugador buffer;
        while(fread(&buffer,sizeof(stRegistroJugador),1,archivo)>0)
        {
            int posicion=-1;
            stJugador nuevoJ=nuevoJugador(buffer.nroJugador,buffer.nombreJugador,buffer.nombreEquipo,buffer.clase,buffer.puestoJugador);
            nodoListaJugador *nuevoNodoJugador=nuevoNodo(nuevoJ);
            posicion=buscarEquipo(equipos,*validos,buffer.nombreEquipo);
            if(posicion==-1) //Si no lo encontro el equipo lo crea
            {
                stEquipo nuevoEquipo=crearEquipo(*validos,buffer.nombreEquipo,buffer.puntosGanados);
                posicion=*validos;
                agregarEquipo(equipos,*validos,nuevoEquipo);
            }
            agregarJugador(equipos,posicion,nuevoNodoJugador);
        }
        fclose(archivo);
    }
}


//Punto 4
void mostrarJugador(stJugador jugador)
{
    printf("Apellido: %s Nombre: %s N: %i Clase: %i Puesto: %s \n",jugador.apellidoJugador,jugador.nombreJugador,jugador.clase, jugador.puestoJugador);
}

void mostrarEquipo(stEquipo equipo)
{
    printf("\n===================================");
    printf("EQUIPO: %s PUNTOS: %i ID: %i",equipo.nombreEquipo,equipo.puntosGanados,equipo.idEquipo);
    printf("\n===================================");
}

void mostrarTodo(arregloEquipo equipos[],int validos)
{

}



/*
void pasarACsv(char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        FILE *archivoSalida=fopen("registro_jugadores.csv","w");
        stRegistroJugador buffer;
        while(fread(&buffer,sizeof(stRegistroJugador),1,archivo)>0)
        {
            fprintf(archivoSalida,"%i;%i;%s;%s;%i;%s;%s;%i\n",buffer.idRegistro,buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador,buffer.nombreEquipo,buffer.puntosGanados);
        }
        fclose(archivoSalida);
        fclose(archivo);
    }
}
*/
