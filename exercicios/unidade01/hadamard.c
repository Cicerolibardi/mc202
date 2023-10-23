#include <stdio.h>

#define MAX_SIZE 100

void ler_vetor(int vetor[], int tamanho){
    for (int i = 0; i < tamanho; i++){
        scanf("%d", &vetor[i]);
    }
}

void calcular_produto_hadamard(int u[], int v[], int tamanho, int produto[]){
    for (int i = 0; i < tamanho; i++){
        produto[i] = u[i] * v[i];
    }
}

void imprimir_vetor(int produto[], int tamanho){
    for (int i = 0; i < tamanho; i++){
        printf("%d\n", produto[i]);
    }
}

int main(){
    int u[MAX_SIZE], v[MAX_SIZE], produto[MAX_SIZE], tamanho;

    scanf("%d", &tamanho);
    ler_vetor(v, tamanho);
    ler_vetor(u, tamanho);
    calcular_produto_hadamard(u, v, tamanho, produto);
    imprimir_vetor(produto, tamanho);

    return 0;
}