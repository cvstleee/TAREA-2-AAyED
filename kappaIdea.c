#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"
#include "time.h"

//Función que revisa si se puede asignar una carga a un proceso
//Lo que en otras palabras significa que un proceso no tenga una carga procesandose, lo que significa que la lista de procesos actuales
//está vacía
//también revisa que otra carga no se esté procesando actualmente, ya que puede hacer un proceso a la vez
//devuelve bool, pero realmente es int
//debereía significar que hay procesosActuales vacíos, creo que no es tan necesario el pilasCargas

int sePuedeAsignar(lista *procesosActuales, listaPila *pilasCargas){
    nodo *auxProcesos = procesosActuales ->inicio;

    while(auxProcesos != NULL){
        //si un proceso está vacío
        if(auxProcesos->carga == 0){
            //hay que buscar si alguna carga tiene ese proceso en el tope
            printf("EXISTE PROCESO SIN CARGA ASIGNADA\n");
            nodoListaPila *auxListaCargas = pilasCargas->inicio;
            while(auxListaCargas != NULL){
                if(tope(auxListaCargas->pilaDatos)->proceso == auxProcesos->proceso){
                    printf("EXISTE CARGA CON PROCESO SIN CARGA ASIGNADA\n");
                    return 1;
                }
                auxListaCargas = auxListaCargas->siguiente;
            }
        }
        auxProcesos = auxProcesos->siguiente;
    }
    return 0;
}

//Función que asigna cargas a procesos vacíos, las agrega a la lista de procesosActuales y a la cola de procesos realizados

void asignarCargas(lista *procesosActuales, listaPila *pilasCargas, listaCola *procesosRealizados){
    nodo *auxProcesos = procesosActuales->inicio;

    while(auxProcesos != NULL){
        //hay que buscar si alguna carga tiene ese proceso en el tope
        printf("PROCESO ACTUAL %i\n", auxProcesos->proceso);
        nodoListaPila *auxListaCargas = pilasCargas->inicio;
        while(auxListaCargas != NULL){
            printf("CARGA ACTUAL %i\n", auxListaCargas->posicion);
            if(tope(auxListaCargas->pilaDatos)->proceso == auxProcesos->proceso && auxProcesos -> carga == 0){
                nodoListaCola *auxRealizados = procesosRealizados->inicio;
                //ahora la carga del proceso con carga nula, será la posición del aux, ya que nos da el n° de la pila
                auxProcesos->carga = auxListaCargas->posicion;
                printf("COMO VA COLA DE PROCESOS ACTUALES\n");
                imprime_lista(procesosActuales);
                //y se guarda en procesosRealizados
                while(auxRealizados != NULL){
                    if(auxRealizados->numeroProceso == auxProcesos->proceso){
                        encolar(auxRealizados->colaProceso, auxListaCargas->posicion);
                        printf("COMO VA COLA DE PROCESOS REALIZADOS\n");
                        imprime_listaCola(procesosRealizados);
                    }
                    auxRealizados = auxRealizados->siguiente;
                }
            }
            auxListaCargas = auxListaCargas->siguiente;
        }
        auxProcesos = auxProcesos->siguiente;
    }
    printf("\nTERMINA DE ASIGNAR CARGAS\n");
}


//según los procesos actuales, va desapilando en pilasCargas la carga que está siendo procesada hasta llegar a t = 0, avanza solo de 1 en 1 
//restando en 1
//en otra función, se irá aumentando el tiempo cada que esta se utilice
void avanzarProcesamiento(lista *procesosActuales, listaPila *pilasCargas){
    nodo *auxProcesos = procesosActuales->inicio;

    //se buscan las cargas 
    while(auxProcesos != NULL){
        nodoListaPila *auxCargas = pilasCargas->inicio;
        while(auxCargas != NULL){
            //busco la carga, ya que si un proceso tiene una carga asignada es pq se está realizando
            if(auxProcesos -> carga == auxCargas->posicion && tope(auxCargas->pilaDatos)->tiempo != 0){
                int tiempoCargaActual = tope(auxCargas->pilaDatos)->tiempo;
                tiempoCargaActual = tiempoCargaActual - 1;
                tope(auxCargas->pilaDatos)->tiempo = tiempoCargaActual;
            }
            //si el tiempo es == 0, significa que el proceso terminó
            if(tope(auxCargas->pilaDatos)->tiempo == 0){
                desapilar(auxCargas->pilaDatos);
                auxProcesos -> carga == 0;
                if (es_pila_vacia(auxCargas->pilaDatos)) {
                    eliminarNodoListaPila(pilasCargas, auxCargas->posicion);
                    auxCargas = NULL;
                }
            }
            auxCargas = auxCargas->siguiente;
        }
        auxProcesos = auxProcesos->siguiente;
    }
}

//PARA ELIMINAR PILAS VACÍAS DE LA LISTA
/*if (es_pila_vacia(auxListaCargas->pilaDatos)) {
                eliminarNodoListaPila(pilasCargas, auxListaCargas->posicion);
                auxListaCargas = NULL;
            }
*/

int procesamientoCargas(listaCola *colasProcesos, listaPila *pilasCargas, int cantidadProcesos){
    //procesos actuales inicia vacío
    lista *procesosActuales = nueva_lista();
    int i;
    for(i = cantidadProcesos; i >= 1; i--){
        inserta_inicio(procesosActuales, 0, i);
    }
    printf("PROCESOS ACTUALES\n");
    imprime_lista(procesosActuales);


    int tiempo = 0;

    while(!es_listaPila_vacia(pilasCargas)){
        if(sePuedeAsignar(procesosActuales, pilasCargas)){
            printf("SALIO DEL LOOP RARO\n");
            asignarCargas(procesosActuales, pilasCargas, colasProcesos);
            avanzarProcesamiento(procesosActuales, pilasCargas);
            tiempo++;
            printf("TIEMPO ACTUAL %i\n", tiempo);
        }else{
            avanzarProcesamiento(procesosActuales, pilasCargas);
            tiempo++;
            printf("TIEMPO ACTUAL %i\n", tiempo);
        }
    }
    return tiempo;
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

    int tiempo;
    //calculo de tiempo
    //float tiempo_algoritmo = 0;
	//clock_t clock_ini, clock_fin;

    //clock_ini = clock();

    tiempo = procesamientoCargas(colasProcesos, pilasCargas, cantidadProcesos);
    imprime_listaCola(colasProcesos);
    printf("TIEMPO AAAAAAA %i\n", tiempo);
	
	//clock_fin = clock();
	//tiempo_algoritmo = (float)((clock_fin - clock_ini) / CLOCKS_PER_SEC);
	
	//printf("\nTiempo del algoritmo en segundos: %.2f  \n", tiempo_algoritmo); 


    // Cerrar el archivo
    fclose(archivo);
    //faltan free cola proceso, pilascargas

    // Imprimir los valores almacenados
    //printf("\nCantidad cargas: %d\n", cantidadCargas);
    //printf("Cantidad procesos: %d\n", cantidadProcesos);
    


    return 0;
}