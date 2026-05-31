#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"

#define MAX_INIMIGOS 8

typedef struct {
    int x, y;
    int vivo;
    int dir;
    int timer;
} Inimigo;

struct NoBomba;

typedef struct {
    Mapa mapa;
    int px;
    int py;
    int rodando;
    int pontos;
    int fim;
    int melhor_score;
    struct NoBomba *bombas;
    Inimigo inimigos[MAX_INIMIGOS];
    int n_inimigos;
} Jogo;

void iniciar(Jogo *jogo);
void desenhar(Jogo *jogo);
void tecla(Jogo *jogo, int t);
void atualizar(Jogo *jogo);
void liberar(Jogo *jogo);

#endif