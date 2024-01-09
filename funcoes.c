//
// Created by barba on 18/12/2023.
//

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Converte um caractere para sua representação UFP6.
 *
 * Esta função converte um caractere para sua representação UFP6, que é uma forma de codificação de caracteres.
 * A tabela de codificação inclui dígitos de 0 a 9 e letras minúsculas de 'a' a 'z'.
 *
 * @param caractere O caractere a ser convertido para UFP6.
 * @return Retorna a representação UFP6 do caractere. Se o caractere não estiver na tabela de codificação,
 *         retorna uma string vazia.
 */
char *converterCaracterParaUFP6(char caractere) {
    // Tabela de codificação UFP6 para dígitos e letras minúsculas
    const char *ufp6Table[36] = {
            "000000", "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001",
            "001010", "001011", "001100", "001101", "001110", "001111", "010000", "010001", "010010", "010011",
            "010100", "010101", "010110", "010111", "0011000", "011001", "011010", "011011", "011100", "011101",
            "011110",
            "011111", "100000", "100001", "100010", "100011"
    };

    char *codigoUFP6 = NULL;

    if (caractere >= '0' && caractere <= '9') {
        // Remover zeros à esquerda
        codigoUFP6 = strdup(ufp6Table[caractere - '0'] + strspn(ufp6Table[caractere - '0'], "0"));
    } else if (caractere >= 'a' && caractere <= 'z') {
        // Remover zeros à esquerda
        codigoUFP6 = strdup(ufp6Table[caractere - 'a' + 10] + strspn(ufp6Table[caractere - 'a' + 10], "0"));
    } else {
        // Caracteres não suportados (ignorados na codificação)
        codigoUFP6 = strdup("");
    }

    return codigoUFP6;
}

/**
 * @brief Converte uma palavra para sua representação UFP6.
 *
 * Esta função converte uma palavra para sua representação UFP6, que é uma forma de codificação de caracteres.
 * Utiliza a função auxiliar converterCaracterParaUFP6 para converter cada caractere da palavra.
 *
 * @param palavra A palavra a ser convertida para UFP6.
 * @return Retorna a representação UFP6 da palavra. Se a palavra contiver caracteres não suportados,
 *         a representação UFP6 desses caracteres será uma string vazia.
 *         A memória para a representação UFP6 é alocada dinamicamente e deve ser libertada
 */
char *converterPalavraParaUFP6(const char *palavra) {
    int tamanho = strlen(palavra);
    char *ufp6 = (char *) malloc((tamanho * 6 + 1) * sizeof(char));
    ufp6[0] = '\0';  // Inicializar a string vazia

    for (int i = 0; i < tamanho; i++) {
        char *codigoCaracter = converterCaracterParaUFP6(palavra[i]);
        strcat(ufp6, codigoCaracter);
        free(codigoCaracter);
    }

    return ufp6;
}

/**
 * @brief Cria uma estrutura PalavraUFP6.
 *
 * Esta função cria uma estrutura PalavraUFP6 a partir de uma palavra dada, incluindo sua representação UFP6.
 * A memória para a palavra e sua representação UFP6 é alocada dinamicamente e deve ser libertada.
 *
 * @param palavra A palavra para a qual a estrutura PalavraUFP6 será criada.
 * @return Retorna a estrutura PalavraUFP6 criada. A memória para a estrutura e seus campos é alocada dinamicamente
 */
PalavraUFP6 criarPalavraUFP6(const char *palavra) {
    PalavraUFP6 palavraUFP6;
    palavraUFP6.palavra = strdup(palavra);
    palavraUFP6.ufp6 = converterPalavraParaUFP6(palavra);
    return palavraUFP6;
}

/**
 * @brief Cria um conjunto de palavras inicializado com um tamanho específico.
 *
 * Esta função cria e retorna um conjunto de palavras, inicializado com um tamanho inicial fornecido.
 * O conjunto de palavras é uma estrutura que contém um array de PalavraUFP6 e um campo que rastreia o tamanho atual do conjunto.
 * A memória para o array de PalavraUFP6 é alocada dinamicamente
 *
 * @param tamanhoInicial O tamanho inicial para alocar para o conjunto de palavras.
 * @return Retorna o conjunto de palavras inicializado com o tamanho especificado.
 *         A memória para o array de PalavraUFP6 é alocada dinamicamente e deve ser liberatada.
 */
ConjuntoPalavras criarConjuntoPalavras(int tamanhoInicial) {
    ConjuntoPalavras conjunto;
    conjunto.palavras = (PalavraUFP6 *) malloc(tamanhoInicial * sizeof(PalavraUFP6));
    conjunto.tamanho = 0;
    return conjunto;
}

/**
 * @brief Adiciona uma palavra ao conjunto de palavras.
 *
 * Esta função adiciona uma palavra ao conjunto de palavras. Se o tamanho atual do conjunto for um múltiplo de 10,
 * o array de PalavraUFP6 é realocado para acomodar mais 10 elementos.
 * A memória para a palavra e sua representação UFP6 é alocada dinamicamente
 *
 * @param conjunto Um ponteiro para o conjunto de palavras ao qual a palavra será adicionada.
 * @param palavra A palavra a ser adicionada ao conjunto de palavras.
 */
void adicionarPalavra(ConjuntoPalavras *conjunto, const char *palavra) {
    if (conjunto->tamanho % 10 == 0) {
        conjunto->palavras = (PalavraUFP6 *) realloc(conjunto->palavras,
                                                     (conjunto->tamanho + 10) * sizeof(PalavraUFP6));
    }

    conjunto->palavras[conjunto->tamanho] = criarPalavraUFP6(palavra);
    conjunto->tamanho++;
}

