#ifndef LISTAS_LEGAIS
#define LISTAS_LEGAIS

enum Cor
{
    VERMELHO,
    PRETO
};

typedef struct No_arvore
{
    long int dado;
    int qtd_dado;
    enum Cor cor;
    struct No_arvore *esq;
    struct No_arvore *dir;

} No_arvore;

// Modifica a cor do pai para vermelho e a cor dos dois filhos para preto.
void sobe_vermelho(No_arvore *raiz);

// Verifica se um nó é vermelho.
int ehVermelho(No_arvore *x);

// Verifica se um nó é preto.
int ehPreto(No_arvore *x);

// Faz a rotação da árvore para a esquerda para quando necessita-se balanceamento.
No_arvore *rotaciona_para_esquerda(No_arvore *raiz);

// Faz a rotação da árvore para a direita para quando necessita-se balanceamento.
No_arvore *rotaciona_para_direita(No_arvore *raiz);

// Insere recursivamente em uma árvore um novo nó (função chamada pela função inserir)
No_arvore *inserir_rec(No_arvore *raiz, long int dado);

// A partir de inserir_rec, insere um novo dado na raíz, balanceando a cor da raiz posteriormente
No_arvore *inserir(No_arvore *raiz, long int dado);

// Busca um nó em uma árvore com o dado correspondente e retorna esse nó.
No_arvore *buscar_arvore(No_arvore *raiz, long int dado);

// Busca o antecessor de um nó em uma árvore e retorna esse nó
No_arvore *buscar_antecessor(No_arvore *raiz, No_arvore *atual);

// Busca o nó com valor máximo na árvore e retorna esse nó.
No_arvore *maximo_arvore(No_arvore *raiz);

// Descobre a quantidade de nós que necessita-se de retirar para uma árvore ficar legal,
// printando na tela essa quantidade. O return é a raíz da árvore
No_arvore *qtd_retirar_tornar_legal(No_arvore *raiz);

// Verifica se a operação é 1, 2 ou 3 e printa na tela para cada caso. O return value é a raíz
// da árvore.
No_arvore *identificar_operacao_e_operar(No_arvore *raiz);

// A partir da raíz de uma árvore, libera toda a memória alocada para esta.
void deletar_arvore(No_arvore *raiz);

#endif
