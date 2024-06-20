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
        //se me va a bucle después del primer ciclo
        printf("TIEMPO PARCIAL INICIAL %i\n", tiempoParcial);
        //se recorre la lista de pilas, ciclo que hace el procesamiento por topes
        //lista para controlar que no se hagan procesos repetidos en el mismo ciclo

        //LO ESTOY REINICIANDO MAL EN EL CASO DE 1 CARGA EN ESPERA Y CARGAS DISTINTAS PROCESADAS AL MISMO TIEMPO
        lista *procesosRealizados = nueva_lista();
        nodo *auxRealizados;

        //revisar carga en espera
        //Si hay una carga en espera, se procesa la en espera como prioridad y las distintas a ella
        //NO ENTRA A ACÁ
        if(!es_lista_vacia(cargaEspera)){
            //en el segundo ciclo entra a acá
            printf("SEGUNDO CICLO\n");
            //buscar la carga en la lista de pilas
            auxListaCargas = pilasCargas->inicio;
            auxEspera = cargaEspera->inicio;
            while(auxListaCargas != NULL){
                if(auxListaCargas->posicion == auxEspera->carga){

                    pilaActual = auxListaCargas->pilaDatos;
                    printf("PILA EN ESPERA\n");
                    imprime_pila(pilaActual);
                    //FUNCIONA BIEN HASTA ACÁ

                    //se procesa la carga en espera
                    procesoActual = tope(pilaActual)->proceso;
                    //deberia ser lo mismo de auxEspera
                    cargaActual = auxListaCargas->posicion;

                    //guarda solo el tiempo mayor de la ronda actual
                    if(tiempoParcial < tope(pilaActual)->tiempo){
                        tiempoParcial = tope(pilaActual)->tiempo;
                    }
                    
                    printf("TIEMPO PARCIAL 2 %i\n", tiempoParcial);

                    //FUNCIONA HASTA ACÁ

                    //ahora posicionarnos en el procesoActual de la lista
                    auxListaProcesos = colasProcesos->inicio;
                    while(auxListaProcesos!= NULL){
                        if(auxListaProcesos->numeroProceso == procesoActual){
                            encolar(auxListaProcesos->colaProceso,cargaActual);
                            desapilar(auxListaCargas->pilaDatos);
                            printf("PILA 2 DESPUES DE DESAPILAR\n");
                            imprime_pila(auxListaCargas->pilaDatos);
                            //se guarda el ya procesado para no repetirlo
                            inserta_inicio(procesosRealizados, cargaActual, procesoActual);
                            //deberia estar solo el 1 1
                            //printf("deberia dar 1 2\n");
                            //imprime_lista(procesosRealizados);

                            if(es_pila_vacia(auxListaCargas->pilaDatos)){
                                //eliminarla de la lista
                                printf("NO DEBERIA ESTAR ACA 2819\n");
                                eliminarNodoListaPila(pilasCargas, auxListaCargas->posicion);
                            }
                        }
                        //FUNCIONA BIEN HASTA ACÁ
                        auxListaProcesos = auxListaProcesos ->siguiente;
                    }
                    //auxListaCargas = auxListaCargas->siguiente;
                }
                //avanza hasta el nulo, pq este ciclo es solo para buscar la carga en espera
            auxListaCargas = auxListaCargas->siguiente;
            }
            //vacia el cargaEspera
            elimina_inicio(cargaEspera);

            //Y SI AQUI MISMO VEO LAS CARGAS !=? no se me ocurre otra cosa tbh
            //NO FUNCIONA ESTO
            /*auxListaCargas = pilasCargas->inicio;
            while(auxListaCargas != NULL){
                pilaActual = auxListaCargas->pilaDatos;
                procesoActual = tope(pilaActual)->proceso;
                cargaActual = auxListaCargas->posicion;

                //buscar si no fueron procesadas en este ciclo
                auxRealizados = procesosRealizados->inicio;
                while(auxRealizados != NULL){
                    if(procesoActual == auxRealizados->proceso){
                        //que avance en la lista
                        auxListaCargas = auxListaCargas->siguiente;
                    }
                    if(cargaActual == auxRealizados->carga);
                        auxListaCargas = auxListaCargas->siguiente;
                }
                //se quedará apuntando a la carga que no tenga un proceso ya realizado o que la carga en si no haya sido procesada
                pilaActual = auxListaCargas->pilaDatos;
                procesoActual = tope(pilaActual)->proceso;
                cargaActual = auxListaCargas->posicion;
                //guarda solo el tiempo mayor de la ronda actual
                if(tiempoParcial < tope(pilaActual)->tiempo){
                    tiempoParcial = tope(pilaActual)->tiempo;
                }

                auxListaProcesos = colasProcesos->inicio;
                while(auxListaProcesos!= NULL){
                    if(auxListaProcesos->numeroProceso == procesoActual){
                        encolar(auxListaProcesos->colaProceso,cargaActual);
                        printf("ENCOLO LA CARGA %i\n", cargaActual);
                        printf("EN EL PROCESO %i\n",auxListaProcesos->numeroProceso);
                        desapilar(auxListaCargas->pilaDatos);
                        printf("PILA DESPUES DE DESAPILAR LO ANTERIOR\n");
                        imprime_pila(auxListaCargas->pilaDatos);


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
            }*/


        }else{
            //de aqui hacia abajo funciona bien

            //ciclo 2, se reinicia, ya que se encoló la carga en espera
            auxListaCargas = pilasCargas->inicio;
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


                //FALLA ACÁ HACIA ABAJO EN EL CASO DE QUE SE REALIZA CARGA EN ESPERA + 1 DISTINTA, VUELVE A LA QUE ERA CARGA EN ESPERA
                //se avanza en la lista de pilas después de haber encolado alguna carga
                //el error debe ser pq no controlo que no exista la carga que se está viendo en la lista de procesados
                
                
                auxListaCargas = auxListaCargas->siguiente;
                printf("AQUI DEBERIA APUNTAR A LA CARGA 2\n");
                imprime_pila(auxListaCargas->pilaDatos);


                pilaActual = auxListaCargas->pilaDatos;
                //ahora hay que ver si el que sigue es repetido, revisando la lista de procesados en el ciclo anterior
                //SOLO VEO REPETIDOS EN ESTE CICLO
                auxRealizados = procesosRealizados->inicio;
                while(auxRealizados != NULL){
                    //si hay un proceso repetido, se deja en espera para el proximo ciclo
                    if(tope(pilaActual)->proceso == auxRealizados->proceso || auxListaCargas->posicion == auxRealizados->carga){
                        printf("CARGA 2 TIENE PROCESO YA REALIZADO, entra a aca \n");
                        //FUNCIONA HASTA ACÁ
                        if(es_lista_vacia(cargaEspera)){
                            //insertar en la lista de carga espera, la carga y su proceso en espera
                            printf("PRIMER REPETIDO, SE GUARDA\n");
                            //FUNCIONA HASTA ACÁ
                            inserta_inicio(cargaEspera, auxListaCargas->posicion, tope(pilaActual)->proceso);
                            printf("CARGA Y PROCESO EN ESPERA\n");
                            imprime_lista(cargaEspera);
                            auxListaCargas = auxListaCargas->siguiente;
                            printf("ahora apunta a la carga 3\n");
                            imprime_pila(auxListaCargas->pilaDatos);
                            printf("\n");
                            //FUNCIONA HASTA ACÁ
                        }else{
                            //si no está vacía la carga en espera
                            //no se deja en espera, pero se avanza
                            auxListaCargas = auxListaCargas->siguiente;
                            //printf("NO DEBERIA ESTAR ACA\n");
                        }
                    }
                    auxRealizados = auxRealizados->siguiente;
                }

                //avanza, no es repetido, que hace?
                //se procesan los distintos que queden
                pilaActual = auxListaCargas ->pilaDatos;
                //printf("PILA 3\n");
                //imprime_pila(pilaActual);
                //se procesa la tercera carga, ya que se repitió el proceso de la 2da
                procesoActual = tope(pilaActual)->proceso;
                cargaActual = auxListaCargas->posicion;
                //guarda solo el tiempo mayor de la ronda actual
                if(tiempoParcial < tope(pilaActual)->tiempo){
                    tiempoParcial = tope(pilaActual)->tiempo;
                }
             
                printf("TIEMPO PARCIAL 1RA Y 3RA CARGA, DEBE DAR 3: %i\n", tiempoParcial);

                //FUNCIONA HASTA ACÁ

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

                        //FUNCIONA BIEN HASTA ACÁ CON EL PRIMER CICLO, CARGA 3

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
                auxListaCargas = auxListaCargas->siguiente;
                //ESTO FUNCIONA BIEN
               // printf("PROCESOS CON CARGAS DEL PRIMER CICLO\n");
                //imprime_listaCola(colasProcesos);
            }
        }

        printf("TIEMPO PARCIAL %i\n", tiempoParcial);
        //se termina el primer ciclo, vuelve a arriba, pero ahora tenemos una carga en espera
        tiempoFinal = tiempoFinal + tiempoParcial;
        tiempoParcial = 0;
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
