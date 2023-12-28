//
// Created by barba on 18/12/2023.
//

#ifndef PROJETOAEDLP12023_ESTRUTURAS_H
#define PROJETOAEDLP12023_ESTRUTURAS_H
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
    char *palavra;
    char *ufp6;
} PalavraUFP6;

typedef struct {
    PalavraUFP6 *palavras;
    int tamanho;
} ConjuntoPalavras;

// Protótipos de funções
PalavraUFP6 criarPalavraUFP6(const char *palavra);
ConjuntoPalavras criarConjuntoPalavras(int tamanhoInicial);
void adicionarPalavra(ConjuntoPalavras *conjunto, const char *palavra);
void listarConjuntoPalavras(const ConjuntoPalavras *conjunto);

#endif

#endif //PROJETOAEDLP12023_ESTRUTURAS_H
