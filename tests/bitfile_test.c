#include "testmain.h"
#include "../bitfile.h"

char *name_of_testsuit = "bitfile";

BOOL bitfile_read_bit(BITFILE *fd);
BYTE bitfile_read_byte(BITFILE *fd);
BITARRAY *bitfile_read_bitarray(BITFILE *fd, int length);
void bitfile_write_bit(BITFILE *fd, BOOL d);
void bitfile_write_byte(BITFILE *fd, BYTE d);
void bitfile_write_bitarray(BITFILE *fd, BITARRAY d);
BOOL bitfile_is_eof(BITFILE *fd);
int bitfile_seek(BITFILE *fd, long int offset, int origin);
BOOL bitfile_last_read_was_error(BITFILE *fd);

BOOL test_open_ungueltig()
{
    BITFILE *fd = bitfile_open("bitfile_open_ungueltig.txt", FALSE);
    
    return fd == NULL;
}

BOOL test_open_gueltig()
{
    BITFILE *fd = bitfile_open("franz.txt", FALSE);
    
    return fd != NULL;
}

BOOL test_close()
{
    BITFILE *fd = bitfile_open("franz.txt", FALSE);
    bitfile_close(&fd);
    
    return fd == NULL;
}

BOOL test_read_bit()
{
    BOOL result;
    BITFILE *fd = bitfile_open("franz.txt", FALSE);
    
    result = bitfile_read_bit(fd) == FALSE /* F */
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_bit(fd) == FALSE /* r */
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_bit(fd) == TRUE
        && bitfile_read_bit(fd) == FALSE;
    
    bitfile_close(&fd);
    return result;
}

BOOL test_read_byte()
{
    BOOL result;
    BITFILE *fd = bitfile_open("franz.txt", FALSE);
    
    result = bitfile_read_byte(fd) == 'F'
        && bitfile_read_bit(fd) == FALSE
        && bitfile_read_byte(fd) == ('r'<<1);
    
    bitfile_close(&fd);
    
    return result;
}

BOOL test_read_bitarray()
{
    BOOL result;
    BITARRAY *ba;
    BITFILE *fd = bitfile_open("franz.txt", FALSE);
    
    ba = bitfile_read_bitarray(fd, 17);
    
    result = bitarray_length(ba) == 17
        && bitarray_get_byte(0) == 'F'
        && bitarray_get_byte(8) == 'r'
        && bitarray_get_bit(9) == FALSE;
        
    bitarray_free(&ba);
    bitfile_close(&fd);
    
    return result;
}

testunit testsuit[] = {
    {"new bitarray", test_new},
    {"free bitarray", test_free},
    {"push ein bit", test_push_ein_bit},
    {"push mehrer bits", test_push_mehrere_bits},
    {"pushe 10 bits", test_push_10_bits},
    {"pushe ein byte", test_push_byte},
    {"pushe ein byte folgend auf mehrer bits", test_push_bits_and_bytes},
    {"get bit", test_get_bit},
    {"get byte", test_get_byte},
    {"pop bit", test_pop_bit}
};
int nr_of_unittests = 10;
