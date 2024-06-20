#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
#include "TDAlista.h"
//#include "TDApila.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"

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
//existir, devuelve una lista nula
//se usa TDA lista simple
//devuelve una lista con la carga y el proceso a realizar después del primer desapilado
lista * verificarProcesoRepetido(lista *topes, int cantidadCargas){
    nodo *aux = topes->inicio;
    nodo *sig = aux -> siguiente;
    //int cargaIgual= 0;

    lista *auxLista = nueva_lista();
    //se recorre la lista de topes
    while (aux != NULL) {
        sig = aux->siguiente;
        while (sig != NULL) {
            if (aux ->proceso == sig->proceso) {
                //FUNCIONA BIEN ESTO, aux tiene a la carga 2 y sig a la carga 1
               printf("carga %i tiene el mismo proceso que la carga %i\n", aux->carga, sig->carga);
               inserta_inicio(auxLista,aux->carga, aux->proceso); //me guarda el carga 2 
            }
            //que avance para terminar el ciclo
            sig = sig->siguiente;
        }
        //que avance para terminar el ciclo de los topes
        aux = aux->siguiente;
    }
    return auxLista;
}

//Función que procesa LOS DISTINTOS al mismo tiempo, y compara su tiempo para agregarlo
//a un acumulador
//tiempo acumulado en la primera llamada es 0

//aqui hay que cambiar arreglo a listaPila y listaCola

//esta función hay que llamarla según cuantas cargas hayan (en el main) hasta que queden vacías

//---FUNCIONES PARA PROCESAR CARGAS---

//falta eliminar las pilas que queden vacías

