#include <stdio.h>
#include <stdlib.h>

int main () {
    int tam, i;
    int* vetor;

    printf("Informe o tamanho do vetor a ser alocado: ");
    scanf("%d", &tam);

    vetor = (int *) malloc(tam * sizeof(int));

    printf("Preenchimento do vetor \n");

    for(i = 0; i < tam; i++) {
        printf("Informe o valor para a posição %d: ", i);
        scanf("%d", &vetor[i]);
    }

    printf("Valor no vetor \n");
    for(i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
    free(vetor);

    return 0;
} 