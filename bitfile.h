#ifndef _BITFILE_H
#define _BITFILE_H

#include "bitarray.h"
#include "common.h"



typedef struct {
    
} BITFILE;

BITFILE bitfile_open(char* path, BOOL w);
void bitfile_close(BITFILE fd);

BOOL bitfile_read_bit(BITFILE fd);
BYTE bitfile_read_byte(BITFILE fd);
BITARRAY bitfile_read_bitarray(BITFILE fd, int length);

void bitfile_write_bit(BITFILE fd, BOOL d);
void bitfile_write_byte(BITFILE fd, BYTE d);
void bitfile_write_bitarray(BITFILE fd, BITARRAY d);



#endif
