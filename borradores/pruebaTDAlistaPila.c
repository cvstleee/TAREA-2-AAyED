#include <stdio.h>
#include "TDAlistaCola.h"
//#include "TDApila.h"

int main(){
    /*pila *A = nueva_pila();
    apilar(A, 5,6);
    apilar(A, 6,6);

    printf("pila 1\n");
    imprime_pila(A);

    pila *B = nueva_pila();
    apilar(B, 3, 4);
    apilar(B, 2, 3);

    printf("pila 2\n");
    imprime_pila(B);

    listaPila *prueba = nueva_listaPila();
    insertarPila(prueba, 1, A);
    insertarPila(prueba, 2, B);

    printf("lista con pilas\n");
    imprime_listaPila(prueba);*/

    cola *A = crea_cola_vacia();
    encolar(A, 2);
    encolar(A, 3);

    printf("cola 1\n");
    imprime_cola(A);

    cola *B = crea_cola_vacia();
    encolar(B, 1);
    encolar(B, 0);

    printf("cola 2\n");
    imprime_cola(B);

    listaCola * prueba = nueva_listaCola();
    //imprime_listaCola(prueba);
    insertarCola(prueba, 1, A);
    //imprime_cola(A);
    imprime_listaCola(prueba);
    insertarCola(prueba, 2, B);
    imprime_listaCola(prueba);

    liberar_cola(A);
    liberar_cola(B);
    libera_listaCola(prueba);
}