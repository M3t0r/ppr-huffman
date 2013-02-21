/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "heap.h"
#include "common.h"


/*****************************************************************************
 * Konstanten
 *****************************************************************************/
/**
 * Schrittweite, mit der der Heap vergroessert wird.
 */
 #define STEPS	10


/*****************************************************************************
 * Strukturdefinitionen
 *****************************************************************************/
/**
 * Struktur fuer den Heap.
 */
 struct _HEAP 
{
    /* Groesse des Heaps */
    int size;
	
	/* Anzahl der genutzten Elemente innerhalb des Heaps */
    int used;
	
	/* Funktionszeiger auf eine Funktion zum vergleichen zweier Heap-Elemente */ 
    CMP_FCT comp;
	
	/* Pointer auf die Elemente des Heaps */
    void** elements;
};


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Vergroessert den Heap um STEP Elemente.
 * @param p_heap Der zu vergroessernde Heap.
 */
static void grow(HEAP* p_heap);

/**
 * Verkleinert den Heap.
 * @param p_heap Der zu verkleinernde Heap.
 */
static void shrink(HEAP* p_heap);


/*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
/* ---------------------------------------------------------------------------
 * Funktion: heap_new
 * ------------------------------------------------------------------------ */
 HEAP* heap_new(CMP_FCT cmp_f) 
{
    HEAP* retval = (HEAP*)malloc(sizeof(HEAP));
    ASSERT_ALLOC(retval);

    retval->elements = malloc((STEPS * sizeof(void*)) + 1);
    ASSERT_ALLOC(retval->elements);

    retval->elements[0] = NULL;
    
    retval->comp = cmp_f;
    retval->size = STEPS;
    retval->used = 0;

    return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_free
 * ------------------------------------------------------------------------ */
void heap_free(HEAP** pp_heap)
{
	if ((pp_heap != NULL) && (*pp_heap != NULL) && ((*pp_heap)->elements != NULL)) 
	{
    	free((*pp_heap)->elements);
    	free(*pp_heap);
    	*pp_heap = NULL;
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: grow
 * ------------------------------------------------------------------------ */
static void grow(HEAP* p_heap) 
{    
    if ((p_heap != NULL) && (p_heap->elements != NULL) && (p_heap->used >= p_heap->size)) 
    {
    	p_heap->elements = realloc(p_heap->elements, ((p_heap->size + STEPS)*  sizeof(void*)) + 1);
    	ASSERT_ALLOC(p_heap->elements);
    	p_heap->size += STEPS;
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: shrink
 * ------------------------------------------------------------------------ */
static void shrink(HEAP* p_heap) 
{
	if ((p_heap != NULL) && (p_heap->elements != NULL) && ((p_heap->size - STEPS) > p_heap->used)) 
	{
    	p_heap->elements = realloc(p_heap->elements, ((p_heap->size - STEPS)*  sizeof(void*)) + 1);
    	ASSERT_ALLOC(p_heap->elements);
    	p_heap->size -= STEPS;
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_push
 * ------------------------------------------------------------------------ */
void heap_push(HEAP* p_heap, void* element) 
{	
    if ((p_heap != NULL) && (p_heap->elements != NULL)) 
    {
    	int i = 0;

		if (p_heap->size <= p_heap->used) 
		{
			grow(p_heap);
		}
		
		p_heap->used++;
		
		for (i = p_heap->used; (*p_heap->comp)((p_heap->elements[i / 2]), element) > 0; i /= 2) 
		{
			p_heap->elements[i] = p_heap->elements[i / 2];
		}
		
		p_heap->elements[i] = element;
	}
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_pop
 * ------------------------------------------------------------------------ */
void* heap_pop(HEAP* p_heap) 
{
    void* retval = NULL;
    
    if ((p_heap != NULL) && (p_heap->elements != NULL) && (p_heap->used > 0)) 
    {
    	int i = 0;
    	int child = 0;
    	void* last_element = p_heap->elements[p_heap->used];
    	p_heap->used--;
		retval = p_heap->elements[1];
	
		for (i = 1; (i*  2) <= p_heap->used; i = child) 
		{
			child = i*  2;
			if ((child != p_heap->used) && ((*p_heap->comp)(p_heap->elements[child + 1], p_heap->elements[child]) < 0)) 
			{
				child++;
			}
	
			if ((*p_heap->comp)(last_element, p_heap->elements[child]) > 0) 
			{
				p_heap->elements[i] = p_heap->elements[child];
			} 
			else 
			{
				break;
			}
		}
		p_heap->elements[i] = last_element;
		
		if ((p_heap->size - STEPS) > p_heap->used) 
		{
			shrink(p_heap);
		}
    }
    
    return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_get_size
 * ------------------------------------------------------------------------ */
int heap_get_size(HEAP* p_heap) 
{    
    if (p_heap != NULL) 
    {
        return p_heap->used;
    }
    
    return -1;
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_contains
 * ------------------------------------------------------------------------ */
int heap_contains(HEAP* p_heap, void* element, CMP_FCT cmp_f)
{	
	if ((p_heap != NULL) && (p_heap->elements != NULL)) 
	{
		int i = 1;
		for (i = 1; i <= p_heap->used; i++) 
		{
			if (cmp_f(p_heap->elements[i], element) == 0) 
			{
				return i;
			}
		}
	}
	return -1;
}


/* ---------------------------------------------------------------------------
 * Funktion: heap_get_element
 * ------------------------------------------------------------------------ */
void* heap_get_element(HEAP* p_heap, int index) 
{
	index++;
	if ((p_heap != NULL) && (p_heap->elements != NULL) && (index > 0) && (index <= p_heap->used)) 
	{
		return p_heap->elements[index];
	}
	
	return NULL;
}
