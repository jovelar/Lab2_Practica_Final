#include "util.h"

void generarVotosBin(char nombreArchivoSalida[50])
{
    char provincias[24][30];
    strcpy(provincias[0],"Buenos Aires");
    strcpy(provincias[1],"CABA");
    strcpy(provincias[2],"Entre Rios");
    strcpy(provincias[3],"La Pampa");
    strcpy(provincias[4],"Cordoba");
    strcpy(provincias[5],"Mendoza");
    strcpy(provincias[6],"Santa Fe");
    strcpy(provincias[7],"Formosa");
    strcpy(provincias[8],"Chaco");
    strcpy(provincias[9],"Corrientes");
    strcpy(provincias[10],"Tierra del Fuego");
    strcpy(provincias[11],"Neuquen");
    strcpy(provincias[12],"Salta");
    strcpy(provincias[13],"Rio Negro");
    strcpy(provincias[14],"San Luis");
    strcpy(provincias[15],"San Juan");
    strcpy(provincias[16],"Catamarca");
    strcpy(provincias[17],"Tucuman");
    strcpy(provincias[18],"Santiago del Estero");
    strcpy(provincias[19],"Chubut");
    strcpy(provincias[20],"Jujuy");
    strcpy(provincias[21],"La Rioja");
    strcpy(provincias[22],"Misiones");
    strcpy(provincias[23],"Santa Cruz");
    FILE *archivo=fopen(nombreArchivoSalida,"wb");
    if(archivo)
    {
        int pos_provincia=0;
        for(int x=0;x<24;x++)
        {
            grabaPartido(archivo,"FDT",provincias[pos_provincia]);
            grabaPartido(archivo,"FIT",provincias[pos_provincia]);
            grabaPartido(archivo,"UCR",provincias[pos_provincia]);
            grabaPartido(archivo,"JXC",provincias[pos_provincia]);
            pos_provincia++;
        }
        fclose(archivo);
    }
}

int nroAleatorio()
{
    return 1+rand()%200000;
}

void grabaPartido(FILE *archivo,char nombrePartido[4],char nombreProvincia[30])
{
    RecuentoVotos voto;
    strcpy(voto.provincia,nombreProvincia);
    strcpy(voto.partido,nombrePartido);
    voto.cant_votos=nroAleatorio();
    fwrite(&voto,sizeof(RecuentoVotos),1,archivo);
}

void mostrarBin(char nombreArchivo[50])
{
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        int fdt=0;
        int fit=0;
        int ucr=0;
        int jxc=0;

        float porcFdt;
        float porcFit;
        float porcUcr;
        float porcJxc;

        RecuentoVotos buffer;
        while(fread(&buffer,sizeof(RecuentoVotos),1,archivo)>0)
        {
            mostrarRegistro(buffer);

            if(strcmpi(buffer.partido,"FDT")==0)
            {
                fdt=fdt+buffer.cant_votos;
            }

            if(strcmpi(buffer.partido,"FIT")==0)
            {
                fit=fit+buffer.cant_votos;
            }

            if(strcmpi(buffer.partido,"UCR")==0)
            {
                ucr=ucr+buffer.cant_votos;
            }

            if(strcmpi(buffer.partido,"JXC")==0)
            {
                jxc=jxc+buffer.cant_votos;
            }
        }
        fclose(archivo);

        int total=fdt+fit+ucr+jxc;
        porcFdt=((float)fdt/total)*100;
        porcFit=((float)fit/total)*100;
        porcUcr=((float)ucr/total)*100;
        porcJxc=((float)jxc/total)*100;

        printf("Recuento: \n");
        printf("FDT votos %i %0.2f %% \n",fdt,porcFdt);
        printf("FIT votos %i %0.2f %% \n",fit,porcFit);
        printf("UCR votos %i %0.2f %% \n",ucr,porcUcr);
        printf("JXC votos %i %0.2f %% \n",jxc,porcJxc);

    }
}
void mostrarRegistro(RecuentoVotos registro)
{
    printf("Provincia %-20s; Partido: %-4s ;Votos ;%i \n",registro.provincia,registro.partido,registro.cant_votos);
}
