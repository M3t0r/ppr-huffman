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
    BYTE *data;
    unsigned int capacity;
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
 * Fuegt ein Bit HINTEN an das Bitarray an.
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
 * Holt und entfernt das vorderste Bit aus dem Bitarray.
 * @param ba Bitarray, aus dem gelesen werden soll.
 * @return Gibt das gelesene Bit zurueck. TRUE entspricht 1, FALSE ist 0.
 */
BOOL bitarray_pop(BITARRAY *ba);

/**
 * Gibt die Anzahl der im dem Bitarray enthaltenen Bits zurueck.
 * @param ba Bitarray, dessen Laenge ermittelt werden soll.
 * @return Die Anzahl der im Bitarray enthaltenen Bits.
 */
int bitarray_length(BITARRAY *ba);

/**
 * Gibt das Bit an der Position index zurueck.
 * returns the bit with the bit-based index
 * @param ba Das Bitarray, aus dem gelesen werden soll.
 * @param index Gibt an, das wie vielte Bit gelesen werden soll.
 * @return Das gelesene Bit. TRUE entspricht 1, FALSE ist 0.
 */
BOOL bitarray_get_bit(BITARRAY *ba, int index);

/**
 * Liefert ausgehend vom Index das naechste Byte aus dem Bitarray.
 * @param ba Bitarray, aus dem gelesen werden soll.
 * @param index Position, des ersten zu lesenden Bits.
 * @return Das gelesene Byte.
 */
BYTE bitarray_get_byte(BITARRAY *ba, int index);



#endif