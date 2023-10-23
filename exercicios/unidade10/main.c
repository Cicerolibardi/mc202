#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

int main(){
    p_no lista;
    lista = criar_lista();
    lista = adicionar_no(lista, 5);
    lista = adicionar_no(lista, 4);
    imprimir_listaR(lista);

    return 0;
}