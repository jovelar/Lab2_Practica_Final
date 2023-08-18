#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct{
    int idRegistro;
    int idPaciente; //
    char nombrePaciente[30]; //
    char apellidoPaciente[30]; //
    char diagnostico[100]; //
    char fechaAtencion[11]; //
    int idEspecialidad; //
    char especialidadMedica[30]; //
    char nombreDoctor[30]; //
}stRegistroMedico;

typedef struct{
    int idEspecialidad;
    char especialidadMedica[30];
}stEspecialidadMedica;

typedef struct{
    int id;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11]; /// formato: AAAA-mm-DD
    char nombreDoctor[30];
}stPaciente;

typedef struct _nodoLista{
    stPaciente dato;
    struct _nodoLista* siguiente;
}nodoLista; /// coleccion secundaria

typedef struct{
    stEspecialidadMedica dato;
    nodoLista* lista;
}stCelda; /// coleccion principal

// RECORRER ARCHIVO
void recorrerArchivo(char archivoAAbrir[]);
void mostrarUnRegistro(stRegistroMedico r);

stPaciente crearPaciente(stRegistroMedico nuevoRegistro);
void guardarPorEspecialidad(char archivoAAbrir[], char especialidad[], stCelda array[], int validos);

int main()
{
    printf("2do Parcial Lab II!\n");
    //recorrerArchivo("registroMedico.dat");
    printf("\n\n\nADL\n\n\n");

    int dim = 10;
    stCelda array[dim];
    int validos = 0;
    validos = pasarDeArchivoToADL("registroMedico.dat", array, dim, validos);
    mostrarArrayDeListas(array, validos);

    int rta = buscarPaciente(array, validos, "Adolfa", "Olvido");
    if(rta == 1){
        printf("\nSe encontro al paciente\n");
    }else{
        printf("\nNO se encontro al paciente\n");
    }

//    guardarPorEspecialidad("archivo1.dat", "Neumologia pediatrica", array, validos);
    printf("\nLALALALALAALLALALAL\n");
    mostrarArchivoPorEspecialidad("archivo1.dat");

    return 0;
}

// FUNCIONES DE LISTAS

nodoLista* inicLista(){
    return NULL;
}

nodoLista* crearNodoLista(stPaciente dato){
    nodoLista* aux = (nodoLista*) malloc(sizeof(nodoLista));
    aux->dato = dato;
    aux->siguiente = NULL;

    return aux;
}

nodoLista* agregarAlFinalDeLista(nodoLista* lista, nodoLista* nuevoNodo){
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nodoLista* aux = lista;
        if(aux){
            while(aux-> siguiente != NULL){
                aux = aux-> siguiente;
            }
        }
        aux-> siguiente = nuevoNodo;
    }
    return lista;
}

void mostrarLista(nodoLista* lista){
    if(lista){
        nodoLista* seguidora = lista;
        while(seguidora){
            mostrarPaciente(seguidora->dato);
            seguidora = seguidora->siguiente;
        }
    }
}

void mostrarPaciente(stPaciente r){
    printf("\n Id Paciente.....................: %d",r.id);
    printf("\n Nombre paciente.................: %s",r.nombrePaciente);
    printf("\n Apellido paciente...............: %s",r.apellidoPaciente);
    printf("\n Diagnostico.....................: %s",r.diagnostico);
    printf("\n Fecha de Atencion...............: %s",r.fechaAtencion);
    printf("\n Nombre del medico...............: %s\n",r.nombreDoctor);
}

// ARCHIVO A ADL
int pasarDeArchivoToADL(char archivoAAbrir[], stCelda array[], int dim, int validos){
    FILE *archivo = fopen(archivoAAbrir, "rb");
    stRegistroMedico nuevoRegistro;
    stPaciente paciente;
    stEspecialidadMedica especialidad;

    if(archivo){
        while(fread(&nuevoRegistro, sizeof(stRegistroMedico), 1, archivo) > 0){
            paciente = crearPaciente(nuevoRegistro);
            especialidad.idEspecialidad = nuevoRegistro.idEspecialidad;
            strcpy(especialidad.especialidadMedica, nuevoRegistro.especialidadMedica);

            validos = alta(array, paciente, especialidad, validos, dim);
        }
        fclose(archivo);
    }else{
        printf("El archivo en NULL");
    }
    return validos;
}

stPaciente crearPaciente(stRegistroMedico nuevoRegistro){
    stPaciente paciente;

    strcpy(paciente.nombrePaciente, nuevoRegistro.nombrePaciente);
    strcpy(paciente.apellidoPaciente, nuevoRegistro.apellidoPaciente);
    strcpy(paciente.diagnostico, nuevoRegistro.diagnostico);
    strcpy(paciente.fechaAtencion, nuevoRegistro.fechaAtencion);
    paciente.id = nuevoRegistro.idPaciente;
    strcpy(paciente.nombreDoctor, nuevoRegistro.nombreDoctor);

    return paciente;
}

