#include "testmain.h"
#include "../code.h"

char* name_of_testsuit = "code";

BOOL test_new(void)
{
	unsigned char test_zeichen = 'z';
	CODE* test_code = code_new(test_zeichen, bitarray_new());
	
	return (test_code != NULL);
}

BOOL test_free(void)
{
	unsigned char test_zeichen = 'z';
	CODE* test_code = code_new(test_zeichen, bitarray_new());
	
	code_free(&test_code);
	
	return (test_code == NULL);
}

BOOL test_get_zeichen(void)
{
	unsigned char test_zeichen = 'z';
	CODE* test_code = code_new(test_zeichen, bitarray_new());
	
	return (code_get_zeichen(test_code) == test_zeichen);
}

BOOL test_get_code(void)
{
	BITARRAY* test_bitarray = bitarray_new();
	CODE* test_code;
	
	bitarray_push_byte(test_bitarray, 0xFF);
	test_code = code_new('\0', test_bitarray);
	return bitarray_equals(code_get_code(test_code), test_bitarray);
}

BOOL test_cmp_codes_zeichen(void)
{
	unsigned char zeichen_gleich 	= '1';
	unsigned char zeichen_groesser 	= '2';
	unsigned char zeichen_kleiner 	= '0';
	
	CODE* test_code_gleich1 	= code_new(zeichen_gleich, bitarray_new());
	CODE* test_code_gleich2 	= code_new(zeichen_gleich, bitarray_new());
	CODE* test_code_groesser 	= code_new(zeichen_groesser, bitarray_new());
	CODE* test_code_kleiner 	= code_new(zeichen_kleiner, bitarray_new());
	
	return (cmp_codes_zeichen(test_code_gleich1, test_code_gleich2) == 0)
		&& (cmp_codes_zeichen(test_code_gleich1, test_code_groesser) == -1)
		&& (cmp_codes_zeichen(test_code_gleich1, test_code_kleiner) == 1);
}

BOOL test_equals(void)
{
	unsigned char zeichen_gleich 	= '1';
	unsigned char zeichen_ungleich 	= '2';
	BYTE byte_gleich 	= 0xFF;
	BYTE byte_ungleich 	= 0xF0;
	
	CODE* test_code_gleich;
	CODE* test_code_ungleich;
	BITARRAY* bitarray_gleich 		= bitarray_new();
	BITARRAY* bitarray_ungleich 	= bitarray_new();
	
	bitarray_push(bitarray_gleich, byte_gleich);
	bitarray_push(bitarray_ungleich, byte_ungleich);
	
	test_code_gleich 	= code_new(zeichen_gleich, bitarray_gleich);
	test_code_ungleich 	= code_new(zeichen_ungleich, bitarray_ungleich);
	
	return code_equals(test_code_gleich, test_code_gleich) 
		&& !code_equals(test_code_gleich, test_code_ungleich);
}

testunit testsuit[] = {
    {"new heap", test_new},
    {"free heap", test_free},
    {"get zeichen", test_get_zeichen},
    {"get code", test_get_code},
    {"vergleiche codes anhand von zeichen", test_cmp_codes_zeichen},
    {"prüfe 2 codes auf gleichheit", test_equals}
};
int nr_of_unittests = 6;
