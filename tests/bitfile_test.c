#include "testmain.h"
#include "../bitfile.h"

char *name_of_testsuit = "bitfile";

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
        && bitarray_get_byte(ba, 0) == 'F'
        && bitarray_get_byte(ba, 8) == 'r'
        && bitarray_get_bit(ba, 16) == FALSE;
        
    bitarray_free(&ba);
    bitfile_close(&fd);
    
    return result;
}



testunit testsuit[] = {
    {"fehler beim öffnen", test_open_ungueltig},
    {"datei öffnen", test_open_gueltig},
    {"datei schliessen", test_close},
    {"read bit", test_read_bit},
    {"read byte", test_read_byte},
    {"read bitarray", test_read_bitarray}
};
int nr_of_unittests = 6;
