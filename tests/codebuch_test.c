#include "testmain.h"
#include "../codebuch.h"
#include <string.h>

char* name_of_testsuit = "codebuch";

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

BOOL test_code_for_char(void)
{
	CODEBUCH* cb1 	= build_test_codebuch();
	BITARRAY* ba 	= codebuch_structure(cb1);
	CODEBUCH* cb2	= codebuch_new_from_structure(ba);
	char* chars 	= "DONAUMPFSCHIRTGEL";
	int len 		= strlen(chars);
	int i;
		
	for (i = 0; i < len; i++)
	{
		BITARRAY* ba1 = codebuch_code_for_char(cb1, chars[i]);
		BITARRAY* ba2 = codebuch_code_for_char(cb2, chars[i]);
		if (!bitarray_equals(ba1, ba2))
		{
			int j;
			printf("codes für '%c' unterschiedlich\n", chars[i]);
			for (j = 0; j < bitarray_length(ba1); j++)
			{
				printf("%d", bitarray_get_bit(ba1, j));
			}
			printf("\n<->\n");
			for (j = 0; j < bitarray_length(ba2); j++)
			{
				printf("%d", bitarray_get_bit(ba2, j));
			}
			printf("\n");
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL test_char_for_code(void)
{
	CODEBUCH* cb1 		= build_test_codebuch();
	BITARRAY* ba 		= codebuch_structure(cb1);
	CODEBUCH* cb2 		= codebuch_new_from_structure(ba);
	char* chars 		= "DONAUMPFSCHIRTGEL";
	int len 			= strlen(chars);
	BITARRAY** codes	= malloc(len * sizeof(BITARRAY*));
	int i;
	int index;

	index = 0;
	for (i = 0; i < len; i++)
	{
		BITARRAY* tmp1 = codebuch_code_for_char(cb1, chars[i]);
		BITARRAY* tmp2 = codebuch_code_for_char(cb2, chars[i]);
		
		if (!bitarray_equals(tmp1, tmp2))
		{
			return FALSE;
		}
		else
		{
			codes[index++] = tmp1;
		}
	}
	
	for (i = 0; i < index; i++)
	{
		unsigned int tmp = 0;
		unsigned char zeichen = codebuch_char_for_code(cb1, codes[i], &tmp);
		
		if ((zeichen == 0) && codebuch_last_char_was_error(cb1))
		{
			return FALSE;
		}
		else if (zeichen != chars[i])
		{
			return FALSE;
		}
	}
	
	ba = bitarray_new();
	bitarray_push(ba, FALSE);
	bitarray_push(ba, FALSE);
	bitarray_push(ba, FALSE);
	bitarray_push(ba, FALSE);
	bitarray_push(ba, FALSE);
	bitarray_push(ba, FALSE);
	
	return TRUE && (codebuch_char_for_code(cb1, ba, NULL) == 'O');
}

BOOL test_last_char_was_error(void)
{
	CODEBUCH* test_codebuch = build_test_codebuch();
	unsigned char zeichen = codebuch_char_for_code(test_codebuch, NULL, NULL);
	return (zeichen == 0) && codebuch_last_char_was_error(test_codebuch);
}

BOOL test_equals(void)
{
	CODEBUCH* test_codebuch_gleich = build_test_codebuch();
	CODEBUCH* test_codebuch_ungleich;
	unsigned int f[256];
	int i;
	
	for (i = 0; i < 256; i++)
	{
		f[i] = 0;
	}
	
	f['A'] = 5;
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
	
	test_codebuch_ungleich = codebuch_new_from_frequency(f);
		
	return codebuch_equals(test_codebuch_gleich, test_codebuch_gleich)
		&& !codebuch_equals(test_codebuch_gleich, test_codebuch_ungleich)
		&& !codebuch_equals(test_codebuch_gleich, NULL)
		&& codebuch_equals(NULL, NULL);
}

static BOOL test_undso(char* orig_str)
{
	BITARRAY** codes;
	BITARRAY* full_code;
	
	CODEBUCH* cb1;
	CODEBUCH* cb2;
	BITARRAY* ba;
	
	unsigned int f[256];
	unsigned int i;
	unsigned int count;
	
	BOOL retval 	= TRUE;
	
	size_t len 		= strlen(orig_str);
	char* test_str 	= malloc(len * sizeof(char) + 1);
	
	/* frequencies nullen */
	memset(f, 0, sizeof(unsigned int) * 256);
	
	/* frequencies setzen */
	for (i = 0; i < len; i++)
	{
		f[(int)orig_str[i]]++;
	}
	
	/* verschiedene zeichen zählen */
	count = 0;
	for (i = 0; i < 256; i++)
	{
		if (f[i] > 0)
		{
			count++;
		}
	}
	
	codes = malloc(count * sizeof(BITARRAY*));
	
	/* codebuch erzeugen, speichern und neu auslesen */
	cb1 = codebuch_new_from_frequency(f);
	ba 	= codebuch_structure(cb1);
	cb2 = codebuch_new_from_structure(ba);
	
	retval &= codebuch_equals(cb1, cb2);
	
	/* codes der vorhandenen zeichen aus beiden codebüchern vergleichen */
	count = 0;
	for (i = 0; i < 256; i++)
	{
		if (f[i] > 0)
		{
			BITARRAY* ba1 = codebuch_code_for_char(cb1, (unsigned char)i);
			BITARRAY* ba2 = codebuch_code_for_char(cb2, (unsigned char)i);
			
			retval &= bitarray_equals(ba1, ba2);
			if (!retval)
			{
				printf("codes für '%c' unterschiedlich\n", (unsigned char)i);
				return FALSE;
			}
			else
			{
				codes[count] = ba1;
				count++;
			}
		}
	}
	
	full_code = bitarray_new();
	
	/* orig_str als codes darstellen */
	for (i = 0; i < len; i++)
	{
		unsigned int j;
		BITARRAY* tmp = codebuch_code_for_char(cb1, (unsigned char)orig_str[i]);

		for (j = 0; j < (unsigned int)bitarray_length(tmp); j++)
		{
			bitarray_push(full_code, bitarray_get_bit(tmp, j));
		}
	}
	
	/* test_str aus codes des orig_str wiederherstellen */
	for (i = 0; i < len; i++)
	{
		unsigned int tmp = 0;
		unsigned char zeichen = codebuch_char_for_code(cb1, full_code, &tmp);
		bitarray_remove_front(full_code, tmp);
				
		if ((zeichen == 0) && codebuch_last_char_was_error(cb1))
		{
			printf("codebuch_last_char_was_error!\n");
			return FALSE;
		}
		
		test_str[i] = zeichen;
	}
	test_str[i] = '\0';
		
	return retval && !strncmp(orig_str, test_str, len);
}

BOOL test_all(void)
{
	return test_undso("DONAUDAMPFSCHIFFFAHRTSGESELLSCHAFT")
		&& test_undso("Test")
		&& test_undso("Lorem ipsum dolor sit amet")
		&& test_undso("The quick brown fox jumps over the lazy dog.");
}

BOOL test1(void)
{
	char* orig_ba = "110100000010000011110011101011110000000100111110010001010000010010010110001000001010111110001101011110101011101111110010001011001010101001"; 
	char* test_str = malloc(strlen("DONAUDAMPFSCHIFFFAHRTSGESELLSCHAFT\n") * sizeof(char) + 1);
	CODEBUCH* cb = build_test_codebuch();
	BITARRAY* full_code = bitarray_new();
	int i;
	
	for (i = 0; i < strlen(orig_ba); i++)
	{
		bitarray_push(full_code, ((orig_ba[i] == '0') ? FALSE : TRUE));
	}
	
	while (bitarray_length(full_code) > 0)
	{
		unsigned int tmp = 0;
		unsigned int j;
		BITARRAY* tmp_ba = bitarray_new();
		unsigned char zeichen = codebuch_char_for_code(cb, full_code, &tmp);
		
		if ((zeichen == 0) && codebuch_last_char_was_error(cb))
		{
			return FALSE;
		}
		
		test_str[i] = zeichen;
		
		for (j = tmp; j < (unsigned int)bitarray_length(full_code); j++)
		{
			bitarray_push(tmp_ba, bitarray_get_bit(full_code, j));
		}
		
		full_code = tmp_ba;
	}
	test_str[i] = '\0';

	printf("| 'DONAUDAMPFSCHIFFFAHRTSGESELLSCHAFT\\n'\n| <->\n| '%s'\n", test_str);
	
	return !strcmp("DONAUDAMPFSCHIFFFAHRTSGESELLSCHAFT\n", test_str);
}

testunit testsuit[] = {
    {"new codebuch from frequency", test_new_from_frequency},
    {"codebuch to structure", test_structure},
    {"new codebuch from structure", test_new_from_structure},
    {"free codebuch", test_free},
    {"code for char", test_code_for_char},
    {"char for code", test_char_for_code},
    {"error-handling testen", test_last_char_was_error},
    {"prüfe 2 codebücher auf gleichheit", test_equals},
    {"teste alles", test_all}
};
int nr_of_unittests = 9;
