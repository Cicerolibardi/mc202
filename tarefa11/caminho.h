#ifndef CAMINHO_H
#define CAMINHO_H

typedef struct No
{
    double x, y;
    char tipo_local[9];
    struct No *prox;
} No;

typedef struct Grafo
{
    double **adj;
    int n;
} Grafo;

// Adiciona um novo elemento na lista ligada.
No *adicionar_elemento(No *lista, double x, double y, char *tipo_local);

// Cria uma nova lista ligada apontando para NULL.
No *criar_lista();

//Calcula a distância euclidiana entre dois pontos, dados as posições x e y de cada ponto.
double dist_euclidiana(double x1, double y1, double x2, double y2);

// Cria um grafo na forma de matriz n x n, setando todas as posições iniciais para 0.
Grafo *criar_grafo(int n);

// Inicializa as distâncias entre todos os vertices, pois todos estão interligados.
// Seta como o piso da distância como uma adaptação para corresponder à busca correta
// na função descobrir_menor_caminho.
Grafo *inicializar_distancias(No **vetor_distancias, Grafo *grafo);

// A partir da lista ligada recebida na entrada, transforma tal lista para um vetor
// com os nós na mesma sequência que foi recebido na entrada.
No **transformar_lista_vetor(No *lista, int qtd_elementos);

// Busca recursivamente pela função existe caminho para ver se existe um caminho, isso dado pelas
// condições de que a parada seja quando acha-se o Lugia. Deve-se verificar, diferentemente da função
// original, se o encontro entre os dois vértices tem uma distância entre eles menor do que a distância
// máxima encontrada até o momento entre dois vértices.
int busca_rec(Grafo *grafo, int *visitado, int v, double dist_max_atual, No **vetor_caminhos);

// Gera um vetor chamado visitado para saber se o tal vértice já foi visitado e chama-se
// a função busca_rec para descobrir se existe um caminho com as especificidades dadas na função
// busca_rec.
int existe_caminho(Grafo *grafo, int s, double dist_max_atual, No **vetor_caminhos);

// Descobre o caminho entre dois pokestops que tenha final em um lugia com a menor distância entre
// dois vértices e printa essa distância.
void descobrir_menor_caminho(Grafo *grafo, int pos_inicial, double dist_max_atual, No **vetor_caminhos);

// Destroi uma lista ligada dado o ponteiro para o inicio dessa lista.
void destruir_lista(No *lista);

// A partir do ponteiro para o grafo, destroi o grafo apontado por esse ponteiro.
// Esse grafo tem que ser da forma matricial para poder ser utilizada tal função.
void destruir_grafo(Grafo *grafo);

#endif