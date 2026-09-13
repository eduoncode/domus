#include "TOKENS.h"

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAX_TOKEN_LENGTH e o maximo comprimento de um token. */
#define MAX_TOKEN_LENGTH 50

extern char tokenString[MAX_TOKEN_LENGTH + 1];

/* A funcao getToken retorna o proximo token do arquivo de entrada. */
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
