#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
#include "TDAlista.h"
//#include "TDApila.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"


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