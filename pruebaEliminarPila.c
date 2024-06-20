#include <stdio.h>
#include <stdlib.h>
//#include "TDAcola.h"
#include "TDAlista.h"
//#include "TDApila.h"
#include "TDAlistaPila.h"
#include "TDAlistaCola.h"

int main(){
    listaPila *listaPilaProof = nueva_listaPila();
    pila *pilaAux = nueva_pila();

    for(int i = 0; i < 3; i++){
        insertarPila(listaPilaProof, i + 1, pilaAux);
    }
    printf("LISTA PILA INICIAL\n");
    imprime_listaPila(listaPilaProof);
    eliminarNodoListaPila(listaPilaProof, 2);
    printf("LISTA CON PILA 2 ELIMINADA\n");
    imprime_listaPila(listaPilaProof);


}