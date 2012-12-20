#ifndef _CMDARGS_H
#define _CMDARGS_H

#include "common.h"

typedef struct {
    BOOL    malformed;
    char*   malformed_reason;
    BOOL    show_help;
} cmdargs;

cmdargs parse_args(int argc, char **argv);

#endif
