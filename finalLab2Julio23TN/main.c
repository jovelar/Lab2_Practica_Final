#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int idSocio;
    char nya[50];
    int ultimacuotaPaga;
    float valorCuota;
    int edad;
    int idDeporte;
    char nombreDeporte[50];

}stClub;

typedef struct{
    int idSocio;
    char nya[50];
    int edad;
    int ultimaCuotaPaga;
}stSocio;

typedef struct{
    int idDeporte;
    char nombreDeporte[50];
    float valorCuota;
}stDeporte;

typedef struct{
    stSocio socio;
    struct nodo2* ant;
    struct nodo2* sig;
}nodo2;

typedef struct{
    stDeporte deporte;
    nodo2* listaDeSocios;
    struct nodo* sig;
}nodo;

nodo* inicLista(){
    return NULL;
}

nodo2* inicListaDoble(){
    return NULL;
}

stSocio crearSocio(stClub reg){
    stSocio socio;
    socio.idSocio = reg.idSocio;
    strcpy(socio.nya, reg.nya);
    socio.edad = reg.edad;
    socio.ultimaCuotaPaga = reg.ultimacuotaPaga;
    return socio;
}

stDeporte crearDeporte(stClub reg){
    stDeporte deporte;
    deporte.idDeporte = reg.idDeporte;
    strcpy(deporte.nombreDeporte, reg.nombreDeporte);
    deporte.valorCuota = reg.valorCuota;
    return deporte;
}

