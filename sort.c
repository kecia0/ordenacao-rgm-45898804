#include "sorts.h"
#include <stdlib.h>

#define COUNT_CMP(m)  ((m)->cmp++)
#define COUNT_SWP(m)  ((m)->swp++)

void reset_metrics(Metrics *m) {
    m->cmp = 0;
    m->swp = 0;
}

/* ============================
   INSERTION SORT
   ============================ */
void insertion_sort(int *v, size_t n, Metrics *m) {
    for (size_t i = 1; i < n; i++) {
        int key = v[i];
        size_t j = i;

        while (j > 0) {
            COUNT_CMP(m);
            if (v[j - 1] <= key) break;

            v[j] = v[j - 1];
            COUNT_SWP(m);
            j--;
        }
        v[j] = key;
        COUNT_SWP(m);
    }
}

/* ============================
   MERGE SORT
   ============================ */
static void merge(int *v, int *aux, size_t l, size_t m, size_t r, Metrics *mt) {
    size_t i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        COUNT_CMP(mt);
        aux[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
        COUNT_SWP(mt);
    }

    while (i <= m) { aux[k++] = v[i++]; COUNT_SWP(mt); }
    while (j <= r) { aux[k++] = v[j++]; COUNT_SWP(mt); }

    for (i = l; i <= r; i++) {
        v[i] = aux[i];
        COUNT_SWP(mt);
    }
}

static void merge_sort_r(int *v, int *aux, size_t l, size_t r, Metrics *mt) {
    if (l >= r) return;

    size_t m = (l + r) / 2;
    merge_sort_r(v, aux, l, m, mt);
    merge_sort_r(v, aux, m + 1, r, mt);
    merge(v, aux, l, m, r, mt);
}

void merge_sort(int *v, size_t n, Metrics *m) {
    int *aux = malloc(sizeof(int) * n);
    merge_sort_r(v, aux, 0, n - 1, m);
    free(aux);
}

/* ============================
   QUICK SORT (Lomuto)
   ============================ */
static size_t partition_lomuto(int *v, size_t l, size_t r, Metrics *m) {
    int p = v[r];
    size_t i = l;

    for (size_t j = l; j < r; j++) {
        COUNT_CMP(m);
        if (v[j] < p) {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            COUNT_SWP(m);
            i++;
        }
    }

    int tmp = v[i];
    v[i] = v[r];
    v[r] = tmp;
    COUNT_SWP(m);

    return i;
}

static void quick_sort_r(int *v, size_t l, size_t r, Metrics *m) {
    if (l >= r) return;

    size_t p = partition_lomuto(v, l, r, m);
    if (p > 0) quick_sort_r(v, l, p - 1, m);
    quick_sort_r(v, p + 1, r, m);
}

void quick_sort(int *v, size_t n, Metrics *m) {
    quick_sort_r(v, 0, n - 1, m);
}
