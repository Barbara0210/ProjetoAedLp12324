#include <stdio.h>
#include   "C:\Users\barba\CLionProjects\ProjetoAedLp12023\libs_src\lib_util.h"

#include "funcoes.h"

// Função de teste para verificar a criação e adição de palavras em um conjunto
void testeRequisito1_2() {
    printf("### Teste Requisito 1 ###\n");

    // Criar conjunto de palavras
    ConjuntoPalavras conjunto = criarConjuntoPalavras(10);

    // Adicionar palavras ao conjunto
    adicionarPalavra(&conjunto, "aba");
    adicionarPalavra(&conjunto, "2");
    adicionarPalavra(&conjunto, "passaro");

    // Listar o conjunto de palavras
    listarConjuntoPalavras(&conjunto);

    // Liberar memória alocada
    free(conjunto.palavras);

    printf("### Fim do Teste Requisito 1 ###\n");
}

void testeRequisito3() {
    printf("### Teste Requisito 3 ###\n");

    // Criar conjunto de palavras
    ConjuntoPalavras conjunto = criarConjuntoPalavras(10);

    // Inserir palavras aleatórias no conjunto
    inserirPalavrasAleatorias(&conjunto, 5);

    // Listar o conjunto de palavras antes da remocao
    printf("Antes da remocao:\n");
    listarConjuntoPalavras(&conjunto);

    // Remover uma palavra do conjunto
    removerPalavraPorIndice(&conjunto, 1);

    // Listar o conjunto de palavras após a remoção
    printf("Apos a remocao:\n");
    listarConjuntoPalavras(&conjunto);

    // Liberar memória alocada
    for (int i = 0; i < conjunto.tamanho; ++i) {
        free(conjunto.palavras[i].palavra);
        free(conjunto.palavras[i].ufp6);
    }
    free(conjunto.palavras);

    printf("### Fim do Teste Requisito 3 ###\n");
}

void testeRequisito4() {
    printf("### Teste Requisito 4 ###\n");

    // Criar conjunto de palavras 1
    ConjuntoPalavras conjunto1 = criarConjuntoPalavras(10);

    // Adicionar palavras ao conjunto 1
    adicionarPalavra(&conjunto1, "gato");
    adicionarPalavra(&conjunto1, "cachorro");
    adicionarPalavra(&conjunto1, "passaro");

    // Criar conjunto de palavras 2
    ConjuntoPalavras conjunto2 = criarConjuntoPalavras(10);

    // Adicionar palavras ao conjunto 2
    adicionarPalavra(&conjunto2, "gatocachorro");
    adicionarPalavra(&conjunto2, "passaro");

    // Verificar combinações iguais
    if (verificarCombinacoesIguais(&conjunto1, &conjunto2)) {
        printf("Combinacao igual encontrada.\n");
    } else {
        printf("Nenhuma combinacao igual encontrada.\n");
    }

    // Liberar memória alocada
    free(conjunto1.palavras);
    free(conjunto2.palavras);

    printf("### Fim do Teste Requisito 4 ###\n");
}

void testeRequisito5() {
    printf("### Teste Requisito 5 ###\n");

    // Criar conjuntos de palavras
    ConjuntoPalavras conjunto1 = criarConjuntoPalavras(10);
    ConjuntoPalavras conjunto2 = criarConjuntoPalavras(10);

    // Adicionar palavras aos conjuntos
    adicionarPalavra(&conjunto1, "programacao");
    adicionarPalavra(&conjunto1, "algoritmo");
    adicionarPalavra(&conjunto1, "linguagem");
    adicionarPalavra(&conjunto2, "programador");
    adicionarPalavra(&conjunto2, "computador");
    adicionarPalavra(&conjunto2, "algoritmo");

    // Pesquisar palavras nos conjuntos
    const char *sequenciaPesquisa = "pro";
    ConjuntoPalavras palavrasEncontradas1 = pesquisarPalavras(&conjunto1, sequenciaPesquisa);
    ConjuntoPalavras palavrasEncontradas2 = pesquisarPalavras(&conjunto2, sequenciaPesquisa);

    // Imprimir palavras encontradas
    printf("Palavras encontradas no conjunto 1:\n");
    listarConjuntoPalavras(&palavrasEncontradas1);

    printf("Palavras encontradas no conjunto 2:\n");
    listarConjuntoPalavras(&palavrasEncontradas2);

    // Obter códigos binários das palavras encontradas
    ConjuntoPalavras codigosEncontrados1 = obterCodigosPalavrasEncontradas(&conjunto1, sequenciaPesquisa);
    ConjuntoPalavras codigosEncontrados2 = obterCodigosPalavrasEncontradas(&conjunto2, sequenciaPesquisa);

    // Imprimir códigos binários das palavras encontradas
    printf("Codigos binarios das palavras encontradas no conjunto 1:\n");
    listarConjuntoPalavras(&codigosEncontrados1);

    printf("Codigos binarios das palavras encontradas no conjunto 2:\n");
    listarConjuntoPalavras(&codigosEncontrados2);

    // Liberar memória alocada
    free(conjunto1.palavras);
    free(conjunto2.palavras);
    free(palavrasEncontradas1.palavras);
    free(palavrasEncontradas2.palavras);
    free(codigosEncontrados1.palavras);
    free(codigosEncontrados2.palavras);

    printf("### Fim do Teste Requisito 5 ###\n");
}

