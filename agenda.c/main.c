#include <stdio.h>
#include <stdlib.h>
FILE* abreArquivo(char caminho [30], char modo){
    FILE *arquivo;
    switch (modo){
    case 'g' :
        arquivo = fopen(caminho, "w");
        break;
    case 'l' :
        arquivo = fopen (caminho, "r");
        break;
    case 'a' :
        arquivo = fopen (caminho, "a");
        break;
    if (arquivo == NULL){
        printf("Nao foi possivel abrir o arquivo.");
        exit(0);
    }
    return arquivo;
    }
}

void fechaArquivo(FILE *arquivo){
    fclose(arquivo);
}

void Cadastro(char nome[30], int telefone){
    FILE *arquivo;
   arquivo = abreArquivo("agenda.txt", 'a');
   fprintf(arquivo, "%s %d\n", nome, telefone);
   fechaArquivo(arquivo);
}

void Listar(){
    FILE *arquivo;
    char nome[30];
    int telefone;
    arquivo = abreArquivo("agenda.txt", 'l');
    while(!feof(arquivo)){
        fscanf(arquivo, "%s %d ", &nome, &telefone);
        printf("Nome: %s - Telefone: %d\n", nome, telefone);
    }
}

int main()
{
    int opcao;
    char nome[30];
    int telefone;
 do {
        system("cls");
    printf("\n\n\t\t|Bem Vindo ao App AGENDA|\n");
    printf("\nMENU");
    printf("\n 1 - Cadastrar Nome e Telefone. ");
    printf("\n 2 - Listar todos os nomes e telefones.");
    printf("\n 3 - Sair.");

    printf("\nDigite uma opcao:");
    scanf("%d", &opcao);
    system("cls");

    switch (opcao){
    case 1 :
        printf("\nDigite o nome: ");
        setbuf(stdin, NULL);
        gets(nome);
        printf("\nDigite o telefone: ");
        scanf("%d", &telefone);
        Cadastro(nome, telefone);
         system("pause");
        break;

    case 2:
        Listar();
        system("pause");
        break;

    case 3:
        printf("\n\nFinalizando...\n\n");
        system("pause");
        exit(0);
        break;

    default :
        printf("Opcao Invalida! Tente Novamente.");
        system("pause");

    }
    }while (opcao != 3);
    return 0;
}
