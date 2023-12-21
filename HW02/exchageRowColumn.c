// 112598031 謝天心
// 因前兩次還未被選上這門課而無法繳交，在此補交
// 此為 9/18 HW2 homework
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main (int argc, char *argv[]){
    int n = sqrt(atoi(argv[1]));    
    int *p=0;
    char **ptr;
    ptr = argv+2;
    char temp[100] ;
    
    // origin matrix
    for(int j=0;j<argc-2;j++){
        printf("%s ",*(ptr+j));
        if((j+1)%n==0)printf("\n");        
    }
    printf("\n");

    // exchange Row0, Row3    
    for(int i=0;i<n;i++){
        // char *temp ;
        // temp = *(ptr+i);
        // *(ptr+i) = *(ptr+n+n+i);
        // *(ptr+n+n+i) = *(ptr+i);
        // *(ptr+i) = temp;
        strcpy(temp,"");
        strcpy(temp,*(ptr+i));
        strcpy(*(ptr+i),*(ptr+n+n+i));
        strcpy(*(ptr+n+n+i),temp);
    }   
    for(int j=0;j<argc-2;j++){
        printf("%s ",*(ptr+j));
        if((j+1)%n==0)printf("\n");        
    }
    printf("\n");

    //exchange column0, column3 
    for(int k=0;k<n;k++){
        strcpy(temp,"");
        strcpy(temp,*(ptr+n*k));
        strcpy(*(ptr+n*k),*(ptr+n*k+2));
        strcpy(*(ptr+n*k+2),temp);
    }
    for(int j=0;j<argc-2;j++){
        printf("%s ",*(ptr+j));
        if((j+1)%n==0)printf("\n");        
    }

    
}