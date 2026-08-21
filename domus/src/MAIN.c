#include <stdlib.h>

#include "globals.h"
#include "SCAN.h"

#define SOURCE_FILE "ExemploDomus.txt"

int lineno = 0;
FILE *source;
FILE *listing;

int EchoSource = FALSE;
int TraceScan = FALSE;

static const char *tokenName(TokenType token)
{
  switch (token)
  {
  case ENDFILE:
    return "ENDFILE";
  case ERROR:
    return "ERROR";
  case SENSOR:
    return "SENSOR";
  case ATUADOR:
    return "ATUADOR";
  case PORTA:
    return "PORTA";
  case ANALOGICO:
    return "ANALOGICO";
  case DIGITAL:
    return "DIGITAL";
  case SE:
    return "SE";
  case ENTAO:
    return "ENTAO";
  case SENAO:
    return "SENAO";
  case FIMSE:
    return "FIMSE";
  case ENQUANTO:
    return "ENQUANTO";
  case FIMENQUANTO:
    return "FIMENQUANTO";
  case LER:
    return "LER";
  case ESCREVER:
    return "ESCREVER";
  case MAIS:
    return "MAIS";
  case MENOS:
    return "MENOS";
  case MULT:
    return "MULT";
  case BARRA:
    return "BARRA";
  case MENORQUE:
    return "MENORQUE";
  case MENORIGUAL:
    return "MENORIGUAL";
  case MAIORQUE:
    return "MAIORQUE";
  case MAIORIGUAL:
    return "MAIORIGUAL";
  case IGUAL:
    return "IGUAL";
  case DIFERENTE:
    return "DIFERENTE";
  case ATRIBUICAO:
    return "ATRIBUICAO";
  case PONTO:
    return "PONTO";
  case DOISPONTOS:
    return "DOISPONTOS";
  case VIRGULA:
    return "VIRGULA";
  case ABREPARENTESE:
    return "ABREPARENTESE";
  case FECHAPARENTESE:
    return "FECHAPARENTESE";
  case ID:
    return "ID";
  case NUM:
    return "NUM";
  case COMMENT:
    return "COMMENT";
  default:
    return "DESCONHECIDO";
  }
}

void printToken(TokenType token, const char *lexema)
{
  fprintf(listing, "%-16s | %-20s", tokenName(token), lexema[0] != '\0' ? lexema : "-");
}

int main(void)
{
  TokenType token;

  source = fopen(SOURCE_FILE, "r");
  if (source == NULL)
  {
    fprintf(stderr, "Nao foi possivel abrir o arquivo '%s'.\n", SOURCE_FILE);
    return EXIT_FAILURE;
  }

  listing = stdout;
  lineno = 0;
  TraceScan = FALSE;

  printf("Linha | Token            | Lexema\n");
  printf("------|------------------|---------------------\n");

  do
  {
    token = getToken();
    printf("%5d | ", lineno);
    printToken(token, tokenString);
    putchar('\n');
  } while (token != ENDFILE);

  fclose(source);
  source = NULL;
  return EXIT_SUCCESS;
}
