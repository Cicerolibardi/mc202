#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diadeuber.h"

void troca(Item *a, Item *b)
{
    Item t = *a;
    *a = *b;
    *b = t;
}

// Cria uma fila de priodade com o tamanho dado e retorna o ponteiro para essa fila.
Fila_prio *criar_filaprio(int tam)
{
    Fila_prio *fprio = malloc(sizeof(Fila_prio));
    fprio->v = malloc(tam * sizeof(Item));
    fprio->n = 0;
    fprio->tamanho = tam;
    return fprio;
}

// Função recursiva para consertar o vetor e fazer ele corresponder à um max_heap.
void sobe_no_heap(Fila_prio *fprio, int k)
{
    if (k > 0 && fprio->v[PAI(k)].avaliacao < fprio->v[k].avaliacao)
    {
        troca(&fprio->v[k], &fprio->v[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

// Função recursiva para consertar o vetor e fazer ele corresponder à um max_heap.
void desce_no_heap(Fila_prio *fprio, int k)
{
    int maior_filho;
    if (F_ESQ(k) < fprio->n)
    {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n &&
            fprio->v[F_ESQ(k)].avaliacao < fprio->v[F_DIR(k)].avaliacao)
            maior_filho = F_DIR(k);
        if (fprio->v[k].avaliacao < fprio->v[maior_filho].avaliacao)
        {
            troca(&fprio->v[k], &fprio->v[maior_filho]);
            desce_no_heap(fprio, maior_filho);
        }
    }
}

// Insere o item na fila de prioridade e "balanceia" essa fila de prioridade.
void insere(Fila_prio *fprio, Item item)
{
    fprio->v[fprio->n] = item;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}

// Extrai o máximo na fila de prioridade e "balanceia" essa fila de prioridade.
Item extrai_maximo(Fila_prio *fprio)
{
    Item item = fprio->v[0];
    troca(&fprio->v[0], &fprio->v[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return item;
}

// Calcula os valores das despesas, rendimento liquido e bruto e printa esses valores.
void calcular_printar_valor_final(int distancia_total, int distancia_parcial, int qtd_cancelamentos)
{
    double rendimento_bruto = 0;
    double despesas = 0;
    double rendimento_liquido = 0;

    rendimento_bruto += (qtd_cancelamentos * 7);
    rendimento_bruto += (1.4 * distancia_parcial);

    despesas += 57;
    despesas += (distancia_total / 10.0) * 4.104;

    rendimento_liquido += (0.75 * rendimento_bruto);
    rendimento_liquido -= despesas;

    printf("\n");
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", distancia_total);
    printf("Rendimento bruto: %.2f\n", rendimento_bruto);
    printf("Despesas: %.2f\n", despesas);
    printf("Rendimento liquido: %.2f\n", rendimento_liquido);
}

// Lê a entrada e realiza as operações dos tipos A, C, F e T.
void ler_entrada_realizar_operacoes(Fila_prio *fprioridade)
{
    char operacao;
    Item cliente_atual;
    Item cliente_inserir;
    Posicao pos_motorista;
    char nome_cancelar[16];
    int distancia_parcial = 0;
    int distancia_total = 0;
    int qtd_cancelamentos = 0;

    // Seta as variáveis para inicializar as operações.
    pos_motorista.x_saida = 0;
    pos_motorista.y_saida = 0;
    cliente_atual.esta_vazio = 1;

    while (scanf("%c", &operacao) != EOF)
    {
        if (operacao == 'A')
        {
            scanf("%s %lf %d %d %d %d", cliente_inserir.nome, &cliente_inserir.avaliacao,
                  &cliente_inserir.posicao.x_saida, &cliente_inserir.posicao.y_saida,
                  &cliente_inserir.posicao.x_chegada, &cliente_inserir.posicao.y_chegada);

            // Checa se a variavel cliente_atual está vazia, se não estiver, adiciona-se na fila.
            // Se estiver, muda-se o cliente_atual para o cliente da entrada.
            if (cliente_atual.esta_vazio == 0)
            {
                insere(fprioridade, cliente_inserir);
            }
            else
            {
                cliente_atual = cliente_inserir;
                cliente_atual.esta_vazio = 0;
            }

            printf("Cliente %s foi adicionado(a)\n", cliente_inserir.nome);
        }
        else if (operacao == 'F')
        {
            // Calcula a distância percorrida sem os clientes.
            distancia_total += abs(pos_motorista.x_saida - cliente_atual.posicao.x_saida) +
                               abs(pos_motorista.y_saida - cliente_atual.posicao.y_saida);

            // Calcula a distância percorrida com os clientes.
            distancia_parcial += abs(cliente_atual.posicao.x_saida - cliente_atual.posicao.x_chegada) +
                                 abs(cliente_atual.posicao.y_saida - cliente_atual.posicao.y_chegada);

            // Seta a próxima posição de saída do motorista para atualizar o seu percurso.
            pos_motorista.x_saida = cliente_atual.posicao.x_chegada;
            pos_motorista.y_saida = cliente_atual.posicao.y_chegada;

            printf("A corrida de %s foi finalizada\n", cliente_atual.nome);
            // Verifica se tem algum cliente na fila, se tiver, extrai-se ele para cliente atual.
            // Se não, seta-se o cliente_atual para vazio para receber o próximo cliente já ser recebido
            // na variavel cliente_atual.
            if (fprioridade->n > 0)
            {
                cliente_atual = extrai_maximo(fprioridade);
                cliente_atual.esta_vazio = 0;
            }
            else
            {
                cliente_atual.esta_vazio = 1;
            }
        }
        else if (operacao == 'C')
        {
            scanf("%s", nome_cancelar);
            printf("%s cancelou a corrida\n", nome_cancelar);
            qtd_cancelamentos += 1;

            // Procura no heap qual o cliente que deve-se retirar e "balanceia-se" o heap novamente.
            for (int i = 0; i < fprioridade->n; i++)
            {
                if (strcmp(fprioridade->v[i].nome, nome_cancelar) == 0)
                {
                    troca(&fprioridade->v[i], &fprioridade->v[fprioridade->n - 1]);
                    fprioridade->n--;
                    desce_no_heap(fprioridade, i);
                }
            }
        }
        else if (operacao == 'T')
        {
            // Soma-se a distancia_total, que até o momento é a distancia andada sem os clientes com
            // as distancias andada com os clientes, para assim, gerar a distancia total percorrida.
            distancia_total += distancia_parcial;
            calcular_printar_valor_final(distancia_total, distancia_parcial, qtd_cancelamentos);
        }
    }
}

// Libera uma fila de prioridade e o vetor dentro dela.
void libera_fila_prio(Fila_prio *fprioridade)
{
    free(fprioridade->v);
    free(fprioridade);
}