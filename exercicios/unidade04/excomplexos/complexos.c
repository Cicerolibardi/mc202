#include <stdio.h>
#include <math.h>
#include "complexos.h"

Complexo inicializar_numero()
{
    Complexo numero;
    printf("Digite o número na forma 'a b': ");
    scanf("%lf %lf", &numero.a, &numero.b);

    return numero;
}

void imprimir_complexo(Complexo complexo)
{
    printf("%.3lf + %.3lfi\n", complexo.a, complexo.b);
}

Complexo somar_complexos(Complexo num1, Complexo num2)
{
    Complexo num_somado;

    num_somado.a = num1.a + num2.a;
    num_somado.b = num1.b + num2.b;

    return num_somado;
}

Complexo subtrair_complexos(Complexo num1, Complexo num2)
{
    Complexo num_subtraido;

    num_subtraido.a = num1.a - num2.a;
    num_subtraido.b = num1.b - num2.b;

    return num_subtraido;
}

Complexo obter_conjugado(Complexo num_entrada)
{
    num_entrada.b = (-1) * num_entrada.b;
    return num_entrada;
}

Complexo multiplicar_complexos(Complexo fator1, Complexo fator2)
{
    Complexo num_multiplicado;

    num_multiplicado.a = (fator1.a * fator2.a) + (fator1.b * fator2.b);
    num_multiplicado.b = (fator1.b * fator2.a) + (fator1.a * fator2.b);

    return num_multiplicado;
}

Complexo dividir_complexos(Complexo numerador, Complexo denominador)
{
    Complexo conjugado_denom, complexo_dividido;
    double novo_denominador;

    conjugado_denom = obter_conjugado(denominador);

    denominador = multiplicar_complexos(denominador, conjugado_denom);

    novo_denominador = denominador.a;

    numerador = multiplicar_complexos(numerador, conjugado_denom);

    complexo_dividido.a = numerador.a / novo_denominador;
    complexo_dividido.b = numerador.b / novo_denominador;

    return complexo_dividido;
}

Complexo elevar_complexo(Complexo base, int expoente)
{
    int i;
    Complexo complexo_elevado;

    complexo_elevado = base;

    if (expoente == 0)
    {
        complexo_elevado.a = 1;
        complexo_elevado.b = 0;
        return complexo_elevado;
    }

    for (i = 0; i < (expoente - 1); i++)
    {
        complexo_elevado = multiplicar_complexos(complexo_elevado, base);
    }

    return complexo_elevado;
}