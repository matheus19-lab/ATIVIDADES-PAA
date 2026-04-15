#include <stdio.h>

/* Funcao para trocar dois elementos */
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Funcao para imprimir o vetor dentro de quadradinhos  */
void imprimir_vetor_quadrado(int v[], int n, int pos1, int pos2, const char *mensagem) {
    printf("\n%s\n", mensagem);
    
   
    printf("+");
    for (int i = 0; i < n; i++) {
        printf("-----");
        if (i < n - 1) printf("+");
    }
    printf("+\n");
    
    printf("|");
    for (int i = 0; i < n; i++) {
        if (i == pos1 || i == pos2) {
            printf("[%3d]", v[i]);  
        } else {
            printf(" %3d ", v[i]);
        }
        if (i < n - 1) printf("|");
    }
    printf("|\n");
    

    printf("+");
    for (int i = 0; i < n; i++) {
        printf("-----");
        if (i < n - 1) printf("+");
    }
    printf("+\n");
    

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

/* Funcao para mostrar o gap visualmente */
void mostrar_gap(int v[], int n, int gap, int passagem) {
    printf("\n+-------------------------------------------------+");
    printf("\n| PASSAGEM %-2d | GAP = %-2d                           |", passagem, gap);
    printf("\n+-------------------------------------------------+");
    
    printf("\n\nVisualizacao do gap (distancia = %d):", gap);
    printf("\n+");
    for (int i = 0; i < n; i++) {
        printf("-----");
        if (i < n - 1) printf("+");
    }
    printf("+\n");
    
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" %3d ", v[i]);
        if (i < n - 1) printf("|");
    }
    printf("|\n");
    
    printf("+");
    for (int i = 0; i < n; i++) {
        printf("-----");
        if (i < n - 1) printf("+");
    }
    printf("+\n");
    
    /* Mostra as conexoes do gap */
    printf(" ");
    for (int i = 0; i < n; i++) {
        if (i + gap < n) {
            printf("  |  ");
        } else {
            printf("     ");
        }
        if (i < n - 1) printf(" ");
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        if (i + gap < n) {
            printf("  v  ");
        } else {
            printf("     ");
        }
        if (i < n - 1) printf(" ");
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        if (i + gap < n) {
            printf("  |  ");
        } else {
            printf("     ");
        }
        if (i < n - 1) printf(" ");
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        if (i + gap < n) {
            printf("  +-> ");
        } else {
            printf("     ");
        }
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

/* Combsort principal */
void combsort(int v[], int n) {
    double shrink = 1.3;
    int gap = n;
    int trocou = 1;
    int passagem = 1;
    
    printf("\n+=================================================+");
    printf("\n|                    COMBSORT                      |");
    printf("\n+=================================================+");
    
    imprimir_vetor_normal(v, n, "\nVETOR INICIAL:");
    
    while (gap > 1 || trocou) {
        gap = (int)(gap / shrink);
        if (gap < 1) gap = 1;
        
        trocou = 0;
        
        mostrar_gap(v, n, gap, passagem);
        
        printf("\nComparando elementos com distancia %d:\n", gap);
        
        /* Realiza as comparacoes */
        for (int i = 0; i + gap < n; i++) {
            printf("\n+-------------------------------------------------+");
            printf("\n| Comparando posicao %d (%d) com posicao %d (%d)      |", 
                   i, v[i], i + gap, v[i + gap]);
            printf("\n+-------------------------------------------------+");
            
            imprimir_vetor_quadrado(v, n, i, i + gap, 
                "[ ] Elementos sendo comparados:");
            
            if (v[i] > v[i + gap]) {
                printf("\n>>> %d > %d -> PRECISA TROCAR!", v[i], v[i + gap]);
                printf("\n-> Trocando elementos...\n");
                
                imprimir_vetor_quadrado(v, n, i, i + gap,
                    "Antes da troca ([ ] = a trocar):");
                
                trocar(&v[i], &v[i + gap]);
                trocou = 1;
                
                imprimir_vetor_normal(v, n, "Apos a troca:");
            } else {
                printf("\nOK %d <= %d -> mantem posicao", v[i], v[i + gap]);
            }
        }
        
        if (!trocou && gap == 1) {
            printf("\n\n>>> Nenhuma troca necessaria com gap=1!");
            printf("\n>>> Vetor esta ordenado!\n");
        } else {
            printf("\n\nEstado do vetor apos passagem %d:", passagem);
            imprimir_vetor_normal(v, n, "");
        }
        
        passagem++;
        printf("\n---------------------------------------------------\n");
    }
    
    printf("\n+=================================================+");
    printf("\n|              COMBSORT FINALIZADO                |");
    printf("\n+=================================================+");
    imprimir_vetor_normal(v, n, "\nVETOR ORDENADO FINAL:");
}

int main() {
    printf("\n");
    printf("+==================================================+\n");
    printf("|            EXEMPLO: VETOR MAIOR                 |\n");
    printf("+==================================================+\n");
    
    int vetor[] = {8, 4, 3, 7, 6, 5, 2, 1};
    int n = sizeof(vetor) / sizeof(vetor[0]);
    combsort(vetor, n);
    
    printf("\n\n");
    return 0;
}