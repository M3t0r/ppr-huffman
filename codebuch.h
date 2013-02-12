#ifndef _CODEBUCH_H
#define _CODEBUCH_H

#include "my_bitfile.h"

/**
 * Typdefinition eines Codebuchs.
 */
typedef struct _CODEBUCH CODEBUCH;

/**
 * Erstellt ein neues Codebuch.
 * @param f unsigned int Die Anzahlen aller Zeichen.
 * @return CODEBUCH* Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_frequency(unsigned int f[256]);

/**
 * Erstellt eine neues Codebuch aus einem Bitarray.
 * @param p_ba BITARRAY* Das Bitarray.
 * @return CODEBUCH* Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_structur(BITARRAY* p_ba);

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
 * @return unsigned char Das Zeichen zu dem Code oder blablabla im Fehlerfall.
 */
extern unsigned char codebuch_char_for_code(CODEBUCH* p_cb, BITARRAY* p_code, unsigned int* p_used_bits);

/**
 * Speichert ein Codebuch als Bitarray.
 * @param p_cb CODEBUCH* Das abzuspeichernde Codebuch.
 * @return BITARRAY* Das Codebuch als Bitarray.
 */
extern BITARRAY* codebuch_structure(CODEBUCH* p_cb);

#ifdef TEST
/**
 * Prüft, ob 2 Codebücher gleich sind.
 * @param p_cb1 CODEBUCH* Das eine Codebuch.
 * @param p_cb2 CODEBUCH* Das andere Codebuch.
 * @return BOOL TRUE, falls cb1 und cb2 gleich sind, FALSE sonst.
 */
extern BOOL codebuch_equals(CODEBUCH* p_cb1, CODEBUCH* p_cb2);

/**
 * Gibt die Größe des Codebuchs zurück.
 * @param p_cb CODEBUCH* Das Codebuch.
 * @return unsigned int Die Größe des Codebuchs.
 */
extern unsigned int codebuch_size(CODEBUCH* p_cb);
#endif

#endif
