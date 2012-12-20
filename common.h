#ifndef _COMMON_H
#define _COMMON_H

typedef enum {
    FALSE,
    TRUE
} BOOL;

typedef unsigned char BYTE;


#ifndef ENSURE_ENOUGH_MEMORY
#include <stdlib.h>
#include <stdio.h>
#define ENSURE_ENOUGH_MEMORY(VAR, FUNCTION) \
{ \
	if (VAR == NULL) { \
		printf(FUNCTION ": not enough memory\n"); \
		exit(EXIT_FAILURE); \
	} \
}
#endif

#ifdef DEBUG
	#define DPRINT(E)		printf(E)
	#define DPRINT_E(E, T)	printf(#E " = %" #T "\n", E)
#else
	#define DPRINT(E)
	#define DPRINT_E(E, T)
#endif

#endif
