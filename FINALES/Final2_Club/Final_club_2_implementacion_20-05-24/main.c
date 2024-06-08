#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idSocio;
    char nyo[50];
    int UltimaCuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char NombreDeporte[50];
}stCLub;

typedef struct
{
    int idSocio;
    char nya[50];
    int ultimaCuotaPaga;
    int edad;
    struct nodo *siguiente;
}nodo;

typedef struct
{
    int idDeporte;
    char nombreDeporte[50];
    float valorCuota;
    struct nodo *listaSocios;
    struct nodo2 *sig;
    struct nodo2 *ante;
}nodo2;

//EJERCICIO 1
nodo2 *inicNodo2();
nodo2 *crearNodo2(int idDeporte,char nombreDeporte[50],float valorCuota);
nodo2 *insertarNodo2AlFinal(nodo2 *lista,nodo2 *nuevo);
nodo2 *agregarOrdenadoN2(nodo2 *lista,nodo2 *nuevo);
nodo2 *buscarDeporte(nodo2 *lista,char nombreDeporte[50]);

nodo *inicNodo();
nodo *crearNodo(int idSocio,char nya[50],int ultimaCuota,int edad);
nodo *agregarOrdenado(nodo *lista,nodo *nuevo);
nodo *buscarPersona(nodo *lista,char nya[50]);


nodo2 *pasarALDL(char nombreArchivo[80]);

//EJERCICIO 2
void ejercicio2(nodo2 **lista, char nombreArchivo[80]);

//EJERCICIO 3
nodo2 *altaNuevoSocio(nodo2 *lista,nodo *nuevoSocio,int idDeporte,char nombreDeporte[50],float valorCuota);
void ejercicio3(nodo **lista);

//EJERCICIO 4

void mostrarDeporte(nodo2 *deporte);
void mostrarTodo(nodo2 *lista);
void mostrarSocio(nodo *socio);
void mostrarListaSocio(nodo *lista);

void deporteMasPopular(nodo2 *lista);
int contarSocio(nodo *lista);
void ejercicio4(nodo2 *lista);

//EJERCICIO 5
void volcarListasAArchivos(nodo2 *lista,char archivoDeportes[50],char archivoSocios[50]);
void ejercicio5(nodo2 *lista,char archivoSocios[50],char archivoDeportes[50]);

//EJERCICIO 6
stCLub crearStClub(int id,char nyo[50],int ultimaCuota,float valorCuota,int edad,int idDeporte,char nombreDeporte[50]);
void buscarDeudores(nodo2 *lista,stCLub arregloDeudores[],int cuotaTope,int *validos);
void mostrarDeudores(stCLub deudores[],int validos);
void ejercicio6(nodo2 *lista,stCLub deudores[],int cuotasTope,int *validos);

int main()
{
    nodo2 *listaClub=inicNodo2();
    stCLub deudores[1000];
    int validos=0;
    char nombreArchivo[]="registroClub.dat";
    ejercicio2(&listaClub,nombreArchivo);
    //ejercicio3(&listaClub);
    ejercicio4(listaClub);
    ejercicio5(listaClub,"SOCIOS.bin","DEPORTES.bin");
    ejercicio6(listaClub,deudores,10,&validos);

    return 0;
}


nodo2 *inicNodo2()
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
    nuevo->ante=NULL;
    nuevo->sig=NULL;
    return nuevo;
}
nodo2 *insertarNodo2AlFinal(nodo2 *lista,nodo2 *nuevo)
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
        nuevo->ante=iterador;
    }
    return lista;
}

nodo2 *agregarOrdenadoN2(nodo2 *lista,nodo2 *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->nombreDeporte,nuevo->nombreDeporte)>0)
        {
            nuevo->sig=lista;
            lista->ante=nuevo;
            lista=nuevo;
        }
        else
        {
            nodo2 *iterador=lista;
            nodo2 *ante=iterador;
            while(iterador && strcmpi(iterador->nombreDeporte,nuevo->nombreDeporte)<0)
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
    return lista;
}

nodo2 *buscarDeporte(nodo2 *lista,char nombreDeporte[50])
{
    nodo2 *resultado=NULL;
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador && !resultado)
        {
            if(strcmpi(iterador->nombreDeporte,nombreDeporte)==0)
            {
                resultado=iterador;
            }
            iterador=iterador->sig;
        }
    }
    return resultado;
}



nodo *inicNodo()
{
    return NULL;
}

nodo *crearNodo(int idSocio,char nya[50],int ultimaCuota,int edad)
{
    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->idSocio=idSocio;
    strcpy(nuevo->nya,nya);
    nuevo->ultimaCuotaPaga=ultimaCuota;
    nuevo->edad=edad;
    nuevo->siguiente=NULL;
    return nuevo;
}

