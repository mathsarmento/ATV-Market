#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados de uma peca
struct Peca {
    int codigo;
    char descricao[100];
    char marca[50];
    char aplicacao[100];
    float preco;
    int quantidade; // A quantidade sera exibida apenas no terminal
};

// Funcão para cadastrar uma peca e gravar em um arquivo.txt
void cadastrarPeca() {
    struct Peca p;

    printf("Digite o codigo do item (Somente numeros): ");
    scanf("%d", &p.codigo);
    

    printf("Digite a descricao da peca: ");
    scanf(" %[^\n]", p.descricao);

    printf("Digite a marca da peca: ");
    scanf(" %[^\n]", p.marca);

    printf("Digite a aplicacao da peca: ");
    scanf(" %[^\n]", p.aplicacao);

    printf("Digite a quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Digite o preco: ");
    scanf("%f", &p.preco);

    FILE *arquivo = fopen("cadastro_pecas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%d\n%s\n%s\n%s\n%d\n%.2f\n", p.codigo, p.descricao, p.marca, p.aplicacao, p.quantidade, p.preco);
    fclose(arquivo);

    printf("\nPeca cadastrada e gravada no arquivo com sucesso!\n");
}

// Funcão para alterar uma peca existente
void alterarPeca() {
    int codigoAlvo;
    printf("Digite o codigo do item que deseja alterar: ");
    scanf("%d", &codigoAlvo);

    FILE *arquivo = fopen("cadastro_pecas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Peca pecas[100];
    int totalPecas = 0;
    int encontrado = 0;

    while (fscanf(arquivo, "%d\n", &pecas[totalPecas].codigo) != EOF) {
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].descricao);
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].marca);
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].aplicacao);
        fscanf(arquivo, "%d\n", &pecas[totalPecas].quantidade);
        fscanf(arquivo, "%f\n", &pecas[totalPecas].preco);

        if (pecas[totalPecas].codigo == codigoAlvo) {
            encontrado = 1;
            printf("\nPeca encontrada! O que deseja alterar?\n");
            printf("1. Descricao\n2. Marca\n3. Aplicacao\n4. Preco\n5. Quantidade\n0. Cancelar\n");

            int opcao;
            printf("Escolha a opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite a nova descricao: ");
                    scanf(" %[^\n]", pecas[totalPecas].descricao);
                    break;
                case 2:
                    printf("Digite a nova marca: ");
                    scanf(" %[^\n]", pecas[totalPecas].marca);
                    break;
                case 3:
                    printf("Digite a nova aplicacao: ");
                    scanf(" %[^\n]", pecas[totalPecas].aplicacao);
                    break;
                case 4:
                    printf("Digite o novo preco: ");
                    scanf("%f", &pecas[totalPecas].preco);
                    break;
                case 5: 
                    printf("Digite a nova quantidade: ");
                    scanf("%d", &pecas[totalPecas].quantidade);
                    break;
                case 0:
                    printf("Operacao cancelada.\n");
                    fclose(arquivo);
                    return;
                default:
                    printf("Opcao invalida!\n");
                    fclose(arquivo);
                    return;
            }
        }

        totalPecas++;
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("\nPeca com o codigo %d nao foi encontrada.\n", codigoAlvo);
        return;
    }

    arquivo = fopen("cadastro_pecas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < totalPecas; i++) {
        fprintf(arquivo, "%d\n%s\n%s\n%s\n%d\n%.2f\n", pecas[i].codigo, pecas[i].descricao, pecas[i].marca, pecas[i].aplicacao, pecas[i].quantidade, pecas[i].preco);
    }

    fclose(arquivo);

    printf("\nPeca alterada e arquivo atualizado com sucesso!\n");
}

