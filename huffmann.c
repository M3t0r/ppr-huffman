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
    int byte = 0;
    BOOL ist_leer;
    unsigned int anzahl_zeichen[256];
    CODEBUCH *p_codebuch;
    FILE *p_input;
    BITFILE *p_output;
    BITARRAY *code;
    
    if ((in_filename == NULL) || (out_filename == NULL)) {
        fprintf(stderr, "Kann nicht komprimieren, da Ein- oder Ausgabedatei "
                "nicht angegeben wurde!\n");
        exit(EXIT_FAILURE);
    }
    
    /* Eingabedatei oeffnen */
    p_input = fopen(in_filename, "rb");
    if (p_input == NULL)
    { 
        fprintf(stderr, "Fehler beim Öffnen der Eingabedatei.\n"
                "Stimmt der Pfad: '%s'?\n", in_filename);
        exit(EXIT_FAILURE);
    } 
    DPRINT("Eingabedatei geoeffnet!\n");
    
    /* Ausgabedatei oeffnen */
    p_output = bitfile_open(out_filename, TRUE);
    if (p_output == NULL)
    { 
        fprintf(stderr, "Fehler beim Öffnen der Ausgabedatei.\n"
                "Stimmt der Pfad: '%s'?\n", out_filename);
        exit(EXIT_FAILURE);
    } 
    DPRINT("Ausgabedatei geoeffnet!\n");
    
    /* Initialisiere anzahl_zeichen Vektor */
    memset(anzahl_zeichen, 0, sizeof(unsigned int)*256);

    ist_leer = TRUE;
    
    /* Codebuch aufbauen */
    byte = fgetc(p_input);
    while (byte != EOF)
    {
    	anzahl_zeichen[byte]++;
        ist_leer = FALSE;
    	
    	byte = fgetc(p_input);
    }
    
    if (ist_leer == FALSE) 
    {
        unsigned int benutzte_bits;
        BITARRAY *codebuch;
        BYTE erste_byte;
        int i;
        
        fclose(p_input);
        p_input = fopen(in_filename, "rb");
		if(p_input == NULL)
		{ 
			fprintf(stderr, "Fehler beim Öffnen der Eingabedatei.\n"
					"Stimmt der Pfad: '%s'?\n", in_filename);
			exit(EXIT_FAILURE);
		} 
    
        p_codebuch = codebuch_new_from_frequency(anzahl_zeichen);
        if(p_codebuch == NULL)
        {
            fprintf(stderr, "Beim Erstellen des Codebuchs trat ein Fehler auf.\n\n");
            exit(EXIT_FAILURE);
        }
        


        /* Ausgabedatei erzeugen */
        
        /* platz für benutzte_bits am anfang lassen */
        bitfile_write_bit(p_output, FALSE);
        bitfile_write_bit(p_output, FALSE);
        bitfile_write_bit(p_output, FALSE);
        
        codebuch = codebuch_structure(p_codebuch);
        bitfile_write_bitarray(p_output, codebuch);
                
        for(i = 0; i < bitarray_length(codebuch); i++)
        {
            if(((i/8) % 10) == 0 && i%8 == 0)
                printf("\n%6d: ", i);
        
            else if(i%8 == 0)
                printf(" ");
    
            printf("%d", bitarray_get_bit(codebuch, i));
        }
        
        benutzte_bits = (bitarray_length(codebuch) + 3) % 8;
        
        byte = fgetc(p_input);
        
        do
        {
            code = codebuch_code_for_char(p_codebuch, byte);
            
            if(code == NULL)
            {
                fprintf(stderr, "Es ist ein Fehler aufgetreten.\n");
                exit(EXIT_FAILURE);
            }
            
            benutzte_bits = (benutzte_bits + bitarray_length(code)) % 8;
            
            bitfile_write_bitarray(p_output, code);
            
            byte = fgetc(p_input);
        } while (byte != EOF);
        
        bitfile_flush_write(p_output);
        bitfile_seek(p_output, 0, SEEK_SET);
        erste_byte = benutzte_bits;
        
        for(i = 0; i < 5; i++)
        {
            erste_byte = (erste_byte << 1) | bitarray_get_bit(codebuch, i);
        }
        
        bitfile_write_byte(p_output, erste_byte);
    }
    else
    {
        DPRINT("Die Eingabedatei war leer, es wird nichts komprimiert.");
    }
    
    
    bitfile_close(&p_output);
    DPRINT("Ausgabedatei wurde geschlossen!\n");
    
    fclose(p_input);
    DPRINT("Eingabedatei wurde geschlossen\n");
}

