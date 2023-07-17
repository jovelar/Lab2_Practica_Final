#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include ".\pilas.h"

#define ARCHIVOUNO "archivoUno.dat"
#define ARCHIVODOS "archivoDos.dat"

/// STRUCT ///
typedef struct{
    char nombreCalle[30];
    int altura;
}stDireccion;

typedef struct{
    char nombre[30];
    int edad;
    stDireccion direccion;
}stPersona;

typedef struct{
    int datoEntero;
    struct stEntero* siguiente;
}stEntero;

typedef struct{
    stPersona dato;
    struct nodo* siguiente;
}nodo;

/// PROTOTIPO ///
nodo* inicLista();
nodo* crearNodo(stPersona dato); ///1
stEntero* crearNodoEntero(int dato);
nodo* agregarNodoPrincipio(nodo* listaFuncion, nodo* nodoFuncion); ///1
stEntero* ultimoNodo(stEntero* listaFuncion);
stEntero* agregarAlFinal(stEntero* listaFuncion, stEntero* nodoNuevo);
int cargarArchivoUno(char* archivo);
int cargarArchivoDos(char* archivo);
stPersona cargarDatos(char nombre[], int edad, char calle[], int altura);
void abrirArchivo(char* archivo);
void mostrarArchivo(FILE* archivoFuncion);
void mostrarArchivoRecursivo(FILE* archivoFuncion);
void mostrarNodo(nodo* nodoFuncion);
void mostrarNodoEntero(stEntero* nodoFuncion);
void mostrarLista(nodo* listaFuncion);
void mostrarListaEnteros(stEntero* listaFuncion);
nodo* agregarEnLista(nodo* listaFuncion, nodo* nodoFuncion);
nodo* deArchivoLista(char* archivo);
nodo* agregarEnOrden(nodo* listaFuncion, nodo* nodoNuevo);
nodo* deArchivoListaEnOrden(char* archivo);
nodo * buscarNodo(char dato[], nodo * lista);
void BusquedaDeUnNodo(nodo * lista);
nodo* intercalarListas(nodo* listaFuncionA, nodo* listaFuncionB);
nodo* invertirLista(nodo* listaFuncion);
nodo* invertirListaRecursiva(nodo* listaFuncion);
stEntero* borrarNodo(stEntero* listaFuncion);
stEntero* borrarMenores(stEntero* listaFuncion, int valor);

/// MAIN ///

