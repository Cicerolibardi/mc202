#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala_de_espera.h"

// Retira do início do deque o primeiro elemento.
No_deque *desenfilerar(Deque *fila)
{
    No_deque *primeiro;
    primeiro = fila->inicio;
    fila->inicio = fila->inicio->dir;
    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }
    return primeiro;
}

// Inicializa os médicos de especialidades, setando o número máximo de profissionais.
Medicos inicializar_medicos(Medicos especialidades, int pos)
{
    int qtd_medicos_especialidades[9] = {10, 2, 5, 3, 4, 7, 2, 1, 4};

    for (int i = 0; i < 9; i++)
    {
        especialidades.qtd_profissionais = qtd_medicos_especialidades[pos];
        especialidades.qtd_fila = 0;
        especialidades.fila->inicio = NULL;
        especialidades.fila->fim = NULL;
    }

    return especialidades;
}

void inserir_dir_deque(Deque *lista_pacientes, Paciente *acidentado)
{
    No_deque *novo;

    novo = malloc(sizeof(No_deque));

    novo->dir = NULL;
    novo->esq = lista_pacientes->fim;
    novo->paciente = acidentado;

    if (lista_pacientes->fim != NULL)
    {
        lista_pacientes->fim->dir = novo;
    }
    else
    {
        lista_pacientes->inicio = novo; // é setado o inicio e o fim para o mesmo ponteiro para
                                        // quando o deque está vazio.
    }
    lista_pacientes->fim = novo;
}

void inserir_esq_deque(Deque *lista_pacientes, Paciente *acidentado)
{
    No_deque *novo;

    novo = malloc(sizeof(No_deque));

    novo->dir = lista_pacientes->inicio;
    novo->esq = NULL;
    novo->paciente = acidentado;

    if (lista_pacientes->inicio != NULL)
    {
        lista_pacientes->inicio->esq = novo;
    }
    else
    {
        lista_pacientes->fim = novo;
    }
    lista_pacientes->inicio = novo;
}

// Lê os pacientes e sua lista de atendimentos e retorna um Deque com os pacientes nesse deque
Deque ler_pacientes_e_organizar()
{
    char tipo_paciente[10];
    char seq_atendimento_prov[50];
    int ordem_chegada = 0;
    Deque lista_pacientes;

    lista_pacientes.inicio = NULL;
    lista_pacientes.fim = NULL;

    Paciente *acidentado;
    acidentado = malloc(sizeof(Paciente));
    if (acidentado == NULL)
    {
        exit(1);
    }

    while (scanf(" \"%[^\"]\" %s %[^\n]", acidentado->nome, tipo_paciente, seq_atendimento_prov) != EOF)
    {
        ordem_chegada += 1;

        acidentado->tipo = tipo_paciente[0];
        acidentado->id = ordem_chegada;
        acidentado->qtd_atendimentos_total = (strlen(seq_atendimento_prov) + 1) / 2;
        acidentado->qtd_atendimentos_atual = 0;

        acidentado->lista_atendimentos = malloc(acidentado->qtd_atendimentos_total * sizeof(int));
        if (acidentado->lista_atendimentos == NULL)
        {
            exit(1);
        }

        // são utilizados 2 contadores pois um deles tem que pular os espaços inseridos na entrada
        // para assim inserir corretamente na lista de atendimentos.
        for (int i = 0, j = 0; i < strlen(seq_atendimento_prov); i += 2, j++)
        {
            // é utilizada a retirada do caractere '0' pois a entrada foi lida como string.
            acidentado->lista_atendimentos[j] = seq_atendimento_prov[i] - '0';
        }

        inserir_dir_deque(&lista_pacientes, acidentado);
        acidentado = malloc(sizeof(Paciente));
    }
    free(acidentado); // utilizado para liberar o ultimo malloc
                      // que não foi usado pois scanf retornou EOF
    return lista_pacientes;
}

// Inicializa os pacientes dentro dos seus primeiros atendimentos.
void iniciar_pacientes_especialidades(Deque lista_pacientes, Medicos *especialidades, int i)
{
    No_deque *aux;
    aux = lista_pacientes.inicio;

    while (aux)
    {
        if ((aux->paciente->lista_atendimentos[0] - 1) == i && aux->paciente->tipo == 'p')
        {
            inserir_esq_deque(especialidades->fila, aux->paciente);
            especialidades->qtd_fila += 1;
        }
        else if ((aux->paciente->lista_atendimentos[0] - 1) == i && aux->paciente->tipo == 'n')
        {
            inserir_dir_deque(especialidades->fila, aux->paciente);
            especialidades->qtd_fila += 1;
        }
        aux = aux->dir;
    }
}

