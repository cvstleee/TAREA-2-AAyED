#include <stdio.h>
#include <stdlib.h>
#include "TDApila.h"


pila* nueva_pila(void){
    pila *p = (pila*)malloc(sizeof(pila));
	p->size = 0;
	p->tope = NULL;
	return p;
    }


int es_pila_vacia(pila *p){
	if(p->size == 0){
		return 1;
	    }
	else{
		return 0;
	    }
    }
    
    
void apilar(pila *p, int pro, int tie){
	nodo* aux=(nodo*)malloc(sizeof(nodo));
	aux -> proceso = pro;
	aux -> tiempo = tie;
	aux -> siguiente = p -> tope;
	p -> tope = aux;
	p -> size = p -> size + 1;
}

nodo *tope(pila *p){
	return p -> tope;
}

void desapilar(pila *p){
	nodo* aux=(nodo*)malloc(sizeof(nodo));
	aux = p -> tope;
	p -> tope = p -> tope -> siguiente;
	p -> size = p -> size - 1;
	free(aux);
}


void imprime_pila(pila *p){
	pila *aux_pila;
	aux_pila = nueva_pila();
	nodo* aux;
	aux = p -> tope;
	
	if(es_pila_vacia(p)){
		printf("la pila esta vacia\n");
	}else{
		while(!es_pila_vacia(p)){
		printf("proceso: %i tiempo: %i", aux -> proceso, aux -> tiempo);
		apilar(aux_pila, aux -> proceso, aux -> tiempo);
		desapilar(p);
		aux = p -> tope;
	 	}
	 
		aux = aux_pila -> tope; 
		while(!es_pila_vacia(aux_pila)){
			apilar(p, aux -> proceso, aux -> tiempo);
			desapilar(aux_pila);
			aux = aux_pila -> tope;
		}

	}
}
void invertirPila(pila *p){
	pila* pilaAuxiliar = nueva_pila();
    while (!es_pila_vacia(p)) {
        apilar(pilaAuxiliar, tope(p)->proceso, tope(p)->tiempo);
		desapilar(p);
    }
    while (!es_pila_vacia(pilaAuxiliar)) {
        apilar(p, tope(pilaAuxiliar)->proceso, tope(pilaAuxiliar)->tiempo);
		desapilar(pilaAuxiliar);
    }
    liberarPila(pilaAuxiliar);
}

/*int busca_dato_pila(pila *p, int d){
	int dato_encontrado = 0;
	nodo *aux;
	pila *aux_pila;
	aux_pila = nueva_pila();
	
	
	while(!es_pila_vacia(p)){
		aux = p -> tope;
		if(aux -> dato == d){
			apilar(aux_pila, aux -> dato);
			dato_encontrado = 1;
			desapilar(p);
			aux = p -> tope;
			//return dato_encontrado;
		}else{
			apilar(aux_pila, aux -> dato);
			desapilar(p);
			aux = p -> tope;
		}
	} 
	aux = aux_pila -> tope; 
	while(!es_pila_vacia(aux_pila)){
		apilar(p, aux -> dato);
		desapilar(aux_pila);
		aux = aux_pila -> tope;
	}
	return dato_encontrado;
}

int esPalindroma(pila *A){
	pila *B = nueva_pila();
	pila *C = nueva_pila();

	while (!es_pila_vacia(A)){
		apilar(B, tope(A)->dato);
		apilar(C, tope(A)->dato);
		desapilar(A);
	}
	while (!es_pila_vacia(B)){
		apilar(A, tope(B)->dato);
		desapilar(B);
	}
	free(B);
	while (!es_pila_vacia(A)){
		if(tope(A)->dato != tope(C)->dato){
			return 0;
		}else{
			desapilar(A);
			desapilar(C);
		}
	}
	//ME FALTA DEJAR LA A CON TODOS SUS DATOS, AL SER ENTREGA CON * SE PIERDEN AL DESAPILAR
	free(C);
	return 1;
}*/