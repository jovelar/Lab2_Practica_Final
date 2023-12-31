#include "ADL.h"

celda crearCeldaMateria(int idMateria, char materia[40])
{
    celda nuevo;
    nuevo.idMateria=idMateria;
    strcpy(nuevo.materia,materia);
    nuevo.listaDeNotas=NULL;
    return nuevo;
}

int insertarCelda(celda listaDeMaterias[],int validos,celda nuevaCelda)
{
    listaDeMaterias[validos]=nuevaCelda;
    validos++;
    return validos;
}

int buscarCeldaMateria(celda listaMaterias[],char nombreMateria[40],int validos)
{
    int posicion=-1;
    int contador=0;

    while(posicion==-1 && contador< validos)
    {
        if(strcmp(listaMaterias[contador].materia,nombreMateria)==0)
        {
            posicion=contador;
        }
        contador++;
    }

    return posicion;
}

nodo *crearNodo(notaAlumno nuevaNota)
{

    nodo *nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->dato=nuevaNota;
    nuevo->siguiente=NULL;
    return nuevo;
}

nodo *insertarAlPrincipio(nodo *lista,nodo *nuevo, notaAlumno notaAlumnoNueva)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}

int pasarDeArchivoToADL(celda materias[],int materiasValidas,char nombreArchivo[30])
{
    FILE *archivo=fopen(nombreArchivo,"r");
    if(archivo)
    {
        registroArchivo buffer;

        while(fread(&buffer,sizeof(registroArchivo),1,archivo)>0)
        {
            //PRIMERO SIEMPRE SE CREA EL NODO CON LA NOTA A INSERTAR, Y SE BUSCA LA POSICION DE LA MATERIA
            notaAlumno nuevaNota=(notaAlumno){buffer.nota,buffer.legajo,buffer.nombreApe};
            strcpy(nuevaNota.nombreApe,buffer.nombreApe);
            nodo *nuevo=crearNodo(nuevaNota);
            int posicionMateria=buscarCeldaMateria(materias,buffer.materia,materiasValidas);

            if(posicionMateria==-1) // SI NO ENCONTRO LA MATERIA O NO EXISTE
            {
                celda nuevaMateria=crearCeldaMateria(buffer.idMateria,buffer.materia);
                nuevaMateria.listaDeNotas=NULL;
                materiasValidas=insertarCelda(materias,materiasValidas,nuevaMateria);
                posicionMateria=materiasValidas-1; //ESENCIAL PARA NO PERDER LA PRIMER NOTA AL INSERTAR!!!
            }
            materias[posicionMateria].listaDeNotas=insertarAlPrincipio(materias[posicionMateria].listaDeNotas,nuevo,nuevaNota);
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo esta vacio! \n");
    }
    return materiasValidas;
}


void pasarDeADLToArchivoDeAprobados(celda listaADL[],int validos, char archivoSalida[40])
{
    FILE *archivo=fopen(archivoSalida,"wb");

    if(archivo)
    {
        for(int x=0;x<validos;x++)
        {

            nodo *punteroANota=listaADL[x].listaDeNotas;
            while(punteroANota!=NULL)
            {
                if(punteroANota->dato.nota>=6)
                {
                    registroArchivo buffer;
                    buffer.nota=punteroANota->dato.nota;
                    buffer.legajo=punteroANota->dato.legajo;
                    strcpy(buffer.nombreApe,punteroANota->dato.nombreApe);
                    strcpy(buffer.materia,listaADL[x].materia);
                    buffer.idMateria=listaADL[x].idMateria;
                    fwrite(&buffer,sizeof(registroArchivo),1,archivo);
                }
                punteroANota=punteroANota->siguiente;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo no existe/no se pudo crear!");
    }
}
