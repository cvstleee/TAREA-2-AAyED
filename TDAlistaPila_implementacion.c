#include <stdio.h>
#include <stdlib.h>
#include "TDAlistaPila.h"

/*------------- operaciones -------------*/



//crear lista
listaPila *nueva_listaPila(){
    listaPila *l = (listaPila*)malloc(sizeof(listaPila));
    l ->inicio = NULL;
    return l;
}

int es_listaPila_vacia(listaPila *l){
    if (l->inicio == NULL)
        return 1;
    else
      return 0;
    }


//cambiarlo para que inserte al final, idea chatgpt:

// Función para insertar un nodo al final de la lista de pilas
//simula el insertar inicio y final
void insertarPila(listaPila *l, int posicion, pila *p) {
    nodoListaPila *nuevoNodo = (nodoListaPila*)malloc(sizeof(nodoListaPila));
    nuevoNodo->posicion = posicion;
    nuevoNodo->pilaDatos = p;
    nuevoNodo->siguiente = NULL;

    if (l->inicio == NULL) {
        // La lista está vacía, insertar el nuevo nodo como el primero
        l->inicio = nuevoNodo;
    } else {
        // La lista no está vacía, encontrar el último nodo e insertar el nuevo nodo
        nodoListaPila *final = l->inicio;
        while (final->siguiente != NULL) {
            final = final->siguiente;
        }
        final->siguiente = nuevoNodo;
    }
}

/*void insertarPila(listaPila *l, int posicion, pila *p) {
    nodoListaPila *nuevoNodo = (nodoListaPila*)malloc(sizeof(nodoListaPila));
    nuevoNodo->posicion = posicion;
    nuevoNodo->pilaDatos = p;
    nuevoNodo->siguiente = l->inicio;
    l->inicio = nuevoNodo;
}*/

void imprime_listaPila(listaPila *l){
    printf("Lista con las siguientes pilas: \n");
    if (!es_listaPila_vacia(l)){
        nodoListaPila *aux = l->inicio;
        while (aux != NULL){
            printf("carga: %i datos pila: \n", aux->posicion);
            imprime_pila(aux->pilaDatos);
            aux = aux->siguiente;
            }
        printf("\n");
        }
    else
        printf("%c\n", 157);
    }


void libera_listaPila(listaPila *l){
    while (!es_listaPila_vacia(l)){
        elimina_inicioListaPila(l);
        }
    free(l);
	}

void elimina_inicioListaPila(listaPila *l){
    nodoListaPila *aux;
    if(!es_listaPila_vacia(l)){
        aux = l->inicio;
        l->inicio = l->inicio->siguiente;
        free(aux);
        }
    }