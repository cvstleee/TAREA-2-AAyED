#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"
#include "time.h"


//Dominio: lista x listaPila (con cargas a procesar)
//Recorrido: int (valores 0 o 1)
//Descripción: revisa si es que hay procesos sin utilizar, entrega un 0 en caso de que todos estén ocupados y un 1 cuando al menos 1 esé libre

int sePuedeAsignar(lista *procesosActuales, listaPila *pilasCargas){
    nodo *auxProcesos = procesosActuales ->inicio;

    while(auxProcesos != NULL){
        //si un proceso está vacío
        if(auxProcesos->carga == 0){
            nodoListaPila *auxListaCargas = pilasCargas->inicio;
            while(auxListaCargas != NULL){
                if(tope(auxListaCargas->pilaDatos)->proceso == auxProcesos->proceso){
                    return 1;
                }
                auxListaCargas = auxListaCargas->siguiente;
            }
        }
        auxProcesos = auxProcesos->siguiente;
    }
    return 0;
}


//Dominio: lista x listaPila (con cargas a procesar) x listaCola (procesos con cargas ya procesadas)
//Recorrido: no tiene
//Descripción: Asigna cargas a procesos vacíos en caso de que estás tengan ese proceso en el tope de sus pilas.

void asignarCargas(lista *procesosActuales, listaPila *pilasCargas, listaCola *procesosRealizados){
    nodo *auxProcesos = procesosActuales->inicio;

    while(auxProcesos != NULL){
        nodoListaPila *auxListaCargas = pilasCargas->inicio;
        while(auxListaCargas != NULL){
            if(tope(auxListaCargas->pilaDatos)->proceso == auxProcesos->proceso && auxProcesos -> carga == 0){
                nodoListaCola *auxRealizados = procesosRealizados->inicio;
                auxProcesos->carga = auxListaCargas->posicion;
                while(auxRealizados != NULL){
                    if(auxRealizados->numeroProceso == auxProcesos->proceso){
                        encolar(auxRealizados->colaProceso, auxListaCargas->posicion);
                    }
                    auxRealizados = auxRealizados->siguiente;
                }
            }
            auxListaCargas = auxListaCargas->siguiente;
        }
        auxProcesos = auxProcesos->siguiente;
    }
}


//Dominio: lista x listaPila (con cargas a procesar)
//Recorrido: no tiene
//Descripción: encargada de controlar el procesamiento, resta en 1 el tiempo de las cargas que van siendo procesadas, desapila una carga si el proces asignado 
//llega a un tiempo igual a 0, y elimina el nodo en la listaPila cuando la pila quede vacía

void avanzarProcesamiento(lista *procesosActuales, listaPila *pilasCargas){
    nodo *auxProcesos = procesosActuales->inicio;
    while(auxProcesos != NULL){
        nodoListaPila *auxCargas = pilasCargas->inicio;
        while(auxCargas != NULL){
            if(auxProcesos -> carga == auxCargas->posicion && tope(auxCargas->pilaDatos)->tiempo != 0){
                int tiempoCargaActual = tope(auxCargas->pilaDatos)->tiempo;
                tiempoCargaActual = tiempoCargaActual - 1;
                tope(auxCargas->pilaDatos)->tiempo = tiempoCargaActual;
            }
            if(tope(auxCargas->pilaDatos)->tiempo == 0){
                desapilar(auxCargas->pilaDatos);
                auxProcesos -> carga = 0;
                if (es_pila_vacia(auxCargas->pilaDatos)) {
                    eliminarNodoListaPila(pilasCargas, auxCargas->posicion);
                }
            }
            auxCargas = auxCargas->siguiente;
        }
        auxProcesos = auxProcesos->siguiente;
    }
}


//Dominio: listaCola x listaPila (con cargas a procesar) x int
//Recorrido: int (entrega el tiempo final)
//Descripción: Inicializa el procesamiento de las cargas obtenidas, actúa según la función sePuedeAsignar y es la encargada de ir aumentando el tiempo en 1
//cada vez que se avanza en el procesamiento

int procesamientoCargas(listaCola *colasProcesos, listaPila *pilasCargas, int cantidadProcesos){
    //procesos actuales inicia vacío
    lista *procesosActuales = nueva_lista();
    int i;
    for(i = cantidadProcesos; i >= 1; i--){
        inserta_inicio(procesosActuales, 0, i);
    }


    int tiempo = 0;

    while(!es_listaPila_vacia(pilasCargas)){
        if(sePuedeAsignar(procesosActuales, pilasCargas)){
            asignarCargas(procesosActuales, pilasCargas, colasProcesos);
            avanzarProcesamiento(procesosActuales, pilasCargas);
            tiempo++;
        }else{
            avanzarProcesamiento(procesosActuales, pilasCargas);
            tiempo++;
        }
    }
    libera_lista(procesosActuales);
    return tiempo;
}



int main(int argc, char *argv[]){
    int cantidadCargas, cantidadProcesos;
    int procesoCarga, tiempoProcesoCarga; 
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

        //crea pilas según cantidad de procesos
        pila *pilaAux = nueva_pila();
        pila *pilaAuxInv = nueva_pila();

        // Leer y procesar los pares de enteros en la línea
        for (z = 0; z < cantidadProcesos; z++) {
            fscanf(archivo,"%d %d", &num1, &num2);
            apilar(pilaAux, num1, num2);
            linea += offset; // Avanzar en la línea
        }
        pilaAuxInv = invertirPila(pilaAux);
        insertarPila(pilasCargas, carga, pilaAuxInv);
        carga++;
    }

    //printf("LISTA CON PILAS RESULTANTE:\n");
    //imprime_listaPila(pilasCargas);

    //inicializar lista colas
    for(i = 0; i < cantidadProcesos; i++){
        cola *colaAux = crea_cola_vacia();
        insertarCola(colasProcesos, i+1, colaAux);
    }

    int tiempo;
    //calculo de tiempo
    float tiempo_algoritmo = 0;
	clock_t clock_ini, clock_fin;

    clock_ini = clock();

    tiempo = procesamientoCargas(colasProcesos, pilasCargas, cantidadProcesos);
    //para ver como quedaron las colas de los procesos
    //imprime_listaCola(colasProcesos);
    printf("TIEMPO FINAL %i\n", tiempo);
	
	clock_fin = clock();
	tiempo_algoritmo = (float)((clock_fin - clock_ini) / CLOCKS_PER_SEC);
	
	printf("\nTiempo del algoritmo en segundos: %.2f  \n", tiempo_algoritmo); 


    // Cerrar el archivo
    fclose(archivo);
    libera_listaCola(colasProcesos);
    libera_listaPila(pilasCargas);

    return 0;
}