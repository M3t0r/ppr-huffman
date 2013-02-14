#ifndef HEADER_TESTMAIN
#define HEADER_TESTMAIN

#include "../common.h"

typedef BOOL (*TEST)(void);

typedef struct {
    char *name;
    TEST test;
} testunit;

extern testunit testsuit[];
extern int nr_of_unittests;
extern char *name_of_testsuit;
    
    
#endif