void decompress(char *in_filename, char *out_filename)
{
    BITFILE *p_input;
    FILE* p_output;
    int benutzte_bits;
    
    if(in_filename == NULL || out_filename == NULL) {
        fprintf(stderr, "Kann nicht dekomprimieren, da Ein- oder Ausgabedatei "
                "nicht angegeben wurde!\n");
        exit(EXIT_FAILURE);
    }
    
    /* Eingabedatei oeffnen */
    p_input = bitfile_open(in_filename, FALSE);
    if(p_input == NULL)
    { 
        fprintf(stderr, "Fehler beim Öffnen der Eingabedatei.\n"
                "Stimmt der Pfad: '%s'?\n", in_filename);
        exit(EXIT_FAILURE);
    } 
    DPRINT("Eingabedatei geoeffnet!\n");
    
    /* Ausgabedatei oeffnen */
    p_output = fopen(out_filename, "wb");
    if(p_output == NULL)
    { 
        fprintf(stderr, "Fehler beim Öffnen der Ausgabedatei.\n"
                "Stimmt der Pfad: '%s'?\n", out_filename);
        exit(EXIT_FAILURE);
    } 
    DPRINT("Ausgabedatei geoeffnet!\n");
    
    
    benutzte_bits = bitfile_read_bit(p_input) << 2 | bitfile_read_bit(p_input) << 1 | bitfile_read_bit(p_input);
    if(bitfile_last_read_was_error(p_input))
    {
        perror("Fehler beim einlesen");
    }
    else if(bitfile_is_eof(p_input))
    {
        DPRINT("Eingabedatei war leer, es wird nichts dekomprimiert.");
    }
    else
    {
        CODEBUCH *p_codebuch;
        BITARRAY *pipeline;
        unsigned int anzahl_zeichen[256];
        int i;
<<<<<<< HEAD
        
=======
                
>>>>>>> tuts jetzt
        memset(anzahl_zeichen, 0, sizeof(unsigned int) * 256);
        
        /* häufigkeit der zeichen einlesen */
        for(i = 0; i < 256; i++)
        {
<<<<<<< HEAD
            int anzahl_byte = bitfile_read_bit(p_input) << 2 | bitfile_read_bit(p_input) << 1 | bitfile_read_bit(p_input);
            for(; anzahl_byte > 0; anzahl_byte--)
=======
            int groesse_anzahl = bitfile_read_bit(p_input) << 2 | bitfile_read_bit(p_input) << 1 | bitfile_read_bit(p_input);
            for(; groesse_anzahl > 0; groesse_anzahl--)
>>>>>>> tuts jetzt
            {
                anzahl_zeichen[i] = (anzahl_zeichen[i] << 8) | bitfile_read_byte(p_input);
            }            
        }
        
        p_codebuch = codebuch_new_from_frequency(anzahl_zeichen);
        pipeline = bitarray_new();
                
        do
        {
            unsigned int verwendete_bits = 0;
            BYTE zeichen = codebuch_char_for_code(p_codebuch, pipeline, &verwendete_bits);
            if ((zeichen == 0) && codebuch_last_char_was_error(p_codebuch))
            {
                if (!bitfile_is_eof(p_input))
                {
                    int i;
                    BITARRAY *lese = bitfile_read_bitarray(p_input, 8);

                    bitarray_merge(pipeline, lese);

                    bitarray_free(&lese);
                    if (bitfile_is_eof(p_input))
                    {
                        for (i = 0; (benutzte_bits + i) < 8; i++)
                        {
                            bitarray_pop(pipeline);
                        }
                    }
                }
            }
            else
            {	
                bitarray_remove_front(pipeline, verwendete_bits);
                
                fputc(zeichen, p_output);
            }
<<<<<<< HEAD
        } while(!bitfile_is_eof(p_input));
        bitarray_print(pipeline);
        
/*
k 0b1000
a 0b0010
r 0b101
t 0b0011
o 0b0000
f 0b11
f 0b11
e 0b011
l 0b0001
p 0b1001
u 0b0100
f 0b11
f 0b11
e 0b011
r 0b101
*/
        
=======
        } while (!bitfile_is_eof(p_input) || (bitarray_length(pipeline) != 0));
>>>>>>> tuts jetzt
    }
    
    fclose(p_output);
    DPRINT("Ausgabedatei wurde geschlossen!\n");
    
    bitfile_close(&p_input);
    DPRINT("Eingabedatei wurde geschlossen\n");
}
