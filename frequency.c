#include "frequency.h"

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

struct _FREQUENCY 
{
	unsigned char 		zeichen;
	unsigned int 		anzahl;
	struct _FREQUENCY* 	left;
	struct _FREQUENCY* 	right;
};

FREQUENCY* frequency_new_with_anzahl(unsigned char new_zeichen, unsigned int new_anzahl)
{
	FREQUENCY* retval 	= (FREQUENCY*)malloc(sizeof(FREQUENCY));
	ASSERT_ALLOC(retval);
	retval->zeichen 	= new_zeichen;
	retval->anzahl 		= new_anzahl;
	retval->left 		= NULL;
	retval->right 		= NULL;
	return retval;
}

void frequency_free(FREQUENCY** pp_freq)
{
	if ((pp_freq != NULL) && (*pp_freq != NULL))
	{
		/*printf("0x%1$x '%1$c'\n", (*pp_freq)->zeichen);
		printf("\t%p\n", pp_freq);
		printf("\t%p\n", *pp_freq);*/
		frequency_free(&((*pp_freq)->left));
		frequency_free(&((*pp_freq)->right));
		free(*pp_freq);
		(*pp_freq) = NULL;
	}
}

unsigned char frequency_get_zeichen(FREQUENCY* p_freq)
{
	if (p_freq != NULL)
	{
		return p_freq->zeichen;
	}
	return 0;
}

unsigned int frequency_get_anzahl(FREQUENCY* p_freq)
{
	if (p_freq != NULL)
	{
		return p_freq->anzahl;
	}
	return 0;
}

FREQUENCY* frequency_get_left(FREQUENCY* p_freq)
{
	if (p_freq != NULL)
	{
		return p_freq->left;
	}
	return NULL;
}

void frequency_set_left(FREQUENCY* p_freq, FREQUENCY* p_new_left)
{
	if (p_freq != NULL)
	{
		p_freq->left = p_new_left;
	}
}

FREQUENCY* frequency_get_right(FREQUENCY* p_freq)
{
	if (p_freq != NULL)
	{
		return p_freq->right;
	}
	return NULL;
}

void frequency_set_right(FREQUENCY* p_freq, FREQUENCY* p_new_right)
{
	if (p_freq != NULL)
	{
		p_freq->right = p_new_right;
	}
}

BOOL frequency_is_leaf(FREQUENCY* p_freq)
{
	return ((p_freq != NULL) && (p_freq->left == NULL) && (p_freq->right == NULL));
}

/*@unused@*/
/**
 * Gibt die Summe der Anzahlen der Frequenz und ihrer Kinder zurück.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return unsigned int 
 */
static unsigned int frequency_get_summe(FREQUENCY* p_freq)
{
	return ((p_freq == NULL)
            ? 0
            : p_freq->anzahl 
            				+ ((p_freq->left == NULL) 
            					? 0 
            					: p_freq->left->anzahl) 
            				+ ((p_freq->right == NULL) 
            					? 0 
            					: p_freq->left->anzahl));
	
	/*return ((p_freq == NULL)
            ? 0
            : p_freq->anzahl + frequency_get_summe(p_freq->left) + frequency_get_summe(p_freq->right));*/
}

int cmp_frequency_haeufigkeiten(FREQUENCY* p_freq1, FREQUENCY* p_freq2)
{
    if (p_freq1 == NULL) 
    {
        return -1;
    }
    
    if (p_freq2 == NULL) 
    {
        return 1;
    }

    return ((p_freq1->anzahl == p_freq2->anzahl) 
            ? 0 
            : ((p_freq1->anzahl > p_freq2->anzahl) 
                ? 1 
                : -1));
}

void frequency_print(FREQUENCY* p_freq, int depth, int index)
{
	int i = 0;
	
	if (p_freq == NULL)
	{
		return;
	}
	
	for (i = 0; i < depth; i++)
	{
		printf("\t");
	}
	
	/*printf("|-- ('%c':%u) @%d\n", p_freq->zeichen, p_freq->anzahl, index - 1);*/
	printf("|-- ('%c':%u) @%d @%p\n", p_freq->zeichen, p_freq->anzahl, index - 1, p_freq);
	frequency_print(p_freq->left, i + 1, index * 2);
	frequency_print(p_freq->right, i + 1, (index * 2) + 1);
	
}

unsigned int frequency_get_height(FREQUENCY* p_freq)
{	
	return (p_freq == NULL) 
			? 0 
			: MAX(frequency_get_height(p_freq->left), frequency_get_height(p_freq->right)) + 1;
}

BOOL frequency_equals(FREQUENCY* p_freq1, FREQUENCY* p_freq2)
{
	if (p_freq1 == NULL && p_freq2 == NULL)
	{
		return TRUE;
	}
	else if (p_freq1 == NULL)
	{
		return FALSE;
	}
	else if (p_freq2 == NULL)
	{
		return FALSE;
	}
	else
	{
		if (p_freq1->zeichen != p_freq2->zeichen)
		{
			/*printf("Zeichen unterschiedlich '%c' <-> '%c'\n", p_freq1->zeichen, p_freq2->zeichen);*/
			return FALSE;
		}
		else
		{
			return (frequency_equals(p_freq1->left, p_freq2->left)
					&& frequency_equals(p_freq1->right, p_freq2->right));
		}
	}
}
