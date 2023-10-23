#ifndef DIADEUBER
#define DIADEUBER

#define PAI(i) ((i - 1) / 2) /*Pai de i*/
#define F_ESQ(i) (2 * i + 1) /*Filho esquerdo de i*/
#define F_DIR(i) (2 * i + 2) /*Filho direito de i*/

typedef struct Posicao
{
    int x_saida, x_chegada, y_saida, y_chegada;
} Posicao;

typedef struct Item
{
    char nome[16];
    double avaliacao;
    int esta_vazio;
    Posicao posicao;
} Item;

typedef struct Fila_prio
{
    Item *v;
    int n, tamanho;
} Fila_prio;

// Cria uma fila de priodade com o tamanho dado e retorna o ponteiro para essa fila.
Fila_prio *criar_filaprio(int tam);

// Função recursiva para consertar o vetor e fazer ele corresponder à um max_heap.
void sobe_no_heap(Fila_prio *fprio, int k);

// Função recursiva para consertar o vetor e fazer ele corresponder à um max_heap.
void desce_no_heap(Fila_prio *fprio, int k);

// Insere o item na fila de prioridade e "balanceia" essa fila de prioridade.
void insere(Fila_prio *fprio, Item item);

// Extrai o máximo na fila de prioridade e "balanceia" essa fila de prioridade.
Item extrai_maximo(Fila_prio *fprio);

// Calcula os valores das despesas, rendimento liquido e bruto e printa esses valores.
void calcular_printar_valor_final(int distancia_total, int distancia_parcial, int qtd_cancelamentos);

// Lê a entrada e realiza as operações dos tipos A, C, F e T.
void ler_entrada_realizar_operacoes(Fila_prio *fprioridade);

// Libera uma fila de prioridade e o vetor dentro dela.
void libera_fila_prio(Fila_prio *fprioridade);

#endif