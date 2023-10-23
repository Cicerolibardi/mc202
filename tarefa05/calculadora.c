#include <stdio.h>
#include <stdlib.h>

typedef struct No *p_no;

// define uma lista duplamente ligada
typedef struct No
{
    int valor;
    p_no esquerda;
    p_no direita;

} No;

// define um número natural que tem ponteiros pro inicio e fim da lista
// ligada e o número de elementos nela.
typedef struct Natural
{
    p_no mais_esq, mais_dir;
    int qtd;

} Natural;

//Cria um número natural com 0 elementos e seus ponteiros de início e fim apontam para NULL.
Natural criar_natural()
{
    Natural numero;
    numero.qtd = 0;
    numero.mais_esq = NULL;
    numero.mais_dir = NULL;
    return numero;
}

//insere um nó à esquerda da lista ligada
void inserir_esquerda(Natural *lista, int x)
{
    p_no novo;
    novo = calloc(sizeof(No), 1);
    if (novo == NULL)
    {
        exit(1);
    }
    novo->valor = x;
    novo->esquerda = NULL;
    novo->direita = lista->mais_esq;
    if (lista->mais_esq)
    {
        lista->mais_esq->esquerda = novo;
    }
    else
    { //faz com que os ponteiros mais_esq e mais_dir de lista
        //apontem para o mesmo nó, pois a lista estava vazia.
        lista->mais_dir = novo;
    }
    lista->mais_esq = novo;
    lista->qtd += 1;
}

//insere um nó à direita da lista ligada
void inserir_direita(Natural *lista, int x)
{
    p_no novo;
    novo = calloc(sizeof(No), 1);
    if (novo == NULL)
    {
        exit(1);
    }
    novo->valor = x;
    novo->direita = NULL;
    novo->esquerda = lista->mais_dir;
    if (lista->mais_dir)
    {
        lista->mais_dir->direita = novo;
    }
    else
    { //faz com que os ponteiros mais_esq e mais_dir de lista
        //apontem para o mesmo nó, pois a lista estava vazia.
        lista->mais_esq = novo;
    }
    lista->mais_dir = novo;
    lista->qtd += 1;
}

//Lê um número natural ignorando possíveis inconsistências na entrada.
Natural ler_natural()
{
    Natural numero = criar_natural();

    char c;
    do
    {
        scanf("%c", &c);
    } while (c < '0' || c > '9'); //lê todos os caracteres inválidos até que ache um que seja válido, um número.

    while (c >= '0' && c <= '9') //lê todos os números até que ache-se um caractere inválido, espaço ' ' ou '\n',
                                 //dada a entrada da forma como foi definida.
    {
        inserir_direita(&numero, c - '0');
        scanf("%c", &c);
    }
    return numero;
}

/*Recebe dois números naturais "lista1" e "lista2" e soma ambos, devolvendo um novo número natural
 * que representa a soma dos dois números da entrada.
 */ 
Natural somar_naturais(Natural lista1, Natural lista2)
{
    Natural soma;
    int aux = 0;

    soma = criar_natural();
    p_no p_lista1 = lista1.mais_dir;
    p_no p_lista2 = lista2.mais_dir;

    while (p_lista1 != NULL || p_lista2 != NULL)
    {
        if (p_lista1 != NULL) //descobre se o numero 1 já chegou ao fim, para não se acessar memória inválida
        {                     //dentro do if, nem somar "lixo".
            aux = aux + p_lista1->valor;
            p_lista1 = p_lista1->esquerda;
        }
        if (p_lista2 != NULL) //descobre se o numero 2 já chegou ao fim, para não se acessar memória inválida
        {                     //dentro do if, nem somar "lixo".

            aux = aux + p_lista2->valor;
            p_lista2 = p_lista2->esquerda;
        }
        inserir_esquerda(&soma, aux % 10);
        aux = aux / 10;
    }
    if (aux > 0)
    {
        inserir_esquerda(&soma, aux);
    }
    return soma;
}

//devolve 1 se o num1 > num2, 0 se num1 == num2 e -1 se num1 < num2.
int descobrir_maior(Natural lista1, Natural lista2)
{
    p_no p_lista1, p_lista2;
    p_lista1 = lista1.mais_esq;
    p_lista2 = lista2.mais_esq;

    while (p_lista1 != NULL && p_lista2 != NULL)
    {
        if (p_lista1->valor > p_lista2->valor)
        {
            return 1;
        }
        else if (p_lista1->valor < p_lista2->valor)
        {
            return -1;
        }
        else if (p_lista1->valor == p_lista2->valor)
        {
            p_lista1 = p_lista1->direita;
            p_lista2 = p_lista2->direita;
        }
    }
    return 0;
}

/* Recebe dois números naturais "lista1" e "lista2", subtrai-se o maior do menor e devolve um novo número
 * número que é a subtração do primeiro pelo segundo.
 */
