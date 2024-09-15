#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idRegistro;
    int nroJugador;
    char nombreJugador[30];
    char apellidoJugador[30];
    int clase; //4 digitos anio
    char puestoJugador[30];// Delantero Medio Defensor Arquero
    char nombreEquipo[30];
    int puntosGanados;
}stRegistrojugador;

//Jugador
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

//Equipo
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
 }celdaEquipo;

 //Punto 1
 //{
 nodoListaJugador *inicLista();
 nodoListaJugador *crearNodo(int nroJugador, char nombreJugador[30], char apellidoJugador[30], int clase, char puestoJugador[30]);
 nodoListaJugador *insertarRecursivo(nodoListaJugador *lista, nodoListaJugador *nuevo);
 //}

 //Punto 2
 //{
 int buscarEquipo(celdaEquipo arreglo[],char nombreEquipo[30], int validos);
  celdaEquipo crearCeldaEquipo(int idEquipo,char nombreEquipo[30],int puntosGanados);
 void altaJugador(celdaEquipo arreglo[], int *validos);
 //}

 //Punto 3
 //{
 int buscarJugador(nodoListaJugador *lista, char apellido[30],char nombre[30]);
 int buscar(celdaEquipo arreglo[],char equipo[30],char apellido[30],char nombre[30], int validos);
 void pasarAADL(celdaEquipo arreglo[],char nombreArchivo[40], int *validos);
 //}

 //Punto 4
 //{
 void mostrarEquipo(stEquipo equipo);
 void mostrarEquipos(celdaEquipo arreglo[],int validos);
 void mostrarJugador(nodoListaJugador *jugador);
 void mostrarJugadores(nodoListaJugador *lista);
 //}

 void punto1();
 void punto2();
 void punto3(char nombreArchivo[50],celdaEquipo arreglo[],int *validos);
 void punto4(celdaEquipo arreglo[], int validos);
 void punto5(celdaEquipo arreglo[], int validos);

int main()
{
    char nombreArchivo[]="registroJugador.dat";
    //pasaraCSV(nombreArchivo);
    int validos=0;
    celdaEquipo arreglo[5000];
    punto3(nombreArchivo,arreglo,&validos);
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

 nodoListaJugador *crearNodo(int nroJugador, char nombreJugador[30], char apellidoJugador[30], int clase, char puestoJugador[30])
 {
     nodoListaJugador *nuevo=(nodoListaJugador*)malloc(sizeof(nodoListaJugador));
     stJugador j;
     strcpy(j.nombreJugador,nombreJugador);
     strcpy(j.apellidoJugador,apellidoJugador);
     strcpy(j.puestoJugador,puestoJugador);
     j.nroJugador=nroJugador;
     j.clase=clase;
     nuevo->j=j;
     nuevo->sig=NULL;
     return nuevo;
 }

 nodoListaJugador *insertarRecursivo(nodoListaJugador *lista, nodoListaJugador *nuevo)
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
             lista->sig=insertarRecursivo(lista->sig,nuevo);
         }
     }
     return lista;
 }
//}
//Punto 2
//{
 int buscarEquipo(celdaEquipo arreglo[],char nombreEquipo[30], int validos)
 {
     int posicion=-1;
     int contador=0;
     while(contador<validos && posicion==-1)
     {
         if(strcmpi(arreglo[contador].e.nombreEquipo,nombreEquipo)==0)
         {
             posicion=contador;
         }
         contador++;
     }
     return posicion;
 }

  celdaEquipo crearCeldaEquipo(int idEquipo,char nombreEquipo[30],int puntosGanados)
 {
     stEquipo nuevo;
     strcpy(nuevo.nombreEquipo,nombreEquipo);
     nuevo.idEquipo=idEquipo;
     nuevo.puntosGanados=puntosGanados;
     celdaEquipo nuevoNodo;
     nuevoNodo.e=nuevo;
     nuevoNodo.listaJugadores=NULL;

     return nuevoNodo;
 }

  void altaJugador(celdaEquipo arreglo[], int *validos)
 {
     int id;
     char apellido[30];
     char nombre[30];
     char posicion[30];
     int clase;
     char equipo[30];

     printf("Ingrese el apellido del jugador: ");
     gets(apellido);
     fflush(stdin);
     printf("Ingrese el nombre del jugador: ");
     gets(nombre);
     fflush(stdin);
     printf("Ingrese la posicion (delantero, medio, defensor, arquero: ");
     gets(posicion);
     printf("Ingrese el nro del jugador: ");
     scanf("%d",&id);
     printf("Ingrese la clase del jugador (4 digitos): ");
     scanf("%d",clase);
     printf("Ingrese el equipo del jugador: ");
     fflush(stdin);
     gets(equipo);
     nodoListaJugador *nuevoJugador=crearNodo(id,nombre,apellido,clase,posicion);
     int posArreglo=buscarEquipo(arreglo,equipo,*validos);
     if(posArreglo==-1)
     {
         stEquipo nuevo;
         strcpy(nuevo.nombreEquipo,equipo);
         nuevo.idEquipo=validos+1;
         nuevo.puntosGanados=0;
         arreglo[*validos].e=nuevo;
         (*validos)++;
         posArreglo=*validos;
     }
     arreglo[posArreglo].listaJugadores=insertarRecursivo(arreglo[posArreglo].listaJugadores,nuevoJugador);
     printf("Jugador agregado! \n");
 }
 //}
