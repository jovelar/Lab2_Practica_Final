#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nombreCanal[40];
    char rubro[30];              //los rubros de juegos a los que se dedica cada canal son (y estan escritos
                                          // tal cual: “fantasia","creativos","accion","aventura","retro","construccion"
    int cantSuscriptores;            //cantidad de suscript total del canal
    int cantVistasSemestre;       //cantidad de vistas que recibieron sus videos en el último semestre
} stYoutuber;

void pasarACSV(char nombreArchivo[30]);

int main()
{
    pasarACSV("archivoYoutubers.bin");
    return 0;
}

void pasarACSV(char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stYoutuber buffer;
        FILE *archivoSalida=fopen("RegistroYT.CSV","wb");
        while(fread(&buffer,sizeof(stYoutuber),1,archivo)>0)
        {
            fprintf(archivoSalida,"%i;%s;%s;%i;%i\n`",buffer.id,buffer.nombreCanal,buffer.rubro,buffer.cantSuscriptores,buffer.cantVistasSemestre);
        }
        fclose(archivo);
        fclose(archivoSalida);
    }
    else
    {
        printf("\nError\n");
    }
}
