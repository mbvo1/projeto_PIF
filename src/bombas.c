#include <stdio.h>
#include <stdlib.h>

#include "screen.h"
#include "bombas.h"
#include "inimigos.h"

#define OFF_X 4
#define OFF_Y 3
#define TEMPO_BOMBA 35
#define TEMPO_EXPLOSAO 10
#define ALCANCE_EXPLOSAO 2

static int aviso_atingido = 0;

static int explosao_pega_player(Jogo *jogo, int x, int y)
{
    return jogo->px == x && jogo->py == y;
}

static void processar_celula_explosao(Jogo *jogo, int x, int y)
{
    char cel;

    cel = ler_celula(&jogo->mapa, x, y);
    if (cel == '#') {
        return;
    }

    if (cel == '%') {
        mudar_celula(&jogo->mapa, x, y, ' ');
    }

    inimigos_explodidos(jogo, x, y);

    if (explosao_pega_player(jogo, x, y)) {
        jogo->fim = 1;
        jogo->rodando = 0;
        salvar_score(jogo);
    }
}

static void explosao_direcao(Jogo *jogo, int bx, int by, int dx, int dy)
{
    int i, x, y;
    char cel;

    for (i = 1; i <= ALCANCE_EXPLOSAO; i++) {
        x = bx + dx * i;
        y = by + dy * i;
        cel = ler_celula(&jogo->mapa, x, y);
        if (cel == '#') {
            break;
        }
        processar_celula_explosao(jogo, x, y);
        if (cel == '%') {
            break;
        }
    }
}

static void aplicar_explosao(Jogo *jogo, NoBomba *b)
{
    processar_celula_explosao(jogo, b->x, b->y);
    explosao_direcao(jogo, b->x, b->y, 0, -1);
    explosao_direcao(jogo, b->x, b->y, 0, 1);
    explosao_direcao(jogo, b->x, b->y, -1, 0);
    explosao_direcao(jogo, b->x, b->y, 1, 0);
}

static void desenhar_celula_explosao(Jogo *jogo, int x, int y)
{
    if (ler_celula(&jogo->mapa, x, y) == '#') {
        return;
    }

    screenGotoxy(OFF_X + x, OFF_Y + y);
    screenSetColor(LIGHTRED, BLACK);
    printf("*");
}

static void desenhar_direcao(Jogo *jogo, int bx, int by, int dx, int dy)
{
    int i, x, y;
    char cel;

    for (i = 1; i <= ALCANCE_EXPLOSAO; i++) {
        x = bx + dx * i;
        y = by + dy * i;
        cel = ler_celula(&jogo->mapa, x, y);
        if (cel == '#') {
            break;
        }
        desenhar_celula_explosao(jogo, x, y);
        if (cel == '%') {
            break;
        }
    }
}

static void desenhar_explosao(Jogo *jogo, NoBomba *b)
{
    desenhar_celula_explosao(jogo, b->x, b->y);
    desenhar_direcao(jogo, b->x, b->y, 0, -1);
    desenhar_direcao(jogo, b->x, b->y, 0, 1);
    desenhar_direcao(jogo, b->x, b->y, -1, 0);
    desenhar_direcao(jogo, b->x, b->y, 1, 0);
}

void bombas_iniciar(Jogo *jogo)
{
    jogo->bombas = NULL;
}

void bombas_tecla(Jogo *jogo, int tecla)
{
    NoBomba *b;

    if (tecla != ' ') {
        return;
    }

    if (jogo->bombas != NULL) {
        return;
    }

    b = malloc(sizeof(NoBomba));
    if (b == NULL) {
        return;
    }

    b->x = jogo->px;
    b->y = jogo->py;
    b->tempo = 0;
    b->prox = NULL;
    jogo->bombas = b;
}

void bombas_atualizar(Jogo *jogo)
{
    if (jogo->bombas == NULL) {
        if (aviso_atingido > 0) {
            aviso_atingido--;
        }
        return;
    }

    jogo->bombas->tempo++;

    if (jogo->bombas->tempo >= TEMPO_BOMBA + TEMPO_EXPLOSAO) {
        free(jogo->bombas);
        jogo->bombas = NULL;
    }

    if (aviso_atingido > 0) {
        aviso_atingido--;
    }
}

void bombas_desenhar(Jogo *jogo)
{
    NoBomba *b;

    b = jogo->bombas;
    if (b == NULL) {
        if (aviso_atingido > 0) {
            screenGotoxy(3, 23);
            screenSetColor(LIGHTRED, BLACK);
            printf("Voce foi atingido pela explosao! ");
        } else {
            screenGotoxy(3, 23);
            screenSetColor(WHITE, BLACK);
            printf("                                ");
        }
        return;
    }

    if (b->tempo < TEMPO_BOMBA) {
        screenGotoxy(OFF_X + b->x, OFF_Y + b->y);
        screenSetColor(YELLOW, BLACK);
        printf("o");
    } else {
        desenhar_explosao(jogo, b);
        if (b->tempo == TEMPO_BOMBA) {
            aplicar_explosao(jogo, b);
        }
    }

    if (aviso_atingido > 0) {
        screenGotoxy(3, 23);
        screenSetColor(LIGHTRED, BLACK);
        printf("Voce foi atingido pela explosao! ");
    } else {
        screenGotoxy(3, 23);
        screenSetColor(WHITE, BLACK);
        printf("                                ");
    }
}

void bombas_liberar(Jogo *jogo)
{
    NoBomba *b;
    NoBomba *prox;

    b = jogo->bombas;
    while (b != NULL) {
        prox = b->prox;
        free(b);
        b = prox;
    }
    jogo->bombas = NULL;
}
