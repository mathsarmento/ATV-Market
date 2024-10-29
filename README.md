# Gerenciamento de Loja de Peças e Clientes

Este programa em C é destinado ao gerenciamento de uma loja de peças de automóveis, permitindo o cadastro, alteração, pesquisa e compra de peças, bem como o cadastro e modificação de clientes. Ele também inclui funcionalidades de controle para usuários administradores e clientes.

## Funcionalidades

### Para Administradores
1. **Cadastrar Peça:** Permite o registro de novas peças no inventário, com dados como código, descrição, marca, aplicação, preço e quantidade.
2. **Alterar Peça:** Modifica informações já cadastradas de uma peça, incluindo descrição, marca, aplicação, preço e quantidade.
3. **Pesquisar Peça:** Exibe as informações de uma peça específica.
4. **Cadastrar Cliente:** Armazena informações de um novo cliente, como nome, endereço, telefone e email.
5. **Alterar Cliente:** Permite modificar as informações já cadastradas de um cliente.
6. **Autenticação:** Acesso controlado ao menu do administrador com verificação de senha.

### Para Clientes
1. **Pesquisar Peça:** Visualiza as informações detalhadas de uma peça específica.
2. **Comprar Peça:** Realiza a compra de uma peça, atualizando a quantidade disponível em estoque.

### Estrutura do Código

- **Struct `Peca`**: Armazena informações da peça, incluindo código, descrição, marca, aplicação, preço e quantidade.
- **Struct `Cliente`**: Armazena dados pessoais do cliente, como nome, endereço, telefone e email.
- **Funções Principais**:
  - `cadastrarPeca` e `alterarPeca`: Cadastra e edita informações das peças no inventário.
  - `cadastrarCliente` e `alterarCliente`: Cadastra e edita dados dos clientes.
  - `pesquisarPeca` e `comprarPeca`: Permitem ao cliente pesquisar e comprar peças.
  - `menuCliente` e `menuAdmin`: Oferecem as opções de funcionalidades para cada tipo de usuário.

## Arquivos Utilizados

- **`cadastro_pecas.txt`**: Armazena as informações das peças em texto, sendo utilizado para carregar e salvar os dados das peças no programa.
- **`cadastro_clientes.bin`**: Armazena os dados dos clientes em formato binário.

## Pré-Requisitos

- **Compilador C** (gcc, clang, etc.)
- **Sistema Operacional Windows** (Uso da função `Sleep` da biblioteca `<windows.h>`)
- **Editor de Texto** para criação e edição de arquivos de dados `cadastro_pecas.txt` e `cadastro_clientes.bin`.

## Instruções de Uso

1. **Compilação**:
   Compile o código com um compilador de C:
   ```bash
   gcc main.c -o main.exe
   
---

## Operação no Terminal

Após iniciar o programa, você verá um menu principal que oferece duas opções de acesso:

1. **Cliente**
2. **Administrador**

Escolha a opção desejada digitando o número correspondente e pressionando Enter.

---

### 1. Menu do Cliente

Este menu oferece funcionalidades básicas para os clientes:

- **Pesquisar Peça**: O cliente pode pesquisar uma peça pelo código. As informações detalhadas da peça serão exibidas.
- **Comprar Peça**: Permite que o cliente compre uma peça específica, atualizando a quantidade em estoque.

#### Exemplo de Uso para Clientes:

1. Digite o código da peça que deseja pesquisar e visualize os detalhes, como preço e quantidade em estoque.
2. Para realizar a compra, insira o código da peça e a quantidade desejada. Se houver estoque suficiente, a quantidade será atualizada.

---

## 2. Menu do Administrador

Para acessar o menu do administrador, você precisará inserir uma senha. Esse menu permite o gerenciamento completo de peças e clientes, com opções adicionais de cadastro e edição.

## Funcionalidades do Administrador:

- **Cadastrar Peça**: Insira o código, descrição, marca, aplicação, quantidade e preço da nova peça. O sistema salvará essas informações automaticamente.
- **Alterar Peça**: Digite o código da peça que deseja alterar. Em seguida, escolha o campo (descrição, marca, aplicação, preço ou quantidade) para atualizar.
- **Pesquisar Peça**: Similar ao menu do cliente, exibe as informações detalhadas de uma peça pelo código.
- **Cadastrar Cliente**: Permite inserir os dados do cliente, incluindo nome, endereço, telefone e email.
- **Alterar Cliente**: Digite o nome do cliente a ser alterado e escolha o campo a ser atualizado.

## Exemplo de Uso para Administradores:

1. Para cadastrar uma nova peça, selecione a opção correspondente, insira todas as informações solicitadas e confirme.
2. Para alterar uma peça, escolha a opção de alteração, insira o código da peça e selecione o campo a ser atualizado.

---

## Observações Adicionais

- O arquivo **`cadastro_pecas.txt`** será atualizado automaticamente sempre que uma peça for cadastrada ou alterada.
- **Senha de Administrador**: Certifique-se de definir e lembrar a senha do administrador para acesso seguro.
- **Limites**: O sistema suporta até 100 peças no inventário.

--- 
