#include "stdio.h"
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAX_RESERVADAS 13

extern FILE *source;
extern FILE *listing;

extern int lineno;

extern int EchoSource;
extern int TraceScan;

#endif
