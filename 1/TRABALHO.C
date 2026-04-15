/*
 * Trabalho 02 - Algoritmos de Ordenação
 * Disciplina: Projeto e Análise de Algoritmos
 * Professor: Raí Araújo de Miranda
 * Dupla 02 – Julio e Matheus
 * Algoritmos: Heapsort e Combsort
 * Universidade Federal do Piauí – UFPI
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#endif

/* ============================================================
   UTILITÁRIOS
   ============================================================ */

/* Gera vetor com números aleatórios entre 1 e 1.000.000 */
void gerar_aleatorio(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % 1000000 + 1;
}

/* Gera vetor ordenado em ordem crescente */
void gerar_crescente(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = i + 1;
}

/* Gera vetor ordenado em ordem decrescente */
void gerar_decrescente(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = n - i;
}

/* Copia vetor src para dst */
void copiar_vetor(int *dst, int *src, int n) {
    memcpy(dst, src, n * sizeof(int));
}

/*
 * Retorna o tempo atual em segundos.
 * Usa QueryPerformanceCounter no Windows e clock_gettime no Linux/Mac,
 * garantindo alta precisão em ambas as plataformas.
 */
double tempo_atual() {
#ifdef _WIN32
    LARGE_INTEGER freq, contador;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&contador);
    return (double)contador.QuadPart / (double)freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
#endif
}

