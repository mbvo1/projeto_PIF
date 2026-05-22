#ifndef BOMBAS_H
#define BOMBAS_H

#include "jogo.h"

typedef struct NoBomba {
    int x;
    int y;
    int tempo;
    struct NoBomba *prox;
} NoBomba;

void bombas_iniciar(Jogo *jogo);
void bombas_tecla(Jogo *jogo, int tecla);
void bombas_atualizar(Jogo *jogo);
void bombas_desenhar(Jogo *jogo);
void bombas_liberar(Jogo *jogo);

#endif
