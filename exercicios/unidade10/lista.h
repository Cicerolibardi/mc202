#ifndef LISTA_H
#define LISTA_H

struct No{
    int dado;
    struct No *prox;
};

typedef struct No *p_no;

p_no criar_lista();

p_no adicionar_no(p_no lista, int x);

p_no buscar_no(p_no lista, int x);

p_no remover_elemento(p_no lista, int x);

void imprimir_listaR(p_no lista);

void imprimir_listaR_reversa(p_no lista);

p_no copiar_lista(p_no lista);

#endif