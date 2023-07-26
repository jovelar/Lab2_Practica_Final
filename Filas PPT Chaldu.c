typedef struct
{
	struct Nodo2 *cabecera;
	struct Nodo2 *cola;
}Fila;

typedef struct
{
	int dato;
	struct Nodo2 *ste;
	struct Nodo2 *ante;
}Nodo2;

void inicFila(Fila *fila)
{
    fila->cabecera=inicLista();
    fila->cola=inicLista();
}

void agregar(Fila *fila, int dato)
{
    Nodo2 *nuevo=crearNodo(dato);
    if(fila->cabecera==NULL)
    {
        fila->cabecera=nuevo;
        fila->cola=nuevo;
    }
    else
    {
        fila->cabecera=agregarAlFinal(fila->cabecera,nuevo);
        fila->cola=nuevo;
    }
}

int verPrimero(Nodo2 *lista)
{
    int reespuesta=0;
    if(lista)
    {
        respuesta=lista->dato;
    }
    return respuesta;
}

int extraer(Fila *fila)
{
    int respuesta;
    if(fila->inicio!=NULL)
    {
        respuesta=verPrimero(fila->inicio);
        fila->inicio=borrarPrimero(fila->inicio);
        if(fila->inicio==NULL)
        {
            fila->fin=inicLista();
        }
    }
    return respuesta;
}
