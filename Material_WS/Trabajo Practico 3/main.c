#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
//Extras.
void mostrarInt_archivo(char archivoNombre[]);


int factorial(int x);
int factoria2(int x);
int potencia(int base, int exponente);
int potencia2(int base, int exponente);
void mostrarArreglo(int arreglo[], int validos);
void mostrarArreglo_ej4(int arreglo[], int validos, int comienzo); // 4
int es_capicua(int arreglo[], int desde, int hasta); // 5
int sumaElementos(int arreglo[], int validos);       // 6
int sumaElementos_Ninja(int arreglo[], int validos); // 6
int menor(int arreglo[], int desde, int hasta);       // 7
void guardar_archivo(char nombreArchivo[]);         // 8 para cargar datos ejecuto una vez
int menor_archivo(char archivoNombre[]);            // 8 funcion que abre el archivo e inicializa el primero
int buscarMenor_archivo(FILE* archivo, int menor);  // 8 busca un el minimo de un archivo en comparación a uno ingresado
void invertirElementos_archivo(char archivoNombre[]); // 9 contenerdor de las funciones
int contarElementos_archivo(FILE * archivo);        // 9
void invertir_archivo(FILE * archivo, int desde, int hasta); // 9 este es el que invierte
void mostrarInvertido_archivo(FILE * archivo, int bytes); //10
void guardarCaracter(); // 11
char leerCadena(); //11
void mostraCadenaInvertiro();  //11
void Borrar(); //11

int contiene(int arreglo[],int desde,int validos,int elemento); // 12

int main()
{
    setlocale(LC_ALL,"");
    ////////////////////////////////////////////////////////////////////// Ejercicio 1 //////////////////////////////////////////////////////////////////

//    printf("Resultado ej 1: %d\n", factorial(4));
//    printf("Resultado ej 1: de la ninja %d\n", factorial2(4));

    ////////////////////////////////////////////////////////////////////// Ejercicio 2 //////////////////////////////////////////////////////////////////

//    printf("El resultado de la potencia es %d", potencia2(2,3));

    ////////////////////////////////////////////////////////////////////// Ejercicio 3 //////////////////////////////////////////////////////////////////

//    int arreglo_ej3[10] = {1,2,3,4};
//    int validos_ej3 = 4;
//    mostrarArreglo(arreglo_ej3, validos_ej3);

    ////////////////////////////////////////////////////////////////////// Ejercicio 4 ////////////////////////////////////////////////////////////////·//

//    int arreglo_ej4[10] = {1,2,3,4};
//    int validos_ej4 = 4;
//    mostrarArreglo_ej4(arreglo_ej4, validos_ej4, 0);

    ////////////////////////////////////////////////////////////////////// Ejercicio 5 ////////////////////////////////////////////////////////////////·//

//    int arreglo_ej5[10] = {1,2,3,2,1};
//    int validos_ej5 = 5;
//
//    if(es_capicua(arreglo_ej5, 0, validos_ej5-1)) // recordar que el indice del ultimo es validos-1
//    {
//        printf("Es capicua. \n");
//    } else
//    {
//        printf("No es capicua. \n");
//    }

    ////////////////////////////////////////////////////////////////////// Ejercicio 6 ////////////////////////////////////////////////////////////////·//

//    int arreglo_ej6[10] = {1,2,3,4};
//    int validos_ej6 = 4;
//    printf("La sumatoria es = %d \n", sumaElementos(arreglo_ej6, validos_ej6-1));

    ////////////////////////////////////////////////////////////////////// Ejercicio 7 ////////////////////////////////////////////////////////////////·//

//    int arreglo_ej7[10] = {2,1,7,4};
//    int validos_ej7 = 4;
//    printf("El menor es = %d \n", menor(arreglo_ej7, 0, 3));

    ////////////////////////////////////////////////////////////////////// Ejercicio 8 ////////////////////////////////////////////////////////////////·//

//    char nombreArchivo_ej8[30] = "archivosConNumeros.bin";
////    guardar_archivo(nombreArchivo); // esto para cargar datos uso una vez
//    printf("El menor en el archivo es: %d", menor_archivo(nombreArchivo_ej8));


    ////////////////////////////////////////////////////////////////////// Ejercicio 9 ////////////////////////////////////////////////////////////////·//

//    char nombreArchivo_ej9[30] = "archivosConNumeros_ej9.bin";
////    guardar_archivo(nombreArchivo_ej9); // esto para cargar datos uso una vez
//    mostrarInt_archivo(nombreArchivo_ej9);
//    printf("Luego de invertir: \n\n");
//    invertirElementos_archivo(nombreArchivo_ej9);
//    mostrarInt_archivo(nombreArchivo_ej9);

    ////////////////////////////////////////////////////////////////////// Ejercicio 10 ////////////////////////////////////////////////////////////////·//
////    guardar_archivo("archivo_ej10.bin");
//    printf("El archivo contiene: \n");
//    mostrarInt_archivo("archivo_ej10.bin");
//
//    FILE * archivo_ej10 = fopen("archivo_ej10.bin", "r+b");
//    if(archivo_ej10 != NULL)
//    {
//        fseek(archivo_ej10,0,SEEK_END);
//        int bytes_ej10 = ftell(archivo_ej10) - sizeof(int);
//        mostrarInvertido_archivo(archivo_ej10, bytes_ej10);
//        fclose(archivo_ej10);
//    } else
//    {
//        printf("Error cargar archivo ejercicio 10.\n");
//    }

    ////////////////////////////////////////////////////////////////////// Ejercicio 11 ////////////////////////////////////////////////////////////////·//

mostraCadenaInvertiro();

    ////////////////////////////////////////////////////////////////////// Ejercicio 12 ////////////////////////////////////////////////////////////////·//

//    int arreglo_ej12[10] = {3,54,67,2,24} ;
//    int elemento = 1;
//    if (contiene(arreglo_ej12,0, 5, elemento))
//    {
//        printf("Si el elemento : %d, se encuentra en el arreglo.\n", elemento);
//    }else
//    {
//        printf("NO se encuentra el elemento : %d en el arreglo.\n", elemento);
//    }



    printf("\n\n                                            Fin programa\n");
    return 0;
}
// 1. Calcular el factorial de un número en forma recursiva.
int factorial(int x)
{
    int rta = 0;
    if(x == 0)
    {
        rta = 1;
    }
    else
    {
        rta = x * factorial(x-1);
    }
    return rta;
}

