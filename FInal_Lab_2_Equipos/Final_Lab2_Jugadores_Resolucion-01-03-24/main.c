#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char nombreDeporte[50];
}stClub;

typedef struct nodo2
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    float valorCuota;
    int edad;
    struct nodo2 *sig;
    struct nodo2 *ante;
}nodo2;

typedef struct nodo
{
    int idDeporte;
    char nombreDeporte[50];
    nodo2 *listaSocios;
    struct nodo *sig;
}nodo;

void pasarACVC(char nombreArchivoSalida[40],char nombreArchivoEntrada[40]);

nodo *pasarALDL(char nombreArchivo[50]);

nodo *crearNodoDeporte(int idDeporte,char nombreDeporte[30]);
nodo *agregarNodoAlFinal(nodo *lista,nodo* nuevo);

void mostrarDeporte(nodo *deporte);
void mostrarTodo(nodo *listaDeportes);
nodo *buscarDeportePorId(nodo *listaDeporte,int idDeporte);

nodo2 *crearNodoSocio(int idSocio,char nya[50],int ultimaCuota,float valorCuota, int edad);

nodo2 *agregarOrdenadoSocio(nodo2 *listaSocio,nodo2 *nuevo);

void altaManual(nodo **listado);
int buscarSocio(nodo *listado,char nya[40]);

void mostrarSocio(nodo2 *socio);
void mostrarListaSocios(nodo2 *listaSocios);
void mostrarDeporteMasPopular(nodo *listaDeportes);

int contarSocios(nodo2 *listaSocios);
nodo *buscarDeporteMasPopular(nodo *listaDeportes);


void ejercicio2(char nombreArchivo[50],nodo **lista);
void ejercicio3();
void ejercicio4();
void ejercicio5();
void ejercicio6();

int main()
{
    //pasarACVC("jugadores.csv","registroClub.dat");
    nodo *listado=NULL;
    char nombreArchivo[50]="registroClub.dat";

    ejercicio2(nombreArchivo,&listado);

    return 0;
}

/*
void pasarACVC(char nombreArchivoSalida[40],char nombreArchivoEntrada[40])
{
    FILE *archivoEntrada = fopen(nombreArchivoEntrada,"rb");
    if(archivoEntrada)
    {
        FILE *archivoSalida=fopen(nombreArchivoSalida,"wb");
        stClub buffer;

        while(fread(&buffer,sizeof(stClub),1,archivoEntrada)>0)
        {
            fprintf(archivoSalida,"%i;%s;%i;%0.2f;%i;%i;%s\n",buffer.idSocio,buffer.nya,buffer.ultimaCuotaPaga,buffer.valorCuota,buffer.edad,buffer.idDeporte,buffer.nombreDeporte);
        }
        fclose(archivoEntrada);
        fclose(archivoSalida);
    }

}
*/

nodo *pasarALDL(char nombreArchivo[50])
{
    nodo *listaCargada=NULL;

    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stClub buffer;
        while(fread(&buffer,sizeof(stClub),1,archivo)>0)
        {
            nodo2 *socio=crearNodoSocio(buffer.idDeporte,buffer.nya,buffer.ultimaCuotaPaga,buffer.valorCuota,buffer.edad);

            nodo *posicionDeporte=buscarDeportePorId(listaCargada,buffer.idDeporte);
            if(!posicionDeporte)
            {
                nodo *nuevoDeporte=crearNodoDeporte(buffer.idDeporte,buffer.nombreDeporte);
                listaCargada=agregarNodoAlFinal(listaCargada,nuevoDeporte);
                posicionDeporte=nuevoDeporte;
            }
            posicionDeporte->listaSocios=agregarOrdenadoSocio(posicionDeporte->listaSocios,socio);

        }
        fclose(archivo);
    }
    return listaCargada;
}
nodo *crearNodoDeporte(int idDeporte,char nombreDeporte[30])
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->idDeporte=idDeporte;
    strcpy(nuevo->nombreDeporte,nombreDeporte);
    nuevo->listaSocios=NULL;
    nuevo->sig=NULL;

    return nuevo;
}

nodo *agregarNodoAlFinal(nodo *lista,nodo* nuevo)
{
    if (!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo *iterador=lista;

        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }
    return lista;
}

void mostrarDeporte(nodo *deporte)
{
    if(deporte)
    {
        printf("\n %i | %s ",deporte->idDeporte,deporte->nombreDeporte);
    }
}

