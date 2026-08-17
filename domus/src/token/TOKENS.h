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
  FIMSE,
  ENQUANTO,
  FIMENQUANTO,
  LER,
  ESCREVER,

  /* operadores */
  MAIS,
  MENOS,
  MULT,
  BARRA,
  MENORQUE,
  MENORIGUAL,
  MAIORQUE,
  MAIORIGUAL,
  IGUAL,
  DIFERENTE,
  ATRIBUICAO,
  PONTO,
  DOISPONTOS,
  VIRGULA,
  ABREPARENTESE,
  FECHAPARENTESE,

  /* identificadores e literais */
  ID,
  NUM,
  COMMENT
} TokenType;

#endif
