#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados de uma peça
struct Peca {
    int codigo;
    char descricao[100];
    char marca[50];
    char aplicacao[100];
    int quantidade;
    float preco;
};

// Função para cadastrar uma peça e gravar em um arquivo.txt
void cadastrarPeca() {
    struct Peca p;

    printf("Digite o código do item: ");
    scanf("%d", &p.codigo);
    
    printf("Digite a descrição da peça: ");
    scanf(" %[^\n]", p.descricao);  // Lê a descrição com espaços

    printf("Digite a marca da peça: ");
    scanf(" %[^\n]", p.marca);  // Lê a marca com espaços

    printf("Digite a aplicação da peça: ");
    scanf(" %[^\n]", p.aplicacao);  // Lê a aplicação com espaços

    printf("Digite a quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Digite o preço: ");
    scanf("%f", &p.preco);

    // Abrindo arquivo para gravar os dados
    FILE *arquivo = fopen("cadastro_pecas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Gravando os dados no arquivo
    fprintf(arquivo, "%d\n", p.codigo);
    fprintf(arquivo, "%s\n", p.descricao);
    fprintf(arquivo, "%s\n", p.marca);
    fprintf(arquivo, "%s\n", p.aplicacao);
    fprintf(arquivo, "%d\n", p.quantidade);
    fprintf(arquivo, "%.2f\n", p.preco);

    // Fechando o arquivo
    fclose(arquivo);

    printf("\nPeça cadastrada e gravada no arquivo com sucesso!\n");
}

// Função para alterar uma peça existente
void alterarPeca() {
    int codigoAlvo;
    printf("Digite o código do item que deseja alterar: ");
    scanf("%d", &codigoAlvo);

    FILE *arquivo = fopen("cadastro_pecas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Peca pecas[100]; // Supondo que não vamos alterar mais de 100 peças
    int totalPecas = 0;
    int encontrado = 0;

    // Ler o arquivo e carregar as peças
    while (fscanf(arquivo, "%d\n", &pecas[totalPecas].codigo) != EOF) {
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].descricao);
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].marca);
        fscanf(arquivo, " %[^\n]", pecas[totalPecas].aplicacao);
        fscanf(arquivo, "%d\n", &pecas[totalPecas].quantidade);
        fscanf(arquivo, "%f\n", &pecas[totalPecas].preco);

        if (pecas[totalPecas].codigo == codigoAlvo) {
            encontrado = 1;
            printf("\nPeça encontrada! O que deseja alterar?\n");
            printf("1. Descrição\n");
            printf("2. Marca\n");
            printf("3. Aplicação\n");
            printf("4. Quantidade\n");
            printf("5. Preço\n");
            printf("0. Cancelar\n");

            int opcao;
            printf("Escolha a opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite a nova descrição: ");
                    scanf(" %[^\n]", pecas[totalPecas].descricao);
                    break;
                case 2:
                    printf("Digite a nova marca: ");
                    scanf(" %[^\n]", pecas[totalPecas].marca);
                    break;
                case 3:
                    printf("Digite a nova aplicação: ");
                    scanf(" %[^\n]", pecas[totalPecas].aplicacao);
                    break;
                case 4:
                    printf("Digite a nova quantidade: ");
                    scanf("%d", &pecas[totalPecas].quantidade);
                    break;
                case 5:
                    printf("Digite o novo preço: ");
                    scanf("%f", &pecas[totalPecas].preco);
                    break;
                case 0:
                    printf("Operação cancelada.\n");
                    fclose(arquivo);
                    return;
                default:
                    printf("Opção inválida!\n");
                    fclose(arquivo);
                    return;
            }
        }

        totalPecas++;
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("\nPeça com o código %d não foi encontrada.\n", codigoAlvo);
        return;
    }

    // Abrir o arquivo para reescrever com as alterações
    arquivo = fopen("cadastro_pecas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Reescrevendo todas as peças (inclusive as alteradas)
    for (int i = 0; i < totalPecas; i++) {
        fprintf(arquivo, "%d\n", pecas[i].codigo);
        fprintf(arquivo, "%s\n", pecas[i].descricao);
        fprintf(arquivo, "%s\n", pecas[i].marca);
        fprintf(arquivo, "%s\n", pecas[i].aplicacao);
        fprintf(arquivo, "%d\n", pecas[i].quantidade);
        fprintf(arquivo, "%.2f\n", pecas[i].preco);
    }

    fclose(arquivo);

    printf("\nPeça alterada e arquivo atualizado com sucesso!\n");
}

int main() {
    int opcao;
    
    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Cadastrar peça\n");
        printf("2. Alterar peça\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Implementar função de cadastro se necessário
                break;
            case 2:
                alterarPeca();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}