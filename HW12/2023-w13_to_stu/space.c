 
#include "space.h"

unsigned char buffer[SMALL_ELEMENT_SIZE * NUM_SMALL_BYTE_BUF + LARGE_ELEMENT_SIZE * NUM_LARGE_BYTE_BUF];
unsigned char byte_small_buf_mask = 0;
unsigned char byte_large_buf_mask = 0;

void print_buffer_status (void)
{
    int i;
    unsigned char mask = 0x80;
  
    //print small
    printf ("      byte_small_buf_mask: ");
    for (i = 0; i< NUM_SMALL_BYTE_BUF; i++)
    {
        printf ("%d ", (byte_small_buf_mask & mask) >> (7-i));
        mask = mask >> 1;
    }
    printf ("\n");  

    //print large
    mask = 0x80;
    printf ("      byte_large_buf_mask: ");
    for (i = 0; i< NUM_LARGE_BYTE_BUF; i++)
    {
        printf ("%d ", (byte_large_buf_mask & mask) >> (7-i));
        mask = mask >> 1;
    }
    printf ("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;
    if (type == TYPE_SMALL)
    {
        if(byte_small_buf_mask == FULL){
            location = test_single_location( byte_large_buf_mask, NUM_LARGE_BYTE_BUF);
            if(location >= 0){
                set_dual_bit(&byte_large_buf_mask, location);
                *target = &buffer[SMALL_ELEMENT_SIZE * NUM_SMALL_BYTE_BUF + LARGE_ELEMENT_SIZE * location];
                *mem_location = location + 8;
            }
        }else{
            location = test_single_location( byte_small_buf_mask, NUM_SMALL_BYTE_BUF );
            if(location >= 0){
                set_single_bit(&byte_small_buf_mask, location);
                *target = &buffer[SMALL_ELEMENT_SIZE*location] ;
                *mem_location = location;
            }
        }
    }
    else
    {
        if(byte_large_buf_mask == FULL){
            location = test_dual_location( byte_small_buf_mask, NUM_SMALL_BYTE_BUF);
            if(location >= 0){
                set_dual_bit(&byte_small_buf_mask, location);
                *target = &buffer[SMALL_ELEMENT_SIZE * location];
                *mem_location = location - TYPE_LARGE;
            }
        }else{
            location = test_single_location( byte_large_buf_mask, NUM_LARGE_BYTE_BUF);
            if (location >= 0)
            {
                set_single_bit( &byte_large_buf_mask, location );
                *target = &buffer[SMALL_ELEMENT_SIZE * NUM_SMALL_BYTE_BUF + LARGE_ELEMENT_SIZE * location] ;
                *mem_location = location+8;
            }            
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
            printf("i: %d\n", i);
            return i;
        }
        set = set << 1;
    }
    return -1;
}

void set_single_bit(unsigned char *mask, int location)
{
    char set=0x01;
    for (int i = 0; i< location; i++){
        set = set << 1;
    }
    *mask = *mask | set;
    printf("mask: %d\n", *mask);
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
    for (int i = 1; i< location; i++){
        set = set << 1;
    }
    *mask = *mask | set;
}

void clear_single_bit(unsigned char *mask, int location)
{
    char set=0x01;
    for (int i = 0; i< location; i++){
        set = set << 1;
    }
    *mask = *mask & (~set);
}

void clear_dual_bit(unsigned char *mask, int location)
{
    char set=0x03;
    for (int i = 1; i< location; i++){
        set = set << 1;
    }
    *mask = *mask & (~set);
}

void our_free(int type, int mem_location)
{
    if (type == TYPE_SMALL)
    {
        if(mem_location < 8){
            clear_single_bit(&byte_small_buf_mask, mem_location);
        }else{
            clear_single_bit(&byte_large_buf_mask, mem_location - 8);
        }
    }
    else if (type == TYPE_LARGE)
    {
        if(mem_location < 8){
            clear_dual_bit(&byte_small_buf_mask, mem_location + TYPE_LARGE);
        }else{
            clear_single_bit(&byte_large_buf_mask, mem_location - 8);
        }
    }
}
