//
// Created by barba on 18/12/2023.
//

#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para converter um caractere para UFP6
char *converterCaracterParaUFP6(char caractere) {
    // Tabela de codificação UFP6 para dígitos e letras minúsculas
    const char *ufp6Table[36] = {
            "000000", "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001",
            "001010", "001011", "001100", "001101", "001110", "001111", "010000", "010001", "010010", "010011",
            "010100",
            "010101", "010110", "010111", "0011000", "011001", "011010", "011011", "011100", "011101", "011110",
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

// Função auxiliar para converter uma palavra para UFP6
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

// Função auxiliar para criar uma estrutura PalavraUFP6
PalavraUFP6 criarPalavraUFP6(const char *palavra) {
    PalavraUFP6 palavraUFP6;
    palavraUFP6.palavra = strdup(palavra);
    palavraUFP6.ufp6 = converterPalavraParaUFP6(palavra);
    return palavraUFP6;
}

// Função principal para criar um conjunto de palavras
ConjuntoPalavras criarConjuntoPalavras(int tamanhoInicial) {
    ConjuntoPalavras conjunto;
    conjunto.palavras = (PalavraUFP6 *) malloc(tamanhoInicial * sizeof(PalavraUFP6));
    conjunto.tamanho = 0;
    return conjunto;
}

// Função para adicionar uma palavra ao conjunto
void adicionarPalavra(ConjuntoPalavras *conjunto, const char *palavra) {
    if (conjunto->tamanho % 10 == 0) {
        conjunto->palavras = (PalavraUFP6 *) realloc(conjunto->palavras,
                                                     (conjunto->tamanho + 10) * sizeof(PalavraUFP6));
    }

    conjunto->palavras[conjunto->tamanho] = criarPalavraUFP6(palavra);
    conjunto->tamanho++;
}

// Função para listar o conjunto de palavras
void listarConjuntoPalavras(const ConjuntoPalavras *conjunto) {
    for (int i = 0; i < conjunto->tamanho; i++) {
        printf("Palavra: %s, UFP6: %s\n", conjunto->palavras[i].palavra, conjunto->palavras[i].ufp6);
    }
}

// Função para liberar a memória alocada pelo conjunto de palavras
void liberarConjuntoPalavras(ConjuntoPalavras *conjunto) {
    for (int i = 0; i < conjunto->tamanho; i++) {
        free(conjunto->palavras[i].palavra);
        free(conjunto->palavras[i].ufp6);
    }
    free(conjunto->palavras);
}

// Função auxiliar para gerar uma palavra aleatória
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

// Função para inserir palavras aleatórias no conjunto
void inserirPalavrasAleatorias(ConjuntoPalavras *conjunto, int numPalavras) {
    for (int i = 0; i < numPalavras; ++i) {
        char *palavraAleatoria = gerarPalavraAleatoria(7); // Altere conforme necessário
        adicionarPalavra(conjunto, palavraAleatoria);
        free(palavraAleatoria);
    }
}

// Função para remover uma palavra do conjunto
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

// Função para verificar se uma combinação de palavras do conjunto1 é igual a outra combinação do conjunto2
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

// Função para pesquisar palavras no conjunto que contenham a sequência de pesquisa
ConjuntoPalavras pesquisarPalavras(const ConjuntoPalavras *conjunto, const char *sequencia) {
    ConjuntoPalavras palavrasEncontradas = criarConjuntoPalavras(10); // Inicialização com um tamanho arbitrário

    for (int i = 0; i < conjunto->tamanho; i++) {
        if (strstr(conjunto->palavras[i].palavra, sequencia) != NULL) {
            adicionarPalavra(&palavrasEncontradas, conjunto->palavras[i].palavra);
        }
    }

    return palavrasEncontradas;
}

// Função para obter os códigos binários das palavras encontradas na pesquisa
ConjuntoPalavras obterCodigosPalavrasEncontradas(const ConjuntoPalavras *conjunto, const char *sequencia) {
    ConjuntoPalavras palavrasEncontradas = pesquisarPalavras(conjunto, sequencia);

    // Atualizar os códigos binários das palavras encontradas
    for (int i = 0; i < palavrasEncontradas.tamanho; i++) {
        free(palavrasEncontradas.palavras[i].ufp6);
        palavrasEncontradas.palavras[i].ufp6 = converterPalavraParaUFP6(palavrasEncontradas.palavras[i].palavra);
    }

    return palavrasEncontradas;
}

// Função de comparação para qsort: ordem alfabética crescente
int compararPalavrasCrescente(const void *a, const void *b) {
    return strcmp(((PalavraUFP6 *) a)->palavra, ((PalavraUFP6 *) b)->palavra);
}

// Função de comparação para qsort: ordem alfabética decrescente
int compararPalavrasDecrescente(const void *a, const void *b) {
    return strcmp(((PalavraUFP6 *) b)->palavra, ((PalavraUFP6 *) a)->palavra);
}

// Função de comparação para qsort: ordem de tamanho crescente
int compararTamanhosCrescente(const void *a, const void *b) {
    return strlen(((PalavraUFP6 *) a)->palavra) - strlen(((PalavraUFP6 *) b)->palavra);
}

// Função de comparação para qsort: ordem de tamanho decrescente
int compararTamanhosDecrescente(const void *a, const void *b) {
    return strlen(((PalavraUFP6 *) b)->palavra) - strlen(((PalavraUFP6 *) a)->palavra);
}

// Função para ordenar o conjunto de palavras por critério específico
void ordenarConjuntoPalavras(ConjuntoPalavras *conjunto, int criterio, int ordem) {
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
// Função para comparar datas (retorna <0 se a primeira for anterior à segunda, 0 se iguais, >0 se posterior)
    int compararDatas(Data data1, Data data2) {
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
AD_WORDS_HOLDER criarAdWordsHolder(int tamanhoInicial) {
    AD_WORDS_HOLDER adArray;
    adArray.tamanho = tamanhoInicial;
    adArray.elementosInseridos = 0;
    adArray.array = (VAL_AD_WORDS_HOLDER *)malloc(tamanhoInicial * sizeof(VAL_AD_WORDS_HOLDER));
    return adArray;
}

// Função para redimensionar o array dinâmico
void redimensionarADWordsHolder(AD_WORDS_HOLDER *adArray, int novoTamanho) {
    adArray->tamanho = novoTamanho;
    adArray->array = realloc(adArray->array, novoTamanho * sizeof(VAL_AD_WORDS_HOLDER));
}
VAL_AD_WORDS_HOLDER criarValAdWordsHolder(WORDS_HOLDER dados, Data dataAtualizacao) {
    VAL_AD_WORDS_HOLDER val;
    val.wordsHolder = dados;
    val.dataAtualizacao = dataAtualizacao;
    return val;
}


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

// Função para inserir um elemento no array, ordenado cronologicamente pelas datas de modificação
void inserirElementoOrdenado(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER elemento) {
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

// Função para inserir um elemento no array numa dada posição/índice, ajustando as posições dos restantes elementos
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

// Função para eliminar um elemento no array que está numa dada posição/índice, ajustando as posições dos restantes elementos
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

// Função para pesquisar palavras e respectivos códigos UFP6 em determinados elementos do array
void pesquisarPalavrasEmElementos(AD_WORDS_HOLDER *adArray, const char *palavraPesquisa) {
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

// Função para liberar a memória alocada para o array dinâmico
void liberarADWordsHolder(AD_WORDS_HOLDER *adArray) {
    free(adArray->array);
}
// Função para listar os elementos no array
// Função para listar os elementos no array
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

// Função para escrever um conjunto de palavras em um arquivo de texto
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

// Função para ler um conjunto de palavras de um arquivo de texto
int lerConjuntoDeFicheiroTexto(ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
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
                adArray->array[i].dataAtualizacao.dia, adArray->array[i].dataAtualizacao.mes, adArray->array[i].dataAtualizacao.ano);
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

// Função para escrever um conjunto de palavras e códigos UFP6 em um arquivo binário
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

// Função para ler um conjunto de palavras e códigos UFP6 de um arquivo binário
int lerConjuntoDeFicheiroBinario(ConjuntoPalavras *conjunto, const char *nomeFicheiro) {
    FILE *arquivo = fopen(nomeFicheiro, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0; // Falha ao abrir o arquivo
    }

    // Ler o número total de palavras no conjunto
    fread(&conjunto->tamanho, sizeof(int), 1, arquivo);

    // Alocar espaço para as palavras no conjunto
    conjunto->palavras = (PalavraUFP6 *)malloc(conjunto->tamanho * sizeof(PalavraUFP6));

    // Ler cada palavra e código UFP6 do arquivo
    for (int i = 0; i < conjunto->tamanho; ++i) {
        // Ler o comprimento da palavra
        int comprimentoPalavra;
        fread(&comprimentoPalavra, sizeof(int), 1, arquivo);

        // Alocar espaço para a palavra
        conjunto->palavras[i].palavra = (char *)malloc((comprimentoPalavra + 1) * sizeof(char));

        // Ler a palavra
        fread(conjunto->palavras[i].palavra, sizeof(char), comprimentoPalavra, arquivo);
        conjunto->palavras[i].palavra[comprimentoPalavra] = '\0'; // Adicionar terminador nulo

        // Ler o código UFP6
        fread(&conjunto->palavras[i].ufp6, sizeof(int), 1, arquivo);
    }

    fclose(arquivo);
    return 1; // Sucesso
}