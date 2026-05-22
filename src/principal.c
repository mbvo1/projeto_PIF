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

    liberar(&jogo);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
