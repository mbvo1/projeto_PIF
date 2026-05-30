# pasta da cli-lib do professor
CLI = lib/cli-lib
CC = gcc
CFLAGS = -Iinclude -I$(CLI)/include

# codigo do nosso jogo
SRC_JOGO = src/principal.c src/jogo.c src/mapa.c src/bombas.c src/inimigos.c

# tela, teclado e timer da lib
SRC_CLI = $(CLI)/src/screen.c $(CLI)/src/keyboard.c $(CLI)/src/timer.c

bomberman: $(SRC_JOGO) $(SRC_CLI)
	$(CC) $(SRC_JOGO) $(SRC_CLI) $(CFLAGS) -o bomberman

run: bomberman
	./bomberman

clean:
	rm -f bomberman
