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

BOOL test_remove_front()
{
    BITARRAY *ba = bitarray_new();
    bitarray_push_byte(ba, 'T');
    bitarray_push_byte(ba, 'e');
    bitarray_push_byte(ba, 's');
    bitarray_push_byte(ba, 't');
    
    bitarray_remove_front(ba, 12); /* 'T' und halbes 'e' */
    
    return bitarray_length(ba) == 20
        && bitarray_get_bit(ba, 0) == FALSE
        && bitarray_get_bit(ba, 1) == TRUE
        && bitarray_get_bit(ba, 2) == FALSE
        && bitarray_get_bit(ba, 3) == TRUE
        && bitarray_get_byte(ba, 4) == 's'
        && bitarray_get_byte(ba, 12) == 't';
}

BOOL test_merge()
{
    BITARRAY *ba1 = bitarray_new();
    BITARRAY *ba2 = bitarray_new();
    
    bitarray_push_byte(ba1, 'T');
    bitarray_push(ba1, FALSE);
    bitarray_push(ba1, TRUE);
    bitarray_push(ba1, TRUE);
    bitarray_push(ba1, FALSE);
    
    bitarray_push(ba2, FALSE);
    bitarray_push(ba2, TRUE);
    bitarray_push(ba2, FALSE);
    bitarray_push(ba2, TRUE);
    bitarray_push_byte(ba2, 's');
    bitarray_push_byte(ba2, 't');
    
    bitarray_merge(ba1, ba2);
    
    return bitarray_length(ba1) == 32
        && bitarray_get_byte(ba1, 0)  == 'T'
        && bitarray_get_byte(ba1, 8)  == 'e'
        && bitarray_get_byte(ba1, 16) == 's'
        && bitarray_get_byte(ba1, 24) == 't';
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
    {"pop bit", test_pop_bit},
    {"remove front", test_remove_front},
    {"bitarrays mergen", test_merge}
};
int nr_of_unittests = 12;
