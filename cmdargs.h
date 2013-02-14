/**
 * @file
 * Dieses Modul dient dazu die beim Aufruf des Programms anegegebenen 
 * Argumente zu parsen und in einer passenden Struktur zur weiteren Verarbeitung
 * aufzubereiten.
 * 
 * File:   cmdargs.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */
#ifndef _CMDARGS_H
#define _CMDARGS_H

/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "common.h"

/*****************************************************************************
 * Typdefinition
 *****************************************************************************/
/**
 * Definition einer Struktur und des Typs cmdargs zur Repraesentation der,
 * beim Aufruf des Programms angegebenen, Argumente.
 */
typedef struct {
    /* Flag, ob die Parameter den Anforderungen genuegen*/
    BOOL    ungueltig;
    
    /* Falls ungueltig = TRUE enthaelt fehlermeldung eine Beschreibung */
    char*   fehlermeldung;
    
    /* Flag, ob der Hilfetext angezeigt werden soll */
    BOOL    zeige_hilfe;
    
    /* Gibt den Namen der Eingabedatei an */
    char*   input_file;
    
    /* Gibt den Namen der Ausgabedatei an, ist NULL, falls das Argument nicht
     * angegeben wurde.
     */
    char*   output_file;
    
    /* Flag, ob komprimiert (TRUE) oder dekomprimiert (FALSE) werden soll */
    BOOL    komprimiere;
} cmdargs;


/*****************************************************************************
 * Konstanten definieren
 *****************************************************************************/
/**
 * Konstante fuer den Fehlerfall, dass zu wenig Parameter angegeben wurden.
 */
#define FEHLER_ZU_WENIG_ARGUMENTE "Es wurden zu wenig Paramenter angebenen."

/**
 * Konstante fuer den Fehlerfall, dass ein unbekannter Paramenter gefunden wurde.
 */
#define UNGUELTIGER_PARAMETER "Ungueltige Parameter: "

/**
 * Konstante fuer den Fehlerfall, dass zu viele Parameter angegeben wurden.
 */
#define FEHLER_ZU_VIELE_ARGUEMENTE "Es wurden zu viele Parameter angegeben."


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Parst die uebergegebenen Argumente.
 * @param argc Anzahl der uebergebenen Arguemente.
 * @param argv Array von Argumenten.
 * @return Gibt ein Objekt cmdargs zurueck.
 */
cmdargs parse_args(int argc, char **argv);



#endif
