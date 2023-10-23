#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mensageiro.h"

//Dados o ponteiro para raíz da árvore, o dado e o verso, insere-se um novo nó na árvore
//com esses parâmetros, retornando a raíz para a função.
No_arvore *inserir_arvore(No_arvore *raiz, long int dado, char *texto_verso)
{
    No_arvore *novo;
    if (raiz == NULL)
    {
        novo = malloc(sizeof(No_arvore));
        if (novo == NULL){
            exit(1);
        }

        int tamanho_verso = strlen(texto_verso) + 1; // é adicionado 1 para caber o caractere '\0'
        novo->texto_verso = malloc(tamanho_verso * sizeof(char));
        if (novo->texto_verso == NULL){
            exit(1);
        }

        novo->esq = NULL;
        novo->dir = NULL;

        novo->dado = dado;
        strcpy(novo->texto_verso, texto_verso);
        return novo;
    }
    if (dado < raiz->dado)
    {
        raiz->esq = inserir_arvore(raiz->esq, dado, texto_verso);
    }
    else
    {
        raiz->dir = inserir_arvore(raiz->dir, dado, texto_verso);
    }
    return raiz;
}

// Modifica os valores que são recebidos por raíz para os valores do sucessor,
// removendo o nó do sucessor e atualizando a árvore, ou seja, nao há a remoção
// do nó raiz, e sim a substituição dos seus dados pelos dados do nó do sucessor
// e assim o nó denotado por raíz é automaticamente excluido.
void remover_sucessor(No_arvore *raiz)
{
    No_arvore *min = raiz->dir;
    No_arvore *pai = raiz;
    int tamanho_str_min;

    while (min->esq != NULL)
    {
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min)
        pai->esq = min->dir;
    else
        pai->dir = min->dir;

    free(raiz->texto_verso);
    tamanho_str_min = strlen(min->texto_verso) + 1; // é adicionado 1 para caber o caractere '\0'
    raiz->texto_verso = malloc(tamanho_str_min * sizeof(char));
    if (raiz->texto_verso == NULL){
        exit(1);
    }

    raiz->dado = min->dado;
    strcpy(raiz->texto_verso, min->texto_verso);
    free(min->texto_verso);
    free(min);
}

// Retorna a raíz da árvore após remover o dado, caso ele exista.
// Para casos simples, ou seja, sem duas subárvores, a remoção é feita na própria função.
// Para caso hajam duas subárvores, é chamada a função remover_sucessor().
No_arvore *remover_rec(No_arvore *raiz, long int dado)
{
    No_arvore *aux;
    if (raiz == NULL)
    {
        return NULL;
    }
    if (dado < raiz->dado)
    {
        raiz->esq = remover_rec(raiz->esq, dado);
    }
    else if (dado > raiz->dado)
    {
        raiz->dir = remover_rec(raiz->dir, dado);
    }
    else if (raiz->esq == NULL)
    {
        aux = raiz->dir;
        free(raiz->texto_verso);
        free(raiz);
        return aux;
    }
    else if (raiz->dir == NULL)
    {
        aux = raiz->esq;
        free(raiz->texto_verso);
        free(raiz);
        return aux;
    }
    else
    {
        remover_sucessor(raiz);
    }
    return raiz;
}

// Dado o nó da raíz da árvore e o nó que deseja-se procurar o antecessor,
// busca-se o nó do antecessor, caso ele exista e retorna esse nó. Caso não exista,
// o retorno é NULL.
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

// Acha o máximo de uma árvore e retorna o nó desse máximo.
No_arvore *maximo_arvore(No_arvore *raiz)
{
    if (raiz == NULL || raiz->dir == NULL)
    {
        return raiz;
    }
    return maximo_arvore(raiz->dir);
}

// Faz a busca de um nó, dados o ponteiro para a raíz da árvore e um inteiro que equivale ao dado
// a ser buscado. Caso ele exista, é retornado o nó desse valor. Caso não exista, o retorno é NULL.
No_arvore *buscar_valor(No_arvore *raiz, int dado)
{
    if (raiz == NULL || dado == raiz->dado)
        return raiz;
    if (dado < raiz->dado)
        return buscar_valor(raiz->esq, dado);
    else
        return buscar_valor(raiz->dir, dado);
}

// Busca 3 nós, cujo a soma dos dados desses 3 nós seja igual a autoridade.
// Dentro dessa função, quando acha-se os 3 nós, concatena-se suas strings conforme
// a ordem crescente dos dados, são removidos os 3 nós da árvore, é inserido um novo nó
// com a string concatenada e o dado novo, que no caso é o da autoridade, e retorna-se
// o ponteiro para a raíz dessa árvore.
No_arvore *buscar_triade(No_arvore *raiz, long int autoridade)
{
    Triade triade_valores;

    //busca do máximo até NULL, que seria depois de verificar o mínimo.
    for (triade_valores.a = maximo_arvore(raiz); triade_valores.a != NULL;
         triade_valores.a = buscar_antecessor(raiz, triade_valores.a))
    {

        //busca do antecessor do máximo até NULL, que seria depois de verificar o mínimo.
        for (triade_valores.b = buscar_antecessor(raiz, triade_valores.a);
             triade_valores.b != NULL; triade_valores.b = buscar_antecessor(raiz, triade_valores.b))
        {

            int valor_autoridade_resultante = autoridade - triade_valores.a->dado - triade_valores.b->dado;

            triade_valores.c = buscar_valor(raiz, valor_autoridade_resultante);

            if (triade_valores.c != NULL) // ou seja, achou uma soma de triades a + b + c = autoridade.
            {
                int tam_3_str = strlen(triade_valores.a->texto_verso) + strlen(triade_valores.b->texto_verso)
                             + strlen(triade_valores.c->texto_verso) + 1;
                char *tres_strings_concat = calloc(sizeof(char), tam_3_str);
                if (tres_strings_concat == NULL){
                    exit(1);
                }
                
                strcat(tres_strings_concat, triade_valores.c->texto_verso);
                strcat(tres_strings_concat, triade_valores.b->texto_verso);
                strcat(tres_strings_concat, triade_valores.a->texto_verso);

                raiz = remover_rec(raiz, triade_valores.a->dado);
                raiz = remover_rec(raiz, triade_valores.b->dado);
                raiz = remover_rec(raiz, triade_valores.c->dado);
                raiz = inserir_arvore(raiz, autoridade, tres_strings_concat);
                free(tres_strings_concat);
                return raiz;
            }
        }
    }
    return raiz;
}

// Printa na tela a árvore binária, nesse caso, as strings, conforme o método de escrita inordem
// de uma árvore binária.
void printar_inordem(No_arvore *raiz)
{
    if (raiz != NULL)
    {
        printar_inordem(raiz->esq);
        for (int i = 0; raiz->texto_verso[i] != '\0'; i++)
        {
            printf("%c", raiz->texto_verso[i]);
        }
        printar_inordem(raiz->dir);
    }
}

// Dado o ponteiro para a raíz da árvore, é desalocada toda a memória que está sendo
// utilizada nessa árvore.
void destruir_arvore(No_arvore *raiz)
{
    if (raiz != NULL)
    {
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        free(raiz->texto_verso);
        free(raiz);
    }
}
