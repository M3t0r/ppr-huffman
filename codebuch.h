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
 * @param ba BITARRAY* Das Bitarray.
 * @return CODEBUCH* Das neue Codebuch oder NULL im Fehlerfall.
 */
extern CODEBUCH* codebuch_new_from_structur(BITARRAY* ba);

/**
 * Gibt das Codebuch frei.
 * @param cb CODEBUCH** Das freizugebende Codebuch.
 */
extern void codebuch_free(CODEBUCH** cb);

/**
 * Gibt den Code zu einem Zeichen zurück.
 * @param cb CODEBUCH* Das zu durchsuchende Codebuch.
 * @param c unsigned char Das zu suchende Zeichen.
 * @return BITARRAY* Der Code zu dem Zeichen als Bitarray oder NULL im Fehlerfall.
 */
extern BITARRAY* codebuch_code_for_char(CODEBUCH* cb, unsigned char c);

/**
 * Gibt das Zeichen zu einem Code zurück.
 * @param cb CODEBUCH* Das Codebuch.
 * @param c BITARRAY* Der zu suchende Code als Bitarray.
 * @param used_bits unsigned int* Wenn != NULL, wird hier die Anzahl der benutzten Bits gespeichert.
 * @return unsigned char Das Zeichen zu dem Code oder blablabla im Fehlerfall.
 */
extern unsigned char codebuch_char_for_code(CODEBUCH* cb, BITARRAY* c, unsigned int* used_bits);

/**
 * Speichert ein Codebuch als Bitarray.
 * @param cb CODEBUCH* Das abzuspeichernde Codebuch.
 * @return BITARRAY* Das Codebuch als Bitarray.
 */
extern BITARRAY* codebuch_structure(CODEBUCH* cb);

#ifdef TEST
/**
 * Prüft, ob 2 Codebücher gleich sind.
 * @param cb1 CODEBUCH* Das eine Codebuch.
 * @param cb2 CODEBUCH* Das andere Codebuch.
 * @return BOOL TRUE, falls cb1 und cb2 gleich sind, FALSE sonst.
 */
extern BOOL codebuch_equals(CODEBUCH* cb1, CODEBUCH* cb2);

/**
 * Gibt die Größe des Codebuchs zurück.
 * @param cb CODEBUCH* Das Codebuch.
 * @return unsigned int Die Größe des Codebuchs.
 */
extern unsigned int codebuch_size(CODEBUCH* cb);
#endif

#endif
