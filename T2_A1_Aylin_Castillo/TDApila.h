#include <stdio.h> 
#include <stdlib.h>

/*------------- estructura de datos -------------*/
typedef struct nodoPila{
    int proceso;
    int tiempo;
    struct nodoPila *siguiente;
    }nodoPila;

typedef struct{
 	int size;
 	nodoPila *tope;
    }pila;


/*------------- operaciones -------------*/

// nueva_pila() retorna una pila vacía 
// orden de complejidad: O(1)
pila* nueva_pila(void);


// es_pila_vacia(p) determina si la pila p está vacía
// orden de complejidad: O(1)
int es_pila_vacia(pila *p);


/*------------- Actividad 1 -------------*/
// apilar(p, d) inserta el dato d al inicio de la pila p 
// orden de complejidad: O(1)
void apilar(pila *p, int pro, int tie);


// desapilar(p) elimina el primer elemento de la pila p 
// orden de complejidad: O(1)
void desapilar(pila *p);


// tope(p) retorna la dirección del primer elemento de la lista p
// orden de complejidad: O(1)
nodoPila* tope(pila *p);


// imprime_pila(p) imprime por consola los elementos de la pila p
// orden de complejidad: O(n)
void imprime_pila(pila *p);

// invierte la pila p 
// orden de complejidad: O(n)
pila * invertirPila(pila *p);