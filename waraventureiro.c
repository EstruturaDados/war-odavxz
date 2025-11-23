#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
   Struct Territorio
   Representa um território do jogo WAR.
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
   Função: cadastrarTerritorios
   Objetivo: preencher os dados dos territórios alocados dinamicamente.
*/
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        printf("Nome: ");
        scanf("%29s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/*
   Função: exibirMapa
   Objetivo: mostrar os dados de todos os territórios.
*/
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
    printf("=============================\n\n");
}

/*
   Função: atacar
   Objetivo: simular um ataque entre territórios usando rand() como dado.
   Regras:
   - Atacante e defensor rolam um dado (1 a 6)
   - Maior valor vence
   - Se atacante vencer:
         * Território defensor muda de cor
         * Tropas do defensor passam a ser a metade do atacante (mínimo 1)
   - Se perder:
         * Atacante perde 1 tropa
*/
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== Iniciando ataque ===\n");
    printf("%s (%s) ATACANDO %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoA);
    printf("Dado do defensor: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("O atacante venceu!\n");

        strcpy(defensor->cor, attacker->cor); // transfere controle
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;

        printf("Território %s agora pertence ao exército %s.\n",
               defensor->nome, defensor->cor);

    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/*
   Função: liberarMemoria
   Objetivo: liberar memória alocada dinamicamente.
*/
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso.\n");
}

/*
   MAIN
*/
int main() {

    srand(time(NULL)); // aleatoriedade para os dados

    int qtd;

    printf("===== WAR Estruturado - Nivel Aventureiro =====\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        exibirMapa(mapa, qtd);

        printf("Escolha um território para ATACAR (-1 para sair): ");
        scanf("%d", &opcao);

        if (opcao == -1) break;

        int atk = opcao - 1;

        printf("Escolha um território para DEFENDER: ");
        scanf("%d", &opcao);
        int def = opcao - 1;

        if (atk < 0 || atk >= qtd || def < 0 || def >= qtd) {
            printf("Índices inválidos!\n");
            continue;
        }

        if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
            printf("Você não pode atacar um território da mesma cor!\n");
            continue;
        }

        atacar(&mapa[atk], &mapa[def]);

    } while (1);

    liberarMemoria(mapa);

    return 0;
}
