#define MAX 997

int hashing(char *palavra)//função pelo metodo da divisao do hash
{
    int i, n = 0;
    for (i = 0; i < strlen(palavra); i++)
        n = (256 * n + palavra[i]) % MAX;
    return n;
}

//Feito por: Cícero Libardi, César Devens, Leonardo Borges e Lucas Oliveira