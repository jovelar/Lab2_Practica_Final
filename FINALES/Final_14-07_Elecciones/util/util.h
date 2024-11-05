#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#endif // UTIL_H_INCLUDED

typedef struct
{
    char provincia[30];
    char partido[30];//FDT,FIT,UCR,JXC
    int cant_votos;
}RecuentoVotos;

void generarVotosBin(char nombreArchivoSalida[50]);
int nroAleatorio();
void grabaPartido(FILE *archivo,char nombrePartido[4],char nombreProvincia[30]);
void mostrarBin(char nombreArchivo[50]);
void mostrarRegistro(RecuentoVotos registro);
