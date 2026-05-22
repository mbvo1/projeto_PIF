#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"

struct NoBomba;

typedef struct {
    Mapa mapa;
    int px;
    int py;
    int rodando;
    int pontos;
    struct NoBomba *bombas;
} Jogo;

void iniciar(Jogo *jogo);
void desenhar(Jogo *jogo);
void tecla(Jogo *jogo, int t);
void atualizar(Jogo *jogo);
void liberar(Jogo *jogo);

#endif
