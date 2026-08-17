#include <stdio.h>
#include <string.h>
#include "cidade.h"

static int lerCoordenada(const char *nome) {
    int valor;

    printf("%s (0 a 4): ", nome);
    scanf("%d", &valor);

    return valor;
}

static int coordenadaValida(int x, int y) {
    return x >= 0 && x < TAM_CIDADE &&
           y >= 0 && y < TAM_CIDADE;
}

void inicializarCidade(Cidade *cidade) {
    cidade->totalProblemas = 0;

    for (int x = 0; x < TAM_CIDADE; x++) {
        for (int y = 0; y < TAM_CIDADE; y++) {
            inicializarProblemas(&cidade->pontos[x][y]);
        }
    }
}

void cadastrarProblema(Cidade *cidade) {
    int x = lerCoordenada("Ponto X");
    int y = lerCoordenada("Ponto Y");

    if (!coordenadaValida(x, y)) {
        printf("Ponto invalido!\n");
        return;
    }

    if (adicionarProblema(&cidade->pontos[x][y])) {
        cidade->totalProblemas++;
        printf("\nProblema cadastrado com sucesso!\n");
    }
}

void buscarUrgencia(const Cidade *cidade) {
    char busca[20];
    int encontrado = 0;

    printf("Qual a urgencia do seu problema?\n");
    printf("(Normal, Media, Maxima): ");
    scanf(" %19[^\n]", busca);

    for (int x = 0; x < TAM_CIDADE; x++) {
        for (int y = 0; y < TAM_CIDADE; y++) {
            const Problemas *p = &cidade->pontos[x][y];

            for (int i = 0; i < p->contador; i++) {
                if (strcmp(busca, p->urgencia[i]) == 0) {
                    printf("\nLocal: [%d,%d]\n", x, y);
                    printf("Tipo: %s\n", p->tipo[i]);
                    printf("Horario: %s\n", p->horario[i]);
                    encontrado = 1;
                }
            }
        }
    }

    if (!encontrado) {
        printf("\nNenhum problema encontrado com essa urgencia.\n");
    }
}

void consultarPonto(const Cidade *cidade) {
    int x = lerCoordenada("Ponto X");
    int y = lerCoordenada("Ponto Y");

    if (!coordenadaValida(x, y)) {
        printf("Ponto invalido!\n");
        return;
    }

    const Problemas *p = &cidade->pontos[x][y];

    printf("\n--- Problemas no ponto (%d,%d) ---\n", x, y);
    listarProblemas(p);
}

void imprimirCidade(const Cidade *cidade) {
    printf("Mapa de problemas:\n\n");

    for (int x = 0; x < TAM_CIDADE; x++) {
        for (int y = 0; y < TAM_CIDADE; y++) {
            printf("%d ", cidade->pontos[x][y].contador);
        }
        printf("\n");
    }

    printf("\nTemos no total %d problemas na cidade.\n",
           cidade->totalProblemas);
}

void solucionarProblema(Cidade *cidade) {
    int x = lerCoordenada("Ponto X");
    int y = lerCoordenada("Ponto Y");

    if (!coordenadaValida(x, y)) {
        printf("Ponto invalido!\n");
        return;
    }

    Problemas *p = &cidade->pontos[x][y];

    if (p->contador == 0) {
        printf("Nao temos problemas nesse ponto!\n");
        return;
    }

    printf("\n--- Problemas no ponto (%d,%d) ---\n", x, y);
    listarProblemas(p);

    int escolha;
    printf("\nDigite o numero do problema que deseja solucionar: ");
    scanf("%d", &escolha);

    if (removerProblema(p, escolha - 1)) {
        cidade->totalProblemas--;
        printf("\nProblema solucionado e removido com sucesso!\n");
    } else {
        printf("\nOpcao invalida!\n");
    }
}

typedef struct {
    int urgencia;
    int x;
    int y;
    char tipo[100];
    char horario[20];
    char urgenciaTexto[20];
} ProblemaOrdenado;

void ordenarPorUrgencia(const Cidade *cidade) {
    if (cidade->totalProblemas == 0) {
        printf("Nao existem problemas cadastrados.\n");
        return;
    }

    ProblemaOrdenado lista[TAM_CIDADE * TAM_CIDADE * MAX_PROBLEMAS];
    int quantidade = 0;
    int ordem;

    for (int x = 0; x < TAM_CIDADE; x++) {
        for (int y = 0; y < TAM_CIDADE; y++) {
            const Problemas *p = &cidade->pontos[x][y];

            for (int i = 0; i < p->contador; i++) {
                lista[quantidade].urgencia = p->urgenciaNum[i];
                lista[quantidade].x = x;
                lista[quantidade].y = y;

                strcpy(lista[quantidade].tipo, p->tipo[i]);
                strcpy(lista[quantidade].horario, p->horario[i]);
                strcpy(lista[quantidade].urgenciaTexto, p->urgencia[i]);

                quantidade++;
            }
        }
    }

    printf("Voce deseja ordenar por:\n");
    printf("[1] - Mais urgente\n");
    printf("[2] - Menos urgente\n");
    printf("Escolha: ");
    scanf("%d", &ordem);

    if (ordem != 1 && ordem != 2) {
        printf("Opcao invalida!\n");
        return;
    }

    /* Insertion Sort */
    for (int i = 1; i < quantidade; i++) {
        ProblemaOrdenado chave = lista[i];
        int j = i - 1;

        if (ordem == 1) {
            while (j >= 0 && lista[j].urgencia < chave.urgencia) {
                lista[j + 1] = lista[j];
                j--;
            }
        } else {
            while (j >= 0 && lista[j].urgencia > chave.urgencia) {
                lista[j + 1] = lista[j];
                j--;
            }
        }

        lista[j + 1] = chave;
    }

    printf("\nTodos os problemas ordenados:\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("[%d] - Local (%d,%d) | %s | Horario: %s | Urgencia: %s\n",
               i + 1,
               lista[i].x,
               lista[i].y,
               lista[i].tipo,
               lista[i].horario,
               lista[i].urgenciaTexto);
    }
}
