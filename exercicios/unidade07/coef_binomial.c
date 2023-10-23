
/**
 * Devolve o binômial
 * de n escolhe k
 */

int combinacao(int n, int k)
{
    if (n == 0 || k == 0)
    {
        return 1;
    }
    else
    {
        return (combinacao(n - 1, k - 1) + combinacao(n - 1, k));
    }
}