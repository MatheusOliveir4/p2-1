#include <stdio.h>

int main() {
    float preco_produto, desconto;

    printf("Informe o preço de um produto: ");
    scanf("%f", &preco_produto);

    printf("\nInforme o desconto que será aplicado: ");
    scanf("%f", &desconto);

    float preco_produto_total = preco_produto - preco_produto * desconto;

    printf("\nPreço real do produto: %f", preco_produto);
    printf("\nQuanto você estará pagando pelo produto: %f", preco_produto_total); 
    printf("\nQuanto você está economizando: %f", preco_produto - preco_produto_total); 

    return 0;
}