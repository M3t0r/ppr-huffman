#include "code.h"

struct _CODE {
	unsigned char 	zeichen;
	BITARRAY* 		code;
};

CODE* code_new(unsigned char z, BITARRAY* p_bitarray)
{
	unsigned int i;
	CODE* retval 	= (CODE*)malloc(sizeof(CODE));
	ASSERT_ALLOC(retval);
	
	retval->zeichen = z;
	retval->code 	= NULL;
	if (p_bitarray != NULL)
	{
		retval->code 	= bitarray_new();
		for (i = 0; i < bitarray_length(p_bitarray); i++)
		{
			bitarray_push(retval->code, bitarray_get_bit(p_bitarray, i));
		}
	}
	
	return retval;
}

void code_free(CODE** pp_code)
{
	if ((pp_code != NULL) && (*pp_code != NULL))
	{
		if ((*pp_code)->code != NULL) {
			bitarray_free(&((*pp_code)->code));
		}
		free((*pp_code)->code);
		free(*pp_code);
		*pp_code = NULL;
	}
}

unsigned char code_get_zeichen(CODE* p_code)
{
	if (p_code == NULL)
	{
		return 0;
	}
	
	return p_code->zeichen;
}

BITARRAY* code_get_code(CODE* p_code)
{
	if (p_code == NULL)
	{
		return NULL;
	}
	
	return p_code->code;
}

int cmp_codes_zeichen(CODE* p_code1, CODE* p_code2)
{
	if (p_code1 == NULL || p_code1->code == NULL)
	{
		return -1;
	}
	
	if (p_code2 == NULL || p_code2->code == NULL)
	{
		return 1;
	}
	
	return ((p_code1->zeichen == p_code2->zeichen) 
    		? 0
    		: ((p_code1->zeichen > p_code2->zeichen) 
    			? 1
    			: -1));
}

BOOL code_equals(CODE* c1, CODE* c2)
{
	if (c1->zeichen != c2->zeichen)
	{
		/*printf("zeichen ist unterschiedlich (0x%x <-> 0x%x)\n", c1->zeichen, c2->zeichen);*/
		return FALSE;
	}
	else
	{
		if (!bitarray_equals(c1->code, c2->code))
		{
			return FALSE;
		}
	}
	return TRUE;
}
