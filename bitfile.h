/**
 * @file
 * Dieses Modul stellt Funktionen zum bit- und byteweisen Zugriff auf Dateien
 * zur Verfuegung.
 * 
 * File:   bitfile.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */

#ifndef _BITFILE_H
#define _BITFILE_H

/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "bitarray.h"
#include "common.h"


/*****************************************************************************
 * Typdefinitionen
 *****************************************************************************/
/**
 * Defintion eines Typs BITFILE und seiner Struktur. 
 */ 
 typedef struct {
    /* Handle auf die zu verarbeitende Datei.  */
    FILE *fd;
	
	/* Puffer fuer das naechste Byte der Datei. */
    BYTE buffer;
	
	/* Position des naechsten Bits, das zurueckgegeben werden soll, innerhalb 
	 * des buffer. 
	 */
    int buffer_index;
	
	/* Flag, ob das Ende der Datei bereits erreicht wurde. */
    BOOL eof;
	
	/* Flag, ob das Bitfile zum Schreiben (TRUE) oder Lesen (FALSE) geoeffnet 
	 * wurde.
	 */
    BOOL write_mode;
} BITFILE;

/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Oeffnet eine Datei als Bitfile.
 * @param path Pfad zur zu oeffnenden Datei.
 * @param w TRUE, falls die Datei zum Schreiben geoeffnet werden soll, 
 *          sonst FALSE.
 * @return Liefert ein BITFILE oder NULL, falls das Oeffnen nicht erfolgreich 
 *         war.
 */
BITFILE *bitfile_open(char* path, BOOL w);

/**
 * Schliesst ein Bitfile.
 * @param fd Zu schliessendes Bitfile.
 */
void bitfile_close(BITFILE **fd);

/**
 * Liest das naechste Bit aus dem Bitfile.
 * @param fd Bitfile, aus dem gelesen werden soll.
 * @return Das gelesene Bit. TRUE entspricht 1, FALSE ist 0.
 */
BOOL bitfile_read_bit(BITFILE *fd);

/**
 * Liest das naechste Byte aus dem Bitfile.
 * @param fd Bitfile, aus dem gelesen werden soll.
 * @return Gelesesenes Byte.
 */
BYTE bitfile_read_byte(BITFILE *fd);

/**
 * Liest eine bestimmte zusammenhaengender Bits aus dem Bitfile.
 * @param fd Bitfile, aus dem gelesen werden soll.
 * @param length Anzahl der zu lesenden Bits.
 * @return Array gelesener Bits.
 */
BITARRAY *bitfile_read_bitarray(BITFILE *fd, int length);

/**
 * Schreib das uebergebene Bit in das Bitfile.
 * @param fd Bitfile, in das geschrieben werden soll.
 * @param d Zu schreibendes Bit. TRUE entspricht 1, FALSE ist 0.
 */
void bitfile_write_bit(BITFILE *fd, BOOL d);

/**
 * Schreibt ein Byte in das Bitfile.
 * @param fd Bitfile, in das geschrieben werden soll.
 * @param d Zu schreibendes Byte.
 */
void bitfile_write_byte(BITFILE *fd, BYTE d);

/**
 * Schreibt die uebergebene Anzahl Bits in das Bitfile.
 * @param fd Bitfile, in das geschrieben werden soll.
 * @param d Zu schreibendes Bitarray.
 */
void bitfile_write_bitarray(BITFILE *fd, BITARRAY *ba);

/**
 * 
 * @param fd
 * @return 
 */
BOOL bitfile_is_eof(BITFILE *fd);

/**
 * 
 * @param fd
 * @param offset
 * @param origin
 * @return 
 */
int bitfile_seek(BITFILE *fd, long int offset, int origin);

void bitfile_flush_write(BITFILE *fd);

BOOL bitfile_last_read_was_error(BITFILE *fd);

#endif
