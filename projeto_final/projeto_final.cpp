#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct aluno {
  char matricula [30];
  char nome [30];
  char email[30];
  char telefone[9];
  int qnt_disciplinas;
  int status_registro;
} Aluno;

typedef struct disciplina {
  char codigo [7];
  char nome [30];
  char horario [30];
  char sala [30];
	int qnt_vagas_totais;
  int qnt_vagas_ocupadas;
  int status_registro;
} Disciplina;

typedef struct matricula {
  char codigo_disciplina [7];
  char matricula_aluno [30];
  char data_matricula [30];
  int status_registro;
} Matricula;

FILE* prepararArquivo(char* nome) {
  FILE* aux;
  aux = fopen(nome, "r+b");
  if (aux == NULL) {
    aux = fopen(nome, "w+b");
  }
  return aux;
}

void remover_enter(char* texto) {
  int indice = strlen(texto);

  if (texto[indice] == '\n') {
    texto[indice] = '\0';
  } 
}

int consultar_aluno(FILE* arq, char* matricula) {
  if (arq == NULL || matricula == NULL) {
    return -2; 
  }

  Aluno al;
  int indice;

  rewind(arq);

  while (fread(&al, sizeof(Aluno), 1, arq) == 1) {
    if (strcmp(al.matricula, matricula) == 0 && al.status_registro != 0) {
      indice = ftell(arq) - sizeof(Aluno);
      return indice; 
    }
  }

  return -1; 
}

int verificar_nome(char* nome) {
  int len = strlen(nome); 
    for (int i = 0; i < len; i++) {
      if (!(isalpha(nome[i]) || isspace(nome[i]))) {
        return -1; 
      }
    }

  return 0;
}

// FAZER VERIFICAÇÕES
void cadastrar_aluno(FILE* arq) {
  Aluno al;

  printf("Digite a matricula: ");
  fgets(al.matricula, 30, stdin); remover_enter(al.matricula);

  int indice = consultar_aluno(arq, al.matricula); 

  if (indice >= 0) {
    printf("Matricula %s ja existe", al.matricula);
    return;
  }

  printf("Digite o nome: ");
  fgets(al.nome, 30, stdin); remover_enter(al.nome);

  int verificao = verificar_nome(al.nome);

  if (verificao < 0) {
    printf("Formato do nome invalido. O nome deve conter apenas letras e espacos");
    return;
  }

  printf("Digite a e-mail: ");
  fgets(al.email, 30, stdin); remover_enter(al.email);

  printf("Digite o telefone: ");
  fgets(al.telefone, 9, stdin); remover_enter(al.telefone);

  // VERIFICAR TELEFONE
  
  al.qnt_disciplinas = 0;
  al.status_registro = 1;

  fseek(arq, sizeof(Aluno), SEEK_END);
  fwrite(&al, sizeof(Aluno), 1, arq);

  rewind(arq);
}

// AJEITAR 
void alterar_dados(FILE* arq, char* matricula) {
  int indice = consultar_aluno(arq, matricula);

  if (indice < 0) {
    printf("Aluno não encontrado");
  } else {
    Aluno al;
		fseek(arq, indice, SEEK_SET);
    fread(&al, sizeof(Aluno), 1, arq);

    char opcao;
    int alteracao = 0;

    printf("Deseja alterar o nome? (s/n): ");
    scanf("%c", &opcao); getchar();

    if (opcao == 's') {
      printf("Alterar nome: ");
      fgets(al.nome, 30, stdin); remover_enter(al.nome);

      int verificao_nome = verificar_nome(al.nome);

      if (verificao_nome < 0) {
        printf("Formato do nome invalido. O nome deve conter apenas letras e espacos");
        return;
      }

      alteracao = 1;
    }

    printf("Deseja alterar o email? (s/n): ");
    scanf("%c", &opcao); getchar();
    
    if (opcao == 's') {
      printf("Alterar email: ");
      fgets(al.email, 30, stdin); remover_enter(al.email);
      alteracao = 1;
    }

    printf("Deseja alterar o telefone? (s/n): ");
    scanf("%c", &opcao); getchar();
    
    if (opcao == 's') {
      printf("Alterar telefone: ");
      fgets(al.telefone, 9, stdin); remover_enter(al.telefone);
      alteracao = 1;
    }

    if (alteracao == 1) {
      fseek(arq, indice, SEEK_SET);
      fwrite(&al, sizeof(Aluno), 1, arq);
      printf("Aluno de matricula %s alterado com sucesso!", matricula);
    
      return;
    }
    
    printf("Voce nao alterou nenhum dado, portanto nao houve alteracoes!");
  }

  rewind(arq);
}

