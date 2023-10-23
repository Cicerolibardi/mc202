#include <stdio.h>

#define MAX_LINHA_SIZE 101
#define MAX_COLUNA_SIZE 101
#define MAX_NUM_PALAVRAS 10
#define MAX_PALAVRA_SIZE 21

void ler_matrizes(char matriz[][MAX_COLUNA_SIZE], char vetor_palavras[][MAX_PALAVRA_SIZE], int n, int q)
{
    int i;

    for (i = 0; i < n; i++)
    {
        scanf(" %s", matriz[i]);
    }

    for (i = 0; i < q; i++)
    {
        scanf(" %s", vetor_palavras[i]);
    }
}

int verificar_vizinho(char matriz[][MAX_COLUNA_SIZE], char palavra[], int n, int m, int idx_palavra,
                      int i, int j)
{
    int existe1, existe2, existe3, existe4;
    char aux;

    if (palavra[idx_palavra] == '\0'){
        return 1;
    }
    else if ((i >= n) || (j >= m) || (i < 0) || (j < 0) || (palavra[idx_palavra] != matriz[i][j])){
        return 0;
    }
    else{
        aux = matriz[i][j];
        matriz[i][j] = '0';
        existe1 = verificar_vizinho(matriz, palavra, n, m, idx_palavra + 1, i - 1, j);
        if (existe1){
            matriz[i][j] = aux; 
            return 1;
        }
        existe2 = verificar_vizinho(matriz, palavra, n, m, idx_palavra + 1, i + 1, j);
        if (existe2){
            matriz[i][j] = aux; 
            return 1;
        }
        existe3 = verificar_vizinho(matriz, palavra, n, m, idx_palavra + 1, i, j + 1);
        if (existe3){
            matriz[i][j] = aux; 
            return 1;
        }
        existe4 = verificar_vizinho(matriz, palavra, n, m, idx_palavra + 1, i, j - 1);
        if (existe4){
            matriz[i][j] = aux; 
            return 1;
        }
        matriz[i][j] = aux;
    }
    return 0;
}

int palavra_esta_presente(char matriz[][MAX_COLUNA_SIZE], char palavra[], int n,
                          int m, int idx_palavra)
{
    int i, j, existe = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (palavra[idx_palavra] == matriz[i][j])
            {
                existe = verificar_vizinho(matriz, palavra, n, m, idx_palavra, i, j);
                if (existe == 1)
                    return existe;
            }
        }
    }
    return existe;
}

int main()
{
    int n, m, q, existe;
    char matriz[MAX_COLUNA_SIZE][MAX_COLUNA_SIZE];
    char vetor_palavras[MAX_NUM_PALAVRAS][MAX_PALAVRA_SIZE];

    scanf("%d %d %d", &n, &m, &q);
    ler_matrizes(matriz, vetor_palavras, n, q);

    for (int i = 0; i < q; i++)
    {
        existe = palavra_esta_presente(matriz, vetor_palavras[i], n, m, 0);
        if (existe)
            printf("sim\n");
        else
            printf("nao\n");
    }
}