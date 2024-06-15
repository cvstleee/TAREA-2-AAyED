#include <stdio.h>
#include <stdlib.h>
#include "TDAcola.h"
#include "TDAlista.h"
#include "TDApila.h"

// Función para llenar la lista con los topes de las pilas
void llenarTopes(pila **pilasCargas, lista *topes, int cantidadCargas) {
    // Vaciar la lista de topes actual
    while (topes->inicio != NULL) {
        elimina_inicio(topes);
    }
    // Llenar la lista con los nuevos topes de las pilas
    for (int i = 0; i < cantidadCargas; i++) {
        inserta_inicio(topes, i + 1, tope(pilasCargas[i])->proceso);
    }
}

//devuelve el número de la carga que queda en espera
int verificarProcesoRepetido(lista *topes, int cantidadCargas){
    //comparar procesos, caso = queda una en espera, caso != se procesan al mismo tiempo
    nodo *aux = topes->inicio;
    nodo *sig = aux -> siguiente;
    //int iguales = 0;
    int cargaIgual= 0;
    while (aux != NULL) {
        sig = aux->siguiente;
        while (sig != NULL) {
            if (aux ->proceso == sig->proceso) {
                //FUNCIONA BIEN ESTO, aux tiene a la carga 2 y sig a la carga 1
               printf("carga %i tiene el mismo proceso que la carga %i\n", aux->carga, sig->carga);
               //pero y si hay más de dos cargas con el proceso igual?
               cargaIgual = aux->carga; //me guarda el carga 2 
            }
            sig = sig->siguiente;
        }
        aux = aux->siguiente;
    }
    return cargaIgual;
}


void procesamientoCargasCiclo(pila ** pilasCargas, cola ** colasProcesos, int cantidadCargas){
    //aqui va el ciclo que ve cuales se guardan y bla
}


//debe devolver el optimo (tiempo)
void procesamientoCargas(pila ** pilasCargas, cola ** colasProcesos, int cantidadCargas){
    int tiempoUsado = 0;
    lista *topes = nueva_lista();

    llenarTopes(pilasCargas, topes, cantidadCargas);

    //comparar procesos, caso = queda una en espera, caso != se procesan al mismo tiempo
    //se mantiene en 0 en caso de no haber ==
    int cargaEspera = 0;
    cargaEspera = verificarProcesoRepetido(topes, cantidadCargas); //funciona

    printf("carga guardada para procesar despues: %i\n", cargaEspera);
    //aqui se procesarian las cargas != a carga igual
    int cargaActual = 0;
    int procesoActual = 0;
    int tiempoInvertido = 0;
    /*aux=topes->inicio;
    while(aux != NULL){
        //primero sería 3 y después 1
        cargaActual = aux -> carga;
        if(cargaActual != cargaIgual){
            //extraer que proceso tiene esa carga en los topes y llamar al arreglo de colas
            procesoActual = aux -> proceso - 1;
            //encola en la cola del proceso 2, el tiempo que está en el tope de la carga 3
            printf("se está procesando la carga %i en el proceso %i\n", cargaActual, procesoActual);
            encolar(colasProcesos[procesoActual], cargaActual);
            printf("carga encolada %i en procesoCola %i\n", colasProcesos[procesoActual]->n_frente->dato, procesoActual);
            //aumentamos el tiempo optimo

            //es - 1 pq justamente las puse en la lista con + 1
            //printf("tope tiempo %i\n", tope(pilasCargas[cargaActual - 1])->tiempo);

            //y si no tengo que comparar el tiempoInvertido?, sino el tiempo de las cargas que se procesan?
            //pero y si el tiempo invertido es = al tiempo que se quiere agregar? error!!
            //hay que comparar los tiempos que se van a agregar, tendré que hacer otra lista???
            if (tiempoInvertido != tope(pilasCargas[cargaActual - 1])->tiempo){
                if(tiempoInvertido < tope(pilasCargas[cargaActual - 1])->tiempo){
                    //duda con este, me da el 3, pero dudo
                    //DE MOMENTO FUNCIONA BIEN
                    tiempoInvertido = tiempoInvertido + tope(pilasCargas[cargaActual - 1])->tiempo;
                    //printf("el tiempo que se lleva es %i\n",tiempoInvertido);
                    //desapila la carga que ya se procesó, x alguna razón se me cae aqui el código
                    desapilar(pilasCargas[cargaActual - 1]);
                }
            }
            //tiempoInvertido = tiempoInvertido + tope(pilasCargas[cargaActual - 1])->tiempo;
            printf("el tiempo que se lleva es %i\n",tiempoInvertido);
        }
        aux = aux->siguiente;
    }*/
    //debe dar 6, pero realmente es 3, tengo que arreglarlo
    printf("el tiempo que se lleva es %i\n",tiempoInvertido);

    //si carga igual es != a 0 significa que hay una carga en espera para cierto proceso

    llenarTopes(pilasCargas, topes, cantidadCargas);
    int i;
    /*if(cargaIgual != 0){
       //se hace el ciclo distinto, ya que se prioriza el procesamiento de esta carga para desapilarla dsp
       //1. revisar lista topes nuevos y procesar los que son != al que tiene la cargaIgual
       //comparar procesos, caso = queda una en espera, caso != se procesan al mismo tiempo

        nodo *aux = topes->inicio;
        //nodo *sig = aux -> siguiente;
        //int iguales = 0;
        //int cargaIgual= 0;
        while (aux != NULL) {
            //sig = aux->siguiente;
                //si el proceso de x carga es != al proceso de la carga que quedó en espera, procesarlas
                if (aux ->proceso != tope(pilasCargas[cargaIgual])->proceso) {
                    encolar(colasProcesos[tope(pilasCargas[cargaIgual])->proceso - 1], aux->carga);
                    desapilar(pilasCargas[aux -> carga - 1]);
                //pero y si hay más de dos cargas con el proceso igual?
                //cargaIgual = aux->carga; //me guarda el carga 2 
                }
    
            //pero y si el tiempo invertido es = al tiempo que se quiere agregar? error!!
            //LO QUE HAY QUE COMPARAR SON LOS TIEMPOS QUE SE VAN A AGREGAR, NO EL TIEMPO INVERTIDO CON LOS OTROS!!
            if (tiempoInvertido != tope(pilasCargas[cargaActual - 1])->tiempo){
                if(tiempoInvertido < tope(pilasCargas[cargaActual - 1])->tiempo){
                                //duda con este, me da el 3, pero dudo
                                //DE MOMENTO FUNCIONA BIEN
                    tiempoInvertido = tiempoInvertido + tope(pilasCargas[cargaActual - 1])->tiempo;
                                //printf("el tiempo que se lleva es %i\n",tiempoInvertido);
                                //desapila la carga que ya se procesó, x alguna razón se me cae aqui el código
                    //desapilar(pilasCargas[cargaActual - 1]);
                }
            }

        aux = aux->siguiente;
        }
        //printf("el tiempo 2 que se lleva es %i\n",tiempoInvertido);
    }*/

}



