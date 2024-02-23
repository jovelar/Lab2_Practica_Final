#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
 char origen[30];
 char destino[30];
 char tipo[30];//”aereo”,“ferrocarril”
 float costo;
 int tiempoViaje;
}registroEnvios;

typedef struct nodoDestino
{
   char nombre[30];
   float costo;
   int tiempoViaje;
   struct nodoDestino* sig;
}nodoDestino;

typedef struct nodoOrigen
 {
   char nombre[30];
   nodoDestino* destinosAereos;
   nodoDestino* destinosFerro;
   struct nodoOrigen* sig;
}nodoOrigen;

typedef struct
{
    int tiempoViaje;
    struct Pila *siguiente;
}Pila;



nodoOrigen *inicOrigen();
nodoOrigen *nuevoOrigen(char nombre[30]);
nodoOrigen *agregarRec(nodoOrigen *listaOrigen,nodoOrigen *nuevoOrigen);
nodoOrigen *eliminarNodo(nodoOrigen *listaOrigen);
nodoDestino *nuevoNodoDestino(char nombre[30],float costo,int tiempoViaje)
nodoDestino *agregarAlFinal(nodoDestino *listaDestino)

int promedioDestinos(nodoDestino *listaDestinos);
void pasarRegistrosALista(FILE *archivo);

void pasarRegistroACSV(FILE *archivo, char archivoSalida[30]);

int main()
{
    FILE *archivo=fopen("registroEnvios.bin","rb");
    pasarRegistroACSV(archivo,"registroEnvios.csv");
    return 0;
}

void pasarRegistroACSV(FILE *archivo, char archivoSalida[30])
{
    if(archivo)
    {
        FILE *archivoSal=fopen(archivoSalida,"w");
        registroEnvios buffer;

        while(fread(&buffer,sizeof(registroEnvios),1,archivo)>0)
        {
            fwrite(&buffer,sizeof(registroEnvios),1,archivoSal);
        }
        fclose(archivo);
        fclose(archivoSal);
    }
}
