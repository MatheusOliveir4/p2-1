#include <stdio.h>
#include <string.h>

typedef struct aluno {
    char ra [12];
    char nome [100];
    int faltas;
    float media;
} Aluno;

FILE* prepararArquivo(char* nome) {
    FILE* aux;
    aux = fopen (nome, "r+b");
    if (aux == NULL) {
        aux = fopen (nome, "w+b");
    }
    return aux;
}

void retirarEnter(char* nomeArq) {
    int indice = strlen(nomeArq) - 1;
    if (nomeArq[indice] == '\n') {
        nomeArq[indice] = '\0';
    }
}

void liberarArquivo(FILE* arq, char* nome) {
    int status;
    status = fclose(arq);
    if (status == 0) {
        printf("Arquivo fechado com sucesso!");
    } else {
        printf("Erro ao fechar ao arquivo!");

    }
}

int main() {
    char nomeArq [100];
    FILE* arq;

    Aluno al;
    int i, retorno;

    printf("Informe o nome do arquivo: ");
    fgets(nomeArq, 100, stdin);
    retirarEnter(nomeArq);

    arq = prepararArquivo(nomeArq);

    if (arq == NULL) {
        printf("\nErro ao tentar criar/abrir o arquivo %s", nomeArq);
    } else {
        printf("Gravando dados no arquivo \n");
        fseek(arq, 0, SEEK_END);
        for (i = 0; i < 5; i++)
        {
            printf("Dados dos aluno %d: ", i);
            printf("\nInforme o ra: ");  
            fgets(al.ra, 12, stdin); retirarEnter(nomeArq);

            printf("\nInforme o nome: ");
            fgets(al.nome, 100, stdin); retirarEnter(nomeArq);

            printf("\nInforme a quantidade de faltas: ");
            scanf("%d", &al.faltas); setbuf(stdin, NULL);

            printf("\nInforme a média: ");
            scanf("%f", &al.media); setbuf(stdin, NULL);
            
            retorno = fwrite(&al, sizeof(Aluno), 1, arq);

            if (retorno == 1) {
                printf("\nRegistro gravado com sucesso!");
            } else {
                printf("\nErro ao tentar gravar o registro!");

            }

        }
    }

    return 0;
}