nodo2* crearNodoDoble(stSocio socio){

    nodo2* nuevo = (nodo2*) malloc(sizeof(nodo2));
    nuevo->socio = socio;
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

nodo* crearNodo(stDeporte deporte){
    nodo* nuevo = (nodo*) malloc(sizeof(nodo));
    nuevo->deporte = deporte;
    nuevo->listaDeSocios = inicListaDoble();
    nuevo->sig = NULL;
    return nuevo;
}

nodo2* insertarOrdXNombre(nodo2* listaD, nodo2* nuevo){
    if (listaD == NULL){
        listaD = nuevo;
    }else{
        if (strcmpi(nuevo->socio.nya, listaD->socio.nya)<0){
            nuevo->sig = listaD;
            listaD->ant = nuevo;
            listaD = nuevo;
        }else{
            nodo2* aux = listaD;
            nodo2* seg = listaD->sig;
            while (seg != NULL && strcmpi(nuevo->socio.nya, listaD->socio.nya)>0){
                aux = seg;
                seg = seg->sig;
            }
            aux->sig = nuevo;
            nuevo->ant = aux;
            if (seg != NULL){
                nuevo->sig = seg;
                seg->ant = nuevo;
            }
        }
    }
    return listaD;

}

nodo* insertarAlPpio(nodo* lista, nodo* nuevo){
    if (lista == NULL){
        lista = nuevo;
    }else{
        nuevo->sig = lista;
        lista = nuevo;
    }
    return lista;
}

nodo* buscarDeporte(nodo* lista, int idDeporte){
    nodo* aux = lista;
    while (aux != NULL && aux->deporte.idDeporte != idDeporte){
        aux = aux->sig;
    }
    return aux;
}

nodo* insertarEnLista(nodo* lista, stClub reg){
    stSocio socio = crearSocio(reg);
    nodo2* nuevoD = crearNodoDoble(socio);
    nodo* pos = buscarDeporte(lista, reg.idDeporte);
    if (pos == NULL){
        stDeporte deporte = crearDeporte(reg);
        nodo* nuevo = crearNodo(deporte);
        nuevo->listaDeSocios = insertarOrdXNombre(nuevo->listaDeSocios, nuevoD);
        lista = insertarAlPpio(lista, nuevo);
    }else{
        pos->listaDeSocios = insertarOrdXNombre(pos->listaDeSocios, nuevoD);
    }
    return lista;
}

nodo* pasarArchALista(nodo* lista){

    FILE* fp;
    stClub reg;
    fp = fopen("registroClub.dat", "rb");
    if (fp != NULL){
        while (fread(&reg, sizeof(stClub), 1, fp)>0){
            lista = insertarEnLista(lista, reg);
        }
        fclose(fp);
    }
    return lista;
}
///3. Realizar las funciones necesarias para que el empleado administrativo del club pueda realizar
///el ALTA Manual de socios del club y disciplinas deportivas que realiza.
///a. Tiene que trabajar directamente sobre la lista de listas.
nodo* altaSocio(nodo* lista){
    stSocio socio;
    stDeporte deporte;
    printf("Ingrese los datos del socio: \n");
    printf("Id del socio: ");
    fflush(stdin);
    scanf("%i", &socio.idSocio);
    printf("Nombre y Apellido: ");
    fflush(stdin);
    gets(socio.nya);
    printf("Edad: ");
    fflush(stdin);
    scanf("%i", &socio.edad);
    printf("Ultima cuota paga: ");
    fflush(stdin);
    scanf("%i", &socio.ultimaCuotaPaga);
    printf("Id deporte: ");
    fflush(stdin);
    scanf("%i", &deporte.idDeporte);
    printf("...\n");
    nodo* pos = buscarDeporte(lista, deporte.idDeporte);
    nodo2* nuevoD = crearNodoDoble(socio);
    if (pos == NULL){
        nodo* nuevo = crearNodo(deporte);
        nuevo->listaDeSocios = insertarOrdXNombre(nuevo->listaDeSocios, nuevoD);
        lista = insertarAlPpio(lista, nuevo);
    }else{
        strcpy(deporte.nombreDeporte, pos->deporte.nombreDeporte);
        deporte.valorCuota = pos->deporte.valorCuota;
        pos->listaDeSocios = insertarOrdXNombre(pos->listaDeSocios, nuevoD);
    }
    return lista;

}
int contarSocios(nodo2* listaD){
    int cont=0;
    while (listaD != NULL){
        cont++;
        listaD = listaD->sig;
    }
    return cont;

}
nodo* deporteConMasSocios(nodo* lista){
    int mayor, cont;
    nodo* aux;
    if (lista != NULL){
        mayor = contarSocios(lista->listaDeSocios);
        aux = lista;
    }
    nodo* seg=lista->sig;
    while (seg != NULL){
        cont= contarSocios(seg->listaDeSocios);
        if (cont>mayor){
            mayor = contarSocios(seg->listaDeSocios);
            aux = seg;
        }
        seg = seg->sig;
    }
    return aux;
}
void crearArchivosSocios(nodo2* listaD){

    FILE* fp= fopen("socios.dat", "ab");
    while (listaD != NULL){
        fwrite(&listaD->socio, sizeof(stSocio), 1, fp);
        listaD = listaD->sig;
    }
    fclose(fp);
}
void crearArchivosDeportes(nodo* lista){
    FILE* arch1;
    FILE* arch2;
    arch1 = fopen("deportes.dat", "wb");
    arch2 = fopen("socios.dat", "wb");

    while (lista != NULL){
        fwrite(&lista->deporte, sizeof(stDeporte), 1, arch1);
        crearArchivosSocios(lista->listaDeSocios);
        lista = lista->sig;
    }
    fclose(arch1);

}

///4. Realizar una función que liste todas las disciplinas deportivas del club y los socios que la practican. Modularizar

void mostrarSocio(stSocio socio){
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("Id: %i ..................Nombre y Apellido: %s ................Edad: %i..........Ultima cuota paga: %i\n", socio.idSocio, socio.nya, socio.edad, socio.ultimaCuotaPaga);
    printf("-------------------------------------------------------------------------------------------------------------\n");
}
void imprimirDeporte(stDeporte deporte){
    printf("\n**************************************************************************************************************\n");
    printf("Id: %i ..................Deporte: %s...................Valor de cuota: %.2f\n", deporte.idDeporte, deporte.nombreDeporte, deporte.valorCuota);
    printf("\n**************************************************************************************************************\n");

}

void imprimirSocios(nodo2* listaD){

    while (listaD != NULL){
        mostrarSocio(listaD->socio);
        listaD = listaD->sig;
    }
}

void imprimirDeportes(nodo* lista){

    while (lista != NULL){
        imprimirDeporte(lista->deporte);
        imprimirSocios(lista->listaDeSocios);
        lista = lista->sig;
    }

}
void imprimirArchivoSocios(){
    FILE* fp;
    stSocio reg;
    fp = fopen("socios.dat", "rb");
    if (fp != NULL){
        while (fread(&reg, sizeof(stSocio), 1, fp)>0){
            mostrarSocio(reg);
        }
        fclose(fp);
    }

}

void imprimirArchivoDeportes(){
    FILE* fp;
    stDeporte reg;
    fp = fopen("deportes.dat", "rb");
    if (fp != NULL){
        while (fread(&reg, sizeof(stDeporte), 1, fp)>0){
            imprimirDeporte(reg);
        }
        fclose(fp);
    }

}

///6. Hacer una función busque a los socios, de un deporte en particular, que adeuden cuotas (el mes para filtrar se envía
///por parámetro) y los copie a un arreglo.
///a. Tenga en cuenta que tendrá que utilizar un arreglo de tipo stClub
///b. Tiene que trabajar directamente sobre la lista de listas.

int crearArreglo(stClub a[], int i, nodo2* listaD, int mes, stDeporte deporte){
    while(listaD != NULL){
        if (listaD->socio.ultimaCuotaPaga<mes){
            a[i].idSocio=listaD->socio.idSocio;
            strcpy(a[i].nya, listaD->socio.nya);
            a[i].ultimacuotaPaga = listaD->socio.ultimaCuotaPaga;
            a[i].idDeporte = deporte.idDeporte;
            strcpy(a[i].nombreDeporte, deporte.nombreDeporte);
            a[i].valorCuota = deporte.valorCuota;
            i++;
        }
        listaD =listaD->sig;
    }
    return i;

}
int crearArregloDeudores(stSocio a[], nodo* lista, int cuotaNro){
    int i=0;
    while (lista != NULL){
        i = crearArreglo(a, i, lista->listaDeSocios, cuotaNro, lista->deporte);
        lista = lista->sig;
    }
    return i;


}
void imprimirArreglo(stClub a[], int validos){
    int i=0;
    while (i<validos){
        printf("socio: %s - cuota: %i\n", a[i].nya, a[i].ultimacuotaPaga);
        i++;
    }
}
int main()
{
    nodo* lista = inicLista();
    lista = pasarArchALista(lista);
    imprimirDeportes(lista);
    nodo* aux = deporteConMasSocios(lista);
    printf("El deporte con mas socios es %s\n", aux->deporte.nombreDeporte);
    imprimirDeporte(aux->deporte);
    imprimirSocios(aux->listaDeSocios);
    lista = altaSocio(lista);
    imprimirDeportes(lista);
    crearArchivosDeportes(lista);
    imprimirArchivoSocios();
    imprimirArchivoDeportes();
    int validos=0;
    stClub a[100];
    validos = crearArregloDeudores(a, lista, 6);
    imprimirArreglo(a, validos);
    return 0;
}
