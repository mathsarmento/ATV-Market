#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct {
    int codigo;
    char descricao[100];
    char marca[50];
    char aplicacao[100];
    float preco;
    int quantidade;
} Peca;

typedef struct {
    char nome[100];
    char endereco[100];
    char telefone[15];
    char email[100];
} Cliente;

void loading() {
    for (int i = 0; i < 100; i++) {
        printf(".");
        fflush(stdout);
        Sleep(15);
    }
    printf("\n");
}

void loadPecas(Peca pecas[100]){
    FILE *arquivo = fopen("cadastro_pecas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Peca p;
    int totalPecas = 0;
    while (fscanf(arquivo, "%d\n", &p.codigo) != EOF) {
        fscanf(arquivo, " %[^\n]", p.descricao);
        fscanf(arquivo, " %[^\n]", p.marca);
        fscanf(arquivo, " %[^\n]", p.aplicacao);
        fscanf(arquivo, "%d\n", &p.quantidade);
        fscanf(arquivo, "%f\n", &p.preco);

        pecas[totalPecas] = p;
        totalPecas++;
    }

    fclose(arquivo);
}

void salvaPecas(Peca pecas[100]) {
    FILE *arquivo = fopen("cadastro_pecas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < 100; i++) {
        if (pecas[i].codigo == 0) {
            break;
        }

        fprintf(arquivo, "%d\n%s\n%s\n%s\n%d\n%.2f\n", pecas[i].codigo, pecas[i].descricao, pecas[i].marca, pecas[i].aplicacao, pecas[i].quantidade, pecas[i].preco);
    }

    fclose(arquivo);
}

int lenPecas(Peca pecas[100]) {
    int i = 0;
    while (pecas[i].codigo != 0) {
        i++;
    }

    return i;
}

void mostrarPeca(Peca p) {
    printf("\nCodigo: %d\nDescricao: %s\nMarca: %s\nAplicacao: %s\nPreco: %.2f\nQuantidade: %d\n\n", 
        p.codigo, p.descricao, p.marca, p.aplicacao, p.preco, p.quantidade);
}

void listarPecas(Peca pecas[100]) {
    int i = 0;

    while (pecas[i].codigo != 0) {
        printf("%d - %s\n", pecas[i].codigo, pecas[i].descricao);
        i++;
    }
}

int checkPeca(Peca pecas[100], int codigo) {
    for (int i = 0; i < 100; i++) {
        if (pecas[i].codigo == codigo) {
            return i + 1;
        }
    }

    return 0;
}

void cadastrarPeca(Peca pecas[100]) {
    Peca p;

    printf("Digite o codigo da peca: ");
    scanf("%d", &p.codigo);

    if (checkPeca(pecas, p.codigo)) {
        printf("Peca com o codigo %d ja cadastrada!\n", p.codigo);
        loading();
        cadastrarPeca(pecas);
        return;
    }

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

    int tamanho = lenPecas(pecas);
    if (tamanho == 100) {
        printf("Limite de pecas atingido!\n");
        return;
    }
    
    pecas[tamanho] = p;
    salvaPecas(pecas);
    printf("\nPeca cadastrada e gravada no arquivo com sucesso!\n");
    loading();
}

void alterarPeca(Peca pecas[100]) {
    int codigoAlvo;
    listarPecas(pecas);
    printf("Digite o codigo do item que deseja alterar: ");
    scanf("%d", &codigoAlvo);

    int index = checkPeca(pecas, codigoAlvo);
    if (!index) {
        printf("Peca com o codigo %d nao encontrada.\n", codigoAlvo);
        return;
    }

    int opcao;
    printf("Peca encontrada! O que deseja alterar?\n\n");
    mostrarPeca(pecas[index - 1]);
    loading();

    printf("\n1. Descricao\n2. Marca\n3. Aplicacao\n4. Preco\n5. Quantidade\n0. Cancelar\n");
    printf("Escolha a opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite a nova descricao: ");
            scanf(" %[^\n]", pecas[index - 1].descricao);
            break;
        case 2:
            printf("Digite a nova marca: ");
            scanf(" %[^\n]", pecas[index - 1].marca);
            break;
        case 3:
            printf("Digite a nova aplicacao: ");
            scanf(" %[^\n]", pecas[index - 1].aplicacao);
            break;
        case 4:
            printf("Digite o novo preco: ");
            scanf("%f", &pecas[index - 1].preco);
            break;
        case 5: 
            printf("Digite a nova quantidade: ");
            scanf("%d", &pecas[index - 1].quantidade);
            break;
        case 0:
            printf("Operacao cancelada.\n");
            return;
        default:
            printf("Opcao invalida!\n");
            return;
    }
    salvaPecas(pecas);
}

