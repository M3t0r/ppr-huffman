/**
 * @file
 * Dieses Modul stellt Funktionen zum Verwalten einer flexiblen Anzahl Bits
 * zur Verfuegung.
 * 
 * File:   bitarray.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */
#ifndef _BITARRAY_H
#define _BITARRAY_H

/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "common.h"


/*****************************************************************************
 * Typdefintionen
 *****************************************************************************/
/**
 * Definiert den Typ BITARRAY.
 */
typedef struct {
    /* Folge von Bytes */
    BYTE *data;
	
	/* Groesse des Vektors data in bit */
    unsigned int capacity;
	
	/* Anzahl der Bits innerhalb des Bitarrays */
    unsigned int length;
} BITARRAY;

/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Erstellt ein neues BITARRAY mit einer intialen Groesse von einem Byte.
 * @return Das neue, leere Bitarray.
 */
BITARRAY *bitarray_new();

/**
 * Gibt ein Bitarray inklusive dem reservierten Speicher auf dem Heap wieder
 * frei.
 */
void bitarray_free(BITARRAY **ba);

/**
 * Fuegt ein Bit hinten an das Bitarray an.
 * @param ba Bitarray, das erweitert werden soll.
 * @param d Einzufuegendes Bit. TRUE entspricht 1, FALSE ist 0.
 */
void bitarray_push(BITARRAY *ba, BOOL d);

/**
 * Fuegt ein Byte hinten an das Bitarray an.
 * @param ba Bitarray, das erweitert werden soll.
 * @param d Einzufuegendes Byte.
 */
void bitarray_push_byte(BITARRAY *ba, BYTE d);

/**
 * Holt und entfernt das letzte Bit aus dem Bitarray.
 * @param ba Bitarray, aus dem gelesen werden soll.
 * @return Gibt das gelesene Bit zurueck. TRUE entspricht 1, FALSE ist 0.
 */
BOOL bitarray_pop(BITARRAY *ba);

/**
 * Gibt die Anzahl der im dem Bitarray enthaltenen Bits zurueck.
 * @param ba Bitarray, dessen Laenge ermittelt werden soll.
 * @return Die Anzahl der im Bitarray enthaltenen Bits.
 */
unsigned int bitarray_length(BITARRAY *ba);

/**
 * Gibt das Bit an der Position index zurueck.
 * @param ba Das Bitarray, aus dem gelesen werden soll.
 * @param index Gibt an, das wie vielte Bit gelesen werden soll.
 * @return Das gelesene Bit. TRUE entspricht 1, FALSE ist 0.
 */
BOOL bitarray_get_bit(BITARRAY *ba, unsigned int index);

/**
 * Liefert ausgehend vom Index das naechste Byte aus dem Bitarray.
 * @param ba Bitarray, aus dem gelesen werden soll.
 * @param index Position, des ersten zu lesenden Bits.
 * @return Das gelesene Byte.
 */
BYTE bitarray_get_byte(BITARRAY *ba, unsigned int index);

/**
 * Fuegt zwei Bitarrays zusammen. ba2 wird dabei hinter ba1
 * eingefuegt.
 * @param ba1 Der vordere Teil des neuen Bitarrays. Dient auch gleichzeitig 
 *            als Pointer auf das zusammengefuegte Array.
 * @param ba2 Der hintere Teil des neuen Bitarrays.
 */
void bitarray_merge(BITARRAY *ba1, BITARRAY *ba2);

/**
 * Entfernt die vordersten Bits aus dem Bitarray.
 * @param ba Bitarray, dessen vorder Teil entfernt werden soll.
 * @param length Anzahl der zu entfernenden Bits.
 */
void bitarray_remove_front(BITARRAY *ba, unsigned int length);

/**
 * Gibt den Inhalt des Bitarrays als Bitfolge in einer Datei aus.
 * @param ba Bitarray, das ausgegeben werden soll.
 * @param stream Datei, in die das Bitarray geschrieben werden soll.
 * @param print_prefix Gibt an, ob das Prefix 0b ausgegeben werden soll.
 */
void bitarray_print_adv(BITARRAY *ba, FILE *stream, BOOL print_prefix);

/**
 * Gibt ein Bitarray als Bitfolge auf dem Bilsdschirm aus.
 * @param ba Bitarray, das ausgegeben werden soll.
 */
void bitarray_print(BITARRAY *ba);

/**
 * Gibt zurueck, ob die beiden Bitarrays gleich sind.
 * @param ba1 Das eine Bitarray.
 * @param ba2 Das andere Bitarray.
 * @return TRUE falls beide Bitarrays gleich sind, FALSE sonst.
 */
BOOL bitarray_equals(BITARRAY *ba1, BITARRAY *ba2);

#endif
