#include <stdio.h>

#include "screen.h"
#include "jogo.h"
#include "bombas.h"
#include "inimigos.h"

#define OFF_X 4
#define OFF_Y 3

void iniciar(Jogo *jogo)
{
    int x, y;

    jogo->px = 1;
    jogo->py = 1;
    jogo->rodando = 1;
    jogo->pontos = 0;
    jogo->fim = 0;
    jogo->melhor_score = 0;
    jogo->bombas = NULL;
    jogo->mapa.celulas = NULL;

    carregar_mapa(&jogo->mapa, "assets/mapas/fase1.txt");

    for (y = 0; y < jogo->mapa.altura; y++) {
        for (x = 0; x < jogo->mapa.largura; x++) {
            if (jogo->mapa.celulas[y][x] == 'P') {
                jogo->px = x;
                jogo->py = y;
                jogo->mapa.celulas[y][x] = ' ';
            }
        }
    }

    bombas_iniciar(jogo);
    inimigos_iniciar(jogo);
}

void tecla(Jogo *jogo, int t)
{
    int nx, ny;
    char cel;

    if (t == 'q' || t == 'Q') {
        jogo->rodando = 0;
        return;
    }

    bombas_tecla(jogo, t);

    if (t != 'w' && t != 's' && t != 'a' && t != 'd') {
        return;
    }

    nx = jogo->px;
    ny = jogo->py;

    if (t == 'w') {
        ny--;
    }
    if (t == 's') {
        ny++;
    }
    if (t == 'a') {
        nx--;
    }
    if (t == 'd') {
        nx++;
    }

    cel = ler_celula(&jogo->mapa, nx, ny);
    if (cel != '#' && cel != '%') {
        jogo->px = nx;
        jogo->py = ny;
    }
}

void atualizar(Jogo *jogo)
{
    bombas_atualizar(jogo);
    inimigos_atualizar(jogo);
}

void desenhar(Jogo *jogo)
{
    desenhar_mapa(&jogo->mapa);
    bombas_desenhar(jogo);
    inimigos_desenhar(jogo);

    screenGotoxy(OFF_X + jogo->px, OFF_Y + jogo->py);
    screenSetColor(LIGHTRED, BLACK);
    screenSetBold();
    printf("@");
    screenSetNormal();

    screenGotoxy(3, 22);
    screenSetColor(WHITE, BLACK);
    printf("Pontos: %d  Recorde: %d     ", jogo->pontos, jogo->melhor_score);

    screenGotoxy(3, 24);
    screenSetColor(WHITE, BLACK);
    printf("WASD move  ESPACO bomba  Q sai     ");
}

void liberar(Jogo *jogo)
{
    bombas_liberar(jogo);
    inimigos_liberar(jogo);
    liberar_mapa(&jogo->mapa);
}
