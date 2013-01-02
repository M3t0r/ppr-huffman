typedef struct {} BITFILE;

BITFILE bitfile_open(char* path, BOOL w);
void bitfile_close(BITFILE fd);

BOOL bitfile_read_bit(BITFILE fd);
BYTE bitfile_read_byte(BITFILE fd);
BITARRAY bitfile_read_bitarray(BITFILE fd, int length);

void bitfile_write_bit(BITFILE fd, BOOL d);
void bitfile_write_byte(BITFILE fd, BYTE d);
void bitfile_write_bitarray(BITFILE fd, BITARRAY d);



typedef struct {} BITARRAY;

BITARRAY bitarray_new();
void bitarray_free(BITARRAY ba);

void bitarray_push(BITARRAY ba, BOOL d);
void bitarray_push_byte(BITARRAY ba, BYTE d);
BOOL bitarray_pop(BITARRAY ba);

int bitarray_size(BITARRAY ba);
BOOL bitarray_get_bit(BITARRAY ba, int index);
BYTE bitarray_get_byte(BITARRAY ba, int index);
