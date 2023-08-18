#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct{
    int id;
    char nombre[20];
    int cantPag;
    char genero[20];
    int anio;
}libro;

typedef struct nodoListaLibro{
    libro dato;
    struct nodoListaLibro* siguiente;
}nodoListaLibro;

typedef struct{
    libro dato;
    char autor[30];
}registroArchivo;

typedef struct nodoArbolAutor{
    libro dato;
    char autor[30];
    struct nodoArbolAutor* izq;
    struct nodoArbolAutor* der;
}nodoArbolAutor;

typedef struct{
    char autor[30];
    nodoListaLibro* lista;
}stCelda;

// ARBOL
nodoArbolAutor* inicArbol();
nodoArbolAutor* crearNodoArbol(libro dato, char autor[]);
nodoArbolAutor* insertarEnArbol(nodoArbolAutor* arbol, nodoArbolAutor* nuevoNodo);
void preOrder(nodoArbolAutor* arbol);

// ARCHIVO A ARBOL
nodoArbolAutor* archivoToArbol(char archivoAAbrir[], nodoArbolAutor* arbol);

// CARGANDO ARCHIVO
void mostrarArchivo(char archivoAAbrir[]);
void mostrarLibro(libro dato);
void cargarArchivo(char archivoAAbrir[]);
libro nuevoLibro();

nodoArbolAutor* buscarPorAutorYAnio(nodoArbolAutor* arbol, char autor[], int anio);

int main()
{
    //cargarArchivo("libros.dat");
    //mostrarArchivo("libros.dat");

    nodoArbolAutor* arbol = inicArbol();
    arbol = archivoToArbol("libros.dat", arbol);
    //preOrder(arbol);
    //arbolDibujar(arbol);
    int dim = 20;
    int validos = 0;
    stCelda array[dim];

    validos = arbolToADL(arbol, array, dim, validos);
    printf("\nEste es el ADL\n");
    mostrarArrayDeListas(array, validos);

    int rta = buscarAutor(array, validos, -1, "Miguel de Cervantes");
    if(rta == -1){
        printf("\nNo se encontro el autor\n");
    }else{
        printf("\nPos: %d\n", rta);
    }

    printf("\nBuscando...\n");
    nodoArbolAutor* rtaBusqueda = buscarPorAutorYAnio(arbol, "Miguel de Cervantes", 1605);
    if(rtaBusqueda){
        mostrarLibro(rtaBusqueda->dato);
    }else{
        printf("\nNo se encontro el Libro\n");
    }

    return 0;
}

// BUSCAR EN ARBOL
nodoArbolAutor* buscarPorAutorYAnio(nodoArbolAutor* arbol, char autor[], int anio){
    nodoArbolAutor* rta = NULL;
    if(arbol){
        if(strcmpi(autor, arbol->autor) == 0 && anio == arbol->dato.anio){
            rta = arbol;
        }else{
            rta = buscarPorAutorYAnio(arbol->izq, autor, anio);
            if(rta == NULL){
                rta = buscarPorAutorYAnio(arbol->der, autor, anio);
            }
        }
    }
    return rta;
}

// FUNCIONES DE LISTAS

nodoListaLibro* inicLista(){
    return NULL;
}

nodoListaLibro* crearNodoLista(libro dato){
    nodoListaLibro* aux = (nodoListaLibro*) malloc(sizeof(nodoListaLibro));
    aux->dato = dato;
    aux->siguiente = NULL;

    return aux;
}

nodoListaLibro* agregarAlFinalDeLista(nodoListaLibro* lista, nodoListaLibro* nuevoNodo){
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nodoListaLibro* aux = lista;
        if(aux){
            while(aux-> siguiente != NULL){
                aux = aux-> siguiente;
            }
        }
        aux-> siguiente = nuevoNodo;
    }
    return lista;
}

void mostrarLista(nodoListaLibro* lista){
    if(lista){
        nodoListaLibro* seguidora = lista;
        while(seguidora){
            mostrarLibro(seguidora->dato);
            seguidora = seguidora->siguiente;
        }
    }
}

// ARBOL A LISTAS
int arbolToADL(nodoArbolAutor* arbol, stCelda array[], int dim, int validos){
    if(arbol){
        validos = alta(array, arbol->dato, arbol->autor, validos, dim);
        validos = arbolToADL(arbol->izq, array, dim, validos);
        validos = arbolToADL(arbol->der, array, dim, validos);
    }
    return validos;
}

// ADL

int alta(stCelda array[], libro librito, char autor[], int validos, int dim){
    nodoListaLibro* nuevoLibro = crearNodoLista(librito);
    int pos = buscarPosAutor(array, autor, validos);
    if(pos == -1){
        validos = agregarCelda(array, autor, dim, validos);
        pos = validos - 1; // ultima posicion valida
    }
    array[pos].lista = agregarAlFinalDeLista(array[pos].lista, nuevoLibro);

    return validos;
}

int buscarPosAutor(stCelda array[], char autor[], int validos){
    int rta = -1;
    int i = 0;
    while(i < validos && rta == -1){
        if(strcmp(array[i].autor, autor) == 0){
            rta = i;
        }
        i++;
    }
    return rta;
}

int agregarCelda(stCelda array[], char autor[], int dim, int validos){
    if(validos < dim){
        strcpy(array[validos].autor ,autor);
        array[validos].lista = inicLista();
        validos++;
        return validos;
    }
}

int buscarAutor(stCelda array[], int validos, int pos, char autor[]){
    if(validos == 0){
        if(strcmpi(array[validos].autor, autor) == 0){
            pos = validos;
        }
        pos = pos + 0;
    }else{
        if(strcmpi(array[validos].autor, autor) == 0){
            pos = validos;
        }
        pos = buscarAutor(array, validos-1, pos, autor);
    }
    return pos;
}

