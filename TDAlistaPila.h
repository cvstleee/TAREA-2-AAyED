#include <stdio.h>
#include <stdlib.h>
#include "TDApila.h"

/*------------- estructura de datos -------------*/
// TDA lista para almacenar pilas + su respectiva posición

typedef struct nodoListaPila{
    int posicion;
    pila *pilaDatos;
    struct nodoListaPila *siguiente;
    }nodoListaPila;


typedef struct{
    nodoListaPila *inicio;
    }listaPila;


/*------------- operaciones -------------*/

//crear lista
listaPila *nueva_listaPila();

int es_listaPila_vacia(listaPila *l);

void insertarPila(listaPila *l, int posicion, pila *p);

void imprime_listaPila(listaPila *l);


void libera_listaPila(listaPila *l);

void elimina_inicioListaPila(listaPila *l);