//Punto 3
//{
  int buscarJugador(nodoListaJugador *lista, char apellido[30],char nombre[30])
 {
     int numero=-1;
     if(lista)
     {
         nodoListaJugador *iterador=lista;
         while(iterador && numero==-1)
         {
             printf("Comparando %s,%s con %s,%s \n",iterador->j.apellidoJugador,iterador->j.nombreJugador,apellido,nombre);
             if(strcmpi(iterador->j.apellidoJugador,apellido)==0)
             {
                 if(strcmpi(iterador->j.nombreJugador,nombre)==0)
                 {
                     numero=iterador->j.nroJugador;
                 }
             }
             iterador=iterador->sig;
         }
     }
     return numero;
 }

 int buscar(celdaEquipo arreglo[],char equipo[30],char apellido[30],char nombre[30], int validos)
 {
     int numero=-1;
     int posicion=buscarEquipo(arreglo,equipo,validos);
     if(posicion!=-1)
     {
         numero=buscarJugador(arreglo[posicion].listaJugadores,apellido,nombre);
     }
     return numero;
 }

  void pasarAADL(celdaEquipo arreglo[],char nombreArchivo[40], int *validos)
 {
     FILE *archivo=fopen(nombreArchivo,"rb");
     if(archivo)
     {
         stRegistrojugador buffer;
         while(fread(&buffer,sizeof(stRegistrojugador),1,archivo)>0)
         {
             nodoListaJugador *jugador=crearNodo(buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador);
             int posEquipo=buscarEquipo(arreglo,buffer.nombreEquipo,*validos);
             if(posEquipo==-1)
             {
                 celdaEquipo nuevoEquipo=crearCeldaEquipo(*validos+1,buffer.nombreEquipo,buffer.puntosGanados);
                 arreglo[*validos]=nuevoEquipo;
                 posEquipo=*validos;
                 (*validos)++;
             }
             arreglo[posEquipo].listaJugadores=insertarRecursivo(arreglo[posEquipo].listaJugadores,jugador);
         }
         fclose(archivo);
     }
     else
     {
         printf("El archivo no existe! \n");
     }
 }
 //}
//Punto 4
//{
 void mostrarJugador(nodoListaJugador *jugador)
 {
     printf("%2i %20s %20s %10s %4i \n",jugador->j.nroJugador,jugador->j.apellidoJugador,jugador->j.nombreJugador,jugador->j.puestoJugador,jugador->j.clase);
 }

 void mostrarJugadores(nodoListaJugador *lista)
 {
     if(lista)
     {
         nodoListaJugador *iterador=lista;
         while(iterador)
         {
             mostrarJugador(iterador);
             iterador=iterador->sig;
         }
     }
 }

 void mostrarEquipo(stEquipo equipo)
 {
     printf("ID: %i EQUIPO: %s PUNTOS: %\n",equipo.idEquipo,equipo.nombreEquipo,equipo.puntosGanados);
 }
 void mostrarEquipos(celdaEquipo arreglo[],int validos)
 {
     for(int x=0; x<validos;x++)
     {
         mostrarEquipo(arreglo[x].e);
         mostrarJugadores(arreglo[x].listaJugadores);
     }
 }

 //}
 void punto1();
 void punto2();
 void punto3(char nombreArchivo[50],celdaEquipo arreglo[],int *validos)
 {
     pasarAADL(arreglo,nombreArchivo,validos);
 }
 void punto4(celdaEquipo arreglo[], int validos)
 {
     mostrarEquipos(arreglo,validos);
 }

 void punto5(celdaEquipo arreglo[], int validos)
 {
     char equipo[30];
     char nombre[30];
     char apellido[30];
     printf("Ingrese el nombre del club: ");
     fflush(stdin);
     gets(equipo);
     printf("Ingrese el apellido del jugador: ");
     fflush(stdin);
     gets(apellido);
     printf("Ingrese el nombre del jugador: ");
     fflush(stdin);
     gets(nombre);
     int posJugador=buscar(arreglo,equipo,apellido,nombre,validos);

     if(posJugador==-1)
     {
         printf("No encontrado! \n");
     }
     else

     {
         printf("Numero: %i \n",posJugador);
     }

 }

 void pasaraCSV(char nombreArchivo[30])
 {
     FILE *archivo=fopen(nombreArchivo,"rb");
     if(archivo)
     {
         FILE *archivoCSV=fopen("registroCSV.csv","wb");
         stRegistrojugador buffer;
         while(fread(&buffer,sizeof(stRegistrojugador),1,archivo)>0)
         {
             fprintf(archivoCSV,"%i;%i;%s;%s;%i;%s;%s;%i\n",buffer.idRegistro,buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador,buffer.nombreEquipo,buffer.puntosGanados);
         }
         fclose(archivo);
         fclose(archivoCSV);
     }
 }

