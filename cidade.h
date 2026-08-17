#ifndef CIDADE_H
#define CIDADE_H

#include "problema.h"

#define TAM_CIDADE 5

typedef struct {
    Problemas pontos[TAM_CIDADE][TAM_CIDADE];
    int totalProblemas;
} Cidade;

void inicializarCidade(Cidade *cidade);

void cadastrarProblema(Cidade *cidade);
void buscarUrgencia(const Cidade *cidade);
void consultarPonto(const Cidade *cidade);
void imprimirCidade(const Cidade *cidade);
void solucionarProblema(Cidade *cidade);
void ordenarPorUrgencia(const Cidade *cidade);

#endif
