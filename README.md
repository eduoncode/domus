# Analisador Lexico Domus

Analisador lexico manual, implementado em C para a linguagem Domus. Ele le um
arquivo-fonte externo e exibe, para cada token, a linha, o nome textual do token

## Compilacao

Requisito: compilador C compativel com C17 (por exemplo, GCC).

```sh
make
```

Ou sem `make`:

```sh
gcc -Idomus/src -Idomus/src/scan -Idomus/src/token -std=c17 -Wall -Wextra -Wpedantic domus/src/MAIN.c domus/src/scan/SCAN.c -o domus-lexico
```

## Execucao

```sh
./domus-lexico ExemploDomus.txt
```

O nome do arquivo-fonte e obrigatorio. O programa informa `ENDFILE` ao alcancar

```sh
make run
```

## Materiais de entrega

Os arquivos em `docs/` apoiam o relatorio exigido pelo enunciado: descricao dos
tokens, estrategia de implementacao, automato e resultados do exemplo. Antes da
entrega, preencha os nomes dos integrantes na capa do relatorio e aplique a
formatacao ABNT solicitada pela disciplina.
