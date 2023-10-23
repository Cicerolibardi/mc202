typedef struct complexo
{
    double a;
    double b;
} Complexo;

Complexo inicializar_numero();

void imprimir_complexo(Complexo numero_imprimir);

Complexo obter_conjugado(Complexo numero_entrada);

Complexo somar_complexos(Complexo num1, Complexo num2);

Complexo subtrair_complexos(Complexo num1, Complexo num2);

Complexo multiplicar_complexos(Complexo fator1, Complexo fator2);

Complexo dividir_complexos(Complexo numerador, Complexo denominador);

Complexo elevar_complexo(Complexo base, int potencia);

