/*****************************************************************************
 * Includes
 *****************************************************************************/
#include "bitfile.h"
#include <stdio.h>
#include <string.h>

static void bitfile_fill_buffer(BITFILE *fd);

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
    fd->buffer_index = 8;
}

void bitfile_close(BITFILE **fd)
{
    fclose(*(fd)->fd);
    free(*fd);
    *fd = NULL;
}

static void bitfile_fill_buffer(BITFILE *fd)
{
    int character = fgetc(fd->fd);
    
    fd->buffer_index = 0;
    fd->buffer = character;
    
    fd->eof = (character == EOF);
}

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

BYTE bitfile_read_byte(BITFILE *fd)
{
    BYTE byte = 0;
    int index;
    
    if(fd->write_mode)
    {
        fprintf(stderr, "Datei im schreibe Modus geöffnet, kann nicht lesen.\n");
        exit(EXIT_FAILURE);
    }
    
    if(fd->buffer_index > 7)
    {
        bitfile_fill_buffer(fd);
    }
    
    index = fd->buffer_index
    
    byte = fd->buffer << index;
    bitfile_fill_buffer(fd);
    byte |= (fd->buffer >> (8-index)) & ~(0xFF<<index);
    fd->buffer_index = 8-index;
    
    return byte;
}

BITARRAY *bitfile_read_bitarray(BITFILE *fd, int length)
{
    BITARRAY *ba = bitarray_new();
    
    if(fd->write_mode)
    {
        fprintf(stderr, "Datei im schreibe Modus geöffnet, kann nicht lesen.\n");
        exit(EXIT_FAILURE);
    }
    
    while(length > 7)
    {
        bitarray_push_byte(ba, bitfile_read_byte(fd));
        length -= 8;
    }
    while(index > 0)
    {
        bitarray_push(ba, bitfile_read_bit(fd));
        length--;
    }
    
    return ba;
}

void bitfile_write_bit(BITFILE *fd, BOOL d)
{
    
    
    if(!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
}

void bitfile_write_byte(BITFILE *fd, BYTE d)
{
    
    
    if(!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
}

void bitfile_write_bitarray(BITFILE *fd, BITARRAY d)
{
    
    
    if(!fd->write_mode)
    {
        fprintf(stderr, "Datei im lese Modus geöffnet, kann nicht schreiben.\n");
        exit(EXIT_FAILURE);
    }
}

BOOL bitfile_is_eof(BITFILE *fd)
{
    return fd->eof;
}

int bitfile_seek(BITFILE *fd, long int offset, int origin)
{
    fseek(fd->fd, offset, origin);
}

BOOL bitfile_last_read_was_error(BITFILE *fd)
{
    return ferror(fd->fd);
}
