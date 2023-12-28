#include <stdio.h>
#include   "C:\Users\barba\CLionProjects\ProjetoAedLp12023\libs_src\lib_util.h"

#include "funcoes.h"


int main() {
    // Criar conjuntos de palavras
    ConjuntoPalavras conjunto1 = criarConjuntoPalavras(10);
    ConjuntoPalavras conjunto2 = criarConjuntoPalavras(10);

    // Adicionar palavras aos conjuntos
    adicionarPalavra(&conjunto1, "ola");
    adicionarPalavra(&conjunto1, "mundo");
    adicionarPalavra(&conjunto1, "teste");

    adicionarPalavra(&conjunto2, "hello");
    adicionarPalavra(&conjunto2, "world");
    adicionarPalavra(&conjunto2, "test");

    // Listar palavras e códigos UFP6 dos conjuntos
    printf("Conjunto 1:\n");
    listarConjuntoPalavras(&conjunto1);

    printf("\nConjunto 2:\n");
    listarConjuntoPalavras(&conjunto2);

    // Liberar memória alocada
    for (int i = 0; i < conjunto1.tamanho; i++) {
        free(conjunto1.palavras[i].palavra);
        free(conjunto1.palavras[i].ufp6);
    }
    free(conjunto1.palavras);

    for (int i = 0; i < conjunto2.tamanho; i++) {
        free(conjunto2.palavras[i].palavra);
        free(conjunto2.palavras[i].ufp6);
    }
    free(conjunto2.palavras);

    return 0;
}


