/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "codebuch.h"
#include "heap.h"
#include "code.h"
#include "frequency.h"

#include <math.h>

/*****************************************************************************
 * Makrodefinition
 *****************************************************************************/
#define MAX(a, b) (((a) >= (b)) ? (a) : (b))


/*****************************************************************************
 * Strukturdefinitionen
 *****************************************************************************/
/**
 * Struktur eines Codebuchs.
 */
struct _CODEBUCH 
{
	/* Baum der einzelnen Frequenzen */
	FREQUENCY* 		baum;
	
	/* Die Codes für jedes Zeichen, nach Zeichen sortiert */
	void** 			codes;
	
	/* Die Anzahl der vorhandenen Codes */
	unsigned int 	codes_used;
	
	/* Anzahlen der Vorkommen fuer jedes Zeichen */
	unsigned int	frequencies[256];
	
	/* Die Größe des größten Codes */
	unsigned char	max_code_length;
};



/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Fuegt einen neuen Code dem Codebuch hinzu.
 * @param p_cb Das Codebuch.
 * @param p_code Der hinzuzufuegende Code.
 */
static void add_code(CODEBUCH* p_cb, CODE* p_code);

/**
 * Baut das Codebuch rekursiv aus einem Frequenz-Baum auf.
 * @param p_freq Der aktuelle Wurzelknoten.
 * @param p_prev_path Der bisherige Pfad.
 * @param p_cb Das Codebuch.
 */
static void build_codebuch(FREQUENCY* p_freq, BITARRAY* p_prev_path, CODEBUCH* p_cb);

/**
 * Erzeugt ein Grundgeruest für ein neues Codebuch.
 * @param p_baum Der Codebaum.
 * @param num_codes Die Anzahl der Codes. (Anzahl der verschiedenen vorhandenen Zeichen)
 * @param freqs Die Anzahlen aller Zeichen.
 * @return Das Grundgeruest des neuen Codebuchs.
 */
static CODEBUCH* codebuch_new(FREQUENCY* p_baum, int num_codes, unsigned int freqs[256]);

/**
 * Ueberprueft die Codes von zwei Codebuechern auf Gleichheit.
 * @param p_cb1 Das eine Codebuch.
 * @param p_cb2 Das andere Codebuch.
 * @return TRUE falls die Codes beider Codebuecher gleich sind, FALSE sonst.
 */
static BOOL codes_equal(CODEBUCH* p_cb1, CODEBUCH* p_cb2);


/*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
/* ---------------------------------------------------------------------------
 * Funktion: codebuch_new
 * ------------------------------------------------------------------------ */