int main(){
    setlocale(LC_ALL, "");
    stPersona personaMain;
    int cantidad = cargarArchivoUno(ARCHIVOUNO);
    printf(" ===============================================\n");
    printf("                   EJERCICIO 1 \n");
    printf(" ===============================================\n");
    printf(" ====================\n");
    printf("  DE ARCHIVO A LISTA \n");
    printf(" ====================\n");
    printf("\n ARCHIVO UNO\n");
    abrirArchivo(ARCHIVOUNO);
    printf("\n LISTA UNO\n");
    nodo* listaUno = inicLista();
    listaUno = deArchivoLista(ARCHIVOUNO);
    mostrarLista(listaUno);

    printf(" ===============================================\n");
    printf("                   EJERCICIO 2 \n");
    printf(" ===============================================\n");
    printf(" LISTA UNO ORDENADA\n");
    nodo* listaUnoOrdenanda=inicLista();
    listaUnoOrdenanda = deArchivoListaEnOrden(ARCHIVOUNO);
    mostrarLista(listaUnoOrdenanda);

    printf(" ===============================================\n");
    printf("                   EJERCICIO 3 \n");
    printf(" ===============================================\n");
    printf(" EXISTE ELEMENTO\n");
    BusquedaDeUnNodo(listaUnoOrdenanda);
    printf("\n");
    printf("\n");

    printf(" ===============================================\n");
    printf("                   EJERCICIO 4 \n");
    printf(" ===============================================\n");
    printf("\n ARCHIVO DOS\n");
    cargarArchivoDos(ARCHIVODOS);
    abrirArchivo(ARCHIVODOS);

    printf("\n LISTA DOS \n");
    nodo* listaDos=inicLista();
    listaDos=deArchivoLista(ARCHIVODOS);
    mostrarLista(listaDos);

    printf("\n LISTA DOS ORDENADA \n");
    nodo* listaDosOrdenada=inicLista();
    listaDosOrdenada = deArchivoListaEnOrden(ARCHIVODOS);
    mostrarLista(listaDosOrdenada);

    printf("\n LISTA INTERCALADA \n");
    nodo* listaIntercalada=inicLista();
    listaIntercalada=intercalarListas(listaUnoOrdenanda,listaDosOrdenada);
    mostrarLista(listaIntercalada);

    printf(" ===============================================\n");
    printf("                   EJERCICIO 6 \n");
    printf(" ===============================================\n");
    printf("\n LISTA INVERTIDA \n");
    nodo* listaInvertida = listaIntercalada;
    //listaInvertida=invertirLista(listaInvertida);
    listaInvertida=invertirListaRecursiva(listaInvertida);
    mostrarLista(listaInvertida);
    printf("\n");

    printf(" ===================================================\n");
    printf("                   EJERCICIO 5 y 7 \n");
    printf(" ===================================================\n");
    printf(" =========\n");
    printf("  DE PILA \n");
    printf(" =========\n");
    stPila pilaMain;
    inicPila(&pilaMain);
    apilar(&pilaMain,2);
    apilar(&pilaMain,8);
    //desapilar(&pilaMain);
    apilar(&pilaMain,10);
    apilar(&pilaMain,15);
    apilar(&pilaMain,0);
    apilar(&pilaMain,20);
    apilar(&pilaMain,25);
    apilar(&pilaMain,30);
    mostrar(&pilaMain);

    stPila pilaAux;
    inicPila(&pilaAux);
    stPila pilaVacia;
    inicPila(&pilaVacia);
    printf(" TOPE: %i\n", tope(&pilaVacia));

    stEntero* listaPares = inicLista();
    while(!pilavacia(&pilaMain)){
        int ultimo = tope(&pilaMain);
        apilar(&pilaAux,desapilar(&pilaMain));
        if(ultimo %2==0){
            listaPares=agregarAlFinal(listaPares, crearNodoEntero(ultimo));
        }
    }
    while(!pilavacia(&pilaAux)){
        apilar(&pilaMain,desapilar(&pilaAux));
    }
//
//    printf(" =============\n");
//    printf("  LISTA PARES \n");
//    printf(" =============\n");
//    mostrarListaEnteros(listaPares);
//    mostrar(&pilaMain);
//
//    printf("\n ELIMINANDO DATOS MENORES A 10\n");
//    int aEliminar=10;
//    borrarMenores(listaPares,aEliminar);
//    printf(" ====================\n");
//    printf("  LISTA MAYORES A 10 \n");
//    printf(" ====================\n");
//    mostrarListaEnteros(listaPares);
}


nodo* inicLista(){
    return NULL;
}

nodo* crearNodo(stPersona dato){
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo)); //variable nuevo nodo.. malloc (apuntame a esta direccion de memoria).
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

stEntero* crearNodoEntero(int dato){
    stEntero* datoNuevo = (stEntero*)malloc(sizeof(stEntero));
    datoNuevo->datoEntero = dato;
    datoNuevo->siguiente=NULL;
    return datoNuevo;
}

