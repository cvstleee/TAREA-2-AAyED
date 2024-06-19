#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
#include "TDAlista.h"
//#include "TDApila.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"

//probar que funciones sirvan x separado

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

//Función que procesa LOS DISTINTOS al mismo tiempo, y compara su tiempo para agregarlo
//a un acumulador
//tiempo acumulado en la primera llamada es 0

//aqui hay que cambiar arreglo a listaPila y listaCola

//esta función hay que llamarla según cuantas cargas hayan (en el main) hasta que queden vacías

//y si hago una función que actue primero con las !=  y en el 2do ciclo vea si hay una repetida
//la lógica está bien sí
int procesarCargasDistintas(listaPila *pilasCargas, listaCola *colasProcesos, int cantidadProcesos, int tiempoAcumulado) {
    int i, j;
    pila *pilaAux = nueva_pila();
    nodoListaPila *auxCargas = pilasCargas->inicio;
    nodoListaCola *auxProcesos;
    int cargaActual = 0;
    int procesoActual = 0;
    int tiempoParcial = 0;

    while (auxCargas != NULL) {
        pilaAux = auxCargas->pilaDatos;
        procesoActual = tope(pilaAux)->proceso;
        cargaActual++;

        auxProcesos = colasProcesos->inicio;
        for (i = 1; i <= cantidadProcesos; i++) {
            if (i == procesoActual) {
                encolar(auxProcesos->colaProceso, cargaActual);
                desapilar(auxCargas->pilaDatos);
            }
            auxProcesos = auxProcesos->siguiente;
        }

        if (auxCargas->pilaDatos != NULL && tiempoParcial < tope(auxCargas->pilaDatos)->tiempo) {
            tiempoParcial = tope(auxCargas->pilaDatos)->tiempo;
        }

        auxCargas = auxCargas->siguiente;
    }

    tiempoAcumulado += tiempoParcial;
    return tiempoAcumulado;
}

int procesarCargaEnEspera(listaPila *pilasCargas, listaCola *colasProcesos, int cantidadCargas, int cantidadProcesos, int tiempoAcumulado, int cargaEspera) {
    int i, j;
    pila *pilaAux;
    nodoListaPila *auxCargas = pilasCargas->inicio;
    nodoListaCola *auxProcesos;
    int procesoRealizado = 0;
    int tiempoParcial = 0;

    for (i = 1; i <= cantidadCargas; i++) {
        if (i == cargaEspera) {
            pilaAux = auxCargas->pilaDatos;
            procesoRealizado = tope(pilaAux)->proceso;

            auxProcesos = colasProcesos->inicio;
            for (j = 1; j <= cantidadProcesos; j++) {
                if (j == procesoRealizado) {
                    encolar(auxProcesos->colaProceso, cargaEspera);
                    tiempoParcial = tope(pilaAux)->tiempo;
                    desapilar(auxCargas->pilaDatos);
                }
                auxProcesos = auxProcesos->siguiente;
            }
        }
        auxCargas = auxCargas->siguiente;
    }

    auxCargas = pilasCargas->inicio;
    for (i = 1; i <= cantidadCargas; i++) {
        auxProcesos = colasProcesos->inicio;
        pila *topeAux = auxCargas->pilaDatos;

        if ((i != cargaEspera) && (tope(topeAux)->proceso != procesoRealizado)) {
            int procesoActual = tope(topeAux)->proceso;
            int cargaActual = i + 1;

            for (j = 1; j <= cantidadProcesos; j++) {
                if (j == procesoActual) {
                    encolar(auxProcesos->colaProceso, cargaActual);
                    desapilar(auxCargas->pilaDatos);

                    if (tope(topeAux) != NULL && tiempoParcial < tope(topeAux)->tiempo) {
                        tiempoParcial = tope(topeAux)->tiempo;
                    }
                }
                auxProcesos = auxProcesos->siguiente;
            }
        }
        auxCargas = auxCargas->siguiente;
    }

    tiempoAcumulado += tiempoParcial;
    return tiempoAcumulado;
}

 int procesarCargas(listaPila *pilasCargas, listaCola *colasProcesos, int cantidadCargas, int cantidadProcesos, int tiempoAcumulado, int cargaEspera) {
    if (cargaEspera == 0) {
        return procesarCargasDistintas(pilasCargas, colasProcesos, cantidadProcesos, tiempoAcumulado);
    } else {
        return procesarCargaEnEspera(pilasCargas, colasProcesos, cantidadCargas, cantidadProcesos, tiempoAcumulado, cargaEspera);
    }
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

    
    //---PROCESAMIENTO DE CARGAS DESPUÉS DE SACAR INFO DEL ARCHIVO
    //PASO 1: extraer topes
    lista *listaTopes = nueva_lista();
    llenarTopes(pilasCargas, listaTopes, cantidadCargas);
    printf("LISTA TOPES INICIALES\n");
    imprime_lista(listaTopes);

    int pruebaCarga;

    pruebaCarga = verificarProcesoRepetido(listaTopes, cantidadCargas);

    printf("la carga que se repite es %i\n", pruebaCarga);

    //parte para revisar si procesa bien los procesos !=

    //prueba sin cargas en espera
    //debe darme 12 KLDHSFJ
    int tiempo = 0;
    tiempo = procesarCargas(pilasCargas, colasProcesos, cantidadCargas, cantidadProcesos, 0, 0);

    printf("TIEMPO AAA: %i\n", tiempo);


    //Ahora como voy modificando los topes, eso debería terminar cuando todas las cargas estén vacías...

   // procesamientoCargas(pilasCargasAux, colasProcesos, cantidadCargas);

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    //printf("\nCantidad cargas: %d\n", cantidadCargas);
    //printf("Cantidad procesos: %d\n", cantidadProcesos);
    


    return 0;
}
