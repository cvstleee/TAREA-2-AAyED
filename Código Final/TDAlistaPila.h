#include <stdio.h>
#include <stdlib.h>
#include "TDApila.h"

/*------------- estructura de datos -------------*/

typedef struct nodoListaPila{
    int posicion;
    pila *pilaDatos;
    struct nodoListaPila *siguiente;
    }nodoListaPila;


typedef struct{
    nodoListaPila *inicio;
    }listaPila;


/*------------- operaciones -------------*/

//crear lista pila vacía
//orden de complejidad O(1)
listaPila *nueva_listaPila();

//verifica si es una lista pila vacía
//orden de complejidad O(1)
int es_listaPila_vacia(listaPila *l);

//inserta una pila en la lista l con su respectiva posición, simula el inserta_inicio junto al inserta_final
//orden de complejidad O(n)
void insertarPila(listaPila *l, int posicion, pila *p);

//imprime datos lista pila
//orden de complejidad O(n)
void imprime_listaPila(listaPila *l);

//libera lista pila
//orden de complejidad O(n)
void libera_listaPila(listaPila *l);

//elimina el primer nodo de la lista pila
//orden de complejidad O(1)
void elimina_inicioListaPila(listaPila *l);

//elimina el nodo según la posición dada de la lista pila
//orden de complejidad O(n)
void eliminarNodoListaPila(listaPila* lista, int posicion);
