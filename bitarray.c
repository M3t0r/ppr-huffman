/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "bitarray.h"
#include <string.h>


/*****************************************************************************
 * Definitionen von Konstanten
 *****************************************************************************/
/**
 * Schrittweite mit der Bitarray vergroessert bzw. verkleinert werden. Die
 * Angabe erfolgt in Bits.
 */
 #define STEPS (4*8)


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
 /**
  * Prueft, ob das Bitarray noch gross genug ist, um ein weiteres Bit 
  * aufzunehmen. Falls dies nicht der Falls ist, wird das Bitarray um STEPS
  * vergroessert.
  * @param ba Zu vergroesserndes Bitarray.
  */
 static void grow(BITARRAY *ba);
 
 
 /**
  * Prueft, ob das Bitarray verkleinert werden kann. Falls dies der Fall ist, 
  * wird das Bitarray um STEPS verkleinert.
  * @param ba Zu verkleinerndes Bitarray.
  */
 static void shrink(BITARRAY *ba);
 
 
 /*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
/* ---------------------------------------------------------------------------
 * Funktion: bitarray_new
 * ------------------------------------------------------------------------ */
BITARRAY *bitarray_new()
{
	BITARRAY* retval 	= malloc(sizeof(BITARRAY));
	ASSERT_ALLOC(retval);
	retval->data 		= NULL;
	retval->capacity 	= 0;
	retval->length 		= 0;
	grow(retval);
	return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_free
 * ------------------------------------------------------------------------ */
void bitarray_free(BITARRAY **ba)
{
	if ((ba != NULL) && (*ba != NULL))
	{
		free((*ba)->data);
		free(*ba);
		*ba = NULL;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: grow
 * ------------------------------------------------------------------------ */
static void grow(BITARRAY *ba)
{
	if ((ba != NULL) && (ba->length >= ba->capacity))
	{
		ba->data = realloc(ba->data, (ba->capacity + STEPS) * sizeof(BYTE));
		ASSERT_ALLOC(ba->data);
		memset(ba->data + (ba->capacity / 8), 0, STEPS);
		ba->capacity += STEPS;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: shrink
 * ------------------------------------------------------------------------ */
/* tuts aufm linux irgendwie nicht Oo */
static void shrink(BITARRAY *ba)
{
#ifndef __linux__
	if ((ba != NULL) && (ba->length <= (ba->capacity - STEPS)))
	{
		ba->data = realloc(ba->data, (ba->capacity - STEPS) * sizeof(BYTE));
		ASSERT_ALLOC(ba->data);
		ba->capacity -= STEPS;
	}
#endif
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_push
 * ------------------------------------------------------------------------ */
void bitarray_push(BITARRAY *ba, BOOL d)
{
	if (ba != NULL)
	{
		unsigned char mask = (unsigned char)0x01 & d;
		grow(ba);
		ba->data[ba->length / 8] |= mask << (7 - (ba->length % 8));
		ba->length++;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_push_byte
 * ------------------------------------------------------------------------ */
void bitarray_push_byte(BITARRAY* ba, BYTE d)
{
	if (ba != NULL)
	{
		char i;
		unsigned char mask = 0x80;
		for (i = 0; i < 8; i++)
		{
			bitarray_push(ba, ((d & (mask >> i)) ? TRUE : FALSE));
		}
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_pop
 * ------------------------------------------------------------------------ */
BOOL bitarray_pop(BITARRAY *ba)
{
	BOOL retval = 0;
	
	if ((ba != NULL) && (ba->length > 0)) 
	{
		unsigned char mask = 0x80;
		BYTE byte = ba->data[(--ba->length) / 8];
		retval = byte & (mask >> (ba->length % 8));
		shrink(ba);
	}
	
	return ((retval == 0) ? FALSE : TRUE);
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_length
 * ------------------------------------------------------------------------ */
unsigned int bitarray_length(BITARRAY *ba)
{
	if (ba != NULL)
	{
		return ba->length;
	}
	return 0;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_get_bit
 * ------------------------------------------------------------------------ */
BOOL bitarray_get_bit(BITARRAY *ba, unsigned int index)
{
	BOOL retval = 0;
	
	if ((ba != NULL) && (index < ba->length))
	{
		unsigned char mask = 0x80;
		BYTE byte = ba->data[index / 8];
		retval = byte & (mask >> (index % 8));
	}
	
	return ((retval == 0) ? FALSE : TRUE);
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_get_byte
 * ------------------------------------------------------------------------ */
BYTE bitarray_get_byte(BITARRAY *ba, unsigned int index)
{
	BYTE retval = 0;
	if ((ba != NULL) && (index + 8 <= ba->length))
	{
		int i;
		for (i = 0; i < 8; i++)
		{
			retval = (retval << 1) | bitarray_get_bit(ba, index++);
		}
	}
	return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_merge
 * ------------------------------------------------------------------------ */
void bitarray_merge(BITARRAY *ba1, BITARRAY *ba2)
{
	if ((ba1 != NULL) && (ba2 != NULL))
	{
		unsigned int i;
		for(i = 0; i < bitarray_length(ba2); i++)
		{
			bitarray_push(ba1, bitarray_get_bit(ba2, i));
		}
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_remove_front
 * ------------------------------------------------------------------------ */
void bitarray_remove_front(BITARRAY *ba, unsigned int length)
{
	if ((ba != NULL) && (length <= ba->length))
	{
		BITARRAY *tmp = bitarray_new();
		unsigned int i;
		
		for (i = length; i < ba->length; i++)
		{
			bitarray_push(tmp, bitarray_get_bit(ba, i));
		}
		
		free(ba->data);
		ba->data 		= tmp->data;
		ba->length 		= tmp->length;
		ba->capacity 	= tmp->capacity;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_equals
 * ------------------------------------------------------------------------ */
BOOL bitarray_equals(BITARRAY *ba1, BITARRAY *ba2)
{
	if (ba1 == NULL && ba2 == NULL)
	{
		return TRUE;
	}
	else if (ba1 == NULL)
	{
		return FALSE;
	}	
	else if (ba2 == NULL)
	{
		return FALSE;
	}
	else if (ba1->length != ba2->length)
	{
		return FALSE;
	}
	else
	{
	    unsigned int i;
	    for (i = 0; i < ba1->length; i++)
	    {
	        if (bitarray_get_bit(ba1, i) != bitarray_get_bit(ba2, i))
	        {
	            return FALSE;
	        }
	    }
	}
	return TRUE;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_print_adv
 * ------------------------------------------------------------------------ */
void bitarray_print_adv(BITARRAY *ba, FILE *stream, BOOL print_prefix)
{
    unsigned int i;
    
    if (print_prefix)
    {
        fprintf(stream, "0b");
    }
    
    for (i = 0; i < bitarray_length(ba); i++)
    {
        fprintf(stream, bitarray_get_bit(ba, i) ? "1" : "0");
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: bitarray_print
 * ------------------------------------------------------------------------ */
void bitarray_print(BITARRAY *ba)
{
    bitarray_print_adv(ba, stdout, TRUE);
}
