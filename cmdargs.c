/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "cmdargs.h"
#include <string.h>


/*****************************************************************************
* Funktionsprototypen
 *****************************************************************************/
/**
 * Erzeugt eine Parameter-Struktur, mit den folgenden Vorbelegungen:<br>
 * <ul>
 *    <li>Input-File, Output-File und Fehlermeldung sind NULL</li>
 *    <li>Die Struktur repraesentier ein gueltige Kombination von Argumetnen</li>
 *    <li>Es soll komprimiert werden</li>
 *    <li>Die Hilfe soll nicht angezeigt werden</li>
 * </ul>
 * @return Gibt die neue Struktur zurueck.
 */
static cmdargs new_cmdargs(void);


/*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
/* ---------------------------------------------------------------------------
 * Funktion: parse_args
 * ------------------------------------------------------------------------ */
cmdargs parse_args(int argc, char **argv)
{
    cmdargs arguments = new_cmdargs();

    if (argc >= 2 && strcmp(argv[1], "-h") == 0)
    {
	    /* Ist der Paramter -h gesetzt, darf es keine weiteren Parameter 
		 * geben 
		 */
        if (argc == 2)
        {
            arguments.zeige_hilfe = TRUE;
        }
        else
        {
            arguments.fehlermeldung = FEHLER_ZU_VIELE_ARGUEMENTE;
            arguments.ungueltig = TRUE;
        }
    } 
    else if (argc >= 3) 
    {
        if(strcmp(argv[1], "-c") == 0) 
        {
            arguments.komprimiere = TRUE;
            arguments.input_file = argv[2];
            if(argc == 4) 
            {
                arguments.output_file = argv[3];
            } 
            else if (argc > 4) 
            {
                arguments.fehlermeldung = FEHLER_ZU_VIELE_ARGUEMENTE;
                arguments.ungueltig = TRUE;
            }
        } 
        else if (strcmp(argv[1], "-d") == 0) 
        {
            arguments.komprimiere = FALSE;
            arguments.input_file = argv[2];
            if(argc == 4) 
            {
                arguments.output_file = argv[3];
            } 
            else if (argc > 4) 
            {
                arguments.fehlermeldung = FEHLER_ZU_VIELE_ARGUEMENTE;
                arguments.ungueltig = TRUE;
            }
        } 
        else 
        {
            arguments.fehlermeldung = strcat(UNGUELTIGER_PARAMETER, argv[1]);
            arguments.ungueltig = TRUE;   
        }
    } 
    else 
    {
		/* Es wurden keine Parameter angegeben */
        arguments.fehlermeldung = FEHLER_ZU_WENIG_ARGUMENTE;
        arguments.ungueltig = TRUE;   
    }


    return arguments;
}


/* ---------------------------------------------------------------------------
 * Funktion: cmdargs_new
 * ------------------------------------------------------------------------ */
static cmdargs new_cmdargs()
{
    cmdargs arguments;
    arguments.fehlermeldung = NULL;
    arguments.input_file = NULL;
    arguments.komprimiere = TRUE;
    arguments.output_file = NULL;
    arguments.ungueltig = FALSE;
    arguments.zeige_hilfe = FALSE;
    return arguments;
}
