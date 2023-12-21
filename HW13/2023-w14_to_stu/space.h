#ifndef __SPACE__
#define __SPACE__

#include "main.h"

#define NUM_BYTE_BUF      500
#define ELEMENT_SIZE      32
#define MASK_ALL_LENGH (((NUM_BYTE_BUF%8) == 0)?NUM_BYTE_BUF/8 :NUM_BYTE_BUF/8+1)

void print_buffer_status(void);
void our_malloc(int type, void **target, int *mem_location);
void our_free(int type, int mem_location);  
int test_multiple_locations(unsigned char *mask, int mask_length, int x);
void clear_bit(unsigned char *mask, int location, int type);

#endif