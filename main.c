#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
//#include "TDAlista.h"
//#include "TDApila.h"

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

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    printf("Cantidad cargas: %d\n", cantidadCargas);
    printf("Cantidad procesos: %d\n", cantidadProcesos);




    return 0;
}
