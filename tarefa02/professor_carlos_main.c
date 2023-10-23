#include <stdio.h>
#include "professor_carlos.h"

#define MAX_TURMAS 50
#define S 5

void ler_turmas(Turma t[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &t[i].qtd);
        for (j = 0; j < t[i].qtd; j++)
        {
            scanf("%s %s", t[i].alunos[j].nome, t[i].alunos[j].sobrenome);
            scanf("%d %d %d", &t[i].alunos[j].nascimento.dia, &t[i].alunos[j].nascimento.mes,
                  (&t[i].alunos[j].nascimento.ano));
        }
    }
}

void chamar_operacoes_e_printar_resultado(Turma t[], int n, int k)
{
    int i, operacao, j;
    int quantidade_alunos, contagem_substring;
    Aluno mais_novo, mais_velho;
    Aluno A;
    char substring[S];

    for (i = 0; i < k; i++)
    {
        scanf("%d", &operacao);
        if (operacao == 1)
        {
            scanf("%d", &j);
            mais_novo = procura_novo_na_turma(t, n, j);
            printf("%s\n", mais_novo.nome);
        }
        else if (operacao == 2)
        {
            scanf("%d", &j);
            mais_velho = procura_velho_na_turma(t, n, j);
            printf("%s\n", mais_velho.sobrenome);
        }
        else if (operacao == 3)
        {
            mais_velho = procura_velho_todas_turmas(t, n);
            printf("%s\n", mais_velho.nome);
        }
        else if (operacao == 4)
        {
            mais_novo = procura_novo_todas_turmas(t, n);
            printf("%s\n", mais_novo.sobrenome);
        }
        else if (operacao == 5)
        {
            scanf("%s", substring);
            contagem_substring = conta_substrings(t, n, substring);
            printf("%d\n", contagem_substring);
        }
        else if (operacao == 6)
        {
            scanf("%d", &j);
            scanf("%s %s %d %d %d", A.nome, A.sobrenome, &A.nascimento.dia, &A.nascimento.mes, &A.nascimento.ano);
            quantidade_alunos = add_aluno(t, A, j);
            printf("%d\n", quantidade_alunos);
        }
        else if (operacao == 7)
        {
            scanf("%d", &j);
            quantidade_alunos = remove_aluno(t, j);
            printf("%d\n", quantidade_alunos);
            t[j].qtd -= 1;
        }
    }
}

int main()
{
    int n, k;
    Turma t[MAX_TURMAS];
    scanf("%d %d", &n, &k);
    ler_turmas(t, n);
    chamar_operacoes_e_printar_resultado(t, n, k);

    return 0;
}