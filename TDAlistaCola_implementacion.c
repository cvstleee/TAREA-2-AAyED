#include <stdio.h>
#include <stdlib.h>
#include "TDAlistaCola.h"

/*------------- operaciones -------------*/



//crear lista
listaCola *nueva_listaCola(){
    listaCola *l = (listaCola*)malloc(sizeof(listaCola));
    l ->inicio = NULL;
    return l;
}

int es_listaCola_vacia(listaCola *l){
    if (l->inicio == NULL)
        return 1;
    else
      return 0;
    }

void imprime_listaCola(listaCola *l){
    printf("Lista con las siguientes colas de procesos: \n");
    if (!es_listaCola_vacia(l)){
        nodoListaCola *aux = l->inicio;
        while (aux != NULL){
            printf("proceso: %i, cargas procesadas: \n", aux->numeroProceso);
            imprime_cola(aux->colaProceso);
            aux = aux->siguiente;
            }
        printf("\n");
        }
    else
        printf("%c\n", 157);
    }

void elimina_inicioListaCola(listaCola *l){
    nodoListaCola *aux;
    if(!es_listaCola_vacia(l)){
        aux = l->inicio;
        l->inicio = l->inicio->siguiente;
        free(aux);
        }
    }

void libera_listaCola(listaCola *l){
    while (!es_listaCola_vacia(l)){
        elimina_inicioListaCola(l);
        }
    free(l);
	}

void insertarCola(listaCola *l, int numProceso, cola *c) {
    //printf("se esta insertando la cola \n");
    imprime_cola(c); //me esta dando 27 3 ?
    nodoListaCola *nuevoNodo = (nodoListaCola*)malloc(sizeof(nodoListaCola));
    nuevoNodo->numeroProceso = numProceso;
    nuevoNodo->colaProceso = c;
    nuevoNodo->siguiente = NULL;

    if (l->inicio == NULL) {
        // La lista está vacía, insertar el nuevo nodo como el primero
        l->inicio = nuevoNodo;
    } else {
        // La lista no está vacía, encontrar el último nodo e insertar el nuevo nodo
        nodoListaCola *final = l->inicio;
        while (final->siguiente != NULL) {
            final = final->siguiente;
        }
        final->siguiente = nuevoNodo;
    }
}