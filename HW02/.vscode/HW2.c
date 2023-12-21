#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    int n = atoi(argv[0]);
    
    for(int j=1;j<n;j++){
        char temp = **(argv+j);
        **(argv+j) = **(argv+n+n+j);
        **(argv+n+j) = temp;
    }
    for(int k=1;k<n;k++){
        char temp2 = **(argv+k*n);
        **(argv+k*n) = **(argv+k*n+2);
        **(argv+k*n+2) = temp2;
    }
    for(int m=1;m<n*n;m++){
        printf("%d ",**(argv+m));
        if(m%n == 0) printf("\n");
    }
    
}