// ADL A ARCHIVO
void guardarPorEspecialidad(char archivoAAbrir[], char especialidad[], stCelda array[], int validos){
    FILE *archivo = fopen(archivoAAbrir, "ab");
    stPaciente nuevoRegistro;
    int i = 0;
    int flag = 0;

    if(archivo){
        while(flag == 0 && i < validos){
            if(strcmpi(array[i].dato.especialidadMedica, especialidad) == 0){
                if(array[i].lista){
                    nodoLista* seguidora = array[i].lista;
                    while(seguidora){
                        nuevoRegistro = seguidora->dato;
                        fwrite(&nuevoRegistro, sizeof(stPaciente), 1, archivo);
                        seguidora = seguidora->siguiente;
                    }
                }
                flag = 1;
            }
            i++;
        }
        if(flag == 0){
            printf("\nNo se encontro la especialidad\n");
        }
        fclose(archivo);
    }else{
        printf("El archivo en NULL");
    }
}

void mostrarArchivoPorEspecialidad(char archivoAAbrir[]){
    FILE *archivo = fopen(archivoAAbrir, "rb");
    stPaciente nuevoRegistro;
    if(archivo){
        while(fread(&nuevoRegistro, sizeof(stPaciente), 1, archivo) > 0){
            mostrarPaciente(nuevoRegistro);
        }
    }else{
        printf("El archivo en NULL");
    }
}

// ADL (ARREGLO DE LISTAS)
int alta(stCelda array[], stPaciente paciente, stEspecialidadMedica especialidad, int validos, int dim){
    nodoLista* nuevoPaciente = crearNodoLista(paciente);
    int pos = buscarPosEspecialidad(array, especialidad, validos);
    if(pos == -1){
        validos = agregarCelda(array, especialidad, dim, validos);
        pos = validos - 1; // ultima posicion valida
    }
    array[pos].lista = agregarAlFinalDeLista(array[pos].lista, nuevoPaciente);

    return validos;
}

int buscarPosEspecialidad(stCelda array[], stEspecialidadMedica especialidad, int validos){
    int rta = -1;
    int i = 0;
    while(i < validos && rta == -1){
        if(array[i].dato.idEspecialidad == especialidad.idEspecialidad){
            rta = i;
        }
        i++;
    }
    return rta;
}

int agregarCelda(stCelda array[], stEspecialidadMedica especialidad, int dim, int validos){
    if(validos < dim){
        array[validos].dato = especialidad;
        array[validos].lista = inicLista();
        validos++;
        return validos;
    }
}

int buscarPaciente(stCelda array[], int validos, char nombre[], char apellido[]){
    int flag = 0;
    int i = 0;
    while( flag == 0 && i < validos){
        if(array[i].lista){
            nodoLista* seguidora = array[i].lista;
            while(flag == 0 && seguidora){
                if(strcmpi(nombre, seguidora->dato.nombrePaciente) == 0 && strcmpi(apellido, seguidora->dato.apellidoPaciente) == 0){
                    flag = 1;
                }
                seguidora = seguidora->siguiente;
            }
        }
        i++;
    }
    return flag;
}

void mostrarArrayDeListas(stCelda array[], int validos){
    int i = 0;
    printf("\n**************************ADL*********************************\n");
    while(i < validos){
        printf("\nEspecialidad Medica: %s\n", array[i].dato.especialidadMedica);
        printf("\nID Especialidad....: %d\n", array[i].dato.idEspecialidad);
        mostrarLista(array[i].lista);
        printf("\n########################################################################################################\n");
        i++;
    }
    printf("\n**************************ADL*********************************\n");
}

// RECORRER ARCHIVO
void recorrerArchivo(char archivoAAbrir[]){
    FILE *archivo = fopen(archivoAAbrir, "rb");
    stRegistroMedico nuevoRegistro;

    if(archivo){
        while(fread(&nuevoRegistro, sizeof(stRegistroMedico), 1, archivo) > 0){
            mostrarUnRegistro(nuevoRegistro);
        }
        fclose(archivo);
    }else{
        printf("El archivo en NULL");
    }
}

void mostrarUnRegistro(stRegistroMedico r){
    printf("\n Id Registro.....................: %d",r.idRegistro);
    printf("\n Id Paciente.....................: %d",r.idPaciente);
    printf("\n Nombre paciente.................: %s",r.nombrePaciente);
    printf("\n Apellido paciente...............: %s",r.apellidoPaciente);
    printf("\n Diagnostico.....................: %s",r.diagnostico);
    printf("\n Fecha de Atencion...............: %s",r.fechaAtencion);
    printf("\n Id Especialidad.................: %d",r.idEspecialidad);
    printf("\n Especialidad medica.............: %s",r.especialidadMedica);
    printf("\n Nombre del medico...............: %s\n",r.nombreDoctor);

    printf("---------------------------------------------------------------------");
}
