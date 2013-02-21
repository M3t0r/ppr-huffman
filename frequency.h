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
 * Makrodefintion
 *****************************************************************************/
/**
 * Erstellt eine neue Frequenz mit dem angegebenen Zeichen und der Häufigkeit 1.
 * @param new_zeichen Das Zeichen.
 * @return Die neue Frequenz oder NULL im Fehlerfall.
 */
#define frequency_new(new_zeichen) frequency_new_with_anzahl((new_zeichen), 1)

/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Erstellt eine neue Frequenz mit dem angegebenen Zeichen und der angegebenen Häufigkeit.
 * @param new_zeichen Das Zeichen.
 * @param new_anzahl Die Häufigkeit.
 * @return Die neue Frequenz oder NULL im Fehlerfall.
 */
extern FREQUENCY* frequency_new_with_anzahl(unsigned char new_zeichen, unsigned int new_anzahl);

/**
 * Gibt die Frequenz frei.
 * @param f Ein Zeiger auf die freizugebende Frequenz.
 */
extern void frequency_free(FREQUENCY** pp_freq);

/**
 * Gibt das Zeichen der Frequenz zurück.
 * @param p_freq Die Frequenz.
 * @return Das Zeichen der Frequenz.
 */
extern unsigned char frequency_get_zeichen(FREQUENCY* p_freq);

/**
 * Gibt die Anzahl der Frequenz zurück.
 * @param p_freq Die Frequenz.
 * @return Die Anzahl der Frequenz.
 */
extern unsigned int frequency_get_anzahl(FREQUENCY* p_freq);

/**
 * Gibt das linke Kind der Frequenz zurück.
 * @param p_freq Die Frequenz.
 * @return Das linke Kind.
 */
extern FREQUENCY* frequency_get_left(FREQUENCY* p_freq);

/**
 * Setzt ein neues linkes Kind.
 * @param p_freq Die Frequenz.
 * @param p_new_left Das neue linke Kind.
 */
extern void frequency_set_left(FREQUENCY* p_freq, FREQUENCY* p_new_left);

/**
 * Gibt das rechte Kind der Frequenz zurück.
 * @param p_freq Die Frequenz.
 * @return Das rechte Kind.
 */
extern FREQUENCY* frequency_get_right(FREQUENCY* p_freq);

/**
 * Setzt ein neues rechtes Kind.
 * @param p_freq Die Frequenz.
 * @param p_new_right Das neue rechte Kind.
 */
extern void frequency_set_right(FREQUENCY* p_freq, FREQUENCY* p_new_right);

/**
 * Gibt an, ob die Frequenz ein Blatt ist.
 * @param p_freq Die Frequenz.
 * @return TRUE wenn die Frequenz ein Blatt ist, FALSE sonst.
 */
extern BOOL frequency_is_leaf(FREQUENCY* p_freq);

/**
 * Vergleicht zwei Frequenzen anhand ihrer Häufigkeiten.
 * @param p_freq1 Die eine Frequenz.
 * @param p_frep2 Die andere Frequenz.
 * @return 1 wenn p_freq1 > p_freq2, 0 wenn beide Frequenzen gleich sind, -1 wenn p_freq1 < p_freq2.
 */
extern int cmp_frequency_haeufigkeiten(FREQUENCY* p_frep1, FREQUENCY* p_frep2);

/**
 * Gibt die Höhe des Frequenz-Baums zurück.
 * @param p_freq FDie Frequenz.
 * @return Die Höhe des Frequenz-Baums.
 */
extern unsigned int frequency_get_height(FREQUENCY* p_freq);

/**
 * Gibt die übergebene Frequenz als Baum aus.
 * @param p_freq Die auszugebende Frequenz.
 * @param depth Die aktuelle Tiefe.
 * @param index Der aktuelle Index.
 */
extern void frequency_print(FREQUENCY* p_freq, int depth, int index);

/**
 * Prüft, ob 2 Frequenzen gleich sind.
 * @param p_frep1 Die eine Frequenz.
 * @param p_frep2 Die andere Frequenz.
 * @return TRUE, falls p_frep1 und p_frep2 gleich sind, FALSE sonst.
 */
extern BOOL frequency_equals(FREQUENCY* p_freq1, FREQUENCY* p_freq2);

#endif
