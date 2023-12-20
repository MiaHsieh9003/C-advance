// HW4 112598031 謝天心
#include <stdio.h>
#include <stdlib.h>

// define node class
typedef struct num_storage{
    int number;
    struct num_storage *next;    
    struct num_storage *bef;    
}tNumStorage;
// define head class
typedef struct num_stor_head{
    int counts;
    struct num_storage *head;
    struct num_storage *tail;
}tNumStorHead;

void initial_list(tNumStorHead *list);
void print_list(tNumStorHead *list);
void sort_list(tNumStorHead *list,int input);
void get_input(tNumStorHead *list);       
void delete_last(tNumStorHead *list);

int main(void){
    int i;
    tNumStorHead *list;
    list = (tNumStorHead *) malloc (sizeof(tNumStorHead));
    initial_list(list);
    get_input(list);    //include get input, sort and print list
}

void initial_list(tNumStorHead *list){
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

void get_input(tNumStorHead *list){
    int intNum = 0;

    while(intNum != -1){
        printf("Input a number (-1 to exit, -2 to delete last): "); //input a number to this list
        scanf("%d",&intNum);
        if(intNum == -2){
            delete_last(list);          
        }
        else if (intNum != -1)
        {          
            sort_list(list, intNum);     
            list->counts ++;
            printf("    list->counts: %d\n",list->counts);
            print_list(list);
        }   
    }
  
}

void sort_list(tNumStorHead *list,int input){
    tNumStorage *bef_ptr = (tNumStorage *)malloc (sizeof(tNumStorage)); //before node 
    tNumStorage *next_ptr = (tNumStorage *)malloc (sizeof(tNumStorage)); //the node after current node
    tNumStorage *new_ptr = (tNumStorage *)malloc (sizeof(tNumStorage)); //new node
    tNumStorage *end_ptr = (tNumStorage *)malloc (sizeof(tNumStorage)); //the last node for assign tail
    new_ptr->number = input;
    new_ptr->next = NULL;
    new_ptr->bef = NULL;

    if(list->counts == 0){  //only one number
        list->head = new_ptr;
        list->tail = new_ptr;        
        end_ptr = new_ptr;
    }
    else{
        next_ptr = list->head;
        for(int i=0;i<=list->counts;i++){
            if(new_ptr->number <= list->head->number){   //when new number < the list head number
                list->head->bef = new_ptr;
                new_ptr->next = list->head;
                new_ptr->bef = NULL;
                list->head = new_ptr;
                break;
            }
            else{
                if(next_ptr && new_ptr->number > next_ptr->number){
                    bef_ptr = next_ptr;
                    next_ptr = next_ptr->next;
                }
                else if(next_ptr && new_ptr->number <= next_ptr->number){   //if next node is NULL or new number < next_ptr number
                    new_ptr->next = next_ptr;              
                    bef_ptr->next = new_ptr;
                    next_ptr->bef = new_ptr;
                    new_ptr->bef = bef_ptr;
                    break;
                }else{
                    new_ptr->next = NULL;              
                    bef_ptr->next = new_ptr;
                    new_ptr->bef = bef_ptr;
                    list->tail = new_ptr;
                    break;                    
                }
            }                   
        }
    }
    // printf("tail int:%d\n",list->tail->number);
}

void print_list(tNumStorHead *list){
    tNumStorage *node_ptr = list->head;

    printf("    The sorted list:  ");
    while(node_ptr != NULL){
        printf("%d ",node_ptr->number);
        node_ptr = node_ptr->next;
    }
    printf("\n\n");
}

void delete_last(tNumStorHead *list){
    if(list->counts == 0){
        printf("There is nothing to delete.\n");
    }
    else if(list->counts > 1){
        tNumStorage* tail_temp;
        tail_temp = list->tail;
        list->tail = list->tail->bef;  
        list->tail->next =NULL;  
        list->counts --;
        tail_temp->bef = NULL;
        tail_temp->next = NULL;
        free(tail_temp);
        printf("    list->counts: %d\n",list->counts);
        print_list(list);  
    }
    else{
        tNumStorage* tail_temp;
        tail_temp = list->tail;
        list->head=NULL;
        list->tail =NULL;
        list->counts = 0;
        printf("    list->counts: %d\n",list->counts);
        print_list(list);  
    }
}
