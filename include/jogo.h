#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"

#define MAX_INIMIGOS 4

typedef struct {
    int x, y;
    int vivo;
    int dir;
    int timer;
} Inimigo;

<<<<<<< HEAD
=======

>>>>>>> 5d0ffbf (corrige bug de movimentação  e adiciona morte de inimigo por bomba)
struct NoBomba;

typedef struct {
    Mapa mapa;
    int px;
    int py;
    int rodando;
    int pontos;
    struct NoBomba *bombas;
    Inimigo inimigos[MAX_INIMIGOS];
    int n_inimigos;
<<<<<<< HEAD

=======
>>>>>>> 5d0ffbf (corrige bug de movimentação  e adiciona morte de inimigo por bomba)
} Jogo;

void iniciar(Jogo *jogo);
void desenhar(Jogo *jogo);
void tecla(Jogo *jogo, int t);
void atualizar(Jogo *jogo);
void liberar(Jogo *jogo);

#endif
