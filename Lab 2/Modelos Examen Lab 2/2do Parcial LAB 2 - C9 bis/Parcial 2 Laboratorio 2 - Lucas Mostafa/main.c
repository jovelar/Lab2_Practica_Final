#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ESC= 27;

///ESTRUCTURAS -----------------------------------------------------------
typedef struct
{
    int idRegistro;
    int idPaciente;
    int idEspecialidad;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11]; /// formato: AAAA-mm-DD
    char especialidadMedica[30];
    char nombreDoctor[30];
}stRegistroMedico;

typedef struct
{
    int idRegistro;
    int idPaciente;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11]; /// formato: AAAA-mm-DD
    char nombreDoctor[30];
}paciente;

typedef struct _nodoLista
{
    paciente dato;
    struct _nodoLista * siguiente;
}nodoLista;

typedef struct
{
    int idEspecialidad;
    char especialidadMedica[30];
    nodoLista * listaPaciente;
}stCeldaEspecialidad;

///La estructura elegida

///PROTOTIPADO ---------------------------------------------------------------
//Ejercicio 1
nodoLista * inicLista();
void inicArreglo(stCeldaEspecialidad especialidades[], int dim);

//Ejercicio 2
int archivoToArreglo(char arch[], stCeldaEspecialidad especialidades[], int validos, int dimension);
int alta(stCeldaEspecialidad especialidades[],paciente pac, stCeldaEspecialidad espe, int validos);
int agregarEspecialidad (stCeldaEspecialidad especialidades[], stCeldaEspecialidad espe,int validos);
int buscarPosMateria(stCeldaEspecialidad especialidades[], stCeldaEspecialidad espe,int validos);
nodoLista * crearNodo(paciente pac);
nodoLista* agregarAlPrincipio(nodoLista * lista, nodoLista * nuevoNodo);

//Ejercicio 3
void mostrarUnaEspecialidad(stCeldaEspecialidad especialidades[], int pos);
void recorrerYMostrarTodasLasMaterias(stCeldaEspecialidad especialidad[], int validos);
void recorrerYMostrar(nodoLista * lista);
void mostrarUnNodo(nodoLista * lista);
void mostrarPaciente(paciente pac);

//Ejercicio 4
int ingresarPacientes(stCeldaEspecialidad especialidades[], int validos, int dimension);

//Ejercicio 5
int atendido (stCeldaEspecialidad especilidades[], int validos, char nombre[], char apellido[], stCeldaEspecialidad nombreEspe);

//Ejercicio 6
int recorrerYContar(stCeldaEspecialidad especialidad[], int validos);
int recorrerYContarLista(nodoLista * lista);

//Ejercicio 7
void generarArchivo(stCeldaEspecialidad especialidades[], int validos, char nuevo[], char nombreEspe[]);

///MAIN ----------------------------------------------------------------------
int main()
{
    char arch[]="registroMedico.dat";
    int dim= 20;
    stCeldaEspecialidad especialidades[dim];

    ///EJERCICIO 1
    inicArreglo(especialidades, dim);

    ///EJERCICIO 2
    int validos= 0;
    validos= archivoToArreglo(arch, especialidades, validos, dim);

    ///EJERCICIO 3
    recorrerYMostrarTodasLasMaterias(especialidades, validos);

    ///EJERCICIO 4
    ingresarPacientes(especialidades, validos, dim);

    ///EJERCICIO 5
    char nombre[20];
    char apellido[20];

    printf("\nIngrese nombre del paciente: ");
    fflush(stdin);
    gets(nombre);

    printf("\nIngrese apellido del paciente: ");
    fflush(stdin);
    gets(apellido);

    stCeldaEspecialidad espe;

    printf("\nIngrese especialidad: ");
    fflush(stdin);
    gets(espe.especialidadMedica);

    printf("\nIngrese id especialidad: ");
    scanf("%d", &espe.idEspecialidad);
    espe.listaPaciente= inicLista();

    int rta=0;

    rta= atendido(especialidades, validos, nombre, apellido, espe);

    if(1)
    {
        printf("\nCliente atendido.");
    }
    else
    {
        printf("\nCliente no atendido.");
    }

    ///EJERCICIO 6
    int num;

    num= recorrerYContar(especialidades, validos);

    printf("\nLa especialidad que mas pacientes atendio es: %d", especialidades[num]);

    ///EJERCICIO 7
    char nuevo[]="especialidades.dat";

    char nombreEspe[20];

    printf("\nIngrese el nombre de la especialidad: ");
    fflush(stdin);
    gets(nombreEspe);

    generarArchivo(especialidades, validos, nuevo, nombreEspe);

    return 0;
}

