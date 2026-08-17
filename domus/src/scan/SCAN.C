#include "scan.h"
#include "globals.h"
#include "tokens.h"

char tokenString[MAX_TOKEN_LENGTH + 1];

#define BUFLEN 256

static char lineBuf[BUFLEN];
static int linepos = 0;
static int bufsize = 0;
static int EOF_flag = FALSE;

static int getNextChar(void)
{
  if (!(linepos < bufsize))
  {
    lineno++;
    if (fgets(lineBuf, BUFLEN - 1, source))
    {
      if (EchoSource)
      {
        fprintf(listing, "%4d: %s", lineno, lineBuf);
      }
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    {
      EOF_flag = TRUE;
      return EOF;
    }
  }
  else
  {
    return lineBuf[linepos++];
  }
}

TokenType getToken(void)
{
  int tokenStringIndex = 0;
  TokenType currentToken;
  StateType state = START;
  int save;
  while (state != DONE)
  {
    int ch = getNextChar();
    save = TRUE;
    switch (state)
    {
    case START:
      if (isDigit(ch))
        state = INNUM;
      else if (isalpha(ch))
        state = INID;
      else if (ch == ':')
        state = INASSIGN;
      else if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
        save = FALSE;
      else if (ch == '*')
      {
        char nextChar = getNextChar();
        if (nextChar == '/')
        {
          save = FALSE;
          state = INCOMMENT;
        }
        return;
      }
      else
      {
        state = DONE;
        switch (ch)
        {
        case EOF:
          save = FALSE;
          currentToken = ENDFILE;
          break;
        case '=':
          currentToken = IGUAL;
          break;
        case '<':
          currentToken = MENOR_QUE;
          break;
        case '+':
          currentToken = MAIS;
          break;
        case '-':
          currentToken = MENOS;
          break;
        case '*':
          currentToken = MULT;
          break;
        case '/':
          currentToken = BARRA;
          break;
        case '(':
          currentToken = ABRE_PARENTESE;
          break;
        case ')':
          currentToken = FECHA_PARENTESE;
          break;
        default:
          currentToken = ERROR;
          break;
        }
      }
      break;
    case INCOMMENT:
      save = FALSE;
      if (ch == EOF)
      {
        state = DONE;
        currentToken = ENDFILE;
      }
      else if (ch == '/')
      {
        char nextChar = getNextChar();
        if (nextChar == '*')
        {
          state = START;
        }
      }
      break;
    case INASSIGN:
      state = DONE;
      if (ch == '=')
        currentToken = ATRIBUICAO;
      else
      {
        ungetNextChar();
        save = FALSE;
        currentToken = ERROR;
      }
      break;
    case INNUM:
      if (!isdigit(ch))
      {
        ungetNextChar();
        save = FALSE;
        state = DONE;
        currentToken = NUM;
      }
      break;
    case INID:
      if (!isalpha(ch))
      {
        ungetNextChar();
        save = FALSE;
        state = DONE;
        currentToken = ID;
      }
      break;
    case DONE:
    default:
      fprintf(listing, "Scanner Bug: state= %d\n", state);
      state = DONE;
      currentToken = ERROR;
      break;
    }
    if ((save) && (tokenStringIndex <= MAX_TOKEN_LENGTH))
      tokenString[tokenStringIndex++] = (char)ch;
    if (state == DONE)
    {
      tokenString[tokenStringIndex] = '\0';
      if (currentToken == ID)
        currentToken = reservedLookup(tokenString);
    }
  }
  if (TraceScan)
  {
    fprintf(listing, "\t%d: ", lineno);
    printToken(currentToken, tokenString);
  }
  return currentToken;
}
