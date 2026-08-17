#ifndef PROBLEMA_H
#define PROBLEMA_H

#define MAX_PROBLEMAS 10

typedef struct {
    char tipo[MAX_PROBLEMAS][100];
    char urgencia[MAX_PROBLEMAS][20];
    char horario[MAX_PROBLEMAS][20];
    int urgenciaNum[MAX_PROBLEMAS];
    int contador;
} Problemas;

void inicializarProblemas(Problemas *problemas);
int adicionarProblema(Problemas *problemas);
int removerProblema(Problemas *problemas, int indice);
void listarProblemas(const Problemas *problemas);

#endif
