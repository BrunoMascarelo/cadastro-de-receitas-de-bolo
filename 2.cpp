#include <stdio.h>  // Biblioteca padr�o para entrada e sa�da (ex: printf, scanf)

#define MAX 100  // Define o n�mero m�ximo de cadastros permitidos

// Estrutura que representa uma receita com c�digo, sabor do bolo e quantas por��es
struct Bolo {
    int codigo;
    char sabor[50];  // String de at� 49 caracteres + 1 para o caractere '\0' de finaliza��o
    int porcoes;
};

// Vetor que armazena at� 100 bolos
struct Bolo bolo[MAX];
// Vari�vel que armazena quantas receitas j� foram cadastradas
int qtd = 0;

// Fun��o que cadastra uma nova receita
void cadastrar() {
    // Verifica se o limite de cadastros foi atingido
    if (qtd >= MAX) {
        printf("\nLimite de receitas atingido (%d cadastros)!\n", MAX);
        return; // Encerra a fun��o
    }

    printf("\n--- NOVO CADASTRO ---\n");

    // Pede os dados da receita: c�digo, sabor do bolo e quantas por��es
    printf("Codigo: ");
    scanf("%d", &bolo[qtd].codigo);
    while (getchar() != '\n'); // Limpa o "lixo" do buffer do teclado

    printf("Sabor: ");
    scanf(" %49[^\n]", bolo[qtd].sabor); // L� at� 49 caracteres com espa�os

    printf("Quantidade de por��es: ");
    scanf("%d", &bolo[qtd].porcoes);

    // Aumenta o n�mero de receitas cadastradas
    qtd++;

    printf("\nCadastro realizado com sucesso!\n");
}

// Fun��o que busca uma receita pelo c�digo informado
int buscarPorCodigo(int codigo) {
    int i;
    for (i = 0; i < qtd; i++) {
        if (bolo[i].codigo == codigo) {
            return i; // Retorna o �ndice da receita no vetor
        }
    }
    return -1; // Retorna -1 se n�o encontrou
}

// Fun��o que edita os dados de uma receita
void editar() {
    int codigo, index;

    printf("\n--- EDITAR CADASTRO ---\n");
    printf("Digite o c�digo da receita: ");
    scanf("%d", &codigo);

    // Procura a receita com o c�digo digitado
    index = buscarPorCodigo(codigo);

    // Se n�o encontrar, avisa e retorna
    if (index == -1) {
        printf("\nReceita n�o encontrada!\n");
        return;
    }

    // Mostra os dados atuais
    printf("\nEDITANDO CADASTRO:\n");
    printf("Codigo: %d\n", bolo[index].codigo);
    printf("Sabor do bolo: %s\n", bolo[index].sabor);
    printf("Quantidade de por��es: %d\n\n", bolo[index].porcoes);

    // Pede os novos dados
    printf("Novo sabor do bolo: ");
    scanf(" %49[^\n]", bolo[index].sabor);

    printf("Nova quantidade de por��es: ");
    scanf("%d", &bolo[index].porcoes);

    printf("\nCadastro atualizado com sucesso!\n");
}

// Fun��o que exclui uma receita do sistema
void excluir() {
    int codigo, index;
    char confirmacao;

    printf("\n--- EXCLUIR CADASTRO ---\n");
    printf("Digite o c�digo da receita: ");
    scanf("%d", &codigo);

    index = buscarPorCodigo(codigo);

    if (index == -1) {
        printf("\nReceita n�o encontrada!\n");
        return;
    }

    // Mostra os dados da receita e pede confirma��o
    printf("\nCONFIRMAR EXCLUS�O:\n");
    printf("Codigo: %d\n", bolo[index].codigo);
    printf("Sabor do bolo: %s\n", bolo[index].sabor);
    printf("Quantidade de por��es: %d\n", bolo[index].porcoes);

    printf("\nTem certeza que deseja excluir? (s/n): ");
    scanf(" %c", &confirmacao);

    // Se confirmar, remove a receita do vetor e ajusta a quantidade
    if (confirmacao == 's' || confirmacao == 'S') {
        int i;
        for (i = index; i < qtd - 1; i++) {
            bolo[i] = bolo[i + 1]; // Desloca os dados para "tapar o buraco"
        }
        qtd--; // Diminui a quantidade total
        printf("\nCadastro exclu�do com sucesso!\n");
    } else {
        printf("\nOpera��o cancelada.\n");
    }
}

// Fun��o que lista todas as receitas cadastradas
void listar() {
    printf("\n--- RECEITAS CADASTRADAS ---\n");
    printf("Total: %d\n\n", qtd);

    if (qtd == 0) {
        printf("Nenhuma receita cadastrada.\n");
        return;
    }

    // Cabe�alho da tabela
    printf("CODIGO  SABOR DO BOLO%-42s QUANTIDADE DE POR��ES\n", "");
    printf("--------------------------------------------------\n");

    // Mostra os dados de cada receita
    int i;
    for (i = 0; i < qtd; i++) {
        printf("%-8d%-45s%d\n",
               bolo[i].codigo,
               bolo[i].sabor,
               bolo[i].porcoes);
    }
}

// Fun��o principal (ponto de entrada do programa)
int main() {
    int op;

    printf("\n----------------------------------------");
    printf("\n    SISTEMA DE CADASTRO DE RECEITAS");
    printf("\n----------------------------------------\n");

    // Loop principal do menu
    do {
        printf("\n----------- MENU PRINCIPAL -----------\n");
        printf("1. Cadastrar nova receita\n");
        printf("2. Listar todas as receitas cadastradas\n");
        printf("3. Editar cadastro existente\n");
        printf("4. Excluir cadastro\n");
        printf("0. Sair do sistema\n");
        printf("--------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &op);
        while (getchar() != '\n'); // Limpa o buffer do teclado

        // Executa a op��o escolhida
        switch (op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 0: printf("\nEncerrando sistema...\n"); break;
            default: printf("\nOp��o inv�lida! Tente novamente.\n");
        }

    } while (op != 0); // Repete at� o usu�rio escolher sair

    printf("\nObrigado por utilizar o sistema!\n");
    return 0; // Finaliza o programa
}
