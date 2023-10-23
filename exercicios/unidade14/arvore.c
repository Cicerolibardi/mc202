
typedef struct No
{
    int dado;
    struct No *esq, *dir; /* *pai */
} No;

typedef struct No *p_no;

/**
 * Cria uma nova árvore com duas árvores já
 * pré existentes
 **/
p_no criar_arvore(int x, p_no esq, p_no dir)
{
    p_no novo = malloc(sizeof(*novo));
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

/**
 * Devolve um nó da árvore com o valor x
 * ou NULL para caso não tenha.
 */
p_no procurar_no(p_no raiz, int x)
{
    p_no aux;

    if (raiz == NULL)
    {
        return NULL;
    }
    else if (x == raiz->dado)
    {
        return raiz;
    }
    else
    {
        aux = procurar_no(raiz->esq, x);
        if (aux != NULL)
        {
            return aux;
        }
        aux = procurar_no(raiz->dir, x);
        if (aux != NULL)
        {
            return aux;
        }
        return NULL;
    }
}

int numero_nos(p_no raiz);
int altura(p_no raiz);

p_no inserir_arvore(p_no raiz, int x)
{
    if (raiz == NULL)
    {
        p_no novo = malloc(sizeof(*novo));
        novo->dado = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    else if (x < raiz->dado)
    {
        raiz->esq = inserir_arvore(raiz->esq, x);
    }
    else
    {
        raiz->dir = inserir_arvore(raiz->dir, x);
    }
    return raiz;
}


void imprimir_ordem_crescente(p_no raiz){
    if (raiz != NULL){
        imprimir_ordem_crescente(raiz->esq);
        printf("%d ", raiz->dado);
        imprimir_ordem_crescente(raiz->dir);
    }
}

void imprimir_ordem_decrescente(p_no raiz){
    if (raiz != NULL){
        imprimir_ordem_decrescente(raiz->dir);
        printf("%d ", raiz->dado);
        imprimir_ordem_decrescente(raiz->esq);
    }
}
