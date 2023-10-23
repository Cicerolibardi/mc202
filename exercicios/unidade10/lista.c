#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

p_no criar_lista(){
    return NULL;
}

p_no adicionar_no(p_no lista, int x){
    p_no novo;
    novo = malloc(sizeof(*novo));
    novo->dado = x;
    novo->prox = lista;
    return novo;
}

void imprimir_listaR(p_no lista){
    if (lista == NULL){

    }
    else{
        imprimir_listaR(lista->prox); // imprime na ordem em que foi colocado os números, ao inverter
                                      // essa linha com a 30, imprimirá na ordem em que está ligada.
        printf("%d\n", lista->dado);
    }
}


void imprimir_listaR_reversa(p_no lista){
    if (lista == NULL){

    }
    else{
        printf("%d\n", lista->dado);
        imprimir_listaR_reversa(lista->prox); // imprime na ordem em que foi colocado os números, ao inverter
                                              // essa linha com a 30, imprimirá na ordem em que está ligada.
    }
}


p_no buscar_no(p_no lista, int x){
    for (p_no atual = lista; atual != NULL; atual = atual->prox){
        if (atual->dado == x){
            return atual;
        }
    }
    return NULL;
}

p_no remover_elemento(p_no lista, int x){
    if (lista == NULL){
        return lista;
    }
    else if(lista->dado == x){
        p_no aux = lista;
        lista = lista->prox;
        free(aux);
        return lista;
    }
    else{
        lista->prox = remover_elemento(lista->prox, x);
        return lista;
    }
}

p_no copiar_lista(p_no lista){
    if (lista == NULL){
        return NULL;
    }
    else{
        p_no novo = malloc(sizeof(*novo));
        novo->dado = lista->dado;
        novo->prox = copiar_lista(lista->prox);
        return novo;
    }
}

p_no copiar_lista2(p_no lista){
    if (lista == NULL){
        return NULL;
    }
    else{
        p_no aux = copiar_lista2(lista->prox);
        aux = adicionar_no(aux, lista->dado);
        return aux;
    }
}

p_no concatenar_lista(p_no lista1, p_no lista2){
    if (lista1 == NULL){
        return lista2;
    }
    else{
        lista1->prox = concatenar_lista(lista1->prox, lista2);
        return lista1;
    }
}

p_no remover_circular(p_no lista, p_no no){
    p_no ant;
    if (no->prox == NULL){
        free(no);
        return NULL;
    }
    ant = no.prox;
    while (ant->prox != no)
}
