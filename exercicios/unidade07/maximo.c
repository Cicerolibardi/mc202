/*
 * Devolve o valor máximo entre as
 * n primeiras posições do vetor.
*/
#include <stdio.h>

int maximo(int *vetor, int n){
    if (n == 1){
        return vetor[0];
    }
    else{
        int max_subvetor;
        max_subvetor = maximo(vetor, n-1);
        if (max_subvetor > vetor[n-1]){
            return max_subvetor;
        }
        else{
            return vetor[n-1];
        }
    }
}

int main(){
    int vetor[5] = {3, 5, 1000000, 1, 3};
    int maior;
    maior = maximo(vetor, 5);
    printf("%d", maior);
}