#include <stdio.h>
#include <stdlib.h>

/*Cria um tabuleiro de jogo da velha, usando uma matriz de caracteres (char) 3x3,
onde o usuário pede o número da linha (1 até 3) e o da coluna (1 até 3).
A cada vez que o usuário entrar com esses dados, colocar um 'X' ou 'O' no local selecionado.
*/
int menu(){
    int opcao;
    printf("Pressione 1 para jogar ou 0 para sair: ");
    scanf("%d", &opcao);
    switch(opcao){
    case 1:
    case 0:
        break;
    default:
        clear();
        printf("Opcao Invalida!!");
    }
    return opcao;
}

void clear(){
    int i = 0;
    while (i != 100){
        putchar('\n');
        i++;
    }
}

void jogar(int tabuleiro [][3]){
    int continua, vez =1;
    zeraTabuleiro(tabuleiro);
    do
        {
        clear();
        exibeTabuleiro(tabuleiro);
        jogada(tabuleiro);
    }while(checaTermino(tabuleiro, vez) != 1);
}

void zeraTabuleiro(int matriz[][3]){
    int i,j;
    for (i=0; i<3; i++){
        for (j=0; j<3; j++)
            matriz[i][j] = 0;
    }
}

void exibeTabuleiro (int tabuleiro[][3]){
    int i, j;
    putchar('\n');

    for(i = 0 ; i < 3 ; i++)
    {
        for(j = 0 ; j < 3 ; j++)
        {
            if(tabuleiro[i][j] == 0)
                printf("    ");
            else
                if(tabuleiro[i][j] == 1)
                    printf("  X ");
                else
                    printf("  O ");

            if(j != (3-1))
                printf("|");
        }
        putchar('\n');
    }
    putchar('\n');
}

int checaLocal(int tabuleiro[][3], int linha, int coluna)
{
    if(linha < 0 || linha > (3-1) || coluna < 0 || coluna > (3-1) || tabuleiro[linha][coluna] != 0)
        return 0;
    else
        return 1;
}

int checaLinha(int tabuleiro[][3])
{
    int linha, coluna,
        soma;

    for(linha = 0 ; linha < 3 ; linha++)
    {
        soma=0;

        for(coluna = 0 ; coluna < 3 ; coluna++)
            soma += tabuleiro[linha][coluna];

        if(soma==3 || soma == (-1)*3)
            return 1;
    }

    return 0;
}

int checaColuna(int tabuleiro[][3])
{
    int linha, coluna,
        soma;


    for(coluna = 0 ; coluna < 3 ; coluna++)
    {
        soma=0;

        for(linha = 0 ; linha < 3 ; linha++)
            soma += tabuleiro[linha][coluna];

        if(soma==3 || soma == (-1)*3)
            return 1;
    }

    return 0;
}

int checaDiagonal(int tabuleiro[][3])
{
    int linha,
        diagonal_principal=0,
        diagonal_secundaria=0;

    for(linha = 0 ; linha < 3 ; linha++)
    {
        diagonal_principal += tabuleiro[linha][linha];
        diagonal_secundaria += tabuleiro[linha][3-linha-1];
    }

    if(diagonal_principal==3 || diagonal_principal==(-1)*3 ||
       diagonal_secundaria==3|| diagonal_secundaria==(-1)*3)
       return 1;

    return 0;
}

int checaEmpate(int tabuleiro[][3])
{
    int linha, coluna;

    for(linha = 0 ; linha < 3 ; linha++)
        for(coluna = 0 ; coluna < 3 ; coluna++)
            if(tabuleiro[linha][coluna] == 0)
                return 0;

    return 1;
}

int checaTermino(int tabuleiro[][3], int vez)
{
    if(checaLinha(tabuleiro))
    {
        printf("Jogo encerrado. Jogador %d venceu !\n\n", (vez%2)+1);
        exibeTabuleiro(tabuleiro);
        return 1;
    }

    if(checaColuna(tabuleiro))
    {
        printf("Jogo encerrado. Jogador %d venceu !\n\n", (vez%2)+1);
        exibeTabuleiro(tabuleiro);
        return 1;
    }

    if(checaDiagonal(tabuleiro))
    {
        printf("Jogo encerrado. Jogador %d venceu !\n\n", (vez%2)+1);
        exibeTabuleiro(tabuleiro);
        return 1;
    }

    if(checaEmpate(tabuleiro))
    {
        printf("Jogo encerrado. Ocorreu um empate! !\n\n");
        exibeTabuleiro(tabuleiro);
        return 1;
    }

    return 0;
}

void jogada(int tabuleiro[][3])
{
    int linha, coluna, vez=1;
    vez++;
    printf("\n--> Jogador %d \n", (vez % 2) + 1);

    do
    {
        printf("Linha: ");
        scanf("%d", &linha);
        linha--;

        printf("Coluna: ");
        scanf("%d", &coluna);
        coluna--;

        if(checaLocal(tabuleiro, linha, coluna) == 0)
            printf("Posicao ocupada ou inexistente, escolha outra.\n");

    } while(checaLocal(tabuleiro, linha, coluna) == 0);

    if(vez%2)
        tabuleiro[linha][coluna] = -1;
    else
        tabuleiro[linha][coluna] = 1;
}


int main()
{
    int continuar, vez;
    int tabuleiro[3][3];

    printf("\n\n =======-------------=======\n");
    printf(" ======|JOGO DA VELHA|======\n");
    printf(" =======-------------=======\n");
    printf("        Vamos jogar?      \n\n");

    do{
        vez = 1;
        continuar = menu();
        if(continuar == 1);
            jogar(tabuleiro);
    }while(continuar);

    return 0;
}
