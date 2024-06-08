#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/
// TDA lista de números enteros

typedef struct nodo{
    int dato;
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

// inserta_inicio(l, d) inserta el dato d al inicio de la lista l 
// orden de complejidad: O(1)
void inserta_inicio(lista *l, int d);

// elimina_inicio(l) elimina el primer elemento de la lista l 
// orden de complejidad: O(1)
void elimina_inicio(lista *l);

// imprime_lista(l) imprime por consola los elementos de la lista l
// orden de complejidad: O(n)
void imprime_lista(lista *l);

// libera_lista(l) libera la memoria asignada a la lista l
// orden de complejidad: O(n)
void libera_lista(lista *l);

/*------------- actividad 2 -------------*/
//retorna la cantidad de nodos de una lista
//orden de complejidad: O(n)
int cuenta_nodos(lista *l);

/*------------- actividad 3 -------------*/
//busca un dato en la lista enlazada
//orden de conplejidad: O(n)
int busca_dato(lista *l, int d);

/*----------actividad 4------*/
//invierte el orden de los valores de una lista
//orden de complejidad: O(n)
lista* lista_inversa(lista *l);

/*----------actividad 5------*/
//genera dos listas, una con los n�meros menores o iguales que el n�mero en la posici�n indicada y otra con los n�meros mayores.
//orden de complejidad: O(n)
void numMenor_numMayor(lista *l, int x, lista *lista_menor, lista *lista_mayor);


/*-------actividad 6 asincrona------*/
void inserta_final(lista *l, int d);

void inserta_despues(lista *l, int valor, int datoAnterior);

void elimina_final(lista* l);

void eliminarDato(lista* l, int dato);

nodo* obtenerNodo(lista *l, int posicion);

lista *eliminarParentesis(lista *A);
lista *eliminarRepetidos(lista *A);

lista *mezclarListasOrdenadas(lista *A, lista *B);