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
}stCLub;

//Punto 1
//{
typedef struct
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    int edad;
    struct nodo *sig;
}nodo;

typedef struct
{
    int idDeporte;
    char nombreDeporte[50];
    float valorCuota;
    nodo *listaSocios;
    struct nodo2 *sig;
    struct nodo2 *ante;
}nodo2;
//}

//Punto 2
//{
nodo *iniciNodo();
nodo *crearNodo(int idSocio,char nya[50],int ultimaCuota,int edad);
nodo *insertarOrdenado(nodo *lista, nodo *nuevo);

nodo2 *inicNodo();
nodo2 *crearNodo2(int idDeporte,char nombreDeporte[50],float valorCuota);
nodo2 *insertarAlFinal(nodo2 *lista, nodo2 *nuevo);
nodo2 *buscarDeporte(nodo2 *lista, char nombreDeporte[50]);

nodo2 *pasarAL2DL(char nombreArchivo[50]);


void punto2(nodo2 **listaDeportes,char nombreArchivo[70]);
//}

//Punto 3
//{
nodo *altaSocio(nodo *lista, int idsocio, char nya[50], int edad, int ultimaCuota);
void ultimoIds(nodo2 *listaDeportes,int *ultimoIDDepo, int *ultimoIDSoc);
void punto3(nodo2 *listaDeportes);
//}

//Punto 4
//{
void mostrarSocio(nodo *socio);
void mostrarSocios(nodo *lista);
void mostrarDeporte(nodo2 *listaDeportes);
void mostrarLDL(nodo2 *listaDeportes);
nodo2 *deporteMasPopular(nodo2 *listaDeportes);
void punto4(nodo2 *listaDeportes);
//}

//Punto 5
//{
void volcarABin(nodo2 *lista,char archivoDep[50],char archivoSoc[50]);
void punto5(nodo2 *lista);
//}

int main()
{
    printf("Hello world!\n");
    return 0;
}

//Punto 2
//{
nodo *iniciNodo()
{
    return NULL;
}

nodo *crearNodo(int idSocio,char nya[50],int ultimaCuota,int edad)
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo2));
    strcpy(nuevo->nya,nya);
    nuevo->edad=edad;
    nuevo->idSocio=idSocio;
    nuevo->ultimaCuotaPaga=ultimaCuota;
    nuevo->sig=NULL;

    return nuevo;
}

nodo *insertarOrdenado(nodo *lista, nodo *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo *ante=NULL;
        nodo *iterador=lista;
        while(iterador && strcmpi(lista->nya,nuevo->nya)>=0)
        {
            ante=iterador;
            iterador=iterador->sig;
        }
        ante->sig=nuevo;
        if(iterador)
        {
            nuevo->sig=iterador;
        }
    }
    return lista;
}

nodo2 *inicNodo()
{
    return NULL;
}

nodo2 *crearNodo2(int idDeporte,char nombreDeporte[50],float valorCuota)
{
    nodo2 *nuevo=(nodo2*)malloc(sizeof(nodo2));
    nuevo->idDeporte=idDeporte;
    strcpy(nuevo->nombreDeporte,nombreDeporte);
    nuevo->valorCuota=valorCuota;
    nuevo->listaSocios=NULL;

    return nuevo;
}

nodo2 *insertarAlFinal(nodo2 *lista, nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo2 *iterador=lista;
        while(iterador->sig)
        {
            iterador=iterador->sig;
        }
        iterador->sig=nuevo;
    }
    return lista;
}

nodo2 *buscarDeporte(nodo2 *lista, char nombreDeporte[50])
{
    nodo2 *ubicacion=NULL;
    if(lista)
    {
        nodo2 *iterador=lista;
        {
            while(!ubicacion && iterador)
            {
                if(strcmpi(iterador->nombreDeporte,nombreDeporte)==0)
                {
                    ubicacion=iterador;
                }
                iterador=iterador->sig;
            }
        }
    }

    return ubicacion;
}

nodo2 *pasarAL2DL(char nombreArchivo[50])
{
    nodo2 *resultante=NULL;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        stCLub buffer;
        while(fread(&buffer,sizeof(stCLub),1,archivo)>0)
        {
            nodo *socio=crearNodo(buffer.idSocio,buffer.nya,buffer.ultimaCuotaPaga,buffer.edad);
            nodo2 *posDeporte=buscarDeporte(resultante,buffer.nombreDeporte);
            if(!posDeporte)
            {
                nodo2 *deporte=crearNodo2(buffer.idDeporte,buffer.nombreDeporte,buffer.valorCuota);
                resultante=insertarAlFinal(resultante,deporte);
                posDeporte=deporte;
            }
            posDeporte->listaSocios=insertarOrdenado(posDeporte->listaSocios,socio);

        }

        fclose(archivo);
    }
    return resultante;
}