static CODEBUCH* codebuch_new(FREQUENCY* p_baum, int num_codes, unsigned int freqs[256])
{
	int i;
    CODEBUCH* retval 		= malloc(sizeof(CODEBUCH));
    ASSERT_ALLOC(retval);

	retval->baum 			= p_baum;

    retval->codes 			= malloc((num_codes * sizeof(void*)));
    ASSERT_ALLOC(retval->codes);
    retval->codes_used 		= 0;

	for (i = 0; i < 256; i++)
	{
		retval->frequencies[i] = freqs[i];
	}
	
	retval->max_code_length = 0;
	
    return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: add_code
 * ------------------------------------------------------------------------ */
static void add_code(CODEBUCH* p_cb, CODE* p_code) 
{	
    if ((p_cb != NULL) && (p_cb->codes != NULL) && (p_code != NULL)) 
    {
    	long i;
    	
    	p_cb->max_code_length = MAX(p_cb->max_code_length, code_get_length(p_code));
    	
    	if (p_cb->codes_used == 0)
    	{
    		p_cb->codes[0] = (void*)p_code;
    		p_cb->codes_used++;
    		return;
    	}
		
		for (i = (long)(p_cb->codes_used - 1); (i >= 0) && (code_get_zeichen((CODE*)p_cb->codes[i]) > code_get_zeichen(p_code)); i--)
		{
			p_cb->codes[i + 1] = p_cb->codes[i];
		}
		
		p_cb->codes[i + 1] = (void*)p_code;
		p_cb->codes_used++;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: build_codebuch
 * ------------------------------------------------------------------------ */
static void build_codebuch(FREQUENCY* p_freq, BITARRAY* p_prev_path, CODEBUCH* p_cb)
{
	unsigned int len = bitarray_length(p_prev_path);
	
	if ((p_freq == NULL) || (p_prev_path == NULL) || (p_cb == NULL))
	{
		return;
	}
		
	if (frequency_is_leaf(p_freq))
	{
		add_code(p_cb, code_new(frequency_get_zeichen(p_freq), p_prev_path));
	}
	else
	{
		if (frequency_get_left(p_freq) != NULL)
		{
			BITARRAY* tmp_left = bitarray_new();
			unsigned int i;
			
			for (i = 0; i < len; i++)
			{
				bitarray_push(tmp_left, bitarray_get_bit(p_prev_path, i));
			}
			
			bitarray_push(tmp_left, (BOOL)0);
			build_codebuch(frequency_get_left(p_freq), tmp_left, p_cb);
		}
		
		if (frequency_get_right(p_freq) != NULL)
		{
			BITARRAY* tmp_right = bitarray_new();
			unsigned int i;
			
			for (i = 0; i < len; i++)
			{
				bitarray_push(tmp_right, bitarray_get_bit(p_prev_path, i));
			}
			
			bitarray_push(tmp_right, (BOOL)1);
			build_codebuch(frequency_get_right(p_freq), tmp_right, p_cb);
		}
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_new_from_frequency
 * ------------------------------------------------------------------------ */
CODEBUCH* codebuch_new_from_frequency(unsigned int frequencies[256])
{
	int i;
	CODEBUCH* retval;
	int count 	= 0;
	HEAP* H 	= heap_new((CMP_FCT)cmp_frequency_haeufigkeiten);
	
	for (i = 0; i < 256; i++)
	{
		if (frequencies[i] > 0)
		{		
			heap_push(H, frequency_new_with_anzahl((unsigned char)i, frequencies[i]));
			count++;
		}
	}
	
	if (count <= 0)
	{
		printf("Keine Häufigkeiten vorhanden\n");
		return NULL;
	}
	
	if (heap_get_size(H) == 1)
	{
		FREQUENCY* p_freq 		= heap_pop(H);
		FREQUENCY* p_new_freq 	= frequency_new_with_anzahl(0, frequency_get_anzahl(p_freq));
		frequency_set_left(p_new_freq, p_freq);
		frequency_set_right(p_new_freq, NULL);
		heap_push(H, p_new_freq);
	}
	else
	{
		while (heap_get_size(H) > 1) 
		{
			FREQUENCY* p_freq1 		= heap_pop(H);
			FREQUENCY* p_freq2 		= heap_pop(H);
			unsigned int summe1 	= frequency_get_anzahl(p_freq1);
			unsigned int summe2 	= frequency_get_anzahl(p_freq2);
			FREQUENCY* p_new_freq 	= frequency_new_with_anzahl(0, summe1 + summe2);
			if (frequency_get_height(p_freq1) > frequency_get_height(p_freq2))
			{
				frequency_set_left(p_new_freq, p_freq1);
				frequency_set_right(p_new_freq, p_freq2);
			}
			else
			{
				frequency_set_left(p_new_freq, p_freq2);
				frequency_set_right(p_new_freq, p_freq1);
			}
			heap_push(H, p_new_freq);
		}
	}
	
	retval = codebuch_new(heap_get_element(H, 0), count, frequencies);
	build_codebuch(retval->baum, bitarray_new(), retval);
		
	return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_new_from_structure
 * ------------------------------------------------------------------------ */
CODEBUCH* codebuch_new_from_structure(BITARRAY* p_ba)
{
	unsigned int frequencies[256];
	unsigned int index;
	int i;
	
	index = 0;
	for (i = 0; i < 256; i++)
	{
		unsigned char anzahl_bytes_for_anzahl = ((bitarray_get_bit(p_ba, index + 0) << 1) 
												| (bitarray_get_bit(p_ba, index + 1)) << 1) 
												| bitarray_get_bit(p_ba, index + 2);
		index += 3;
		
		if (anzahl_bytes_for_anzahl == 4)
		{
			frequencies[i] = (bitarray_get_byte(p_ba, index) << 24) 
							| (bitarray_get_byte(p_ba, index + 8) << 16) 
							| (bitarray_get_byte(p_ba, index + 16) << 8) 
							| bitarray_get_byte(p_ba, index + 24);
		}
		else if (anzahl_bytes_for_anzahl == 3)
		{
			frequencies[i] = (bitarray_get_byte(p_ba, index) << 16) 
							| (bitarray_get_byte(p_ba, index + 8) << 8) 
							| bitarray_get_byte(p_ba, index + 16);
		} 
		else if (anzahl_bytes_for_anzahl == 2)
		{
			frequencies[i] = (bitarray_get_byte(p_ba, index) << 8) 
							| bitarray_get_byte(p_ba, index + 8);
		}
		else if (anzahl_bytes_for_anzahl == 1)
		{
			frequencies[i] = bitarray_get_byte(p_ba, index);
		}
		else if (anzahl_bytes_for_anzahl == 0)
		{
			frequencies[i] = 0;
		}
		else
		{
			printf("WTF? oO\n");
		}
		
		index += (anzahl_bytes_for_anzahl * 8);
	}
	
	return codebuch_new_from_frequency(frequencies);
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_free
 * ------------------------------------------------------------------------ */
void codebuch_free(CODEBUCH** pp_cb)
{
	if ((pp_cb != NULL) && (*pp_cb != NULL))
	{
		unsigned int i;
		frequency_free(&((*pp_cb)->baum));
		free((*pp_cb)->baum);
		
		for (i = 0; i < (*pp_cb)->codes_used; i++)
		{
			free((*pp_cb)->codes[i]);
		}
		free((*pp_cb)->codes);
		
		free(*pp_cb);
		*pp_cb = NULL;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_code_for_char
 * ------------------------------------------------------------------------ */
BITARRAY* codebuch_code_for_char(CODEBUCH* p_cb, unsigned char c)
{
	int l = 0;
	int r = (int)(p_cb->codes_used - 1);
	
	if ((p_cb == NULL) || (p_cb->codes == NULL))
	{
		return NULL;
	}
	
	while (l <= r)
	{
		int x = (l + r) / 2;
		unsigned char zeichen = code_get_zeichen((CODE*)p_cb->codes[x]);
		if (c == zeichen)
		{
			BITARRAY* tmp = code_get_code((CODE*)p_cb->codes[x]);
			BITARRAY* retval = bitarray_new();
			unsigned int i;
			
			for (i = 0; i < bitarray_length(tmp); i++)
			{
				bitarray_push(retval, bitarray_get_bit(tmp, i));
			}
			
			return retval;
		}
		else if (c < zeichen)
		{
			r = x - 1;
		}
		else
		{
			l = x + 1;
		}
	}
	
	return NULL;
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_char_for_code
 * ------------------------------------------------------------------------ */
unsigned char codebuch_char_for_code(CODEBUCH* p_cb, BITARRAY* p_code, unsigned int* p_used_bits)
{
	FREQUENCY* tmp;
	unsigned int i;
	
	if ((p_cb == NULL) || (p_cb->codes == NULL) || (p_cb->codes_used <= 0))
	{
		if (p_used_bits != NULL)
		{
			(*p_used_bits) = 0;
		}
		return 0;
	}
	
	if ((p_code == NULL) || (bitarray_length(p_code) <= 0)) {
		if (p_used_bits != NULL)
		{
			(*p_used_bits) = 0;
		}
		return 0;
	}
		
	if (p_used_bits != NULL)
	{
		(*p_used_bits) = 0;
	}
	
	i = 0;
	tmp = p_cb->baum;
	while ((i < bitarray_length(p_code)) && (tmp != NULL))
	{
		if (frequency_is_leaf(tmp))
		{
			return frequency_get_zeichen(tmp);
		}
		else
		{
			if (bitarray_get_bit(p_code, i))
			{
				tmp = frequency_get_right(tmp);
			}
			else
			{
				tmp = frequency_get_left(tmp);
			}
			
			if (p_used_bits != NULL)
			{
				(*p_used_bits)++;
			}
			i++;
		}
	}
	
	if (frequency_is_leaf(tmp))
	{
		return frequency_get_zeichen(tmp);
	}
	
	if (p_used_bits != NULL)
	{
		(*p_used_bits) = 0;
	}
	return 0;
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_structure
 * ------------------------------------------------------------------------ */
BITARRAY* codebuch_structure(CODEBUCH* p_cb)
{
	BITARRAY* retval;
	int i;
	
	if (p_cb == NULL)
	{
		return NULL;
	}
	
	retval = bitarray_new();
	
	for (i = 0; i < 256; i++)
	{
		if (p_cb->frequencies[i] == 0)
		{
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)0);

		}
		else if ((double)p_cb->frequencies[i] >= pow(2, 3 * 8))
		{
			bitarray_push(retval, (BOOL)1);
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)0);
			
			bitarray_push_byte(retval, (p_cb->frequencies[i] >> 24) & 0x000000FF);
			bitarray_push_byte(retval, (p_cb->frequencies[i] >> 16) & 0x000000FF);
			bitarray_push_byte(retval, (p_cb->frequencies[i] >> 8) & 0x000000FF);
			bitarray_push_byte(retval, p_cb->frequencies[i] & 0x000000FF);		
		}
		else if ((double)p_cb->frequencies[i] >= pow(2, 2 * 8))
		{
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)1);
			bitarray_push(retval, (BOOL)1);
			
			bitarray_push_byte(retval, (p_cb->frequencies[i] >> 16) & 0x000000FF);
			bitarray_push_byte(retval, (p_cb->frequencies[i] >> 8) & 0x000000FF);
			bitarray_push_byte(retval, p_cb->frequencies[i] & 0x000000FF);
		}
		else if ((double)p_cb->frequencies[i] >= pow(2, 1 * 8))
		{
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)1);
			bitarray_push(retval, (BOOL)0);
			
			bitarray_push_byte(retval, (p_cb->frequencies[i] >> 8) & 0x000000FF);
			bitarray_push_byte(retval, p_cb->frequencies[i] & 0x000000FF);
		}
		else if ((double)p_cb->frequencies[i] >= pow(2, 0 * 8))
		{
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)0);
			bitarray_push(retval, (BOOL)1);
			
			bitarray_push_byte(retval, p_cb->frequencies[i] & 0x000000FF);
		}
		else
		{
			printf("WTF? oO\n");
		}
	}
	
	return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: codes_equal
 * ------------------------------------------------------------------------ */
static BOOL codes_equal(CODEBUCH* p_cb1, CODEBUCH* p_cb2)
{
	if ((p_cb1 == NULL) && (p_cb2 == NULL))
	{
		return TRUE;
	}
	else if (p_cb1 == NULL)
	{
		return FALSE;
	}
	else if (p_cb2 == NULL)
	{
		return FALSE;
	}
	else if (p_cb1->codes_used != p_cb2->codes_used)
	{
		return FALSE;
	}
	else
	{
		unsigned int i;
		for (i = 0; i < p_cb1->codes_used; i++)
		{
			if (!code_equals(p_cb1->codes[i], p_cb2->codes[i]))
			{
				return FALSE;
			}
		}
	}
	
	return TRUE;
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_equals
 * ------------------------------------------------------------------------ */
BOOL codebuch_equals(CODEBUCH* p_cb1, CODEBUCH* p_cb2)
{
	if ((p_cb1 == NULL) && (p_cb2 == NULL))
	{
		return TRUE;
	}
	else if (p_cb1 == NULL)
	{
		return FALSE;
	}
	else if (p_cb2 == NULL)
	{
		return FALSE;
	}
	else if (!frequency_equals(p_cb1->baum, p_cb2->baum))
	{
		return FALSE;
	}
	else if (!codes_equal(p_cb1, p_cb2))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_get_baum
 * ------------------------------------------------------------------------ */
FREQUENCY* codebuch_get_baum(CODEBUCH* p_cb)
{
	if (p_cb == NULL)
	{
		return NULL;
	}
	return p_cb->baum;
}


/* ---------------------------------------------------------------------------
 * Funktion: codebuch_get_max_code_length
 * ------------------------------------------------------------------------ */
unsigned char codebuch_get_max_code_length(CODEBUCH* p_cb)
{
	if (p_cb == NULL)
	{
		return 0;
	}
	return p_cb->max_code_length;
}
