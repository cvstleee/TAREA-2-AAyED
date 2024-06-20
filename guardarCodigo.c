#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
#include "TDAlista.h"
//#include "TDApila.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"

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
               //pero y si hay más de dos cargas con el proceso igual?, da lo mismo, pq igual quedarán en espera
               //ya que solo se procesarán a la vez las distintas, pero si o si hay que tener una que quede en espera para realizarse
               //dsp, ya que puede ocurrir que al avanzar con una, al desapilar, vuelva a topar con una nueva
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


int procesarCargas(listaPila * pilasCargas, listaCola * colasProcesos, int cantidadCargas, int cantidadProcesos, 
int tiempoAcumulado, int cargaEspera){
    int i, j;
    pila *pilaAux = nueva_pila();
    //cola *colaAux = crea_cola_vacia();
    nodoListaPila *auxCargas = pilasCargas ->inicio;
    nodoListaCola *auxProcesos = colasProcesos ->inicio;
    int cargaActual = 0;
    int procesoActual = 0;
    int procesoRealizado = 0;
    int tiempoParcial = 0; //aqui se comparan los tiempos de las cargas que se procesan a la vez en procesos !=
    //caso todos los procesos !=, procesarlos todos 
    //i == posicion en listaPila

    //si veo la cargaEspera antes, siempre va a ser != 0 y necesito procesar antes
    if(cargaEspera == 0){
        //pq hay que encolarlos todos
        while(auxCargas != NULL){
                pilaAux = auxCargas -> pilaDatos;
                procesoActual = tope(pilaAux) -> proceso;
                cargaActual = cargaActual + 1;
                //el proceso se entrega partiendo de 1
                //se reinicia cada que entra al ciclo de buscar proceso
                auxProcesos = colasProcesos->inicio;
                for(i = 1; i <= cantidadProcesos; i++){
                    if(i == procesoActual){
                        encolar(auxProcesos -> colaProceso, cargaActual);
                        //tiempoParcial = tope(pilaAux)->tiempo;
                        desapilar(auxCargas -> pilaDatos);
                    }
                    //avanza en la lista de procesos
                    auxProcesos = auxProcesos -> siguiente;
                }
                    //tiempo parcial siempre será el mayor de los obtenidos en esa ronda
                    if(tiempoParcial < tope(pilaAux)->tiempo){
                            tiempoParcial = tope(pilaAux)->tiempo;
                    }
            auxCargas = auxCargas ->siguiente;
        } 
    }//si hay carga en espera, es pq hay iguales, aqui hay que controlar que solo se procesen las distintas
    if(cargaEspera != 0){
        //se procesa la carga que quedó en espera primero pq es prioridad
        //ciclo para llegar a la carga que se va a encolar
        //auxCargas = pilasCargas -> inicio;
        for(i = 1; i <= cantidadCargas; i++){
            if(i == cargaEspera){  
                pilaAux = auxCargas -> pilaDatos;
                //procesoActual = tope(pilaAux) -> proceso;
                procesoRealizado = tope(pilaAux) -> proceso;
                auxProcesos = colasProcesos ->inicio;
                //busca en la lista con las colas de procesos
                for(j = 1; j <= cantidadProcesos; j++){
                    if(j == procesoRealizado){
                        encolar(auxProcesos -> colaProceso, cargaEspera);
                        tiempoParcial = tope(pilaAux)->tiempo;
                        desapilar(auxCargas -> pilaDatos);
                    }
                    //avanza en la lista de procesos
                    auxProcesos = auxProcesos -> siguiente;
                }
            }
            auxCargas = auxCargas -> siguiente;
        }

        //procesar las cargas con proceso distinto al de la cargaEspera
        auxCargas = pilasCargas -> inicio;
        pila *topeAux;
        for(i = 1; i <= cantidadCargas; i++){
            //si no es la misma carga ya procesada y a la vez el proceso es != al ya procesado en la de espera
            auxProcesos = colasProcesos -> inicio;
            //va cambiando el topeAux cada que avanza rl for
            topeAux = auxCargas -> pilaDatos;
            if((i != cargaEspera) && (tope(topeAux) -> proceso != procesoRealizado)){
                procesoActual = tope(topeAux)->proceso;
                cargaActual = i + 1;
                for(j = 1; j <= cantidadProcesos; j++){
                    if(j == procesoActual){
                        encolar(auxProcesos -> colaProceso, cargaActual);
                        //tiempoParcial = tope(pilaAux)->tiempo;
                        desapilar(auxCargas -> pilaDatos);
                        //tiempo parcial siempre será el mayor de los obtenidos en esa ronda
                        if(tiempoParcial < tope(topeAux)->tiempo){
                                tiempoParcial = tope(topeAux)->tiempo;
                        }
                    }
                    auxProcesos = auxProcesos -> siguiente;
                }
            }
            auxCargas = auxCargas -> siguiente;
        }
    }
            
    tiempoAcumulado = tiempoAcumulado + tiempoParcial;

    return tiempoAcumulado;
}


//caso cargas con distintos procesos en el tope y si realmente no necesito la carga en espera como entrada, sino que haga 
//como un if anidado?

int procesarCargasDistintas(listaPila * pilasCargas, listaCola * colasProcesos, int cantidadCargas, int cantidadProcesos, 
int tiempoAcumulado, int cargaEspera){
    int i, j;
    pila *pilaAux = nueva_pila();
    //cola *colaAux = crea_cola_vacia();
    nodoListaPila *auxCargas = pilasCargas ->inicio;
    nodoListaCola *auxProcesos = colasProcesos ->inicio;
    int cargaActual = 0;
    int procesoActual = 0;
    int procesoRealizado = 0;
    int tiempoParcial = 0; //aqui se comparan los tiempos de las cargas que se procesan a la vez en procesos !=
    //caso todos los procesos !=, procesarlos todos 
    //i == posicion en listaPila

    //la encolación
    //paso 1. ver si se repite alguna
    //PASO 2: extraer topes
    lista *listaTopes = nueva_lista();
    llenarTopes(pilasCargas, listaTopes, cantidadCargas);
    printf("LISTA TOPES INICIALES\n");
    imprime_lista(listaTopes);

    int pruebaCarga;
    //tiene la que queda en espera para el 2do ciclo
    pruebaCarga = verificarProcesoRepetido(listaTopes, cantidadCargas);

    //caso 2, procesar toda carga con proceso != a la cargaEspera y n°carga != a cargaEspera
    //que pasa si se tiene uno más repetido? tipo si son 4 cargas y 3 tienen el mismo proceso?
    //habria que controlar que procesos se usaron en el primer while
    while(auxCargas != NULL){
                //pila de la lista apuntada
                pilaAux = auxCargas -> pilaDatos;
                procesoActual = tope(pilaAux) -> proceso;
                cargaActual = cargaActual + 1;
                //el proceso se entrega partiendo de 1
                //se reinicia cada que entra al ciclo de buscar proceso
                auxProcesos = colasProcesos->inicio;
                for(i = 1; i <= cantidadProcesos; i++){
                    if(i == procesoActual){
                        encolar(auxProcesos -> colaProceso, cargaActual);
                        //tiempoParcial = tope(pilaAux)->tiempo;
                        desapilar(auxCargas -> pilaDatos);
                    }
                    //avanza en la lista de procesos
                    auxProcesos = auxProcesos -> siguiente;
                }
                    //tiempo parcial siempre será el mayor de los obtenidos en esa ronda
                    if(tiempoParcial < tope(pilaAux)->tiempo){
                            tiempoParcial = tope(pilaAux)->tiempo;
                    }
            auxCargas = auxCargas ->siguiente;
        } 
}