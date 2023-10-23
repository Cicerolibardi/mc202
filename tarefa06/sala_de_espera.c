#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala_de_espera.h"

int main()
{
    Medicos **especialidades;
    Deque lista_pacientes;
    int aux = 1;
    int hora = 8;
    int minuto = 1;

    lista_pacientes.inicio = NULL;
    lista_pacientes.fim = NULL;

    lista_pacientes = ler_pacientes_e_organizar();

    especialidades = malloc(9 * sizeof(Medicos *));

    for (int i = 0; i < 9; i++)
    {
        // Esse for é utilizado para alocar todas as posições dentro dos médicos, alocar os deques deles
        // e inicializar esses deques alocados com os primeiros atendimentos de todos pacientes.
        especialidades[i] = malloc(sizeof(Medicos));
        especialidades[i]->fila = malloc(sizeof(*especialidades[i]->fila));
        *especialidades[i] = inicializar_medicos(*especialidades[i], i);
        iniciar_pacientes_especialidades(lista_pacientes, especialidades[i], i);
    }

    while (aux != 0)
    {
        aux = atender_pacientes(especialidades, hora, minuto);
        minuto += 1;
        if (minuto == 6)
        {
            minuto -= 6;
            hora += 1;
        }
    }

    liberar_especialidades(especialidades);
    liberar_pacientes(lista_pacientes.inicio);

    return 0;
}