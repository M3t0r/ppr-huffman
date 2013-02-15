/*****************************************************************************
 * Includes
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "huffmann.h"
#include "bitfile.h"
#include "codebuch.h"


/*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
void compress(char *in_filename, char *out_filename)
{
	/************************************************************************
	 * Wir müssen mit 3Bit noch speichern, wie viele Bits des letzten Bytes *
	 * in der komprimierten Datei noch Code sind.                           *
	 ************************************************************************/
	
    BYTE byte = 0;
    BOOL ist_leer;
    unsigned int anzahl_zeichen[256];
    CODEBUCH *p_codebuch;
    BITFILE *p_input;
    BITFILE *p_output;
    BITARRAY *code;
    
    if(in_filename == NULL || out_filename == NULL) {
        fprintf(stderr, "Kann nicht komprimieren, da Ein- oder Ausgabedatei "
                "nicht angegeben wurde!\n");
        exit(EXIT_FAILURE);
    }
    
    /* Eingabedatei oeffnen */
    p_input = bitfile_open(in_filename, FALSE);
    if(p_input == NULL)
    { 
        fprintf(stderr, "Fehler beim Öffnen der Eingabedatei.\n"
                "Stimmt der Pfad: '%s'\n", in_filename);
        exit(EXIT_FAILURE);
    } 
    DPRINT("Eingabedatei geoeffnet!\n");
    
    /* Ausgabedatei oeffnen */
    p_input = bitfile_open(out_filename, TRUE);
    if(p_output == NULL)
    { 
        fprintf(stderr, "Fehler beim Öffnen der Ausgabedatei.\n"
                "Stimmt der Pfad: '%s'\n", out_filename);
        exit(EXIT_FAILURE);
    } 
    DPRINT("Ausgabedatei geoeffnet!\n");
    
    /* Initialisiere anzahl_zeichen Vektor */
    memset(anzahl_zeichen, 0, sizeof(unsigned int)*256);
    
    
    

    ist_leer = TRUE;
    
    /* Codebuch aufbauen */
    while(!bitfile_is_eof(p_input)) 
    {
        byte = bitfile_read_byte(p_input);
        
        if(byte == 0 && bitfile_last_read_was_error(p_input))
        {
            perror("Fehler beim lesen der Eingabedatei");
            exit(EXIT_FAILURE);
        }
                
        if(!(byte == 0 && bitfile_is_eof(p_input)))
        {
            anzahl_zeichen[byte]++;
            ist_leer = FALSE;
        }
    }

    
    if(ist_leer == FALSE) 
    {
        /* zeiger an den anfang */
        bitfile_seek(p_input, 0, SEEK_SET);
    
        p_codebuch = codebuch_new_from_frequency(anzahl_zeichen);
        if(p_codebuch == NULL)
        {
            fprintf(stderr, "Beim Erstellen des Codebuchs trat ein Fehler auf.\n\n");
            exit(EXIT_FAILURE);
        }


        /* Ausgabedatei erzeugen */
        bitfile_write_bitarray(p_output, codebuch_structure(p_codebuch));
        while(!bitfile_is_eof(p_input)) 
        {
            byte = bitfile_read_byte(p_input);
            code = codebuch_code_for_char(p_codebuch, byte);
            if(code == 0 && codebuch_last_char_was_error(p_codebuch)) 
            {
                fprintf(stderr, "Es ist ein Fehler aufgetreten.");
                exit(EXIT_FAILURE);
            }
            bitfile_write_bitarray(p_output, code);
        }
    }
    else
    {
        DPRINT("Die Eingabedatei war leer, es wird nichts komprimiert.");
    }
    
    bitfile_close(p_output);
    DPRINT("Ausgabedatei wurde geschlossen!\n");
    
    bitfile_close(p_input);
    DPRINT("Eingabedatei wurde geschlossen\n");
}

void decompress(char *in_filename, char *out_filename)
{
    /**********************************************************
     * +-------------------------------------------+--------+ *
     * | 3 Bit -> wie viele Bytes die Anzahl nutzt | Anzahl | *
     * +-------------------------------------------+--------+ *
     *    immer 3 Bit 								 0-4 Byte *
     **********************************************************/
}
