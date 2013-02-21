/**
 * @mainpage Huffmann
 * 
 * Dieses Projekt realisiert eine einfache Komprimierung von Dateien mit Hilfe 
 * des Huffmann-Algorithmus.
 * 
 * Komprimierte Dateien haben den folgenden Aufbau:
 * |--------------------------------------------------------------------------|
 * | Anzahl genutzter Bits im letzten Byte (3 Bit) | Codebuch (max. 1,09 kB)  |
 * | -------------------------------------------------------------------------|
 * | Daten                                                                    |
 * | -------------------------------------------------------------------------|
 *
 * Das Codebuch wiederum enthaelt fuer jedes ASCII-Zeichen folgende Angabe:
 * Die ersten 3 Bits geben an, wie viele der folgenden Bytes fuer die Anzahl von 
 * Vorkommen dieses Zeichens benoetigt werden. Sind alle drei Bits 0, so folgt ab
 * dem naechsten Bit die selbe Angabe fuer das naechste Zeichen.
 * Dies fuehrt dazu, dass das Codebuch maximal 1,09 kB gross wird, hat allerdings
 * die Einschraenkung, dass jedes Zeichen maximal 4.294.967.296 mal in der Datei
 * vorkommen kann.
 * 
 * 
 * @file
 * Dieses Modul dient zum Starten der (De)Komprimierung einer Datei.
 * 
 * File:   main.c
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */

 
/*****************************************************************************
 * Includes
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "cmdargs.h"
#include "huffmann.h"


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Gibt einen Hilfetext zur Verwendung des Programms auf dem Bildschirm aus.
 * @param programm Name des Programms
 */
static void print_help(char* programm);


/*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
/**
 * Hauptfunktion, die beim Starten des Programms aufgerufen wird.
 * @param argc Anzahl der Parameter
 * @param argv Die Parameterliste. Der erste Parameter ist immer der Name des 
               Programms.
 * @return Liefert 0, falls das Programm erfolgreich durchgelaufen ist,
           ansonsten einen Wert ungleich 0.
 */
int main (int argc, char **argv) {
    cmdargs argumente = parse_args(argc, argv);
    
    if (argumente.ungueltig)
    {
        if(argumente.fehlermeldung != NULL)
        {
            printf("FEHLER: %s\n\n", argumente.fehlermeldung);
        }
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    } 
    else if (argumente.zeige_hilfe)
    {
        print_help(argv[0]);
    } 
    else if (argumente.komprimiere) 
    {
        /* Eingabedatei komprimieren */
        DPRINT("Datei wird komprimiert...\n");
        if(argumente.output_file == NULL) {
            int input_file_laenge = (int) strlen(argumente.input_file);
            char *ausgabedatei = malloc((input_file_laenge + 4) * sizeof(char));
            ASSERT_ALLOC(ausgabedatei);
            strcpy(ausgabedatei, argumente.input_file);
            ausgabedatei = strcat(ausgabedatei, ".hc");
            
            argumente.output_file = ausgabedatei;
        }

        compress(argumente.input_file, argumente.output_file);
    }
    else
    {
        /* Eingabedatei dekomprimieren */
        DPRINT("Datei wird dekomprimiert...\n");
        if(argumente.output_file == NULL) {
            char *ausgabedatei = malloc(strlen(argumente.input_file)+ 4);
            ASSERT_ALLOC(ausgabedatei)
            strcpy(ausgabedatei, argumente.input_file);
            strcat(ausgabedatei, ".hd");
            argumente.output_file = ausgabedatei;
        }
        
        decompress(argumente.input_file, argumente.output_file);
    }
    return EXIT_SUCCESS;
}


/**
 * Gibt den Hilfetext inlusive einiger beispielhafter Programmaufrufe auf dem
 * Bildschirm aus.
 * @param programm Name des Programms.
 */
static void print_help(char* programm)
{
    char *einrueckung;
    char *programmname = NULL;
    int laenge_programmname; 
    int i;
    if(programm != NULL) 
    {
        programmname = strrchr(programm, '/');
        programmname++;
    }
    /* Kann der Name des Programms nicht ermittelt werden, wird dieser 
     * auf den Standardwert "huffmann" gesetzt.
     */
    if(programmname == NULL) 
    {
        programmname = "huffmann";
    }
    
    laenge_programmname = (int) strlen(programmname);
    
    einrueckung = malloc(laenge_programmname*sizeof(char));
    ASSERT_ALLOC(einrueckung)
    
    for(i = 0; i < laenge_programmname; i++) {
        einrueckung[i] = ' ';
    }
    einrueckung[i] = 0;
    
    
    /* Hilfetext */
    printf( "SYNTAX:\n"
            "  %s (-c | -d) inputFile [outputFile]\n"
            "\n"
            "  Optionen:\n"
            "     -c  Komprimiert die Datei inputFile.\n"
            "     -d  Behandelt inputFile als komprimierte Datei und\n"
            "         dekomprimiert diese.\n"
            "     -h  Zeigt diese Hilfe an.\n", programmname);
    printf( "\n"
            "Dieses Programm komprimiert Dateien mit Hilfe des Huffmann-"
               "Algorithmus.\n"
            "\n"
            "Wird das Programm mit dem Parameter -c oder -d aufgerufen,\n"
            "so muss zwingend auch ein inputFile angegeben werden.\n"
            "Wird kein OutputFile angegeben, so wird an den Namen der\n"
            "Eingabedatei eine Standardendung angehangen. Diese lautet im \n"
            "Modus Komprimierung .hc bzw. .hd im Modus Dekomprimierung.\n"
            "\n");
    printf( "BEISPIELE:\n"
            "  > %s -h              ... Zeigt diese Hilfe an.\n", programmname);
    printf( "  > %s -c datei.exe    ... Komprimiert die Datei datei.exe,\n"
            "  %s                       dabei wird die Ausgabedatei\n"
            "  %s                       datei.exe.hc erzeugt.\n", programmname,
           einrueckung, einrueckung);
    printf( "  > %s -d datei.exe.hc ... Dekomprimiert die Datei datei.exe.hc\n"
            "  %s                       und speichert das dekomprimierte \n"
            "  %s                       Ergebnis in der datei.exe.hd.\n",
            programmname, einrueckung, einrueckung);
    printf( "  > %s -c d.txt d.comp ... Komprimiert die Datei d.txt und\n"
            "  %s                       speichert das Ergebnis in d.comp.\n",
            programmname, einrueckung);
    free(einrueckung);
}