int factorial2(int x) // a lo ninja, no es legible para juniors
{
    return (x == 0) ? 1 : x * factorial2(x-1);
}

// 2. Calcular la potencia de un número en forma recursiva.
int potencia(int base, int exponente)
{
    int resultado;
    if(exponente == 0)
    {
        resultado = 1;
    }
    else
    {
        resultado = base * potencia(base, exponente - 1);
    }

    return resultado;
}

int potencia2(int base, int exponente)
{
    return (exponente == 0) ? 1 : base * potencia(base, exponente -1);
}

// 3. Recorrer un arreglo y mostrar sus elementos en forma recursiva.
// Los deje invertidos, comienzo mostrando el ultimo y voy hasta la posición 0
void mostrarArreglo(int arreglo[], int validos)
{
    if(validos > 0)
    {
        printf("[%d]", arreglo[validos - 1]);
        mostrarArreglo(arreglo, validos-1);
    }
}

// 4. Recorrer un arreglo comenzando desde la posición 0 y mostrar sus elementos en forma invertida (recursivo).
void mostrarArreglo_ej4(int arreglo[], int validos, int comienzo)
{
    if(comienzo==validos-1) // no olvidar que los validos son uno mas que el indice
    {
        printf("[%d]", arreglo[comienzo]);
    } else
    {
        printf("[%d]", arreglo[comienzo], comienzo);
        mostrarArreglo_ej4(arreglo, validos, comienzo+1);
    }
}

// 5. Determinar en forma recursiva si un arreglo es capicúa.
int es_capicua(int arreglo[], int desde, int hasta)
{
    int esCapicua = 1; // true
    if(desde < hasta)
    {
        if(arreglo[desde] == arreglo[hasta])
        {
            esCapicua = es_capicua(arreglo, desde+1, hasta-1);
        } else
        {
            esCapicua = 0; // false
        }
    }
    return esCapicua;
}

// 6. Sumar en forma recursiva los elementos de un arreglo de enteros y retornar el total de la suma.

