#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diadeuber.h"

int main()
{

    Fila_prio *fprioridade;

    fprioridade = criar_filaprio(500);
    ler_entrada_realizar_operacoes(fprioridade);
    libera_fila_prio(fprioridade);

    return 0;
}