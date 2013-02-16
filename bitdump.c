#include "bitfile.h"
#include "stdio.h"


int main(int argc, char **argv)
{
    BITFILE *f;
    int i = 0;

    if(argc < 1)
    {
        fprintf(stderr, "Datei zum öffnen ist erster parameter.\n");
        exit(EXIT_FAILURE);
    }
    
    f = bitfile_open(argv[1], FALSE);
    
    if(f == NULL)
    {
        fprintf(stderr, "Datei konnte nicht geöffnet werden.\n");
        exit(EXIT_FAILURE);
    }
    
    do
    {
        if(((i/8) % 10) == 0 && i%8 == 0)
            printf("\n%6d: ", i);
            
        else if(i%8 == 0)
            printf(" ");
        
        printf("%d", bitfile_read_bit(f));
        i++;
    } while(!bitfile_is_eof(f));
    
    printf("\n");
    
    return EXIT_SUCCESS;
}
