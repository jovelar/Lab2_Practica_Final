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

typedef struct
{
    int idDeporte;
    char nombreDeporte[50];
}stDeporte;

typedef struct
{
    int idSocio;
    char nya[40];
    int ultimaCuota;
    float valorCuota;
    int edad;
    int idDeporte;
}stSocio;

void pasarACVC(char nombreArchivoSalida[40],char nombreArchivoEntrada[40]);

nodo *pasarALDL(char nombreArchivo[50]);

nodo *crearNodoDeporte(int idDeporte,char nombreDeporte[30]);
nodo *agregarNodoAlFinal(nodo *lista,nodo* nuevo);

void mostrarDeporte(nodo *deporte);
void mostrarTodo(nodo *listaDeportes);
nodo *buscarDeportePorId(nodo *listaDeporte,int idDeporte);

nodo *buscarDeportePorNombre(nodo *lista, char nombreDeporte[40]);
nodo *buscarSocioPorNombre(nodo2 *listaSocios, char nombreSocio[40]);

nodo2 *crearNodoSocio(int idSocio,char nya[50],int ultimaCuota,float valorCuota, int edad);

nodo2 *agregarOrdenadoSocio(nodo2 *listaSocio,nodo2 *nuevo);

void altaManual(nodo **listado);
int buscarSocio(nodo *listado,char nya[40]);

int buscarUltimoDeporteID(nodo *listado);
int buscarUltimoIDSOcioUSado(nodo2 *listaSocios);

void mostrarSocio(nodo2 *socio);
void mostrarListaSocios(nodo2 *listaSocios);
void mostrarDeporteMasPopular(nodo *listaDeportes);

int contarSocios(nodo2 *listaSocios);
nodo *buscarDeporteMasPopular(nodo *listaDeportes);

void pasarADosBinarios(nodo *lista, char binarioUno[40],char binarioDos[40]);

void pasarDeudores(nodo *lista, char deporte[40],int cuota,stClub arreglo[], int *validos);
void mostrarArregloDeudores(stClub arreglo[], int validos);

void borrarTodaLaLista(nodo *listado);

void ejercicio2(char nombreArchivo[50],nodo **lista);
void ejercicio3(nodo **lista);
void ejercicio4(nodo *lista);
void ejercicio5(nodo *lista, char archivoDeporte[40], char archivoSocio[40]);
void ejercicio6(nodo *lista, stClub arreglo[],int *validos);

