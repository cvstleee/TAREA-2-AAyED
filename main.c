//DEJO AQUI SOLO LO QUE FUNCIONE

#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"

// Función para llenar la lista con los topes de las pilas
//TDA usado: lista simple
void llenarTopes(listaPila *pilasCargas, lista *topes, int cantidadCargas) {
    nodoListaPila *aux = pilasCargas->inicio;
    pila *pilaAux;;
    // Vaciar la lista de topes actual
    while (topes->inicio != NULL) {
        elimina_inicio(topes);
    }
    // Llenar la lista con los nuevos topes de las pilas
    for (int i = 0; i < cantidadCargas; i++) {
        //tope me guarda n° de carga y su respectivo proceso
        pilaAux = aux->pilaDatos;
        inserta_inicio(topes, i + 1, tope(pilaAux)->proceso);
        aux = aux -> siguiente;
    }
    //printf("LISTA TOPES INICIALES (dentro funcion)\n");
    //imprime_lista(topes);
}

//Función que verifica si hay procesos repetidos, con que uno se repita, queda uno en espera y ese entrega, en caso de no
//existir, devuelve un 0
//se usa TDA lista simple
int verificarProcesoRepetido(lista *topes, int cantidadCargas){
    nodo *aux = topes->inicio;
    nodo *sig = aux -> siguiente;
    int cargaIgual= 0;
    //se recorre la lista de topes
    while (aux != NULL) {
        sig = aux->siguiente;
        while (sig != NULL) {
            if (aux ->proceso == sig->proceso) {
                //FUNCIONA BIEN ESTO, aux tiene a la carga 2 y sig a la carga 1
               printf("carga %i tiene el mismo proceso que la carga %i\n", aux->carga, sig->carga);
               cargaIgual = aux->carga; //me guarda el carga 2 
            }
            //que avance para terminar el ciclo
            sig = sig->siguiente;
        }
        //que avance para terminar el ciclo de los topes
        aux = aux->siguiente;
    }
    return cargaIgual;
}
