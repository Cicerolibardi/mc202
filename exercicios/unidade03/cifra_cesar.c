#include <stdio.h>

int main(){
    int k;
    char original, encriptado, pos_original, pos_encriptado;

    scanf("%d ", &k);
    scanf("%c", &original);

    while(original != '#'){
        pos_original = original - 'A';
        pos_encriptado = (pos_original + k) % 26;
        encriptado = pos_encriptado + 'A';
        printf("%c", encriptado);
        scanf("%c", &original);
    }

    printf("\n");
    return 0;
}