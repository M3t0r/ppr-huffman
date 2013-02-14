#include "testmain.h"
#include "../frequency.h"

char* name_of_testsuit = "frequency";

BOOL test_new(void)
{
	FREQUENCY* test_frequency = frequency_new_with_anzahl('\0', 0);
	
	return (test_frequency != NULL);
}

BOOL test_free(void)
{
	FREQUENCY* test_frequency = frequency_new_with_anzahl('\0', 0);
	
	frequency_free(&test_frequency);
	
	return (test_frequency == NULL);
}

BOOL test_get_zeichen(void)
{
	unsigned char zeichen = 'z';
	FREQUENCY* test_frequency = frequency_new_with_anzahl(zeichen, 0);
	
	return (frequency_get_zeichen(NULL) == 0)
		&& (frequency_get_zeichen(test_frequency) == zeichen);
}

BOOL test_get_anzahl(void)
{
	unsigned int anzahl = 10;
	FREQUENCY* test_frequency = frequency_new_with_anzahl('\0', anzahl);
	
	return (frequency_get_anzahl(NULL) == 0)
		&& (frequency_get_anzahl(test_frequency) == anzahl);
}

BOOL test_get_left(void)
{
	FREQUENCY* test_frequency = frequency_new_with_anzahl('\0', 0);
	FREQUENCY* left_frequency = frequency_new_with_anzahl('\0', 0);
	
	frequency_set_left(test_frequency, left_frequency);
	
	return (frequency_get_left(NULL) == NULL)
		&& (frequency_get_left(test_frequency) == left_frequency)
		&& (frequency_get_left(frequency_get_left(test_frequency)) == NULL);
}

BOOL test_get_right(void)
{
	FREQUENCY* test_frequency = frequency_new_with_anzahl('\0', 0);
	FREQUENCY* right_frequency = frequency_new_with_anzahl('\0', 0);
	
	frequency_set_right(test_frequency, right_frequency);
	
	return (frequency_get_right(NULL) == NULL)
		&& (frequency_get_right(test_frequency) == right_frequency)
		&& (frequency_get_right(frequency_get_right(test_frequency)) == NULL);
}

BOOL test_get_height(void)
{
	FREQUENCY* test_frequency 	= frequency_new_with_anzahl('\0', 0);
	FREQUENCY* left_frequency 	= frequency_new_with_anzahl('\0', 0);
	FREQUENCY* right_frequency1 = frequency_new_with_anzahl('\0', 0);
	FREQUENCY* right_frequency2 = frequency_new_with_anzahl('\0', 0);
	
	frequency_set_right(right_frequency1, right_frequency2);
	frequency_set_right(test_frequency, right_frequency1);
	frequency_set_left(test_frequency, left_frequency);
	
	return (frequency_get_height(NULL) == 0)
		&& (frequency_get_height(test_frequency) == 3)
		&& (frequency_get_height(right_frequency1) == 2)
		&& (frequency_get_height(right_frequency2) == 1);
}

BOOL test_is_leaf(void)
{
	FREQUENCY* test_frequency = frequency_new_with_anzahl('\0', 0);
	FREQUENCY* left_frequency = frequency_new_with_anzahl('\0', 0);
	
	frequency_set_left(test_frequency, left_frequency);
	
	return !frequency_is_leaf(NULL)
		&& !frequency_is_leaf(test_frequency)
		&& frequency_is_leaf(frequency_get_left(test_frequency));
}

BOOL test_cmp_frequency_haeufigkeiten(void)
{
	unsigned int anzahl_gleich 			= 1;
	unsigned int anzahl_groesser 		= 2;
	unsigned int anzahl_kleiner 		= 0;
	FREQUENCY* test_frequency_gleich 	= frequency_new_with_anzahl('\0', anzahl_gleich);
	FREQUENCY* test_frequency_groesser 	= frequency_new_with_anzahl('\0', anzahl_groesser);
	FREQUENCY* test_frequency_kleiner 	= frequency_new_with_anzahl('\0', anzahl_kleiner);
	
	return (cmp_frequency_haeufigkeiten(test_frequency_gleich, test_frequency_gleich) == 0)
		&& (cmp_frequency_haeufigkeiten(test_frequency_gleich, test_frequency_groesser) == -1)
		&& (cmp_frequency_haeufigkeiten(test_frequency_gleich, test_frequency_kleiner) == 1);
}

BOOL test_equals(void)
{
	unsigned char zeichen_gleich 		= '1';
	unsigned char zeichen_ungleich 		= '0';
	unsigned int anzahl_gleich 			= 1;
	unsigned int anzahl_ungleich 		= 0;
	FREQUENCY* test_frequency_gleich 	= frequency_new_with_anzahl(zeichen_gleich, anzahl_gleich);
	FREQUENCY* test_frequency_ungleich 	= frequency_new_with_anzahl(zeichen_ungleich, anzahl_ungleich);
	FREQUENCY* left_frequency 			= frequency_new_with_anzahl(zeichen_ungleich, anzahl_gleich);
	
	frequency_set_left(test_frequency_gleich, left_frequency);
	
	return frequency_equals(test_frequency_gleich, test_frequency_gleich)
		&& !frequency_equals(test_frequency_gleich, test_frequency_ungleich)
		&& !frequency_equals(test_frequency_gleich, NULL);
}

testunit testsuit[] = {
    {"new frequency", test_new},
    {"free frequency", test_free},
    {"get zeichen", test_get_zeichen},
    {"get anzahl", test_get_anzahl},
    {"get left", test_get_left},
    {"get right", test_get_right},
    {"get height", test_get_height},
    {"is leaf", test_is_leaf},
    {"vergleiche 2 frequencies anhand ihrer haeufigkeiten", test_cmp_frequency_haeufigkeiten},
    {"prüfe 2 frequencies auf gleichheit", test_equals}
};
int nr_of_unittests = 10;
