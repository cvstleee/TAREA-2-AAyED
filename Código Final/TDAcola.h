#include <stdio.h>
#include <stdlib.h>
//#include "TDAlista.h"

/*------------- estructura de datos -------------*/
// TDA cola de números enteros
//dato sería el número de la carga
typedef struct nodoCola{
    int dato;
    struct nodoCola *siguiente;
    }nodoCola;


typedef struct{
	int size;
	nodoCola *n_frente;
	nodoCola *n_final;
	}cola;


/*------------- operaciones -------------*/

// crea_cola_vacia() retorna una cola vacía 
// orden de complejidad: O(1)
cola* crea_cola_vacia(void);


// verifica si la cola c está vacía o no retorna 0 o 1.
// orden de complejidad: O(1)
int es_cola_vacia(cola *c);


// agrega a la cola c un nuevo dato.
// orden de complejidad: O(1)
void encolar(cola* c, int dato);


// eliminna de la cola c un dato
// orden de complejidad: O(1)
void descolar(cola *c);


// Devuelve un puntero al primer nodo de la cola c.
// orden de complejidad: O(1)
nodoCola* frente(cola *c);


// Libera la memoria la memoria del acola c.
// orden de complejidad: O(n)
void liberar_cola(cola *c);

// Imprime los datos de la cola
// orden de complejidad: O(n)
void imprime_cola(cola *c);