/**
 * @brief Lista todas as palavras e suas representações UFP6 no conjunto.
 *
 * Esta função imprime no console todas as palavras e suas representações UFP6 presentes no conjunto.
 *
 * @param conjunto Um ponteiro para o conjunto de palavras a ser listado.
 */
void listarConjuntoPalavras(const ConjuntoPalavras *conjunto) {
    for (int i = 0; i < conjunto->tamanho; i++) {
        printf("Palavra: %s, UFP6: %s\n", conjunto->palavras[i].palavra, conjunto->palavras[i].ufp6);
    }
}

/**
 * @brief Liberta a memória alocada pelo conjunto de palavras.
 *
 * Esta função liberta a memória alocada pelo conjunto de palavras, incluindo as palavras e suas representações UFP6.
 * Devemos chamar esta função para evitar vazamentos de memória ao finalizar o uso do conjunto.
 *
 * @param conjunto Um ponteiro para o conjunto de palavras cuja memória será liberada.
 */
void liberarConjuntoPalavras(ConjuntoPalavras *conjunto) {
    for (int i = 0; i < conjunto->tamanho; i++) {
        free(conjunto->palavras[i].palavra);
        free(conjunto->palavras[i].ufp6);
    }
    free(conjunto->palavras);
}

/**
 * @brief Gera uma palavra aleatória com o comprimento especificado.
 *
 * Esta função gera uma palavra aleatória com o comprimento especificado, utilizando os caracteres permitidos.
 * A memória para a palavra é alocada dinamicamente e deve ser libertada
 *
 * @param comprimento O comprimento desejado da palavra aleatória.
 * @return Retorna a palavra aleatória gerada. A memória para a palavra é alocada dinamicamente
 *         e deve ser liberada pelo chamador.
 */
char *gerarPalavraAleatoria(int comprimento) {
    const char caracteresPermitidos[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int numCaracteresPermitidos = strlen(caracteresPermitidos);

    char *palavra = (char *) malloc((comprimento + 1) * sizeof(char));
    for (int i = 0; i < comprimento; ++i) {
        palavra[i] = caracteresPermitidos[rand() % numCaracteresPermitidos];
    }
    palavra[comprimento] = '\0';

    return palavra;
}

/**
 * @brief Insere palavras aleatórias no conjunto.
 *
 * Esta função insere um número especificado de palavras aleatórias no conjunto de palavras.
 * A memória para as palavras e suas representações UFP6 é alocada dinamicamente e deve ser libertada depois
 *
 * @param conjunto Um ponteiro para o conjunto de palavras no qual as palavras aleatórias serão inseridas.
 * @param numPalavras O número de palavras aleatórias a serem inseridas no conjunto.
 */
void inserirPalavrasAleatorias(ConjuntoPalavras *conjunto, int numPalavras) {
    for (int i = 0; i < numPalavras; ++i) {
        char *palavraAleatoria = gerarPalavraAleatoria(7); // Altere conforme necessário
        adicionarPalavra(conjunto, palavraAleatoria);
        free(palavraAleatoria);
    }
}

/**
 * @brief Remove uma palavra do conjunto.
 *
 * Esta função remove uma palavra específica do conjunto de palavras, libertando a memória associada.
 * Se a palavra não estiver presente no conjunto, a função não realiza nenhuma ação.
 *
 * @param conjunto Um ponteiro para o conjunto de palavras do qual a palavra será removida.
 * @param palavra A palavra a ser removida do conjunto.
 */
void removerPalavra(ConjuntoPalavras *conjunto, const char *palavra) {
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

        // Deslocar as palavras após o índice
        for (int i = indiceRemover; i < conjunto->tamanho - 1; ++i) {
            conjunto->palavras[i] = conjunto->palavras[i + 1];
        }

        // Redimensionar o array se necessário
        conjunto->tamanho--;

        if (conjunto->tamanho % 10 == 0 && conjunto->tamanho > 0) {
            conjunto->palavras = (PalavraUFP6 *) realloc(conjunto->palavras, conjunto->tamanho * sizeof(PalavraUFP6));
        }
    }
}

/**
 * @brief Remove uma palavra do conjunto pelo índice.
 *
 * Esta função remove uma palavra do conjunto de palavras com base no índice fornecido,
 * libertando a memória associada. Se o índice estiver fora dos limites do conjunto, a função não realiza nenhuma ação.
 *
 * @param conjunto Um ponteiro para o conjunto de palavras do qual a palavra será removida.
 * @param indice O índice da palavra a ser removida do conjunto.
 */
void removerPalavraPorIndice(ConjuntoPalavras *conjunto, int indice) {
    if (indice >= 0 && indice < conjunto->tamanho) {
        free(conjunto->palavras[indice].palavra);
        free(conjunto->palavras[indice].ufp6);

        // Deslocar as palavras após o índice
        for (int i = indice; i < conjunto->tamanho - 1; ++i) {
            conjunto->palavras[i] = conjunto->palavras[i + 1];
        }

        // Redimensionar o array se necessário
        conjunto->tamanho--;

        if (conjunto->tamanho % 10 == 0 && conjunto->tamanho > 0) {
            conjunto->palavras = (PalavraUFP6 *) realloc(conjunto->palavras, conjunto->tamanho * sizeof(PalavraUFP6));
        }
    }
}

