#include <stdio.h>


int main() {
    int num1 = 10, num2 = 20;
    printf("num1 = %d - num2 = %d\n", num1, num2);

    // passando endereço de memória das varíaveis para a funcao troca
    troca(&num1, &num2);

    printf("num1 = %d - num2 = %d\n", num1, num2);
    return 0;
}

//trocando os valores nos endereços de memória passados como argumentos
void troca (int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}