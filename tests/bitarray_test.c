#include "testmain.h"
#include "../bitarray.h"

char *name_of_testsuit = "bitarray";




BOOL test_new()
{
    BITARRAY *ba = bitarray_new();
    
    if(ba->data == NULL)
        return FALSE;
        
    return TRUE;
}



testunit testsuit[] = {
    {"new bitarray", test_new}
};
int nr_of_unittests = 1;
