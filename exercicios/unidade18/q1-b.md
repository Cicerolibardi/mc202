Para o primeiro caso é verdadeiro, pois ao ordenar primeiro por mes, e depois por dia, nao teria
problemas com a ordenação, porque a ord_mes é instavel e a ord_dia estavel, assim, após a ordenação por mês ser feita, não importa a ordem dos dias pois eles vão ser ordenados pela ordena_dia, que será chamada a cada mês.
Para o segundo caso, a afirmação é falsa, pois, ao serem ordenados os dias e depois os meses, a ordenação dos meses ia prejudicar os dias que já estavam ordenados, por ser instável.