void exibir_dados(FILE* arq, char* matricula) {
  int indice = consultar_aluno(arq, matricula);

  if (indice < 0) {
    printf("Aluno não encontrado");
  } else {
    Aluno al;
		fseek(arq, indice, SEEK_SET);
    fread(&al, sizeof(Aluno), 1, arq);

    printf("\nAluno: %s", al.nome);
    printf("\nE-mail: %s", al.email);
    printf("\nTelefone: %s", al.telefone);
    printf("\nQuantidade de Disciplinas matriculadas: %d", al.qnt_disciplinas);
    printf("\nStatus: %d", al.status_registro);
  }

  rewind(arq);
}

void remover_aluno(FILE* arq, char* matricula) {
  int indice = consultar_aluno(arq, matricula);

  if (indice < 0) {
    printf("Aluno não encontrado");
  } else {
    Aluno al;
		fseek(arq, indice, SEEK_SET);
    fread(&al, sizeof(Aluno), 1, arq);

    if (al.qnt_disciplinas == 0) {
      al.status_registro = 0;
			fseek(arq, indice, SEEK_SET);
			fwrite(&al, sizeof(Aluno), 1, arq);
      printf("Aluno de matricula %s removido com sucesso!", matricula);
    
		} else {
      printf("Nao foi possivel remover aluno de matricula %s, pois ele esta cadastrado em %d disciplinas", matricula, al.qnt_disciplinas);
    }
  }

  rewind(arq);
}

int consultar_disciplina(FILE* arq, char* cod_disciplina) {
	Disciplina disc;
  int indice;

  rewind(arq);

  while (fread(&disc, sizeof(Disciplina), 1, arq) == 1) {
    if (strcmp(disc.codigo, cod_disciplina) == 0 && disc.status_registro != 0) {
      indice = ftell(arq) - sizeof(Disciplina);
      return indice; 
    }
  }

  return -1; 
}

void cadastrar_disciplina(FILE* arq) {
  Disciplina disc;

  printf("Digite o codigo de disciplina: ");
  fgets(disc.codigo, 7, stdin); remover_enter(disc.codigo);

  int indice = consultar_disciplina(arq, disc.codigo); 

  if (indice >= 0) {
    printf("Codigo de disciplina %s ja existe", disc.codigo);
    return;
  }

  // verificar codigo de disciplina
  printf("Digite o nome: ");
  fgets(disc.nome, 30, stdin); remover_enter(disc.nome);

  int verificao = verificar_nome(disc.nome);

  if (verificao < 0) {
    printf("Nome de disciplina invalio. O nome deve conter apenas letras e espacos");
  }

  printf("Digite o horario da disciplina: ");
  fgets(disc.horario, 30, stdin); remover_enter(disc.horario);

  printf("Digite a sala onde ocorrera a disciplina: ");
  fgets(disc.sala, 30, stdin); remover_enter(disc.sala);
  
	printf("Digite a quantidade de vagas totais da disciplina: ");
	scanf("%d", &disc.qnt_vagas_totais); setbuf(stdin, NULL);

  disc.qnt_vagas_ocupadas = 0;
  disc.status_registro = 1;

  fseek(arq, sizeof(Disciplina), SEEK_END);
  fwrite(&disc, sizeof(Disciplina), 1, arq);

  rewind(arq);
}