// Funcão para pesquisar uma peca pelo nome e exibir o preco e código
void pesquisarPeca() {
    char busca[100];
    printf("Digite o nome ou descricao da peca que deseja buscar: ");
    scanf(" %[^\n]", busca);

    FILE *arquivo = fopen("cadastro_pecas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Peca p;
    int encontrado = 0;
    while (fscanf(arquivo, "%d\n", &p.codigo) != EOF) {
        fscanf(arquivo, " %[^\n]", p.descricao);
        fscanf(arquivo, " %[^\n]", p.marca);
        fscanf(arquivo, " %[^\n]", p.aplicacao);
        fscanf(arquivo, "%d\n", &p.quantidade); 
        fscanf(arquivo, "%f\n", &p.preco);

        if (strstr(p.descricao, busca) != NULL) {
            encontrado = 1;
            printf("\nPeca encontrada:\nCodigo: %d\nDescricao: %s\nPreco: %.2f\nQuantidade: %d\n", p.codigo, p.descricao, p.preco, p.quantidade);
            break; // Para a pesquisa após encontrar a primeira peca
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("\nPeca nao encontrada.\n");
    }
}

// Funcão para comprar uma peca
void comprarPeca() {
    char busca[100];
    printf("Digite o nome ou descricao da peca que deseja comprar: ");
    scanf(" %[^\n]", busca);

    FILE *arquivo = fopen("cadastro_pecas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Peca pecas[100];
    int totalPecas = 0;
    int encontrado = 0;

    while (fscanf(arquivo, "%d\n", &pecas[totalPecas].codigo) != EOF) {
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].descricao);
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].marca);
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].aplicacao);
        fscanf(arquivo, "%d\n", &pecas[totalPecas].quantidade);
        fscanf(arquivo, "%f\n", &pecas[totalPecas].preco);
        totalPecas++;
    }

    fclose(arquivo);

    // Buscar pela peca
    for (int i = 0; i < totalPecas; i++) {
        if (strstr(pecas[i].descricao, busca) != NULL) {
            encontrado = 1;
            printf("\nPeca encontrada:\nCodigo: %d\nDescricao: %s\nPreco: %.2f\nQuantidade disponível: %d\n", 
                pecas[i].codigo, pecas[i].descricao, pecas[i].preco, pecas[i].quantidade);

            int quantidadeDesejada;
            printf("Digite a quantidade que deseja comprar: ");
            scanf("%d", &quantidadeDesejada);

            if (quantidadeDesejada > pecas[i].quantidade) {
                printf("Quantidade insuficiente para compra!\n");
            } else {
                // Calcular o valor total
                float valorTotal = quantidadeDesejada * pecas[i].preco;
                printf("Valor total da compra: %.2f\n", valorTotal);
                
                char confirmacao;
                printf("Deseja confirmar a compra? (s/n): ");
                scanf(" %c", &confirmacao);

                if (confirmacao == 's' || confirmacao == 'S') {
                    pecas[i].quantidade -= quantidadeDesejada; // Diminui a quantidade
                    printf("Compra realizada com sucesso!");
                } else {
                    printf("Compra cancelada.\n");
                }
            }
            break; // Para após encontrar a primeira peca correspondente
        }
    }

    // Reescreve o arquivo com as quantidades atualizadas
    arquivo = fopen("cadastro_pecas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < totalPecas; i++) {
        fprintf(arquivo, "%d\n%s\n%s\n%s\n%d\n%.2f\n", pecas[i].codigo, pecas[i].descricao, pecas[i].marca, pecas[i].aplicacao, pecas[i].quantidade, pecas[i].preco);
    }

    fclose(arquivo);
}


// Menu para o cliente
void menuCliente() {
    int opcao;
    do {
        printf("\nMenu Cliente\n1. Pesquisar Peca\n2. Comprar Peca\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pesquisarPeca();
                break;
            case 2:
                comprarPeca();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Menu para o administrador
void menuAdmin() {
    int opcao;
    do {
        printf("\nMenu Admin\n1. Cadastrar Peca\n2. Alterar Peca\n3. Pesquisar Peca\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPeca();
                break;
            case 2:
                alterarPeca();
                break;
            case 3:
                pesquisarPeca();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcão invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    int escolha;

    do {
        printf("Escolha o tipo de usuario:\n1. Admin\n2. Cliente\n0. Sair\nOpcao: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            char senhaAdmin[20];
            int tentativas = 3;

            while (tentativas > 0) {
                printf("Digite a senha do administrador: ");
                scanf("%s", senhaAdmin);

                if (strcmp(senhaAdmin, "admin123") == 0) {
                    menuAdmin();
                    break;
                } else {
                    tentativas--;
                    if (tentativas > 0) {
                        printf("Senha incorreta! Tente novamente. Tentativas restantes: %d\n", tentativas);
                    } else {
                        printf("Numero maximo de tentativas alcancado.\n");
                    }
                }
            }
        } else if (escolha == 2) {
            menuCliente();
        } else if (escolha == 0) {
            printf("Saindo do programa...\n");
        } else {
            printf("Opcão invalida! Tente novamente.\n");
        }

    } while (escolha != 0);

    return 0;
}