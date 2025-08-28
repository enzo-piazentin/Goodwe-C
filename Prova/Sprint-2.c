// Enzo Piazentin 				RM: 564216
// Fernando Almeida				RM: 564820
// Gabriel Ber Soares Tarone		RM: 563520
// Vinicius Barbosa Gomes			RM: 564854


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dispositivo {
    char nome[50];
    float consumo;
    int prioridade; // 1 - Alta, 2 - Media, 3 - Baixa
    int ligado;
};

// Função para ordenar por prioridade (menor valor = maior prioridade)
void ordenar_por_prioridade(struct dispositivo *vet, int n) {
    struct dispositivo temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vet[i].prioridade > vet[j].prioridade) {
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }
}

int main() {
    int N;
    printf("Digite o numero de dispositivos: ");
    scanf("%d", &N);
    getchar();

    while (N <= 0) {
        printf("Numero invalido. Digite novamente: ");
        scanf("%d", &N);
        getchar();
    }

    struct dispositivo *u = (struct dispositivo *)malloc(N * sizeof(struct dispositivo));
    if (u == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Leitura dos dados dos dispositivos
    for (int i = 0; i < N; i++) {
        printf("\nDispositivo %d:\n", i + 1);
        printf("Nome: ");
        fgets(u[i].nome, sizeof(u[i].nome), stdin);
        u[i].nome[strcspn(u[i].nome, "\n")] = 0;

        printf("Consumo (em kWh): ");
        scanf("%f", &u[i].consumo);
        printf("Prioridade (1 - Alta, 2 - Media, 3 - Baixa): ");
        scanf("%d", &u[i].prioridade);
        getchar(); // Limpa o buffer

        u[i].ligado = 0; // Desliga todos no início
    }

    // Solicita a energia disponível
    float energia_disponivel;
    printf("\nDigite a energia disponivel (em kWh): ");
    scanf("%f", &energia_disponivel);

    // Ordena os dispositivos por prioridade
    ordenar_por_prioridade(u, N);

    // Simula o consumo e liga os dispositivos se possível
    float consumo_total = 0;
    for (int i = 0; i < N; i++) {
        if (consumo_total + u[i].consumo <= energia_disponivel) {
            u[i].ligado = 1;
            consumo_total += u[i].consumo;
        }
    }

    // Exibe o resultado
    printf("--------- DISPOSITIVOS LIGADOS ---------\n");
    for (int i = 0; i < N; i++) {
        if (u[i].ligado) {
            printf("%s (%.2f kWh, Prioridade %d)\n", u[i].nome, u[i].consumo, u[i].prioridade);
        }
    }

    printf("--------- DISPOSITIVOS DESLIGADOS ---------\n");
    for (int i = 0; i < N; i++) {
        if (!u[i].ligado) {
            printf("%s (%.2f kWh, Prioridade %d)\n", u[i].nome, u[i].consumo, u[i].prioridade);
        }
    }

    printf("\nConsumo total: %.2f kWh de %.2f kWh disponiveis\n", consumo_total, energia_disponivel);

    free(u);
    return 0;
}

