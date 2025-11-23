#include <stdio.h>
#include <string.h>

/* 
   Struct Territorio
   Armazena:
   - nome: nome do território (string)
   - cor: cor do exército (string)
   - tropas: quantidade de tropas (inteiro)
*/
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    struct Territorio territorios[5]; // Vetor para armazenar 5 territórios

    printf("=== Cadastro de Territórios - Projeto WAR ===\n\n");

    // Entrada dos dados
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);

        printf("Informe o nome do territorio: ");
        scanf("%29s", territorios[i].nome);  // lê string sem espaços

        printf("Informe a cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        printf("Informe a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Quebra de linha para organização
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territorios Cadastrados ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
