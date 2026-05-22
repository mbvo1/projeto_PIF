#ifndef MAPA_H
#define MAPA_H

typedef struct {
    char **celulas;
    int largura;
    int altura;
} Mapa;

void carregar_mapa(Mapa *mapa, char *arquivo);
void desenhar_mapa(Mapa *mapa);
void liberar_mapa(Mapa *mapa);

char ler_celula(Mapa *mapa, int x, int y);
void mudar_celula(Mapa *mapa, int x, int y, char valor);

#endif
