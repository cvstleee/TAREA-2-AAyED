#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"


//---FUNCIONES PARA PROCESAR CARGAS---

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
    //tengo orden, pero no mismo tiempo
    //POSIBLE ERROR ENCONTRADO: en el último tope, pasa que se puede procesar la carga 1 y después la carga 3 (3+1)
    //al mismo tiempo que la carga 2 en el proceso 4 por el tiempo (4)
    //y esto no lo implementé en ningún lado
    //si el tiempo de procesamiento de la carga != es > a la suma del procesamiento de las cargas ==, se pueden procesar 2 cargas en un mismo proceso
    return tiempoFinal;
}




int main(int argc, char *argv[]){
    int cantidadCargas, cantidadProcesos;
    int procesoCarga, tiempoProcesoCarga; //para la pila
    listaCola *colasProcesos = nueva_listaCola();
    listaPila *pilasCargas = nueva_listaPila();
    pila *pilaAux = nueva_pila();
    int i;

    FILE *archivo;
    // Abrir el archivo
    archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    //leer cantidad de cargas y procesos
    fscanf(archivo, "%d %d", &cantidadCargas, &cantidadProcesos);

    //leer procesos y tiempos según cargas y las guarda en pilas
    int num1, num2;
    int result1, result2;
    int count = 0;
    int j = 0;

    char buffer[100]; // Buffer para leer líneas completas
    nodoListaPila *aux = pilasCargas ->inicio;
    int z;
    int carga = 1;

    //hay que invertir las pilas
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        char *linea = buffer;
        int offset = 0;
        int result;
        //imprime_listaPila(pilasCargas);

        //crea pilas según cantidad de procesos, se crea fuera, ya que se necesitan nuevas dsp de completar el for
        pila *pilaAux = nueva_pila();
        pila *pilaAuxInv = nueva_pila();

        // Leer y procesar los pares de enteros en la línea
        for (z = 0; z < cantidadProcesos; z++) {
            //printf("z: %i\n", z); //z está avanzando bien
            fscanf(archivo,"%d %d", &num1, &num2);
            //printf("Proceso: %d, Tiempo: %d\n", num1, num2);
            apilar(pilaAux, num1, num2);
            //printf("apilado %i %i\n", num1, num2);
            //printf("ASI VA LA PILA\n");
            //imprime_pila(pilaAux);
            linea += offset; // Avanzar en la línea
        }
        pilaAuxInv = invertirPila(pilaAux);
        insertarPila(pilasCargas, carga, pilaAuxInv);
        carga++;
    }

    printf("LISTA CON PILAS RESULTANTE:\n");
    imprime_listaPila(pilasCargas);

    //inicializar lista colas
    for(i = 0; i < cantidadProcesos; i++){
        cola *colaAux = crea_cola_vacia();
        insertarCola(colasProcesos, i+1, colaAux);
    }

    int tiempo = 0;
    tiempo = procesarCargas(pilasCargas, colasProcesos);
    imprime_listaCola(colasProcesos);
    printf("TIEMPO AAAAAAA %i\n", tiempo);

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    //printf("\nCantidad cargas: %d\n", cantidadCargas);
    //printf("Cantidad procesos: %d\n", cantidadProcesos);
    


    return 0;
}
