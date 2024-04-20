#include <stdio.h>
#include <stdlib.h>

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

void pasarACsv(char nombreArchivo[30]);

int main()
{
    printf("Hello world!\n");
    pasarACsv("registroClub.dat");
    return 0;
}

void pasarACsv(char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        FILE *archivoSalida=fopen("registro_jugadores.csv","wb");
        stRegistroJugador buffer;
        while(fread(&buffer,sizeof(stRegistroJugador),1,archivo)>0)
        {
            fprintf(archivoSalida,"%i;%i;%s;%s;%i;%s;%s;%i\n",buffer.idRegistro,buffer.nroJugador,buffer.nombreJugador,buffer.apellidoJugador,buffer.clase,buffer.puestoJugador,buffer.nombreEquipo,buffer.puntosGanados);
        }
        fclose(archivoSalida);
        fclose(archivo);
    }
}
