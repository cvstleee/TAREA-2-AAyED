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

//Función que verifica si hay procesos repetidos, con que uno se repita, queda uno en espera y ese entrega, en caso de no
//existir, devuelve un 0
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
int procesarCargas(pila ** pilasCargas, cola ** colasProcesos, int cantidadCargas, int tiempoAcumulado, int cargaEspera){
    int i;
    int cargaActual = 0;
    int procesoActual = 0;
    int tiempoParcial = 0; //aqui se comparan los tiempos de las cargas que se procesan a la vez en procesos !=
    //caso todos los procesos != 
    if(cargaEspera == 0){
        for(i = 0; i < cantidadCargas; i++){
               if(pilasCargas[i] != NULL){
                    procesoActual = tope(pilasCargas[i])->proceso;
                    cargaActual = i + 1;
                    encolar(colasProcesos[procesoActual], cargaActual);
                    desapilar(pilasCargas[cargaActual - 1]);
                    //tiempo parcial siempre será el mayor de los obtenidos en esa ronda
                    if(tiempoParcial < tope(pilasCargas[i])->tiempo){
                            tiempoParcial = tope(pilasCargas[i])->tiempo;
                    }
               } 
        }
    }//si hay carga en espera, es pq hay iguales, aqui hay que controlar que solo se procesen las distintas
    if(cargaEspera != 0){
        //se procesa la carga que quedó en espera primero pq es prioridad
        procesoActual = tope(pilasCargas[cargaEspera - 1])->proceso;
        encolar(colasProcesos[procesoActual], cargaEspera);
        tiempoParcial = tope(pilasCargas[cargaEspera - 1])->tiempo;
        desapilar(pilasCargas[cargaEspera - 1]);
        for(i = 0; i < cantidadCargas; i++){
            //si no es la misma carga ya procesada y a la vez el proceso es != al ya procesado en la de espera
            if((i != cargaEspera - 1) && (pilasCargas[i] != NULL) && (tope(pilasCargas[cargaEspera - 1])->proceso != tope(pilasCargas[i])->proceso)){
                procesoActual = tope(pilasCargas[i])->proceso;
                cargaActual = i + 1;
                encolar(colasProcesos[procesoActual], cargaActual);
                desapilar(pilasCargas[cargaActual - 1]);
               //tiempo parcial siempre será el mayor de los obtenidos en esa ronda
               if(tiempoParcial < tope(pilasCargas[i])->tiempo){
                    tiempoParcial = tope(pilasCargas[i])->tiempo;
               }
            }
        }
    }
    tiempoAcumulado = tiempoAcumulado + tiempoParcial;
    return tiempoAcumulado;
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

    //---PROCESAMIENTO DE CARGAS DESPUÉS DE SACAR INFO DEL ARCHIVO
    //Ahora como voy modificando los topes, eso debería terminar cuando todas las cargas estén vacías...

   // procesamientoCargas(pilasCargasAux, colasProcesos, cantidadCargas);

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
