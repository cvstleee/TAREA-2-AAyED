#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/
// TDA lista de números enteros

typedef struct nodo{
    int carga;
    int proceso;
    struct nodo *siguiente;
    }nodo;


typedef struct{
    nodo *inicio;
    }lista;


/*------------- operaciones -------------*/

// nueva_lista() retorna una lista vacía 
// orden de complejidad: O(1)
lista* nueva_lista();

// es_lista_vacia(l) determina si la lista l está vacía
// orden de complejidad: O(1)
int es_lista_vacia(lista *l);

// inserta_inicio(l, d) (l, ca, pro) inserta el dato de carga y proceso en la lista d 
// orden de complejidad: O(1)
void inserta_inicio(lista *l, int ca, int pro);

// elimina_inicio(l) elimina el primer elemento de la lista l 
// orden de complejidad: O(1)
void elimina_inicio(lista *l);

// imprime_lista(l) imprime por consola los elementos de la lista l
// orden de complejidad: O(n)
void imprime_lista(lista *l);

// libera_lista(l) libera la memoria asignada a la lista l
// orden de complejidad: O(n)
void libera_lista(lista *l);

//retorna la cantidad de nodos de una lista
//orden de complejidad: O(n)
int cuenta_nodos(lista *l);

// inserta_final(l, ca, pro) inserta el dato de carga y proceso en la lista l
// orden de complejidad: O(n)
void inserta_final(lista *l, int ca, int pro);

// elimina el nodo final en la lista l
// orden de complejidad: O(n)
void elimina_final(lista* l);

// elimina el nodo de la posición dada en la lista l
// orden de complejidad: O(n)
nodo* obtenerNodo(lista *l, int posicion);