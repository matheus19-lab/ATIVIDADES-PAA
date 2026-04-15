#include <stdio.h>
#include <string.h>

/* Funcao para trocar dois elementos */
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Funcao para imprimir o vetor dentro de quadradinhos  */
void imprimir_vetor_quadrado(int v[], int n, int destaque1, int destaque2, const char *mensagem) {
    printf("\n%s\n", mensagem);
    
    /* Linha superior */
    printf("+");
    for (int i = 0; i < n; i++) {
        printf("-----");
        if (i < n - 1) printf("+");
    }
    printf("+\n");
    
    /* Linha dos numeros */
    printf("|");
    for (int i = 0; i < n; i++) {
        if (i == destaque1 || i == destaque2) {
            printf("[%3d]", v[i]); 
        } else {
            printf(" %3d ", v[i]);
        }
        if (i < n - 1) printf("|");
    }
    printf("|\n");
    
    /* Linha inferior */
    printf("+");
    for (int i = 0; i < n; i++) {
        printf("-----");
        if (i < n - 1) printf("+");
    }
    printf("+\n");
    
    /* Indices */
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("  %d  ", i);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}


void imprimir_vetor_normal(int v[], int n, const char *mensagem) {
    imprimir_vetor_quadrado(v, n, -1, -1, mensagem);
}

/* Funcao heapify com visualizacao */
void heapify(int v[], int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    
    printf("\n+-------------------------------------------------+");
    printf("\n| heapify: raiz = indice %d (valor %d)              |", i, v[i]);
    printf("\n+-------------------------------------------------+");
    
    imprimir_vetor_quadrado(v, n, i, -1, "Vetor atual (* = raiz):");
    
    if (esquerda < n && v[esquerda] > v[maior]) {
        maior = esquerda;
    }
    if (direita < n && v[direita] > v[maior]) {
        maior = direita;
    }
    
    if (maior != i) {
        printf("\n>>> %d (indice %d) e maior que %d (indice %d)", 
               v[maior], maior, v[i], i);
        printf("\n-> Trocando elementos das posicoes %d e %d\n", i, maior);
        
        imprimir_vetor_quadrado(v, n, i, maior, "Trocando ([ ] = elementos a trocar):");
        
        trocar(&v[i], &v[maior]);
        
        imprimir_vetor_normal(v, n, "Apos a troca:");
        
        heapify(v, n, maior);
    } else {
        printf("\nOK - Posicao %d ja esta correta\n", i);
    }
}


void heapsort(int v[], int n) {
    printf("\n+=================================================+");
    printf("\n|                    HEAPSORT                      |");
    printf("\n+=================================================+");
    
    imprimir_vetor_normal(v, n, "\nVETOR INICIAL:");
    
    /* Fase 1: Construir heap */
    printf("\n\n===================================================");
    printf("\nFASE 1: CONSTRUINDO MAX-HEAP");
    printf("\n===================================================\n");
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        printf("\n>> Processando no %d (valor %d)\n", i, v[i]);
        heapify(v, n, i);
        imprimir_vetor_normal(v, n, "Estado atual do heap:");
    }
    
    printf("\nMAX-HEAP construido com sucesso!");
    imprimir_vetor_normal(v, n, "Heap final:");
    
    /* Fase 2: Extrair elementos */
    printf("\n\n===================================================");
    printf("\nFASE 2: EXTRAINDO ELEMENTOS");
    printf("\n===================================================\n");
    
    for (int i = n - 1; i > 0; i--) {
        printf("\n+-------------------------------------------------+");
        printf("\n| Passo %d de %d                                     |", n - i, n - 1);
        printf("\n+-------------------------------------------------+");
        
        printf("\n-> Trocando raiz (indice 0, valor %d) com ultimo (indice %d, valor %d)",
               v[0], i, v[i]);
        
        imprimir_vetor_quadrado(v, n, 0, i, "[ ] Elementos a serem trocados:");
        
        trocar(&v[0], &v[i]);
        
        imprimir_vetor_normal(v, n, "Apos a troca (maior na posicao correta):");
        
        printf("\n-> Restaurando heap para os primeiros %d elementos\n", i);
        heapify(v, i, 0);
        imprimir_vetor_normal(v, n, "Heap restaurado:");
    }
    
    printf("\n\n+=================================================+");
    printf("\n|              HEAPSORT FINALIZADO                |");
    printf("\n+=================================================+");
    imprimir_vetor_normal(v, n, "\nVETOR ORDENADO FINAL:");
}

int main() {
    int vetor[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(vetor) / sizeof(vetor[0]);
    
    heapsort(vetor, n);
    
    printf("\n\n");
    return 0;
}