nodo* agregarNodoPrincipio(nodo* lista, nodo* nuevoNodo){
    if(lista==NULL){
        lista=nuevoNodo;
    }else{
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}

stEntero* ultimoNodo(stEntero* listaFuncion){
    stEntero* iterador = listaFuncion;
    if(listaFuncion!=NULL){
        while(iterador->siguiente){
            iterador = iterador->siguiente;
        }
    }
    return iterador;
}

stEntero* agregarAlFinal(stEntero* listaFuncion, stEntero* nodoNuevo){
    if(listaFuncion == NULL){
        listaFuncion = nodoNuevo;
    } else{
        stEntero* ultimo = ultimoNodo(listaFuncion);
        ultimo->siguiente = nodoNuevo;
    }
    return listaFuncion;
}

stPersona cargarDatos(char nombre[], int edad, char calle[], int altura){
    stPersona personaFuncion;
    strcpy(personaFuncion.nombre,nombre);
    personaFuncion.edad=edad;
    strcpy(personaFuncion.direccion.nombreCalle,calle);
    personaFuncion.direccion.altura = altura;
    return personaFuncion;
}

void mostrarDato(stPersona dato){
    printf(" NOMBRE: %s \n", dato.nombre);
    printf(" EDAD: %i \n", dato.edad);
    printf(" CALLE: %s \n", dato.direccion.nombreCalle);
    printf(" ALTURA: %i \n", dato.direccion.altura);
    printf(" ---------------------\n");
}

int cargarArchivoUno(char* archivo){
    FILE* archivoFuncion = fopen(archivo, "wb");
    int contador=0;
    stPersona personaFuncion;
    if(archivoFuncion!=NULL){
        stPersona personaFuncion1 = cargarDatos("Jorge",33,"Murga",2078);
        fwrite(&personaFuncion1,sizeof(personaFuncion1),1,archivoFuncion);
        contador++;
        stPersona personaFuncion2 = cargarDatos("Cesar",18,"Vida",4501);
        fwrite(&personaFuncion2,sizeof(personaFuncion2),1,archivoFuncion);
        contador++;
        stPersona personaFuncion3 = cargarDatos("Agustin",24,"Ave",7789);
        fwrite(&personaFuncion3,sizeof(personaFuncion3),1,archivoFuncion);
        contador++;
        stPersona personaFuncion4 = cargarDatos("Belen",45,"Ave",6785);
        fwrite(&personaFuncion4,sizeof(personaFuncion4),1,archivoFuncion);
        contador++;
        stPersona personaFuncion5 = cargarDatos("German",45,"Ave",8770);
        fwrite(&personaFuncion5,sizeof(personaFuncion5),1,archivoFuncion);
        contador++;
        fclose(archivoFuncion);
    }else{
        printf("\n NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    return contador;
}

int cargarArchivoDos(char* archivo){
    FILE* archivoFuncion = fopen(archivo, "wb");
    int contador=0;
    stPersona personaFuncion;
    if(archivoFuncion!=NULL){
        stPersona personaFuncion1 = cargarDatos("JuanPe",29,"Murga",6757);
        fwrite(&personaFuncion1,sizeof(personaFuncion1),1,archivoFuncion);
        contador++;
        stPersona personaFuncion2 = cargarDatos("Eze",25,"Ave",4897);
        fwrite(&personaFuncion2,sizeof(personaFuncion2),1,archivoFuncion);
        contador++;
        stPersona personaFuncion3 = cargarDatos("Isaias",35,"Vida",7454);
        fwrite(&personaFuncion3,sizeof(personaFuncion3),1,archivoFuncion);
        contador++;
        stPersona personaFuncion4 = cargarDatos("Juancito",29,"Ave",6542);
        fwrite(&personaFuncion4,sizeof(personaFuncion4),1,archivoFuncion);
        contador++;
        stPersona personaFuncion5 = cargarDatos("Flor",20,"Ave",8653);
        fwrite(&personaFuncion5,sizeof(personaFuncion5),1,archivoFuncion);
        contador++;
        fclose(archivoFuncion);
    }else{
        printf("\n NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    return contador;
}

void mostrarArchivoRecursivo(FILE* archivoFuncion){
    stPersona personaFuncion;
    if(fread(&personaFuncion, sizeof(stPersona), 1, archivoFuncion) > 0){
        mostrarDato(personaFuncion);
        mostrarArchivoRecursivo(archivoFuncion);
    }
}

void mostrarArchivo(FILE* archivoFuncion){
        stPersona personaFuncion;
        mostrarArchivoRecursivo(archivoFuncion);
}

void abrirArchivo(char* archivo){
    FILE* archivoFuncion=fopen(archivo, "rb");
    if(archivoFuncion!=NULL){
        mostrarArchivo(archivoFuncion);
        fclose(archivoFuncion);
    }else{
        printf("\n NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
}

nodo* agregarEnLista(nodo* listaFuncion, nodo* nodoFuncion){
    if(listaFuncion==NULL){
        listaFuncion=nodoFuncion;
    }else{
        nodoFuncion->siguiente=listaFuncion;
        listaFuncion=nodoFuncion;
    }
    return listaFuncion;
}

nodo* deArchivoLista(char* archivo){
    nodo* listaFuncion=inicLista();
    FILE* archivoFuncion=fopen(archivo, "rb");
    if(archivoFuncion!=NULL){
        stPersona personaFuncion;
        while(fread(&personaFuncion,sizeof(stPersona),1,archivoFuncion)>0){
            nodo* nodoFuncion = crearNodo(personaFuncion);
            listaFuncion = agregarEnLista(listaFuncion,nodoFuncion);
        }
        fclose(archivoFuncion);
    }else{
        printf("\n NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    return listaFuncion;
}

void mostrarNodo(nodo* nodoFuncion){
    printf("------------------------------\n");
    printf(" NOMBRE: %s \n", nodoFuncion->dato.nombre);
    printf(" EDAD: %i \n", nodoFuncion->dato.edad);
    printf(" DIRECCION: %s ALTURA: %i \n", nodoFuncion->dato.direccion.nombreCalle, nodoFuncion->dato.direccion.altura);
    printf("------------------------------\n");

}

void mostrarNodoEntero(stEntero* nodoFuncion){
    printf("------------------------------\n");
    printf(" DATO: %d \n", nodoFuncion->datoEntero);
    printf("------------------------------\n");

}

void mostrarLista(nodo* listaFuncion){
    nodo* nodoAuxiliar = listaFuncion;
    while(nodoAuxiliar!=NULL){
        mostrarNodo(nodoAuxiliar);
        nodoAuxiliar = nodoAuxiliar->siguiente;
    }
}

void mostrarListaEnteros(stEntero* listaFuncion){
    stEntero* nodoAuxiliar = listaFuncion;
    while(nodoAuxiliar!=NULL){
        mostrarNodoEntero(nodoAuxiliar);
        nodoAuxiliar = nodoAuxiliar->siguiente;
    }
}

nodo* agregarEnOrden(nodo* listaFuncion, nodo* nodoNuevo){
    if(listaFuncion==NULL){
        listaFuncion=nodoNuevo;
    }else{
        if(strcmpi(nodoNuevo->dato.nombre, listaFuncion->dato.nombre)<0){
            listaFuncion=agregarEnLista(listaFuncion,nodoNuevo);
        }else{
            nodo* enlace = listaFuncion;
            nodo* iterador = listaFuncion->siguiente;
            while(iterador!=NULL && strcmpi(nodoNuevo->dato.nombre, iterador->dato.nombre)>0){
                enlace = iterador;
                iterador = iterador->siguiente;
            }
            nodoNuevo->siguiente = iterador;
            enlace->siguiente=nodoNuevo;
        }
    }
    return listaFuncion;
}

nodo* deArchivoListaEnOrden(char* archivo){
    nodo* listaFuncion=inicLista();
    FILE* archivoFuncion = fopen(archivo,"r+b");
    if(archivoFuncion!=NULL){
        stPersona personaFuncion;
        while(fread(&personaFuncion,sizeof(stPersona),1,archivoFuncion)>0){
            nodo* nodoFuncion = crearNodo(personaFuncion);
            listaFuncion = agregarEnOrden(listaFuncion,nodoFuncion);
        }
        fclose(archivoFuncion);
    }else{
        printf("\n NO SE PUEDE ACCEDER AL ARCHIVO\n");
    }
    return listaFuncion;
}

nodo * buscarNodo(char dato[], nodo * lista){
    nodo * seg;
    seg = lista;

    while ((seg != NULL) && strcmpi(seg->dato.nombre,dato)!=0)
    {
        seg=seg->siguiente;
    }

    return seg;
}

void BusquedaDeUnNodo(nodo * lista){
    char dato[30];
    printf("INGRESE DATO A BUSCAR: ");
    scanf("%s",&dato);
    printf("\n");
    nodo* aux=buscarNodo(dato,lista);
    if(aux!=NULL){
        printf("EL NOMBRE %s ESTA EN LA LISTA",aux->dato);
    }else{
        printf("EL NOMBRE %s NO ESTA EN LA LISTA",dato);
    }
}

nodo* intercalarListas(nodo* listaFuncionA, nodo* listaFuncionB){
    nodo* nodoFuncionA = listaFuncionA;
    nodo* nodoFuncionB = listaFuncionB;
    nodo* listaFinal = inicLista();
    nodo* listaFinalAux = inicLista();
    while(nodoFuncionA!=NULL && nodoFuncionB!=NULL){
        if(listaFinal==NULL){
            if(strcmp(nodoFuncionA->dato.nombre, nodoFuncionB->dato.nombre)<0){
                listaFinal=nodoFuncionA;
                nodoFuncionA=nodoFuncionA->siguiente;
            }else{
                listaFinal=nodoFuncionB;
                nodoFuncionB=nodoFuncionB->siguiente;
            }
            listaFinalAux=listaFinal;
        }else{
            if(strcmp(nodoFuncionA->dato.nombre,nodoFuncionB->dato.nombre)>0){
                listaFinalAux->siguiente=nodoFuncionB;
                listaFinalAux=nodoFuncionB;
                nodoFuncionB=nodoFuncionB->siguiente;
            }else{
                listaFinalAux->siguiente=nodoFuncionA;
                listaFinalAux=nodoFuncionA;
                nodoFuncionA=nodoFuncionA->siguiente;
            }
        }
    }
    if(nodoFuncionA!=NULL){
        listaFinalAux->siguiente=nodoFuncionA;
    }
    if(nodoFuncionB!=NULL){
        listaFinalAux->siguiente=nodoFuncionB;
    }
    return listaFinal;
}

nodo* invertirLista(nodo* listaFuncion){
    nodo* listaInvertida = inicLista();
    nodo* aux;
    while(listaFuncion!=NULL){
        aux=listaFuncion;
        listaFuncion=listaFuncion->siguiente;
        aux->siguiente=NULL;
        listaInvertida=agregarEnLista(listaInvertida,aux);
    }
    return listaInvertida;
}

nodo* invertirListaRecursiva(nodo* listaFuncion){
    if(listaFuncion==NULL){
        return NULL;
    }
    if(listaFuncion->siguiente==NULL){
        return listaFuncion;
    }
    nodo* nuevaLista = invertirListaRecursiva(listaFuncion->siguiente);
    nodo* proximoNodo = listaFuncion->siguiente;
    proximoNodo->siguiente = listaFuncion;
    listaFuncion->siguiente = NULL;
    return nuevaLista;
}

stEntero* borrarNodo(stEntero* listaFuncion){
    if(listaFuncion->siguiente==NULL){
        listaFuncion=NULL;
    }else{
        stEntero* eliminar = listaFuncion;
        listaFuncion = listaFuncion->siguiente;
        free(eliminar);
    }
    return listaFuncion;
}

stEntero* borrarMenores(stEntero* listaFuncion, int valor){
    if(listaFuncion!=NULL && listaFuncion->datoEntero<valor){
        stEntero* eliminar = listaFuncion;
        listaFuncion = listaFuncion->siguiente;
        free(eliminar);
    }
    stEntero* iterador = listaFuncion;
    stEntero* anterior = listaFuncion;
    while(iterador!=NULL){
        anterior = iterador;
        iterador = iterador->siguiente;
        if(iterador != NULL && iterador->datoEntero < 10){
            anterior->siguiente = borrarNodo(iterador);
            iterador = anterior;
        }
    }
    return listaFuncion;
}
