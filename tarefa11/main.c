#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "caminho.h"

int main()
{
    No *lista;
    double x_ini, y_ini, x, y;
    double dist_max_inicial;
    char tipo_local[9];
    int qtd_elementos = 0;
    int pos_inicial = 0;
    No **vetor_entrada;

    lista = criar_lista();
    scanf("%lf %lf", &x_ini, &y_ini);

    while (scanf("%lf %lf %s", &x, &y, tipo_local) != EOF)
    {
        lista = adicionar_elemento(lista, x, y, tipo_local);
        qtd_elementos += 1;
        if ((x_ini == x) && (y_ini == y))
        {
            pos_inicial = qtd_elementos; // descobre-se qual a posição de inserção da posição inicial.
        }
        if (strcmp(tipo_local, "Lugia") == 0)
        {
            // Como o local que foi lido é uma Lugia, seta-se a distância máxima inicial como
            // a distância da origem até o Lugia.
            dist_max_inicial = dist_euclidiana(x_ini, y_ini, x, y);
        }
    }

    // Converte-se a posição inicial da entrada para a quantidade de elementos - a posição
    // inicial, pois a lista ligada é gerada no inverso de como a entrada é recebida.
    pos_inicial = qtd_elementos - pos_inicial;

    // Gera-se um vetor a partir da lista da entrada para que quando desejar-se buscar na função
    // busca_rec se um dado vértice é um Lugia a busca possa ser dada por O(1).
    vetor_entrada = transformar_lista_vetor(lista, qtd_elementos);

    Grafo *grafo = criar_grafo(qtd_elementos);

    grafo = inicializar_distancias(vetor_entrada, grafo);

    descobrir_menor_caminho(grafo, pos_inicial, dist_max_inicial, vetor_entrada);

    free(vetor_entrada);
    destruir_lista(lista);
    destruir_grafo(grafo);
    return 0;
}