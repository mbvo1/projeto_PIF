# projeto_PIF

Jogo inspirado no estilo Bomberman, desenvolvido em linguagem C para rodar diretamente no terminal.

O projeto foi criado para a disciplina de Programação Imperativa e Funcional e utiliza a biblioteca `cli-lib` para controle de tela, teclado e tempo de execução.

---

## Grupo

- Victor Paes
- Marcelo Bresani
- Eraldo Neto

---

## Sobre o jogo

O jogo acontece em um mapa exibido no terminal. O jogador controla um personagem que pode se movimentar pelo cenário, posicionar bombas e interagir com obstáculos e inimigos.

O projeto busca recriar a experiência básica de um Bomberman no terminal, trabalhando movimentação, bombas, inimigos, colisões e leitura de mapas em C.

---

## Funcionalidades

- Movimentação do jogador pelo mapa;
- Posicionamento de bombas;
- Explosão das bombas após determinado tempo;
- Interação com paredes, obstáculos e inimigos;
- Leitura de mapas a partir de arquivos;
- Execução em terminal.

---

## Tecnologias utilizadas

- C
- GCC
- Makefile
- Biblioteca `cli-lib`
- Terminal Linux, macOS ou WSL

---

## Como executar

É necessário ter `gcc` e `make` instalados.

Compile o projeto:

```bash
make
```

Execute:

```bash
make run
```

Ou:

```bash
./bomberman
```

## Controles

- WASD - mover
- Espaco - colocar bomba
- Q - sair

Para limpar o executavel:

```bash
make clean
```