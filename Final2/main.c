#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int idSocio;
    char nya[50];
    int UltimaCuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char NombreDeporte[50];
}stClub;

typedef struct{
    float valorCuota;
    int idDeporte;
    char nombreDeporte[50];
}deporte;

typedef struct{
    int idSocio;
    char nya[50];
    int UltimaCuotaPaga;
    int edad;
}socio;

typedef struct{
    socio s;
    struct listaSocios *sig;
}listaSocios;

typedef struct{
    deporte d;
    listaSocios *listadoSocios;
    struct listaDeportes *ant;
    struct listaDeportes *sig;
}listaDeportes;

listaDeportes *inicListaDeportes();
listaDeportes *archivoToLista(listaDeportes *lista);
listaDeportes *ingresarDeporteManual(listaDeportes *lista);

int main()
{
    //EJ 2
    listaDeportes *listaDeTodosLosDeportes = inicListaDeportes();
    listaDeTodosLosDeportes = archivoToLista(listaDeTodosLosDeportes);
    //EJ 3
    //listaDeTodosLosDeportes = ingresarDeporteManual(listaDeTodosLosDeportes);
    //EJ 4
    //mostrarListaDeportes(listaDeTodosLosDeportes);
    //listarDeporteConMasSocios(listaDeTodosLosDeportes);
    //EJ 5
    //listaToArchivos(listaDeTodosLosDeportes);
    //mostrarArchivoDeportes();
    //mostrarArchivoSocios();
    //EJ 6
    stClub arreglo[50];
    int validos = 0;
    validos = listaToArreglo(listaDeTodosLosDeportes, arreglo, "futbol", 7);
    mostrarArregloStClub(arreglo, validos);


    return 0;
}

listaDeportes *inicListaDeportes(){
    return NULL;
}

listaSocios *inicListaSocios(){
    return NULL;
}

deporte crearDeporte(int id, float valorCuota, char nombre[]){
    deporte aux;

    strcpy(aux.nombreDeporte, nombre);
    aux.idDeporte = id;
    aux.valorCuota = valorCuota;

    return aux;
}

listaDeportes *crearNodoDeporte(deporte d){
    listaDeportes *nueva = (listaDeportes*)malloc(sizeof(listaDeportes));

    nueva->d = d;
    nueva->listadoSocios = inicListaSocios();
    nueva->ant = NULL;
    nueva->sig = NULL;

    return nueva;
}

listaDeportes *buscarUltimo(listaDeportes *lista){
    listaDeportes *ultimo = lista;

    if(ultimo){
        while(ultimo->sig){
            ultimo = ultimo->sig;
        }
    }
    return ultimo;
}

listaDeportes *agregarAlFinal(listaDeportes *lista, listaDeportes *nueva){
    listaDeportes *ultimo = NULL;
    if(!lista){
        lista = nueva;
    }else{
        ultimo = buscarUltimo(lista);
        ultimo->sig = nueva;
        nueva->ant = ultimo;
    }
    return lista;
}

socio crearSocio(int id, char nombreyape[], int ultimaCuota, int edad){
    socio aux;

    aux.idSocio = id;
    aux.edad = edad;
    aux.UltimaCuotaPaga = ultimaCuota;
    strcpy(aux.nya, nombreyape);

    return aux;
}

listaSocios *crearNodoSocio(socio s){
    listaSocios *nuevo = (listaSocios*)malloc(sizeof(listaSocios));

    nuevo->s = s;
    nuevo->sig = NULL;

    return nuevo;
}

listaSocios *agregarAlPrincipio(listaSocios *lista, listaSocios *nuevo){
    if(lista){
        nuevo->sig = lista;
    }
    lista = nuevo;
    return lista;
}

listaSocios *agregarEnOrden(listaSocios *lista, listaSocios *nuevo){
    if(!lista){
        lista = nuevo;
    }else if(strcmpi(nuevo->s.nya, lista->s.nya) < 0){
        lista = agregarAlPrincipio(lista, nuevo);
    }else{
        listaSocios *ant = lista;
        listaSocios *seg = lista->sig;

        while(seg != NULL && strcmpi(nuevo->s.nya, seg->s.nya) > 0){
            ant = seg;
            seg = seg->sig;
        }

        ant->sig = nuevo;
        nuevo->sig = seg;
    }
    return lista;
}

