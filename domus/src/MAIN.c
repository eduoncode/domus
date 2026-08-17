#include "globals.h"

#define NO_PARSE TRUE

#define NO_ANALYZE TRUE

#define NO_CODE TRUE

#include "scan.h"

int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;

int EchoSource = FALSE;
int TraceScan = FALSE;
