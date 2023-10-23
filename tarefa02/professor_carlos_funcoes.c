#include <stdio.h>
#include "professor_carlos.h"

int desempatar_por_nome(int i_aluno1, int i_aluno2, Turma t[], int j)
{
    int i;

    for (i = 0; t[j].alunos[i_aluno1].nome[i] != '\0'; i++)
    {
        if ((t[j].alunos[i_aluno2].nome[i] != '\0') && (t[j].alunos[i_aluno1].nome[i] != '\0'))
        {
            if (t[j].alunos[i_aluno1].nome[i] < t[j].alunos[i_aluno2].nome[i])
            {
                return i_aluno1;
            }
            else if (t[j].alunos[i_aluno1].nome[i] > t[j].alunos[i_aluno2].nome[i])
            {
                return i_aluno2;
            }
        }
        else if ((t[j].alunos[i_aluno2].nome[i] == '\0') && (t[j].alunos[i_aluno1].nome[i] != '\0'))
        {
            return i_aluno2;
        }
    }

    if (t[j].alunos[i_aluno1].nome[i] == '\0' && t[j].alunos[i_aluno2].nome[i] != '\0')
    {
        return i_aluno1;
    }

    for (i = 0; t[j].alunos[i_aluno1].sobrenome[i] != '\0'; i++)
    {
        if ((t[j].alunos[i_aluno2].sobrenome[i] != '\0') && (t[j].alunos[i_aluno1].sobrenome[i] != '\0'))
        {
            if (t[j].alunos[i_aluno1].sobrenome[i] < t[j].alunos[i_aluno2].sobrenome[i])
            {
                return i_aluno1;
            }
            else if (t[j].alunos[i_aluno1].sobrenome[i] > t[j].alunos[i_aluno2].sobrenome[i])
            {
                return i_aluno2;
            }
        }
        else if ((t[j].alunos[i_aluno2].sobrenome[i] != '\0') && (t[j].alunos[i_aluno1].sobrenome[i] == '\0'))
        {
            return i_aluno2;
        }
        else if ((t[j].alunos[i_aluno2].sobrenome[i] == '\0') && (t[j].alunos[i_aluno1].sobrenome[i] != '\0'))
        {
            return i_aluno1;
        }
    }
    return i_aluno1;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j)
{
    int i;
    int indice_mais_novo = 0;
    Data mais_novo;

    mais_novo.dia = 0;
    mais_novo.mes = 0;
    mais_novo.ano = 0;
    for (i = 0; i < t[j].qtd; i++)
    {
        if (t[j].alunos[i].nascimento.ano > mais_novo.ano)
        {
            mais_novo.ano = t[j].alunos[i].nascimento.ano;
            mais_novo.mes = t[j].alunos[i].nascimento.mes;
            mais_novo.dia = t[j].alunos[i].nascimento.dia;
            indice_mais_novo = i;
        }
        else if (t[j].alunos[i].nascimento.ano == mais_novo.ano)
        {
            if (t[j].alunos[i].nascimento.mes > mais_novo.mes)
            {
                mais_novo.mes = t[j].alunos[i].nascimento.mes;
                mais_novo.dia = t[j].alunos[i].nascimento.dia;
                indice_mais_novo = i;
            }
            else if (t[j].alunos[i].nascimento.mes == mais_novo.mes)
            {
                if (t[j].alunos[i].nascimento.dia > mais_novo.dia)
                {
                    mais_novo.dia = t[j].alunos[i].nascimento.dia;
                    indice_mais_novo = i;
                }
                else if (t[j].alunos[i].nascimento.dia == mais_novo.dia)
                {
                    indice_mais_novo = desempatar_por_nome(indice_mais_novo, i, t, j);
                }
            }
        }
    }

    return t[j].alunos[indice_mais_novo];
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j)
{
    int i;
    int indice_mais_velho = 0;
    Data mais_velho;

    mais_velho.dia = t[j].alunos[0].nascimento.dia;
    mais_velho.mes = t[j].alunos[0].nascimento.mes;
    mais_velho.ano = t[j].alunos[0].nascimento.ano;
    for (i = 1; i < t[j].qtd; i++)
    {
        if (t[j].alunos[i].nascimento.ano < mais_velho.ano)
        {
            mais_velho.ano = t[j].alunos[i].nascimento.ano;
            mais_velho.mes = t[j].alunos[i].nascimento.mes;
            mais_velho.dia = t[j].alunos[i].nascimento.dia;
            indice_mais_velho = i;
        }
        else if (t[j].alunos[i].nascimento.ano == mais_velho.ano)
        {
            if (t[j].alunos[i].nascimento.mes < mais_velho.mes)
            {
                mais_velho.mes = t[j].alunos[i].nascimento.mes;
                mais_velho.dia = t[j].alunos[i].nascimento.dia;
                indice_mais_velho = i;
            }
            else if (t[j].alunos[i].nascimento.mes == mais_velho.mes)
            {
                if (t[j].alunos[i].nascimento.dia < mais_velho.dia)
                {
                    mais_velho.dia = t[j].alunos[i].nascimento.dia;
                    indice_mais_velho = i;
                }
                else if (t[j].alunos[i].nascimento.dia == mais_velho.dia)
                {
                    indice_mais_velho = desempatar_por_nome(indice_mais_velho, i, t, j);
                }
            }
        }
    }

    return t[j].alunos[indice_mais_velho];
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas)
{
    int i;
    Turma novos_todas_turmas[1];
    Aluno mais_novo, mais_novo_turma;

    for (i = 0; i < qtd_turmas; i++)
    {
        mais_novo_turma = procura_novo_na_turma(t, qtd_turmas, i);
        novos_todas_turmas[0].alunos[i] = mais_novo_turma;
    }

    novos_todas_turmas[0].qtd = qtd_turmas;
    mais_novo = procura_novo_na_turma(novos_todas_turmas, 0, 0);

    return mais_novo;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas)
{
    int i;
    Turma velhos_todas_turmas[1];
    Aluno mais_velho, mais_velho_turma;

    for (i = 0; i < qtd_turmas; i++)
    {
        mais_velho_turma = procura_velho_na_turma(t, qtd_turmas, i);
        velhos_todas_turmas[0].alunos[i] = mais_velho_turma;
    }

    velhos_todas_turmas[0].qtd = qtd_turmas;
    mais_velho = procura_velho_na_turma(velhos_todas_turmas, 0, 0);

    return mais_velho;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao)
{
    int i, j, k, l;
    int contador = 0;
    int tamanho_padrao = 0;
    int repeticoes = 0;

    for (i = 0; padrao[i] != '\0'; i++)
    {
        tamanho_padrao += 1;
    }

    for (i = 0; i < qtd_turmas; i++)
    {
        for (j = 0; j < t[i].qtd; j++)
        {
            for (k = 0; t[i].alunos[j].nome[k] != '\0'; k++)
            {
                if (t[i].alunos[j].nome[k] == padrao[0])
                {
                    for (l = 0; padrao[l] != '\0'; l++)
                    {
                        if (t[i].alunos[j].nome[k + l] == padrao[l])
                        {
                            contador += 1;
                        }
                    }
                }
                if (tamanho_padrao == contador)
                {
                    repeticoes += 1;
                    break;
                }
            contador = 0;
            }
        contador = 0;
        }
    }
    return repeticoes;
}

int add_aluno(Turma t[], Aluno A, int j)
{
    t[j].alunos[t[j].qtd] = A;
    t[j].qtd += 1;
    return t[j].qtd;
}

int remove_aluno(Turma t[], int j)
{
    return (t[j].qtd - 1);
}
