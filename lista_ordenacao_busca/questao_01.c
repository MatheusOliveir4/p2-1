#include <stdio.h>
#include <stdlib.h>

void ordernarVetor(int *vet, int n) {
    int fim = n - 1;
    int troca;

    do {
        troca = 0;
        for (int i = 0; i < fim; i++)
        {
            if (vet[i] < vet[i+1]) {
                int aux = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = aux;
                troca = 1;
            }
        }

        fim--;

    }while(troca == 1);
}

int buscarValor(int *vet, int n, int valor) {
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int mid = (right + left) / 2;

        if (vet[mid] == valor) {
            return mid;
        }
        else if(vet[mid] < valor) { 
            right = mid-1;
        }
        else {
            left = mid+1;
        }
    }

    return -1;
} 

void preencherVetor(int *vet, int n) {
    for (int i = 0; i < n; i++)
    {
        vet[i] = 1+ (rand() % 10000);
    }
}

void exibirVetor(int *vet, int n) {
    for (int i = 0; i < n; i++)
    {
        printf("%d ", vet[i]);
    }
}

int main() {
    int tam = 5, valor;
    int vet[tam];
    preencherVetor(vet, tam);

    printf("\n");
    exibirVetor(vet, tam);
    
    ordernarVetor(vet, tam);
    printf("\n");
    exibirVetor(vet, tam);

    printf("\nDigite um valor para fazer a busca: ");
    scanf("%d", &valor);

    int indice = buscarValor(vet, tam, valor);

    printf("\nIndice: %d", indice);

    return 0;
}