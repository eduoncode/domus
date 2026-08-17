#ifndef _TOKENS_H_
#define _TOKENS_H_

typedef enum
{
  /* tokens de controle */
  ENDFILE,
  ERROR,

  /* palavras reservadas */
  SENSOR,
  ATUADOR,
  PORTA,
  ANALOGICO,
  DIGITAL,
  SE,
  ENTAO,
  SENAO,
  FIM_SE,
  ENQUANTO,
  FIM_ENQUANTO,
  LER,
  ESCREVER,

  /* operadores */
  MAIS,
  MENOS,
  MULT,
  BARRA,
  MENOR_QUE,
  MENOR_IGUAL,
  MAIOR_QUE,
  MAIOR_IGUAL,
  IGUAL,
  DIFERENTE,
  ATRIBUICAO,
  PONTO,
  DOIS_PONTOS,
  VIRGULA,
  ABRE_PARENTESE,
  FECHA_PARENTESE,

  /* identificadores e literais */
  ID,
  NUM,
  COMMENT
} TokenType;

#endif