void mostrarTodo(nodo *listaDeportes)
{
    if(listaDeportes)
    {
        nodo *iterador=listaDeportes;
        while(iterador)
        {
            mostrarDeporte(iterador);
            mostrarListaSocios(iterador->listaSocios);
            iterador=iterador->sig;
        }
    }
    else
    {
        printf("\nLa lista esta vacia!");
    }
}
nodo *buscarDeportePorId(nodo *listaDeporte,int idDeporte)
{
    nodo *posDeporte=NULL;
    if(listaDeporte)
    {
        nodo *iterador=listaDeporte;

        while(iterador && !posDeporte)
        {
            if(iterador->idDeporte==idDeporte)
            {
                posDeporte=iterador;
            }
            iterador=iterador->sig;
        }
    }
    return posDeporte;
}

nodo2 *crearNodoSocio(int idSocio,char nya[50],int ultimaCuota,float valorCuota, int edad)
{
    nodo2 *nuevoSocio=(nodo2*)malloc(sizeof(nodo2));

    nuevoSocio->idSocio=idSocio;
    strcpy(nuevoSocio->nya,nya);
    nuevoSocio->ultimaCuotaPaga=ultimaCuota;
    nuevoSocio->valorCuota=valorCuota;
    nuevoSocio->edad=edad;
    nuevoSocio->sig=NULL;

    return nuevoSocio;
}


nodo2 *agregarOrdenadoSocio(nodo2 *listaSocio,nodo2 *nuevo)
{
    if(!listaSocio)
    {
        listaSocio=nuevo;
    }
    else
    {
        if(strcmpi(listaSocio->nya,nuevo->nya)>0)
        {
            nuevo->sig=listaSocio;
            listaSocio->ante=nuevo;
            listaSocio=nuevo;

        }
        else
        {
            nodo2 *iterador=listaSocio;
            nodo2 *ante=iterador;


            while(iterador && strcmpi(iterador->nya,nuevo->nya)<0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            if(!iterador)
            {
                ante->sig=nuevo;
                nuevo->ante=ante;
            }
            else
            {
                ante->sig=nuevo;
                nuevo->ante=ante;

                nuevo->sig=iterador;
                iterador->ante=nuevo;
            }
        }
    }
    return listaSocio;
}

void altaManual(nodo **listado)
{

}

int buscarSocio(nodo *listado,char nya[40]) //SI EL USUARIO EXISTE NO SE CARGARA 2 VECES
{
    int encontrado=0;

    if(listado)
    {
        nodo *iterador=listado;
        while(iterador && encontrado==0)
        {
            if(iterador->listaSocios)
            {
                nodo2 *iteradorSocio=iterador->listaSocios;
                while(iteradorSocio && encontrado==0)
                {
                    if(strcmpi(iteradorSocio->nya,nya)==0)
                    {
                        encontrado==1;
                    }
                    iteradorSocio=iteradorSocio->sig;
                }
            }
            iterador=iterador->sig;
        }
    }
    return encontrado;
}

void mostrarSocio(nodo2 *socio)
{
    if(socio)
    {
        printf("\n   %i | %-30s | %2i | %0.2f | %i ",socio->idSocio,socio->nya,socio->edad,socio->valorCuota,socio->ultimaCuotaPaga);
    }
}
void mostrarListaSocios(nodo2 *listaSocios)
{
    if(listaSocios)
    {
        nodo2 *iterador=listaSocios;
        while(iterador)
        {
            mostrarSocio(iterador);
            iterador=iterador->sig;
        }
    }
}

void mostrarDeporteMasPopular(nodo *listaDeportes)
{
    if(listaDeportes)
    {
        nodo *deporteMasPopular=buscarDeporteMasPopular(listaDeportes);
        printf("\n DEPORTE MAS POPULAR : %s ",deporteMasPopular->nombreDeporte);
        printf("\n Socios que lo practican");
        mostrarListaSocios(deporteMasPopular->listaSocios);
    }
}

int contarSocios(nodo2 *listaSocios)
{
    int resultado=0;
    if(listaSocios)
    {
        nodo2 *iterador=listaSocios;
        while(iterador)
        {
            resultado++;
            iterador=iterador->sig;
        }
    }
    return resultado;
}

nodo *buscarDeporteMasPopular(nodo *listaDeportes)
{
    int contador,maximo=0;

    nodo *deporteMasPopular=NULL;
    if(listaDeportes)
    {
        nodo *iterador=listaDeportes;
        while(iterador)
        {
            contador=contarSocios(iterador->listaSocios);
            if(contador>maximo)
            {
                maximo=contador;
                deporteMasPopular=iterador;
            }
            iterador=iterador->sig;
            contador=0;
        }
    }

    return deporteMasPopular;
}

void ejercicio2(char nombreArchivo[50], nodo **lista)
{
    *lista=pasarALDL(nombreArchivo);


    return lista;
}