int sumaElementos(int arreglo[], int posicionUltimo)
{
    int acumulador = 0;
    if(posicionUltimo == 0)
    {
        acumulador += arreglo[posicionUltimo];
    } else
    {
        acumulador += arreglo[posicionUltimo] + sumaElementos(arreglo, posicionUltimo-1);
    }
}
int sumaElementos_Ninja(int arreglo[], int validos)
{
    int acumulador = 0;
    if(validos > 0)
    {
        acumulador += arreglo[--validos] + sumaElementos_Ninja(arreglo, validos);
    }
}

// 7. Buscar el menor elemento de un arreglo en forma recursiva. muestra: 2,1,7,4
int menor(int arreglo[], int desde, int hasta)
{
    int minimo;
    if(desde == hasta)
    {
        minimo = arreglo[hasta];
    } else
    {
        minimo = menor(arreglo, desde + 1, hasta);
        if(minimo > arreglo[desde])
        {
            minimo = arreglo[desde];
        }
    }
    return minimo;
}

// 8

void guardar_archivo(char nombreArchivo[])
{
    FILE * archivo = fopen(nombreArchivo, "w+b");
    if (archivo != NULL)
    {
        char option = 's';
        int number;
        while(option != 27 )
        {
            printf("Ingrese un numero: ");
            fflush(stdin);
            scanf("%d", &number);
            fwrite(&number, sizeof(number), 1, archivo);

            printf("¿Continuar? Salir = ESC \n");
            fflush(stdin);
            option = getch();

        }
        fclose(archivo);
    } else
    {
        printf("Error al abrir el archivo en guardar_archivo.\n");
    }
}

// 8. Buscar el menor elemento de un archivo de números enteros de forma recursiva. (desde el mismo archivo)
int buscarMenor_archivo(FILE* archivo, int menor)
{
    int numeroActual;
    if(fread(&numeroActual, sizeof(numeroActual), 1, archivo) > 0 ) // Si aun quedan numeros
    {
        if(numeroActual < menor)
        {
            menor = numeroActual;
        }
        menor = buscarMenor_archivo(archivo, menor);
    }
    return menor;
}

int menor_archivo(char archivoNombre[])
{
    int menor;
    int aux;
    FILE * archivo = fopen(archivoNombre, "r+b");
    if(archivo != NULL)
    {
        fread(&aux, sizeof(aux),1,archivo);
        menor = aux; // inicializo con el primer valor
        menor = buscarMenor_archivo(archivo, menor); // busco si existe otro...
        fclose(archivo);
    } else
    {
        printf("Error al abrir el archivo en funcion menor_archivo.\n");
    }
    return menor;
}



// 9. Invertir los elementos de un archivo de números enteros de forma recursiva.
//  (si no te sale, primero proba con invertir los elementos de un arreglo de int)

void invertirElementos_archivo(char archivoNombre[])
{
    int hasta;
    FILE * archivo = fopen(archivoNombre, "r+b");
    if(archivo != NULL)
    {
        hasta = contarElementos_archivo(archivo) -1 ;
        invertir_archivo(archivo, 0, hasta);
        fclose(archivo);
    } else
    {
        printf("Error al cargar el archivo en invertirElementos_archivo.\n");
    }
}

int contarElementos_archivo(FILE * archivo)
{
    int cantidad = 0;
    int inicio = ftell(archivo);
    fseek(archivo, 0, SEEK_END);
    cantidad = ftell(archivo)/ sizeof(int);
    fseek(archivo, inicio, SEEK_SET);
    return cantidad;
}

void invertir_archivo(FILE * archivo, int desde, int hasta)
{
    int numeroInicial;
    int numeroFinal;
    if(desde < hasta)
    {
        fseek(archivo, sizeof(numeroInicial) * desde, SEEK_SET);
        fread(&numeroInicial, sizeof(numeroInicial), 1, archivo); // guardo el inicio

        fseek(archivo, sizeof(numeroFinal) * hasta, SEEK_SET);
        fread(&numeroFinal, sizeof(numeroFinal), 1, archivo); // guardo el final

        //Paro y guardo en primero
        fseek(archivo, sizeof(numeroInicial) * desde, SEEK_SET);
        fwrite(&numeroFinal, sizeof(numeroInicial), 1, archivo);
        //Paro y guardo en ultimo
        fseek(archivo, sizeof(numeroFinal) * hasta, SEEK_SET);
        fwrite(&numeroInicial, sizeof(numeroFinal), 1, archivo);

        invertir_archivo(archivo, desde+1, hasta-1);
    }
}


