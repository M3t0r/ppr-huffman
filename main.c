#include "common.h"
#include "cmdargs.h"

#include <stdlib.h>
#include <stdio.h>

void print_help();
void print_usage();

int main (int argc, char **argv) {
    cmdargs args;
    
    args = parse_args(argc, argv);
    
    if (args.malformed)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}

void print_usage()
{
    printf("usage\n");
}

void print_help()
{
    printf("help\n");
}
