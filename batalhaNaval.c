#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
#define TAMANHO 10
#define TAMANHO_HAB 5





// Verifica se uma célula está dentro do tabuleiro
int dentroDosLimites(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO;
}


    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = 0;
}
// Imprime o cabeçalho e o conteúdo do tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("  ");
    for (char c = 'A'; c < 'A' + TAMANHO; c++) {
        printf(" %c", c); // Letras A-J
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d", i + 1); // Números 1-10
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d", tabuleiro[i][j]); // Conteúdo: 0 = água, 3 = navio, 5 = área afetada
        }
        printf("\n");
    }
}

// Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

// Posiciona navios
void posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        if (dentroDosLimites(linha, coluna + i))
            tabuleiro[linha][coluna + i] = 3;
}

void posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        if (dentroDosLimites(linha + i, coluna))
            tabuleiro[linha + i][coluna] = 3;
}

void posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        if (dentroDosLimites(linha + i, coluna + i))
            tabuleiro[linha + i][coluna + i] = 3;
}

void posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        if (dentroDosLimites(linha + i, coluna - i))
            tabuleiro[linha + i][coluna - i] = 3;
}
 
    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

// Gera habilidade em Cruz dinamicamente
void gerarMatrizHabilidadeCruz(int matriz[TAMANHO_HAB][TAMANHO_HAB]) {
    int centro = TAMANHO_HAB / 2;
    for (int i = 0; i < TAMANHO_HAB; i++) {
        for (int j = 0; j < TAMANHO_HAB; j++) {
            if (i == centro || j == centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera habilidade em Cone dinamicamente
void gerarMatrizHabilidadeCone(int matriz[TAMANHO_HAB][TAMANHO_HAB]) {
    int centro = TAMANHO_HAB / 2;
    for (int i = 0; i < TAMANHO_HAB; i++) {
        for (int j = 0; j < TAMANHO_HAB; j++) {
            if (j >= centro - i && j <= centro + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera habilidade em Octaedro dinamicamente
void gerarMatrizHabilidadeOctaedro(int matriz[TAMANHO_HAB][TAMANHO_HAB]) {
    int centro = TAMANHO_HAB / 2;
    for (int i = 0; i < TAMANHO_HAB; i++) {
        for (int j = 0; j < TAMANHO_HAB; j++) {
            int distancia = (i > centro ? i - centro : centro - i) +
                            (j > centro ? j - centro : centro - j);
            if (distancia <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int matriz[TAMANHO_HAB][TAMANHO_HAB], int linhaCentro, int colunaCentro) {
    int centro = TAMANHO_HAB / 2;

    for (int i = 0; i < TAMANHO_HAB; i++) {
        for (int j = 0; j < TAMANHO_HAB; j++) {
            int linha = linhaCentro + i - centro;
            int coluna = colunaCentro + j - centro;
            if (matriz[i][j] == 1 && dentroDosLimites(linha, coluna) && tabuleiro[linha][coluna] != 3)
                tabuleiro[linha][coluna] = 5;
        }
    }
}

// Função principal
int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int habilidade[TAMANHO_HAB][TAMANHO_HAB];

    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    posicionarNavioHorizontal(tabuleiro, 1, 1);
    posicionarNavioVertical(tabuleiro, 4, 6);
    posicionarNavioDiagonalPrincipal(tabuleiro, 6, 0);
    posicionarNavioDiagonalSecundaria(tabuleiro, 5, 9);

    // Aplica habilidade em Cruz
    gerarMatrizHabilidadeCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 3, 3);

    // Aplica habilidade em Cone
    gerarMatrizHabilidadeCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 0, 7);

    // Aplica habilidade em Octaedro
    gerarMatrizHabilidadeOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 6, 6);

    // Exibe o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}