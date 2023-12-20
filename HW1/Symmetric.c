// 112598031 謝天心
// 因前兩次還未被選上這門課而無法繳交，在此補交
// 此為 9/11 HW1 homework
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10


int main(){
	int n=0;
	int SyMatrix[MAX_SIZE][MAX_SIZE];
	bool IsSym=true;
	printf("Num of layers: ");
	scanf("%d",&n);
	printf("Is this matrix symmetic?(please input a matrix)\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d",&SyMatrix[i][j]);
		} 
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<i;j++){
			if(SyMatrix[i][j] != SyMatrix[j][i])
				IsSym=false;
		}
	}
	if(IsSym == true){
		printf("Symmetric"); 
	}else{
		printf("NOT Symmetric"); 
	}
}
