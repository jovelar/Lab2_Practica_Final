#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char palabra[50]; //PALABRA CLAVE
    int dato;         //VALOR ASOCIADO
    char frase[50];   //FRASE CON PALABRA CLAVE
    int numero;       //VALOR ASOCIADO
}stRegistro;

typedef struct
{
    char palabra[50];
    int dato;
}DatoNodoLS;

typedef struct
{
    DatoNodoLS datoNodoLS;
    struct NodoLD *listaSecundaria;
    struct NodoLS *siguiente;
}NodoLS;

typedef struct
{
    char frase[50];
    int numero;
}DatoNodoLD;

typedef struct
{
    DatoNodoLD datoNodoLD;
    struct NodoLD *nodoslD;
}NodoLD;


////////FUNCIONES LISTA SIMPLE////////
NodoLS *inicLS();
NodoLS *nuevoNodoLS(NodoLS *lista,NodoLS *nuevo);
NodoLS *insertarOrdenadoLS(NodoLS lista,NodoLS *nuevo);
NodoLS *insertarAlPrincipio();
NodoLS *insertarAlFinal();
NodoLS *buscarLS(NodoLS *lista);
NodoLS *borrarNodoLS(NodoLS *lista,char palabraABuscar[50]);

////////FUNCIONES LISTA DOBLE////////
NodoLD *inicLD();
NodoLD *nuevoNodoLD(DatoNodoLD datoNodoLD);
NodoLD *insertarOrdenado(NodoLD *lista,NodoLD *nuevo);
NodoLD *buscarLD(NodoLD *lista,char frase[50]);
NodoLD *borrarNodoLD(NodoLD *lista,char palabra[50]);

////////FUNCIONES VARIAS/////////////
void mostrarLDL(NodoLS *lista);
void mostrarNodoLS(NodoLS *nodo);
void mostrarLS(NodoLS *lista);
void mostrarNodoLD(NodoLD *nodo);
void mostrarLD(NodoLD *lista);
NodoLS *pasarDeArchivoALDL(char nombreArchivo[50]);
void generarArchivoRegistros(char nombreArchivo[50]);

int main()
{
    int opcion=0;
    while(opcion!=27)
    {
        system("cls");
        opcion=menu();
        switch(opcion)
        {
        case 27:
            system("cls");
            break;
        case 49:
            system("cls");
            printf(" 1- No implementado aun!\n");
            system("pause");
            break;
        case 50:
            system("cls");
            printf(" 2- No implementado aun!\n");
            system("pause");
            break;
        case 57:
            system("cls");
            generarArchivoRegistros("registros.bin");
            printf("\nRegistros.bin creado!\n");
            system("pause");
            break;
        default:
            system("cls");
            printf("Opcion invalida!\n");
            break;
        }
    }
    return 0;
}

int menu()
{
    int opc;
    printf("1- Pasar archivo a LDL\n"); //49
    printf("2- Mostrar LDL\n");//50
    printf("7- Generar archivo de registros\n");
    printf("\n\nESC- SALIR: "); //27
    opc=getch();
    return opc;
}

NodoLS *pasarDeArchivoALDL(char nombreArchivo[50])
{
    FILE *archivo=fopen(nombreArchivo,"r");
    if(archivo)
    {
        NodoLD *nuevaLista=NULL;
        stRegistro buffer;
        while(fread(&buffer,sizeof(stRegistro),1,archivo)>0)
        {
            if(nuevaLista==NULL)
            {
                NodoLS *nuevo=nuevoNodoLS()
            }
        }
    }
    NodoLD *listaNueva;

}

void generarArchivoRegistros(char nombreArchivo[50])
{
    FILE *archivo=fopen(nombreArchivo,"wb");
    if(archivo)
    {
        stRegistro registros[]=
        {
            {"Dimension",1,"La dimension desconocida",1},
            {"Dimension",1,"Dimension oscura",2},
            {"Paz",1,"La guerra y la paz",3},
            {"Paz",1,"La paz de los mundos",4},
            {"Pesos",1,"El peso se desvaloriza",5},
            {"Pesos",1,"El peso",6},
            {"Pesos",1,"Cuestion de peso",7},
            {"Pesos",1,"El peso no sirve",8}
        };
        for(int x=0;x<8;x++)
        {
            fwrite(&registros[x],sizeof(stRegistro),1,archivo);
        }
        fclose(archivo);
    }
    else
    {
        printf("\nNo se pudo encontra el archivo.\n");
        system("pause");
    }
}
