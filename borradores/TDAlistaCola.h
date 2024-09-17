#include <stdio.h>
#include <stdlib.h>
#include "TDAcola.h"

/*------------- estructura de datos -------------*/
// TDA lista para almacenar pilas + su respectiva posición

typedef struct nodoListaCola{
    int numeroProceso; 
    cola *colaProceso; 
    struct nodoListaCola *siguiente;
    }nodoListaCola;


typedef struct{
    nodoListaCola *inicio;
    }listaCola;


/*------------- operaciones -------------*/

//crear lista
listaCola *nueva_listaCola();

int es_listaCola_vacia(listaCola *l);

void imprime_listaCola(listaCola *l);

void libera_listaCola(listaCola *l);

void elimina_inicioListaCola(listaCola *l);

void insertarCola(listaCola *l, int numProceso, cola *c);
