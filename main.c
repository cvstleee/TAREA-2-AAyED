#include <stdio.h>
#include <stdlib.h>
#include "TDAcola.h"
//#include "TDAlista.h"
#include "TDApila.h"

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
