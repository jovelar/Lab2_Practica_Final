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
//void agregarEquipo(arregloEquipo equipos[], int *validos,stEquipo nuevoEquipo);
stEquipo crearEquipo(int idEquipo,char nombreEquipo[30], int puntosGanados);
void agregarJugador(arregloEquipo equipos[],int posicion,nodoListaJugador *nuevoJugador);
void altaJugador(arregloEquipo equipos[],int *validos);

//Punto 3
void pasarAADL(arregloEquipo equipos[],int *validos,char nombreArchivo[30]);
void ejercicio3(arregloEquipo equipos[],int *validos,char nombreArchivo[30]);

//Punto 4
void mostrarJugador(stJugador jugador);
void mostrarJugadores(nodoListaJugador *lista);
void mostrarEquipo(stEquipo equipo);
void mostrarTodo(arregloEquipo equipos[],int validos);
void ejercicio4(arregloEquipo equipos[],int validos);

//Punto 5
int buscaNumeroJugador(arregloEquipo equipos[],int validos,char nombreEquipo[30],char nombre[30],char apellido[30]);
void ejercicio5(arregloEquipo equipos[],int validos);

int main()
{
   // pasarACsv("registroJugador.dat");
   int validos=0;
   arregloEquipo equipos[50];
   char nombreArchivo[30]="registroJugador.dat";
   ejercicio3(equipos,&validos,nombreArchivo);
   ejercicio5(equipos,validos);
    return 0;
}

//Punto 1

stJugador nuevoJugador(int nroJugador,char nombreJugador[30],char apellidoJugador[30],int clase, char puestoJugador[30])
{
    stJugador nuevo;
    nuevo.nroJugador=nroJugador;
    strcpy(nuevo.nombreJugador,nombreJugador);
    strcpy(nuevo.apellidoJugador,apellidoJugador);
    nuevo.clase=clase;
    strcpy(nuevo.puestoJugador,puestoJugador);

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
    if(validos>=0)
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

/*
void agregarEquipo(arregloEquipo equipos[], int *validos,stEquipo nuevoEquipo)
{
    equipos[(int)*validos].lista_jugadores=NULL;
    equipos[(int)*validos].e=nuevoEquipo;
}
*/
stEquipo crearEquipo(int idEquipo,char nombreEquipo[30], int puntosGanados)
{
    stEquipo nuevo;
    nuevo.idEquipo=idEquipo;
    nuevo.puntosGanados=puntosGanados;
    strcpy(nuevo.nombreEquipo,nombreEquipo);
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
            stJugador nuevoJ=nuevoJugador(buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador);
            nodoListaJugador *nuevoNodoJugador=nuevoNodo(nuevoJ);
            posicion=buscarEquipo(equipos,(int)*validos,buffer.nombreEquipo);
            printf("\nLos validos son %i, equipo a buscar: %s",*validos,buffer.nombreEquipo);
            if(posicion==-1) //Si no lo encontro el equipo lo crea
            {
                stEquipo nuevoEquipo=crearEquipo((int)*validos,buffer.nombreEquipo,buffer.puntosGanados);
                posicion=(int)*validos;
                printf("\nValidos: %i",*validos);
                //agregarEquipo(equipos,(int)*validos,nuevoEquipo);
                equipos[(int)*validos].e=nuevoEquipo;
                *validos=*validos+1;
            }
            agregarJugador(equipos,posicion,nuevoNodoJugador);
        }
        fclose(archivo);
    }
}

void ejercicio3(arregloEquipo equipos[],int *validos,char nombreArchivo[30])
{
    pasarAADL(equipos,validos,nombreArchivo);
}

//Punto 4
void mostrarJugador(stJugador jugador)
{
    printf("Apellido: %s Nombre: %s N: %i Clase: %i Puesto: %s \n",jugador.apellidoJugador,jugador.nombreJugador,jugador.clase, jugador.puestoJugador);
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

void mostrarEquipo(stEquipo equipo)
{
    printf("\n===================================");
    printf("EQUIPO: %s PUNTOS: %i ID: %i",equipo.nombreEquipo,equipo.puntosGanados,equipo.idEquipo);
    printf("\n===================================");
}

void mostrarTodo(arregloEquipo equipos[],int validos)
{
    int contador=0;
    while(contador<=validos)
    {
        mostrarEquipo(equipos[contador].e);
        mostrarJugadores(equipos[contador].lista_jugadores);
        contador+=1;
    }
}

void ejercicio4(arregloEquipo equipos[],int validos)
{
    mostrarTodo(equipos,validos);
}

//Punto 5
int buscaNumeroJugador(arregloEquipo equipos[],int validos,char nombreEquipo[30],char nombre[30],char apellido[30])
{
    int nroJugador=-1;
    int posicionEquipo=buscarEquipo(equipos,validos,nombreEquipo);
    if(posicionEquipo>-1)
    {
        nodoListaJugador *iterador=equipos[posicionEquipo].lista_jugadores;
        while(iterador && nroJugador==-1)
        {
            if(strcmpi(iterador->j.nombreJugador,nombre==0)&&strcmpi(iterador->j.apellidoJugador,apellido)==0)
            {
                nroJugador=iterador->j.nroJugador;
            }
            iterador=iterador->sig;
        }
    }
    return nroJugador;
}

void ejercicio5(arregloEquipo equipos[],int validos)
{
    printf("\nIngrese el nombre del jugador: ");
    char nombre[30];
    gets(nombre);
    printf("\n Ingrese el apellido de jugador: ");
    char apellido[30];
    gets(apellido);
    printf("\nIngrese el nombre del equipo: ");
    char equipo[30];
    gets(equipo);
    int nroJugador=buscaNumeroJugador(equipo,validos,equipo,nombre,apellido);
    if(nroJugador==-1)
    {
        printf("\nNo se encontro el jugador");
    }
    else
    {
        printf("\n Jugador: %s %s Nro: %i ",apellido,nombre,nroJugador);
    }
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
