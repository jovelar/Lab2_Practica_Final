typedef struct
{
    int dato;
    struct nodoArbol *izq;
    struct nodoArbol *der;
}nodoArbol

nodoArbol *inicArbol()
{
    return NULL;
}

nodoArbol *crearNodoArbol(int dato)
{
    nodoArbol *aux=malloc(sizeof(nodoArbol));
    
    aux->dato=dato;
    aux->izq=NULL;
    aux->der=NULL;
    
    return aux;
}

nodoArbol *buscar(nodoArbol *arbol,int dato)
{
    nodoArbol *rta=NULL;
    if(arbol!=NULL)          //SI EL ARBOL NO ESTA VACIO
    {
        if(dato==arbol->dato) //SI LO ENCUENTRA
        {
            rta=arbol;
        }
        else
        {
            if(dato > arbol->dato)
            {
                rta=buscar(arbol->der,dato);
            }
            else
            {
                rta=buscar(arbol->izq,dato);
            }
        }
    }
    return rta; //SI NO LO ENCUENTRA DEVUELVE NULL
}

nodoArbol *insertar(nodoArbol *arbol, int dato) //INSERTAR ORDENADO
{
    if(arbol==NULL) //SI ESTA VACIO
    {
        arbol=crearNodoArbol(dato);
    }
    else
    {
        if(dato > arbol->dato)  //SI EL DATO ES MAYOR, LO INSERTA 
        {                       //EN RAMA DERECHA, SINO IZQUIERDA
            arbol->der=insertar(arbol->der,dato);
        }
        else
        {
            arbol->izq=insertar(arbol->izq,dato);
        }
    }
    return arbol;
}

////////////////////////////////////////////////////////////
//////FORMAS DE MOSTRAR UN ARBOL: 3 ALGORITMOS//////////////
////////////////////////////////////////////////////////////

//PREORDEN (RAIZ, IZQUIERDO, DERECHO)

void preorder(nodoArbol *arbol)
{
    if(arbol!=NULL)
    {
        printf("%d",arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

//INORDER (IZQUIERD,RAIZ,DERECHO)
void inorder(nodoArbol *arbol)
{
    if(arbol!=NULL)
    {
        inorder(arbol->izq);
        printf("%d",arbol->dato);
        inorder(arbol->der);
    }
}

//POSTORDER (IZQUIERDO,DERECHO,RAIZ)
void postOrder(nodoArbol *arbol)
{
    if(arbol!=NULL)
    {
        postOrder(arbol->izq);
        postOrder(arbol->der);
        printf("%d",arbol->dato);
    }
}