listaDeportes *buscarDeporte(listaDeportes *lista, char deporte[]){
    listaDeportes *deporteBuscado = NULL;
    listaDeportes *seg = lista;

    while(seg){
        if(strcmpi(seg->d.nombreDeporte, deporte) == 0){
            deporteBuscado = seg;
            break;
        }
        seg = seg->sig;
    }
    return deporteBuscado;
}

listaDeportes *alta(listaDeportes *lista, socio s, deporte d){
    listaDeportes *buscado = buscarDeporte(lista, d.nombreDeporte);
    listaSocios *nuevo = crearNodoSocio(s);
    if(!buscado){
        listaDeportes *nuevoDeporte = crearNodoDeporte(d);
        lista = agregarAlFinal(lista, nuevoDeporte);
        nuevoDeporte->listadoSocios = agregarEnOrden(nuevoDeporte->listadoSocios, nuevo);
    }else{
        buscado->listadoSocios = agregarEnOrden(buscado->listadoSocios, nuevo);
    }
    return lista;
}

listaDeportes *archivoToLista(listaDeportes *lista){
    FILE *buf = fopen("registroClub.dat", "rb");
    stClub aux;

    if(!buf){
        printf("\nEL ARCHIVO NO SE PUEDE ABRIR.\n");
    }else{
        while(fread(&aux, sizeof(stClub), 1, buf) > 0){
            deporte d = crearDeporte(aux.idDeporte, aux.valorCuota, aux.NombreDeporte);
            socio s = crearSocio(aux.idSocio, aux.nya, aux.UltimaCuotaPaga, aux.edad);
            lista = alta(lista, s, d);
        }
        fclose(buf);
    }
    return lista;
}

//EJ 3

socio cargarSocioManual(){
    socio nuevo;

    printf("\nNOMBRE y APELLIDO SOCIO: ");
    fflush(stdin);
    gets(&nuevo.nya);
    printf("\nEDAD: ");
    fflush(stdin);
    scanf("%i", &nuevo.edad);
    printf("\nULTIMA CUOTA PAGA: ");
    fflush(stdin);
    scanf("%i", &nuevo.UltimaCuotaPaga);
    printf("\nID: ");
    fflush(stdin);
    scanf("%i", &nuevo.idSocio);

    return nuevo;
}

listaDeportes *ingresarDeporteManual(listaDeportes *lista){
    char aux[50];
    int num;
    deporte d;

    socio nuevo = cargarSocioManual();

    printf("INGRESE EL DEPORTE DEL SOCIO: ");
    fflush(stdin);
    scanf("%s", &d.nombreDeporte);

    listaDeportes *nuevoDeporte = buscarDeporte(lista, d.nombreDeporte);
    if(!nuevoDeporte){
        printf("\nEL DEPORTE INGRESADO NO SE ENCUENTRA EN LA BASE DE DATOS... \nCARGUELO A CONTINUACION:");

        printf("\n\nNOMBRE DEPORTE INGRESADO: %s", d.nombreDeporte);
        printf("\nID: ");
        fflush(stdin);
        scanf("%i", &d.idDeporte);

        printf("\nVALOR CUOTA: ");
        fflush(stdin);
        scanf("%f", &d.valorCuota);
    }else{
        d = crearDeporte(nuevoDeporte->d.idDeporte, nuevoDeporte->d.valorCuota, d.nombreDeporte);
    }
    lista = alta(lista, nuevo, d);

    return lista;
}


//EJ 4

void mostrarUnSocio(socio s){
    printf("\n----------------------------------------------");
    printf("\nNOMBRE Y APELLIDO: %s", s.nya);
    printf("\n         ID SOCIO: %i", s.idSocio);
    printf("\n             EDAD: %i", s.edad);
    printf("\nULTIMA CUOTA PAGA: %i", s.UltimaCuotaPaga);
    printf("\n----------------------------------------------\n");
}
void mostrarUnDeporte(deporte d){
    printf("\n----------------------------------------------");
    printf("\n----------------> DEPORTE: %s", d.nombreDeporte);
    printf("\n---------------------> ID: %i", d.idDeporte);
    printf("\n------------> VALOR CUOTA: %.2f", d.valorCuota);
    printf("\n----------------------------------------------\n");
}

void mostrarListaSocios(listaSocios *lista){
    listaSocios *seg = lista;

    while(seg){
        mostrarUnSocio(seg->s);
        seg = seg->sig;
    }
}

void mostrarListaDeportes(listaDeportes *lista){
    listaDeportes *seg = lista;

    while(seg){
        mostrarUnDeporte(seg->d);
        mostrarListaSocios(seg->listadoSocios);
        seg = seg->sig;
    }
}

