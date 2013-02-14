/**
 * @file
 * Dieses Modul stellt einen Typ Codebuch zur Verfügung. Dieses wird für eine
 * definierte Menge von Zeichen entsprechend des Huffmann-Algorithmus aufgebaut.
 * 
 * File:   codebuch.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */

#ifndef _CODEBUCH_H
#define _CODEBUCH_H

/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "bitarray.h"
#include "common.h"


/*****************************************************************************
 * Typdefinitionen
 *****************************************************************************/
/**
 * Typdefinition eines Codebuchs.
 */
typedef struct _CODEBUCH CODEBUCH;



/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Erstellt ein neues Codebuch.
 * @param frequencies unsigned int[256] Die Anzahlen aller Zeichen.
 * @return CODEBUCH* Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_frequency(unsigned int frequencies[256]);

/**
 * Erstellt eine neues Codebuch aus einem Bitarray.
 * @param p_ba BITARRAY* Das Bitarray.
 * @return CODEBUCH* Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_structure(BITARRAY* p_ba);

/**
 * Gibt das Codebuch frei.
 * @param pp_cb CODEBUCH** Ein Zeiger auf das freizugebende Codebuch.
 */
extern void codebuch_free(CODEBUCH** pp_cb);

/**
 * Gibt den Code zu einem Zeichen zurück.
 * @param p_cb CODEBUCH* Das zu durchsuchende Codebuch.
 * @param c unsigned char Das zu suchende Zeichen.
 * @return BITARRAY* Der Code zu dem Zeichen als Bitarray oder NULL im Fehlerfall.
 */
extern BITARRAY* codebuch_code_for_char(CODEBUCH* p_cb, unsigned char c);

/**
 * Gibt das Zeichen zu einem Code zurück.
 * @param p_cb CODEBUCH* Das Codebuch.
 * @param p_code BITARRAY* Der zu suchende Code als Bitarray.
 * @param p_used_bits unsigned int* Wenn != NULL, wird hier die Anzahl der benutzten Bits gespeichert.
 * @return unsigned char Das Zeichen zu dem Code oder 0 im Fehlerfall. (Bei 0 mit codebuch_last_char_was_error auf Fehler prüfen)
 */
extern unsigned char codebuch_char_for_code(CODEBUCH* p_cb, BITARRAY* p_code, unsigned int* p_used_bits);

/**
 * Speichert ein Codebuch als Bitarray.
 * @param p_cb CODEBUCH* Das abzuspeichernde Codebuch.
 * @return BITARRAY* Das Codebuch als Bitarray.
 */
extern BITARRAY* codebuch_structure(CODEBUCH* p_cb);

/**
 * Prüft, ob der zuletzt von codebuch_char_for_code zurückgegebene char ein Fehler war.
 * @param p_cb CODEBUCH* Das Codebuch.
 * @return BOOL TRUE, wenn der letzte zurückgegebene char ein Fehler war, FALSE sonst.
 */
extern BOOL codebuch_last_char_was_error(CODEBUCH* p_cb);

/**
 * Prüft, ob 2 Codebücher gleich sind.
 * @param p_cb1 CODEBUCH* Das eine Codebuch.
 * @param p_cb2 CODEBUCH* Das andere Codebuch.
 * @return BOOL TRUE, falls cb1 und cb2 gleich sind, FALSE sonst.
 */
extern BOOL codebuch_equals(CODEBUCH* p_cb1, CODEBUCH* p_cb2);

#endif