/* Troca dois inteiros */
void trocar(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ============================================================
   HEAPSORT
   ============================================================ */

/*
 * Heapify (peneirar para baixo): mantém a propriedade de max-heap
 * na subárvore enraizada no índice i, para um heap de tamanho n.
 */
void heapify(int *v, int n, int i) {
    int maior = i;          /* raiz */
    int esq   = 2 * i + 1; /* filho esquerdo */
    int dir   = 2 * i + 2; /* filho direito */

    if (esq < n && v[esq] > v[maior])
        maior = esq;

    if (dir < n && v[dir] > v[maior])
        maior = dir;

    if (maior != i) {
        trocar(&v[i], &v[maior]);
        heapify(v, n, maior); /* recursão na subárvore afetada */
    }
}

/*
 * Heapsort:
 *  1. Constrói um max-heap a partir do vetor (fase build-heap).
 *  2. Extrai o máximo repetidamente, colocando-o no final.
 *
 * Complexidade:
 *  - Melhor caso : O(n log n)
 *  - Caso médio  : O(n log n)
 *  - Pior caso   : O(n log n)
 *  - Espaço      : O(1) — in-place
 */
void heapsort(int *v, int n) {
    /* Fase 1: Build-heap — começa no último nó interno */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    /* Fase 2: Extração — move raiz (máximo) para o final */
    for (int i = n - 1; i > 0; i--) {
        trocar(&v[0], &v[i]); /* maior elemento vai para a posição i */
        heapify(v, i, 0);     /* restaura heap sem o elemento já ordenado */
    }
}

/* ============================================================
   COMBSORT
   ============================================================ */

/*
 * Combsort:
 *  Melhoria do Bubble Sort: em vez de comparar elementos adjacentes,
 *  usa um "gap" (intervalo) que começa grande e vai diminuindo com um
 *  fator de encolhimento (shrink factor), tipicamente 1.3.
 *  Isso elimina "tartarugas" (valores pequenos no fim do vetor) rapidamente.
 *
 * Complexidade:
 *  - Melhor caso : O(n log n)
 *  - Caso médio  : O(n^2 / 2^p)  (p = número de incrementos)
 *  - Pior caso   : O(n^2)
 *  - Espaço      : O(1) — in-place
 */
void combsort(int *v, int n) {
    double shrink = 1.3;  
    int gap = n;
    int ordenado = 0;

    while (!ordenado) {
        gap = (int)(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            ordenado = 1;
        }

        for (int i = 0; i + gap < n; i++) {
            if (v[i] > v[i + gap]) {
                trocar(&v[i], &v[i + gap]);
                ordenado = 0; 
            }
        }
    }
}

/* ============================================================
   BENCHMARK
   ============================================================ */

typedef void (*FuncOrdenacao)(int *, int);

/*
 * Mede o tempo de execução de um algoritmo de ordenação
 * sobre uma cópia do vetor original.
 * Retorna o tempo em segundos.
 */
double medir_tempo(FuncOrdenacao algoritmo, int *original, int n) {
    int *copia = (int *)malloc(n * sizeof(int));
    if (!copia) {
        fprintf(stderr, "Erro: falha na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    copiar_vetor(copia, original, n);

    double inicio = tempo_atual();
    algoritmo(copia, n);
    double fim = tempo_atual();

    free(copia);
    return fim - inicio;
}

/* ============================================================
   MAIN
   ============================================================ */

int main(void) {
    srand((unsigned)time(NULL));

    /* Conjuntos de dados conforme o enunciado */
    int tamanhos[] = {20000, 40000, 60000};
    int num_tamanhos = 3;

    const char *tipos[]   = {"Crescente", "Decrescente", "Aleatorio"};
    int         num_tipos = 3;

    /* Tabela de resultados: [tamanho][tipo][algoritmo] */
    double resultados[3][3][2]; /* [tam][tipo][alg: 0=heap, 1=comb] */

    printf("=======================================================\n");
    printf("  Trabalho 02 - Algoritmos de Ordenacao\n");
    printf("  Dupla 02: Julio e Matheus\n");
    printf("  Algoritmos: Heapsort e Combsort\n");
    printf("=======================================================\n\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        int *base = (int *)malloc(n * sizeof(int));
        if (!base) {
            fprintf(stderr, "Erro: falha na alocação de memória.\n");
            return EXIT_FAILURE;
        }

        printf("-------------------------------------------------------\n");
        printf("  Tamanho do vetor: %d elementos\n", n);
        printf("-------------------------------------------------------\n");
        printf("  %-15s  %-15s  %-15s\n", "Tipo", "Heapsort (s)", "Combsort (s)");
        printf("  %-15s  %-15s  %-15s\n", "---------------", "---------------", "---------------");

        for (int tp = 0; tp < num_tipos; tp++) {
            /* Gera o vetor base conforme o tipo */
            if (tp == 0)      gerar_crescente(base, n);
            else if (tp == 1) gerar_decrescente(base, n);
            else              gerar_aleatorio(base, n);

            double t_heap = medir_tempo(heapsort, base, n);
            double t_comb = medir_tempo(combsort, base, n);

            resultados[t][tp][0] = t_heap;
            resultados[t][tp][1] = t_comb;

            printf("  %-15s  %-15.6f  %-15.6f\n", tipos[tp], t_heap, t_comb);
        }

        printf("\n");
        free(base);
    }

    /* Resumo comparativo */
    printf("=======================================================\n");
    printf("  RESUMO COMPARATIVO (tempos em segundos)\n");
    printf("=======================================================\n");
    printf("  %-12s  %-12s  %-15s  %-15s  %-10s\n",
           "Tamanho", "Tipo", "Heapsort (s)", "Combsort (s)", "Vencedor");
    printf("  %-12s  %-12s  %-15s  %-15s  %-10s\n",
           "------------", "------------", "---------------", "---------------", "----------");

    for (int t = 0; t < num_tamanhos; t++) {
        for (int tp = 0; tp < num_tipos; tp++) {
            double h = resultados[t][tp][0];
            double c = resultados[t][tp][1];
            const char *vencedor = (h <= c) ? "Heapsort" : "Combsort";
            printf("  %-12d  %-12s  %-15.6f  %-15.6f  %-10s\n",
                   tamanhos[t], tipos[tp], h, c, vencedor);
        }
    }

    printf("\n=======================================================\n");
    printf("  COMPLEXIDADE ASSINTÓTICA\n");
    printf("=======================================================\n");
    printf("  Heapsort:\n");
    printf("    Melhor caso  : O(n log n)\n");
    printf("    Caso medio   : O(n log n)\n");
    printf("    Pior caso    : O(n log n)\n");
    printf("    Espaco extra : O(1)  — in-place\n");
    printf("    Estavel      : Nao\n\n");
    printf("  Combsort:\n");
    printf("    Melhor caso  : O(n log n)\n");
    printf("    Caso medio   : O(n^2 / 2^p)\n");
    printf("    Pior caso    : O(n^2)\n");
    printf("    Espaco extra : O(1)  — in-place\n");
    printf("    Estavel      : Nao\n");
    printf("=======================================================\n");

    return 0;
}