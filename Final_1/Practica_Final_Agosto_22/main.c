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
    char puestoJugador[30]; //Delantero - Medio - Defensor - Arquero
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
    struct nodoJugador *sig;
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
    nodoListaJugador * listaJugadores;
}arregloEquipo;



int main()
{
    generarArchivoRegistros("listaDeJugadores.bin");
}

//FUNCIONES AUXILIARES

void generarArchivoRegistros(char nombreArchivo[50])
{
    FILE *archivo=fopen(nombreArchivo,"w");
    stRegistroJugador listaJugadores[]={
    //River Plate
    {1,1,"Miguel Angel","Dominguez",1998,"Arquero","River Plate",4},
    {2,2,"Angel","Saenz",2000,"Medio","River Plate",25},
    {3,3,"Miguel","Perez",1998,"Defensor","River Plate",10},
    {4,4,"Maximo","Suarez",1998,"Defensor","River Plate",10},
    {5,5,"Norberto","Valiant",1993,"Medio","River Plate",8},
    {6,6,"Favio","LongChamps",1994,"medio","River Plate",18},
    {7,7," Angel","Dominguez",1998,"Arquero","River Plate",4},
    {8,8,"Favio","Lambs",2000,"Medio","River Plate",4},
    {9,9,"Ricardo","Bans",1996,"Delantero","River Plate",4},
    {10,10,"Martin","Suarez",1999,"Delantero","River Plate",4},
    {11,11,"Lalo","Dominguez",1997,"Delantero","River Plate",4},

    //San Lorenzo
    {1,1,"Jorge Angel","Dominguez",1998,"Arquero","San Lorenzo",4},
    {2,2,"Angel","Funs",2000,"Medio","San Lorenzo",25},
    {3,3,"Cacho","Perez",1998,"Defensor","San Lorenzo",10},
    {4,4,"Maximo","Longchamps",1998,"Defensor","San Lorenzo",10},
    {5,5,"Julio","Valiant",1993,"Medio","San Lorenzo",8},
    {6,6,"Favio","LeClerc",1994,"medio","San Lorenzo",18},
    {7,7,"Tito","Dominguez",1998,"Arquero","San Lorenzo",4},
    {8,8,"Favio","Pogo",2000,"Medio","San Lorenzo",4},
    {9,9,"Miguel","Bans",1996,"Delantero","San Lorenzo",4},
    {10,10,"Martin","Roger",1999,"Delantero","San Lorenzo",4},
    {11,11,"Estanislao","Dominguez",1997,"Delantero","San Lorenzo",4},

    //Velez
    {1,1,"Jorge Klauzz","Dominguez",1998,"Arquero","Velez",4},
    {2,2,"Pepe","Funs",2000,"Medio","Velez",25},
    {3,3,"Cacho","Spirits",1998,"Defensor","Velez",10},
    {4,4,"Julian","Longchamps",1998,"Defensor","Velez",10},
    {5,5,"Julio","Ricks",1993,"Medio","Velez",8},
    {6,6,"Claudio","LeClerc",1994,"medio","Velez",18},
    {7,7,"Tito","Fernandez",1998,"Arquero","Velez",4},
    {8,8,"Kio","Pogo",2000,"Medio","Velez",4},
    {9,9,"Miguel","Fantasma",1996,"Delantero","Velez",4},
    {10,10,"Martin","Roger",1999,"Delantero","Velez",4},
    {11,11,"Estanislao","Dominguez",1997,"Delantero","Velez",4},

    //Racing

    {1,1,"Jorge Klauzz","Damper",1998,"Arquero","Racing",4},
    {2,2,"Pepe","Crops",2000,"Medio","Racing",25},
    {3,3,"Cacho","Slimer",1998,"Defensor","Racing",10},
    {4,4,"Julian","GhostBuster",1998,"Defensor","Racing",10},
    {5,5,"Julio","Morty",1993,"Medio","Racing",8},
    {6,6,"Claudio","Van Halen",1994,"medio","Racing",18},
    {7,7,"Tito","Toto",1998,"Arquero","Racing",4},
    {8,8,"Toto","Africa",2000,"Medio","Racing",4},
    {9,9,"Miguel","Lumps",1996,"Delantero","Racing",4},
    {10,10,"Martin","Richards III",1999,"Delantero","Racing",4},
    {11,11,"Estanislao","Carpenter Williams",1997,"Delantero","Racing",4}

    };

    for(int x=0;x<44;x++)
    {
        fwrite(&listaJugadores[x],sizeof(stRegistroJugador),1,archivo);
    }
    fclose(archivo);
}
