/**
 * @mainpage Huffmann
 * 
 * Dieses Projekt realisiert eine einfache Komprimierung von Dateien mit Hilfe 
 * des Huffmann-Algorithmus.
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
            char *ausgabedatei = malloc((input_file_laenge + 3) * sizeof(char));
            ASSERT_ALLOC(ausgabedatei);
            strncpy(ausgabedatei, argumente.input_file, (size_t) input_file_laenge);
            ausgabedatei = strcat(ausgabedatei, ".hc");
            
            argumente.output_file = ausgabedatei;
        }

        //compress(argumente.input_file, argumente.output_file);
    }
    else
    {
        /* Eingabedatei dekomprimieren */
        DPRINT("Datei wird dekomprimiert...\n");
        if(argumente.output_file == NULL) {
            int input_file_laenge = (int) strlen(argumente.input_file);
            char *dateiendung = argumente.input_file + input_file_laenge - 3;
            char *ausgabedatei = malloc((input_file_laenge + 3) * sizeof(char));
            ASSERT_ALLOC(ausgabedatei);
            
            /* Wenn die Dateiendung der Eingabedatei .hc ist, wird die 
             * Ausgabedatei genauso benannt, einzig der letzte Buchstabe des
             * Namens wird durch d ersetzt, so dass die Endung .hd entsteht.
             */
            if(dateiendung != NULL && strcmp(dateiendung, ".hc") == 0) {
                strncpy(ausgabedatei, argumente.input_file, (size_t) (input_file_laenge - 1));
                ausgabedatei = strcat(ausgabedatei, "d");
            } else {
                strncpy(ausgabedatei, argumente.input_file, (size_t) input_file_laenge);
                ausgabedatei = strcat(ausgabedatei, ".hd");
            }
            argumente.output_file = ausgabedatei;
        }
        
        //decompress(argumente.input_file, argumente.output_file);
    }
    return EXIT_SUCCESS;
}



static void print_help(char* programm)
{
    char* einrueckung = "";
    char* programmname = NULL;
    int laenge_programmname; 
    int i;
    if(programm != NULL) 
    {
        programmname = strrchr(programm, '/');
        programmname++;
    }
    /* Kann der Name des Programms nicht ermittelt werden, wird dieser 
     * auf den Standardwert "hufmann" gesetzt.
     */
    if(programmname == NULL) 
    {
        programmname = "huffmann";
    }
    
    laenge_programmname = (int) strlen(programmname);
    
    for(i = 0; i < laenge_programmname; i++) {
        einrueckung = strcat(einrueckung, " ");
    }
    
    
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
            "  %s                       speichert das Ergebnis in d.comp.",
            programmname, einrueckung);
}
