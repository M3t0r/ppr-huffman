#ifndef _BIT_ACCESS_H
#define _BIT_ACCESS_H

#include "common.h"

BOOL get_bit(BYTE *ptr, int index);
void set_bit(BYTE *ptr, int index, BOOL value);
void print_bytes(BYTE *ptr, int length);

#endif