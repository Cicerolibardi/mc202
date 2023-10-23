#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas_legais.h"

// Modifica a cor do pai para vermelho e a cor dos dois filhos para preto.
void sobe_vermelho(No_arvore *raiz)
{
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

// Verifica se um nó é vermelho.
int ehVermelho(No_arvore *x)
{
    if (x == NULL)
        return 0;
    return x->cor == VERMELHO;
}

// Verifica se um nó é preto.
int ehPreto(No_arvore *x)
{
    if (x == NULL)
        return 1;
    return x->cor == PRETO;
}

// Faz a rotação da árvore para a esquerda para quando necessita-se balanceamento.
No_arvore *rotaciona_para_esquerda(No_arvore *raiz)
{
    No_arvore *x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

// Faz a rotação da árvore para a direita para quando necessita-se balanceamento.
No_arvore *rotaciona_para_direita(No_arvore *raiz)
{
    No_arvore *x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

// Insere recursivamente em uma árvore um novo nó (função chamada pela função inserir)
No_arvore *inserir_rec(No_arvore *raiz, long int dado)
{
    No_arvore *novo;
    if (raiz == NULL)
    {
        novo = malloc(sizeof(No_arvore));
        novo->esq = novo->dir = NULL;
        novo->dado = dado;
        novo->qtd_dado = 1;
        novo->cor = VERMELHO;
        return novo;
    }
    if (dado < raiz->dado)
        raiz->esq = inserir_rec(raiz->esq, dado);
    else if (dado > raiz->dado)
        raiz->dir = inserir_rec(raiz->dir, dado);
    else if (dado == raiz->dado)
        raiz->qtd_dado += 1;

    /* corrige a árvore */
    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
        raiz = rotaciona_para_esquerda(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        sobe_vermelho(raiz);
    return raiz;
}

// A partir de inserir_rec, insere um novo dado na raíz, balanceando a cor da raiz posteriormente
No_arvore *inserir(No_arvore *raiz, long int dado)
{
    raiz = inserir_rec(raiz, dado);
    raiz->cor = PRETO;
    return raiz;
}

// Busca um nó em uma árvore com o dado correspondente e retorna esse nó.
No_arvore *buscar_arvore(No_arvore *raiz, long int dado)
{
    if (raiz == NULL || dado == raiz->dado)
        return raiz;
    if (dado < raiz->dado)
        return buscar_arvore(raiz->esq, dado);
    else
        return buscar_arvore(raiz->dir, dado);
}

// Busca o antecessor de um nó em uma árvore e retorna esse nó
No_arvore *buscar_antecessor(No_arvore *raiz, No_arvore *atual)
{
    No_arvore *aux = NULL;
    No_arvore *aux_raiz = raiz;
    // para achar o antecessor, se a subarvore esquerda não for nula,
    // precisa-se de buscar o mais a direita do atual->esquerda.
    if (atual->esq != NULL)
    {
        aux = atual->esq;
        while (aux->dir != NULL)
        {
            aux = aux->dir;
        }
        return aux;
    }
    // para caso a subárvore esquerda seja nula, deve-se percorrer a partir da raíz,
    // buscando-se a última "curva" a direita realizada, até achar-se o nó com o valor desejado
    // então o nó antecessor ao que deseja-se é o último a virar à esquerda.
    else
    {
        while (atual->dado != aux_raiz->dado)
        {
            if (atual->dado > aux_raiz->dado)
            {
                aux = aux_raiz; //guardará qual foi a última "curva" a esquerda.
                aux_raiz = aux_raiz->dir;
            }
            else
            {
                aux_raiz = aux_raiz->esq;
            }
        }
        return aux;
    }
    return aux;
}

// Busca o nó com valor máximo na árvore e retorna esse nó.
No_arvore *maximo_arvore(No_arvore *raiz)
{
    if (raiz == NULL || raiz->dir == NULL)
    {
        return raiz;
    }
    return maximo_arvore(raiz->dir);
}

// Descobre a quantidade de nós que necessita-se de retirar para uma árvore ficar legal,
// printando na tela essa quantidade. O return é a raíz da árvore
No_arvore *qtd_retirar_tornar_legal(No_arvore *raiz)
{
    No_arvore *aux;
    int qtd_retirar = 0;

    for (aux = maximo_arvore(raiz); aux != NULL; aux = buscar_antecessor(raiz, aux))
    {
        if (aux->dado > aux->qtd_dado){
            qtd_retirar += aux->qtd_dado;
        }
        else if (aux->dado < aux->qtd_dado){
            qtd_retirar += aux->qtd_dado - aux->dado;
        }
    }
    printf("%d\n", qtd_retirar);
    return raiz;
}

// Verifica se a operação é 1, 2 ou 3 e printa na tela para cada caso. O return value é a raíz
// da árvore.
No_arvore *identificar_operacao_e_operar(No_arvore *raiz)
{
    int operacao;
    long int dado;

    scanf("%d", &operacao);

    if (operacao == 1)
    {
        scanf("%ld", &dado);
        raiz = inserir(raiz, dado);
    }
    else if (operacao == 2)
    {
        scanf("%ld", &dado);
        No_arvore *no_desejado = buscar_arvore(raiz, dado);
        if (no_desejado != NULL){
            printf("%d\n", no_desejado->qtd_dado);
        }
        else{
            printf("0\n");
        }
        
    }
    else if (operacao == 3)
    {
        raiz = qtd_retirar_tornar_legal(raiz);
    }
    return raiz;
}

// A partir da raíz de uma árvore, libera toda a memória alocada para esta.
void deletar_arvore(No_arvore *raiz)
{
    if (raiz != NULL)
    {
        deletar_arvore(raiz->esq);
        deletar_arvore(raiz->dir);
        free(raiz);
    }
}