#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor.h"

int main()
{
    int n, q;
    char palavra_correta[27];
    char palavra_errada[27];
    p_hash tabela_verdes;
    p_hash tabela_amarelos;

    tabela_verdes = criar_hash();
    tabela_amarelos = criar_hash();

    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++)
    {
        scanf("%s", palavra_correta);
        inserir_hash(tabela_verdes, palavra_correta);
        gerar_permutacoes_palavras(tabela_amarelos, palavra_correta);
    }

    for (int i = 0; i < q; i++)
    {
        scanf("%s", palavra_errada);
        buscar_tabelas_e_printar(tabela_verdes, tabela_amarelos, palavra_errada);
    }

    for (int i = 0; i < MAX; i++)
    {
        destruir_lista(tabela_verdes->vetor[i]);
        destruir_lista(tabela_amarelos->vetor[i]);
    }

    free(tabela_verdes->vetor);
    free(tabela_amarelos->vetor);
    free(tabela_verdes);
    free(tabela_amarelos);
}