void alterar_disciplina(FILE* arq, char* cod_disciplina) {
	int indice = consultar_disciplina(arq, cod_disciplina);

  if (indice < 0) {
    printf("Disciplina não encontrada");
  } else {
    Disciplina disc;
		fseek(arq, indice, SEEK_SET);
    fread(&disc, sizeof(Disciplina), 1, arq);

    char opcao;
    int alteracao = 0;

    printf("Deseja alterar o nome da disciplina? (s/n): ");
    scanf("%c", &opcao); getchar();

    if (opcao == 's') {
      printf("Alterar nome: ");
      fgets(disc.nome, 30, stdin); remover_enter(disc.nome);

      int verificao_nome = verificar_nome(disc.nome);

      if (verificao_nome < 0) {
        printf("Formato do nome invalido. O nome deve conter apenas letras e espacos");
        return;
      }

      alteracao = 1;
    }

    printf("Deseja alterar a sala da disciplina? (s/n): ");
    scanf("%c", &opcao); getchar();

    if (opcao == 's') {
      printf("Alterar sala: ");
      fgets(disc.sala, 30, stdin); remover_enter(disc.sala);

      alteracao = 1;
    }

    printf("Deseja alterar a quantidade de vagas totais da disciplina? (s/n): ");
    scanf("%c", &opcao); getchar();

    if (opcao == 's') {
      printf("Alterar quantidade de vagas totais: ");
      scanf("%d", &disc.qnt_vagas_totais); setbuf(stdin, NULL);

      alteracao = 1;
    }
	
    if (alteracao == 1) {
      fseek(arq, indice, SEEK_SET);
      fwrite(&disc, sizeof(Disciplina), 1, arq);
      
      printf("Disciplina de matricula %s alterada com sucesso!", cod_disciplina);
    } else {
      printf("Nao houve alteracoes");
    }
  }

  rewind(arq);
}

void exibir_disciplina(FILE* arq, char* cod_disciplina) {
  int indice = consultar_disciplina(arq, cod_disciplina);

  printf("%d", indice);

  if (indice < 0) {
    printf("Disciplina não encontrada");

  } else {
    Disciplina disc;
		fseek(arq, indice, SEEK_SET);
    fread(&disc, sizeof(Disciplina), 1, arq);

    printf("\nNome da Disciplina: %s", disc.nome);
    printf("\nHorario: %s", disc.horario);
    printf("\nSala: %s", disc.sala);

    int qnt_vagas_disponiveis = disc.qnt_vagas_totais - disc.qnt_vagas_ocupadas;

    printf("\nQuantidade de vagas disponiveis: %d", qnt_vagas_disponiveis);
    printf("\nStatus: %d", disc.status_registro);
  }

  rewind(arq);
}

void remover_disciplina(FILE* arq, char* cod_disciplina) {
  int indice = consultar_disciplina(arq, cod_disciplina);

  if (indice < 0) {
    printf("Disciplina não encontrada");

  } else {
    Disciplina disc;
		fseek(arq, indice, SEEK_SET);
    fread(&disc, sizeof(Disciplina), 1, arq);

    if (disc.qnt_vagas_ocupadas == 0) {
      disc.status_registro = 0;
			fseek(arq, indice, SEEK_SET);
			fwrite(&disc, sizeof(Disciplina), 1, arq);
      printf("Disciplina de codigo %s removido com sucesso!", cod_disciplina);
    
		} else {
      printf("Nao foi possivel remover disciplina de codigo %s, pois ele tem %d alunos cadastrados na disciplina", cod_disciplina, disc.qnt_vagas_ocupadas);
    }
  }

  rewind(arq);
}

int consultar_matricula(FILE* arq, char* matricula_aluno, char* codigo_disciplina) {
	Matricula mat;
  int indice;

  rewind(arq);

  while (fread(&mat, sizeof(Matricula), 1, arq) == 1) {
    if (mat.status_registro != 0 && strcmp(mat.matricula_aluno, matricula_aluno) == 0 && strcmp(mat.codigo_disciplina, codigo_disciplina) == 0) {
      indice = ftell(arq) - sizeof(Matricula);
      return indice; 
    }
  }

  return -1; 
}

