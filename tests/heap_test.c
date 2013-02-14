#include "testmain.h"
#include "../heap.h"

char* name_of_testsuit = "heap";

static int cmp_char(char* c1, char* c2)
{
	if (c1 == NULL)
	{
		return -1;
	}
	else if (c2 == NULL)
	{
		return 1;
	}
	else
	{
		return ((*c1 == *c2) 
			? 0 
			: ((*c1 > *c2) 
				? 1 
				: -1));
	}
}

static int cmp_int(int* c1, int* c2)
{
	if (c1 == NULL)
	{
		return -1;
	}
	else if (c2 == NULL)
	{
		return 1;
	}
	else
	{
		return ((*c1 == *c2) 
			? 0 
			: ((*c1 > *c2) 
				? 1 
				: -1));
	}
}

BOOL test_new(void)
{
	HEAP* test_heap = heap_new((CMP_FCT)cmp_char);
	return (test_heap != NULL);
}

BOOL test_free(void)
{
	HEAP* test_heap = heap_new((CMP_FCT)cmp_char);
	heap_free(&test_heap);
	return (test_heap == NULL);
}

BOOL test_size(void)
{
	HEAP* test_heap = heap_new((CMP_FCT)cmp_char);
	return (heap_size(test_heap) == 0);
}

BOOL test_push(void)
{
	int i;
	char* orig_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* new_str = malloc(strlen(orig_str) * sizeof(char) + 1);
	HEAP* test_heap = heap_new((CMP_FCT)cmp_char);
	
	for (i = 0; i < (int)strlen(orig_str); i++)
	{
		char* tmp = malloc(sizeof(char) + 1);
		tmp[0] = orig_str[i];
		tmp[1] = '\0';
		heap_push(test_heap, (void*)tmp);
	}
	
	return (heap_size(test_heap) == strlen(orig_str));
}

BOOL test_push_und_pop_chars(void)
{
	int i;
	char* orig_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* new_str = malloc(strlen(orig_str) * sizeof(char) + 1);
	HEAP* test_heap = heap_new((CMP_FCT)cmp_char);
	
	for (i = 0; i < (int)strlen(orig_str); i++)
	{
		char* tmp = malloc(sizeof(char) + 1);
		tmp[0] = orig_str[i];
		tmp[1] = '\0';
		heap_push(test_heap, (void*)tmp);
	}
	
	i = 0;
	while (heap_size(test_heap) > 0)
	{
		char tmp = ((char*)heap_pop(test_heap))[0];
		new_str[i] = tmp;
		i++;
	}
	new_str[i]= '\0';
	
	heap_free(&test_heap);
	
	return !strncmp(orig_str, new_str, strlen(orig_str));
}

BOOL test_push_und_pop_ints(void)
{
	int i;
	BOOL retval = TRUE;
	int orig_int[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int* new_int = malloc(10 * sizeof(int));
	HEAP* test_heap = heap_new((CMP_FCT)cmp_int);
	
	for (i = 0; i < 10; i++)
	{
		int* tmp = &(orig_int[i]);
		heap_push(test_heap, (void*)tmp);
	}
	
	i = 0;
	while (heap_size(test_heap) > 0)
	{
		int* tmp = (int*)heap_pop(test_heap);
		new_int[i] = *tmp;
		i++;
	}
	
	for (i = 0; i < 10; i++)
	{
		retval &= (orig_int[i] == new_int[i]);
	}
	
	heap_free(&test_heap);
	
	return retval;
}

BOOL test_get_element(void)
{
	int i;
	char* orig_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* new_str = malloc(strlen(orig_str) * sizeof(char) + 1);
	HEAP* test_heap = heap_new((CMP_FCT)cmp_char);
	
	for (i = 0; i < (int)strlen(orig_str); i++)
	{
		char* tmp = malloc(sizeof(char) + 1);
		tmp[0] = orig_str[i];
		tmp[1] = '\0';
		heap_push(test_heap, (void*)tmp);
	}
	
	return !strncmp((char*)heap_get_element(test_heap, 0), "A", 1);
}

testunit testsuit[] = {
    {"new heap", test_new},
    {"free heap", test_free},
    {"teste size", test_size},
    {"push ein paar chars", test_push},
    {"push und pop ein paar chars", test_push_und_pop_chars},
    {"push und pop ein paar ints", test_push_und_pop_ints},
    {"teste get_element", test_get_element}
};
int nr_of_unittests = 7;
