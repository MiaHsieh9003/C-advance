#include <stdio.h>
#include <stdlib.h>
#define N 30

typedef struct num_list{
    int counts;
    int *p_list;
}tNumList;

void fill_list(tNumList *list);
void bubble_sort(tNumList *list);
void merge (tNumList *list1, tNumList *list2);
void print_list (tNumList *list);

int main(){
    tNumList *list1, *list2;
    list1 = (tNumList *) malloc (sizeof(tNumList));
    list2 = (tNumList *) malloc (sizeof(tNumList));

    //list1 輸入與排序
    printf("Please enter how many numbers in list1: ");
    scanf("%d",&(list1->counts));
    printf("    Please input %d numbers: ",list1->counts);
    fill_list(list1);
    bubble_sort(list1);

    //list2 輸入與排序
    printf("Please enter how many numbers in list2: ");
    scanf("%d",&(list2->counts));
    printf("    Please input %d numbers: ",list2->counts);
    fill_list(list2);
    bubble_sort(list2);
    
    //印出list值
    printf("sorted list1: ");
    print_list(list1);
    printf("sorted list2: ");
    print_list(list2);
    printf("merge list: ");
    merge(list1, list2);
}

void fill_list(tNumList *list){
    int *array = (int *)malloc(list->counts * sizeof(int)); //額外分配list空間存輸入值
    for(int i=0;i<list->counts;i++){
        scanf("%d",&(array[i]));
    }
    list->p_list = array;
}

void bubble_sort(tNumList *list){
    int *present;
    present = list->p_list;
    int temp=0;
    for (int i=0;i<list->counts;i++){
        for(int j=i;j<list->counts-1;j++){
            if(present[i]>present[j+1]){
                temp = present[i];
                present[i] = present[j+1];
                present[j+1] = temp;
            }
        }
    }
}

void merge(tNumList *list1, tNumList *list2){
    int list1Current=0, list2Current=0;
    int allCount;
    allCount = list1->counts + list2->counts;
    for(int k=0;k<allCount;k++){
        if(list1->p_list[list1Current]<list2->p_list[list2Current]){
            printf("%d ",list1->p_list[list1Current]);
            list1Current++;
        }else{
            printf("%d ",list2->p_list[list2Current]);
            list2Current++;
        }
    }
}

void print_list(tNumList *list){
    for(int i=0;i<list->counts;i++){
        printf("%d ",list->p_list[i]);
    }
    printf("\n");
}