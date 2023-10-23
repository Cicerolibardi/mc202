
typedef struct no *p_no;

struct no
{
    double coef;
    int grau;
    p_no prox;
};

p_no somar_polinomios(p_no p, p_no q)
{
    if (p == NULL)
    {
        return copiar_lista(q);
    }
    else if (q == NULL)
    {
        return copiar_lista(p);
    }
    else
    {
        p_no novo = malloc(sizeof(*novo));
        p_no r, s;
        if (p->grau < q->grau)
        {
            novo->grau = p.grau;
            novo->coef = p->coef;
            r = p->prox;
            s = q;
        }
        else if (p->grau > q.grau)
        {
            novo->grau = q.grau;
            novo->coef = q->coef;
            r = q->prox;
            s = p;
        }
        else
        {
            novo->grau = p->grau;
            novo->coef = p->coef + q.coef;
            r = p->prox;
            s = q->prox;
        }
        novo->prox = somar_polinomios(r,s);
        return novo;
    }
}