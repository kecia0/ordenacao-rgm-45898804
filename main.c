#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorts.h"

double run_sort(void (*fn)(int*, size_t, Metrics*),
                int *v, size_t n, Metrics *m) {
    reset_metrics(m);
    clock_t t0 = clock();
    fn(v, n, m);
    clock_t t1 = clock();
    return 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
}

void fill_random(int *v, size_t n) {
    for (size_t i = 0; i < n; i++)
        v[i] = rand() % 100000;
}

void print_csv_header() {
    printf("metodo,N,caso,passos_cmp,passos_swp,tempo_ms\n");
}

void run_all_methods(int *orig, size_t n, const char *caso) {
    Metrics m;
    int *tmp = malloc(n * sizeof(int));

    struct { char *nome; void (*fn)(int*,size_t,Metrics*); } algs[] = {
        {"insertion", insertion_sort},
        {"merge",     merge_sort},
        {"quick",     quick_sort},
    };

    for (int a = 0; a < 3; a++) {
        double avg_time = 0;
        long long avg_cmp = 0, avg_swp = 0;

        for (int r = 0; r < 5; r++) {
            memcpy(tmp, orig, n * sizeof(int));
            double t = run_sort(algs[a].fn, tmp, n, &m);

            avg_time += t;
            avg_cmp += m.cmp;
            avg_swp += m.swp;
        }

        avg_time /= 5.0;
        avg_cmp  /= 5;
        avg_swp  /= 5;

        printf("%s,%zu,%s,%lld,%lld,%.3f\n",
               algs[a].nome, n, caso,
               avg_cmp, avg_swp, avg_time);
    }

    free(tmp);
}

int main() {
    srand(time(NULL));

    print_csv_header();

    // Seu RGM fixo no código:
    char rgm_str[] = "45898804";

    size_t n = strlen(rgm_str);
    int *rgm = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++) rgm[i] = rgm_str[i] - '0';

    run_all_methods(rgm, n, "rgm");
    free(rgm);

    size_t Ns[] = {100, 1000, 10000};

    for (int k = 0; k < 3; k++) {
        size_t N = Ns[k];
        int *v = malloc(N * sizeof(int));

        fill_random(v, N);
        run_all_methods(v, N, "aleatorio");
        free(v);
    }

    return 0;
}
