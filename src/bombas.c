#include <stdio.h>
#include <stdlib.h>

#include "screen.h"
#include "bombas.h"

#define OFF_X 4
#define OFF_Y 3
#define TEMPO_BOMBA 35

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
        return;
    }

    jogo->bombas->tempo++;
    if (jogo->bombas->tempo >= TEMPO_BOMBA) {
        free(jogo->bombas);
        jogo->bombas = NULL;
    }
}

void bombas_desenhar(Jogo *jogo)
{
    NoBomba *b;

    b = jogo->bombas;
    if (b == NULL) {
        return;
    }

    screenGotoxy(OFF_X + b->x, OFF_Y + b->y);
    screenSetColor(YELLOW, BLACK);
    printf("o");
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