void inclusao_matricula(FILE* arqAlunos, FILE* arqDisciplinas, FILE* arqMatricula) {
  int indice_disc, indice_al;
  
  Matricula mat;
  fseek(arqMatricula, sizeof(Matricula), SEEK_END);

  printf("\nDigite a matricula do aluno: ");
  fgets(mat.matricula_aluno, 30, stdin); remover_enter(mat.matricula_aluno);

  indice_al = consultar_aluno(arqAlunos, mat.matricula_aluno);

  if (indice_al < 0) {
    printf("\nMatricula de aluno digitado nao existe");
    return;
  }

  Aluno al;

  fseek(arqAlunos, indice_al, SEEK_SET);
  fread(&al, sizeof(Aluno), 1, arqAlunos);

  if (al.qnt_disciplinas >= 6) {
    printf("O aluno ja atingiu sua cota maxima de disciplinas cursadas");
    return;
  }

  printf("Digite o codigo de disciplina: ");
  fgets(mat.codigo_disciplina, 7, stdin); remover_enter(mat.codigo_disciplina);

  indice_disc = consultar_disciplina(arqDisciplinas, mat.codigo_disciplina);
  
  if (indice_disc < 0) {
    printf("\nCodigo de disciplina digitado nao existe");
    return;
  } 

  Disciplina disc;

  fseek(arqDisciplinas, indice_disc, SEEK_SET);
  fread(&disc, sizeof(Disciplina), 1, arqDisciplinas);

  int consulta_matricula = consultar_matricula(arqMatricula, al.matricula, disc.codigo);

  if (consulta_matricula >= 0) {
    printf("O aluno de matricula: %s ja esta matriculado na disciplina: %s", al.matricula, disc.codigo);
    return;
  }

  if (disc.qnt_vagas_ocupadas == disc.qnt_vagas_totais) {
    printf("Nao existe mais vaga na disciplina %s", disc.codigo);
    return;
  }

  printf("Digite a data de matricula: ");
  fgets(mat.data_matricula, 30, stdin); remover_enter(mat.data_matricula);

  mat.status_registro = 1;

  al.qnt_disciplinas++;
  disc.qnt_vagas_ocupadas++;

  fseek(arqAlunos, indice_al, SEEK_SET);
  fwrite(&al, sizeof(Aluno), 1, arqAlunos);

  fseek(arqDisciplinas, indice_disc, SEEK_SET);
  fwrite(&disc, sizeof(Disciplina), 1, arqDisciplinas);

  fwrite(&mat, sizeof(Matricula), 1, arqMatricula);

  rewind(arqMatricula);
  rewind(arqAlunos);
  rewind(arqDisciplinas);

  printf("Matricula efetuada!");

}

void exclusao_matricula(FILE* arqAlunos, FILE* arqDisciplinas, FILE* arqMatricula) {
  int indice_disc, indice_al;
  
  Matricula mat;
  fseek(arqMatricula, sizeof(Matricula), SEEK_END);

  printf("\nDigite a matricula do aluno: ");
  fgets(mat.matricula_aluno, 30, stdin); remover_enter(mat.matricula_aluno);

  indice_al = consultar_aluno(arqAlunos, mat.matricula_aluno);

  if (indice_al < 0) {
    printf("\nMatricula de aluno digitado nao existe");
    return;
  }

  Aluno al;

  fseek(arqAlunos, indice_al, SEEK_SET);
  fread(&al, sizeof(Aluno), 1, arqAlunos);

  printf("Digite o codigo de disciplina: ");
  fgets(mat.codigo_disciplina, 7, stdin); remover_enter(mat.codigo_disciplina);

  indice_disc = consultar_disciplina(arqDisciplinas, mat.codigo_disciplina);
  
  if (indice_disc < 0) {
    printf("\nCodigo de disciplina digitado nao existe");
    return;
  } 

  Disciplina disc;

  fseek(arqDisciplinas, indice_disc, SEEK_SET);
  fread(&disc, sizeof(Disciplina), 1, arqDisciplinas);

  int consulta_matricula = consultar_matricula(arqMatricula, al.matricula, disc.codigo);

  if (consulta_matricula < 0) {
    printf("O aluno de matricula: %s nao esta matriculado na disciplina: %s. Portanto, nao e possivel remove-lo dessa disciplina", al.matricula, disc.codigo);
    return;
  }

  mat.status_registro = 0;

  al.qnt_disciplinas--;
  disc.qnt_vagas_ocupadas--;

  // fazer verificações

  fseek(arqAlunos, indice_al, SEEK_SET);
  fwrite(&al, sizeof(Aluno), 1, arqAlunos);

  fseek(arqDisciplinas, indice_disc, SEEK_SET);
  fwrite(&disc, sizeof(Disciplina), 1, arqDisciplinas);

  fwrite(&mat, sizeof(Matricula), 1, arqMatricula);

  rewind(arqMatricula);
  rewind(arqAlunos);
  rewind(arqDisciplinas);

  printf("Exclusão de matricula efetuada!");
}