// Função de teste para o requisito 6
void testeRequisito6() {
    printf("### Teste Requisito 6 ###\n");

    // Criar conjunto de palavras
    ConjuntoPalavras conjunto = criarConjuntoPalavras(10);

    // Adicionar palavras ao conjunto
    adicionarPalavra(&conjunto, "gato");
    adicionarPalavra(&conjunto, "cachorro");
    adicionarPalavra(&conjunto, "passaro");
    adicionarPalavra(&conjunto, "abelha");

    // Listar o conjunto de palavras antes de ordenar
    printf("Antes de ordenar:\n");
    listarConjuntoPalavras(&conjunto);

    // Ordenar por ordem alfabética crescente
    ordenarConjuntoPalavras(&conjunto, ALFABETICA, CRESCENTE);

    // Listar o conjunto de palavras após ordenar
    printf("\nDepois de ordenar alfabeticamente (crescente):\n");
    listarConjuntoPalavras(&conjunto);

    // Ordenar por ordem de tamanho decrescente
    ordenarConjuntoPalavras(&conjunto, TAMANHO, DECRESCENTE);

    // Listar o conjunto de palavras após ordenar
    printf("\nDepois de ordenar por tamanho (decrescente):\n");
    listarConjuntoPalavras(&conjunto);

    // Liberar memória alocada
    for (int i = 0; i < conjunto.tamanho; i++) {
        free(conjunto.palavras[i].palavra);
        free(conjunto.palavras[i].ufp6);
    }
    free(conjunto.palavras);

    printf("### Fim do Teste Requisito 6 ###\n");
}

/*
// Função de teste para o requisito 10

    void testarLeituraEscritaFicheiro() {
        // Criar um conjunto de palavras para teste
        ConjuntoPalavras conjuntoTeste;
        conjuntoTeste = criarConjuntoPalavras(50);

        adicionarPalavra(&conjuntoTeste, "Cachorro");
        adicionarPalavra(&conjuntoTeste, "Gato");
        adicionarPalavra(&conjuntoTeste, "Elefante");

        // Escrever o conjunto de palavras em um ficheiro de texto
        escreverConjuntoParaFicheiro(&conjuntoTeste, "output_conjunto.txt");

        // Limpar o conjunto antes de ler
        liberarConjuntoPalavras(&conjuntoTeste);

        // Ler o conjunto de palavras do ficheiro de texto
       lerConjuntoDeFicheiro(&conjuntoTeste, "output_conjunto.txt");

        // Imprimir o conjunto de palavras lido (apenas para verificação)
      imprimirConjuntoPalavras(&conjuntoTeste);


    }*/
// Função de teste para escrever um conjunto de palavras em um arquivo de texto
void testeEscreverConjuntoTexto() {
    ConjuntoPalavras conjuntoTeste = criarConjuntoPalavras(10);

    adicionarPalavra(&conjuntoTeste, "teste1");
    adicionarPalavra(&conjuntoTeste, "teste2");
    adicionarPalavra(&conjuntoTeste, "teste3");

    if (escreverConjuntoParaFicheiroTexto(&conjuntoTeste, "conjunto_teste.txt")) {
        printf("Conjunto de palavras escrito com sucesso.\n");
    } else {
        printf("Falha ao escrever o conjunto de palavras.\n");
    }

    liberarConjuntoPalavras(&conjuntoTeste);
}

