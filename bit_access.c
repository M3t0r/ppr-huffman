#include "bit_access.h"

BOOL get_bit(BYTE *ptr, int index)
{
    return (ptr[index / 8] >> index % 8) & 1;
}

void set_bit(BYTE *ptr, int index, BOOL value)
{
    BYTE mask = (BYTE) 1 << (index % 8);
    ptr[index / 8] =  (ptr[index / 8] & ~mask) | (value << (index % 8));
}

void print_bits(BYTE *ptr, int offset, int length)
{
    int i;
    for(i = offset; i < (offset + length); i++)
    {
        printf("%d", get_bit(ptr, i));
    }
}