/**
 * @brief Verifica se uma combinação de palavras do conjunto1 é igual a outra combinação do conjunto2.
 *
 * Esta função verifica se existe uma combinação de duas palavras do conjunto1 cuja concatenação UFP6 seja igual
 * à concatenação UFP6 de duas palavras do conjunto2.
 *
 * @param conjunto1 Um ponteiro para o primeiro conjunto de palavras.
 * @param conjunto2 Um ponteiro para o segundo conjunto de palavras.
 * @return Retorna 1 se uma combinação igual for encontrada, 0 caso contrário.
 */
int verificarCombinacoesIguais(const ConjuntoPalavras *conjunto1, const ConjuntoPalavras *conjunto2) {
    for (int i = 0; i < conjunto1->tamanho; i++) {
        for (int j = 0; j < conjunto1->tamanho; j++) {
            char *combinacao1 = (char *) malloc(
                    (strlen(conjunto1->palavras[i].ufp6) + strlen(conjunto1->palavras[j].ufp6) + 1) * sizeof(char));
            strcpy(combinacao1, conjunto1->palavras[i].ufp6);
            strcat(combinacao1, conjunto1->palavras[j].ufp6);

            for (int k = 0; k < conjunto2->tamanho; k++) {
                for (int l = 0; l < conjunto2->tamanho; l++) {
                    char *combinacao2 = (char *) malloc(
                            (strlen(conjunto2->palavras[k].ufp6) + strlen(conjunto2->palavras[l].ufp6) + 1) *
                            sizeof(char));
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

/**
 * @brief Pesquisa palavras no conjunto que contenham a sequência fornecida.
 *
 * Esta função pesquisa e retorna um novo conjunto de palavras contendo apenas aquelas que contêm a sequência especificada.
 * A memória para o novo conjunto é alocada dinamicamente e deve ser libertada pelo chamador.
 *
 * @param conjunto Um ponteiro para o conjunto de palavras no qual a pesquisa será realizada.
 * @param sequencia A sequência a ser procurada nas palavras do conjunto.
 * @return Retorna um novo conjunto de palavras contendo apenas aquelas que contêm a sequência fornecida.
 *
 */
ConjuntoPalavras pesquisarPalavras(const ConjuntoPalavras *conjunto, const char *sequencia) {
    ConjuntoPalavras palavrasEncontradas = criarConjuntoPalavras(10); // Inicialização com um tamanho arbitrário

    for (int i = 0; i < conjunto->tamanho; i++) {
        if (strstr(conjunto->palavras[i].palavra, sequencia) != NULL) {
            adicionarPalavra(&palavrasEncontradas, conjunto->palavras[i].palavra);
        }
    }

    return palavrasEncontradas;
}

/**
 * @brief Obtém um novo conjunto de palavras com códigos atualizados para aquelas que contêm a sequência fornecida.
 *
 * Esta função pesquisa e retorna um novo conjunto de palavras contendo apenas aquelas que contêm a sequência especificada.
 * Além disso, atualiza os códigos UFP6 das palavras encontradas.
 * A memória para o novo conjunto é alocada dinamicamente e deve ser libertada
 *
 * @param conjunto Um ponteiro para o conjunto de palavras no qual a pesquisa será realizada.
 * @param sequencia A sequência a ser procurada nas palavras do conjunto.
 * @return Retorna um novo conjunto de palavras contendo apenas aquelas que contêm a sequência fornecida,
 *         com os códigos UFP6 atualizados.
 *
 */
ConjuntoPalavras obterCodigosPalavrasEncontradas(const ConjuntoPalavras *conjunto, const char *sequencia) {
    ConjuntoPalavras palavrasEncontradas = pesquisarPalavras(conjunto, sequencia);

    // Atualizar os códigos binários das palavras encontradas
    for (int i = 0; i < palavrasEncontradas.tamanho; i++) {
        free(palavrasEncontradas.palavras[i].ufp6);
        palavrasEncontradas.palavras[i].ufp6 = converterPalavraParaUFP6(palavrasEncontradas.palavras[i].palavra);
    }

    return palavrasEncontradas;
}

/**
 * @brief Função de comparação para ordenar palavras em ordem crescente.
 *
 * Esta função é projetada para ser usada com a função de ordenação qsort() da biblioteca padrão.
 * Ela compara duas palavras UFP6 para determinar a ordem crescente com base em suas representações de palavras.
 *
 * @param a Ponteiro para a primeira PalavraUFP6 a ser comparada.
 * @param b Ponteiro para a segunda PalavraUFP6 a ser comparada.
 * @return Retorna um valor negativo se a < b, 0 se a == b e um valor positivo se a > b.
 */
int compararPalavrasCrescente(const void *a, const void *b) {
    return strcmp(((PalavraUFP6 *) a)->palavra, ((PalavraUFP6 *) b)->palavra);
}

/**
 * @brief Função de comparação para ordenar palavras em ordem decrescente.
 *
 * Esta função é projetada para ser usada com a função de ordenação qsort() da biblioteca padrão.
 * Ela compara duas palavras UFP6 para determinar a ordem decrescente com base em suas representações de palavras.
 *
 * @param a Ponteiro para a primeira PalavraUFP6 a ser comparada.
 * @param b Ponteiro para a segunda PalavraUFP6 a ser comparada.
 * @return Retorna um valor negativo se a > b, 0 se a == b e um valor positivo se a < b.
 */
 int compararPalavrasDecrescente(const void *a, const void *b) {
    return strcmp(((PalavraUFP6 *) b)->palavra, ((PalavraUFP6 *) a)->palavra);
}

/**
 * @brief Função de comparação para ordenar palavras por tamanho em ordem crescente.
 *
 * Esta função é projetada para ser usada com a função de ordenação qsort() da biblioteca padrão.
 * Ela compara duas palavras UFP6 para determinar a ordem crescente com base no tamanho de suas representações de palavras.
 *
 * @param a Ponteiro para a primeira PalavraUFP6 a ser comparada.
 * @param b Ponteiro para a segunda PalavraUFP6 a ser comparada.
 * @return Retorna um valor negativo se o tamanho de a < o tamanho de b, 0 se o tamanho de a == o tamanho de b
 *         e um valor positivo se o tamanho de a > o tamanho de b.
 */int compararTamanhosCrescente(const void *a, const void *b) {
    return strlen(((PalavraUFP6 *) a)->palavra) - strlen(((PalavraUFP6 *) b)->palavra);
}

/**
 * @brief Função de comparação para ordenar palavras por tamanho em ordem decrescente.
 *
 * Esta função é projetada para ser usada com a função de ordenação qsort() da biblioteca padrão.
 * Ela compara duas palavras UFP6 para determinar a ordem decrescente com base no tamanho de suas representações de palavras.
 *
 * @param a Ponteiro para a primeira PalavraUFP6 a ser comparada.
 * @param b Ponteiro para a segunda PalavraUFP6 a ser comparada.
 * @return Retorna um valor negativo se o tamanho de a > o tamanho de b, 0 se o tamanho de a == o tamanho de b
 *         e um valor positivo se o tamanho de a < o tamanho de b.
 */int compararTamanhosDecrescente(const void *a, const void *b) {
    return strlen(((PalavraUFP6 *) b)->palavra) - strlen(((PalavraUFP6 *) a)->palavra);
}

/**
 * @brief Ordena um conjunto de palavras com base no critério especificado e na ordem desejada.
 *
 * Esta função utiliza a função de ordenação qsort() da biblioteca padrão para ordenar as palavras
 * no conjunto de acordo com o critério escolhido e a ordem especificada.
 *
 * @param conjunto Um ponteiro para o conjunto de palavras a ser ordenado.
 * @param criterio O critério de ordenação desejado (ALFABETICA ou TAMANHO).
 * @param ordem A ordem de ordenação desejada (CRESCENTE ou DECRESCENTE).
 */void ordenarConjuntoPalavras(ConjuntoPalavras *conjunto, int criterio, int ordem) {
    switch (criterio) {
        case ALFABETICA:
            qsort(conjunto->palavras, conjunto->tamanho, sizeof(PalavraUFP6),
                  (ordem == CRESCENTE) ? compararPalavrasCrescente : compararPalavrasDecrescente);
            break;
        case TAMANHO:
            qsort(conjunto->palavras, conjunto->tamanho, sizeof(PalavraUFP6),
                  (ordem == CRESCENTE) ? compararTamanhosCrescente : compararTamanhosDecrescente);
            break;

    }
}

/**
 * @brief Compara duas datas para determinar a ordem cronológica.
 *
 * Esta função compara duas datas para determinar se a primeira data é anterior, igual ou posterior à segunda data.
 * Retorna um valor negativo se a primeira data for anterior à segunda, 0 se ambas as datas forem iguais e
 * um valor positivo se a primeira data for posterior à segunda.
 *
 * @param data1 A primeira data a ser comparada.
 * @param data2 A segunda data a ser comparada.
 * @return Retorna um valor negativo se data1 < data2, 0 se data1 == data2 e um valor positivo se data1 > data2.
 */int compararDatas(Data data1, Data data2) {
    if (data1.ano < data2.ano) {
        return -1;
    } else if (data1.ano > data2.ano) {
        return 1;
    } else {
        // Os anos são iguais, comparar meses
        if (data1.mes < data2.mes) {
            return -1;
        } else if (data1.mes > data2.mes) {
            return 1;
        } else {
            // Os meses são iguais, comparar dias
            if (data1.dia < data2.dia) {
                return -1;
            } else if (data1.dia > data2.dia) {
                return 1;
            } else {
                // As datas são iguais
                return 0;
            }
        }
    }
}



//Requisito 8

// Alínea a
/**
 * @brief Cria e inicializa uma estrutura AD_WORDS_HOLDER.
 *
 * Esta função aloca dinamicamente um array de VAL_AD_WORDS_HOLDER para armazenar palavras
 * Inicializa o tamanho inicial, o número de elementos inseridos e o array.
 *
 * @param tamanhoInicial O tamanho inicial do array a ser alocado.
 * @return Retorna uma instância de AD_WORDS_HOLDER inicializada.
 *         A memória para o array é alocada dinamicamente e deve ser libertada quando não for mais necessária.
 */
AD_WORDS_HOLDER criarAdWordsHolder(int tamanhoInicial) {
    AD_WORDS_HOLDER adArray;
    adArray.tamanho = tamanhoInicial;
    adArray.elementosInseridos = 0;
    adArray.array = (VAL_AD_WORDS_HOLDER *) malloc(tamanhoInicial * sizeof(VAL_AD_WORDS_HOLDER));
    return adArray;
}

/**
 * @brief Redimensiona dinamicamente a estrutura AD_WORDS_HOLDER para o novo tamanho especificado.
 *
 * Esta função redimensiona dinamicamente o array da estrutura AD_WORDS_HOLDER para o novo tamanho especificado.
 * Atualiza o tamanho do array na estrutura AD_WORDS_HOLDER.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER a ser redimensionada.
 * @param novoTamanho O novo tamanho desejado para o array.
 * @note Se o novo tamanho for menor que o número de elementos já inseridos, alguns elementos serão truncados.
 *       A memória para o array é redimensionada dinamicamente e deve ser libertada quando não for mais necessária.
 */
void redimensionarADWordsHolder(AD_WORDS_HOLDER *adArray, int novoTamanho) {
    adArray->tamanho = novoTamanho;
    adArray->array = realloc(adArray->array, novoTamanho * sizeof(VAL_AD_WORDS_HOLDER));
}

/**
 * @brief Cria e inicializa uma estrutura VAL_AD_WORDS_HOLDER com os dados fornecidos.
 *
 * Esta função cria e inicializa uma instância de VAL_AD_WORDS_HOLDER com os dados do WORDS_HOLDER fornecidos
 * e a data de atualização especificada.
 *
 * @param dados O WORDS_HOLDER contendo as palavras-chave e suas informações associadas.
 * @param dataAtualizacao A data de atualização associada aos dados.
 * @return Retorna uma instância de VAL_AD_WORDS_HOLDER inicializada com os dados fornecidos.
 */
VAL_AD_WORDS_HOLDER criarValAdWordsHolder(WORDS_HOLDER dados, Data dataAtualizacao) {
    VAL_AD_WORDS_HOLDER val;
    val.wordsHolder = dados;
    val.dataAtualizacao = dataAtualizacao;
    return val;
}

/**
 * @brief Adiciona um VAL_AD_WORDS_HOLDER ao AD_WORDS_HOLDER, redimensionando o array se necessário.
 *
 * Esta função adiciona um VAL_AD_WORDS_HOLDER ao array dentro da estrutura AD_WORDS_HOLDER.
 * Se o número de elementos inseridos atingir o tamanho atual do array, o array é redimensionado para o dobro do tamanho.
 *
 * @param ad_holder Um ponteiro para a estrutura AD_WORDS_HOLDER na qual o VAL_AD_WORDS_HOLDER será adicionado.
 * @param val O VAL_AD_WORDS_HOLDER a ser adicionado ao array.
 * @note Se o array for redimensionado, a memória antiga é liberada e a memória para o novo array é alocada dinamicamente.
 *       A estrutura AD_WORDS_HOLDER é atualizada com o novo tamanho e número de elementos inseridos.
 */
void adicionarAoAdWordsHolder(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER val) {
    if (ad_holder->elementosInseridos == ad_holder->tamanho) {
        redimensionarADWordsHolder(ad_holder, ad_holder->tamanho * 2);
    }

    ad_holder->array[ad_holder->elementosInseridos] = val;
    ad_holder->elementosInseridos++;
}

// Alínea b

void inserirOrdenadoPorData(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER val) {
    if (ad_holder->elementosInseridos == ad_holder->tamanho) {
        redimensionarADWordsHolder(ad_holder, ad_holder->tamanho * 2);
    }

    int i;
    for (i = ad_holder->elementosInseridos - 1; i >= 0; i--) {
        if (compararDatas(val.dataAtualizacao, ad_holder->array[i].dataAtualizacao) > 0) {
            ad_holder->array[i + 1] = ad_holder->array[i];
        } else {
            break;
        }
    }

    ad_holder->array[i + 1] = val;
    ad_holder->elementosInseridos++;
}

/**
 * @brief Insere um VAL_AD_WORDS_HOLDER ordenadamente no AD_WORDS_HOLDER, redimensionando o array se necessário.
 *
 * Esta função insere um VAL_AD_WORDS_HOLDER de forma ordenada no array dentro da estrutura AD_WORDS_HOLDER.
 * O array é redimensionado se o número de elementos inseridos atingir o tamanho atual.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER na qual o VAL_AD_WORDS_HOLDER será inserido.
 * @param elemento O VAL_AD_WORDS_HOLDER a ser inserido no array de forma ordenada com base na data de atualização.
 * @note Se o array for redimensionado, a memória antiga é libertada e a memória para o novo array é alocada dinamicamente.
 *       A estrutura AD_WORDS_HOLDER é atualizada com o novo tamanho e número de elementos inseridos.
 */void inserirElementoOrdenado(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER elemento) {
    if (adArray->elementosInseridos == adArray->tamanho) {
        // Redimensionar o array se estiver cheio
        redimensionarADWordsHolder(adArray, adArray->tamanho * 2);
    }

    int i = adArray->elementosInseridos - 1;
    while (i >= 0 && (elemento.dataAtualizacao.ano < adArray->array[i].dataAtualizacao.ano ||
                      (elemento.dataAtualizacao.ano == adArray->array[i].dataAtualizacao.ano &&
                       (elemento.dataAtualizacao.mes < adArray->array[i].dataAtualizacao.mes ||
                        (elemento.dataAtualizacao.mes == adArray->array[i].dataAtualizacao.mes &&
                         elemento.dataAtualizacao.dia < adArray->array[i].dataAtualizacao.dia))))) {
        // Deslocar elementos maiores para a direita
        adArray->array[i + 1] = adArray->array[i];
        i--;
    }

    // Inserir o novo elemento
    adArray->array[i + 1] = elemento;
    adArray->elementosInseridos++;
}

// Alínea c
void inserirElementoADWordsHolder(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER novoElemento) {
    adicionarAoAdWordsHolder(adArray, novoElemento);
}
/**
 * @brief Insere um VAL_AD_WORDS_HOLDER em um índice específico no AD_WORDS_HOLDER, redimensionando o array se necessário.
 *
 * Esta função insere um VAL_AD_WORDS_HOLDER em um índice específico no array dentro da estrutura AD_WORDS_HOLDER.
 * O array é redimensionado se o número de elementos inseridos atingir o tamanho atual.
 *
 * @param ad_holder Um ponteiro para a estrutura AD_WORDS_HOLDER na qual o VAL_AD_WORDS_HOLDER será inserido.
 * @param val O VAL_AD_WORDS_HOLDER a ser inserido no array.
 * @param indice O índice no qual o elemento será inserido. Deve ser um valor entre 0 e elementosInseridos, inclusive.
 * @note Se o array for redimensionado, a memória antiga é liberada e a memória para o novo array é alocada dinamicamente.
 *       A estrutura AD_WORDS_HOLDER é atualizada com o novo tamanho e número de elementos inseridos.
 */
void inserirNoIndice(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER val, int indice) {
    if (indice >= 0 && indice <= ad_holder->elementosInseridos) {
        if (ad_holder->elementosInseridos == ad_holder->tamanho) {
            redimensionarADWordsHolder(ad_holder, ad_holder->tamanho * 2);
        }

        int i;
        for (i = ad_holder->elementosInseridos - 1; i >= indice; i--) {
            ad_holder->array[i + 1] = ad_holder->array[i];
        }

        ad_holder->array[indice] = val;
        ad_holder->elementosInseridos++;
    } else {
        printf("Índice inválido para inserção.\n");
    }
}

/**
 * @brief Insere um VAL_AD_WORDS_HOLDER em uma posição específica no AD_WORDS_HOLDER, redimensionando o array se necessário.
 *
 * Esta função insere um VAL_AD_WORDS_HOLDER em uma posição específica no array dentro da estrutura AD_WORDS_HOLDER.
 * O array é redimensionado se o número de elementos inseridos atingir o tamanho atual.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER na qual o VAL_AD_WORDS_HOLDER será inserido.
 * @param elemento O VAL_AD_WORDS_HOLDER a ser inserido no array.
 * @param posicao A posição na qual o elemento será inserido. Deve ser um valor entre 0 e elementosInseridos, inclusive.
 * @note Se o array for redimensionado, a memória antiga é libertada e a memória para o novo array é alocada dinamicamente.
 *       A estrutura AD_WORDS_HOLDER é atualizada com o novo tamanho e número de elementos inseridos.
 */
 void inserirElementoNaPosicao(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER elemento, int posicao) {
    if (posicao < 0 || posicao > adArray->elementosInseridos) {
        printf("Posição inválida para inserção.\n");
        return;
    }

    if (adArray->elementosInseridos == adArray->tamanho) {
        // Redimensionar o array se estiver cheio
        redimensionarADWordsHolder(adArray, adArray->tamanho * 2);
    }

    // Deslocar elementos maiores para a direita
    for (int i = adArray->elementosInseridos - 1; i >= posicao; i--) {
        adArray->array[i + 1] = adArray->array[i];
    }

    // Inserir o novo elemento na posição desejada
    adArray->array[posicao] = elemento;
    adArray->elementosInseridos++;
}

// Alínea d
void inserirElementoPosicaoADWordsHolder(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER novoElemento, int posicao) {
    inserirNoIndice(adArray, novoElemento, posicao);
}

void eliminarElementoPosicaoADWordsHolder(AD_WORDS_HOLDER *adArray, int posicao) {
    if (posicao >= 0 && posicao < adArray->elementosInseridos) {
        for (int i = posicao; i < adArray->elementosInseridos - 1; i++) {
            adArray->array[i] = adArray->array[i + 1];
        }

        adArray->elementosInseridos--;
    } else {
        printf("Posição inválida para eliminação.\n");
    }
}

/**
 * @brief Elimina um elemento do AD_WORDS_HOLDER na posição especificada.
 *
 * Esta função elimina um elemento do array dentro da estrutura AD_WORDS_HOLDER na posição especificada.
 * Os elementos à direita do elemento eliminado são deslocados à esquerda para preencher o espaço vago.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER da qual o elemento será eliminado.
 * @param posicao A posição do elemento a ser eliminado. Deve ser um valor entre 0 e elementosInseridos-1, inclusive.
 * @note A memória liberada após a eliminação do elemento não é redimensionada.
 */
 void eliminarElementoNaPosicao(AD_WORDS_HOLDER *adArray, int posicao) {
    if (posicao < 0 || posicao >= adArray->elementosInseridos) {
        printf("Posição inválida para eliminação.\n");
        return;
    }

    // Deslocar elementos à esquerda para preencher o espaço vago
    for (int i = posicao; i < adArray->elementosInseridos - 1; i++) {
        adArray->array[i] = adArray->array[i + 1];
    }

    adArray->elementosInseridos--;
}

/**
 * @brief Pesquisa palavras em elementos do AD_WORDS_HOLDER e exibe os resultados.
 *
 * Esta função pesquisa por uma palavra em cada elemento do array dentro da estrutura AD_WORDS_HOLDER
 * e exibe os resultados da pesquisa, se houver correspondências.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER contendo os elementos a serem pesquisados.
 * @param palavraPesquisa A palavra-chave a ser pesquisada nos elementos.
 * @note Esta função assume que cada elemento contém uma estrutura wordsHolder com um conjuntoAlfanumerico1.
 */void pesquisarPalavrasEmElementos(AD_WORDS_HOLDER *adArray, const char *palavraPesquisa) {
    printf("Resultados da pesquisa por '%s':\n", palavraPesquisa);

    for (int i = 0; i < adArray->elementosInseridos; i++) {
        ConjuntoPalavras *conjunto = &adArray->array[i].wordsHolder.conjuntoAlfanumerico1;
        ConjuntoPalavras palavrasEncontradas = pesquisarPalavras(conjunto, palavraPesquisa);

        if (palavrasEncontradas.tamanho > 0) {
            printf("Elemento %d:\n", i);
            listarConjuntoPalavras(&palavrasEncontradas);
            liberarConjuntoPalavras(&palavrasEncontradas);
        }
    }
}

// Função para imprimir um AD_WORDS_HOLDER
void imprimirADWordsHolder(AD_WORDS_HOLDER adArray) {
    for (int i = 0; i < adArray.elementosInseridos; i++) {
        printf("Elemento %d:\n", i + 1);
        printf("  Data de Atualizacao: %d/%d/%d\n", adArray.array[i].dataAtualizacao.dia,
               adArray.array[i].dataAtualizacao.mes, adArray.array[i].dataAtualizacao.ano);

        printf("  Palavras:\n");
        listarConjuntoPalavras(&adArray.array[i].wordsHolder.conjuntoAlfanumerico1);
        // Adicione outras listagens conforme necessário

        printf("\n");
    }
}

// Função para pesquisar palavras e respectivos códigos UFP6 em determinados elementos do array
void pesquisarPalavrasAdHolder(AD_WORDS_HOLDER *adArray, int posicao) {
    if (posicao >= 0 && posicao < adArray->elementosInseridos) {
        // Implemente a lógica de pesquisa aqui usando adArray->array[posicao]
    } else {
        printf("Posição inválida para pesquisa.\n");
    }
}

/**
 * @brief Liberta a memória alocada para a estrutura AD_WORDS_HOLDER e seus elementos.
 *
 * Esta função liberta a memória alocada para o array de elementos dentro da estrutura AD_WORDS_HOLDER.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER cuja memória será libertada.
 * @note Após chamar esta função, a estrutura AD_WORDS_HOLDER não deve ser acessada, pois a memória associada foi libertada.
 */void liberarADWordsHolder(AD_WORDS_HOLDER *adArray) {
    free(adArray->array);
}

/**
 * @brief Exibe detalhes dos elementos presentes no array dentro da estrutura AD_WORDS_HOLDER.
 *
 * Esta função exibe informações detalhadas sobre cada elemento presente no array dentro da estrutura AD_WORDS_HOLDER,
 * incluindo data de atualização e conjuntos alfanuméricos associados.
 *
 * @param adArray Um ponteiro para a estrutura AD_WORDS_HOLDER cujos elementos serão listados.
 * @note Esta função assume que cada elemento contém uma estrutura wordsHolder com conjuntos alfanuméricos específicos.
 */
void listarElementosADWordsHolder(AD_WORDS_HOLDER *adArray) {
    printf("Elementos no array:\n");
    for (int i = 0; i < adArray->elementosInseridos; i++) {
        printf("Elemento %d:\n", i);
        printf("Data de Atualizacao: %02d/%02d/%04d\n",
               adArray->array[i].dataAtualizacao.dia,
               adArray->array[i].dataAtualizacao.mes,
               adArray->array[i].dataAtualizacao.ano);

        printf("Conjunto Alfanumérico 1:\n");
        listarConjuntoPalavras(&adArray->array[i].wordsHolder.conjuntoAlfanumerico1);

        printf("Conjunto Alfanumérico 2:\n");
        listarConjuntoPalavras(&adArray->array[i].wordsHolder.conjuntoAlfanumerico2);

        printf("Conjunto UFP61:\n");
        listarConjuntoPalavras(&adArray->array[i].wordsHolder.conjuntoUFP61);

        printf("Conjunto UFP62:\n");
        listarConjuntoPalavras(&adArray->array[i].wordsHolder.conjuntoUFP62);

        printf("\n");
    }
    printf("\n");
}

/**
 * @brief Escreve as palavras de um ConjuntoPalavras em um arquivo de texto.
 *
 * Esta função escreve as palavras presentes no ConjuntoPalavras para um arquivo de texto especificado.
 *
 * @param conjunto Um ponteiro para o ConjuntoPalavras cujas palavras serão escritas no arquivo.
 * @param nomeFicheiro O nome do arquivo de texto no qual as palavras serão escritas.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha ao abrir o arquivo para escrita.
 * @note Cada palavra é escrita em uma nova linha no arquivo.
 */
 int escreverConjuntoParaFicheiroTexto(const ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 0; // Falha ao abrir o arquivo
    }

    for (int i = 0; i < conjunto->tamanho; i++) {
        fprintf(arquivo, "%s\n", conjunto->palavras[i].palavra);
    }

    fclose(arquivo);
    return 1; // Sucesso
}

/**
 * @brief Lê palavras de um arquivo de texto para um ConjuntoPalavras.
 *
 * Esta função lê palavras de um arquivo de texto especificado e adiciona a um ConjuntoPalavras.
 *
 * @param conjunto Um ponteiro para o ConjuntoPalavras no qual as palavras serão armazenadas.
 * @param nomeFicheiro O nome do arquivo de texto do qual as palavras serão lidas.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha ao abrir o arquivo para leitura.
 * @note Cada linha do arquivo é considerada uma palavra, e o caractere de nova linha é removido.
 *       A função adicionarPalavra é usada para adicionar cada palavra ao ConjuntoPalavras.
 */int lerConjuntoDeFicheiroTexto(ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0; // Falha ao abrir o arquivo
    }

    char linha[100]; // Ajuste o tamanho conforme necessário
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; // Remover o caractere de nova linha
        adicionarPalavra(conjunto, linha);
    }

    fclose(arquivo);
    return 1; // Sucesso
}

// Função para escrever um AD_WORDS_HOLDER em um arquivo de texto
int escreverADWordsHolderParaFicheiroTexto(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 0; // Falha ao abrir o arquivo
    }

    for (int i = 0; i < adArray->elementosInseridos; i++) {
        fprintf(arquivo, "Elemento %d: Data de atualizacao: %d/%d/%d\n", i + 1,
                adArray->array[i].dataAtualizacao.dia, adArray->array[i].dataAtualizacao.mes,
                adArray->array[i].dataAtualizacao.ano);
    }

    fclose(arquivo);
    return 1; // Sucesso
}

// Função para ler um AD_WORDS_HOLDER de um arquivo de texto
// Função para ler um AD_WORDS_HOLDER de um arquivo de texto
int lerADWordsHolderDeFicheiroTexto(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0; // Falha ao abrir o arquivo
    }

    // Variáveis temporárias para armazenar os dados lidos do arquivo
    int dia, mes, ano;
    char palavra[100];  // Ajuste o tamanho conforme necessário

    while (fscanf(arquivo, "%s %d/%d/%d", palavra, &dia, &mes, &ano) == 4) {
        // Criar uma nova instância de VAL_AD_WORDS_HOLDER
        VAL_AD_WORDS_HOLDER novoElemento;
        novoElemento.dataAtualizacao.dia = dia;
        novoElemento.dataAtualizacao.mes = mes;
        novoElemento.dataAtualizacao.ano = ano;

        // Criar uma nova instância de WORDS_HOLDER e adicionar a palavra
        WORDS_HOLDER wordsHolder;
        wordsHolder.conjuntoAlfanumerico1 = criarConjuntoPalavras(10);
        adicionarPalavra(&wordsHolder.conjuntoAlfanumerico1, palavra);

        // Adicionar o VAL_AD_WORDS_HOLDER ao AD_WORDS_HOLDER
        adicionarAoAdWordsHolder(adArray, novoElemento);
    }

    fclose(arquivo);
    return 1; // Sucesso
}