int contarSociosDeporte(listaSocios *lista){
    int contador = 0;

    while(lista){
        contador++;
        lista = lista->sig;
    }
    return contador;
}

listaDeportes *buscarDeporteConMasSocios(listaDeportes *lista){
    int mayorActual = 0, mayor = 0;
    listaDeportes *seg = lista;
    listaDeportes *deporteConMasSocios = NULL;

    while(seg){
        mayorActual = contarSociosDeporte(seg->listadoSocios);
        if(mayorActual > mayor){
            mayor = mayorActual;
            deporteConMasSocios = seg;
        }
        seg = seg->sig;
    }
    return deporteConMasSocios;
}

void listarDeporteConMasSocios(listaDeportes *lista){
    listaDeportes *deporteMayor = buscarDeporteConMasSocios(lista);
    mostrarUnDeporte(deporteMayor->d);
    mostrarListaSocios(deporteMayor->listadoSocios);
}

//EJ 5

void listaToArchivos(listaDeportes *lista){
    FILE *bufd = fopen("archivoDeportes", "ab");
    FILE *bufs = fopen("archivoSocios", "ab");
    deporte auxDeporte;
    socio auxSocio;

    listaDeportes *seg = lista;

    while(seg){
        auxDeporte = seg->d;
        fwrite(&auxDeporte, sizeof(deporte), 1, bufd);

        while(seg->listadoSocios){
            auxSocio = seg->listadoSocios->s;
            fwrite(&auxSocio, sizeof(socio), 1, bufs);
            seg->listadoSocios = seg->listadoSocios->sig;
        }
        seg = seg->sig;
    }
    fclose(bufd);
    fclose(bufs);
}

void mostrarArchivoDeportes(){
    FILE *buf = fopen("archivoDeportes", "rb");
    deporte aux;

    if(!buf){
        printf("\nEL ARCHIVO NO SE PUEDE ABRIR.\n");
    }else{
        while(fread(&aux, sizeof(deporte), 1, buf) > 0){
            mostrarUnDeporte(aux);
        }
        fclose(buf);
    }
}

void mostrarArchivoSocios(){
    FILE *buf = fopen("archivoSocios", "rb");
    socio aux;

    if(!buf){
        printf("\nEL ARCHIVO NO SE PUEDE ABRIR.\n");
    }else{
        while(fread(&aux, sizeof(socio), 1, buf) > 0){
            mostrarUnSocio(aux);
        }
        fclose(buf);
    }
}

//EJ 6

stClub crearstClub(socio s, deporte d){
    stClub aux;

    aux.idSocio = s.idSocio;
    strcpy(aux.nya, s.nya);
    aux.UltimaCuotaPaga = s.UltimaCuotaPaga;
    aux.valorCuota = d.valorCuota;
    aux.edad = s.edad;
    aux.idDeporte = d.idDeporte;
    strcpy(aux.NombreDeporte, d.nombreDeporte);

    return aux;
}

int listaToArreglo(listaDeportes *lista, stClub arreglo[], char deporte[], int mes){
    int i=0, u=0;
    listaDeportes *seg = lista;
    int validos = 0;

    while(seg){
        if(strcmpi(seg->d.nombreDeporte, deporte) == 0){
            while(seg->listadoSocios){
                if(seg->listadoSocios->s.UltimaCuotaPaga < mes){
                    stClub aux = crearstClub(seg->listadoSocios->s, seg->d);
                    arreglo[i] = aux;
                    i++;
                    validos = i;
                }
                seg->listadoSocios = seg->listadoSocios->sig;
            }
        }
        seg = seg->sig;
    }
    return validos;
}

void mostrarUnStClub(stClub s){
    printf("\n----------------------------------------------");
    printf("\n        NOMBRE Y APELLIDO: %s", s.nya);
    printf("\n                 ID SOCIO: %i", s.idSocio);
    printf("\n                     EDAD: %i", s.edad);
    printf("\n        ULTIMA CUOTA PAGA: %i", s.UltimaCuotaPaga);
    printf("\n----------------> DEPORTE: %s", s.NombreDeporte);
    printf("\n---------------------> ID: %i", s.idDeporte);
    printf("\n------------> VALOR CUOTA: %.2f", s.valorCuota);
    printf("\n----------------------------------------------\n");
}

void mostrarArregloStClub(stClub arreglo[], int validos){
    for(int i=0; i<validos; i++){
        mostrarUnStClub(arreglo[i]);
    }
}

