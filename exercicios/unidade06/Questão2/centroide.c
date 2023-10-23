#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ** ler_pontos(int n, int k){
    double **pontos;
    int i, j;
    pontos = malloc(k * sizeof(double*));
    for(i = 0; i < k; i++){
        pontos[i] = malloc(n * sizeof(double));
    }
    for(i = 0; i < k; i++){
        for(j = 0; j < n; j++){
            scanf(" %lf", &pontos[i][j]);
        }
    }
    return pontos;
}

double * calcular_centroide(double ** pontos, int n, int k){
    int i, j;
    double *centroide;
    centroide = calloc(n, sizeof(double));

    for(i = 0; i < n; i++){
        for(j = 0; j < k; j++){
            centroide[i] += pontos[j][i];
        }
        centroide[i] = centroide[i] / k;
    }
    return centroide;
}

double * calcular_distancias (double ** pontos, int n, int k, double * centroide){
    double *distancias;
    int i, j;
    malloc(k * sizeof(double));
    for(i = 0; i < k; i++){
        for(j = 0; j < n; j++){
            distancias[i] += pow((pontos[i][j] - centroide[j]), 2);
        }
        distancias[i] = sqrt(distancias[i]);
    }
    return distancias;
}


void limpar(double ** pontos, int k, double * distancias, double * centroide){
    for(int i = 0; i < k; i++){
        free(pontos[i]);
    }
    free(distancias);
    free(centroide);

}

int main(){
    int n, k;
    double **pontos;
    double *centroide;
    double *distancias;
    double soma_distancias = 0;
    scanf("%d", &n);
    scanf("%d", &k);
    pontos = ler_pontos(n, k);
    centroide = calcular_centroide(pontos, n, k);
    distancias = calcular_distancias(pontos, n, k, centroide);
    for(int i = 0; i < k; i++){
        soma_distancias += distancias[i];
    }
    printf("%lf", soma_distancias);
    limpar(pontos, k, distancias, centroide);
    
}

// Feito por Cícero Libardi, Leonardo Borges e Lucas Oliveira.