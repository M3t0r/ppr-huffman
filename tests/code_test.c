#include "testmain.h"
#include "../code.h"

char* name_of_testsuit = "code";

CODE* code_new(unsigned char z, BITARRAY* p_bitarray);
void code_free(CODE** pp_code);
unsigned char code_get_zeichen(CODE* p_code);
BITARRAY* code_get_code(CODE* p_code);
int cmp_codes_zeichen(CODE* p_code1, CODE* p_code2);
BOOL code_equals(CODE* c1, CODE* c2);

BOOL test_new(void)
{
	unsigned char test_zeichen = 'z';
	CODE* test_code = code_new(test_zeichen, NULL);
	
	return (test_code != NULL);
}

BOOL test_free(void)
{
	unsigned char test_zeichen = 'z';
	CODE* test_code = code_new(test_zeichen, NULL);
	
	code_free(test_code);
	
	return (test_code == NULL);
}

BOOL test_get_zeichen(void)
{
	unsigned char test_zeichen = 'z';
	CODE* test_code = code_new(test_zeichen, NULL);
	
	return (code_get_zeichen(test_code) == test_zeichen);
}

BOOL test_get_code(void)
{
	BITARRAY* test_bitarray = bitarray_new();
	CODE* test_code;
	
	bitarray_push_byte(test_bitarray, 0xFF);
	test_code = code_new('\0', test_bitarray);
	return bitarray_equals(code_get_code(test_code), test_code);
}

BOOL test_cmp_codes_zeichen(void)
{
	unsigned char zeichen_gleich 	= '1';
	unsigned char zeichen_groesser 	= '2';
	unsigned char zeichen_kleiner 	= '0';
	
	CODE* test_code_gleich1 	= code_new(zeichen_gleich, NULL);
	CODE* test_code_gleich2 	= code_new(zeichen_gleich, NULL);
	CODE* test_code_groesser 	= code_new(zeichen_groesser, NULL);
	CODE* test_code_kleiner 	= code_new(zeichen_kleiner, NULL);
	
	return (cmp_codes_zeichen(test_code_gleich1, test_code_gleich2) == 0)
		&& (cmp_codes_zeichen(test_code_gleich1, test_code_groesser) == -1)
		&& (cmp_codes_zeichen(test_code_gleich1, test_code_kleiner) == 1);
}

BOOL test_equals(void)
{
	
}

testunit testsuit[] = {
    {"new heap", test_new},
};
int nr_of_unittests = ;
