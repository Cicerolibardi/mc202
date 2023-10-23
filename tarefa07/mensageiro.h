#ifndef MENSAGEIRO_H
#define MENSAGEIRO_H

typedef struct No_arvore
{
    long int dado;
    char *texto_verso;
    struct No_arvore *esq;
    struct No_arvore *dir;
} No_arvore;

typedef struct Triade
{
    No_arvore *a;
    No_arvore *b;
    No_arvore *c;
} Triade;

//Dados o ponteiro para raíz da árvore, o dado e o verso, insere-se um novo nó na árvore
//com esses parâmetros, retornando a raíz para a função.
No_arvore *inserir_arvore(No_arvore *raiz, long int dado, char *texto_verso);

// Modifica os valores que são recebidos por raíz para os valores do sucessor,
// removendo o nó do sucessor e atualizando a árvore, ou seja, nao há a remoção
// do nó raiz, e sim a substituição dos seus dados pelos dados do nó do sucessor
// e assim o nó denotado por raíz é automaticamente excluido.
void remover_sucessor(No_arvore *raiz);

// Retorna a raíz da árvore após remover o dado, caso ele exista.
// Para casos simples, ou seja, sem duas subárvores, a remoção é feita na própria função.
// Para caso hajam duas subárvores, é chamada a função remover_sucessor().
No_arvore *remover_rec(No_arvore *raiz, long int dado);

// Dado o nó da raíz da árvore e o nó que deseja-se procurar o antecessor,
// busca-se o nó do antecessor, caso ele exista e retorna esse nó. Caso não exista,
// o retorno é NULL.
No_arvore *buscar_antecessor(No_arvore *raiz, No_arvore *atual);

// Acha o máximo de uma árvore e retorna o nó desse máximo.
No_arvore *maximo_arvore(No_arvore *raiz);

// Faz a busca de um nó, dados o ponteiro para a raíz da árvore e um inteiro que equivale ao dado
// a ser buscado. Caso ele exista, é retornado o nó desse valor. Caso não exista, o retorno é NULL.
No_arvore *buscar_valor(No_arvore *raiz, int dado);

// Busca 3 nós, cujo a soma dos dados desses 3 nós seja igual a autoridade.
// Dentro dessa função, quando acha-se os 3 nós, concatena-se suas strings conforme
// a ordem crescente dos dados, são removidos os 3 nós da árvore, é inserido um novo nó
// com a string concatenada e o dado novo, que no caso é o da autoridade, e retorna-se
// o ponteiro para a raíz dessa árvore.
No_arvore *buscar_triade(No_arvore *raiz, long int autoridade);

// Printa na tela a árvore binária, nesse caso, as strings, conforme o método de escrita inordem
// de uma árvore binária.
void printar_inordem(No_arvore *raiz);

// Dado o ponteiro para a raíz da árvore, é desalocada toda a memória que está sendo
// utilizada nessa árvore.
void destruir_arvore(No_arvore *raiz);

#endif