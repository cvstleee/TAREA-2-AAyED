#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
#include "TDAlista.h"
//#include "TDApila.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"


void procesarCargaEspecifica(nodoListaPila *auxListaCargas, listaCola *colasProcesos, int *tiempoParcial, lista *procesosRealizados, listaPila *pilasCargas) {
    pila *pilaActual = auxListaCargas->pilaDatos;
    int procesoActual = tope(pilaActual)->proceso;
    int cargaActual = auxListaCargas->posicion;

    //si el tiempo de la carga procesada es mayor al tiempo parcial, se actualiza en la misma variable
    //porque en cada "ciclo" se debe guardar en el final el mayor de todas las cargas procesadas
    if (*tiempoParcial < tope(pilaActual)->tiempo) {
        *tiempoParcial = tope(pilaActual)->tiempo;
    }

    nodoListaCola *auxListaProcesos = colasProcesos->inicio;
    while (auxListaProcesos != NULL) {
        if (auxListaProcesos->numeroProceso == procesoActual) {
            encolar(auxListaProcesos->colaProceso, cargaActual);
            desapilar(auxListaCargas->pilaDatos);
            inserta_inicio(procesosRealizados, cargaActual, procesoActual);

            if (es_pila_vacia(auxListaCargas->pilaDatos)) {
                eliminarNodoListaPila(pilasCargas, auxListaCargas->posicion);
                auxListaCargas = NULL; // Marcar como NULL para indicar eliminación
            }
        }
        auxListaProcesos = auxListaProcesos->siguiente;
    }
}


void procesarCargasEnEspera(listaPila *pilasCargas, listaCola *colasProcesos, lista *cargaEspera, int *tiempoParcial, lista *procesosRealizados) {
    nodo *auxEspera = cargaEspera->inicio;
    while (auxEspera != NULL) {
        nodoListaPila *auxListaCargas = pilasCargas->inicio;
        while (auxListaCargas != NULL) {
            if (auxListaCargas->posicion == auxEspera->carga) {
                procesarCargaEspecifica(auxListaCargas, colasProcesos, tiempoParcial, procesosRealizados, pilasCargas);
                //auxListaCargas = auxListaCargas->siguiente;
            }
            auxListaCargas = auxListaCargas->siguiente;
        }
        elimina_inicio(cargaEspera);
        auxEspera = cargaEspera->inicio;
    }
}

int procesarCargas(listaPila *pilasCargas, listaCola *colasProcesos) {
    int i = 1;
    int tiempoParcial = 0;
    int tiempoFinal = 0;
    lista *cargaEspera = nueva_lista();
    
    while (!es_listaPila_vacia(pilasCargas)) {
       // printf("TIEMPO PARCIAL INICIAL %i\n", tiempoParcial);
        lista *procesosRealizados = nueva_lista();

        if (!es_lista_vacia(cargaEspera)) {
         //   printf("SEGUNDO CICLO\n");
            procesarCargasEnEspera(pilasCargas, colasProcesos, cargaEspera, &tiempoParcial, procesosRealizados);
        }

        nodoListaPila *auxListaCargas = pilasCargas->inicio;
        while (auxListaCargas != NULL) {
            nodo *auxRealizados = procesosRealizados->inicio;
            int repetido = 0;
            
            // Verificar si el proceso actual ya se ha realizado
            while (auxRealizados != NULL) {
                if (auxListaCargas->posicion == auxRealizados->carga || tope(auxListaCargas->pilaDatos)->proceso == auxRealizados->proceso) {
                    repetido = 1;
                }
                auxRealizados = auxRealizados->siguiente;
            }

            if (!repetido) {
                procesarCargaEspecifica(auxListaCargas, colasProcesos, &tiempoParcial, procesosRealizados, pilasCargas);
            } else if (es_lista_vacia(cargaEspera)) {
                inserta_inicio(cargaEspera, auxListaCargas->posicion, tope(auxListaCargas->pilaDatos)->proceso);
            }

            if (auxListaCargas != NULL) {
                auxListaCargas = auxListaCargas->siguiente;
            } else {
                auxListaCargas = pilasCargas->inicio;
            }

        }
        printf("TOPE %i\n ", i);
        i++;
        printf("ASI VAN QUEDANDO PILAS\n");
        imprime_listaPila(pilasCargas);
        printf("\n");
        printf("TIEMPO PARCIAL ANTES DE GUARDARSE EN EL FINAL %i\n", tiempoParcial);
        tiempoFinal += tiempoParcial;
        printf("TIEMPO FINAL NUEVO %i\n", tiempoFinal);
        tiempoParcial = 0;
    }
    
    return tiempoFinal;
}