#ifndef SALA_DE_ESPERA_H
#define SALA_DE_ESPERA_H

typedef struct Paciente Paciente;

struct Paciente
{
    char nome[51];
    char tipo;
    int id;
    int qtd_atendimentos_total;
    int qtd_atendimentos_atual;
    int *lista_atendimentos;
};

typedef struct No_deque
{
    Paciente *paciente;
    struct No_deque *esq;
    struct No_deque *dir;
} No_deque;

typedef struct Deque
{
    No_deque *inicio;
    No_deque *fim;
} Deque;

typedef struct Medicos
{
    Deque *fila;
    int qtd_fila;
    int qtd_profissionais;
} Medicos;

No_deque *desenfilerar(Deque *fila);
Medicos inicializar_medicos(Medicos especialidades, int pos);
void inserir_dir_deque(Deque *lista_pacientes, Paciente *acidentado);
void inserir_esq_deque(Deque *lista_pacientes, Paciente *acidentado);
Deque ler_pacientes_e_organizar();
void iniciar_pacientes_especialidades(Deque lista_pacientes, Medicos *especialidades, int i);
void printar_paciente(Paciente *paciente, int hora, int minuto, No_deque *no_paciente);
int comparar_pacientes(const void *no1, const void *no2);
int atender_pacientes(Medicos **especialidades, int hora, int minuto);
void liberar_especialidades(Medicos **especialidades);
void liberar_pacientes(No_deque *inicio_lista_pacientes);

#endif