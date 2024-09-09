#include <stdio.h>
#define TAM 10

int buscaMelhorada (int* vet, int quant, int valor) {
    int i, retorno = -1;
    if (quant == 0) {
        return -2;
    }
    else {
        for (i = 0; i < quant; i++)
        {
            if (vet[i] >= valor) {
                retorno = i;
                break;
            }            
        }
        return retorno;
    }
}

void inserir(float* vet, int* quant, float valor) {
    int retorno, i;
    if (*quant == TAM) {
        printf("Vetor cheio! Inserção não realizada! \n");
    }
    else {
        retorno = buscaMelhorada(vet, *quant, valor);
        if (retorno != -2) {
            vet[0] = valor;
            *quant = *quant + 1;
            printf("Valor inserido! \n");
        }
        else if (retorno == -1){
            vet[*quant] = valor;
            *quant = *quant + 1;
            printf ("Valor inserido! \n");
        }
        else {
            if (vet[retorno] == valor) {
                printf("Valor repetido! Inserção não efetuada!");
            }
            else {
                for (i = quant; i > retorno; i--)
                {   
                    vet[i] = vet[i-1];
                }
                vet[retorno] = valor;
                *quant = *quant + 1;
                printf("Valor inserido! \n");
            }
        }
    }
}

void exibir (int* vet, int quant) {
    int i;
    if (quant == 0) {
        printf("Vetor vazio! \n");
    }
    else {
        for (i = 0; i < quant; i++)
        {
            printf("%d ", vet[i]);
        }
        printf("\n");
    }
}
