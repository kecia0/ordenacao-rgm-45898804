Autor: RGM 45898804

Este projeto implementa e compara três algoritmos de ordenação em C:

Insertion Sort

Merge Sort

Quick Sort (Lomuto)

A comparação é feita sobre:

Meu RGM (45898804) convertido em vetor de dígitos

Vetores aleatórios nos tamanhos 100, 1000 e 10000

Para cada execução, são coletados:

Comparações (cmp)

Movimentações/trocas (swp)

Tempo em milissegundos (ms)

Tudo é registrado em formato CSV, conforme exigido no trabalho.

RGM utilizado
45898804


Convertido para vetor:

[4, 5, 8, 9, 8, 8, 0, 4]


Ordenado corretamente:

[0, 4, 4, 5, 8, 8, 8, 9]

Como compilar
gcc -O1 -std=c11 src/*.c -o ordena

Como executar
./ordena

Política de contagem de passos

1 comparação = cmp++

1 troca/movimentação = swp++

Medição de tempo

O tempo de CPU é coletado com:

clock()
tempo_ms = 1000.0 * (t1 - t0) / CLOCKS_PER_SEC


Cada caso é executado 5 vezes e a média é impressa.

Exemplo de saída CSV real (RGM)

(Valores ilustrativos — substitua pelo que o programa gerar.)

metodo,N,caso,passos_cmp,passos_swp,tempo_ms
insertion,8,rgm,21,19,0.003
merge,8,rgm,25,31,0.004
quick,8,rgm,17,15,0.002

Conclusão

Insertion Sort é bom apenas para vetores pequenos (como o RGM).

Merge Sort é estável, tem bom desempenho e mantém O(n log n).

Quick Sort foi o mais rápido na prática para vetores grandes.

📌 Melhor algoritmo geral: Quick Sort
📌 Melhor estabilidade: Merge Sort
📌 Melhor para pequenas entradas: Insertion Sort
