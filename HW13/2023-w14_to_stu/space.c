
#include "space.h"

unsigned char buffer[ELEMENT_SIZE*NUM_BYTE_BUF];
unsigned char byte_buf_mask[MASK_ALL_LENGH] ;

void print_buffer_status (void)
{
    int local_loc = 0;
    int index = MASK_ALL_LENGH - 1;
    int flag = 0;
    unsigned char mask = 0x80;
    printf ("       byte_buf_mask: ");
    for (int i = 0; i< NUM_BYTE_BUF; i++)
    {
        local_loc++;
        if(index == (MASK_ALL_LENGH - 1) && flag == 0){
            mask = (0x80 >> (8 - (NUM_BYTE_BUF%8)) );
            local_loc = (8 - (NUM_BYTE_BUF%8));
            flag = 1;
        }
        if((byte_buf_mask[index] & mask) != 0)
        {
            printf("1 ");
        }else{
            printf("0 ");
        }
        mask = mask >> 1;
        
        if(mask == 0x00){
            printf(", ");
            index--;
            local_loc = 0;
            mask = 0x80;
        }
    }
    printf ("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;

    if (*byte_buf_mask == (NUM_BYTE_BUF * ELEMENT_SIZE - 1)){
        return;
    }
    else
    {
        location = test_multiple_locations( byte_buf_mask, NUM_BYTE_BUF , type);
        if(location >= 0){
            *target = &buffer[ELEMENT_SIZE*location] ;
            *mem_location = location;
        }else
        {
            return;
        }
        
    }
        
}

int test_multiple_locations(unsigned char *mask, int mask_length, int x)
{
    unsigned char set = 0x01;
    int count = 0;
    int loc = 0;
    int start = 0;
    int index = 0;

    for (int i = 0; i < mask_length; i++) {
        if ((set & mask[index]) == 0) {
            count++;
            if (count == x) {
                // 找到連續 x 個 bit 為 0 ，讓他們為 1
                mask[index] = mask[index] | set;
                for(int j=count; j>0; j--){
                    mask[index] = mask[index] | set;
                    set = set >> 1;
                    if(set == 0x00){
                        index--;
                        set = 0x80;
                    }
                }
                return i;
            }
        } else {
            count = 0; // 重置计数器，因为找到的不是連續的 0
        }
        set = set << 1;
        if(set == 0x00){
            index++;
            if(index >= MASK_ALL_LENGH){
                return -1;
            }
            set = 0x01;
        }
    }
    return -1;
}

void clear_bit(unsigned char *mask, int location, int type)
{
    unsigned char set=0x01;
    int index = location/8;
    set = set << (location)%8;
    for(int i=0; i<type; i++){
        mask[index] = mask[index] & (~set);
        set = set >> 1;
        if(set == 0x00){
            index--;
            set = 0x80;
        }
    }    
}

void our_free(int type, int mem_location)
{
    clear_bit(byte_buf_mask, mem_location, type);
}
