#include <stdio.h>
#include "menu.h"
#include "cidade.h"

static void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    limparEntrada();
    getchar();
}

void executarMenu(void) {
    Cidade cidade;
    int opcao;

    inicializarCidade(&cidade);

    do {
        printf("\n");
        printf("====================================\n");
        printf("          SISTEMA DE BIRIGUI\n");
        printf("====================================\n");
        printf("[1] - Registrar um problema\n");
        printf("[2] - Ver os problemas da cidade\n");
        printf("[3] - Identificacao dos problemas\n");
        printf("[4] - Buscar por urgencia\n");
        printf("[5] - Solucionar problemas\n");
        printf("[6] - Ordenar por urgencia\n");
        printf("[7] - Sair\n");
        printf("Digite sua escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            limparEntrada();
            continue;
        }

        printf("\n");

        switch (opcao) {
            case 1:
                cadastrarProblema(&cidade);
                break;

            case 2:
                imprimirCidade(&cidade);
                break;

            case 3:
                consultarPonto(&cidade);
                break;

            case 4:
                buscarUrgencia(&cidade);
                break;

            case 5:
                solucionarProblema(&cidade);
                break;

            case 6:
                ordenarPorUrgencia(&cidade);
                break;

            case 7:
                printf("Sistema fechado. Volte sempre!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

        if (opcao != 7) {
            pausar();
        }

    } while (opcao != 7);
}
