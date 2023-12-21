#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL 200

int comp_inc (char x, char y)
{
    return x-y;
}

int comp_dec (char x, char y)
{
    return y-x;
}

typedef int (*CompareFunc)(char, char);
void bubble_sort(char *buf, int length, CompareFunc compare)
{
    int i, j;
    char tmp;

    for (i = 0; i< (length - 1); i++)
    {
        for (j = i; j< length; j++)
        {
            if (compare(buf[i] , buf[j]) > 0 )
            {
                tmp = buf[i];
                buf[i] = buf[j];
                buf[j] = tmp;   
            }
        }
    }
}

void print_result (char *buf)
{
    printf("    Result: %s \n", buf);
}

int main (void)
{
    int i, flag, length;
    char *buf = (char *)malloc (TOTAL * sizeof(char));
    CompareFunc compare;

    while (1)
    {        
        //menu 
        printf("Please enter (0) increasing or (1) descesing sort: ");
        scanf("%d", &flag);
        if (flag < 0 || flag > 1)
        {
            printf("ERROR: no such option! \n\n");
            continue;
        }
        
        printf("  Please enter a string: ");
        scanf("%s", buf);
        length = strlen(buf);

        //here you can modify to function pointer array
        if(flag){
            compare = comp_dec;
        }else{
            compare = comp_inc;
        }
        bubble_sort(buf, length, compare);
        print_result(buf);
    }
}