Natural subtrair_naturais(Natural lista1, Natural lista2)
{
    Natural subtracao;
    int maior, aux = 0;

    subtracao = criar_natural();
    p_no p_lista1 = lista1.mais_dir;
    p_no p_lista2 = lista2.mais_dir;

    if (lista2.qtd > lista1.qtd)
    { // inverte a lógica de qual número é maior, para facilitar a implementação
        // da subtração
        p_lista1 = lista2.mais_dir;
        p_lista2 = lista1.mais_dir;
    }
    else if (lista1.qtd == lista2.qtd)
    {
        maior = descobrir_maior(lista1, lista2); //descobre o maior e coloca ele como p_lista1 para facilitar o
                                                 //algoritmo de subtração
        if (maior == -1)
        {
            p_lista1 = lista2.mais_dir;
            p_lista2 = lista1.mais_dir;
        }
    }

    while (p_lista1 != NULL || p_lista2 != NULL)
    {
        if (p_lista2 != NULL)
        {
            if (p_lista1->valor >= p_lista2->valor)
            {
                aux = p_lista1->valor - p_lista2->valor;
            }
            else
            {
                aux = p_lista1->valor - p_lista2->valor;
                aux = aux + 10; // deve-se adicionar 10 para manter a subtração correta, pois segue a lógica de
                                // "emprestar um" do algoritmo de subtração.
                if (p_lista1->esquerda != NULL)
                {
                    p_lista1->esquerda->valor -= 1;
                }
            }
            p_lista1 = p_lista1->esquerda;
            p_lista2 = p_lista2->esquerda;
        }
        else
        {
            aux = p_lista1->valor;
            p_lista1 = p_lista1->esquerda;
        }
        inserir_esquerda(&subtracao, abs(aux));
    }
    return subtracao;
}

// Remove todos os zeros à esquerda para configurar a saída do modo correto.
Natural remover_zeros_esquerda(Natural num_natural)
{
    p_no p_lista;
    p_lista = num_natural.mais_esq;
    while (p_lista->valor == 0 && num_natural.qtd > 1)
    {
        num_natural.mais_esq = num_natural.mais_esq->direita;
        free(p_lista);
        num_natural.qtd -= 1;
        p_lista = num_natural.mais_esq;
    }
    return num_natural;
}

// Recebe o ponteiro para o início da lista ligada e desaloca todas suas posições
void deletar_natural(p_no p_lista)
{
    p_no aux;
    while (p_lista)
    {
        aux = p_lista;
        p_lista = p_lista->direita;
        free(aux);
    }
}

//Dados dois números "lista1" e "lista2", multiplica-se eles e devolve um novo numero multiplicado.
Natural multiplicar_naturais(Natural lista1, Natural lista2)
{
    Natural multiplicacao, multiplicacao_parcial;
    int aux = 0, contador = 0;

    multiplicacao = criar_natural();

    p_no p_lista1;
    p_no p_lista2 = lista2.mais_dir;
    p_no p_mult_aux; //utilizado para se liberar as multiplicações parciais provenientes da soma na linha xxx.

    while (p_lista2 != NULL)
    {
        p_lista1 = lista1.mais_dir;
        aux = 0;
        multiplicacao_parcial = criar_natural();

        for (int i = 0; i < contador; i++)
        {
            inserir_direita(&multiplicacao_parcial, 0); //insere zeros à direita para alinhar a soma corretamente.
        }

        while (p_lista1 != NULL)
        {
            aux = (p_lista1->valor * p_lista2->valor) + aux;
            inserir_esquerda(&multiplicacao_parcial, aux % 10);
            aux = aux / 10;
            p_lista1 = p_lista1->esquerda;
        }

        if (aux > 0)
        {
            inserir_esquerda(&multiplicacao_parcial, aux); //insere um resto que talvez exista na variável aux.
        }

        contador += 1;
        
        p_mult_aux = multiplicacao.mais_esq;
        multiplicacao = somar_naturais(multiplicacao, multiplicacao_parcial);
        deletar_natural(p_mult_aux);
        deletar_natural(multiplicacao_parcial.mais_esq);
        
        p_lista2 = p_lista2->esquerda;
    }
    return multiplicacao;
}

//Printa na tela o número grande que foi operado.
void escrever_natural(Natural num_natural)
{
    p_no p_lista;
    p_lista = num_natural.mais_esq;
    while (p_lista)
    {
        printf("%d", p_lista->valor);
        p_lista = p_lista->direita;
    }
    printf("\n");
}

// A partir do parâmetro operacao, define se será realizada a soma, subtração ou multiplicação dos números.
void identificar_e_realizar_operacoes(char operacao)
{
    Natural lista1, lista2, soma, subtracao, multiplicacao;
    lista1 = ler_natural();
    lista2 = ler_natural();
    if (operacao == '+')
    {
        soma = somar_naturais(lista1, lista2);
        escrever_natural(soma);
        deletar_natural(soma.mais_esq);
    }
    else if (operacao == '-')
    {
        subtracao = subtrair_naturais(lista1, lista2);
        subtracao = remover_zeros_esquerda(subtracao);
        escrever_natural(subtracao);
        deletar_natural(subtracao.mais_esq);
    }

    else if (operacao == '*')
    {
        multiplicacao = multiplicar_naturais(lista1, lista2);
        multiplicacao = remover_zeros_esquerda(multiplicacao);
        escrever_natural(multiplicacao);
        deletar_natural(multiplicacao.mais_esq);
    }
    deletar_natural(lista1.mais_esq);
    deletar_natural(lista2.mais_esq);
}

int main()
{
    int n;
    char operacao;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &operacao);
        identificar_e_realizar_operacoes(operacao);
    }
    return 0;
}