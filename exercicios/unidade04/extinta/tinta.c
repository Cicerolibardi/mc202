#include <stdio.h>
#include <math.h>

typedef struct tinta{
    double azul, vermelho, amarelo;
} Tinta;

Tinta misturar(Tinta t1, Tinta t2){
    Tinta tsaida;
    tsaida.azul = (t1.azul + t2.azul) / 2;
    tsaida.vermelho = (t1.vermelho + t2.vermelho) / 2;
    tsaida.amarelo = (t1.amarelo + t2.amarelo) / 2;
    return tsaida;
}

int main(){
    Tinta t1;
    Tinta t2;
    Tinta tsaida;
    scanf("%lf %lf %lf", &t1.azul, &t1.vermelho, &t1.amarelo);
    scanf("%lf %lf %lf", &t2.azul, &t2.vermelho, &t2.amarelo);
    tsaida = misturar(t1, t2);
    printf("%.02lf %.02lf %.02lf\n", tsaida.azul, tsaida.vermelho, tsaida.amarelo);

}