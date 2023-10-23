#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas_legais.h"

int main()
{
    int n, k;
    long int dado;
    No_arvore *raiz = NULL;

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%ld", &dado);
        raiz = inserir(raiz, dado);
    }
    for (int i = 0; i < k; i++)
    {
        raiz = identificar_operacao_e_operar(raiz);
    }
    deletar_arvore(raiz);
    return 0;
}