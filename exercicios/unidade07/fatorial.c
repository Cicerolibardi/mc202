/* c) A versão iterativa faz mais operações do que a operação
 *  recursiva, porém, ambas gastam a mesma quantidade de memória
 */

#include<stdio.h>

int pot(int a, int b){
    if ( b == 0 )
        return 1;
    else{
        return a*pot(a,b-1);
    }
}

int main(){
    int a,b, resp;
    scanf("%d %d", &a, &b);
    resp = pot(a,b);
    printf("Resposta: %d", resp);

}
// iterativa 
int pot (int base, int exp){
    int i, resultado = 1;

    for (i = 0; i < exp; i++)
    resultado = base;
    return resultado;
}

