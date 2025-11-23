#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
   Struct Territorio
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ============================
        FUNÇÃO DE ATAQUE
   ============================ */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n--- Ataque Iniciado ---\n");
    printf("%s (%s) ATACA %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf("Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;

    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/* ============================
        EXIBIR MAPA
   ============================ */
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
    printf("==========================\n");
}

/* ============================
      ATRIBUIR MISSÃO
   ============================ */
/*
   destino = memória alocada dinamicamente para armazenar a missão
   missoes[] = vetor de strings já existentes
   totalMissoes = quantidade de missões possíveis
*/
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

/* ============================
      EXIBIR MISSÃO (passagem por valor)
   ============================ */
void exibirMissao(char* missao) {
    printf("\n>>> Sua missão: %s\n", missao);
}

/* ============================
      VERIFICAR MISSÃO
   ============================ */
/*
   Regra simples (exemplo):
   - "Conquistar todos os territórios da cor vermelha"
     -> retorna 1 se não houver territórios "vermelhos" no mapa.
   - "Ter pelo menos 1 território com mais de 10 tropas"
*/
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    if (strcmp(missao, "Conquistar todos os territorios vermelhos") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Controlar um territorio com mais de 10 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 10)
                return 1;
        }
        return 0;
    }

    if (strcmp(missao, "Ter 3 territorios consecutivos com a mesma cor") == 0) {
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i+2].cor) == 0) {
                return 1;
            }
        }
        return 0;
    }

    if (strcmp(missao, "Eliminar todos os territorios azuis") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Controlar ao menos 5 territorios") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "amarelo") == 0)
                count++;
        }
        return count >= 5 ? 1 : 0;
    }

    return 0;
}

/* ============================
     LIBERAR MEMÓRIA
   ============================ */
void liberarMemoria(Territorio* mapa, char* missaoJog1, char* missaoJog2) {
    free(mapa);
    free(missaoJog1);
    free(missaoJog2);
}

/* ============================
              MAIN
   ============================ */
int main() {
    srand(time(NULL));

    int qtdTerritorios;

    printf("=== WAR Estruturado - Nivel Mestre ===\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);

    /* Alocação dinâmica do mapa */
    Territorio* mapa = (Territorio*) calloc(qtdTerritorios, sizeof(Territorio));

    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    /* Cadastro dos territórios */
    for (int i = 0; i < qtdTerritorios; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);
        printf("Nome: ");
        scanf("%29s", mapa[i].nome);
        printf("Cor: ");
        scanf("%9s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    /* ================================
          MISSÕES PRÉ-DEFINIDAS
       ================================ */
    char* missoes[] = {
        "Conquistar todos os territorios vermelhos",
        "Controlar um territorio com mais de 10 tropas",
        "Ter 3 territorios consecutivos com a mesma cor",
        "Eliminar todos os territorios azuis",
        "Controlar ao menos 5 territorios"
    };
    int totalMissoes = 5;

    /* Alocação dinâmica para as missões dos jogadores */
    char* missaoJog1 = (char*) malloc(200 * sizeof(char));
    char* missaoJog2 = (char*) malloc(200 * sizeof(char));

    atribuirMissao(missaoJog1, missoes, totalMissoes);
    atribuirMissao(missaoJog2, missoes, totalMissoes);

    printf("\n--- Missões atribuídas ---\n");
    printf("Jogador 1: ");
    exibirMissao(missaoJog1);
    printf("Jogador 2: ");
    exibirMissao(missaoJog2);

    /* =============================
            LOOP DO JOGO
       ============================= */
    int turno = 1;
    while (1) {

        printf("\n===== TURNO %d =====\n", turno);
        exibirMapa(mapa, qtdTerritorios);

        int jogador = (turno % 2 == 1) ? 1 : 2;
        printf("\nVez do Jogador %d\n", jogador);

        int atk, def;
        printf("Escolha território ATACANTE (-1 para sair): ");
        scanf("%d", &atk);
        if (atk == -1) break;

        printf("Escolha território DEFENSOR: ");
        scanf("%d", &def);

        atk--; def--;

        if (atk < 0 || atk >= qtdTerritorios || def < 0 || def >= qtdTerritorios) {
            printf("Territórios inválidos!\n");
            continue;
        }

        if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
            printf("Não pode atacar território da mesma cor!\n");
            continue;
        }

        atacar(&mapa[atk], &mapa[def]);

        /* Verificação silenciosa da missão */
        int venceu = 0;

        if (jogador == 1)
            venceu = verificarMissao(missaoJog1, mapa, qtdTerritorios);
        else
            venceu = verificarMissao(missaoJog2, mapa, qtdTerritorios);

        if (venceu) {
            printf("\n=====================================\n");
            printf("🎉 Jogador %d COMPLETOU SUA MISSÃO! 🎉\n", jogador);
            printf("=====================================\n");
            break;
        }

        turno++;
    }

    liberarMemoria(mapa, missaoJog1, missaoJog2);

    return 0;
}
