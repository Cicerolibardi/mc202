#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planilha.h"

// Lê uma entrada com o arquivo csv, delimintando os caracteres chaves por ',' ou '\n'
// para que leia somente até esses caracteres e insira no local correto da matriz.
Vertice **ler_tabela(char *local_arquivo, int colunas, int linhas)
{
    FILE *arquivo = fopen(local_arquivo, "r");
    char *expressao;

    Vertice **tabela = malloc(linhas * sizeof(Vertice *));

    for (int i = 0; i < linhas; i++)
    {
        tabela[i] = malloc(colunas * sizeof(Vertice));
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            tabela[i][j].visitado = 0;
            // O bloco abaixo transforma a string lida em um vetor de strings,
            // por exemplo ["=", "(", "A5", "-", "A3", ")"], sem a inclusão dos espaços.
            tabela[i][j].expressao = malloc(MAX_EXPRESSAO_ENTRADA * sizeof(char *));
            fscanf(arquivo, " %m[^,\n]", &expressao);
            fscanf(arquivo, "%*c");
            char *provisorio = strtok(expressao, " ");
            int contador = 0;
            while (provisorio != NULL)
            {
                tabela[i][j].expressao[contador] = malloc(TAM_MAX_EXPRESSAO * sizeof(char));
                strcpy(tabela[i][j].expressao[contador], provisorio);
                provisorio = strtok(NULL, " ");
                contador += 1;
            }

            tabela[i][j].tam_expressao = contador;
            free(expressao);
        }
    }
    fclose(arquivo);
    return tabela;
}

// Dado uma expressão do tipo "G13", retorna qual o endereço (linha e coluna)
// dessa célula na matriz.
Endereco descobrir_celula(char *expressao)
{
    Endereco endereco;
    endereco.coluna = expressao[0] - 'A';
    endereco.linha = atoi(expressao + 1) - 1;
    return endereco;
}

// Atualiza uma célula na tabela com a nova expressão do endereço dado.
Vertice **atualizar_celula(Vertice **tabela, char *nova_expressao, Endereco endereco)
{
    strcpy(tabela[endereco.linha][endereco.coluna].expressao[0], nova_expressao);
    return tabela;
}

// Verifica se tal vértice já foi visitado, utilizado para saber se houve
// ciclo ou não.
int esta_visitado(Vertice **tabela, Endereco endereco)
{
    if (tabela[endereco.linha][endereco.coluna].visitado == 1)
    {
        return 1;
    }
    return 0;
}

// Calcula o valor de uma célula, sendo essas expressões ou números inteiros.
// Retorna um valor do tipo Valor_visitado, que se retorno.visitado for 1, quer 
// dizer que houve um ciclo, ou seja, há um erro. Caso seja 0, o retorno.visitado,
// o valor retorno.resultado será o valor que foi calculado, ou seja, não houve erro.
Valor_visitado calcular_valor_expressao(Vertice **tabela, char *celula)
{
    Endereco endereco = descobrir_celula(celula);
    Valor_visitado retorno;
    Valor_visitado retorno1;
    Valor_visitado retorno2;

    retorno.resultado = 0;
    retorno.visitado = 0;
    retorno1.resultado = 0;
    retorno2.resultado = 0;

    // Utilizado para casos que a expressão tem mais que duas células, para
    // não ocorrer erros na memória.
    if (tabela[endereco.linha][endereco.coluna].tam_expressao > 6){
        return retorno;
    }

    // Verifica se a célula foi visitada, para interpretar os ciclos.
    if (esta_visitado(tabela, endereco))
    {
        retorno.visitado = 1;
        return retorno;
    }

    tabela[endereco.linha][endereco.coluna].visitado = 1;

    // Para quando o valor [0] da string é diferente de =, o valor é uma constante.
    if (strcmp(tabela[endereco.linha][endereco.coluna].expressao[0], "=") != 0)
    {
        retorno.resultado = atoi(tabela[endereco.linha][endereco.coluna].expressao[0]);
        tabela[endereco.linha][endereco.coluna].visitado = 0;
        return retorno;
    }

    // Para caso o tamanho do vetor de strings seja 2, há caracteres do tipo ["=", "A5"]
    else if (tabela[endereco.linha][endereco.coluna].tam_expressao == 2)
    {
        // E deve-se verificar se esse valor foi visitado ou não.
        if (esta_visitado(tabela,
                          descobrir_celula(tabela[endereco.linha][endereco.coluna].expressao[1])))
        {
            retorno.visitado = 1;
            return retorno;
        }
        retorno = calcular_valor_expressao(tabela,
                                           tabela[endereco.linha][endereco.coluna].expressao[1]);
    }

    else if (tabela[endereco.linha][endereco.coluna].tam_expressao > 2)
    {
        // Verifica-se se os dois valores que serão operados são visitados ou não.
        if (esta_visitado(tabela,
                          descobrir_celula(tabela[endereco.linha][endereco.coluna].expressao[2])))
        {
            retorno.visitado = 1;
            return retorno;
        }
        else if (esta_visitado(tabela,
                               descobrir_celula(tabela[endereco.linha][endereco.coluna].expressao[4])))
        {
            retorno.visitado = 1;
            return retorno;
        }

        // Gera a busca dos valores de retorno1 e retorno2 para saber se houve ciclo ou não 
        // calculando seus valores quando não houve ciclo e somando eles na variável retorno.
        if (strcmp(tabela[endereco.linha][endereco.coluna].expressao[3], "+") == 0)
        {
            retorno1 = calcular_valor_expressao(tabela,
                                                tabela[endereco.linha][endereco.coluna].expressao[2]);
            retorno2 = calcular_valor_expressao(tabela,
                                                tabela[endereco.linha][endereco.coluna].expressao[4]);
            retorno.resultado = retorno1.resultado + retorno2.resultado;
        }
        // Gera a busca dos valores de retorno1 e retorno2 para saber se houve ciclo ou não 
        // calculando seus valores quando não houve ciclo e subtraindo eles na variável retorno.
        else if (strcmp(tabela[endereco.linha][endereco.coluna].expressao[3], "-") == 0)
        {
            retorno1 = calcular_valor_expressao(tabela,
                                                tabela[endereco.linha][endereco.coluna].expressao[2]);
            retorno2 = calcular_valor_expressao(tabela,
                                                tabela[endereco.linha][endereco.coluna].expressao[4]);
            retorno.resultado = retorno1.resultado - retorno2.resultado;
        }

        // Verifica se houve ciclo em alguma das variáveis retorno1 ou retorno2
        // para saber se deve-se modificar o valor de retorno.visitado para identificar-se
        // se ocorreu erro ou não.
        if (retorno1.visitado == 1 || retorno2.visitado == 1)
        {
            retorno.visitado = 1;
        }
    }

    tabela[endereco.linha][endereco.coluna].visitado = 0;
    return retorno;
}

// Dada uma matriz do tipo vértice, a quantidade de linhas e de colunas,
// libera toda a memória que foi alocada para essa matriz.
void liberar_tabela(Vertice **tabela, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            for (int k = 0; k < tabela[i][j].tam_expressao; k++)
            {
                free(tabela[i][j].expressao[k]);
            }
            free(tabela[i][j].expressao);
        }
        free(tabela[i]);
    }
    free(tabela);
}

