#include "testmain.h"
#include "../codebuch.h"

char* name_of_testsuit = "codebuch";

CODEBUCH* codebuch_new_from_frequency(unsigned int frequencies[256]);
CODEBUCH* codebuch_new_from_structure(BITARRAY* p_ba);
void codebuch_free(CODEBUCH** pp_cb);
BITARRAY* codebuch_code_for_char(CODEBUCH* p_cb, unsigned char c);
unsigned char codebuch_char_for_code(CODEBUCH* p_cb, BITARRAY* p_code, unsigned int* p_used_bits);
BITARRAY* codebuch_structure(CODEBUCH* p_cb);
BOOL codebuch_last_char_was_error(CODEBUCH* p_cb);
BOOL codebuch_equals(CODEBUCH* p_cb1, CODEBUCH* p_cb2);

static CODEBUCH* build_test_codebuch(void)
{
	CODEBUCH* retval;
	unsigned int f[256];
	int i;
	
	for (i = 0; i < 256; i++)
	{
		f[i] = 0;
	}
	
	f['A'] = 4;
	f['C'] = 2;
	f['D'] = 2;
	f['E'] = 2;
	f['F'] = 5;
	f['G'] = 1;
	f['H'] = 3;
	f['I'] = 1;
	f['L'] = 2;
	f['M'] = 1;
	f['N'] = 1;
	f['O'] = 1;
	f['P'] = 1;
	f['R'] = 1;
	f['S'] = 4;
	f['T'] = 2;
	f['U'] = 1;
	
	retval = codebuch_new_from_frequency(f);
	
	return retval;
}

BOOL test_new_from_frequency(void)
{
	CODEBUCH* test_codebuch = build_test_codebuch();
	
	return (test_codebuch != NULL);
}

BOOL test_structure(void)
{
	CODEBUCH* test_codebuch = build_test_codebuch();
	BITARRAY* test_bitarray = codebuch_structure(test_codebuch);
	
	return (bitarray_length(test_bitarray) != 0);
}

BOOL test_new_from_structure(void)
{
	CODEBUCH* orig_codebuch = build_test_codebuch();
	BITARRAY* ba 			= codebuch_structure(orig_codebuch);
	CODEBUCH* test_codebuch = codebuch_new_from_structure(ba);
	
	return codebuch_equals(orig_codebuch, test_codebuch);
}

BOOL test_free(void)
{
	CODEBUCH* test_codebuch = build_test_codebuch();
	
	codebuch_free(&test_codebuch);
	
	return (test_codebuch == NULL);
}

BOOL test_char_for_code(void)
{
	return FALSE;
}

BOOL test_code_for_char(void)
{
	return FALSE;
}

BOOL test_last_char_was_error(void)
{
	return FALSE;
}

BOOL test_equals(void)
{
	CODEBUCH* test_codebuch_gleich = build_test_codebuch();
		
	return codebuch_equals(test_codebuch_gleich, test_codebuch_gleich)
		&& !codebuch_equals(test_codebuch_gleich, NULL);
}

testunit testsuit[] = {
    {"new codebuch from frequency", test_new_from_frequency},
    {"codebuch to structure", test_structure},
    {"new codebuch from structure", test_new_from_structure},
    {"free codebuch", test_free},
    {"char for code", test_char_for_code},
    {"code for char", test_code_for_char},
    {"error-handling testen", test_last_char_was_error},
    {"prüfe 2 codebücher auf gleichheit", test_equals}
};
int nr_of_unittests = 8;
