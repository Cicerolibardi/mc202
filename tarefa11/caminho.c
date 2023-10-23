#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "caminho.h"


// Adiciona um novo elemento na lista ligada.
No *adicionar_elemento(No *lista, double x, double y, char *tipo_local)
{
    No *novo;
    novo = malloc(sizeof(No));
    if (novo == NULL)
        exit(1);

    novo->x = x;
    novo->y = y;
    strcpy(novo->tipo_local, tipo_local);
    novo->prox = lista;
    return novo;
}

// Cria uma nova lista ligada apontando para NULL.
No *criar_lista()
{
    return NULL;
}

//Calcula a distância euclidiana entre dois pontos, dados as posições x e y de cada ponto.
double dist_euclidiana(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// Cria um grafo na forma de matriz n x n, setando todas as posições iniciais para 0.
Grafo *criar_grafo(int n)
{
    int i, j;
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->n = n;
    grafo->adj = malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
        grafo->adj[i] = malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            grafo->adj[i][j] = 0;
    return grafo;
}

// Inicializa as distâncias entre todos os vertices, pois todos estão interligados.
// Seta como o piso da distância como uma adaptação para corresponder à busca correta
// na função descobrir_menor_caminho.
Grafo *inicializar_distancias(No **vetor_distancias, Grafo *grafo)
{
    for (int i = 0; i < grafo->n; i++)
    {
        for (int j = 0; j < grafo->n; j++)
        {
            // Guardará no grafo o piso da distância, ou seja, o arredondamento pra baixo da distância.
            // Na busca, quando encontrar alguma vez, deverá ser somado 1 no valor para que ache a
            // distância mínima correta.
            grafo->adj[i][j] = floor(dist_euclidiana(vetor_distancias[i]->x, vetor_distancias[i]->y,
                                                     vetor_distancias[j]->x, vetor_distancias[j]->y));
        }
    }
    return grafo;
}

// A partir da lista ligada recebida na entrada, transforma tal lista para um vetor
// com os nós na mesma sequência que foi recebido na entrada.
No **transformar_lista_vetor(No *lista, int qtd_elementos)
{
    No **vetor_entrada = malloc(qtd_elementos * sizeof(No *));
    No *aux;
    int i = 0;

    for (aux = lista; aux != NULL; aux = aux->prox)
    {
        vetor_entrada[i] = aux;
        i++;
    }
    return vetor_entrada;
}

// Busca recursivamente pela função existe caminho para ver se existe um caminho, isso dado pelas
// condições de que a parada seja quando acha-se o Lugia. Deve-se verificar, diferentemente da função
// original, se o encontro entre os dois vértices tem uma distância entre eles menor do que a distância
// máxima encontrada até o momento entre dois vértices.
int busca_rec(Grafo *grafo, int *visitado, int v, double dist_max_atual, No **vetor_caminhos)
{
    int w;
    if (strcmp(vetor_caminhos[v]->tipo_local, "Lugia") == 0)
        return 1; /*sempre existe caminho de t para t*/
    visitado[v] = 1;
    for (w = 0; w < grafo->n; w++)
        if ((grafo->adj[v][w] < dist_max_atual) && !visitado[w])
            if (busca_rec(grafo, visitado, w, dist_max_atual, vetor_caminhos))
                return 1;
    return 0;
}

// Gera um vetor chamado visitado para saber se o tal vértice já foi visitado e chama-se
// a função busca_rec para descobrir se existe um caminho com as especificidades dadas na função
// busca_rec.
int existe_caminho(Grafo *grafo, int s, double dist_max_atual, No **vetor_caminhos)
{
    int encontrou, i, *visitado = malloc(grafo->n * sizeof(int));
    for (i = 0; i < grafo->n; i++)
        visitado[i] = 0;
    encontrou = busca_rec(grafo, visitado, s, dist_max_atual, vetor_caminhos);
    free(visitado);
    return encontrou;
}

// Descobre o caminho entre dois pokestops que tenha final em um lugia com a menor distância entre
// dois vértices e printa essa distância.
void descobrir_menor_caminho(Grafo *grafo, int pos_inicial, double dist_max_atual, No **vetor_caminhos)
{
    //int resultado;
    int encontrou = 1;
    double dist_max_parcial = dist_max_atual - 1;
    int executou = 0;

    while (encontrou)
    {
        encontrou = existe_caminho(grafo, pos_inicial, dist_max_parcial, vetor_caminhos);
        if (encontrou)
        {
            executou = 1;
            dist_max_parcial -= 2;
            dist_max_atual -= 2;
        }
    }

    if (existe_caminho(grafo, pos_inicial, dist_max_parcial + 1, vetor_caminhos) && executou == 1)
    {
        dist_max_parcial += 1;
    }
    else
    {
        dist_max_parcial += 2;
    }

    if (executou == 0)
        // se não houve execução, ou seja, não achou caminho com distância menor.
        dist_max_atual = ceil(dist_max_atual);
    else
        // houve execução, então deve-se adicionar um na distância parcial pois a ultima execução
        // não achou nenhum caminho.
        dist_max_atual = ceil(dist_max_parcial);

    printf("%.0f\n", dist_max_atual);
}

// Destroi uma lista ligada dado o ponteiro para o inicio dessa lista.
void destruir_lista(No *lista)
{
    No *aux;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

// A partir do ponteiro para o grafo, destroi o grafo apontado por esse ponteiro.
// Esse grafo tem que ser da forma matricial para poder ser utilizada tal função.
void destruir_grafo(Grafo *grafo)
{
    int i;
    for (i = 0; i < grafo->n; i++)
        free(grafo->adj[i]);
    free(grafo->adj);
    free(grafo);
}