/**
 * @brief Escreve um ConjuntoPalavras em um arquivo binário.
 *
 * Esta função escreve as palavras e códigos UFP6 presentes no ConjuntoPalavras em um arquivo binário especificado.
 *
 * @param conjunto Um ponteiro para o ConjuntoPalavras cujas palavras e códigos UFP6 serão escritos no arquivo.
 * @param nomeFicheiro O nome do arquivo binário no qual as palavras e códigos UFP6 serão escritos.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha ao abrir o arquivo para escrita.
 * @note Cada palavra é escrita junto com seu comprimento e cada código UFP6 é escrito no arquivo binário.
 */
 int escreverConjuntoParaFicheiroBinario(const ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 0; // Falha ao abrir o arquivo
    }

    // Escrever o número total de palavras no conjunto
    fwrite(&conjunto->tamanho, sizeof(int), 1, arquivo);

    // Escrever cada palavra e código UFP6 no arquivo
    for (int i = 0; i < conjunto->tamanho; ++i) {
        // Escrever o comprimento da palavra
        int comprimentoPalavra = strlen(conjunto->palavras[i].palavra);
        fwrite(&comprimentoPalavra, sizeof(int), 1, arquivo);

        // Escrever a palavra
        fwrite(conjunto->palavras[i].palavra, sizeof(char), comprimentoPalavra, arquivo);

        // Escrever o código UFP6
        fwrite(&conjunto->palavras[i].ufp6, sizeof(int), 1, arquivo);
    }

    fclose(arquivo);
    return 1; // Sucesso
}