void menu(FILE* arqAlunos, FILE* arqDisciplinas, FILE* arqMatricula) {
	int opcao = 0;

  do {
    printf("\n-----------MENU-----------");
    printf("\n1. Modulo Alunos");
    printf("\n2. Modulo Disciplinas");
    printf("\n3. Modulo Matricula");
    printf("\n0. SAIR\n");
    
    scanf("%d", &opcao); setbuf(stdin, NULL);

    switch (opcao) {
      case 1:
        printf("\n-----------Modulo Alunos-----------");
        printf("\n1. Cadastrar Novo Aluno");
        printf("\n2. Alterar Dados do Aluno");
        printf("\n3. Exibir Dados do Aluno");
        printf("\n4. Remover Aluno");
        printf("\n8. VOLTAR\n");

        scanf("%d", &opcao); setbuf(stdin, NULL);

        char matricula[30];

        switch (opcao) {
          case 1:
            cadastrar_aluno(arqAlunos);
            break;
          case 2:
            printf("Digite uma matricula p/ alterar: ");
            fgets(matricula, 30, stdin); remover_enter(matricula);
            alterar_dados(arqAlunos, matricula);
            break;
          case 3:
            printf("Digite uma matricula p/ exibir: ");
            fgets(matricula, 30, stdin); remover_enter(matricula);
            exibir_dados(arqAlunos, matricula);
            break;
          case 4:
            printf("Digite uma matricula p/ remover: ");
            fgets(matricula, 30, stdin); remover_enter(matricula);
            remover_aluno(arqAlunos, matricula);
          default:
            break;
        }

				break;
			case 2:
				printf("\n-----------Modulo Disciplinas-----------");
        printf("\n1. Cadastrar Nova Disciplina");
        printf("\n2. Alterar Dados da Disciplina");
        printf("\n3. Exibir Dados da Disciplina");
        printf("\n4. Remover Disciplina\n");
				
        scanf("%d", &opcao); setbuf(stdin, NULL);

        char cod_disciplina[30];

				switch (opcao) {
          case 1:
            cadastrar_disciplina(arqDisciplinas);
            break;
          case 2:
            printf("Digite um codigo de disciplina p/ alterar: ");
            fgets(cod_disciplina, 7, stdin); remover_enter(cod_disciplina);
            alterar_disciplina(arqDisciplinas, cod_disciplina);
            break;
          case 3:
            printf("Digite um codigo de disciplina p/ exibir: ");
            fgets(cod_disciplina, 7, stdin); remover_enter(cod_disciplina);
            exibir_disciplina(arqDisciplinas, cod_disciplina);
            break;
          case 4:
            printf("Digite um codigo de disciplina p/ remover: ");
            fgets(cod_disciplina, 7, stdin); remover_enter(cod_disciplina);
            remover_disciplina(arqDisciplinas, cod_disciplina);
          default:
            break;
        }
				break;
			case 3:
        printf("\n-----------Modulo Matricula-----------");
        printf("\n1. Inclusao de Matricula");
        printf("\n2. Exclusao de Matricula\n");
				
        scanf("%d", &opcao); setbuf(stdin, NULL);

        switch (opcao)
        {
        case 1:
          inclusao_matricula(arqAlunos, arqDisciplinas, arqMatricula);
          break;
        case 2:
          exclusao_matricula(arqAlunos, arqDisciplinas, arqMatricula);
          break;
        default:
          break;
        }
				break;
			default:
				break;
			}
  } while(opcao != 0);
}

int main() {
  FILE* arqAlunos = prepararArquivo("Alunos");
  FILE* arqDisciplinas = prepararArquivo("Disciplinas");
  FILE* arqMatricula = prepararArquivo("Matricula");

  if(!arqAlunos || !arqDisciplinas || !arqMatricula ) {
    printf("Erro ao tentar abrir o arquivo");
  } else {
    menu(arqAlunos, arqDisciplinas, arqMatricula);
  }

  // remover fisicamente os registros com status 0

  fclose(arqAlunos);
  fclose(arqDisciplinas);
  fclose(arqMatricula);

  return 0;
}