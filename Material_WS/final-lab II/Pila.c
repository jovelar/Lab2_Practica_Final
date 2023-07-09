#include "Pila.h"

void inicPila(Pila* p)
{
    (*p).tope = -1;
}

int tope(Pila p)
{
    return p.arreglo[p.tope];
}

int pilavacia(Pila p)
{
    return (p.tope == -1);
}


void apilar(Pila* p,int dato)
{
 ///completar
    if(p->arreglo[p->tope] < 50){
        p->arreglo[p->tope] = dato;
        p->tope++;
    }else{
        printf(" La pila esta llena. \n\n");
    }
}

int desapilar(Pila* p)
{
  ///completar
  int extraer;

  if(p->tope != -1){
    extraer = p->arreglo[p->tope];
  }

  return extraer;

}


void mostrar(Pila p)
{
    printf("BASE ....");
    for(int i = 0; i <= p.tope; i++)
    {
        printf("%i ", p.arreglo[i]);
    }
    printf("....TOPE\n");
}

