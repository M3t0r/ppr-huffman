#ifndef _BITARRAY_H
#define _BITARRAY_H

#include "common.h"



typedef struct {
    BYTE *array;
    unsigned int capacity;
    unsigned int length;
} BITARRAY;

/**
 * creates a new BITARRAY with an initial capacity of one byte
 */
BITARRAY *bitarray_new();
/**
 * frees the bitarray and  al it's reserved heap space
 */
void bitarray_free(BITARRAY *ba);

void bitarray_push(BITARRAY *ba, BOOL d);
void bitarray_push_byte(BITARRAY *ba, BYTE d);
BOOL bitarray_pop(BITARRAY *ba);

/**
 * returns the length (read: number of used bits) of the bitarray
 * @param ba the bitarray
 */
int bitarray_length(BITARRAY *ba);
/**
 * returns the bit with the bit-based index
 * @param ba the bitarray
 * @param index the bit-based index
 */
BOOL bitarray_get_bit(BITARRAY *ba, int index);
/**
 * returns the byte beginning at the bit-based index
 * @param ba the bitarray
 * @param index the bit-based(!!) index of the byte
 */
BYTE bitarray_get_byte(BITARRAY *ba, int index);



#endif
