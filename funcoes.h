#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    char* palavra;
    char* ufp6;
} PalavraUFP6;

typedef struct {
    PalavraUFP6* palavras;
    int tamanho;
} ConjuntoPalavras;

// Constantes para critérios de ordenação
#define ALFABETICA 0
#define TAMANHO 1

// Constantes para ordem de ordenação
#define CRESCENTE 0
#define DECRESCENTE 1

char* converterCaracterParaUFP6(char caractere);
char* converterPalavraParaUFP6(const char* palavra);

PalavraUFP6 criarPalavraUFP6(const char* palavra);
ConjuntoPalavras criarConjuntoPalavras(int tamanhoInicial);
void adicionarPalavra(ConjuntoPalavras* conjunto, const char* palavra);
void listarConjuntoPalavras(const ConjuntoPalavras* conjunto);

char* gerarPalavraAleatoria(int comprimento);
void inserirPalavrasAleatorias(ConjuntoPalavras* conjunto, int numPalavras);
void removerPalavra(ConjuntoPalavras* conjunto, const char* palavra);

int verificarCombinacoesIguais(const ConjuntoPalavras* conjunto1, const ConjuntoPalavras* conjunto2);

ConjuntoPalavras pesquisarPalavras(const ConjuntoPalavras* conjunto, const char* sequencia);
ConjuntoPalavras obterCodigosPalavrasEncontradas(const ConjuntoPalavras* conjunto, const char* sequencia);

void ordenarConjuntoPalavras(ConjuntoPalavras* conjunto, int criterio, int ordem);


typedef struct {
    ConjuntoPalavras conjuntoAlfanumerico1;
    ConjuntoPalavras conjuntoAlfanumerico2;
    ConjuntoPalavras conjuntoUFP61;
    ConjuntoPalavras conjuntoUFP62;
} WORDS_HOLDER;
typedef struct {
    WORDS_HOLDER dados;
    char dataModificacao[20];  // Assumindo uma string para representar a data
} VAL_AD_WORDS_HOLDER;

typedef struct {
    int tamanho;
    int elementosInseridos;
    VAL_AD_WORDS_HOLDER* elementos;
} AD_WORDS_HOLDER;
// Alínea a
AD_WORDS_HOLDER criarADWordsHolder(int tamanhoInicial);

// Alínea b
void redimensionarADWordsHolder(AD_WORDS_HOLDER* adArray, int novoTamanho);

// Alínea c
void inserirElementoADWordsHolder(AD_WORDS_HOLDER* adArray, VAL_AD_WORDS_HOLDER novoElemento);

// Alínea d
void inserirElementoPosicaoADWordsHolder(AD_WORDS_HOLDER* adArray, VAL_AD_WORDS_HOLDER novoElemento, int posicao);

// Alínea d
void eliminarElementoPosicaoADWordsHolder(AD_WORDS_HOLDER* adArray, int posicao);

// Alínea e
VAL_AD_WORDS_HOLDER* pesquisarElementoPorDataADWordsHolder(const AD_WORDS_HOLDER* adArray, const char* data);

// Novas estruturas e funções para manipulação de ficheiros
int escreverConjuntoParaFicheiro(const ConjuntoPalavras *conjunto, const char *nomeFicheiro);
int lerConjuntoDeFicheiro(ConjuntoPalavras *conjunto, const char *nomeFicheiro);

int escreverADWordsHolderParaFicheiro(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);
int lerADWordsHolderDeFicheiro(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);

int escreverConjuntoParaFicheiroBinario(const ConjuntoPalavras *conjunto, const char *nomeFicheiro);
int lerConjuntoDeFicheiroBinario(ConjuntoPalavras *conjunto, const char *nomeFicheiro);

int escreverADWordsHolderParaFicheiroBinario(const AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);
int lerADWordsHolderDeFicheiroBinario(AD_WORDS_HOLDER *adArray, const char *nomeFicheiro);
#endif  // FUNCOES_H