void mostrarInt_archivo(char archivoNombre[])
{
    FILE * archivo = fopen(archivoNombre, "r+b");
    if(archivo != NULL)
    {
        int numeroActual;
        while(fread(&numeroActual, sizeof(numeroActual),1,archivo) > 0)
        {
            printf("[%d]", numeroActual);
        }
        printf("\n");
        fclose(archivo);
    } else
    {
        printf("Error al cargar el archivo en mostrarInt_archivo.\n");
    }
}


// 10. Recorrer un archivo y mostrar sus elementos en forma invertida de forma recursiva.

void mostrarInvertido_archivo(FILE * archivo, int bytes) // se puede armar la version ninja pero lo dejo aca
{
    int numeroActual;
    fseek(archivo, bytes, SEEK_SET);
    if(bytes == 0)
    {
        fread(&numeroActual, sizeof(numeroActual),1,archivo);
        printf("[%d]", numeroActual);
    } else
    {
        fread(&numeroActual, sizeof(numeroActual),1,archivo);
        printf("[%d]", numeroActual);
        bytes -= sizeof(numeroActual);
        mostrarInvertido_archivo(archivo, bytes);
    }
}


// 11. Ingresar valores a una variable de tipo char (por teclado) y mostrarlo en el orden
//      inverso (hasta ingresar un ‘*’) de forma recursiva. NO usar arreglos.

void guardarCaracter()
{
    FILE * archivo = fopen("archivo_j11.bin", "ab");
    if(archivo!=NULL)
    {
        char tecla;
        printf("\nIngrese un caracter: ");
        fflush(stdin);
        tecla = getch();
        fwrite(&tecla,sizeof(tecla),1,archivo);
        fclose(archivo);
    } else
    {
        printf("Error al abrir el archivo en mostrarCadena\n");
    }
}

char leerCadena()
{
    FILE * archivo = fopen("archivo_j11.bin", "r+b");
    char ultimaLetra;
    if(archivo!=NULL)
    {
        // Leo la ultima para hacerlo de corte luego
        fseek(archivo, -sizeof(char), SEEK_END);
        fread(&ultimaLetra, sizeof(ultimaLetra), 1,archivo);

        // calculo los bytes para mostrar del final hacia el inicio
        int bytes = ftell(archivo);
        bytes -= sizeof(char);              // resto un modulo porque el final no me sirve para leer
        fseek(archivo, bytes, SEEK_SET);    // Ahora dejo el puntero al inicio del ultimo char

        char letra;
        printf("Cadena: [");
        while(bytes >= 0)
        {
            fread(&letra, sizeof(letra),1,archivo);
            printf("%c", letra);
            bytes -= 2 * sizeof(char);
            fseek(archivo, bytes, SEEK_SET);
        }
        printf("]");
        fclose(archivo);
    } else
    {
//        printf("Error al abrir el archivo en leerCadena\n");
    }
    return ultimaLetra;
}

void mostraCadenaInvertiro()
{
    if(leerCadena() != 42)
    {
        guardarCaracter();
        mostraCadenaInvertiro();
    }
    Borrar();
}

void Borrar()
{
    FILE * archivo = fopen("archivo_j11.bin", "wb");
    if(archivo!=NULL)
    {
        fclose(archivo);
    } else
    {
        printf("Error al abrir el archivo en Borrar\n");
    }
}



// 12. Determinar si un arreglo contiene un determinado elemento de forma recursiva.
//      (Pueden intentarlo también con una función void)(Tener en cuenta para un arreglo
//      desordenado y el caso para un arreglo ordenado)
int contiene(int arreglo[],int desde,int validos,int elemento)
{
    int encuentra = 0;
    if(desde < validos)
    {
        if(arreglo[desde] == elemento)
        {
            encuentra = 1;
        } else
        {
            encuentra = contiene(arreglo, desde + 1,validos, elemento);
        }
    }
    return encuentra;
}

