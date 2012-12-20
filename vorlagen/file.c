#include "file.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int grow_memory(void **mem, unsigned int size)
{
    unsigned int new_size = size+buffer_step;
    void *swap;
    
    /* if the previous size was 0 (eg reserve a completly new chunk), 
     * realloc needs a NULL pointer */
    *mem = (size==0)?NULL:*mem; 
    
    swap = realloc(*mem, new_size);
    if(swap == NULL)
    {
        return 0;
    }
    *mem = swap;
    return new_size;
}

int readline(char **line, FILE *input)
{
    char *buffer;
    char *last_chunk = buffer;
    unsigned int size = 0;
    unsigned int chunk_size;
    unsigned int zero_offset; /* do we have a \0 we need to overwrite? */
    BOOL line_end = FALSE;
    
    do {
        /* allocate/grow the memory block, calculate new sizes and update pointers */
        chunk_size = grow_memory((void**)&buffer, size) - size;
        last_chunk = buffer+size;
        size = size + chunk_size;
        zero_offset = (last_chunk==buffer)?0:1;
        
        fgets(last_chunk-zero_offset, (int)chunk_size+zero_offset, input);
        
        /* is the last character a \n? if so we can stop */
        if(last_chunk[strlen(last_chunk) -1] == '\n')
            line_end = TRUE;
        
    } while(!line_end && !feof(input));
    
    *line = buffer;
    return size;
}

void remove_trailing_newline(char *str)
{
    int length = strlen(str);
    if(length == 0)
        return;
    
    if(str[length-1] == '\n')
        str[length-1] = '\0';
}