nodo *agregarOrdenado(nodo *lista,nodo *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->nya,nuevo->nya)>0)
        {
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else
        {
            nodo *iterador=lista;
            nodo *ante=iterador;
            while(iterador && strcmpi(iterador->nya,nuevo->nya)<0)
            {
                ante=iterador;
                iterador=iterador->siguiente;
            }
            if(!iterador)
            {
                ante->siguiente=nuevo;
            }
            else
            {
                ante->siguiente=nuevo;
                nuevo->siguiente=iterador;
            }
        }
    }
    return lista;
}

nodo *buscarPersona(nodo *lista,char nya[50])
{
    nodo *resultado=NULL;
    if(lista)
    {
        nodo *iterador=lista;
        while(iterador && !resultado)
        {
            if(strcmpi(lista->nya,nya)==0)
            {
                resultado=iterador;
            }
            iterador=iterador->siguiente;
        }
    }
    return resultado;
}



nodo2 *pasarALDL(char nombreArchivo[80])
{
    nodo2 *nuevaLista=inicNodo2();
    FILE *archivo=fopen(nombreArchivo,"rb");

    if(archivo)
    {
        stCLub buffer;
        while(fread(&buffer,sizeof(stCLub),1,archivo)>0)
        {
            nodo *nuevoSocio=crearNodo(buffer.idSocio,buffer.nyo,buffer.UltimaCuotaPaga,buffer.edad);

            nodo2 *posDeporte=buscarDeporte(nuevaLista,buffer.NombreDeporte);

            if(!posDeporte)
            {
                nodo2 *nuevoDeporte=crearNodo2(buffer.idDeporte,buffer.NombreDeporte,buffer.valorCuota);
                nuevaLista=insertarNodo2AlFinal(nuevaLista,nuevoDeporte);
                posDeporte=nuevoDeporte;
            }
            posDeporte->listaSocios=agregarOrdenado(posDeporte->listaSocios,nuevoSocio);
            //posDeporte->listaSocios=agregarAlFinalN(posDeporte->listaSocios,nuevoSocio);
        }
        fclose(archivo);
    }
    return nuevaLista;
}

void ejercicio2(nodo2 **lista, char nombreArchivo[80])
{
    *lista=pasarALDL(nombreArchivo);
    mostrarTodo(*lista);
}

//EJERCICIO 3
nodo2 *altaNuevoSocio(nodo2 *lista,nodo *nuevoSocio,int idDeporte,char nombreDeporte[50],float valorCuota)
{
    if(lista)
    {
        nodo2 *posDeporte=buscarDeporte(lista,nombreDeporte);
        if(!posDeporte)
        {
            nodo2 *nuevoDeporte=crearNodo2(idDeporte,nombreDeporte,valorCuota);
            lista=insertarNodo2AlFinal(lista,nuevoDeporte);
            posDeporte=nuevoDeporte;
        }
        posDeporte->listaSocios=agregarOrdenado(posDeporte->listaSocios,nuevoSocio);
    }
    return lista;
}

void ejercicio3(nodo **lista)
{
    int id;
    char nya[50];
    int ultimaCuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char nombreDeporte[50];
    printf("\n Ingrese el ID del socio: ");
    scanf("%d",&id);
    fflush(stdin);
    printf("\nIngrese el nombre y apellido del socio: ");
    gets(nya);

    printf("\nIngrese la ultima cuota paga:");
    scanf("%d",&ultimaCuotaPaga);

    printf("\nIngrese el valor de la cuota: ");
    scanf("%f",&valorCuota);

    printf("\nIngrese la edad: ");
    scanf("%d",&edad);
    fflush(stdin);
    printf("\nIngrese el deporte que realiza: ");
    gets(nombreDeporte);

    printf("\nIngrese el ID del deporte: ");
    scanf("%d",&idDeporte);

    nodo *nuevoSocio=crearNodo(id,nya,ultimaCuotaPaga,edad);

    *lista=altaNuevoSocio(*lista,nuevoSocio,idDeporte,nombreDeporte,valorCuota);
}

void mostrarDeporte(nodo2 *deporte)
{
    printf("\n\n\n ******* ID: %i | TIPO: %12s | VALOR CUOTA: %0.2f*******",deporte->idDeporte,deporte->nombreDeporte,deporte->valorCuota);
}

void mostrarTodo(nodo2 *lista)
{
    if(lista)
    {
        nodo2 *iteradorDeporte=lista;
        while(iteradorDeporte)
        {
            mostrarDeporte(iteradorDeporte);
            nodo *iteradorSocio=iteradorDeporte->listaSocios;
            mostrarListaSocio(iteradorDeporte->listaSocios);
            iteradorDeporte=iteradorDeporte->sig;
        }
    }
}

