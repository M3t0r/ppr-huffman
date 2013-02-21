/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "bitfile.h"
#include <stdio.h>
#include <string.h>


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Liest das naechste Byte der Datei ein und schreibt dieses zur weiteren
 * Verarbeitung in den Buffer.
 * @BITFILE fd BITFILE, dessen Buffer gefuellt werden soll.
 */
static void bitfile_fill_buffer(BITFILE *fd);

/**
 * Schreibt den aktuellen Inhalt des Buffer in die Datei.
 * @BITFILE fd BITFILE, dessen Buffer geschrieben werden soll.
 */
static void bitfile_write_buffer_to_file(BITFILE *fd);


/*****************************************************************************
 * Funktionsdefinitionen
 *****************************************************************************/
/* ---------------------------------------------------------------------------
 * Funktion: bitfile_open
 * ------------------------------------------------------------------------ */
BITFILE *bitfile_open(char* path, BOOL w)
{
    BITFILE *fd = malloc(sizeof(BITFILE));
    ASSERT_ALLOC(fd)
    memset(fd, 0, sizeof(BITFILE));
    
    fd->fd = fopen(path, w?"wb":"rb");
    
    if(fd->fd == NULL)
    {
        free(fd);
        return NULL;
    }
    
    fd->write_mode = w;
    fd->buffer_index = w?0:8;
    
    return fd;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_close
 * ------------------------------------------------------------------------ */
void bitfile_close(BITFILE **fd)
{
    if((*fd)->write_mode && (*fd)->buffer_index != 0)
    {
        bitfile_flush_write(*fd);
    }

    fclose((*fd)->fd);
    free(*fd);
    *fd = NULL;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_fill_buffer
 * ------------------------------------------------------------------------ */
static void bitfile_fill_buffer(BITFILE *fd)
{
    int character = fgetc(fd->fd);
    
    fd->buffer_index = 0;
    
    if (character == EOF)
    {
        fd->eof = TRUE;
        fd->buffer = 0;
    }
    else
    {
    	fd->buffer = (BYTE)character;
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_read_bit
 * ------------------------------------------------------------------------ */
BOOL bitfile_read_bit(BITFILE *fd)
{
    BOOL bit;
    
    if(fd->write_mode)
    {
        fprintf(stderr, "Datei im schreibe Modus geöffnet, kann nicht lesen.\n");
        exit(EXIT_FAILURE);
    }
    
    if(fd->buffer_index > 7)
    {
        bitfile_fill_buffer(fd);
    }
    
    bit = (fd->buffer >> (7-fd->buffer_index)) & 0x01;
    
    fd->buffer_index++;
    
    return bit;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_read_byte
 * ------------------------------------------------------------------------ */
BYTE bitfile_read_byte(BITFILE *fd)
{
	BYTE retval = 0;
	int i;
	for (i = 0; i < 8; i++)
	{
		retval = (retval << 1) | bitfile_read_bit(fd);
	}
	return retval;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_read_bitarray
 * ------------------------------------------------------------------------ */
BITARRAY *bitfile_read_bitarray(BITFILE *fd, int length)
{
    BITARRAY *ba = bitarray_new();
    while(length > 0 && !bitfile_is_eof(fd))
    {
        bitarray_push(ba, bitfile_read_bit(fd));
        length--;
    }
    if(bitfile_is_eof(fd))
    {
        /* das letzte bit war EOF */
        bitarray_pop(ba);
    }
    
    return ba;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_write_buffer_to_file
 * ------------------------------------------------------------------------ */
static void bitfile_write_buffer_to_file(BITFILE *fd)
{
    int wv = fputc(fd->buffer, fd->fd);
    
    if(wv == EOF)
    {
        fprintf(stderr, "Fehler beim Schreiben. Festplatte vol?\n");
        exit(EXIT_FAILURE);
    }
    
    fd->buffer = 0;
    fd->buffer_index = 0;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_write_bit
 * ------------------------------------------------------------------------ */
void bitfile_write_bit(BITFILE *fd, BOOL bit)
{
    if(!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
    
    fd->buffer = (fd->buffer << 1)| bit;
    fd->buffer_index++;
    
    if(fd->buffer_index > 7)
    {
        bitfile_write_buffer_to_file(fd);
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_write_byte
 * ------------------------------------------------------------------------ */
void bitfile_write_byte(BITFILE *fd, BYTE byte)
{
    int i;
    if(!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < 8; i++)
    {
        bitfile_write_bit(fd, (byte & 128) == 128);
        byte = byte << 1;
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_write_bitarray
 * ------------------------------------------------------------------------ */
void bitfile_write_bitarray(BITFILE *fd, BITARRAY *ba)
{
    unsigned int i;
    if (!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < bitarray_length(ba); i++)
    {
        bitfile_write_bit(fd, bitarray_get_bit(ba, i));
    }
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_is_eof
 * ------------------------------------------------------------------------ */
BOOL bitfile_is_eof(BITFILE *fd)
{
    return fd->eof;
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_seek
 * ------------------------------------------------------------------------ */
int bitfile_seek(BITFILE *fd, long int offset, int origin)
{
    if(fd->write_mode)
    {
        fd->buffer = 0;
        fd->buffer_index = 0;
    }
    else
    {
        fd->buffer_index = 8;
    }
    fd->eof = FALSE;
    return fseek(fd->fd, offset, origin);
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_flush_write
 * ------------------------------------------------------------------------ */
void bitfile_flush_write(BITFILE *fd)
{
    BYTE buffer;
    
    if(!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
    
    buffer = fd->buffer << (8 - fd->buffer_index);
    fputc(buffer, fd->fd);
    bitfile_seek(fd, -1, SEEK_CUR);
}


/* ---------------------------------------------------------------------------
 * Funktion: bitfile_last_read_was_error
 * ------------------------------------------------------------------------ */
BOOL bitfile_last_read_was_error(BITFILE *fd)
{
    return ferror(fd->fd);
}
