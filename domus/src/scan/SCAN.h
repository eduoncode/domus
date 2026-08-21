#include "TOKENS.h"

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAX TOKEN LENGTH é o maximo comprimento de um token */
#define MAX_TOKEN_LENGTH 50

extern char tokenString[MAX_TOKEN_LENGTH + 1];

/* a funcao getToken retorna o próximo token do input */
TokenType getToken(void);
void printToken(TokenType token, const char *lexema);

typedef enum
{
  START,
  INBARRACOMMENT,
  INASTERISCOCOMMENT,
  INMAIOR,
  INMENOR,
  INEXCLAMACAO,
  INIGUAL,
  INCOMMENT,
  INNUM,
  INID,
  DONE
} StateType;

#endif
