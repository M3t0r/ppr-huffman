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
#include "frequency.h"


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
 * @param frequencies Die Anzahlen aller Zeichen.
 * @return Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_frequency(unsigned int frequencies[256]);

/**
 * Erstellt eine neues Codebuch aus einem Bitarray.
 * @param p_ba Das Bitarray, aus dem das Codebuch erstellt werden soll.
 * @return Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_structure(BITARRAY* p_ba);

/**
 * Loescht ein Codebuch.
 * @param pp_cb Ein Zeiger auf das freizugebende Codebuch.
 */
extern void codebuch_free(CODEBUCH** pp_cb);

/**
 * Gibt den Code zu einem Zeichen zurück.
 * @param p_cb Das zu durchsuchende Codebuch.
 * @param c Das zu suchende Zeichen.
 * @return Der Code zu dem Zeichen als Bitarray oder NULL im Fehlerfall.
 */
extern BITARRAY* codebuch_code_for_char(CODEBUCH* p_cb, unsigned char c);

/**
 * Gibt das Zeichen zu einem Code zurück.
 * @param p_cb Das Codebuch.
 * @param p_code Der zu suchende Code als Bitarray.
 * @param p_used_bits Wenn != NULL, wird hier die Anzahl der benutzten 
 *                    Bits gespeichert.
 * @return Das Zeichen zu dem Code oder 0 im Fehlerfall. Bei 0 kann mit 
 *         codebuch_last_char_was_error geprueft werden, ob ein Fehler 
 *         aufgetreten ist oder ob das Byte 0 dekodiert wurde.
 */
extern unsigned char codebuch_char_for_code(CODEBUCH* p_cb, BITARRAY* p_code,
                                            unsigned int* p_used_bits);

/**
 * Speichert ein Codebuch als Bitarray.
 * @param p_cb Das abzuspeichernde Codebuch.
 * @return Das Codebuch als Bitarray.
 */
extern BITARRAY* codebuch_structure(CODEBUCH* p_cb);

/**
 * Prueft, ob der zuletzt von codebuch_char_for_code zurückgegebene char ein Fehler war.
 * @param p_cb Das Codebuch.
 * @return TRUE, wenn der letzte zurückgegebene char ein Fehler war, sonst FALSE.
 */
extern BOOL codebuch_last_char_was_error(CODEBUCH* p_cb);

/**
 * Prueft, ob 2 Codebuecher gleich sind.
 * @param p_cb1 Das eine Codebuch.
 * @param p_cb2 Das andere Codebuch.
 * @return BOOL TRUE, falls cb1 und cb2 gleich sind, FALSE sonst.
 */
extern BOOL codebuch_equals(CODEBUCH* p_cb1, CODEBUCH* p_cb2);

/**
 * Liefert den Baum eines Codebuchs.
 * @param p_cb Codebuch, dessen Baum zurueckgegeben werden soll.
 * @return Liefert den Baum eines Codebuchs.
 */
extern FREQUENCY* codebuch_get_baum(CODEBUCH* p_cb);

#endif
