#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char provincia[30];
    char partido[30];
    int cant_votos;
}RecuentoVotos;

typedef struct nodoProvincia
{
    char provincia[30];
    struct nodoPartido *partido;
    struct nodoProvincia *sig;
}nodoProvincia;

typedef struct nodoPartido
{
    char partido[30];
    int cant_votos;
    struct nodoPartido *sig;
}nodoPartido;

typedef struct
{
    char provincia[30];
    int votos_Totales;
}VotosProvincia;

typedef struct
{
    VotosProvincia v;
    struct VotosXProvincia *ante;
    struct VotosXProvincia *sig;
}VotosXProvincia;
// Punto 1
//{
nodoProvincia *crearProvincia(char provincia[30]);
nodoProvincia *insertarOrdProv(nodoProvincia *lista,nodoProvincia *nuevo);
nodoProvincia *buscarProv(nodoProvincia *lista,char nombreProv[30]);

nodoPartido *crearPartido(char partido[30],int cant_votos);
nodoPartido *insertarOrdPart(nodoPartido *lista,nodoPartido *nuevo);

nodoProvincia *pasarALDL(char nombreArchivo[50]);

void punto1(nodoProvincia **lista,char nombreArchivo[50]);
//}


// Punto 2
//{
VotosXProvincia *totales(VotosXProvincia *resultante,nodoProvincia *lista,nodoPartido *listaPartido,int sumaVotos);
void punto2(nodoProvincia *lista, VotosXProvincia **listaResumen);
//}

// Punto 3
//{
VotosXProvincia *borrarProvincia(VotosXProvincia *lista,char nombreProv[30]);
void punto3(VotosXProvincia **lista,char nombreProv[30]);
//}

// AUX
//OPCIONAL, NO FORMA PARTE DEL EJERCICIO, SOLO SIRVE PARA EVALUAR LA SOLUCION.
//{
void mostrarLDL(nodoProvincia *listaProv);
void mostrarListaP(nodoPartido *listapart);

void mostrarLDL2(VotosXProvincia *listaProv2);    //Muestra la lista de votos por provincia
void mostrarLDL2Inv(VotosXProvincia *listaProv2); //Muestra la lista de votos por provincia invertido

//}
int main()
{
    char nombreArchivo[50]="votos.bin";
    nodoProvincia *lista=NULL;
    punto1(&lista,nombreArchivo);
    VotosXProvincia *listaResumen=NULL;
    punto2(lista,&listaResumen);
    //punto3(&listaResumen,"tierra del fuego");
    mostrarLDL2(listaResumen);
    mostrarLDL2Inv(listaResumen);
    return 0;
}

// Punto 1
//{
nodoProvincia *crearProvincia(char provincia[30])
{
    nodoProvincia *nuevo=(nodoProvincia*)malloc(sizeof(nodoProvincia));
    strcpy(nuevo->provincia,provincia);
    nuevo->sig=NULL;
    nuevo->partido=NULL;
    return nuevo;
}

nodoProvincia *insertarOrdProv(nodoProvincia *lista,nodoProvincia *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->provincia,nuevo->provincia)>=0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodoProvincia *iterador=lista->sig;
            nodoProvincia *ante=lista;
            while(iterador && strcmpi(iterador->provincia,nuevo->provincia)<=0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->sig=iterador;
        }
    }
    return lista;
}

nodoProvincia *buscarProv(nodoProvincia *lista,char nombreProv[30])
{
    nodoProvincia *resultante=NULL;
    if(lista)
    {
        nodoProvincia *iterador=lista;
        while(iterador && !resultante)
        {
            if(strcmpi(iterador->provincia,nombreProv)==0)
            {
                resultante=iterador;
            }
            iterador=iterador->sig;
        }
    }
    return resultante;
}

nodoPartido *crearPartido(char partido[30],int cant_votos)
{
    nodoPartido *nuevo=(nodoPartido*)malloc(sizeof(nodoPartido));
    strcpy(nuevo->partido,partido);
    nuevo->cant_votos=cant_votos;
    nuevo->sig=NULL;
    return nuevo;
}
nodoPartido *insertarOrdPart(nodoPartido *lista,nodoPartido *nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        if(strcmpi(lista->partido,nuevo->partido)>0)
        {
            nuevo->sig=lista;
            lista=nuevo;
        }
        else
        {
            nodoPartido *iterador=lista;
            nodoPartido *ante;
            while(iterador && strcmpi(iterador->partido,nuevo->partido)<0)
            {
                ante=iterador;
                iterador=iterador->sig;
            }
            ante->sig=nuevo;
            nuevo->sig=iterador;

        }
    }
    return lista;
}

