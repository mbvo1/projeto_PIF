CLI = lib/cli-lib

SRC = src/principal.c src/jogo.c src/mapa.c src/bombas.c src/inimigos.c
LIB = $(CLI)/src/screen.c $(CLI)/src/keyboard.c $(CLI)/src/timer.c

bomberman: $(SRC) $(LIB)
	gcc $(SRC) $(LIB) -Iinclude -I$(CLI)/include -o bomberman

clean:
	rm -f bomberman
