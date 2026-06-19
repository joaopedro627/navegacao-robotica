# navegacao-robotica

Desenvolvi este simulador de navegação robótica em C como um projeto acadêmico de Engenharia de Software na Universidade Católica de Brasília. O sistema processa sequências de comandos direcionais (Norte, Sul, Leste, Oeste) para rastrear coordenadas em um plano, calculando rotas e métricas espaciais avançadas, como a distância de Manhattan e a distância geométrica pura.

A principal barreira técnica foi coordenar a alocação dinâmica e o encadeamento seguro de múltiplas estruturas, garantindo que o rastreamento da rota funcionasse perfeitamente sem causar vazamentos de memória ou falhas de segmentação durante a construção e destruição do caminho.

A construção desse sistema foi fundamental para minha compreensão sobre o uso de ponteiros. Aperfeiçoei consideravelmente minha capacidade de gerenciar a memória de forma manual com malloc e free, consolidando a manipulação de listas encadeadas e o controle de arquiteturas de baixo nível.
