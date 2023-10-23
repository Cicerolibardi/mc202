# a)

    - O(n^5)
    - O(n*log(n))
    - O(2^n)
    - O(n^2)
    - O(n^n)

# b)

## 1)

    f(n) = O(g(n)) se f(n) <= c.g(n), para todo n>=n0.

    f(n) = 2^n

    g(n) = 2^(n-0,01)

    Como:

    2^(n-0,001) = 2^(n).(1/(2^0,001))

    Portanto c = (1/(2^0,001))

    Então, como f(n) <= c.g(n) para todo n>=n0, a afirmação é verdadeira.

## 2)

    f(n) = 2^n

    g(n) = O(2^(n.(1-0,001)))

    Como:

    2^(n.(1-0,001)) = 2^n.(1/(2^0,001n))

    Como c é uma constante, c não pode ser igual a 2^n.(1/(2^0,001n)).

    Então, como f(n) > c.g(n) para todo n>=n0, a afirmação é falsa.

## 3)

    f(n) = n^2

    g(n) = O(n^1.999)

    Como:

    n^2 > n^1.999, não existe n >= n0 que faça com que f(n) <= c.g(n),
    portanto, a afirmação é falsa.

> Feito por: Cícero Libardi, Leonardo Borges e Lucas Oliveira.