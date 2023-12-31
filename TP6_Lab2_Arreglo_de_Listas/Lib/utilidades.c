#include "utilidades.h"

void mostrarRegistroAprobados(char nombreArchivo[40])
{
    FILE * archivo=fopen(nombreArchivo,"rb");
    if(archivo)
    {
        registroArchivo buffer;
        while(fread(&buffer,sizeof(registroArchivo),1,archivo)>0)
        {
            printf("NOTA: %i, LEGAJO: %i, NOMBRE-APELLIDO: %s, MATERIA: %s, ID-MATERIA: %i \n",buffer.nota,buffer.legajo,buffer.nombreApe,buffer.materia,buffer.idMateria);
        }
    }
    else
    {
        printf("El archivo no se pudo abrir/no existe/esta vacio!");
    }
}

void mostrarArregloCeldas(celda arregloCeldas[], int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarCelda(arregloCeldas[x]);
    }
}
void mostrarCelda(celda celdaAVisualizar)
{
    printf("IDMATERIA: %i, MATERIA: %s \n",celdaAVisualizar.idMateria,celdaAVisualizar.materia);
}

void mostrarBuffer(registroArchivo buffer)
{
    printf("NOTA: %-2i, LEGAJO: %-5i, NOMBRE-APE: %-20s, MATERIA: %-11s, IDMATERIA: %-1i \n", buffer.nota,buffer.legajo,buffer.nombreApe,buffer.materia,buffer.idMateria);
}

void mostrarNota(notaAlumno nota)
{
    printf("NOTA: %i, LEGAJO: %i, NOMBRE: %s \n",nota.nota,nota.legajo,nota.nombreApe);
}
void mostrarListaNotas(nodo *listaNotas)
{
    nodo *temp=listaNotas;
    while(temp!=NULL)
    {
        mostrarNota(temp->dato);
        temp=temp->siguiente;
    }
}

void mostrarListaCompleta(celda listaMaterias[],int validos)
{
    for(int x=0;x<validos;x++)
    {
        mostrarCelda(listaMaterias[x]);
        mostrarListaNotas(listaMaterias[x].listaDeNotas);
    }
}
void generarArchivoRegistros(char nombreArchivo[30])
{
    //IDS
    //QUIMICA 1
    //FISICA 2
    //MATEMATICA 3
    //LENGUA 4
    //ARTE 5


    FILE *archivo=fopen(nombreArchivo,"wb");
    registroArchivo listaDeAlumnos[]={
        //QUIMICA
        {10,10488,"Mariana Gomez","Quimica",1},
        {4,10588,"Lucas Penzoil","Quimica",1},
        {6,10722,"Miriam Saenz","Quimica",1},
        {9,10888,"Julio Cesar","Quimica",1},
        {7,10999,"Jesus de Nazareth","Quimica",1},
        //FISICA
        {7,10488,"Mariana Gomez","Fisica",2},
        {6,10588,"Lucas Penzoil","Fisica",2},
        {10,10722,"Miriam Saenz","Fisica",2},
        {7,10888,"Julio Cesar","Fisica",2},
        {10,10999,"Jesus de Nazareth","Fisica",2},
        //MATEMATICA
        {8,10488,"Mariana Gomez","Matematica",3},
        {8,10588,"Lucas Penzoil","Matematica",3},
        {8,10722,"Miriam Saenz","Matematica",3},
        {10,10888,"Julio Cesar","Matematica",3},
        {4,10999,"Jesus de Nazareth","Matematica",3},
        //LENGUA
        {10,10488,"Mariana Gomez","Lengua",4},
        {8,10588,"Lucas Penzoil","Lengua",4},
        {6,10722,"Miriam Saenz","Lengua",4},
        {10,10888,"Julio Cesar","Lengua",4},
        {10,10999,"Jesus de Nazareth","Lengua",4},
        //ARTE
        {6,10488,"Mariana Gomez","Arte",5},
        {7,10588,"Lucas Penzoil","Arte",5},
        {4,10722,"Miriam Saenz","Arte",5},
        {8,10888,"Julio Cesar","Arte",5},
        {8,10999,"Jesus de Nazareth","Arte",5}
        };

        for(int x=0;x<25;x++)
        {
            fwrite(&listaDeAlumnos[x],sizeof(registroArchivo),1,archivo);
        }
        fclose(archivo);

}

void purgarArchivo(char nombreArchivo[40])
{
    FILE *archivo=fopen(nombreArchivo,"w");
    {
        if(archivo)
        {
            fclose(archivo);
        }
    }
}
