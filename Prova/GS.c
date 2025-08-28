

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de cadastro
struct cadastro{
    char nome[50];            // Nome do usuário
    char RG[11];              // RG (Registro Geral) com até 10 dígitos + '\0'
    char CPF[15];             // CPF com até 14 caracteres (com pontos e traços)
    char email[50];           // Email do usuário
    char geologicas[50], meteorologicas[50]; // Campos reservados (não usados no código atual)
};

// Definição da estrutura de relatos (acidentes/catástrofes)
struct relatos{
    char tipo[50];            // Tipo do acidente (ex: Terremoto, Furacão)
    char localizacao[100];    // Local onde ocorreu o acidente
    int dia, mes, ano;        // Data do acidente
    int hora, minuto;         // Hora do acidente
};

// Função de comparação para ordenação do vetor de relatos por tipo (ordem alfabética)
int compararTipo(const void *a, const void *b) {
    const struct relatos *acidente1 = (const struct relatos *)a;
    const struct relatos *acidente2 = (const struct relatos *)b;
    return strcmp(acidente1->tipo, acidente2->tipo);
}

int main(){

    // Aloca memória dinamicamente para o cadastro de um usuário
    struct cadastro *cad = malloc(sizeof(struct cadastro));
    if (cad == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1; // Sai se não conseguir alocar memória
    }

    // Registro dos dados do usuário
    printf("--------Registro de Cadastro--------\n");

    // Entrada do nome com fgets para ler linha completa e remover '\n'
    printf("Digite o nome: ");
    fgets(cad->nome, sizeof(cad->nome), stdin);
    cad->nome[strcspn(cad->nome, "\n")] = 0;  // Remove o caractere de nova linha

    // Entrada do RG com scanf e validação de tamanho (9 ou 11 caracteres)
    printf("Digite o RG: ");
    scanf("%11s", cad->RG);
    getchar(); // Limpa o '\n' que ficou no buffer
    while (strlen(cad->RG) != 11 && strlen(cad->RG) != 9) {
        printf("RG invalido. Digite novamente: ");
        scanf("%11s", cad->RG);
        getchar();
    }

    // Entrada do CPF com scanf e validação de tamanho (11 ou 14 caracteres)
    printf("Digite o CPF: ");
    scanf("%15s", cad->CPF);
    getchar();
    while (strlen(cad->CPF) != 14 && strlen(cad->CPF) != 11) {
        printf("CPF invalido. Digite novamente: ");
        scanf("%15s", cad->CPF);
        getchar();
    }

    // Entrada do email com scanf (sem espaços)
    printf("Digite o email: ");
    scanf("%50s", cad->email);
    getchar();

    int opcao = 0;

    // Loop do menu principal, que só termina se o usuário digitar 3 para sair
    while (opcao != 3){
        printf("\n------------Menu Principal----------\n");
        printf("1. tipos de catastrofes\n");
        printf("2. registros de catastrofes\n");
        printf("3. Sair\n");
        printf("Digite a opcao: ");
        scanf("%d", &opcao);
        getchar();

        // Opção 1: mostrar os tipos de catástrofes
        if (opcao == 1){
            printf("--------Tipos de Catastrofes--------\n");

            // Catástrofes geológicas
            printf("Geologicas\n\n");
            char geologicas[4][50] = {"Terremoto", "Tsunami", "Erupcao Vulcanica", "Deslizamento de Terra"};
            for (int i = 0; i < 4; i++) {
                printf("%d. %s\n", i + 1, geologicas[i]);
            }

            printf("----------------------------------\n");

            // Catástrofes meteorológicas
            printf("Meteorologicas\n\n");
            char meteorologicas[5][50] = {"Furacao", "Tornado", "Tempestade", "Inundacao", "secas"};
            for (int i = 0; i < 5; i++) {
                printf("%d. %s\n", i + 1, meteorologicas[i]);
            }

        // Opção 2: registrar acidentes/catástrofes
        } else if (opcao == 2){
            printf("--------Registro de Acidente--------\n");
            int N = 0;

            // Pergunta quantos acidentes o usuário quer registrar, garante que N > 0
            while (N <= 0){
                printf("Quantos acidentes deseja registrar? ");
                scanf("%d", &N);
                getchar();
            }

            // Aloca memória para N relatos
            struct relatos *rel = malloc(N * sizeof(struct relatos));
            if (rel == NULL) {
                printf("Erro ao alocar memoria.\n");
                return 1; // Sai se não conseguir alocar
            }

            // Para cada acidente, lê os dados
            for (int i = 0; i < N; i++){

                // Tipo do acidente (com fgets para poder ler espaços)
                printf("Digite o tipo de acidente %d: ", i + 1);
                fgets(rel[i].tipo, sizeof(rel[i].tipo), stdin);
                rel[i].tipo[strcspn(rel[i].tipo, "\n")] = 0; // Remove '\n'

                // Localização do acidente
                printf("Digite a localizacao do acidente %d: ", i + 1);
                fgets(rel[i].localizacao, sizeof(rel[i].localizacao), stdin);
                rel[i].localizacao[strcspn(rel[i].localizacao, "\n")] = 0;

                // Hora do acidente
                printf("Digite a hora do acidente %d (formato HH MM): ", i + 1);
                scanf("%d %d", &rel[i].hora, &rel[i].minuto);
                getchar();

                // Valida hora e minuto
                while (rel[i].hora < 0 || rel[i].hora > 23 || rel[i].minuto < 0 || rel[i].minuto > 59) {
                    printf("Hora invalida. Digite novamente (formato 24h): ");
                    scanf("%d %d", &rel[i].hora, &rel[i].minuto);
                    getchar();
                }

                // Data do acidente
                printf("Quando for colocar a data, Coloque assim: (formato dd mm aaaa)\n");
                printf("Digite a data %d: ", i + 1);
                scanf("%d %d %d", &rel[i].dia, &rel[i].mes, &rel[i].ano);
                getchar();

                // Valida dia, mês e ano
                while (rel[i].dia <= 0 || rel[i].dia > 31 || rel[i].mes <= 0 || rel[i].mes > 12 || rel[i].ano <= 0) {
                    printf("Data invalida. Digite novamente (formato dd mm aaaa): ");
                    scanf("%d %d %d", &rel[i].dia, &rel[i].mes, &rel[i].ano);
                    getchar();
                }
            }

            // Ordena os acidentes registrados em ordem alfabética pelo tipo
            qsort(rel, N, sizeof(struct relatos), compararTipo);

            // Exibe os dados cadastrados
            for (int i = 0; i < N; i++){
                printf("\n---------------------------------\n");    
                printf("\n--------Dados Cadastrados--------\n");
                printf("Nome: %s\n", cad->nome);
                printf("RG: %s\n", cad->RG);
                printf("CPF: %s\n", cad->CPF);
                printf("Email: %s\n", cad->email);
                printf("Data do acidente %d: %02d/%02d/%02d\n", i + 1, rel[i].dia, rel[i].mes, rel[i].ano);
                printf("Hora do acidente %d: %02d:%02d\n", i + 1, rel[i].hora, rel[i].minuto);
                printf("Tipo de acidente %d: %s\n", i + 1, rel[i].tipo);
                printf("localizacao %d: %s\n", i + 1, rel[i].localizacao);
            }

            // Libera a memória alocada para os relatos
            free(rel);

        // Opção 3: sair do programa
        } else if (opcao == 3){
            printf("Saindo do programa...\n");
            break;

        // Caso o usuário digite opção inválida
        } else{
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    // Libera memória do cadastro antes de sair
    free(cad);
    return 0;
}
