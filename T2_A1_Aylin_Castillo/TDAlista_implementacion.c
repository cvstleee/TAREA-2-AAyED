#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"

/*------------- operaciones -------------*/



lista* nueva_lista(){
    lista *l = (lista*)malloc(sizeof(lista));
    l->inicio = NULL;
    return l;
    }


int es_lista_vacia(lista *l){
    if (l->inicio == NULL)
        return 1;
    else
      return 0;
    }


void inserta_inicio(lista *l, int ca, int pro){
    nodo *nuevo_nodo = (nodo*)malloc(sizeof(nodo));
    nuevo_nodo->carga = ca;
    nuevo_nodo->proceso = pro;
    nuevo_nodo->siguiente = l->inicio;
    l->inicio = nuevo_nodo;
  }


void inserta_final(lista *l, int ca, int pro){
  nodo *final = l -> inicio;
  while(final -> siguiente != NULL){
    final = final -> siguiente;
  }
  nodo *nuevo_nodo = (nodo*)malloc(sizeof(nodo));
  nuevo_nodo->carga = ca;
  nuevo_nodo->proceso = pro;
  nuevo_nodo -> siguiente = NULL;
  final -> siguiente = nuevo_nodo;
}


void elimina_inicio(lista *l){
    nodo *aux;
    if(!es_lista_vacia(l)){
        aux = l->inicio;
        l->inicio = l->inicio->siguiente;
        free(aux);
        }
    }

void elimina_final(lista* l){
  nodo* final = l -> inicio;
  nodo* anteriorFinal = NULL;
  if (!es_lista_vacia(l)){
    while (final -> siguiente != NULL){
      anteriorFinal = final;
      final = final -> siguiente;
    }    
  }
  anteriorFinal -> siguiente = NULL;
  free(final);
}

void imprime_lista(lista *l){
    //printf("Lista procesos realizados: \n");
    if (!es_lista_vacia(l)){
        nodo *aux = l->inicio;
        while (aux != NULL){
            printf("proceso: %i carga: %i\n", aux->proceso, aux->carga);
            aux = aux->siguiente;
            }
        printf("\n");
        }
    else
        printf("%c\n", 157);
    }


void libera_lista(lista *l){
    while (!es_lista_vacia(l)){
        elimina_inicio(l);
        }
    free(l);
	}
	
	
int cuenta_nodos(lista *l){
  if(!es_lista_vacia(l)){
    int count = 0;
    nodo *auxiliar = l->inicio;
    while (auxiliar != NULL){
    	count++;
      	auxiliar = auxiliar->siguiente;
    }
    return count;

  }else{
    return 0;
  }
}



nodo* obtenerNodo(lista *l, int posicion){
  nodo* aux = l -> inicio;
  int count = 0;

  while (count != posicion){ 
    aux = aux -> siguiente;
    count++;
  }
  return aux;
}