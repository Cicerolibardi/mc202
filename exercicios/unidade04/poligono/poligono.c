#include <stdio.h>

#define MAX_VERTICES 100

typedef struct ponto{
    double x, y;
} Ponto;

typedef struct poligono{
    Ponto vertices[MAX_VERTICES];
    int n;
} Poligono;

Poligono *poligono_criar(){
    Poligono *p;

    p = malloc(sizeof(*p));
    p->n = 0;
    return p;

}

void poligono_adicionar(Poligono *p, Ponto v){
    p->vertices[p->n] = v;
    p->n++;
}

void liberar_poligono(Poligono *p){
    free(p);
}

int main(){
    
}