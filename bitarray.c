#include "bitarray.h"

BOOL bitarray_get_bit(BITARRAY ba, int index)
{
    return (ba.array[index / 8] >> index % 8) & 1;
}

/*void set_bit(BYTE *ptr, int index, BOOL value)
{
    BYTE mask = (BYTE) 1 << (index % 8);
    ptr[index / 8] =  (ptr[index / 8] & ~mask) | (value << (index % 8));
}*/