void printar_paciente(Paciente *paciente, int hora, int minuto, No_deque *no_paciente)
{
    if (hora < 10)
    {
        printf("0%d:%d0 ", hora, minuto);
    }
    else
    {
        printf("%d:%d0 ", hora, minuto);
    }
    for (int i = 0; no_paciente->paciente->nome[i] != '\0'; i++)
    {
        printf("%c", no_paciente->paciente->nome[i]);
    }
    printf("\n");
}

// Função utilizada para comparar os pacientes no qsort().
int comparar_pacientes(const void *no1, const void *no2)
{
    return (((*(No_deque **)no1)->paciente->id) - ((*(No_deque **)no2)->paciente->id));
}

// Faz o atendimento dos pacientes e coloca eles nas suas próximas posições de atendimento.
// O tipo de retorno int é 1 para quando ainda há pacientes para serem atendidos e 0 para quando
// não há mais pacientes para se atender.
int atender_pacientes(Medicos **especialidades, int hora, int minuto)
{
    No_deque *vetor[38];
    No_deque *aux;
    int contador = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < especialidades[i]->qtd_profissionais; j++)
        {
            if (especialidades[i]->fila->inicio != NULL)
            {
                aux = desenfilerar(especialidades[i]->fila);
                aux->paciente->qtd_atendimentos_atual += 1;
                // Significa que o número de atendimentos que ele deve realizar acabou.
                if ((aux->paciente->qtd_atendimentos_total) == aux->paciente->qtd_atendimentos_atual)
                {
                    printar_paciente(aux->paciente, hora, minuto, aux);
                    free(aux->paciente->lista_atendimentos);
                    free(aux->paciente);
                    free(aux);
                    especialidades[i]->qtd_fila -= 1;
                    continue;
                }
                aux->dir = NULL;
                aux->esq = NULL;
                vetor[contador] = aux;
                contador += 1;
                especialidades[i]->qtd_fila -= 1;
                if (especialidades[i]->qtd_fila == 0)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    int auxiliar = 0;

    //verifica se ainda há algum paciente em alguma fila
    for (int i = 0; i < 9; i++)
    {
        auxiliar += especialidades[i]->qtd_fila;
    }

    if (contador == 0 && auxiliar == 0)
    {
        return 0;
    }

    if (contador > 0)
    {
        qsort(vetor, contador, sizeof(No_deque *), comparar_pacientes);

        int pos_medico;
        // Esse for é utilizado para recolocar os pacientes que acabaram de sair de um atendimento e
        // tem que entrar em outro atendimento, ou seja, eles não terminaram sua lista de atendimentos
        // e devem ser recolocados em suas devidas posições.
        for (int i = 0; i < contador; i++)
        {
            // a expressão enorme abaixo significa que será pego a posição dentro de lista_atendimentos
            // correspondente ao próximo atendimento a ser realizado, e é utilizado esse inteiro - 1 para
            // designar qual das especialidades aquele paciente vai visitar.
            pos_medico = vetor[i]->paciente->lista_atendimentos[vetor[i]->paciente->qtd_atendimentos_atual] - 1;

            if (vetor[i]->paciente->tipo == 'n')
            {
                inserir_dir_deque(especialidades[pos_medico]->fila, vetor[i]->paciente);
            }
            else if (vetor[i]->paciente->tipo == 'p')
            {
                inserir_esq_deque(especialidades[pos_medico]->fila, vetor[i]->paciente);
            }
            especialidades[pos_medico]->qtd_fila += 1;
            free(vetor[i]);
        }
    }
    return 1;
}

void liberar_especialidades(Medicos **especialidades)
{
    for (int i = 0; i < 9; i++)
    {
        free(especialidades[i]->fila);
        free(especialidades[i]);
    }
    free(especialidades);
}

void liberar_pacientes(No_deque *inicio_lista_pacientes)
{
    No_deque *aux;
    aux = inicio_lista_pacientes;
    while (aux != NULL)
    {
        inicio_lista_pacientes = inicio_lista_pacientes->dir;
        free(aux);
        aux = inicio_lista_pacientes;
    }
}
