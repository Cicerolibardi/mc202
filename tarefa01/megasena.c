#include <stdio.h>

#define MAX_JOGADORES 1000

void ler_matriz_jogos(int matriz_jogos[][10], int num_jogadores) {
    // Lê a matriz dos jogos passados na entrada.
    int i, j;

    for (i = 0; i < (6* num_jogadores); i++) {
        for (j = 0; j < 10; j++) {
            scanf("%d", &matriz_jogos[i][j]);
        }
    }
}

void achar_quantidade_acertos(int matriz_jogos[][10], int acertos_jogadores[],
                                        int jogo_vencedor[], int num_jogadores){
    /*Recebe a matriz com todos os jogos, o número de jogadores, o jogo vencedor
    e modifica os elementos de "acertos_jogadores" para a quantidade de acertos
    de cada jogador a partir do jogo_vencedor.*/

    int i, j, k, valor_jogo_decimal, acertos;
    int pos_jogadores = 0;
    valor_jogo_decimal = 1;
    acertos = 0;

    for (i = 0; i < (num_jogadores * 6); i++){
        for (j = 0; j < 10; j++){
            for (k = 0; k < 6; k++){
                if ((jogo_vencedor[k] == valor_jogo_decimal) && (matriz_jogos[i][j] == 1)){
                    acertos += 1;
                    break;
                }
            }
            valor_jogo_decimal += 1;
        }

        if ((i + 1) % 6 == 0){
            acertos_jogadores[pos_jogadores] = acertos;
            pos_jogadores += 1;
            acertos = 0;
            valor_jogo_decimal = 1;
        }
    }
}

void definir_premio_jogadores(double vetor_premio[], double premio, int num_jogadores, int acertos_jogadores[]){
    /*Recebe o valor do prêmio, o número de jogadores, um vetor com a quantidade de acertos
    de cada jogador e modifica os elementos do vetor "vetor_premio" para a quantidade que cada
    jogador deve receber, com as posições na ordem da entrada.*/

    int quatro_acertos = 0, cinco_acertos = 0, seis_acertos = 0;
    double premio_quatro = 0.0, premio_cinco = 0.0, premio_seis = 0.0;
    int i;

    for (i = 0; i < num_jogadores; i++){
        if (acertos_jogadores[i] == 4){
            quatro_acertos += 1;
        }
        else if (acertos_jogadores[i] == 5){
            cinco_acertos += 1;
        }
        else if (acertos_jogadores[i] == 6){
            seis_acertos += 1;
        }
    }
    if (quatro_acertos != 0){
        premio_quatro = (premio * 0.19) / quatro_acertos;
    }
    if (cinco_acertos != 0){
        premio_cinco = (premio * 0.19) / cinco_acertos;
    }
    if (seis_acertos != 0){
        premio_seis = (premio * 0.62) / seis_acertos;
    }

    for (i = 0; i < num_jogadores; i++){
        if (acertos_jogadores[i] == 4){
            vetor_premio[i] = premio_quatro;
        }
        else if (acertos_jogadores[i] == 5){
            vetor_premio[i] = premio_cinco;
        }
        else if(acertos_jogadores[i] == 6){
            vetor_premio[i] = premio_seis;
        }
        else{
            vetor_premio[i] = 0.00;
        }
    }


}

void imprimir_premios(double vetor_premio[], int num_jogadores){
    /*Recebe o vetor que contém os prêmios de cada jogador e o número de jogadores e 
    mostra na tela os prêmios individuais, um por linha.*/

    for (int i = 0; i < num_jogadores; i++){
        printf("%.2f\n", vetor_premio[i]);
    }
}

void ler_jogo_vencedor(int jogo_vencedor[]){
    /*Lê o jogo vencedor de 6 números e modifica o vetor "jogo_vencedor" com os elementos sendo
    os números ganhadores.*/
    
    for (int i = 0; i < 6; i++){
        scanf("%d", &jogo_vencedor[i]);
    }
}

int main() {
    int num_jogadores;
    double premio;
    int jogo_vencedor[6];
    int acertos_jogadores[MAX_JOGADORES];
    int matriz_jogos[MAX_JOGADORES * 6][10];
    double vetor_premio[MAX_JOGADORES];

    scanf("%i %lf", &num_jogadores, &premio);
    ler_matriz_jogos(matriz_jogos, num_jogadores);
    ler_jogo_vencedor(jogo_vencedor);

    achar_quantidade_acertos(matriz_jogos, acertos_jogadores, jogo_vencedor, num_jogadores);

    definir_premio_jogadores(vetor_premio, premio, num_jogadores, acertos_jogadores);
    
    imprimir_premios(vetor_premio, num_jogadores);

    return 0;
}