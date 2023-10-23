#define TAM_MAX_ARQUIVO 20
#define TAM_MAX_EXPRESSAO 5
#define MAX_EXPRESSAO_ENTRADA 40

typedef struct Vertice
{
    int visitado;
    char **expressao;
    int tam_expressao;
} Vertice;

typedef struct Endereco
{
    int linha;
    int coluna;
} Endereco;

typedef struct Valor_visitado
{
    int resultado;
    int visitado;
} Valor_visitado;

// Lê uma entrada com o arquivo csv, delimintando os caracteres chaves por ',' ou '\n'
// para que leia somente até esses caracteres e insira no local correto da matriz.
Vertice **ler_tabela(char *local_arquivo, int colunas, int linhas);

// Dado uma expressão do tipo "G13", retorna qual o endereço (linha e coluna)
// dessa célula na matriz.
Vertice **atualizar_celula(Vertice **tabela, char *nova_expressao, Endereco endereco);

// Atualiza uma célula na tabela com a nova expressão do endereço dado.
Endereco descobrir_celula(char *expressao);

// Verifica se tal vértice já foi visitado, utilizado para saber se houve
// ciclo ou não.
int esta_visitado(Vertice **tabela, Endereco endereco);

// Calcula o valor de uma célula, sendo essas expressões ou números inteiros.
// Retorna um valor do tipo Valor_visitado, que se retorno.visitado for 1, quer 
// dizer que houve um ciclo, ou seja, há um erro. Caso seja 0, o retorno.visitado,
// o valor retorno.resultado será o valor que foi calculado, ou seja, não houve erro.
Valor_visitado calcular_valor_expressao(Vertice **tabela, char *celula);

// Dada uma matriz do tipo vértice, a quantidade de linhas e de colunas,
// libera toda a memória que foi alocada para essa matriz.
void liberar_tabela(Vertice **tabela, int linhas, int colunas);
