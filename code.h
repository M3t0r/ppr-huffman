#ifndef _CODE_H
#define _CODE_H

#include "bitarray.h"
#include "common.h"

/**
 * Typdefinition eines Codes.
 */
typedef struct _CODE CODE;

/**
 * Erstellt einen neuen Code.
 * @param z unsigned char Das Zeichen des neuen Codes.
 * @param p_bitarray BITARRAY* Das Bitarray (Code) des neuen Codes.
 * @return CODE* Der neue Code oder NULL im Fehlerfall.
 */
extern CODE* code_new(unsigned char z, BITARRAY* p_bitarray);

/**
 * Gibt das Zeichen des Codes zurück.
 * @param p_code CODE* Der Code.
 * @return unsigned char Das Zeichen des Codes.
 */
extern unsigned char code_get_zeichen(CODE* p_code);

/**
 * Gibt das Bitarray (Code) des Codes zurück.
 * @param p_code CODE* Der Code.
 * @return BITARRAY* Das Bitarray (Code) des Codes.
 */
extern BITARRAY* code_get_code(CODE* p_code);

/**
 * Vergleicht 2 Codes anhand ihres Zeichens.
 * @param p_code1 CODE* Der eine Code.
 * @param p_code2 CODE* Der andere Code.
 * @return int 1 wenn p_code1 > p_code2, 0 wenn beide Codes gleich sind, -1 wenn p_code1 < p_code2.
 */
extern int cmp_codes_zeichen(CODE* p_code1, CODE* p_code2);

/**
 * Prüft, ob 2 Codes gleich sind.
 * @param c1 CODE* Der eine Code.
 * @param c2 CODE* Der andere Code.
 * @return BOOL TRUE, falls c1 und c2 gleich sind, FALSE sonst.
 */
extern BOOL code_equals(CODE* c1, CODE* c2);

#endif
