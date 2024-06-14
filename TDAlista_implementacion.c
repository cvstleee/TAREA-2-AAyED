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


/*void inserta_despues(lista *l, int valor, int datoAnterior){
  nodo *anterior = l -> inicio;
  while(anterior -> dato != datoAnterior){
    anterior = anterior -> siguiente;
  }
  nodo *nuevo_nodo = (nodo*)malloc(sizeof(nodo));
  nuevo_nodo ->dato = valor;
  nuevo_nodo -> siguiente = anterior -> siguiente;
  anterior ->siguiente = nuevo_nodo;
}*/



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

/*void eliminarDato(lista* l, int dato){
  nodo* indicado = l -> inicio;
  nodo* anteriorIndicado = NULL;
  if (!es_lista_vacia(l)){
    while (indicado -> dato != dato){
      anteriorIndicado = indicado;
      indicado = indicado -> siguiente;
    }  
  }  anteriorIndicado -> siguiente = indicado -> siguiente;
}*/

void imprime_lista(lista *l){
    printf("Lista topes a comparar: ");
    if (!es_lista_vacia(l)){
        nodo *aux = l->inicio;
        while (aux != NULL){
            printf("proceso: %i carga: %i", aux->proceso, aux->carga);
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

/*int busca_dato(lista *l, int d){
	nodo *auxiliar = l->inicio;
	while (auxiliar != NULL){
    	if(auxiliar->dato == d){
    		return 1;
		}
		auxiliar = auxiliar->siguiente;
    }return 0;
}

lista* lista_inversa(lista* l){
  nodo* aux = l -> inicio;
  lista* aux_invertido = nueva_lista();

  while (aux->siguiente != NULL){
    inserta_inicio(aux_invertido, aux->dato);
    aux = aux->siguiente;
  }
  inserta_inicio(aux_invertido, aux->dato);
  return aux_invertido;
}*/

/*void numMenor_numMayor(lista *l, int x, lista *lista_menor, lista *lista_mayor){
	int j = 0;
	int dato_x = 0;
	nodo *auxiliar = l -> inicio;
	
	while (auxiliar != NULL){
			if(j == x){
				dato_x = auxiliar -> dato;
			}
			auxiliar = auxiliar -> siguiente;
			j++;
	}
	
	auxiliar = l -> inicio;
	while (auxiliar != NULL){
		if(auxiliar -> dato <= dato_x){
			inserta_inicio(lista_menor,auxiliar->dato);
		}else{
			inserta_inicio(lista_mayor,auxiliar->dato);
		}
		auxiliar = auxiliar -> siguiente;
	}
	
}*/


nodo* obtenerNodo(lista *l, int posicion){
  nodo* aux = l -> inicio;
  int count = 0;

  while (count != posicion){ 
    aux = aux -> siguiente;
    count++;
  }
  return aux;
}



/*lista *eliminarParentesis(lista *A){
  lista *lista_aux = nueva_lista();
  nodo *aux = A ->inicio;

  while(aux != NULL){
    if ((aux -> dato == '(') || (aux->dato == ')')){
      aux = aux ->siguiente;
      elimina_inicio(A);
    }else{
      inserta_inicio(lista_aux, aux -> dato);
      aux = aux ->siguiente;
      elimina_inicio(A);
    }
  }return lista_aux;
}


lista *eliminarRepetidos(lista *A){
  nodo *aux = A->inicio;
  lista *B = nueva_lista();
  inserta_inicio(B, aux -> dato);
  nodo *aux2 = B->inicio;
  aux = aux -> siguiente;
  int existe;
  while(aux != NULL){
    existe = 0;
    aux2 = B ->inicio;
    while (aux2 != NULL){
      if (aux -> dato == aux2 -> dato){
        //printf("caso iguales\n");
        aux2 = aux2 -> siguiente;
        existe = 1;
      }else{
        aux2 = aux2 -> siguiente;
        //existe = 0;
      }
    }
    if(existe == 0){
      inserta_final(B, aux ->dato);
    }
    aux = aux ->siguiente;
  }
  return B;
}


lista *mezclarListasOrdenadas(lista *A, lista *B){
  lista *C = nueva_lista();
  nodo *aux1 = A->inicio;
  nodo *aux2 = B->inicio;

  if(aux1->dato <= aux2->dato){
    inserta_inicio(C, aux1->dato);
    aux1 = aux1 -> siguiente;
  

  }if(aux1->dato > aux2->dato){
    inserta_inicio(C, aux2->dato);
    aux2 = aux2 -> siguiente;
  }

  while((aux1 != NULL) && (aux2 != NULL)){
    if(aux1->dato < aux2->dato){
      inserta_final(C, aux1->dato);
      aux1 = aux1->siguiente;
    }if(aux2->dato < aux1->dato){
      inserta_final(C, aux2->dato);
      aux2 = aux2->siguiente;
    }else{
      inserta_final(C, aux1->dato);
      inserta_final(C, aux2->dato);
      aux1 = aux1->siguiente;
      aux2 = aux2->siguiente;
    }
  }

  while(aux1 != NULL){
      inserta_final(C, aux1->dato);
      aux1 = aux1->siguiente;
  }

  while(aux2 != NULL){
      inserta_final(C, aux2->dato);
      aux2 = aux2->siguiente;
  }

  return C;
}*/