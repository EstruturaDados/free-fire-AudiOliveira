// Arquivo: sistema_inventario.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a constante para o tamanho máximo do inventário
#define MAX_ITENS 10

// ******************************************************
// Requisito: Criação da struct Item
// Struct para armazenar as informações essenciais de cada item coletado.
// ******************************************************
typedef struct {
    char nome[30];      // Nome do item (ex: Pistola, Munição .45)
    char tipo[20];      // Tipo do item (ex: arma, munição, cura, ferramenta)
    int quantidade;     // Quantidade em posse
} Item;

// ******************************************************
// Variáveis Globais (Representação do Inventário)
// ******************************************************
Item mochila[MAX_ITENS]; // Vetor de structs para armazenar os itens
int totalItens = 0;      // Contador para rastrear o número atual de itens na mochila

// ******************************************************
// Funções de Utilitário
// ******************************************************

/**
 * @brief Função para exibir uma linha de separação para melhorar a usabilidade.
 */
void exibirSeparador() {
    printf("\n============================================\n");
}

/**
 * @brief Função para listar todos os itens atualmente registrados na mochila.
 * * Requisito: Listagem dos itens registrados com seus dados.
 */
void listarItens() {
    exibirSeparador();
    printf("        ESTADO ATUAL DA MOCHILA (%d/%d)      \n", totalItens, MAX_ITENS);
    exibirSeparador();

    if (totalItens == 0) {
        printf("A mochila está vazia. Colete alguns itens!\n");
        exibirSeparador();
        return;
    }

    printf("| %-25s | %-15s | %-10s |\n", "NOME DO ITEM", "TIPO", "QUANTIDADE");
    printf("|---------------------------|-----------------|------------|\n");

    for (int i = 0; i < totalItens; i++) {
        // Uso de nomes de variáveis e campos claros para manutenibilidade
        printf("| %-25s | %-15s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("|---------------------------|-----------------|------------|\n");
}


// ******************************************************
// Funções Obrigatórias
// ******************************************************

/**
 * @brief Função para cadastrar um novo item na mochila.
 * * Requisito: Cadastro de itens (limite de 10).
 */
void inserirItem() {
    // Verifica se a mochila está cheia
    if (totalItens >= MAX_ITENS) {
        printf("\n[ALERTA] Mochila Cheia! Não é possível carregar mais itens.\n");
        return;
    }

    exibirSeparador();
    printf("-> CADASTRAR NOVO ITEM DE LOOT <-\n");
    exibirSeparador();

    // Leitura do Nome
    printf("Nome do Item (max 29 caracteres): ");
    // Limpa o buffer de entrada para evitar problemas com fgets após scanf
    int c; while ((c = getchar()) != '\n' && c != EOF); 
    if (fgets(mochila[totalItens].nome, 30, stdin) == NULL) {
        printf("\n[ERRO] Falha na leitura do nome.\n");
        return;
    }
    // Remove a quebra de linha adicionada por fgets
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0;

    // Leitura do Tipo
    printf("Tipo do Item (ex: arma, munição, cura): ");
    if (scanf("%19s", mochila[totalItens].tipo) != 1) {
        printf("\n[ERRO] Falha na leitura do tipo.\n");
        return;
    }

    // Leitura da Quantidade
    printf("Quantidade: ");
    if (scanf("%d", &mochila[totalItens].quantidade) != 1 || mochila[totalItens].quantidade <= 0) {
        printf("\n[ERRO] Quantidade inválida. Item não cadastrado.\n");
        return;
    }
    
    // Incrementa o contador de itens
    totalItens++; 

    printf("\n[SUCESSO] Item '%s' adicionado à mochila!\n", mochila[totalItens-1].nome);
    listarItens(); // Listagem após a operação (Requisito Funcional)
}

/**
 * @brief Implementa a busca sequencial para localizar um item pelo nome.
 * * @param nomeBusca O nome do item a ser procurado.
 * @return int O índice do item na mochila se encontrado, ou -1 caso contrário.
 * * Requisito: Busca sequencial.
 */
int buscarItemPorNome(const char *nomeBusca) {
    // Uso de laços: 'for' para percorrer o vetor
    for (int i = 0; i < totalItens; i++) {
        // strcasecmp (se disponível) ou strncmp pode ser usado para busca não sensível a maiúsculas/minúsculas
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado no índice i
        }
    }
    return -1; // Item não encontrado
}

/**
 * @brief Função que permite ao jogador buscar e exibir os dados de um item.
 */
void buscarItem() {
    char nomeBusca[30];
    
    exibirSeparador();
    printf("-> BUSCAR ITEM <-\n");
    exibirSeparador();

    if (totalItens == 0) {
        printf("[ALERTA] A mochila está vazia. Nada para buscar.\n");
        return;
    }

    printf("Digite o NOME do item que deseja buscar: ");
    // Limpa o buffer
    int c; while ((c = getchar()) != '\n' && c != EOF); 
    if (fgets(nomeBusca, 30, stdin) == NULL) {
        printf("\n[ERRO] Falha na leitura do nome.\n");
        return;
    }
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove quebra de linha

    // Chamada da função de busca sequencial
    int indice = buscarItemPorNome(nomeBusca); 

    if (indice != -1) {
        printf("\n[SUCESSO] Item Encontrado:\n");
        printf("  Nome: %s\n", mochila[indice].nome);
        printf("  Tipo: %s\n", mochila[indice].tipo);
        printf("  Quantidade: %d\n", mochila[indice].quantidade);
    } else {
        printf("\n[ALERTA] Item '%s' NÃO encontrado na mochila.\n", nomeBusca);
    }
}


/**
 * @brief Função para remover um item da mochila, informando seu nome.
 * * Requisito: Remoção de itens.
 */
void removerItem() {
    char nomeBusca[30];
    
    exibirSeparador();
    printf("-> REMOVER ITEM <-\n");
    exibirSeparador();

    if (totalItens == 0) {
        printf("[ALERTA] A mochila está vazia. Nada para remover.\n");
        return;
    }

    printf("Digite o NOME do item que deseja REMOVER: ");
    // Limpa o buffer
    int c; while ((c = getchar()) != '\n' && c != EOF); 
    if (fgets(nomeBusca, 30, stdin) == NULL) {
        printf("\n[ERRO] Falha na leitura do nome.\n");
        return;
    }
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove quebra de linha

    // Chamada da função de busca sequencial para encontrar o índice
    int indice = buscarItemPorNome(nomeBusca);

    if (indice != -1) {
        // Encontrado. Agora, realiza a remoção (deslocamento)
        
        // Uso de laços: 'for' para deslocar os itens seguintes
        for (int i = indice; i < totalItens - 1; i++) {
            // Desloca o item seguinte para a posição atual
            mochila[i] = mochila[i + 1]; 
        }

        totalItens--; // Decrementa o contador de itens

        printf("\n[SUCESSO] Item '%s' removido da mochila.\n", nomeBusca);
        listarItens(); // Listagem após a operação (Requisito Funcional)
    } else {
        printf("\n[ALERTA] Item '%s' NÃO encontrado na mochila. Nada foi removido.\n", nomeBusca);
    }
}


// ******************************************************
// Função Principal (main)
// ******************************************************

/**
 * @brief Função principal que implementa o menu de interatividade.
 * * Requisito: Usabilidade (interface clara e orientativa).
 */
int main() {
    int opcao;

    printf("BEM-VINDO AO SISTEMA DE INVENTÁRIO (MOCHILA DE LOOT INICIAL)\n");

    // Uso de laços: 'while' para manter o menu ativo até a saída
    while (1) {
        exibirSeparador();
        printf("Escolha uma opção (Total de Itens: %d/%d):\n", totalItens, MAX_ITENS);
        printf("1. Cadastrar Item (Coletar Loot)\n");
        printf("2. Remover Item (Descartar Loot)\n");
        printf("3. Listar Itens (Visualizar Mochila)\n");
        printf("4. Buscar Item (Checar Detalhes)\n");
        printf("0. Sair do Jogo (Fechar Inventário)\n");
        exibirSeparador();
        
        printf("Sua opção: ");
        
        // Leitura de dados: uso de scanf
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada inválida. Tente novamente.\n");
            // Limpa o buffer de entrada
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        // Execução do comando escolhido
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n[FIM] Inventário fechado. Boa sorte na sua missão!\n");
                exibirSeparador();
                return 0; // Sai do programa
            default:
                printf("\n[ALERTA] Opção inválida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}