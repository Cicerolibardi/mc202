#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMO_SIZE 26

typedef struct termo
{
    char *nome_termo;
    double *historico;
    double maximo, minimo, media, desvpad;
    int id_categoria;

} Termo;

void alocar_memoria_termo(Termo *p_vetor_termos, int m, int n)
{
    if (p_vetor_termos == NULL)
        exit(1);

    for (int i = 0; i < n; i++)
    {
        p_vetor_termos[i].historico = malloc(m * sizeof(double));
        if (p_vetor_termos[i].historico == NULL)
            exit(1);

        p_vetor_termos[i].nome_termo = malloc(MAX_TERMO_SIZE * sizeof(char));
        if (p_vetor_termos[i].nome_termo == NULL)
            exit(1);
    }
}

void receber_entrada(Termo *p_vetor_termos, int m, int n)
{
    int i, k;
    for (i = 0; i < n; i++)
    {
        scanf(" %s", p_vetor_termos[i].nome_termo);
        for (k = 0; k < m; k++)
        {
            scanf("%lf", &p_vetor_termos[i].historico[k]);
        }
    }
}

double achar_maximo(Termo *p_vetor_termos, int m, int idx)
{
    int k;
    double maximo;
    maximo = p_vetor_termos[idx].historico[0];
    for (k = 1; k < m; k++)
    {
        if (p_vetor_termos[idx].historico[k] > maximo)
        {
            maximo = p_vetor_termos[idx].historico[k];
        }
    }
    return maximo;
}

double achar_minimo(Termo *p_vetor_termos, int m, int idx)
{
    int k;
    double minimo;
    minimo = p_vetor_termos[idx].historico[0];
    for (k = 1; k < m; k++)
    {
        if (p_vetor_termos[idx].historico[k] < minimo)
        {
            minimo = p_vetor_termos[idx].historico[k];
        }
    }
    return minimo;
}

double calcular_media(Termo *p_vetor_termos, int m, int idx)
{
    int k;
    double media = 0.0;
    for (k = 0; k < m; k++)
    {
        media += p_vetor_termos[idx].historico[k];
    }
    media = media / m;
    return media;
}

double calcular_desvpad(Termo *p_vetor_termos, int m, int idx, double media)
{
    int k;
    double desvpad = 0.0;

    for (k = 0; k < m; k++)
    {
        desvpad += (p_vetor_termos[idx].historico[k] - media) * (p_vetor_termos[idx].historico[k] - media);
    }
    desvpad = desvpad / m;
    desvpad = sqrt(desvpad);
    return desvpad;
}

void calcular_parametros_e_printar(Termo *p_vetor_termos, int m, int n)
{
    for (int i = 0; i < n; i++)
    {
        p_vetor_termos[i].maximo = achar_maximo(p_vetor_termos, m, i);
        p_vetor_termos[i].minimo = achar_minimo(p_vetor_termos, m, i);
        p_vetor_termos[i].media = calcular_media(p_vetor_termos, m, i);
        p_vetor_termos[i].desvpad = calcular_desvpad(p_vetor_termos, m, i, p_vetor_termos[i].media);

        printf("%s %.2lf %.2lf %.2lf %.2lf\n", p_vetor_termos[i].nome_termo, p_vetor_termos[i].maximo,
               p_vetor_termos[i].minimo, p_vetor_termos[i].media, p_vetor_termos[i].desvpad);
    }
    printf("\n");
}

void adicionar_identificadores(Termo *p_vetor_termos, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (p_vetor_termos[i].media >= 60 && p_vetor_termos[i].desvpad > 15)
        {
            p_vetor_termos[i].id_categoria = 0; // 0 é identificador para Bot.
        }
        else if (p_vetor_termos[i].media >= 60 && p_vetor_termos[i].desvpad <= 15)
        {
            p_vetor_termos[i].id_categoria = 1; // 1 é identificador para Evento Surpreendente.
        }
        else if (p_vetor_termos[i].media < 60 && p_vetor_termos[i].maximo >= 80 && p_vetor_termos[i].minimo > 20)
        {
            p_vetor_termos[i].id_categoria = 2; // 2 é identificador para Evento normal.
        }
        else if (p_vetor_termos[i].media < 60 && p_vetor_termos[i].maximo >= 80 && p_vetor_termos[i].minimo <= 20)
        {
            p_vetor_termos[i].id_categoria = 3; // 3 é identificador para Evento local.
        }
        else if (p_vetor_termos[i].media < 60 && p_vetor_termos[i].maximo < 80)
        {
            p_vetor_termos[i].id_categoria = 4; // 4 é identificador para Evento irrelevante.
        }
    }
}

void contabilizar_identificadores_e_printar(Termo *p_vetor_termos, int n)
{
    int i, k, contador;

    printf("RESULTADO:\n");

    for (i = 0; i < 5; i++)
    {
        contador = 0;
        for (k = 0; k < n; k++)
        {
            if (p_vetor_termos[k].id_categoria == i)
            {
                contador += 1;
            }
        }
        if (i == 0)
        {
            printf("Bot (%d): ", contador);
        }
        else if (i == 1)
        {
            printf("Surpreendente (%d): ", contador);
        }
        else if (i == 2)
        {
            printf("Normal (%d): ", contador);
        }
        else if (i == 3)
        {
            printf("Local (%d): ", contador);
        }
        else if (i == 4)
        {
            printf("Irrelevante (%d): ", contador);
        }
        for (k = 0; k < n; k++)
        {
            if (p_vetor_termos[k].id_categoria == i)
            {
                printf("%s ", p_vetor_termos[k].nome_termo);
            }
        }
        printf("\n");
    }
}

void liberar_memoria(Termo *p_vetor_termos, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(p_vetor_termos[i].historico);
        free(p_vetor_termos[i].nome_termo);
    }
    free(p_vetor_termos);
}

int main()
{
    Termo *p_vetor_termos;
    int m, n;

    scanf("%d %d", &n, &m);

    p_vetor_termos = malloc(n * sizeof(Termo));
    alocar_memoria_termo(p_vetor_termos, m, n);

    receber_entrada(p_vetor_termos, m, n);

    calcular_parametros_e_printar(p_vetor_termos, m, n);

    adicionar_identificadores(p_vetor_termos, n);
    contabilizar_identificadores_e_printar(p_vetor_termos, n);

    liberar_memoria(p_vetor_termos, n);
    return 0;
}