#include <stdio.h>
#include <string.h>
#include "problema.h"

void inicializarProblemas(Problemas *problemas) {
    problemas->contador = 0;
}

int adicionarProblema(Problemas *problemas) {
    int urgencia;
    int pos;

    if (problemas->contador >= MAX_PROBLEMAS) {
        printf("Este ponto atingiu o limite de %d problemas.\n", MAX_PROBLEMAS);
        return 0;
    }

    pos = problemas->contador;

    printf("Qual problema deseja reportar: ");
    scanf(" %99[^\n]", problemas->tipo[pos]);

    do {
        printf("\nQual a urgencia do seu problema?\n");
        printf("[1] - Normal\n");
        printf("[2] - Media\n");
        printf("[3] - Maxima\n");
        printf("Escolha: ");
        scanf("%d", &urgencia);

        switch (urgencia) {
            case 1:
                strcpy(problemas->urgencia[pos], "Normal");
                break;
            case 2:
                strcpy(problemas->urgencia[pos], "Media");
                break;
            case 3:
                strcpy(problemas->urgencia[pos], "Maxima");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (urgencia < 1 || urgencia > 3);

    problemas->urgenciaNum[pos] = urgencia;

    printf("Qual o horario da ocorrencia? (Manha, tarde, noite): ");
    scanf(" %19[^\n]", problemas->horario[pos]);

    problemas->contador++;

    return 1;
}

int removerProblema(Problemas *problemas, int indice) {
    if (indice < 0 || indice >= problemas->contador) {
        return 0;
    }

    for (int i = indice; i < problemas->contador - 1; i++) {
        strcpy(problemas->tipo[i], problemas->tipo[i + 1]);
        strcpy(problemas->urgencia[i], problemas->urgencia[i + 1]);
        strcpy(problemas->horario[i], problemas->horario[i + 1]);
        problemas->urgenciaNum[i] = problemas->urgenciaNum[i + 1];
    }

    problemas->contador--;

    return 1;
}

void listarProblemas(const Problemas *problemas) {
    if (problemas->contador == 0) {
        printf("Nao temos problemas nesse ponto!\n");
        return;
    }

    for (int i = 0; i < problemas->contador; i++) {
        printf("[%d] %s - Urgencia: %s - Horario: %s\n",
               i + 1,
               problemas->tipo[i],
               problemas->urgencia[i],
               problemas->horario[i]);
    }
}
