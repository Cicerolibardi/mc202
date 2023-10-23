#include <stdio.h>

#define MAX 100


int main(){
    double x[MAX], y[MAX];
    double cx, cy;
    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("%lf %lf", &x[i], &y[i]);
    }

    cx = 0;
    cy = 0;

    for (int i = 0; i < n; i++){
        cx = cx + x[i];
        cy = cy + y[i];
    }

    cx = cx / n;
    cy = cy / n;

    printf("%lf %lf\n", cx, cy);

    return 0;
}