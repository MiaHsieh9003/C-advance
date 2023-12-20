#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*CallbackFunc)(char);

int hexToDec(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return 0;
}

int binToDec(char c) {
    return c - '0';
}

int convertToDecimal(char *input, CallbackFunc call) {
    int len = strlen(input);
    int result = 0, base = 0;

    if(input[0] == 'h'){
        base = 16;
    }
    else if(input[0] == 'b'){
        base = 2;
    }

    for (int i = 1; i < len; i++) {
        result = result * base + call(input[i]);
    }
    return result;
}

int main() {
    char *input = (char *)malloc(20 * sizeof(char));
    
    while (1) {
        printf("Implement a HEX and binary to decimal: ");
        scanf("%s", input);
        
        if (input[0] == 'h' || input[0] == 'b') {
            printf("result: %d\n", convertToDecimal(input, input[0] == 'h' ? hexToDec : binToDec));
        } else {
            break;
        }
    }

    free(input);
    return 0;
}
