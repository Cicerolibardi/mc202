#include <stdio.h>
/*
int surpresaAux(int N, int K){
    if (N % 10 == K){
        return 1;
    }
    return 0;
}

int surpresa(int N, int K){
    if (N == 0){
        return 0;
    }
    return surpresa(N/10, K) + surpresaAux(N, K);
}
*/

int incognita(int n){
    if (n == 0){
        return 1;
    }
    if (n == 1){
        return 1;
    }
    else
        return incognita(n-1) + 2*incognita(n-2);
    
}

int main(){
    int i;
    i = incognita(8);
    printf("%d", i);
}