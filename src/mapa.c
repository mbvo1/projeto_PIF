#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "mapa.h"

#define OFF_X 4
#define OFF_Y 3

void carregar_mapa(Mapa *mapa, char *arquivo)
{
    FILE *arq;
    char linha[40];
    int y = 0;
    int i, j;
    int tam;

    arq = fopen(arquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir %s\n", arquivo);
        exit(1);
    }

    mapa->celulas = malloc(20 * sizeof(char *));
    mapa->altura = 0;
    mapa->largura = 0;

    while (fgets(linha, 40, arq) != NULL && y < 20) {
        for (i = 0; linha[i] != '\0'; i++) {
            if (linha[i] == '\n' || linha[i] == '\r') {
                linha[i] = '\0';
            }
        }
        if (linha[0] == '\0') {
            continue;
        }

        tam = strlen(linha);
        if (tam > mapa->largura) {
            mapa->largura = tam;
        }

        mapa->celulas[y] = malloc(40);
        strcpy(mapa->celulas[y], linha);
        y++;
    }
    fclose(arq);

    mapa->altura = y;

    for (i = 0; i < mapa->altura; i++) {
        tam = strlen(mapa->celulas[i]);
        for (j = tam; j < mapa->largura; j++) {
            mapa->celulas[i][j] = ' ';
        }
        mapa->celulas[i][mapa->largura] = '\0';
    }
}

char ler_celula(Mapa *mapa, int x, int y)
{
    if (x < 0 || y < 0 || x >= mapa->largura || y >= mapa->altura) {
        return '#';
    }
    return mapa->celulas[y][x];
}

void mudar_celula(Mapa *mapa, int x, int y, char valor)
{
    if (x < 0 || y < 0 || x >= mapa->largura || y >= mapa->altura) {
        return;
    }
    mapa->celulas[y][x] = valor;
}

void desenhar_mapa(Mapa *mapa)
{
    int x, y;
    char c;

    screenBoxEnable();

    for (y = 0; y < mapa->altura; y++) {
        for (x = 0; x < mapa->largura; x++) {
            c = ler_celula(mapa, x, y);
            screenGotoxy(OFF_X + x, OFF_Y + y);

            if (c == '#') {
                screenSetColor(LIGHTGRAY, DARKGRAY);
                printf("%c", BOX_BLOCK);
            } else if (c == '%') {
                screenSetColor(YELLOW, BROWN);
                printf("%c", BOX_BLOCK);
            } else {
                screenSetColor(BLACK, BLACK);
                printf(" ");
            }
        }
    }

    screenBoxDisable();
}

void liberar_mapa(Mapa *mapa)
{
    int i;

    if (mapa->celulas == NULL) {
        return;
    }

    for (i = 0; i < mapa->altura; i++) {
        free(mapa->celulas[i]);
    }
    free(mapa->celulas);
    mapa->celulas = NULL;
}
