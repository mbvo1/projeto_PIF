#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "inimigos.h"
#include "screen.h"

#define OFF_X 4
#define OFF_Y 3

static int dx[] = {0, 0, -1, 1};
static int dy[] = {-1, 1, 0, 0};

static int pode_andar(Jogo *jogo, int x,int y){
    char c = ler_celula(&jogo->mapa, x, y);
    return (c != '#'&& c != '%');
}

static void salvar_score(Jogo *jogo)
{
    FILE *arq;

    arq = fopen("scores.txt", "a");
    if (arq == NULL) {
        return;
    }
    fprintf(arq, "%d\n", jogo->pontos);
    fclose(arq);
}

void inimigos_iniciar(Jogo *jogo)
{
    jogo->pontos = 0;
    jogo->n_inimigos = 3;

    int posX[] = {21, 21, 11};
    int posY[] = {11, 1, 11};

    for(int i=0; i<jogo->n_inimigos; i++){
        jogo->inimigos[i].x = posX[i];
        jogo->inimigos[i].y = posY[i];
        jogo->inimigos[i].vivo = 1;
        jogo->inimigos[i].dir = rand() % 4;
        jogo->inimigos[i].timer = 0;
    }
}

void inimigos_atualizar(Jogo *jogo)
{
    for(int i=0; i<jogo->n_inimigos; i++){
        Inimigo *ini = &jogo->inimigos[i];
        if(!ini->vivo) continue;

        ini->timer++;
        if (ini->timer < 20) continue;
        ini->timer = 0;

        int nx = ini->x + dx[ini->dir];
        int ny = ini->y + dy[ini->dir];

        if (pode_andar(jogo, nx, ny)) {
            ini->x = nx;
            ini->y = ny;
            if (rand() % 10 == 0){
                ini->dir = rand() % 4;
            }    
        } else {
            int dirs[4] = {0, 1, 2, 3};
            for (int j = 3; j > 0; j--){
                int k = rand() % (j + 1);
                int tmp =dirs[j];dirs[j] = dirs[k]; dirs[k] = tmp;
            }
            for (int j = 0; j < 4; j++) {
                nx = ini->x + dx[dirs[j]];
                ny = ini->y + dy[dirs[j]];
                if (pode_andar(jogo, nx, ny)) {
                    ini->dir = dirs[j];
                    ini->x = nx;
                    ini->y = ny;
                    break;
                }
            }
        }    
        if (ini->x == jogo->px && ini->y == jogo->py) {
            jogo->rodando = 0;
            salvar_score(jogo);
        }
    }
}

void inimigos_desenhar(Jogo *jogo)
{
    for (int i = 0; i < jogo->n_inimigos; i++) {
        Inimigo *ini = &jogo->inimigos[i];
        if (!ini->vivo) continue;

        screenSetColor(LIGHTRED, BLACK);
        screenGotoxy(OFF_X + ini->x, OFF_Y + ini->y);
        printf("X");
    }
}
void inimigos_explodidos(Jogo *jogo, int x, int y) {
    for (int i = 0; i < jogo->n_inimigos; i++) {
        Inimigo *ini = &jogo->inimigos[i];
        if (!ini->vivo) continue;
        if (ini->x == x && ini->y == y) {
            ini->vivo = 0;
            jogo->pontos += 100;
        }
    }
}
void inimigos_liberar(Jogo *jogo)
{
    (void)jogo;
}
