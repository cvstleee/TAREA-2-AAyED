#include <stdio.h>
#include <stdlib.h>
#include "TDAlistaPila.h"

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

// Función para eliminar un nodo con una posición específica de la lista de pilas
void eliminarNodoListaPila(listaPila* lista, int posicion) {
    nodoListaPila* temp = lista->inicio;
    nodoListaPila* prev = NULL;

    // Caso en el que el nodo a eliminar es el nodo inicio
    if (temp != NULL && temp->posicion == posicion) {
        lista->inicio = temp->siguiente;
        free(temp->pilaDatos); // Suponemos que también hay que liberar la pila
        free(temp);
        return;
    }

    // Buscar el nodo a eliminar y mantener el nodo previo
    while (temp != NULL && temp->posicion != posicion) {
        prev = temp;
        temp = temp->siguiente;
    }

    // Si la posición no se encuentra en la lista
    if (temp == NULL) {
        printf("Posición no encontrada en la lista\n");
        return;
    }

    // Desconectar el nodo a eliminar de la lista enlazada
    prev->siguiente = temp->siguiente;

    // Liberar memoria del nodo eliminado
    free(temp->pilaDatos); // Suponemos que también hay que liberar la pila
    free(temp);
}
