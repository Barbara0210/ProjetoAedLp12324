#ifndef FUNCOES_H
#define FUNCOES_H

#include <time.h>

// Constantes para critérios de ordenação
#define ALFABETICA 0
#define TAMANHO 1

// Constantes para ordem de ordenação
#define CRESCENTE 0
#define DECRESCENTE 1
#define ALFABETO "0123456789abcdefghijklmnopqrstuvwxyz"

typedef struct {
    char *palavra;
    char *ufp6;
} PalavraUFP6;

typedef struct {
    PalavraUFP6 *palavras;
    int tamanho;
} ConjuntoPalavras;

//requisito7
typedef struct {
    ConjuntoPalavras conjuntoAlfanumerico1;  // Matriz de palavras alfanuméricas do conjunto 1
    ConjuntoPalavras conjuntoAlfanumerico2;  // Matriz de palavras alfanuméricas do conjunto 2
    ConjuntoPalavras conjuntoUFP61;  // Matriz de palavras codificadas em UFP6 do conjunto 1
    ConjuntoPalavras conjuntoUFP62;  // Matriz de palavras codificadas em UFP6 do conjunto 2
} WORDS_HOLDER;

// Estrutura que define a data
typedef struct {
    int dia, mes, ano;
} Data;

// Estrutura que define um VAL_AD_WORDS_HOLDER
typedef struct {
    WORDS_HOLDER wordsHolder;
    Data dataAtualizacao;
} VAL_AD_WORDS_HOLDER;

// Estrutura que define o Array Dinâmico AD_WORDS_HOLDER
typedef struct {
    int tamanho;
    int elementosInseridos;
    VAL_AD_WORDS_HOLDER *array;
} AD_WORDS_HOLDER;


//Requisito1
ConjuntoPalavras criarConjuntoPalavras(int tamanhoInicial);

void adicionarPalavra(ConjuntoPalavras *conjunto, const char *palavra);

void listarConjuntoPalavras(const ConjuntoPalavras *conjunto);

void liberarConjuntoPalavras(ConjuntoPalavras *conjunto);

//Requisito2
char *converterCaracterParaUFP6(char caractere);

char *converterPalavraParaUFP6(const char *palavra);

PalavraUFP6 criarPalavraUFP6(const char *palavra);

//Requisito3
char *gerarPalavraAleatoria(int comprimento);

void inserirPalavrasAleatorias(ConjuntoPalavras *conjunto, int numPalavras);

void removerPalavra(ConjuntoPalavras *conjunto, const char *palavra);

void removerPalavraPorIndice(ConjuntoPalavras *conjunto, int indice);


//Requisito4
int verificarCombinacoesIguais(const ConjuntoPalavras *conjunto1, const ConjuntoPalavras *conjunto2);

//Requisito5
ConjuntoPalavras pesquisarPalavras(const ConjuntoPalavras *conjunto, const char *sequencia);

ConjuntoPalavras obterCodigosPalavrasEncontradas(const ConjuntoPalavras *conjunto, const char *sequencia);

//Requisito6
void ordenarConjuntoPalavras(ConjuntoPalavras *conjunto, int criterio, int ordem);

int compararDatas(Data data1, Data data2);
//Requisito 8

AD_WORDS_HOLDER criarAdWordsHolder(int tamanhoInicial);

void redimensionarADWordsHolder(AD_WORDS_HOLDER *adArray, int novoTamanho);

VAL_AD_WORDS_HOLDER criarValAdWordsHolder(WORDS_HOLDER dados, Data dataAtualizacao);

void adicionarAoAdWordsHolder(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER val);

void inserirOrdenadoPorData(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER val);

void inserirElementoADWordsHolder(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER novoElemento);

void inserirNoIndice(AD_WORDS_HOLDER *ad_holder, VAL_AD_WORDS_HOLDER val, int indice);

void inserirElementoPosicaoADWordsHolder(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER novoElemento, int posicao);

void eliminarElementoPosicaoADWordsHolder(AD_WORDS_HOLDER *adArray, int posicao);

void imprimirADWordsHolder(AD_WORDS_HOLDER adArray);

void pesquisarPalavrasAdHolder(AD_WORDS_HOLDER *adArray, int posicao);

void inserirElementoOrdenado(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER elemento);
void inserirElementoNaPosicao(AD_WORDS_HOLDER *adArray, VAL_AD_WORDS_HOLDER elemento, int posicao);
void eliminarElementoNaPosicao(AD_WORDS_HOLDER *adArray, int posicao);
void pesquisarPalavrasEmElementos(AD_WORDS_HOLDER *adArray, const char *palavraPesquisa);
void liberarADWordsHolder(AD_WORDS_HOLDER *adArray);
void listarElementosADWordsHolder(AD_WORDS_HOLDER *adArray);

//Requisito11
int escreverConjuntoParaFicheiroBinario(const ConjuntoPalavras *conjunto, const char *nomeFicheiro);

int lerConjuntoDeFicheiroBinario(ConjuntoPalavras *conjunto, const char *nomeFicheiro);

int escreverADWordsHolderParaFicheiroBinario(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);

int lerADWordsHolderDeFicheiroBinario(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);

int escreverConjuntoParaFicheiroTexto(const ConjuntoPalavras *conjunto, const char *nomeFicheiro);
int lerConjuntoDeFicheiroTexto(ConjuntoPalavras *conjunto, const char *nomeFicheiro);
int escreverADWordsHolderParaFicheiroTexto(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);
int lerADWordsHolderDeFicheiroTexto(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);

int escreverConjuntoParaFicheiroBinario(const ConjuntoPalavras *conjunto, const char *nomeFicheiro);
int lerConjuntoDeFicheiroBinario(ConjuntoPalavras *conjunto, const char *nomeFicheiro);
#endif  // FUNCOES_H