void mostrarSocio(nodo *socio)
{
    printf("\n ID: %2i NOMBRE: %-20s EDAD: %2i ULTIMA C.PAGA: %2i ",socio->idSocio,socio->nya,socio->edad,socio->ultimaCuotaPaga);
}

void mostrarListaSocio(nodo *lista)
{
    if(lista)
    {
        nodo *iterador=lista;
        while(iterador)
        {
            mostrarSocio(iterador);
            iterador=iterador->siguiente;
        }
    }
}

void deporteMasPopular(nodo2 *lista)
{
    if(lista)
    {
        int maximo=0;
        nodo2 *deportePopular=NULL;
        nodo2 *iteradorDeporte=lista;

        while(iteradorDeporte)
        {
            int contador=contarSocio(iteradorDeporte->listaSocios);
            if(contador>maximo)
            {
                maximo=contador;
                deportePopular=iteradorDeporte;
            }
            iteradorDeporte=iteradorDeporte->sig;
        }
        printf("\n\n\nDeporte mas popular: \n");
        mostrarDeporte(deportePopular);
        mostrarListaSocio(deportePopular->listaSocios);

    }
    else
    {
        printf("\nLa lista esta vacia!");
    }
}

int contarSocio(nodo *lista)
{
    int contador=0;
    if(lista)
    {
        nodo *iterador=lista;
        while(iterador)
        {
            contador++;
            iterador=iterador->siguiente;
        }
    }
    return contador;
}


void ejercicio4(nodo2 *lista)
{
    mostrarTodo(lista);
    deporteMasPopular(lista);
}

//EJERCICIO 5
void volcarListasAArchivos(nodo2 *lista,char archivoDeportes[50],char archivoSocios[50])
{
    if(lista)
    {
        FILE *archivoD=fopen(archivoDeportes,"wb");
        FILE *archivoS=fopen(archivoSocios,"wb");
        nodo2 *iteradorDepo=lista;
        while(iteradorDepo)
        {
            fwrite(iteradorDepo,sizeof(nodo2),1,archivoD);
            nodo *iteradorSocio=iteradorDepo->listaSocios;
            while(iteradorSocio)
            {
                fwrite(iteradorSocio,sizeof(nodo),1,archivoS);
                iteradorSocio=iteradorSocio->siguiente;
            }
            iteradorDepo=iteradorDepo->sig;
        }
        fclose(archivoD);
        fclose(archivoS);
    }
}

void ejercicio5(nodo2 *lista,char archivoSocios[50],char archivoDeportes[50])
{
    volcarListasAArchivos(lista,archivoDeportes,archivoSocios);
}

stCLub crearStClub(int id,char nyo[50],int ultimaCuota,float valorCuota,int edad,int idDeporte,char nombreDeporte[50])
{
    stCLub nuevo;
    nuevo.idSocio=id;
    nuevo.UltimaCuotaPaga=ultimaCuota;
    nuevo.valorCuota=valorCuota;
    nuevo.edad=edad;
    nuevo.idDeporte=idDeporte;
    strcpy(nuevo.nyo,nyo);
    strcpy(nuevo.NombreDeporte,nombreDeporte);
    return nuevo;
}

void buscarDeudores(nodo2 *lista,stCLub arregloDeudores[],int cuotaTope,int *validos)
{
    if(lista)
    {
        nodo2 *iterador=lista;
        while(iterador)
        {
            nodo *iteradorSocio=iterador->listaSocios;
            while(iteradorSocio)
            {
                if(iteradorSocio->ultimaCuotaPaga>cuotaTope)
                {
                    stCLub nuevo=crearStClub(iteradorSocio->idSocio,iteradorSocio->nya,iteradorSocio->ultimaCuotaPaga,iterador->valorCuota,iteradorSocio->edad,iterador->idDeporte,iterador->nombreDeporte);
                    arregloDeudores[*validos]=nuevo;
                    (*validos)++;
                }
                iteradorSocio=iteradorSocio->siguiente;
            }
            iterador=iterador->sig;
        }
    }
}

void mostrarDeudores(stCLub deudores[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        printf("\n IDSOCIO: %i NYA: %s DEPORTE:%s \n",deudores[x].idSocio,deudores[x].nyo,deudores[x].NombreDeporte);
    }
}

void ejercicio6(nodo2 *lista,stCLub deudores[],int cuotasTope,int *validos)
{
    buscarDeudores(lista,deudores,cuotasTope,validos);
    printf("\n\n *******DEUDORES*******\n\n");
    mostrarDeudores(deudores,*validos);
}


