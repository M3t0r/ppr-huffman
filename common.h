#ifndef _COMMON_H
#define _COMMON_H

typedef enum {
    FALSE,
    TRUE
} BOOL;

typedef unsigned char BYTE;


#ifndef ASSERT_ALLOC
#include <stdlib.h>
#include <stdio.h>
#define ASSERT_ALLOC(ptr)\
    if (ptr == NULL) {\
        printf("Could not allocate memory block in %s:%i\nAborting\n", __FILE__, __LINE__);\
        exit(EXIT_FAILURE);\
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
