#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planilha.h"

int main()
{
    int colunas, linhas;
    char local_arquivo[TAM_MAX_ARQUIVO];

    scanf("%s %d %d", local_arquivo, &colunas, &linhas);

    Vertice **tabela = ler_tabela(local_arquivo, colunas, linhas);

    char operacao;
    char celula[TAM_MAX_EXPRESSAO];
    char nova_expressao[TAM_MAX_EXPRESSAO];
    Endereco endereco;
    while (scanf(" %c %s", &operacao, celula) == 2)
    {
        endereco = descobrir_celula(celula);
        printf("%s: ", celula);
        if (operacao == 'S')
        {
            scanf("%s", nova_expressao);
            printf("%s ->", tabela[endereco.linha][endereco.coluna].expressao[0]);
            tabela = atualizar_celula(tabela, nova_expressao, endereco);
            printf(" %s\n", tabela[endereco.linha][endereco.coluna].expressao[0]);
        }
        else if (operacao == 'G')
        {
            Valor_visitado valor_retorno = calcular_valor_expressao(tabela, celula);
            if (valor_retorno.visitado == 0)
                printf("%d\n", valor_retorno.resultado);
            else
                printf("#ERRO#\n");
        }
    }

    liberar_tabela(tabela, linhas, colunas);
}
