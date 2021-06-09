#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //p usar funcao para o programa pausar

typedef struct{
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct{
    Produto produto;
    int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrar_produto();
void listar_produtos();
void visualizar_carrinho();
void comprar_produto();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];



int main()
{
    menu();
    return 0;
}

void infoProduto(Produto prod){
    printf("Codigo: %d\nNome: %s\nPreço: R$ %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);

}

void menu(){
    printf("\t============================\n");
    printf("\t=======Bem Vindo(a)=========\n");
    printf("\t=======Shop Soares==========\n");
    printf("\t============================\n");
    printf("Selecione uma opcao abaixo:\n");
    printf("1 - Cadastrar Produtos.\n");
    printf("2 - Listar Produtos.\n");
    printf("3 - Comprar Produtos.\n");
    printf("4 - Visualizar Carrinho.\n");
    printf("5 - Fechar Pedido.\n");
    printf("6 - Sair do Sistema.\n");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao){
        case 1:
            cadastrar_produto();
            break;
        case 2:
            listar_produtos();
            break;
        case 3:
            comprar_produto();
            break;
        case 4:
            visualizar_carrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            printf("Volte Sempre!!\n");
            Sleep(2);
            exit(0);
            break;
        default:
            printf("Opcao Invalida!!\n");
            Sleep(2);
            menu();
            break;
    }
}

void cadastrar_produto(){
    printf("\tCadastro de Produto:\n");
    printf("\t===================\n\n");

    printf("Informe o nome do produto:\n");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("Informe o preco do produto:\n");
    scanf("%f", &produtos[contador_produto].preco);

    printf("O Produto %s foi cadastrado com sucesso.\n",
           strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++;

    Sleep(3);
    menu();

}

void listar_produtos(){
    if(contador_produto > 0){
        printf("Listagem de produtos:\n");
        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("----------------------------------\n");
            Sleep(2);
        }
        Sleep(2);
        menu();
    }else {
        printf("Ainda nao tem produtos na sua lista. Adicione agora:\n\n");
        Sleep(3);
        menu();
    }
}

void visualizar_carrinho(){
    if(contador_carrinho > 0){
       printf("Produtos do Carrinho:\n");
       printf("----------------------------\n");
        for(int i = 0; i < contador_carrinho; i++){
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("----------------------------\n");
            Sleep(1);
        }
        Sleep(2);
        menu();
    }else{
        printf("Nao ha produtos no carrinho'\n");
        printf("----------------------------\n");
        Sleep(2);
        menu();
    }
}

void comprar_produto(){
    if(contador_produto > 0){
        printf("Informe o codigo do produto que deseja adicionar no carrinho:\n");
        printf("\t=============Produtos Disponiveis=================\n");

        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("----------------------------\n");
            Sleep(1);
        }
        int codigo;
        scanf("%d", &codigo);
        getchar();

        int tem_mercado = 0;
        for(int i = 0; i < contador_produto; i++){
            if(produtos[i].codigo == codigo){
                tem_mercado = 1;

                if(contador_carrinho > 0){
                    int * retorno = temNoCarrinho(codigo);

                    if(retorno[0] == 1){
                        carrinho[retorno[1]].quantidade++;
                        printf("Aumentei a quantidade do produto %s ja existente no carrinho.\n",
                               strtok(carrinho[retorno[1]].produto.nome, "\n"));
                        Sleep(2);
                        menu();
                    }else{
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                        Sleep(2);
                        menu();
                    }
                }else{
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                    Sleep(2);
                    menu();
                }
            }
        }
        if(tem_mercado < 1){
           printf("Nao foi encontrado o produto com codigo %d.\n", codigo);
           Sleep(2);
           menu();
        }
    }else{
        printf("Nao ha produtos no carrinho!!\n");
        Sleep(2);
        menu();
    }
}

Produto pegarProdutoPorCodigo(int codigo){
    Produto p;
    for(int i = 0; i < contador_produto; i++){
        if(produtos[i].codigo == codigo){
            p = produtos[i];
        }
    }
    return p;
}

int * temNoCarrinho(int codigo){
    int static retorno[] = {0,0};
    for(int i = 0; i < contador_carrinho; i++){
        if(carrinho[i].produto.codigo == codigo){
        retorno[0] = 1; //significa q tem o produto no carrinho
        retorno[1] = i; //o indice do produto no carrinho
    }
   }
   return retorno;
}

void fecharPedido(){
    if(contador_carrinho > 0){
        float valorTotal = 0.0;
        for(int i = 0; i < contador_carrinho; i++){
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("----------------\n");
            Sleep(1);
        }
        printf("Sua fatura e de R$ %.2f\n", valorTotal);

        //limpa carrinho
        contador_carrinho = 0;
        printf("Obrigado pela preferencia!!!");
        Sleep(5);
        menu();
    }else{
        printf("Nao ha itens no carrinho!!\n");
        Sleep(3);
        menu();
    }
}