int main()
{
    //pasarACVC("jugadores.csv","registroClub.dat");
    nodo *listado=NULL;
    char nombreArchivo[50]="registroClub.dat";
    stClub deudores[50];
    int validos=0;

    ejercicio2(nombreArchivo,&listado);
    ejercicio3(&listado);
    ejercicio4(listado);
    ejercicio5(listado,"deportes.bin","socios.bin");
    ejercicio6(listado,deudores,&validos);

    borrarTodaLaLista(listado);

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
            nodo2 *socio=crearNodoSocio(buffer.idSocio,buffer.nya,buffer.ultimaCuotaPaga,buffer.valorCuota,buffer.edad);

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

nodo *buscarDeportePorNombre(nodo *lista, char nombreDeporte[40])
{
    nodo *posDeporte=NULL;

    if(lista)
    {
        printf("\nComparando %s con %s ",lista->nombreDeporte,nombreDeporte);
        if(strcmpi(lista->nombreDeporte,nombreDeporte)==0)
        {

            posDeporte=lista;
        }
        else
        {
            nodo *iterador=lista;
            while(iterador  && !posDeporte)
            {
                printf("\nComparando %s con %s ",iterador->nombreDeporte,nombreDeporte);
                if(strcmpi(iterador->nombreDeporte,nombreDeporte)==0)
                {
                    posDeporte=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }
    return posDeporte;
}

nodo *buscarSocioPorNombre(nodo2 *listaSocios, char nombreSocio[40])
{
    nodo *socioAbuscar=NULL;

    return socioAbuscar;
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

    printf("\nIngrese el deporte: ");
    char deporte[40];
    gets(deporte);
    nodo *posDeporte=buscarDeportePorNombre(*listado,deporte);
    int opcion=0;
    if(!posDeporte)
    {
        printf("\nEl deporte no existe. desea crearlo [s/n]?");
        int opcion;
        while(opcion!=115 && opcion!=110)
        {
            opcion=getch();
            switch(opcion)
            {
                case 110:
                    break;

                case 115:;
                    int ultimoId=1+buscarUltimoDeporteID(*listado);
                    nodo *nuevoDeporte=crearNodoDeporte(ultimoId,deporte);
                    *listado=agregarNodoAlFinal(*listado,nuevoDeporte);
                    posDeporte=nuevoDeporte;
                    break;

                default:
                    printf("\nOpcion Invalida!, Solo s y n");
                    break;
            }
        }
    }
    if(posDeporte || opcion==115)
    {
        int idSocio=1+buscarUltimoIDSOcioUSado((*listado)->listaSocios);
        printf("\n Ingrese el nombre del socio");
        char nombreSocio[40];
        gets(nombreSocio);
        int edad;
        printf("\nIngrese la edad: ");
        scanf("%d",&edad);
        printf("\nIngrese el valor de la cuota: ");
        float valorCuota;
        scanf("%f",&valorCuota);
        printf("\nIngrese la ultima cuota paga; ");
        int ultimaCuotaPaga;
        scanf("%d",&ultimaCuotaPaga);
        nodo2 *nuevoSocio=crearNodoSocio(idSocio,nombreSocio,ultimaCuotaPaga,valorCuota,edad);
        posDeporte->listaSocios=agregarOrdenadoSocio(posDeporte->listaSocios,nuevoSocio);

    }

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

int buscarUltimoDeporteID(nodo *listado)
{
    int ultimoID=0;

    if(listado)
    {
        nodo *iterador=listado;
        while(listado)
        {
            if(listado->idDeporte>ultimoID)
            {
                ultimoID=listado->idDeporte;
            }
            listado=listado->sig;
        }
    }

    return ultimoID;
}

int buscarUltimoIDSOcioUSado(nodo2 *listaSocios)
{
    int ultimoID=0;

    if(listaSocios)
    {
        nodo2 *iterador=listaSocios;

        while(iterador)
        {
            if(iterador->idSocio>ultimoID)
            {
                ultimoID=iterador->idSocio;
            }
            iterador=iterador->sig;
        }
    }

    return ultimoID;
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

void pasarADosBinarios(nodo *lista, char binarioUno[40],char binarioDos[40])
{
    if(lista)
    {
        nodo *iteradorDeporte=lista;
        FILE *archivoDeportes=fopen(binarioUno,"wb");
        FILE *archivoSocios=fopen(binarioDos,"wb");

        while(iteradorDeporte)
        {
            nodo2 *iteradorSocio=iteradorDeporte->listaSocios;
            stDeporte bufferDeporte;
            bufferDeporte.idDeporte=iteradorDeporte->idDeporte;
            strcpy(bufferDeporte.nombreDeporte,iteradorDeporte->nombreDeporte);

            fwrite(&bufferDeporte,sizeof(stDeporte),1,archivoDeportes);

            while(iteradorSocio)
            {
                stSocio bufferSocio;
                bufferSocio.edad=iteradorSocio->edad;
                bufferSocio.idDeporte=iteradorDeporte->idDeporte;
                bufferSocio.idSocio=iteradorSocio->idSocio;
                bufferSocio.ultimaCuota=iteradorSocio->ultimaCuotaPaga;
                bufferSocio.valorCuota=iteradorSocio->valorCuota;
                strcpy(bufferSocio.nya,iteradorSocio->nya);
                fwrite(&bufferSocio,sizeof(stSocio),1,archivoSocios);
                iteradorSocio=iteradorSocio->sig;
            }
            iteradorDeporte=iteradorDeporte->sig;
        }
        fclose(archivoDeportes);
        fclose(archivoSocios);
    }
}

void pasarDeudores(nodo *lista, char deporte[40],int cuota,stClub arreglo[], int *validos)
{
    if(lista)
    {
        nodo *iteradorDeporte=lista;
        while(iteradorDeporte)
        {
            if(strcmpi(iteradorDeporte->nombreDeporte,deporte)==0)
            {
                stClub itemArreglo;
                itemArreglo.idDeporte=iteradorDeporte->idDeporte;
                strcpy(&itemArreglo.nombreDeporte,iteradorDeporte->nombreDeporte);

                nodo2 *iteradorSocio=iteradorDeporte->listaSocios;

                while(iteradorSocio)
                {
                    if(iteradorSocio->ultimaCuotaPaga<=cuota)
                    {
                        itemArreglo.idSocio=iteradorSocio->idSocio;
                        itemArreglo.edad=iteradorSocio->edad;
                        strcpy(&itemArreglo.nya,iteradorSocio->nya);
                        itemArreglo.ultimaCuotaPaga=iteradorSocio->ultimaCuotaPaga;
                        itemArreglo.valorCuota=iteradorSocio->valorCuota;
                        arreglo[*validos]=itemArreglo;
                        *validos=*validos+1;
                    }

                    iteradorSocio=iteradorSocio->sig;
                }

            }
            iteradorDeporte=iteradorDeporte->sig;
        }
    }
}

void mostrarArregloDeudores(stClub arreglo[], int validos)
{
    printf("\n IDDEPORTE DEPORTE IDSOCIO SOCIO VALOR$ U.CUOTA");
    for(int x=0;x<validos;x++)
    {
        printf("\n %i %s %i %s %0.2f %i",arreglo[x].idDeporte,arreglo[x].nombreDeporte,arreglo[x].idSocio,arreglo[x].nya,arreglo[x].valorCuota,arreglo[x].ultimaCuotaPaga);
    }
}

void borrarTodaLaLista(nodo *listado)
{
    if(listado)
    {
        nodo *iterador=listado;
        nodo *siguiente;

        while(iterador)
        {
            siguiente=iterador->sig;
            free(iterador);
            iterador=siguiente;
        }
    }
}

void ejercicio2(char nombreArchivo[50], nodo **lista)
{
    *lista=pasarALDL(nombreArchivo);


    return lista;
}

void ejercicio3(nodo **lista)
{
    altaManual(lista);
}

void ejercicio4(nodo *lista)
{
    mostrarTodo(lista);
    mostrarDeporteMasPopular(lista);
}


void ejercicio5(nodo *lista, char archivoDeporte[40], char archivoSocio[40])
{
    pasarADosBinarios(lista,archivoDeporte,archivoSocio);
}

void ejercicio6(nodo *lista, stClub arreglo[],int *validos)
{
    int cuota;
    char nombreDeporte[40];

    fflush(stdin);
    printf("\Ingrese el deporte a buscar: ");
    gets(nombreDeporte);
    printf("\nIngrese la cuota limite: ");
    scanf("%d",&cuota);

    pasarDeudores(lista,nombreDeporte,cuota,arreglo,validos);
    mostrarArregloDeudores(arreglo,*validos);
}
