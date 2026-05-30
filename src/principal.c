#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "jogo.h"

int main()
{
    Jogo jogo;
    int t;

    screenInit(1);
    keyboardInit();
    timerInit(80);
    srand(time(NULL));

    iniciar(&jogo);
    desenhar(&jogo);
    screenUpdate();

    while (jogo.rodando == 1) {
        if (keyhit()) {
            t = readch();
            tecla(&jogo, t);
            desenhar(&jogo);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            atualizar(&jogo);
            desenhar(&jogo);
            screenUpdate();
        }
    }

    if (jogo.fim == 1) {
        screenGotoxy(3, 10);
        screenSetColor(LIGHTRED, BLACK);
        printf("Voce morreu! Pontos: %d          ", jogo.pontos);
    } else if (jogo.fim == 2) {
        screenGotoxy(3, 10);
        screenSetColor(LIGHTGREEN, BLACK);
        printf("Voce venceu! Pontos: %d           ", jogo.pontos);
    }
    if (jogo.fim > 0) {
        screenGotoxy(3, 12);
        screenSetColor(WHITE, BLACK);
        printf("Pressione qualquer tecla...     ");
        screenUpdate();
        while (!keyhit()) {
        }
        readch();
    }

    liberar(&jogo);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
