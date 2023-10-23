#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mensageiro.h"

int main()
{
    No_arvore *raiz;
    int m, n;
    long int dado;
    long int autoridade;
    char texto_verso[6];

    raiz = NULL;

    while (scanf("%d %d", &m, &n) != EOF)
    {
        for (int i = 0; i < m; i++)
        {
            scanf("%ld \"%[^\"]\"", &dado, texto_verso);
            raiz = inserir_arvore(raiz, dado, texto_verso);
        }

        for (int i = 0; i < n; i++)
        {
            scanf("%ld", &autoridade);
            raiz = buscar_triade(raiz, autoridade);
        }
        printar_inordem(raiz);
        destruir_arvore(raiz);
        printf("\n");
        raiz = NULL;
    }
}