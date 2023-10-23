#include <stdio.h>
#include "complexos.h"

int main()
{
    char operacao;
    Complexo num1, num2, soma, subtracao, multiplicacao, divisao, potencia, conjugado;
    int expoente, i;
    int num_operacoes;

    scanf("%d", &num_operacoes);

    for (i = 0; i < num_operacoes; i++)
    {
        printf("Escreva a operação desejada: ");
        scanf(" %c", &operacao);
        if (operacao == '+')
        {
            num1 = inicializar_numero();
            num2 = inicializar_numero();
            soma = somar_complexos(num1, num2);
            printf("%.3lf %.3lfi\n", soma.a, soma.b);
        }
        else if (operacao == '-')
        {
            num1 = inicializar_numero();
            num2 = inicializar_numero();
            subtracao = subtrair_complexos(num1, num2);
            printf("%.3lf %.3lfi\n", subtracao.a, subtracao.b);
        }
        else if (operacao == '*')
        {
            num1 = inicializar_numero();
            num2 = inicializar_numero();
            multiplicacao = multiplicar_complexos(num1, num2);
            printf("%.3lf %.3lfi\n", multiplicacao.a, multiplicacao.b);
        }
        else if (operacao == '/')
        {
            num1 = inicializar_numero();
            num2 = inicializar_numero();
            divisao = dividir_complexos(num1, num2);
            printf("%.3lf %.3lfi\n", divisao.a, divisao.b);
        }
        else if (operacao == 'p')
        {
            num1 = inicializar_numero();
            printf("Escreva a potência do seu complexo: ");
            scanf("%d", &expoente);
            potencia = elevar_complexo(num1, expoente);
            printf("%.3lf %.3lfi\n", potencia.a, potencia.b);
        }
        else if (operacao == 'c')
        {
            num1 = inicializar_numero();
            conjugado = obter_conjugado(num1);
            printf("%.3lf %.3lfi\n", conjugado.a, conjugado.b);
        }
        else if (operacao == 'f')
        {
            return 0;
        }
    }
}