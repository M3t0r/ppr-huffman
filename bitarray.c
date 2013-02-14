#include "bitarray.h"
#include <stdlib.h>
#include <string.h>


#define BITARRAY_INITIAL_CAPACITY   (4*8)
#define BITARRAY_INCREMENT          (4*8)

BITARRAY *bitarray_new()
{
    BITARRAY *ba = malloc(sizeof(BITARRAY));
    if(ba == NULL)
        return NULL;
    
    memset(ba, 0, sizeof(BITARRAY));
    
    ba->data = malloc(BITARRAY_INITIAL_CAPACITY/8);
    if(ba->data == NULL)
    {
        free(ba);
        return NULL;
    }
    
    ba->capacity = BITARRAY_INITIAL_CAPACITY;
    ba->length = 0;
    
    return ba;
}

void bitarray_free(BITARRAY **ba)
{
    free((*ba)->data);
    free((*ba));
    *ba = NULL;
}




void bitarray_grow(BITARRAY *ba)
{
    ba->capacity = (ba->capacity+BITARRAY_INCREMENT)/8;
    ba->data = realloc(ba->data, ba->capacity);
    if(ba->data == NULL)
    {
        printf("Could not grow bitarray.\nAborting\n");
        exit(EXIT_FAILURE);
    }
}




void bitarray_push(BITARRAY *ba, BOOL bit)
{
    BYTE mask;
    
    int index = ba->length++;
    if(ba->length >= ba->capacity)
        bitarray_grow(ba);
        
    mask = 0x01 << (7-(index % 8));
    ba->data[index / 8] =  (ba->data[index / 8] & ~mask) | (bit << (7-(index % 8)));
}

void bitarray_push_byte(BITARRAY *ba, BYTE byte)
{
    int i;
    for(i = 0; i < 8; i++)
    {
        bitarray_push(ba, ((byte<<i)&128) == 128);
    }
}

BOOL bitarray_pop(BITARRAY *ba)
{
    int index = --ba->length;
    return bitarray_get_bit(ba, index);
}

int bitarray_length(BITARRAY *ba)
{
    return ba->length;
}





BOOL bitarray_get_bit(BITARRAY *ba, int index)
{
    return (ba->data[index / 8] >> (7-(index % 8))) & 1;
}

BYTE bitarray_get_byte(BITARRAY *ba, int index)
{
    if(index + 8 > ba->length)
        return 0;
    
    else if(index % 8 == 0)
        return ba->data[index/8];
    
    else
    {
        BYTE mask = 0xFF >> (index%8);
        BYTE byte;
        
        byte  = (ba->data[index/8]   &  mask) << (index%8);
        byte |= (ba->data[index/8+1] & ~mask) >> (8 - (index%8));
        
        return byte;
    }
}

BOOL bitarray_equals(BITARRAY *ba1, BITARRAY *ba1)
{
	if (ba1 == NULL && ba2 == NULL)
		return TRUE;

	else if (ba1 == NULL)
		return FALSE;
		
	else if (ba2 == NULL)
		return FALSE;

	else if (ba1->length != ba2->length)
		return FALSE;

	else
		return !memcmp(ba1->data, ba2->data, ba1->length);

}
