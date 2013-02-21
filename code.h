/**
 * @file
 * Dieses Modul stellt einen Typ CODE zur Verfuegung, um ein Zeichen
 * und seine Codierung nach Hufmann abspeichern zu koennen.
 * 
 * File:   code.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */
#ifndef _CODE_H
#define _CODE_H

/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "bitarray.h"
#include "common.h"


/*****************************************************************************
 * Typdefinitionen
 *****************************************************************************/
/**
 * Typdefinition eines Codes.
 */
typedef struct _CODE CODE;


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Erstellt einen neuen Code.
 * @param z Das Zeichen des neuen Codes.
 * @param p_bitarray Das Bitarray (Code) des neuen Codes.
 * @return Der neue Code oder NULL im Fehlerfall.
 */
extern CODE* code_new(unsigned char z, BITARRAY* p_bitarray);

/**
 * Gibt den Code frei.
 * @param pp_code Ein Zeiger auf den freizugebenden Code.
 */
extern void code_free(CODE** pp_code);

/**
 * Gibt das Zeichen des Codes zurück.
 * @param p_code Der Code.
 * @return Das Zeichen des Codes.
 */
extern unsigned char code_get_zeichen(CODE* p_code);

/**
 * Gibt das Bitarray (Code) des Codes zurück.
 * @param p_code Der Code.
 * @return Das Bitarray (Code) des Codes.
 */
extern BITARRAY* code_get_code(CODE* p_code);

/**
 * Vergleicht 2 Codes anhand ihres Zeichens.
 * @param p_code1 Der eine Code.
 * @param p_code2 Der andere Code.
 * @return 1 wenn p_code1 > p_code2, 0 wenn beide Codes gleich sind, -1 wenn p_code1 < p_code2.
 */
extern int cmp_codes_zeichen(CODE* p_code1, CODE* p_code2);

/**
 * Prueft, ob 2 Codes gleich sind.
 * @param c1 Der eine Code.
 * @param c2 Der andere Code.
 * @return TRUE, falls c1 und c2 gleich sind, FALSE sonst.
 */
extern BOOL code_equals(CODE* c1, CODE* c2);

#endif
