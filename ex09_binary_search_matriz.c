#include <stdio.h>
#define LINHAS 2
#define COLUNAS 3

void preencher_matriz(int matriz[LINHAS][COLUNAS]) {
    int i, j;

    for(i = 0; i < LINHAS; i++) {
        for(j = 0; j < COLUNAS; j++) {
            printf("Insira um valor em [%d][%d]: \n", j, i);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void exibir(int matriz[LINHAS][COLUNAS]) {
    int i, j;

    for(i = 0; i < LINHAS; i++) {
        for(j = 0; j < COLUNAS; j++) {
            printf("%d, ", matriz[i][j]);
        }
        printf("\n");
    }
}

void sort(int matriz[LINHAS][COLUNAS]) {
    int i, j, k, l;

    for(i = 0; i < LINHAS; i++) {
        for(j = 0; j < COLUNAS; j++) {
            for (k = i; k < LINHAS; k++)
            {
                for(l = j; l < COLUNAS; l++) {
                    if (matriz[k][l] < matriz[i][j]) {
                        int aux = matriz[i][j];
                        matriz[i][j] = matriz[k][l];
                        matriz[k][l] = aux;
                    }
                }
            }
            
        }
    }
}

int main() {
    int matriz[LINHAS][COLUNAS];

    preencher_matriz(matriz);
    exibir(matriz);

    sort(matriz);

    printf("--------------------------------");

    exibir(matriz);

    return 0;
}