void punto2(nodo2 **listaDeportes,char nombreArchivo[70])
{
    *listaDeportes=pasarAL2DL(nombreArchivo);
}
//}


//Punto 3
//{
nodo *altaSocio(nodo *lista, int idsocio, char nya[50], int edad, int ultimaCuota)
{
    nodo *nuevoSocio=crearNodo(idsocio,nya,edad,ultimaCuota);
    lista=insertarOrdenado(lista,nuevoSocio);

    return lista;
}

void ultimoIds(nodo2 *listaDeportes,int *ultimoIDDepo, int *ultimoIDSoc)
{
    nodo2 *iterador=listaDeportes;
    while(iterador)
    {
        nodo *itSocios=iterador->listaSocios;
        while(itSocios)
        {
            if(itSocios->idSocio > *ultimoIDSoc)
            {
                *ultimoIDSoc=itSocios->idSocio;
            }
            itSocios=itSocios->sig;
        }
        if(iterador->idDeporte > *ultimoIDDepo)
        {
            ultimoIDDepo=iterador->idDeporte;
        }
        iterador=iterador->sig;
    }
}

void punto3(nodo2 *listaDeportes)
{
    char nya[50];
    char nombreDeporte[50];
    int idSocio;
    float valorCuota;
    int edad;
    int idDeporte;

    int ultimoIDDepo=0;
    int ultimoIDSoc=0;
    ultimoIds(listaDeportes,&ultimoIDDepo,&ultimoIDSoc);

    printf("Ingrese el nombre del socio: ");
    gets(nya);
    printf("Ingrese la edad: ");
    scanf("%d",&edad);
    printf("Ingrese el deporte que practica: ");
    gets(nombreDeporte);
    nodo *nuevoSocio=crearNodo(ultimoIDSoc+1,nya,0,edad);//Cuota 0, se asume que aun no pago ninguna por ser nuevo.
    nodo2 *posDeporte=buscarDeporte(listaDeportes,nombreDeporte);
    if(!posDeporte)
    {
        printf("El deporte no existe, se solicitaran datos adicionales para darlo de alta\n");
        printf("Ingrese el valor de la cuota: ");
        scanf("%f",&valorCuota);
        nodo2 *nuevoDeporte=crearNodo2(ultimoIDDepo+1,nombreDeporte,valorCuota);
        listaDeportes=insertarAlFinal(listaDeportes,nuevoDeporte);
        posDeporte=nuevoDeporte;
    }
    posDeporte->listaSocios=insertarOrdenado(posDeporte->listaSocios,nuevoSocio);
}
//}


//Punto 4
//{
void mostrarSocio(nodo *socio)
{
    printf("ID: %i NYA: %s EDAD: %i ULTIMA CUOTA PAGA: %i \n ",socio->idSocio,socio->nya,socio->edad,socio->ultimaCuotaPaga);
}

void mostrarSocios(nodo *lista)
{
    if(lista)
    {
        nodo *iterador=lista;
        while(iterador)
        {
            mostrarSocio(iterador);
        }
    }
}

void mostrarDeporte(nodo2 *listaDeportes)
{
    printf("**********\n");
    printf("IDDEPORTE: %i DEPORTE: %s VALOR CUOTA: %0.2f \n",listaDeportes->idDeporte,listaDeportes->nombreDeporte,listaDeportes->valorCuota);
    printf("**********\n");
}
void mostrarLDL(nodo2 *listaDeportes)
{
    if(listaDeportes)
    {
        nodo2 *iterador=listaDeportes;
        while(iterador)
        {
            mostrarDeporte(iterador);
            mostrarSocios(iterador->listaSocios);
        }
    }
}
nodo2 *deporteMasPopular(nodo2 *listaDeportes)
{
    nodo2 *masPopular=NULL;
    if(listaDeportes)
    {
        int maxPopular=0;
        int contador=0;
        nodo2 *iterador=listaDeportes;
        while(iterador)
        {
            nodo *iterSocio=iterador->listaSocios;
            while(iterSocio)
            {
                contador++;
                iterSocio=iterSocio->sig;
            }
            if(contador>maxPopular)
            {
                maxPopular=contador;
                masPopular=iterador;
                contador=0;
            }
            iterador=iterador->sig;
        }
    }
    return masPopular;
}
void punto4(nodo2 *listaDeportes)
{
    mostrarLDL(listaDeportes);
    nodo2 *masPopular=deporteMasPopular(listaDeportes);
    if(masPopular)
    {
        printf("El deporte mas popular es ID: %i %s \n",masPopular->idDeporte,masPopular->nombreDeporte);
    }
}
//}


//Punto 5
//{
void volcarABin(nodo2 *lista,char archivoDep[50],char archivoSoc[50])
{
    if(lista)
    {
        nodo2 *iterador=lista;

    }
}
void punto5(nodo2 *lista);
//}

