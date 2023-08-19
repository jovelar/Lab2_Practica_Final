typedef struct
{
	int dato;
	struct nodo *siguiente;
}nodo;

nodo *agragarUltimoRecursivo(nodo *lista,nodo *nuevo)
{
	if(lista==NULL)
	{
		lista=nuevo;
	}
	else
	{
		lista->siguiente=agregarUltimoRecursivo(lista->siguiente,nuevo);
	}
	return lista;
}

void recorrerYmostrar(nodo *lista)
{
	if(lista!=NULL)
	{
		printf("%d",lista->dato);
		recorrerYmostrar(lista->siguiente);
	}
}

nodo *borrarNodoR(nodo *lista,int dato)
{
	nodo *aBorrar=NULL;
	if(lista->dato==dato)
	{
		aBorrar=lista;
		lista=lista->siguiente;
		free(aBorrar);
	}
	else
	{
		lista->siguiente=borrarNodoR(Lista->siguiente,dato);
	}
	return lista;
}