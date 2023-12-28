//
// Created by barba on 18/12/2023.
//

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função auxiliar para converter um caractere para sua representação UFP6
 char* converterCaracterParaUFP6(char caractere) {
    // Definindo a representação UFP6 para dígitos e letras
    static const char *ufp6Digits[] = {"0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001"};
    static const char *ufp6Letters[] = {"1010", "1011", "1100", "1101", "1110", "1111", "10000", "10001", "10010", "10011",
                                        "10100", "10101", "10110", "10111", "11000", "11001", "11010", "11011", "11100", "11101",
                                        "11110", "11111", "100000", "100001", "100010", "100011", "100100", "100101", "100110",
                                        "100111", "101000", "101001", "101010", "101011", "101100", "101101", "101110", "101111",
                                        "110000", "110001", "110010", "110011", "110100", "110101", "110110", "110111", "111000",
                                        "111001", "111010", "111011", "111100", "111101", "111110", "111111"};

    char *ufp6;

    // Verificar se o caractere é um dígito
    if (caractere >= '0' && caractere <= '9') {
        ufp6 = strdup(ufp6Digits[caractere - '0']);
    }
        // Verificar se o caractere é uma letra maiúscula
    else if (caractere >= 'A' && caractere <= 'Z') {
        ufp6 = strdup(ufp6Letters[caractere - 'A']);
    }
        // Verificar se o caractere é uma letra minúscula
    else if (caractere >= 'a' && caractere <= 'z') {
        ufp6 = strdup(ufp6Letters[caractere - 'a']);
    }
        // Caractere não suportado
    else {
        ufp6 = strdup("");  // Caractere não suportado, retorna string vazia
    }

    return ufp6;
}

// Função para converter uma palavra para sua representação UFP6
char* converterPalavraParaUFP6(const char *palavra) {
    // Alocar espaço para a representação UFP6 (máximo 6 bits por caractere)
    char *ufp6 = (char *)malloc((strlen(palavra) * 6) + 1);  // +1 para o terminador nulo
    ufp6[0] = '\0';  // Inicializar a string vazia

    // Para cada caractere na palavra, converter e concatenar à representação UFP6
    for (int i = 0; i < strlen(palavra); i++) {
        char *caractereUFP6 = converterCaracterParaUFP6(palavra[i]);
        strcat(ufp6, caractereUFP6);
        free(caractereUFP6);
    }

    return ufp6;
}


PalavraUFP6 criarPalavraUFP6(const char *palavra) {
    PalavraUFP6 novaPalavra;
    novaPalavra.palavra = strdup(palavra);
    novaPalavra.ufp6 = converterPalavraParaUFP6(palavra);  // Correção aqui
    return novaPalavra;
}

ConjuntoPalavras criarConjuntoPalavras(int tamanhoInicial) {
    ConjuntoPalavras conjunto;
    conjunto.palavras = (PalavraUFP6 *)malloc(tamanhoInicial * sizeof(PalavraUFP6));
    conjunto.tamanho = 0;
    return conjunto;
}

void adicionarPalavra(ConjuntoPalavras *conjunto, const char *palavra) {
    if (conjunto->tamanho % 10 == 0) {
        conjunto->palavras = (PalavraUFP6 *)realloc(conjunto->palavras, (conjunto->tamanho + 10) * sizeof(PalavraUFP6));
    }

    conjunto->palavras[conjunto->tamanho] = criarPalavraUFP6(palavra);
    conjunto->tamanho++;
}

void listarConjuntoPalavras(const ConjuntoPalavras *conjunto) {
    for (int i = 0; i < conjunto->tamanho; i++) {
        printf("Palavra: %s, UFP6: %s\n", conjunto->palavras[i].palavra, conjunto->palavras[i].ufp6);
    }
}

