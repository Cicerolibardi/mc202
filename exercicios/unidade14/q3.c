#include <stdlib.h>
#include <stdio.h>

typedef struct No{
    int dado;
    struct No * esq;
    struct No * dir;
}No;
typedef No * p_no;

p_no criar_arvore ( int x, p_no esq, p_no dir){
    p_no raiz = malloc(sizeof(No));
    raiz->dado = x;
    raiz->esq = esq;
    raiz->dir = dir;
    return raiz;
}
int numeros_nos(p_no raiz){
    if ( raiz == NULL)
        return 0;
    return numeros_nos(raiz->esq) + numeros_nos(raiz->dir) + 1;    
}
