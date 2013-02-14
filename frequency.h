/**
 * @file
 * Dieses Modul definiert einen Typ FREQUENCY zum Speicher von 
 * Zeichen und deren Haeufigkeiten.
 * 
 * File:   frequency.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */

#ifndef _FREQUENCY_H
#define _FREQUENCY_H

/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "common.h"


/*****************************************************************************
 * Typdefinitionen
 *****************************************************************************/
/**
 * Typdefinition einer Frequenz.
 */
typedef struct _FREQUENCY FREQUENCY;


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Erstellt eine neue Frequenz mit dem angegebenen Zeichen und der Häufigkeit 1.
 * @param new_zeichen unsigned char Das Zeichen.
 * @return FREQUENCY* Die neue Frequenz oder NULL im Fehlerfall.
 */
#define frequency_new(new_zeichen) frequency_new_with_anzahl((new_zeichen), 1)

/**
 * Erstellt eine neue Frequenz mit dem angegebenen Zeichen und der angegebenen Häufigkeit.
 * @param new_zeichen unsigned char Das Zeichen.
 * @param new_anzahl unsigned int Die Häufigkeit.
 * @return FREQUENCY* Die neue Frequenz oder NULL im Fehlerfall.
 */
extern FREQUENCY* frequency_new_with_anzahl(unsigned char new_zeichen, unsigned int new_anzahl);

/**
 * Gibt die Frequenz frei.
 * @param f FREQUENCY** Ein Zeiger auf die freizugebende Frequenz.
 */
extern void frequency_free(FREQUENCY** pp_freq);

/**
 * Gibt das Zeichen der Frequenz zurück.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return unsigned char Das Zeichen der Frequenz.
 */
extern unsigned char frequency_get_zeichen(FREQUENCY* p_freq);

/**
 * Gibt die Anzahl der Frequenz zurück.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return unsigned int Die Anzahl der Frequenz.
 */
extern unsigned int frequency_get_anzahl(FREQUENCY* p_freq);

/**
 * Gibt das linke Kind der Frequenz zurück.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return FREQUENCY* Das linke Kind.
 */
extern FREQUENCY* frequency_get_left(FREQUENCY* p_freq);

/**
 * Setzt ein neues linkes Kind.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @param p_new_left FREQUENCY* Das neue linke Kind.
 */
extern void frequency_set_left(FREQUENCY* p_freq, FREQUENCY* p_new_left);

/**
 * Gibt das rechte Kind der Frequenz zurück.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return FREQUENCY* Das rechte Kind.
 */
extern FREQUENCY* frequency_get_right(FREQUENCY* p_freq);

/**
 * Setzt ein neues rechtes Kind.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @param p_new_right FREQUENCY* Das neue rechte Kind.
 */
extern void frequency_set_right(FREQUENCY* p_freq, FREQUENCY* p_new_right);

/**
 * Gibt an, ob die Frequenz ein Blatt ist.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return BOOL TRUE wenn die Frequenz ein Blatt ist, FALSE sonst.
 */
extern BOOL frequency_is_leaf(FREQUENCY* p_freq);

/**
 * Vergleicht zwei Frequenzen anhand ihrer Häufigkeiten.
 * @param p_freq1 FREQUENCY* Die eine Frequenz.
 * @param p_frep2 FREQUENCY* Die andere Frequenz.
 * @return int 1 wenn p_freq1 > p_freq2, 0 wenn beide Frequenzen gleich sind, -1 wenn p_freq1 < p_freq2.
 */
extern int cmp_frequency_haeufigkeiten(FREQUENCY* p_frep1, FREQUENCY* p_frep2);

/**
 * Gibt die Höhe des Frequenz-Baums zurück.
 * @param p_freq FREQUENCY* Die Frequenz.
 * @return unsigned int Die Höhe des Frequenz-Baums.
 */
extern unsigned int frequency_get_height(FREQUENCY* p_freq);

/**
 * Gibt die übergebene Frequenz als Baum aus.
 * @param p_freq FREQUENCY* Die auszugebende Frequenz.
 * @param depth int Die aktuelle Tiefe.
 * @param index int Der aktuelle Index.
 */
extern void frequency_print(FREQUENCY* p_freq, int depth, int index);

/**
 * Prüft, ob 2 Frequenzen gleich sind.
 * @param p_frep1 FREQUENCY* Die eine Frequenz.
 * @param p_frep2 FREQUENCY* Die andere Frequenz.
 * @return BOOL TRUE, falls p_frep1 und p_frep2 gleich sind, FALSE sonst.
 */
extern BOOL frequency_equals(FREQUENCY* p_freq1, FREQUENCY* p_freq2);

#endif