// Função auxiliar para gerar uma palavra aleatória
char* gerarPalavraAleatoria(int comprimento) {
    const char caracteresPermitidos[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int numCaracteresPermitidos = strlen(caracteresPermitidos);

    char* palavra = (char*)malloc((comprimento + 1) * sizeof(char));
    for (int i = 0; i < comprimento; ++i) {
        palavra[i] = caracteresPermitidos[rand() % numCaracteresPermitidos];
    }
    palavra[comprimento] = '\0';

    return palavra;
}

// Função para inserir palavras aleatórias no conjunto
void inserirPalavrasAleatorias(ConjuntoPalavras* conjunto, int numPalavras) {
    for (int i = 0; i < numPalavras; ++i) {
        char* palavraAleatoria = gerarPalavraAleatoria(7); // Altere conforme necessário
        adicionarPalavra(conjunto, palavraAleatoria);
        free(palavraAleatoria);
    }
}

// Função para remover uma palavra do conjunto
void removerPalavra(ConjuntoPalavras* conjunto, const char* palavra) {
    int indiceRemover = -1;

    for (int i = 0; i < conjunto->tamanho; ++i) {
        if (strcmp(conjunto->palavras[i].palavra, palavra) == 0) {
            indiceRemover = i;
            break;
        }
    }

    if (indiceRemover != -1) {
        free(conjunto->palavras[indiceRemover].palavra);
        free(conjunto->palavras[indiceRemover].ufp6);

        // Deslocar as palavras à frente do índice
        for (int i = indiceRemover; i < conjunto->tamanho - 1; ++i) {
            conjunto->palavras[i] = conjunto->palavras[i + 1];
        }

        conjunto->tamanho--;

        // Redimensionar o array se necessário
        if (conjunto->tamanho % 10 == 0 && conjunto->tamanho > 0) {
            conjunto->palavras = (PalavraUFP6*)realloc(conjunto->palavras, conjunto->tamanho * sizeof(PalavraUFP6));
        }
    }
}
// Função para verificar se uma combinação de palavras do conjunto1 é igual a outra combinação do conjunto2
int verificarCombinacoesIguais(const ConjuntoPalavras* conjunto1, const ConjuntoPalavras* conjunto2) {
    for (int i = 0; i < conjunto1->tamanho; i++) {
        for (int j = 0; j < conjunto1->tamanho; j++) {
            char* combinacao1 = (char*)malloc((strlen(conjunto1->palavras[i].ufp6) + strlen(conjunto1->palavras[j].ufp6) + 1) * sizeof(char));
            strcpy(combinacao1, conjunto1->palavras[i].ufp6);
            strcat(combinacao1, conjunto1->palavras[j].ufp6);

            for (int k = 0; k < conjunto2->tamanho; k++) {
                for (int l = 0; l < conjunto2->tamanho; l++) {
                    char* combinacao2 = (char*)malloc((strlen(conjunto2->palavras[k].ufp6) + strlen(conjunto2->palavras[l].ufp6) + 1) * sizeof(char));
                    strcpy(combinacao2, conjunto2->palavras[k].ufp6);
                    strcat(combinacao2, conjunto2->palavras[l].ufp6);

                    if (strcmp(combinacao1, combinacao2) == 0) {
                        free(combinacao1);
                        free(combinacao2);
                        return 1; // Combinação igual encontrada
                    }

                    free(combinacao2);
                }
            }

            free(combinacao1);
        }
    }

    return 0; // Nenhuma combinação igual encontrada
}

// Função para pesquisar palavras no conjunto que contenham a sequência de pesquisa
ConjuntoPalavras pesquisarPalavras(const ConjuntoPalavras* conjunto, const char* sequencia) {
    ConjuntoPalavras palavrasEncontradas = criarConjuntoPalavras(10); // Inicialização com um tamanho arbitrário

    for (int i = 0; i < conjunto->tamanho; i++) {
        if (strstr(conjunto->palavras[i].palavra, sequencia) != NULL) {
            adicionarPalavra(&palavrasEncontradas, conjunto->palavras[i].palavra);
        }
    }

    return palavrasEncontradas;
}

// Função para obter os códigos binários das palavras encontradas na pesquisa
ConjuntoPalavras obterCodigosPalavrasEncontradas(const ConjuntoPalavras* conjunto, const char* sequencia) {
    ConjuntoPalavras palavrasEncontradas = pesquisarPalavras(conjunto, sequencia);

    // Atualizar os códigos binários das palavras encontradas
    for (int i = 0; i < palavrasEncontradas.tamanho; i++) {
        free(palavrasEncontradas.palavras[i].ufp6);
        palavrasEncontradas.palavras[i].ufp6 = converterPalavraParaUFP6(palavrasEncontradas.palavras[i].palavra);
    }

    return palavrasEncontradas;
}

// Função de comparação para qsort: ordem alfabética crescente
int compararPalavrasCrescente(const void* a, const void* b) {
    return strcmp(((PalavraUFP6*)a)->palavra, ((PalavraUFP6*)b)->palavra);
}

// Função de comparação para qsort: ordem alfabética decrescente
int compararPalavrasDecrescente(const void* a, const void* b) {
    return strcmp(((PalavraUFP6*)b)->palavra, ((PalavraUFP6*)a)->palavra);
}

// Função de comparação para qsort: ordem de tamanho crescente
int compararTamanhosCrescente(const void* a, const void* b) {
    return strlen(((PalavraUFP6*)a)->palavra) - strlen(((PalavraUFP6*)b)->palavra);
}

// Função de comparação para qsort: ordem de tamanho decrescente
int compararTamanhosDecrescente(const void* a, const void* b) {
    return strlen(((PalavraUFP6*)b)->palavra) - strlen(((PalavraUFP6*)a)->palavra);
}

// Função para ordenar o conjunto de palavras por critério específico
void ordenarConjuntoPalavras(ConjuntoPalavras* conjunto, int criterio, int ordem) {
    switch (criterio) {
        case ALFABETICA:
            qsort(conjunto->palavras, conjunto->tamanho, sizeof(PalavraUFP6), (ordem == CRESCENTE) ? compararPalavrasCrescente : compararPalavrasDecrescente);
            break;
        case TAMANHO:
            qsort(conjunto->palavras, conjunto->tamanho, sizeof(PalavraUFP6), (ordem == CRESCENTE) ? compararTamanhosCrescente : compararTamanhosDecrescente);
            break;
            // Adicione mais critérios de ordenação, se necessário
    }
}
WORDS_HOLDER criarWordsHolder() {
    WORDS_HOLDER holder;
    holder.conjuntoAlfanumerico1 = criarConjuntoPalavras(10);
    holder.conjuntoAlfanumerico2 = criarConjuntoPalavras(10);
    holder.conjuntoUFP61 = criarConjuntoPalavras(10);
    holder.conjuntoUFP62 = criarConjuntoPalavras(10);
    return holder;
}

void adicionarPalavraWordsHolder(WORDS_HOLDER* holder, const char* palavra1, const char* palavra2) {
    adicionarPalavra(&holder->conjuntoAlfanumerico1, palavra1);
    adicionarPalavra(&holder->conjuntoAlfanumerico2, palavra2);
    adicionarPalavra(&holder->conjuntoUFP61, converterPalavraParaUFP6(palavra1));
    adicionarPalavra(&holder->conjuntoUFP62, converterPalavraParaUFP6(palavra2));
}
//alinea a
AD_WORDS_HOLDER criarADWordsHolder(int tamanhoInicial) {
    AD_WORDS_HOLDER adArray;
    adArray.tamanho = tamanhoInicial;
    adArray.elementosInseridos = 0;
    adArray.elementos = (VAL_AD_WORDS_HOLDER*)malloc(tamanhoInicial * sizeof(VAL_AD_WORDS_HOLDER));
    return adArray;
}
//alinea b
void redimensionarADWordsHolder(AD_WORDS_HOLDER* adArray, int novoTamanho) {
    adArray->elementos = (VAL_AD_WORDS_HOLDER*)realloc(adArray->elementos, novoTamanho * sizeof(VAL_AD_WORDS_HOLDER));
    adArray->tamanho = novoTamanho;
}
//alinea c
void inserirElementoADWordsHolder(AD_WORDS_HOLDER* adArray, VAL_AD_WORDS_HOLDER novoElemento) {
    if (adArray->elementosInseridos == adArray->tamanho) {
        redimensionarADWordsHolder(adArray, adArray->tamanho * 2);
    }

    adArray->elementos[adArray->elementosInseridos] = novoElemento;
    adArray->elementosInseridos++;
}
//alinea d
void inserirElementoPosicaoADWordsHolder(AD_WORDS_HOLDER* adArray, VAL_AD_WORDS_HOLDER novoElemento, int posicao) {
    if (posicao < 0 || posicao > adArray->elementosInseridos) {
        printf("Posição inválida\n");
        return;
    }

    if (adArray->elementosInseridos == adArray->tamanho) {
        redimensionarADWordsHolder(adArray, adArray->tamanho * 2);
    }

    for (int i = adArray->elementosInseridos; i > posicao; i--) {
        adArray->elementos[i] = adArray->elementos[i - 1];
    }

    adArray->elementos[posicao] = novoElemento;
    adArray->elementosInseridos++;
}
//alinea d
void eliminarElementoPosicaoADWordsHolder(AD_WORDS_HOLDER* adArray, int posicao) {
    if (posicao < 0 || posicao >= adArray->elementosInseridos) {
        printf("Posição inválida\n");
        return;
    }

    for (int i = posicao; i < adArray->elementosInseridos - 1; i++) {
        adArray->elementos[i] = adArray->elementos[i + 1];
    }

    adArray->elementosInseridos--;

    // Reduzir a alocação se o número de elementos for significativamente menor que o tamanho total
    if (adArray->elementosInseridos < adArray->tamanho / 2) {
        redimensionarADWordsHolder(adArray, adArray->tamanho / 2);
    }
}
//alinea e
VAL_AD_WORDS_HOLDER* pesquisarElementoPorDataADWordsHolder(const AD_WORDS_HOLDER* adArray, const char* data) {
    for (int i = 0; i < adArray->elementosInseridos; i++) {
        if (strcmp(adArray->elementos[i].dataModificacao, data) == 0) {
            return &(adArray->elementos[i]);
        }
    }

    return NULL;  // Elemento não encontrado
}

int escreverConjuntoParaFicheiro(const ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para escrita.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    for (int i = 0; i < conjunto->tamanho; i++) {
        fprintf(ficheiro, "Palavra: %s, UFP6: %s\n", conjunto->palavras[i].palavra, conjunto->palavras[i].ufp6);
    }

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

// Nova função para ler um conjunto de palavras de um ficheiro
int lerConjuntoDeFicheiro(ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para leitura.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de leitura do ficheiro e atualização do conjunto

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

// Nova função para escrever um AD_WORDS_HOLDER para um ficheiro
int escreverADWordsHolderParaFicheiro(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "wb");  // Modo "wb" para escrita binária
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para escrita.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de escrita do AD_WORDS_HOLDER no ficheiro

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

// Nova função para ler um AD_WORDS_HOLDER de um ficheiro
int lerADWordsHolderDeFicheiro(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");  // Modo "rb" para leitura binária
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para leitura.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de leitura do ficheiro e atualização do AD_WORDS_HOLDER

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

int escreverConjuntoParaFicheiroBinario(const ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "wb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para escrita binária.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de escrita binária do conjunto no ficheiro

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

// Nova função para ler um conjunto de palavras de um ficheiro binário
int lerConjuntoDeFicheiroBinario(ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para leitura binária.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de leitura binária do ficheiro e atualização do conjunto

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

// Nova função para escrever um AD_WORDS_HOLDER para um ficheiro binário
int escreverADWordsHolderParaFicheiroBinario(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "wb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para escrita binária.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de escrita binária do AD_WORDS_HOLDER no ficheiro

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}

// Nova função para ler um AD_WORDS_HOLDER de um ficheiro binário
int lerADWordsHolderDeFicheiroBinario(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro) {
    FILE *ficheiro = fopen(nomeFicheiro, "rb");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro para leitura binária.\n");
        return 0;  // Falha na abertura do ficheiro
    }

    // Implementar a lógica de leitura binária do ficheiro e atualização do AD_WORDS_HOLDER

    fclose(ficheiro);
    return 1;  // Operação bem-sucedida
}