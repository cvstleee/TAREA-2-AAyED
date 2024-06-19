#include <stdio.h>
#include <stdlib.h>
#include "TDAcola.h"



nodoCola* crea_nodo(int dato){
	nodoCola *nuevo_nodo = (nodoCola*)malloc(sizeof(nodoCola));
	nuevo_nodo->dato = dato;
	nuevo_nodo->siguiente = NULL;
	return nuevo_nodo;
	}


cola* crea_cola_vacia(void){
	cola *c = (cola*)malloc(sizeof(cola));
	c->size = 0;
	c->n_frente = NULL;
	c->n_final = NULL;
	return c;
	}


int es_cola_vacia(cola *c){
	if (c->size == 0)
		return 1;
	return 0;
	}


void encolar(cola* c, int dato){
    nodoCola *nuevo_nodo = crea_nodo(dato);
    if(c->size == 0){
        c->n_frente = nuevo_nodo;
        c->n_final = nuevo_nodo;
        c->size = 1;
		}
    else{
        c->n_final->siguiente = nuevo_nodo;
        c->n_final = nuevo_nodo;
        c->size = c->size + 1;
		}
	}


void descolar(cola *c){
    if(c->size == 1){
        free(c->n_frente);
        c->n_frente = NULL;
        c->n_final = NULL;
        c->size = 0;
		}
    else 
		if(c->size > 1){
			nodoCola *aux_nodo = c->n_frente;
			c->n_frente = c->n_frente->siguiente;
			free(aux_nodo);
			c->size = c->size-1;
			}
	}


nodoCola* frente(cola *c){
    return c->n_frente;
    }


void liberar_cola(cola *c){
	while(!es_cola_vacia(c)){
		descolar(c);
        }
	free(c);
}

void imprime_cola(cola *c) {
	cola *aux = crea_cola_vacia();
    if (c->n_frente == NULL) {
        printf("La cola está vacía.\n");
        return;
    }
    nodoCola *temp = c->n_frente;

    while (temp != NULL) {
        printf("%d ", temp->dato);
        encolar(aux, temp->dato);
		descolar(c);
		temp = c->n_frente;
    }
    printf("\n");
	temp = aux->n_frente;
	while(temp != NULL){
		encolar(c, temp->dato);
		descolar(aux);
		temp = aux->n_frente;
	}
	free(aux);
}