/**
 * @brief Lê um ConjuntoPalavras de um arquivo binário.
 *
 * Esta função lê palavras e códigos UFP6 de um arquivo binário especificado e os armazena em um ConjuntoPalavras.
 *
 * @param conjunto Um ponteiro para o ConjuntoPalavras onde as palavras e códigos UFP6 serão armazenados.
 * @param nomeFicheiro O nome do arquivo binário do qual as palavras e códigos UFP6 serão lidos.
 * @return Retorna 1 em caso de sucesso e 0 em caso de falha ao abrir o arquivo para leitura.
 * @note A função aloca espaço para as palavras no conjunto e para cada palavra antes de ler os dados do arquivo.
 *       Certifique-se de libertar a memória alocada pelo conjunto após o uso usando a função liberarConjuntoPalavras.
 */
 int lerConjuntoDeFicheiroBinario(ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0; // Falha ao abrir o arquivo
    }

    // Ler o número total de palavras no conjunto
    fread(&conjunto->tamanho, sizeof(int), 1, arquivo);

    // Alocar espaço para as palavras no conjunto
    conjunto->palavras = (PalavraUFP6 *) malloc(conjunto->tamanho * sizeof(PalavraUFP6));

    // Ler cada palavra e código UFP6 do arquivo
    for (int i = 0; i < conjunto->tamanho; ++i) {
        // Ler o comprimento da palavra
        int comprimentoPalavra;
        fread(&comprimentoPalavra, sizeof(int), 1, arquivo);

        // Alocar espaço para a palavra
        conjunto->palavras[i].palavra = (char *) malloc((comprimentoPalavra + 1) * sizeof(char));

        // Ler a palavra
        fread(conjunto->palavras[i].palavra, sizeof(char), comprimentoPalavra, arquivo);
        conjunto->palavras[i].palavra[comprimentoPalavra] = '\0'; // Adicionar terminador nulo

        // Ler o código UFP6
        fread(&conjunto->palavras[i].ufp6, sizeof(int), 1, arquivo);
    }

    fclose(arquivo);
    return 1; // Sucesso
}