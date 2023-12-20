#include <stdio.h>
#include <stdbool.h>
typedef unsigned int Int32;

int check_range_loop(Int32 input, Int32 high, Int32 low);
int check_range_no_loop(Int32 input, Int32 high, Int32 low);

int main(void)
{
    while (1)
    {
        int round=1;
        Int32 input;
        Int32 high;
        Int32 low;
        printf("Please specify the input: ");
        scanf("%x",&input);
        printf("    Please specify the high: ");
        scanf("%u",&high);
        printf("    Please specify the low: ");
        scanf("%u",&low);

        printf("check_range_loop result: %d\n",check_range_loop(input, high, low));
        printf("check_range_no_loop result %d\n",check_range_no_loop(input, high, low));
        printf("\n");
        printf("Input 1 to keep trying the next round: ");
        scanf("%d", &round);
        if(round != 1){
            break;
        }
    }
    

}

int check_range_loop(Int32 input, Int32 high, Int32 low)
{
    bool result;
    Int32 low_mask=0xFF;
    Int32 high_mask=0xFF;
    for(unsigned int j=0;j<low;j++){
        low_mask = low_mask<<1;
    }
    
    for(unsigned int i=0;i<high;i++){
        high_mask = high_mask << 1;
    }    
    
    result = (input & (~high_mask) & (low_mask));
    return result;
}

int check_range_no_loop(Int32 input, Int32 high, Int32 low){
    bool result;
    Int32 low_mask=0xFF;
    Int32 high_mask=0xFF;
    low_mask = low_mask << low;
    high_mask = high_mask << high;
    
    result = (input & (~high_mask) & (low_mask));
    return result;
}
