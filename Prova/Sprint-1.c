// Enzo Piazentin 				RM: 564216
// Fernando Almeida				RM: 564820
// Gabriel Ber Soares Tarone		RM: 563520
// Vinicius Barbosa Gomes			RM: 564854


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dispositivo{
    char nome[50];
    float consumo;
    int prioridade; // 1 - Alta, 2 - Media, 3 - Baixa
};


int main(){
    // delcraração de quantidade de dispositivos
    int N;
    printf("Digite o numero de dispositivos: ");
    scanf("%d", &N);
    getchar();

    // Validação: o número tem que ser positivo
    while(N  <= 0){
        printf("Numero invalido. Digite novamente: ");
        scanf("%d", &N);
        getchar();
    }


    // alocação dinamica de memoria
    struct dispositivo *u = (struct dispositivo *)malloc(N * sizeof(struct dispositivo));
    if (u == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    
    // leitura dos dados dos dispositivos
    for (int i = 0; i < N; i++) {
        printf("Digite o nome do dispositivo %d: ", i + 1);
        fgets(u[i].nome, sizeof(u[i].nome), stdin);
        u[i].nome[strcspn(u[i].nome, "\n")] = 0;

        printf("Digite o consumo do dispositivo %s: ", u[i].nome);
        scanf("%f", u[i].consumo);
        printf("Digite a prioridade do dispositivo %s (1 - Alta, 2 - Media, 3 - Baixa): ", u[i].nome);
        scanf("%d", u[i].prioridade);
    }

    // ordenação dos dispositivos por prioridade
    for (int i = 0; i < N; i++) {
        printf("\nDispositivo %d:\n", i + 1);
        printf("Nome: %s\n", u[i].nome);
        printf("Consumo: %.2f\n", u[i].consumo);
        printf("Prioridade: %d\n", u[i].prioridade);
    }

    free(u);
    return 0;
}