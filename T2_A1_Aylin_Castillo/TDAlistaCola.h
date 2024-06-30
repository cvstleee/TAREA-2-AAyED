#include <stdio.h>
#include <stdlib.h>
#include "TDAcola.h"

/*------------- estructura de datos -------------*/

typedef struct nodoListaCola{
    int numeroProceso; 
    cola *colaProceso; 
    struct nodoListaCola *siguiente;
    }nodoListaCola;


typedef struct{
    nodoListaCola *inicio;
    }listaCola;


/*------------- operaciones -------------*/

//crear lista cola vacía
//orden de complejidad O(1)
listaCola *nueva_listaCola();

//verifica si es una lista cola vacía
//orden de complejidad O(1)
int es_listaCola_vacia(listaCola *l);

//imprime datos lista cola 
//orden de complejidad O(n)
void imprime_listaCola(listaCola *l);

//libera lista cola 
//orden de complejidad O(n)
void libera_listaCola(listaCola *l);

//elimina el primer nodo de la lista cola
//orden de complejidad O(1)
void elimina_inicioListaCola(listaCola *l);

//inserta una cola en la lista l con su respectiva posición, simula el inserta_inicio junto al inserta_final
//orden de complejidad O(n)
void insertarCola(listaCola *l, int numProceso, cola *c);