// Função de teste para ler um conjunto de palavras de um arquivo de texto
void testeLerConjuntoTexto() {
    ConjuntoPalavras conjuntoTeste = criarConjuntoPalavras(10);

    if (lerConjuntoDeFicheiroTexto(&conjuntoTeste, "conjunto_teste.txt")) {
        printf("Conjunto de palavras lido com sucesso.\n");
        listarConjuntoPalavras(&conjuntoTeste);
    } else {
        printf("Falha ao ler o conjunto de palavras.\n");
    }

    liberarConjuntoPalavras(&conjuntoTeste);
}

// Função de teste para escrever um AD_WORDS_HOLDER em um arquivo de texto
void testeEscreverADWordsHolderTexto() {
    AD_WORDS_HOLDER adArrayTeste = criarAdWordsHolder(10);

    VAL_AD_WORDS_HOLDER val1, val2,val3;
    val1.dataAtualizacao.dia = 10;
    val1.dataAtualizacao.mes = 5;
    val1.dataAtualizacao.ano = 2022;

    val2.dataAtualizacao.dia = 15;
    val2.dataAtualizacao.mes = 8;
    val2.dataAtualizacao.ano = 2023;

    val3.dataAtualizacao.dia = 16;
    val3.dataAtualizacao.mes = 9;
    val3.dataAtualizacao.ano = 2023;

    adicionarAoAdWordsHolder(&adArrayTeste, val1);
    adicionarAoAdWordsHolder(&adArrayTeste, val2);
    adicionarAoAdWordsHolder(&adArrayTeste, val3);


    if (escreverADWordsHolderParaFicheiroTexto(&adArrayTeste, "ad_array_teste.txt")) {
        printf("AD_WORDS_HOLDER escrito com sucesso.\n");
    } else {
        printf("Falha ao escrever o AD_WORDS_HOLDER.\n");
    }
}

// Função de teste para ler um AD_WORDS_HOLDER de um arquivo de texto
void testeLerADWordsHolderTexto() {
    AD_WORDS_HOLDER adArrayTeste = criarAdWordsHolder(10);

    if (lerADWordsHolderDeFicheiroTexto(&adArrayTeste, "ad_array_teste.txt")) {
        printf("AD_WORDS_HOLDER lido com sucesso.\n");
        imprimirADWordsHolder(adArrayTeste);
    } else {
        printf("Falha ao ler o AD_WORDS_HOLDER.\n");
    }
}

// Função de teste para escrever e ler um conjunto de palavras em um arquivo binário
void testeEscreverLerConjuntoBinario() {
    printf("### Teste Escrever e Ler Conjunto Binario ###\n");

    // Criar um conjunto de palavras para teste
    ConjuntoPalavras conjuntoTeste = criarConjuntoPalavras(10);
    adicionarPalavra(&conjuntoTeste, "Cachorro");
    adicionarPalavra(&conjuntoTeste, "Gato");
    adicionarPalavra(&conjuntoTeste, "Elefante");

    // Escrever o conjunto de palavras em um arquivo binário
    if (escreverConjuntoParaFicheiroBinario(&conjuntoTeste, "conjunto_binario.bin")) {
        printf("Conjunto de palavras escrito com sucesso.\n");

        // Limpar o conjunto antes de ler
        liberarConjuntoPalavras(&conjuntoTeste);

        // Ler o conjunto de palavras do arquivo binário
        if (lerConjuntoDeFicheiroBinario(&conjuntoTeste, "conjunto_binario.bin")) {
            printf("Conjunto de palavras lido com sucesso.\n");
            listarConjuntoPalavras(&conjuntoTeste);
        } else {
            printf("Falha ao ler o conjunto de palavras do arquivo binario.\n");
        }
    } else {
        printf("Falha ao escrever o conjunto de palavras no arquivo binario.\n");
    }

    liberarConjuntoPalavras(&conjuntoTeste);
    printf("### Fim do Teste Escrever e Ler Conjunto Binario ###\n");
}

int main() {
    // Chamar a função de teste do Requisito 1
    //testeRequisito1_2();
    //testeRequisito3();
    // testeRequisito4();
    // testeRequisito5();
    // testeRequisito6();
    //testeAlineaA();
    //  testeAlineaB();
//testeRequisito8();
    //testeEscreverConjuntoTexto();
   // testeLerConjuntoTexto();
   // testeEscreverADWordsHolderTexto();
   // testeLerADWordsHolderTexto();
   // testeEscreverLerConjuntoBinario();


    return 0;
}


