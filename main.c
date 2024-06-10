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
    int count = 0;
    for(int i = 0; i < cantidadCargas; i++){
        while (fscanf(archivo, "%d", &num1) == 1) {
            count++;
            if (fscanf(archivo, "%d", &num2) == 1) {
                printf("n° proceso: %d, tiempo: %d\n", num1, num2);
                count++;
            } else {
                printf("Solo 1 numero, pero este no deberia pasar Num1: %d, Num2: None\n", num1);
            }
        }
        // y al terminar debería apilar y limpiarlos, para que pase al siguiente, pero como lo hago?
    }



    /*
    for(int i = 0; i < cantidadProcesos; i++){
        fscanf(archivo, "%d %d")
        apilar(pilasCargas[0], )
    }*/

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    printf("Cantidad cargas: %d\n", cantidadCargas);
    printf("Cantidad procesos: %d\n", cantidadProcesos);


    return 0;
}
