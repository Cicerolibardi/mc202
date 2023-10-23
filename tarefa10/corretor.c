#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor.h"

// Gera o hash de uma palavra pelo método da divisão.
int hash(char *palavra)
{
    int i, n = 0;
    for (i = 0; i < strlen(palavra); i++)
        n = (256 * n + palavra[i]) % MAX;
    return n;
}

// Insere um novo nó em uma lista, tendo como parâmetro principal a palavra.
p_no inserir_lista(p_no lista, char *palavra)
{
    p_no novo;
    novo = malloc(sizeof(No));
    if (novo == NULL)
        exit(1);

    novo->palavra = malloc(27 * sizeof(char));

    strcpy(novo->palavra, palavra);
    novo->prox = lista;
    return novo;
}

// Insere um novo nó na posição "n" do hash.
void inserir_hash(p_hash t, char *palavra)
{
    int n = hash(palavra);
    t->vetor[n] = inserir_lista(t->vetor[n], palavra);
}

// Cria uma tabela hash com todas as posições nulas de início e retorna
// essa hash.
p_hash criar_hash()
{
    p_hash tabela_criar;

    tabela_criar = malloc(sizeof(Hash));
    if (tabela_criar == NULL)
        exit(1);

    tabela_criar->vetor = malloc(MAX * sizeof(p_no));
    if (tabela_criar->vetor == NULL)
        exit(1);

    for (int i = 0; i < MAX; i++)
    {
        tabela_criar->vetor[i] = NULL;
    }

    return tabela_criar;
}

// Dado o ponteiro pra lista, libera a memória de todos os nós dessa lista.
void destruir_lista(p_no lista)
{
    p_no aux;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->prox;
        free(aux->palavra);
        free(aux);
    }
}

// Gera todas as permutações das palavras corretas para palavras com 1 erro e coloca na
// hash "tabela_amarelos"
void gerar_permutacoes_palavras(p_hash tabela_amarelos, char *palavra)
{
    char copia_palavra[27];
    int k;
    strcpy(copia_palavra, palavra);

    // Gera a permutação das palavras corretas do dicionário mudando as letras da palavra por todas
    // as outras letras, sem adicionar ou remover letras.
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        for (int j = 0; j <= 'z' - 'a'; j++)
        {
            copia_palavra[i] = 'a' + j;
            inserir_hash(tabela_amarelos, copia_palavra);
        }
        strcpy(copia_palavra, palavra);
    }

    // Gera a permutação das palavras corretas do dicionário retirando uma letra por vez, ou seja, formando
    // uma palavra com tamanho menor em 1 letra da palavra original. Exemplo de como funciona:
    // Dada a palavra "ova", as palavras geradas e inseridas na hash serão: va, oa, ov.
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        strncpy(copia_palavra, palavra, i);
        for (int j = i; palavra[j] != '\0'; j++)
        {
            copia_palavra[j] = palavra[j + 1];
        }
        inserir_hash(tabela_amarelos, copia_palavra);
        strcpy(copia_palavra, palavra);
    }

    // Gera a permutação das palavras corretas do dicionário, inserindo as letras de 'a' até 'z' no ínicio
    // da palavra e entre as letras das palavras, aumentando em 1 o tamanho da palavra original. Não adiciona
    // as letras de 'a' a 'z' após a ultima letra da palavra.
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        strncpy(copia_palavra, palavra, i);
        for (int j = 0; j <= 'z' - 'a'; j++)
        {
            copia_palavra[i] = 'a' + j;
            for (k = i; palavra[k] != '\0'; k++)
            {
                copia_palavra[k + 1] = palavra[k];
            }
            copia_palavra[k + 1] = '\0';
            inserir_hash(tabela_amarelos, copia_palavra);
            strcpy(copia_palavra, palavra);
        }
    }

    // Gera a permutação das palavras corretas do dicionário, inserindo as letras de 'a' até 'z' no fim da
    // palavra, após a ultima letra da palavra correta, aumentando em 1 o tamanho da palavra original. Serve
    // para complementar a iteração acima.
    for (int j = 0; j <= 'z' - 'a'; j++)
    {
        int tam_palavra = strlen(palavra);
        copia_palavra[tam_palavra] = 'a' + j;
        copia_palavra[tam_palavra + 1] = '\0';
        inserir_hash(tabela_amarelos, copia_palavra);
        strcpy(copia_palavra, palavra);
    }
}

// Busca nas tabelas verdes e amarelos a palavra digitada no teclado.
// Caso esteja na verde, printará verde e não buscará mais. Caso não esteja na verde
// busca-se na tabela amarela, e, caso esteja nela, printará amarelo e parará a busca.
// Caso não esteja em nenhuma das duas tabelas, printará vermelho.
void buscar_tabelas_e_printar(p_hash tabela_verdes, p_hash tabela_amarelos, char *palavra)
{
    p_no pont_no;
    int n, retorno_comp;

    n = hash(palavra);

    pont_no = tabela_verdes->vetor[n];

    while (pont_no != NULL)
    {
        retorno_comp = strcmp(palavra, pont_no->palavra);
        if (retorno_comp == 0)
        {
            printf("verde\n");
            return;
        }
        pont_no = pont_no->prox;
    }

    pont_no = tabela_amarelos->vetor[n];
    while (pont_no != NULL)
    {
        retorno_comp = strcmp(palavra, pont_no->palavra);
        if (retorno_comp == 0)
        {
            printf("amarelo\n");
            return;
        }
        pont_no = pont_no->prox;
    }
    printf("vermelho\n");
    return;
}