///EJERCICIO 1 ---------------------------------------------------------------
nodoLista * inicLista()
{
    return NULL;
}

void inicArreglo(stCeldaEspecialidad especialidades[], int dim)
{
    int i;

    for(int i= 0; i<dim; i++)
    {
        especialidades[i].idEspecialidad= 0;
        strcpy(especialidades[i].especialidadMedica, '0');
        especialidades[i].listaPaciente= inicLista();
    }
}

///EJERCICIO 2 ----------------------------------------------------------------
int archivoToArreglo(char arch[], stCeldaEspecialidad especialidades[], int validos, int dimension)
{
    stRegistroMedico registro;
    paciente pac;
    stCeldaEspecialidad espe;

    int i=0;

    FILE * puntero;
    puntero= fopen(arch, "rb");

    if(puntero)
    {
        while((fread(&registro, sizeof(stRegistroMedico), 1, puntero)>0) && i<dimension)
        {
            especialidades[i].idEspecialidad= registro.idEspecialidad;
            strcpy(especialidades[i].especialidadMedica, registro.especialidadMedica);

            pac.idRegistro= registro.idRegistro;
            pac.idPaciente= registro.idPaciente;
            strcpy(pac.nombrePaciente, registro.nombrePaciente);
            strcpy(pac.apellidoPaciente, registro.apellidoPaciente);
            strcpy(pac.nombreDoctor, registro.nombreDoctor);
            strcpy(pac.fechaAtencion, registro.fechaAtencion);
            strcpy(pac.diagnostico, registro.diagnostico);

            validos= alta(especialidades, pac, espe, validos);
        }
    }
    else
        printf("\nNo se pudo abrir el archivo.\n");

    fclose(puntero);

    return i;
}

int alta(stCeldaEspecialidad especialidades[],paciente pac, stCeldaEspecialidad espe, int validos)
{
    nodoLista * aux= crearNodo(pac);

    int pos= buscarPosMateria(especialidades, espe, validos);

    if(pos==-1)
    {
        validos= agregarEspecialidad(especialidades, espe, validos);
        pos= validos-1;
    }
    especialidades[pos].listaPaciente= agregarAlPrincipio(especialidades[pos].listaPaciente, aux);

    return validos;
}

int agregarEspecialidad (stCeldaEspecialidad especialidades[], stCeldaEspecialidad espe,int validos)
{
    strcpy(especialidades[validos].especialidadMedica, espe.especialidadMedica);
    especialidades[validos].listaPaciente= inicLista();
    validos++;
    return validos;
}