void cadastrarCliente() {
    Cliente c;
    FILE *arquivo = fopen("cadastro_clientes.bin", "ab");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", c.nome);
    
    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", c.endereco);
    
    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]", c.telefone);
    
    printf("Digite o email do cliente: ");
    scanf(" %[^\n]", c.email);

    fwrite(&c, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);

    printf("Cliente cadastrado com sucesso!\n");
}

void alterarCliente() {
    char nomeBusca[100];
    int encontrado = 0;

    printf("Digite o nome do cliente que deseja alterar: ");
    scanf(" %[^\n]", nomeBusca);

    FILE *arquivo = fopen("cadastro_clientes.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cliente c;
    long posicao;

    while (fread(&c, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(c.nome, nomeBusca) == 0) {
            encontrado = 1;
            printf("Cliente encontrado!\n");
            printf("Nome: %s\nEndereco: %s\nTelefone: %s\nEmail: %s\n", c.nome, c.endereco, c.telefone, c.email);

            printf("\nDigite os novos dados:\n");
            printf("Digite o novo nome: ");
            scanf(" %[^\n]", c.nome);

            printf("Digite o novo endereco: ");
            scanf(" %[^\n]", c.endereco);

            printf("Digite o novo telefone: ");
            scanf(" %[^\n]", c.telefone);

            printf("Digite o novo email: ");
            scanf(" %[^\n]", c.email);

            // Salvar a posição atual para sobrescrever o cliente
            posicao = ftell(arquivo) - sizeof(Cliente);
            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&c, sizeof(Cliente), 1, arquivo);

            printf("Dados do cliente alterados com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }

    fclose(arquivo);
}

void pesquisarPeca(Peca pecas[100]) {
    int busca;
    listarPecas(pecas);

    printf("Digite o codigo da peca que deseja buscar: ");
    scanf("%d", &busca);

    int index = checkPeca(pecas, busca);

    if (!index) {
        printf("Peca com o codigo %d nao encontrada.\n", busca);
        return;
    }

    mostrarPeca(pecas[index - 1]);
    loading();
}

void comprarPeca(Peca pecas[100]) {
    int codigo;
    int index;

    listarPecas(pecas);
    printf("Digite o codigo da peca que deseja comprar ou 0 para sair: ");
    scanf("%d", &codigo);

    index = checkPeca(pecas, codigo);
    if (!index) {
        printf("Peca com o codigo %d nao encontrada.\n", codigo);
        return;
    }

    int quantidadeDesejada;

    printf("Peca encontrada!\n");
    mostrarPeca(pecas[index - 1]);
    printf("Digite a quantidade que deseja comprar: ");
    scanf("%d", &quantidadeDesejada);

    if (quantidadeDesejada > pecas[index - 1].quantidade) {
        printf("Quantidade insuficiente para compra!\n");
    } else {
        float valorTotal = quantidadeDesejada * pecas[index - 1].preco;
        printf("Valor total da compra: %.2f\n", valorTotal);
        
        char confirmacao;
        printf("Deseja confirmar a compra? (s/n): ");
        scanf(" %c", &confirmacao);
        if (confirmacao == 's' || confirmacao == 'S') {
            pecas[index - 1].quantidade -= quantidadeDesejada;
            printf("Compra realizada com sucesso!");
            salvaPecas(pecas);
        } else {
            printf("Compra cancelada.\n");
        }
    }
}

void menuCliente(Peca pecas[100]) {
    int opcao;
    do {
        printf("\nMenu Cliente\n\n1. Pesquisar Peca\n2. Comprar Peca\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pesquisarPeca(pecas);
                break;
            case 2:
                comprarPeca(pecas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menuAdmin(Peca pecas[100], Cliente clientes[100]) {
    int opcao;
    do {
        printf("\nMenu Admin\n\n1. Cadastrar Peca\n2. Alterar Peca\n3. Pesquisar Peca\n4. Cadastrar Cliente\n5. Alterar Cliente\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        loading();
        
        switch (opcao) {
            case 1:
                cadastrarPeca(pecas);
                break;
            case 2:
                alterarPeca(pecas);
                break;
            case 3:
                pesquisarPeca(pecas);
                break;
            case 4:
                cadastrarCliente(clientes);
                break;
            case 5:
                alterarCliente(clientes);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    int escolha;
    Peca pecas[100];
    Cliente clientes[100];

    loadPecas(pecas);
    int i = 0;
    // while (pecas[i].codigo != 0 || pecas[i].codigo != '\0') {
    //     printf("%d - %s\n", pecas[i].codigo, pecas[i].descricao);
    //     i++;
    // }
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
                    menuAdmin(pecas, clientes);
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
            menuCliente(pecas);
        } else if (escolha == 0) {
            printf("Saindo do programa...\n");
        } else {
            printf("Opcão invalida! Tente novamente.\n");
        }

    } while (escolha != 0);

    return 0;
}
