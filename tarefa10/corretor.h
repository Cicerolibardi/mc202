#ifndef CORRETOR
#define CORRETOR

#define MAX 677

typedef struct No
{
    char *palavra;
    struct No *prox;
} No;

typedef No *p_no;

typedef struct Hash
{
    p_no *vetor;
} Hash;

typedef Hash *p_hash;

// Gera o hash de uma palavra pelo método da divisão.
int hash(char *palavra);

// Insere um novo nó em uma lista, tendo como parâmetro principal a palavra.
p_no inserir_lista(p_no lista, char *palavra);
// Insere um novo nó na posição "n" do hash.

void inserir_hash(p_hash t, char *palavra);
// Cria uma tabela hash com todas as posições nulas de início e retorna
// essa hash.

p_hash criar_hash();
// Dado o ponteiro pra lista, libera a memória de todos os nós dessa lista.

void destruir_lista(p_no lista);
// Gera todas as permutações das palavras corretas para palavras com 1 erro e coloca na
// hash "tabela_amarelos"

void gerar_permutacoes_palavras(p_hash tabela_amarelos, char *palavra);
// Busca nas tabelas verdes e amarelos a palavra digitada no teclado.
// Caso esteja na verde, printará verde e não buscará mais. Caso não esteja na verde
// busca-se na tabela amarela, e, caso esteja nela, printará amarelo e parará a busca.
// Caso não esteja em nenhuma das duas tabelas, printará vermelho.

void buscar_tabelas_e_printar(p_hash tabela_verdes, p_hash tabela_amarelos, char *palavra);

#endif