/**
 * @file
 * Dieser Header definiert einen Heap und die hierfuer benoetigten
 * Funktionen.
 * 
 * File:   heap.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */

#ifndef _HEAP_H
#define _HEAP_H

/*****************************************************************************
 * Typdefinitionen
 *****************************************************************************/
/**
 * Prototyp für eine Vergleichs-Funktion.
 */
typedef int (*CMP_FCT)(void* , void* );

/**
 * Typdefinition eines Heaps.
 */
typedef struct _HEAP HEAP;


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Erstellt einen neuen Heap mit der gegebenen Vergleichsfunktion.
 * @param cmp_f CMP_FCT Die Vergleichsfunktion.
 * @return HEAP* Ein pointer auf den neuen Heap.
 */
extern HEAP* heap_new(CMP_FCT cmp_f);

/**
 * Löscht den gegebenen Heap.
 * @param p_heap HEAP** Der zu löschende Heap.
 */
extern void heap_free(HEAP** pp_heap);

/**
 * Pusht das gegebene Element auf den Heap.
 * @param p_heap HEAP* Der Heap.
 * @param element void* Das zu pushende Element.
 */
extern void heap_push(HEAP* p_heap, void* element);

/**
 * Popt das minimale Element aus dem gegebenen Heap.
 * @param p_heap HEAP* Der Heap.
 * @return void* NULL wenn kein Element mehr vorhanden, ansonsten das minimale Element.
 */
extern void* heap_pop(HEAP* p_heap);

/**
 * Gibt die Anzahl der Elemente im Heap zurück.
 * @param p_heap HEAP* Der Heap.
 * @return int Die Anzahl der Elemente im Heap.
 */
extern int heap_get_size(HEAP* p_heap);

/**
 * Gibt das Element am gewünschten Index zurück.
 * @param p_heap HEAP* Der Heap.
 * @param index int Der gewünschte Index (0-basiert).
 * @return void* NULL, falls der Index invalide war, das gewünschte Element sonst.
 */
extern void* heap_get_element(HEAP* p_heap, int index);

#endif