nodoProvincia *pasarALDL(char nombreArchivo[50])
{
    nodoProvincia *listaNueva=NULL;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        RecuentoVotos buffer;
        while(fread(&buffer,sizeof(RecuentoVotos),1,archivo)>0)
        {
            nodoPartido *nuevoPartido=crearPartido(buffer.partido,buffer.cant_votos);
            nodoProvincia *posicion=buscarProv(listaNueva,buffer.provincia);
            if(!posicion)
            {
                nodoProvincia *nuevaProvincia=crearProvincia(buffer.provincia);
                listaNueva=insertarOrdProv(listaNueva,nuevaProvincia);
                posicion=nuevaProvincia;
            }
            posicion->partido=insertarOrdPart(posicion->partido,nuevoPartido);
        }
        fclose(archivo);
    }
    else
    {
        printf("No se encontro el archivo! \n");
    }
    return listaNueva;
}

void punto1(nodoProvincia **lista,char nombreArchivo[50])
{
    *lista=pasarALDL(nombreArchivo);
}
//}

// Punto 2
//{
VotosXProvincia *totales(VotosXProvincia *resultante,nodoProvincia *lista,nodoPartido *listaPartido,int sumaVotos)
{
    if(lista)
    {
        if(listaPartido)
        {
            sumaVotos=sumaVotos + listaPartido->cant_votos;
            resultante=totales(resultante,lista,listaPartido->sig,sumaVotos);
            printf("Votos %i \n",listaPartido->cant_votos);
        }
        else
        {
            VotosXProvincia *nuevo=(VotosXProvincia*)malloc(sizeof(VotosXProvincia));
            strcpy(nuevo->v.provincia,lista->provincia);
            nuevo->v.votos_Totales=sumaVotos;
            nuevo->ante=resultante;
            nuevo->sig=NULL;
            resultante=nuevo;

            if(lista->sig)
            {
                lista=lista->sig;
                resultante->sig=totales(resultante,lista,lista->partido,0);
                //nodoProvincia *aux=lista->sig;
                //resultante->sig=totales(resultante,aux,aux->partido,0);
            }
        }
    }
    return resultante;
}

void punto2(nodoProvincia *lista, VotosXProvincia **listaResumen)
{
    *listaResumen=totales(*listaResumen,lista,lista->partido,0);
}
//}

// Punto 3
//{
VotosXProvincia *borrarProvincia(VotosXProvincia *lista,char nombreProv[30])
{
    if(lista)
    {
        if(strcmpi(lista->v.provincia,nombreProv)==0)
        {
            VotosXProvincia *sig=lista->sig;
            free(lista);
            lista=sig;
        }
        else
        {

            VotosXProvincia *iterador=lista;
            VotosXProvincia *ante;
            while(iterador)
            {
                printf("Provincia: %s \n",iterador->v.provincia);
                if(strcmpi(iterador->v.provincia,nombreProv)==0)
                {
                    ante->sig=iterador->sig;
                    free(iterador);
                    iterador=ante;
                    if(iterador->sig)
                    {
                        VotosXProvincia *aux=iterador->sig;
                        aux->ante=iterador;
                    }
                }
                ante=iterador;
                iterador=iterador->sig;
            }
        }
    }
    return lista;
}
void punto3(VotosXProvincia **lista,char nombreProv[30])
{
    *lista=borrarProvincia(*lista,nombreProv);
}
//}

// AUX
//{
void mostrarLDL(nodoProvincia *listaProv)
{
    if(listaProv)
    {
        nodoProvincia *iterador=listaProv;
        while(iterador)
        {
            printf("\n\n PROVINCIA %s \n",iterador->provincia);
            mostrarListaP(iterador->partido);
            iterador=iterador->sig;
        }
    }
}
void mostrarListaP(nodoPartido *listapart)
{
    if(listapart)
    {
        nodoPartido *iterador=listapart;
        while(iterador)
        {
            printf(" Partido: %s Votos: %i \n",iterador->partido,iterador->cant_votos);
            iterador=iterador->sig;
        }
    }
}

void mostrarLDL2(VotosXProvincia *listaProv2)
{
    if(listaProv2)
    {
        VotosXProvincia *iterador=listaProv2;
        while(iterador)
        {
            printf(" Provincia: %-20s Recuento: %i \n",iterador->v.provincia,iterador->v.votos_Totales);
            iterador=iterador->sig;
        }
    }
}

void mostrarLDL2Inv(VotosXProvincia *listaProv2)
{
    if(listaProv2)
    {
        VotosXProvincia *iteradorInv=listaProv2;
        while(iteradorInv->sig)
        {
            iteradorInv=iteradorInv->sig;
        }
        while(iteradorInv)
        {
            printf("[INV] Provincia: %-20s Recuento: %i \n",iteradorInv->v.provincia,iteradorInv->v.votos_Totales);
            iteradorInv=iteradorInv->ante;
        }
    }
}

//}
