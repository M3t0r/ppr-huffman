#ifndef _BIT_ACCESS_H
#define _BIT_ACCESS_H

#include "common.h"

/**
 * Gibt den Status des angegebenen Bits zurück.
 * @param ptr Ein Zeiger auf das Byte-Array.
 * @param index Der Index des Bits.
 * @return TRUE wenn das Bit gesetzt ist, FALSE sonst.
 */
BOOL get_bit(BYTE *ptr, int index);

/**
 * Setzt das angegebene Bit in dem Byte-Array auf den angegebenen Wert.
 * @param ptr Ein Zeiger auf das Byte-Array.
 * @param index Der zu setzende Index.
 * @param value Der neue Wert für das Bit.
 */
void set_bit(BYTE *ptr, int index, BOOL value);

/**
 * Gibt das angegebene Byte-Array aus.
 * @param ptr Ein Zeiger auf das Byte-Array.
 * @param length Wie viele Bits ausgegeben werden sollen. 
 */
void print_bytes(BYTE *ptr, int length);

#endif
