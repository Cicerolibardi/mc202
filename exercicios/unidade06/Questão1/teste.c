#include <stdio.h>
#include <stdlib.h>

/*a)Não há como determinar a saída preliminar desse programa, pois há a
    ocorrência de um segmentation fault quando há a designação para o valor
    de *h, quando não se foi alocado memória para essa variável. */

void f(int a, int b)
{
    int c = a;
    a = b;
    b = c;
}
void g(int **c, int n)
{
    *c = malloc(sizeof(int) * n);
}
void h(int *h)
{
    *h = 100;
}
int main()
{
    int a = 1, b = 2, c = 3;
    int **d;
    d = malloc(sizeof(int *));
    f(a, b);
    g(d, 1);
    h(*d);
    printf("%d, %d, %d", b, c, d[0][0]);
    free(d[0]);
    free(d);
    return 0;
}

/* b) Há sim um memory leak, pois não foi liberada a
    memória para o malloc feito para "c", isso dentro da função
    "g". */

