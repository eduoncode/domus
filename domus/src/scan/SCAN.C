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

static void ungetNextChar(void)
{
  if (!EOF_flag)
    linepos--;
}

static struct
{
  char *str;
  TokenType tok;
} reservedWords[MAX_RESERVADAS] = {{"sensor", SENSOR}, {"atuador", ATUADOR}, {"porta", PORTA}, {"analogico", ANALOGICO}, {"digital", DIGITAL}, {"se", SE}, {"entao", ENTAO}, {"senao", SENAO}, {"fim_se", FIMSE}, {"enquanto", ENQUANTO}, {"fim_enquanto", FIMENQUANTO}, {"ler", LER}, {"escrever", ESCREVER}};

static TokenType reservedLookup(char *s)
{
  int i;
  for (i = 0; i < MAX_RESERVADAS; i++)
    if (!strcmp(s, reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
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
      if (isdigit(ch))
        state = INNUM;
      else if (isalpha(ch) || ch == '_')
        state = INID;
      else if (ch == '/')
      {
        save = FALSE;
        state = INBARRACOMMENT;
        break;
      }
      else if (ch == '>')
      {
        state = INMAIOR;
        break;
      }
      else if (ch == '<')
      {
        state = INMENOR;
        break;
      }
      else if (ch == '!')
      {
        state = INEXCLAMACAO;
        break;
      }
      else if (ch == '=')
      {
        state = INIGUAL;
        break;
      }
      else if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
        save = FALSE;
      else
      {
        state = DONE;
        switch (ch)
        {
        case EOF:
          save = FALSE;
          currentToken = ENDFILE;
          break;
        case '.':
          currentToken = PONTO;
          break;
        case ',':
          currentToken = VIRGULA;
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
        case ':':
          currentToken = DOISPONTOS;
          break;
        case '/':
          currentToken = BARRA;
          break;
        case '(':
          currentToken = ABREPARENTESE;
          break;
        case ')':
          currentToken = FECHAPARENTESE;
          break;
        default:
          currentToken = ERROR;
          break;
        }
      }
      break;
    case INBARRACOMMENT:
      state = DONE;
      if (ch == '*')
      {
        state = INCOMMENT;
        break;
      }
      else
      {
        ungetNextChar();
        save = FALSE;
        currentToken =
            BARRA;
        break;
      }
    case INCOMMENT:
      save = FALSE;
      if (ch == EOF)
      {
        state = DONE;
        currentToken = ENDFILE;
      }
      else if (ch == '*')
      {
        state = INASTERISCOCOMMENT;
      }
      break;
    case INASTERISCOCOMMENT:
      save = FALSE;
      if (ch == EOF)
      {
        state = DONE;
        currentToken = ENDFILE;
      }
      if (ch == '/')
      {
        state = START;
      }
      else if (ch != '*')
      {
        state = INCOMMENT;
      }
      break;
    case INMENOR:
      if (ch == '=')
      {
        state = DONE;
        currentToken = MENORIGUAL;
        break;
      }
      if (ch == '-')
      {
        state = DONE;
        currentToken = ATRIBUICAO;
        break;
      }
      else
      {
        ungetNextChar();
        save = FALSE;
        currentToken =
            MENORQUE;
        break;
      }
    case INEXCLAMACAO:
      if (ch == '=')
      {
        state = DONE;
        currentToken = DIFERENTE;
        break;
      }
      else
      {
        ungetNextChar();
        save = FALSE;
        currentToken = ERROR;
        break;
      }
    case INIGUAL:
      if (ch == '=')
      {
        state = DONE;
        currentToken = IGUAL;
        break;
      }
      else
      {
        ungetNextChar();
        save = FALSE;
        currentToken = ERROR;
        break;
      }
    case INMAIOR:
      if (ch == '=')
      {
        state = DONE;
        currentToken = MAIORIGUAL;
        break;
      }
      else
      {
        ungetNextChar();
        save = FALSE;
        currentToken = MAIORQUE;
        break;
      }
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
      if (!isalnum(ch) && ch != '_')
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