int procesarCargas(listaPila *pilasCargas, listaCola *colasProcesos){
    //Procesamiento
    nodoListaPila *auxListaCargas = pilasCargas->inicio;
    nodoListaCola *auxListaProcesos = colasProcesos->inicio;
    pila *pilaActual;
    int procesoActual = 0;
    int cargaActual = 0;
    int tiempoParcial = 0;
    int tiempoFinal = 0;
    //lista para controlar que no se hagan procesos repetidos en el mismo ciclo
    //lista *procesosRealizados = nueva_lista();
    //nodo *auxRealizados;
    lista *cargaEspera = nueva_lista();
    nodo *auxEspera;
    //mientras queden procesos por realizar
    while(!es_listaPila_vacia(pilasCargas)){
        printf("TIEMPO PARCIAL INICIAL %i\n", tiempoParcial);
        //se recorre la lista de pilas, ciclo que hace el procesamiento por topes
        //lista para controlar que no se hagan procesos repetidos en el mismo ciclo
        lista *procesosRealizados = nueva_lista();
        nodo *auxRealizados;

        //revisar carga en espera
        //Si hay una carga en espera, se procesa la en espera como prioridad y las distintas a ella
        if(!es_lista_vacia(cargaEspera)){
            printf("TIEMPO PARCIAL SEGUNDO %i\n", tiempoParcial);
            //buscar la carga en la lista de pilas
            auxListaCargas = pilasCargas->inicio;
            auxEspera = cargaEspera->inicio;
            while(auxListaCargas != NULL){
                if(auxListaCargas->posicion == auxEspera->proceso){
                    pilaActual = auxListaCargas->pilaDatos;
                    //se procesa la primera carga, ya que de momento su proceso no se repite con ninguna
                    procesoActual = tope(pilaActual)->proceso;
                    //deberia ser lo mismo de auxEspera
                    cargaActual = auxListaCargas->posicion;
                    //guarda solo el tiempo mayor de la ronda actual
                    if(tiempoParcial < tope(pilaActual)->tiempo){
                        tiempoParcial = tope(pilaActual)->tiempo;
                    }
                    printf("TIEMPO PARCIAL 1 %i\n", tiempoParcial);
                    //ahora posicionarnos en el procesoActual de la lista
                    while(auxListaProcesos!= NULL){
                        if(auxListaProcesos->numeroProceso == procesoActual){
                            encolar(auxListaProcesos->colaProceso,cargaActual);
                            desapilar(auxListaCargas->pilaDatos);
                            //se guarda el ya procesado para no repetirlo
                            inserta_inicio(procesosRealizados, cargaActual, procesoActual);
                            if(es_pila_vacia(auxListaCargas->pilaDatos)){
                                //eliminarla de la lista
                                eliminarNodoListaPila(pilasCargas, auxListaCargas->posicion);
                            }
                        }
                        auxListaProcesos = auxListaProcesos ->siguiente;
                    }
                }
            auxListaCargas = auxListaCargas->siguiente;
            }
            //vacia el cargaEspera
            elimina_inicio(cargaEspera);
        }else{
            //de aqui hacia abajo funciona bien
            printf("TIEMPO PARCIAL TERCERO %i\n", tiempoParcial);

            //sin carga en espera
            while(auxListaCargas != NULL){
            printf("TIEMPO PARCIAL CUARTO %i\n", tiempoParcial);

                pilaActual = auxListaCargas->pilaDatos;
                //se procesa la primera carga, ya que de momento su proceso no se repite con ninguna
                procesoActual = tope(pilaActual)->proceso;
                cargaActual = auxListaCargas->posicion;
                //guarda solo el tiempo mayor de la ronda actual
                if(tiempoParcial < tope(pilaActual)->tiempo){
                    tiempoParcial = tope(pilaActual)->tiempo;
                }
                //hasta aqui funciona bien
                printf("TIEMPO PARCIAL QUINTO (CAMBIADO) %i\n", tiempoParcial);

                //ahora posicionarnos en el procesoActual de la lista
                auxListaProcesos = colasProcesos->inicio;
                while(auxListaProcesos!= NULL){
                    if(auxListaProcesos->numeroProceso == procesoActual){
                        encolar(auxListaProcesos->colaProceso,cargaActual);
                        printf("ENCOLO LA CARGA %i\n", cargaActual);
                        printf("EN EL PROCESO %i\n",auxListaProcesos->numeroProceso);
                        desapilar(auxListaCargas->pilaDatos);
                        printf("PILA DESPUES DE DESAPILAR LO ANTERIOR\n");
                        imprime_pila(auxListaCargas->pilaDatos);

                        //FUNCIONA BIEN HASTA ACÁ CON EL PRIMER CICLO

                        //se guarda el ya procesado para no repetirlo
                        inserta_inicio(procesosRealizados, cargaActual, procesoActual);
                        printf("PROCESO YA REALIZADO GUARDADO\n");
                        imprime_lista(procesosRealizados);
                        //FUNCIONA BIEN HASTA ACÁ CON LA PRIMERA CARGA

                        if(es_pila_vacia(auxListaCargas->pilaDatos)){
                            printf("NO DEBERIA ENTRAR ACA\n");
                                //eliminarla de la lista
                                eliminarNodoListaPila(pilasCargas, auxListaCargas->posicion);
                            }
                    }
                    //AVANZA
                    auxListaProcesos = auxListaProcesos ->siguiente;
                }
                //se avanza en la lista de pilas después de haber encolado alguna carga
                auxListaCargas = auxListaCargas->siguiente;
                printf("AQUI DEBERIA APUNTAR A LA CARGA 2\n");
                imprime_pila(auxListaCargas->pilaDatos);
                //FUNCIONA HASTA ACÁ
                
                pilaActual = auxListaCargas->pilaDatos;
                //ahora hay que ver si el que sigue es repetido, revisando la lista de procesados en el ciclo anterior
                auxRealizados = procesosRealizados->inicio;
                while(auxRealizados != NULL){
                    //si hay un proceso repetido, se deja en espera para el proximo ciclo
                    if(tope(pilaActual)->proceso == auxRealizados->proceso){
                        if(cargaEspera == NULL){
                            //insertar en la lista de carga espera, la carga y su proceso en espera
                            inserta_inicio(cargaEspera, auxListaCargas->posicion, tope(pilaActual)->proceso);
                            auxListaCargas = auxListaCargas->siguiente;
                        }else{
                            //no se deja en espera, pero se avanza
                            auxListaCargas = auxListaCargas->siguiente;
                        }
                    }else{
                        //caso proceso != y no se encuentra en los ya procesados, se realiza el mismo ciclo de arriba
                        //pero sin el while, ya que se avanzó antes
                                pilaActual = auxListaCargas->pilaDatos;
                                //se procesa la primera carga, ya que de momento su proceso no se repite con ninguna
                                procesoActual = tope(pilaActual)->proceso;
                                cargaActual = auxListaCargas->posicion;
                                //guarda solo el tiempo mayor de la ronda actual
                                if(tiempoParcial < tope(pilaActual)->tiempo){
                                    tiempoParcial = tope(pilaActual)->tiempo;
                                }
                                //ahora posicionarnos en el procesoActual de la lista
                                while(auxListaProcesos!= NULL){
                                    if(auxListaProcesos->numeroProceso == procesoActual){
                                        encolar(auxListaProcesos->colaProceso,cargaActual);
                                        desapilar(auxListaCargas->pilaDatos);
                                        //se guarda el ya procesado para no repetirlo
                                        inserta_inicio(procesosRealizados, cargaActual, procesoActual);
                                        if(es_pila_vacia(auxListaCargas->pilaDatos)){
                                            //eliminarla de la lista
                                            eliminarNodoListaPila(pilasCargas, auxListaCargas->posicion);
                                        }
                                    }
                                    auxListaProcesos = auxListaProcesos ->siguiente;
                                }
                        }
                }
            }
        }
        printf("TIEMPO PARCIAL %i\n", tiempoParcial);
        //se termina el primer ciclo, vuelve a arriba, pero ahora tenemos una carga en espera
        tiempoFinal = tiempoFinal + tiempoParcial;
    }
    return tiempoFinal;
}

