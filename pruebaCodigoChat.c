#include <stdio.h>

#define N 4 // Número de cargas
#define M 4 // Número de procesos

typedef struct {
    int process_id;
    int duration;
} Process;

typedef struct {
    Process processes[M];
} Load;

// Datos de ejemplo actualizados
Load loads[N] = {
    { { {1, 92}, {2, 50}, {3, 75}, {4, 24} } },
    { { {1, 28}, {3, 22}, {4, 25}, {2, 22} } },
    { { {4, 86}, {3, 88}, {2, 12}, {1, 91} } },
    { { {1, 97}, {3, 20}, {2, 91}, {4, 37} } }
};


//DA 12 CON EL PROCESAMIENTO 3, DESGLOSAR LÓGICA
void processLoads(Load loads[], int n, int m) {
    //time es como mi tiempo final
    int time = 0;
    //esto no lo tengo separado
    int process_end_times[M] = {0}; // Tiempos de finalización para cada proceso
    int load_end_times[N] = {0};    // Tiempos de finalización para cada carga

    // Inicializar el tiempo actual para cada carga y proceso
    //esto es como el tiempo parcial
    int current_time[N] = {0}; 

    for (int j = 0; j < m; ++j) { // Iterar sobre cada proceso
        for (int i = 0; i < n; ++i) { // Iterar sobre cada carga
            Process current_process = loads[i].processes[j];
            int process_id = current_process.process_id - 1; // Ajustar índice a 0 basado

            // El tiempo de inicio del proceso actual es el máximo entre el tiempo de finalización del proceso anterior para esta carga y el tiempo de finalización del proceso actual para cualquier carga
            int process_start_time = (j == 0) ? current_time[i] : load_end_times[i];
            if (process_start_time < process_end_times[process_id]) {
                process_start_time = process_end_times[process_id];
            }

            int process_end_time = process_start_time + current_process.duration;
            process_end_times[process_id] = process_end_time;
            load_end_times[i] = process_end_time;
            current_time[i] = process_end_time;

            // Actualizar el tiempo total (makespan) si este proceso es el último en finalizar hasta ahora
            if (process_end_time > time) {
                time = process_end_time;
            }

            printf("Carga %d: Proceso %d, Inicio %d, Fin %d\n", i+1, current_process.process_id, process_start_time, process_end_time);
        }
    }

    printf("Tiempo total necesario (makespan): %d\n", time);
}

int main() {
    processLoads(loads, N, M);
    return 0;
}