int main(int argc, char *argv[]){
    int cantidadCargas, cantidadProcesos;
    int procesoCarga, tiempoProcesoCarga; //para la pila

    FILE *archivo;
    // Abrir el archivo
    archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    //leer cantidad de cargas y procesos
    fscanf(archivo, "%d %d", &cantidadCargas, &cantidadProcesos);

    //guardar orden proceso y tiempo en una pila, para así ir distribuyendo con los topes
    //procesos se van viendo con cola

    //---CREACIÓN COLAS PROCESOS---
    // Crear un arreglo de punteros a Cola
    cola** colasProcesos = (cola**)malloc(cantidadProcesos * sizeof(cola*));
    
    // Inicializar cada cola, se manipulan dsp
    for (int i = 0; i < cantidadProcesos; i++) {
        colasProcesos[i] = crea_cola_vacia();
        printf("cola %i\n", i);
    }

    //---CREACIÓN PILAS DE CARGAS---
    // Crear un arreglo de punteros a Pila
    pila** pilasCargas = (pila**)malloc(cantidadCargas * sizeof(pila*));
    
    // Inicializar cada pila
    for (int i = 0; i < cantidadCargas; i++) {
        pilasCargas[i] = nueva_pila();
    }

    //guardar sus respectivos datos, n°proceso + tiempo en realizarlo, hay que invertirlas!!

    //me almacena el valor de la primera linea de enteros (carga 1), pero como lo hago con las demás cargas?
    int num1, num2;
    int result1, result2;
    int count = 0;
    int j = 0;

    char buffer[100]; // Buffer para leer líneas completas

    // Leer y procesar los datos del archivo línea por línea
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        char *linea = buffer;
        int offset = 0;
        int result;

        // Leer y procesar los pares de enteros en la línea
        for (int z = 0; z < cantidadProcesos; z++) {
            fscanf(archivo,"%d %d", &num1, &num2);
            printf("Proceso: %d, Tiempo: %d\n", num1, num2);
            //imprime_pila(pilasCargas[j]);
           // printf("\nva apilando en %i a %i %i \n", j, num1,num2);
            apilar(pilasCargas[j], num1, num2);
            linea += offset; // Avanzar en la línea
        }
        j = (j + 1) % cantidadCargas; // Cambiar a la siguiente pila después de procesar una línea
    }

    //---PILAS INVERTIDAS, PARA PODER TENER EL PRIMER PROCESO EN EL TOPE DE CADA UNA

    // Inicializar cada pila auxiliar para invertirlas
     pila** pilasCargasAux = (pila**)malloc(cantidadCargas * sizeof(pila*));
    for (int i = 0; i < cantidadCargas; i++) {
        pilasCargasAux[i] = nueva_pila();
    }

   for(j = 0; j < cantidadCargas; j++){
        printf("\nPila carga %i: ", j + 1);
        imprime_pila(pilasCargas[j]);

        printf("PILA INVERTIDA %i\n", j + 1);
        pilasCargasAux[j] = invertirPila(pilasCargas[j]);
        imprime_pila(pilasCargasAux[j]);
    }

    procesamientoCargas(pilasCargasAux, colasProcesos, cantidadCargas);

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    printf("\nCantidad cargas: %d\n", cantidadCargas);
    printf("Cantidad procesos: %d\n", cantidadProcesos);
     // Liberar memoria de las pilas
    for (int i = 0; i < cantidadCargas; i++) {
        free(pilasCargas[i]);
        free(pilasCargasAux[i]);
    }


    return 0;
}