/* int procesarCargas(listaPila *pilasCargas, listaCola *colasProcesos, int cantidadCargas, int cantidadProcesos, int tiempoAcumulado, int cargaEspera) {
    if (cargaEspera == 0) {
        return procesarCargasDistintas(pilasCargas, colasProcesos, cantidadProcesos, tiempoAcumulado);
    } else {
        return procesarCargaEnEspera(pilasCargas, colasProcesos, cantidadCargas, cantidadProcesos, tiempoAcumulado, cargaEspera);
    }
}*/


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
    //printf("LISTA COLA INICIALIZADA CON SOLO POSICIONES, COLAS VACIAS\n");
    //imprime_listaCola(colasProcesos);

    int tiempo = 0;
    tiempo = procesarCargas(pilasCargas, colasProcesos);
    printf("TIEMPO AAAAAAA %i\n", tiempo);
    
    //---PROCESAMIENTO DE CARGAS DESPUÉS DE SACAR INFO DEL ARCHIVO
    //PASO 1: extraer topes
   // lista *listaTopes = nueva_lista();
    /*llenarTopes(pilasCargas, listaTopes, cantidadCargas);
    printf("LISTA TOPES INICIALES\n");
    imprime_lista(listaTopes);
    
    lista *pruebaCarga;

    pruebaCarga = verificarProcesoRepetido(listaTopes, cantidadCargas);

    printf("la carga que se repite es %i y su proceso es %i\n", pruebaCarga ->inicio ->carga, pruebaCarga->inicio->proceso);

    //parte para revisar si procesa bien los procesos !=

    //prueba sin cargas en espera
    //debe darme 12 KLDHSFJ
    int tiempo = 0;
    tiempo = procesarCargas(pilasCargas, colasProcesos, cantidadCargas, cantidadProcesos, 0, 0);

    printf("TIEMPO AAA: %i\n", tiempo);*/


    //Ahora como voy modificando los topes, eso debería terminar cuando todas las cargas estén vacías...

   // procesamientoCargas(pilasCargasAux, colasProcesos, cantidadCargas);

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    //printf("\nCantidad cargas: %d\n", cantidadCargas);
    //printf("Cantidad procesos: %d\n", cantidadProcesos);
    


    return 0;
}