void mostrarArrayDeListas(stCelda array[], int validos){
    int i = 0;
    printf("\n**************************ADL*********************************\n");
    while(i < validos){
        printf("\nAutor: %s\n", array[i].autor);
        mostrarLista(array[i].lista);
        printf("\n########################################################################################################\n");
        i++;
    }
    printf("\n**************************ADL*********************************\n");
}

// FUNCIONES DE ARBOL

nodoArbolAutor* inicArbol(){
    return NULL;
}

nodoArbolAutor* crearNodoArbol(libro dato, char autor[]){
    nodoArbolAutor* aux = malloc(sizeof(nodoArbolAutor));
    aux->dato = dato;
    strcpy(aux->autor, autor);
    aux->izq = NULL;
    aux->der = NULL;

    return aux;
}

nodoArbolAutor* insertarEnArbol(nodoArbolAutor* arbol, nodoArbolAutor* nuevoNodo){
    if(arbol == NULL){
        arbol = nuevoNodo;
    }else{
        if(strcmp(nuevoNodo->dato.nombre, arbol->dato.nombre) > 0){
            arbol-> der = insertarEnArbol(arbol->der, nuevoNodo);
        }else{
            arbol-> izq = insertarEnArbol(arbol->izq, nuevoNodo);
        }
    }
    return arbol;
}

void preOrder(nodoArbolAutor* arbol){
    if(arbol){
        mostrarLibro(arbol->dato);
        preOrder(arbol->izq);
        preOrder(arbol->der);
    }
}

// ARCHIVO A ARBOL

nodoArbolAutor* archivoToArbol(char archivoAAbrir[], nodoArbolAutor* arbol){
    FILE *archivo = fopen(archivoAAbrir, "rb");
    registroArchivo nuevoRegistro;
    nodoArbolAutor* aux;

    if(archivo){
        while(fread(&nuevoRegistro, sizeof(registroArchivo), 1, archivo) > 0){
            aux = crearNodoArbol(nuevoRegistro.dato, nuevoRegistro.autor);
            arbol = insertarEnArbol(arbol, aux);
        }
        fclose(archivo);
    }else{
        printf("\nEl archivo es NULL\n");
    }
    return arbol;
}

// CARGANDO ARCHIVO

void mostrarArchivo(char archivoAAbrir[]){
    FILE *archivo = fopen(archivoAAbrir, "rb");
    registroArchivo nuevoRegistro;
    if(archivo){
        while(fread(&nuevoRegistro, sizeof(registroArchivo), 1, archivo) > 0){
            printf("\n**********************************************************\n");
            mostrarLibro(nuevoRegistro.dato);
            printf("\nAutor del Libro: %s\n", nuevoRegistro.autor);
            printf("\n**********************************************************\n");
        }
        fclose(archivo);
    }
}

void mostrarLibro(libro dato){
    printf("\nNombre del Libro.............: %s\n", dato.nombre);
    printf("\nID del Libro.................: %d\n", dato.id);
    printf("\nCantidad de Paginas del Libro: %d\n", dato.cantPag);
    printf("\nGenero del Libro.............: %s\n", dato.genero);
    printf("\nAnio del Libro...............: %d\n", dato.anio);
    printf("\n*******************************************************************\n");
}

void cargarArchivo(char archivoAAbrir[]){
    char control = 's';
    FILE *archivo = fopen(archivoAAbrir, "ab");
    registroArchivo nuevoRegistro;

    if(archivo){
        printf("\nQuiere cargar un Registro? (s/n)\n");
        fflush(stdin);
        scanf("%c", &control);

        while(control == 's'){
            printf("\n-----------------------CARGANDO REGISTROS---------------------------\n");

            nuevoRegistro.dato = nuevoLibro();
            fflush(stdin);
            printf("\nAutor del Libro:\n");
            gets(nuevoRegistro.autor);

            fwrite(&nuevoRegistro, sizeof(registroArchivo), 1, archivo);

            printf("\Registro Cargado!\n");
            printf("\nCargar otro Registro? (s/n)\n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archivo);
    }else {
        printf("El archivo en NULL");
    }
}

libro nuevoLibro(){
    libro aux;

    printf("\nID del Libro:\n");
    scanf("%d", &aux.id);

    printf("\nNombre del Libro:\n");
    fflush(stdin);
    gets(aux.nombre);

    printf("\nCantidad de Paginas del Libro:\n");
    scanf("%d", &aux.cantPag);

    printf("\nGenero del Libro:\n");
    fflush(stdin);
    gets(aux.genero);

    printf("\nAnio del Libro:\n");
    scanf("%d", &aux.anio);

    return aux;
}

///dibujar internet 1
//arbol - dibujar arbol aux
int _print_t(nodoArbolAutor *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;  //es el ancho del nodo que dibujo

    if (!tree) return 0;

    sprintf(b, "(%3d)", tree->dato.id);    //paso valor int con 3 espacios decimales

    int left  = _print_t(tree->izq,  1, offset,                depth + 1, s);
    int right = _print_t(tree->der, 0, offset + left + width, depth + 1, s);

    //dibujo nodo
#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

        //dibujo lineas
    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}


//arbol - dibujar
void arbolDibujar(nodoArbolAutor *tree)
{
    int cantFilas=20;        //20 filas para 30 nodos
    char s[cantFilas][255];
    //creo una matriz de char para hacer mi "dibujo"
    for (int i = 0; i < cantFilas; i++)
        sprintf(s[i], "%200s", "");    // sprintf(s[i], "%200s", ""); para 30 nodos

    _print_t(tree, 0, 0, 0, s);

    //Imprimo matris
    for (int i = 0; i < cantFilas; i++)
        printf("%s\n", s[i]);
}

