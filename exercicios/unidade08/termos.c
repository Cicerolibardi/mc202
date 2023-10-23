#include <stdio.h>

#define MAX 100

int somar(int vetor[], int n)
{
    int soma = 0;
    for (int i = 0; i < n; i++)
    {
        soma += vetor[i];
    }
    return soma;
}


void imprimir_vetor(int vetor[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void imprimir_sequencias(int vetor[], int m, int soma, int n, int C)
{
    // se o vetor já está todo fixado
    if (n == m)
    {
        if (soma == C)
        {
            imprimir_vetor(vetor, n);
        }
        return;
    }

    //se o vetor está fixado até a posição m - 1

    for (int i = 0; i <= C - soma; i++)
    {
        vetor[m] = i;
        imprimir_sequencias(vetor, m + 1, soma + i, n, C);
    }
}

int main()
{
    int n, C;
    int vetor[MAX];

    printf("Escreva n: ");
    scanf("%d", &n);
    printf("Escreva C: ");
    scanf("%d", &C);

    imprimir_sequencias(vetor, 0, 0, n, C);
}