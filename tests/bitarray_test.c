#include "testmain.h"
#include "../bitarray.h"

char *name_of_testsuit = "bitarray";
    
BOOL test_new()
{
    BITARRAY *ba = bitarray_new();
    
    if (ba->data == NULL)
        return FALSE;
    if (ba->capacity == 0)
        return FALSE;
    if (ba->length != 0)
        return FALSE;
        
    return TRUE;
}

BOOL test_free()
{
    BITARRAY *ba = bitarray_new();
    bitarray_free(&ba);
    
    return ba == NULL;
}

BOOL test_push_ein_bit()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push(ba, TRUE);
    
    return ba->length == 1 && ba->data[0] != 0;
}

BOOL test_push_mehrere_bits()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);

    /* 0b10100000 = 160 */
    return ba->length == 3 && ba->data[0] == 160;
}

BOOL test_push_10_bits()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    
    return ba->length == 10 && ba->data[0] == 127 && ba->data[1] == 64 && ba->capacity >= 10;
}

BOOL test_push_byte()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push_byte(ba, 37);
    
    return ba->length == 8 && ba->data[0] == 37;
}

BOOL test_push_bits_and_bytes()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, FALSE);
    bitarray_push_byte(ba, 255);
    
    return ba->length == 11 && ba->data[0] == 159 && ba->data[1] == 224 && ba->capacity >= 11;
}

BOOL test_get_bit()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push_byte(ba, 32);
    
    return bitarray_get_bit(ba, 2) && ba->length == 8;
}

BOOL test_get_byte()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push(ba, FALSE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    bitarray_push_byte(ba, 33);
    
    return bitarray_get_byte(ba, 3) == 144 && ba->length == 12;
}

BOOL test_pop_bit()
{
    BITARRAY *ba = bitarray_new();
    
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    bitarray_push(ba, TRUE);
    bitarray_push(ba, FALSE);
    
    return bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == TRUE
        && bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == TRUE
        && bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == TRUE
        && bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == TRUE
        && bitarray_pop(ba) == FALSE
        && bitarray_pop(ba) == TRUE
        && ba->length == 0;
}


testunit testsuit[] = {
    {"new bitarray", test_new},
    {"free bitarray", test_free},
    {"push ein bit", test_push_ein_bit},
    {"push mehrer bits", test_push_mehrere_bits},
    {"pushe 10 bits", test_push_10_bits},
    {"pushe ein byte", test_push_byte},
    {"pushe ein byte folgend auf mehrer bits", test_push_bits_and_bytes},
    {"get bit", test_get_bit},
    {"get byte", test_get_byte},
    {"pop bit", test_pop_bit}
};
int nr_of_unittests = 10;
