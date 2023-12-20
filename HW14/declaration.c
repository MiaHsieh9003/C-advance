#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
typedef char my_int[MAX];

void my_add(my_int result, my_int input1, my_int input2);
void my_number_print(my_int result);
void trans_from_string(my_int input, my_int input_string);

int main()
{
    my_int input1;
    my_int input2;
    my_int result;
    while (1)
    {
        for (int i = 0; i < MAX; i++)
        {
            input1[i] = 0;
            input2[i] = 0;
            result[i] = 0;
        }
        printf("Please give a number less than 4: ");
        scanf("%4s", input1);
        printf("Please give another number less than 4: ");
        scanf("%4s", input2);
        my_add(result, input1, input2);
        my_number_print(result);
    }
}

void my_add(my_int result, my_int input1, my_int input2)
{
    unsigned char carry = 0;
    unsigned char digit_sum = 0;
    int index1 = MAX - 1;
    int index2 = MAX - 1;

    while (input1[index1] == 0)
    {
        index1--;
    }
    while (input2[index2] == 0)
    {
        index2--;
    }
    for (unsigned int j = 0; j < MAX; j++)
    {
        digit_sum = 0;
        if (index1 >= 0 && input1[index1] <= '9' && input1[index1] >= '0')
        {
            digit_sum += (input1[index1] - '0');
        }
        if (index2 >= 0 && input2[index2] <= '9' && input2[index2] >= '0')
        {
            digit_sum += (input2[index2] - '0');
        }
        if (j < MAX)
        {
            digit_sum += carry;
            result[j] = (digit_sum % 10) + '0';
            carry = digit_sum / 10;
            if (j == MAX - 1 && carry != 0)
            {
                printf("Overflow!\n");
                result[0] = -1;
                return;
            }
            index1--;
            index2--;
        }
        else
        {
            result[j] = 0;
        }
    }
}

void my_number_print(my_int result)
{
    int index = MAX - 1;
    if (result[0] == -1)
    {
        return;
    }
    while (result[index] == '0')
    {
        index--;
    }

    printf("The add result: ");
    for (int i = index; i >= 0; i--)
    {
        printf("%c", result[i]);
    }
    printf("\n");
}
