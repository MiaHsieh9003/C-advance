
#include "space.h"

unsigned char buffer[ELEMENT_SIZE*NUM_BYTE_BUF];
unsigned char byte_buf_mask = 0x00;

void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
  
    printf ("      byte_buf_mask: ");
    for (i = 0; i< NUM_BYTE_BUF; i++)
    {
        printf ("%d i:%d\n", (byte_buf_mask & mask) >> (7-i),i);
        mask = mask >> 1;
    }

    printf ("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;

    if (byte_buf_mask == FULL){
        return;
    }
    else if (type == TYPE_SMALL)
    {
        location = test_single_location( byte_buf_mask, NUM_BYTE_BUF );
        set_single_bit(&byte_buf_mask, location);
        *target = &buffer[ELEMENT_SIZE*location] ;
        *mem_location = location;
    }
    else
    {

        location = test_dual_location( byte_buf_mask, NUM_BYTE_BUF  );
        if (location >= 0)
        {
            set_dual_bit( &byte_buf_mask, location );
            *target = &buffer[ELEMENT_SIZE*location] ;
            *mem_location = location;
        }
        else
        {
            return;
        }
    }    
}

int test_single_location(unsigned char mask, int mask_length)
{
    char set=0x01;
    char bit;
    for(int i=0;i<mask_length;i++){
        bit = (set & mask);
        if(bit == 0){
            return i;
        }
        set = set << 1;
    }
    return NUM_BYTE_BUF+1;
}

void set_single_bit(unsigned char *mask, int location)
{
    char set=0x01;
    if(location == NUM_BYTE_BUF){
        return ;
    }
    for (int i = 0; i< location; i++){
        set = set << 1;
    }
    *mask = *mask | set;
}

int test_dual_location(unsigned char mask, int mask_length)
{
    char set=0x03;
    char bit;
    for(int i=1;i<mask_length;i++){
        bit = (set & mask);
        if(bit == 0){
            return i;
        }
        set = set << 1;
    }
    return -1;
}

void set_dual_bit(unsigned char *mask, int location)
{
    char set=0x03;
    if(location == NUM_BYTE_BUF){
        return ;
    }
    for (int i = 1; i< location; i++){
        set = set << 1;
    }
    *mask = *mask | set;
}

void clear_single_bit(unsigned char *mask, int location)
{
    char set=0x01;
    if(location == NUM_BYTE_BUF+1){
        return ;
    }
    for (int i = 0; i< location; i++){
        set = set << 1;
    }
    *mask = *mask & (~set);
}

void clear_dual_bit(unsigned char *mask, int location)
{
    char set=0x03;
    if(location == NUM_BYTE_BUF){
        return ;
    }
    for (int i = 1; i< location; i++){
        set = set << 1;
    }
    *mask = *mask & (~set);
}

void our_free(int type, int mem_location)
{
    if (type == TYPE_SMALL)
    {
        clear_single_bit(&byte_buf_mask, mem_location);
    }
    else if (type == TYPE_LARGE)
    {
        clear_dual_bit(&byte_buf_mask, mem_location);
    }
}
