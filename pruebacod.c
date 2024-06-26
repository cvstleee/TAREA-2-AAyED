#include <stdio.h>
#include <stdlib.h>

// Estructuras de datos
typedef struct {
    int proceso;
    int tiempo;
} Carga;

typedef struct {
    Carga *cargas;
    int numCargas;
} CargaSet;

// Función para encontrar el máximo de dos números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Función para procesar las cargas
int procesarCargas(CargaSet *cargaSets, int numCargas, int numProcesos) {
    int *tiempoProceso = (int *)calloc(numProcesos, sizeof(int));
    int *tiempoCarga = (int *)calloc(numCargas, sizeof(int));
    int tiempoTotal = 0;

    for (int i = 0; i < numCargas; i++) {
        int tiempoAcumulado = 0;
        for (int j = 0; j < numProcesos; j++) {
            int procesoActual = cargaSets[i].cargas[j].proceso - 1;
            int tiempoActual = cargaSets[i].cargas[j].tiempo;

            tiempoAcumulado = max(tiempoAcumulado, tiempoProceso[procesoActual]) + tiempoActual;
            tiempoProceso[procesoActual] = tiempoAcumulado;
        }
        tiempoCarga[i] = tiempoAcumulado;
    }

    for (int i = 0; i < numCargas; i++) {
        tiempoTotal = max(tiempoTotal, tiempoCarga[i]);
    }

    free(tiempoProceso);
    free(tiempoCarga);

    return tiempoTotal;
}

int main() {
    // Definición del conjunto de cargas
    CargaSet cargaSets[] = {
        {{ {1, 3}, {2, 3}, {3, 3} }, 3},
        {{ {1, 2}, {3, 3}, {2, 4} }, 3},
        {{ {2, 3}, {1, 2}, {3, 1} }, 3}
    };
    int numCargas = 3;
    int numProcesos = 3;

    // Llamar a la función para procesar las cargas
    int tiempoTotal = procesarCargas(cargaSets, numCargas, numProcesos);
    printf("Tiempo total necesario para procesar todas las cargas: %d\n", tiempoTotal);

    return 0;
}