int buscarPosMateria(stCeldaEspecialidad especialidades[], stCeldaEspecialidad espe,int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos)&&(rta==-1))
    {
        if(strcmp(especialidades[i].especialidadMedica, espe.especialidadMedica)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

nodoLista * crearNodo(paciente pac)
{
    nodoLista * aux= (nodoLista*)malloc(sizeof(nodoLista));

    aux->dato.idRegistro= pac.idRegistro;
    aux->dato.idPaciente= pac.idPaciente;

    strcpy(pac.nombrePaciente, aux->dato.nombrePaciente);
    strcpy(pac.apellidoPaciente, aux->dato.apellidoPaciente);
    strcpy(pac.diagnostico, aux->dato.diagnostico);
    strcpy(pac.fechaAtencion, aux->dato.fechaAtencion);
    strcpy(pac.nombreDoctor, aux->dato.nombreDoctor);

    aux->siguiente= NULL;

    return aux;
}

nodoLista* agregarAlPrincipio(nodoLista * lista, nodoLista * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}

///EJERCICIO 3 ------------------------------------------------------------------
void mostrarUnaEspecialidad(stCeldaEspecialidad especialidades[], int pos)
{
    printf("\n----------------------------------------------");
    printf("\nId especialidad: %d", especialidades[pos].idEspecialidad);
    printf("\nNombre de la especialidad: %s", especialidades[pos].especialidadMedica);
    printf("\n----------------------------------------------");
}

void recorrerYMostrarTodasLasMaterias(stCeldaEspecialidad especialidad[], int validos)
{
    int i;

    for(i=0; i<validos; i++)
    {
        mostrarUnaEspecialidad(especialidad, i);
        recorrerYMostrar(especialidad[i].listaPaciente);
    }
}

void recorrerYMostrar(nodoLista * lista)
{
    nodoLista * seg= lista;

    while(seg!=NULL)
    {
        mostrarUnNodo(seg);
        seg=seg->siguiente;
    }
}

void mostrarUnNodo(nodoLista * lista)
{
    mostrarPaciente(lista->dato);
}

void mostrarPaciente(paciente pac)
{
    printf("\n----------------------------------------------");
    printf("\nId registro: %d", pac.idRegistro);
    printf("\nId paciente: %d", pac.idPaciente);
    printf("\nNombre: %s", pac.nombrePaciente);
    printf("\nApellido: %s", pac.apellidoPaciente);
    printf("\nDiagnostico: %s", pac.diagnostico);
    printf("\nFecha: %s", pac.fechaAtencion);
    printf("\Doctor: %s", pac.nombreDoctor);
    printf("\n----------------------------------------------");
}

///EJERCICIO 4 ------------------------------------------------------------------
int ingresarPacientes(stCeldaEspecialidad especialidades[], int validos, int dimension)
{
    stCeldaEspecialidad espe;
    paciente pac;

    char salir='s';


    while(salir=='s' && validos<dimension)
    {
        printf("Ingrese la especialidad: ");
        fflush(stdin);
        gets(espe.especialidadMedica);

        espe.idEspecialidad= validos;

        pac.idRegistro= validos + 1;

        printf("\nIngrese idPaciente: ");
        fflush(stdin);
        gets(pac.nombrePaciente);

        printf("\nIngrese nombre: ");
        fflush(stdin);
        gets(pac.nombrePaciente);

        printf("Ingrese apellido: ");
        fflush(stdin);
        gets(pac.apellidoPaciente);

        printf("Ingrese diagnostico: ");
        fflush(stdin);
        gets(pac.diagnostico);

        printf("Ingrese fecha: ");
        fflush(stdin);
        gets(pac.fechaAtencion);

        printf("Ingrese doctor: ");
        fflush(stdin);
        gets(pac.nombreDoctor);


        validos= alta(especialidades, pac, espe, validos);

        printf("\nPresione 's' si desea continuar.\n");
        fflush(stdin);
        salir= getch();
    }
    return validos;
}

///EJERCICIO 5 -----------------------------------------------------------------------------------------------------------------------------
int atendido (stCeldaEspecialidad especilidades[], int validos, char nombre[], char apellido[], stCeldaEspecialidad nombreEspe)
{
    int i= 0;
    int rta=0;

    int pos=0;

    pos= buscarPosMateria(especilidades, nombreEspe, validos);

    if(pos!=-1)
    {
       nodoLista * seg= especilidades[pos].listaPaciente;
       while(seg!=NULL && rta!=1)
       {
           if(strcmp(seg->dato.apellidoPaciente, apellido)==0)
           {
               if(strcmp(seg->dato.nombrePaciente, nombre)==0)
               {
                   rta= 1;
               }
           }
           seg= seg->siguiente;
       }
    }
    return rta;
}

///EJERCICIO 6 ------------------------------------------------------------------------------------------
int recorrerYContar(stCeldaEspecialidad especialidad[], int validos)
{
    int i;
    int contar=0;
    int pos;
    int anterior= 0;
    char nombre[20];

    strcpy(nombre, especialidad[i].especialidadMedica);

    for(i=0; i<validos; i++)
    {
        contar= recorrerYContar(especialidad[i].listaPaciente);
        if(contar>anterior)
        {
            strcpy(nombre, especialidad[i].especialidadMedica);
            pos= i;
        }
    }
    return nombre;
}

int recorrerYContarLista(nodoLista * lista)
{
    nodoLista * seg= lista;

    int i= 0;

    while(seg!=NULL)
    {
        seg=seg->siguiente;
        i++;
    }
    return i;
}

///EJERCICIO 7 ------------------------------------------------------------------------------------------
void generarArchivo(stCeldaEspecialidad especialidades[], int validos, char nuevo[], char nombreEspe[])
{
    int i= 0;
    char espe[20];

    stRegistroMedico registro;

    while(i<validos && strcmp(especialidades[i].especialidadMedica, nombreEspe)!=0)
    {
        i++;
    }
    if(i<validos)
    {
        strcpy(especialidades, especialidades[i].especialidadMedica);
        FILE * puntero;
        puntero= fopen(nuevo, "ab");

        if(puntero)
        {
            paciente pac;
            nodoLista * seg= especialidades[i].listaPaciente;
            while(seg!=NULL)
            {
                pac= seg->dato;
                fwrite(&pac, sizeof(paciente), 1, puntero);
                seg= seg->siguiente;
            }
        }
    }
}
