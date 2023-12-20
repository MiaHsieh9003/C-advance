
#include "space.h"

unsigned char buffer[ELEMENT_SIZE*NUM_BYTE_BUF];
unsigned char byte_buf_mask[MASK_ALL_LENGH] ;

void print_buffer_status (void)
{
    int local_loc = 0;
    int index = MASK_ALL_LENGH - 1;
    int flag = 0;
    unsigned char mask = 0x80;
    printf ("      mask:%d %d\n",byte_buf_mask[0], byte_buf_mask[1]);
    printf ("      byte_buf_mask: ");
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
            index--;
            local_loc = 0;
            mask = 0x80;
        }
    }

    printf ("\n");
}

// void print_buffer_status (void)
// {
//     int local_loc =0;
//     int index = MASK_ALL_LENGH;
//     int flag = 0;
//     unsigned char mask = 0x80;
//     printf("mask:%d %d\n",byte_buf_mask[0], byte_buf_mask[1]);
//     printf ("      byte_buf_mask: ");
//     for (int i = 0; i< NUM_BYTE_BUF; i++)
//     {
//         local_loc++;
//         if(index == MASK_ALL_LENGH && flag == 0){
//             mask = (0x80 >> (8 - (NUM_BYTE_BUF%8)) );
//             local_loc = (8 - (NUM_BYTE_BUF%8));
//             printf("max len mask:%d\n",mask);
//             flag = 1;
//         }
//         printf ("%d , loc:%d\n", (byte_buf_mask[index] & mask) >> (7-local_loc), local_loc);
//         printf("byte_buf_mask[index] & mask:%d\n",byte_buf_mask[index] & mask);
//         mask = mask >> 1;        
//         if(mask == 0x00){
//             index--;
//             local_loc = 0;
//             mask = 0x80;
//         }
//     }
//     printf ("\n");
// }

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
            // printf("ELEMENT_SIZE*location: %d\n",ELEMENT_SIZE*location);
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
    printf("MASK_ALL_LENGH:%d\n", MASK_ALL_LENGH);

    for (int i = 0; i < mask_length; i++) {
        if ((set & mask[index]) == 0) {
            // if(set == 0x01){
            //     printf("set 01!!\n");
            // }
            printf("in for, count:%d\n", count);
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
                return start+count-1;
            }
        } else {
            start ++;
            count = 0; // 重置计数器，因为找到的不是連續的 0
        }
        set = set << 1;
        if(set == 0x00){
            printf("set & mask[index] & i: %d %d %d\n",set, mask[index], i);
            index++;
            if(index >= MASK_ALL_LENGH){
                return -1;
            }
            printf("index:%d\n", index);
            set = 0x01;
        }
    }
    return -1;
}


void set_bit(unsigned char * mask, int location){
    unsigned char set[NUM_BYTE_BUF/8 + 1] = {0};
    set[NUM_BYTE_BUF/8 ] = 0x01;
    if(location == NUM_BYTE_BUF){
        return;
    }
    for(int i=0; i<location; i++){
        *set = *set << 1;
    }
    *mask = *mask | *set;
}

void set_single_bit(unsigned char *mask, int location)
{
    char set=0x01;
    if(location == NUM_BYTE_BUF+1){
        return ;
    }
    for (int i = 0; i< location; i++){
        set = set << 1;
    }
    *mask = *mask | set;
}
void set_dual_bit(unsigned char *mask, int location)
{
    char set=0x03;
    if(location == NUM_BYTE_BUF+1){
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
    if(location == NUM_BYTE_BUF+1){
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
        clear_single_bit(byte_buf_mask, mem_location);
    }
    else if (type == TYPE_LARGE)
    {
        clear_dual_bit(byte_buf_mask, mem_location);
    }
}
