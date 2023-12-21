// 112598031 謝天心
// 因前兩次還未被選上這門課而無法繳交，在此補交
// 此為 9/18 HW2 homework v2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main (int argc, char *argv[]){
    int all = argc-2;
    int n = sqrt(atoi(*(argv+1)));    
    int *p=0;
    int *array;
    char **ptr;
    ptr = argv+2;
    char temp[100] ;
    array = (int *)malloc(all * sizeof(int));

    // origin matrix
    for(int j=0;j<all;j++){
        printf("%s ",*(ptr+j));
        *(array+j) = atoi(*(ptr+j)); //將argv二維陣列轉變為array一維陣列
        if((j+1)%n==0)printf("\n");        
    }
    printf("\n");    

    // exchange Row0, Row3    
    for(int i=0;i<n;i++){
        int temp = *(array+i);
        *(array+i) = *(array+n+n+i);
        *(array+n+n+i) = temp;
    }   
    // print matrix(or array)
    for(int j=0;j<all;j++){
        printf("%d ",*(array+j));
        if((j+1)%n==0)printf("\n");        
    }
    printf("\n");
    
    // exchange column1, column3
    for(int k=0;k<n;k++){
        int temp = *(array+n*k);
        *(array+n*k) = *(array+n*k+2);
        *(array+n*k+2) = temp;
    }
    // print matrix(or array)
    for(int j=0;j<all;j++){
        printf("%d ",*(array+j));
        if((j+1)%n==0)printf("\n");        
    }
    printf("\n");   
}