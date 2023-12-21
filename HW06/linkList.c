// HW5 112598031 謝天心
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
void get_input(tNumStorHead *list);       
void add_node(tNumStorHead *list);
void delete_node(tNumStorHead *list);

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
        printf("1. Add a number or 2. Delete a number: "); //input a number to this list
        scanf("%d",&intNum);
        if (intNum == 1)    //Add a number
        {           
            add_node(list);
            printf("count: %d\n",list->counts);
            print_list(list);
        }   
        else if(intNum == 2){      //Delete a number
            delete_node(list);
            printf("count: %d\n",list->counts);
            print_list(list);            
        }
        else{
            printf("No such choose !\n");
        }
    }
  
}

void delete_node(tNumStorHead *list){
    int choose_tar =0; //choose the action   
    tNumStorage *tar_ptr = NULL; //taeget node to delete

    printf("    Specify a target location: ");
    scanf("%d",&choose_tar);
    if(choose_tar>list->counts || choose_tar<1){
        printf("Not an exist number!\n");
        return;
    }
    else{
        tar_ptr = list->head;
        if(list->counts > 1){
            if(choose_tar == 1){    //delete first number
                list->head = list->head->next;
                list->head->bef = NULL;
            }else if(choose_tar == list->counts){   //delete the last number
                printf("delete last\n");
                tar_ptr = list->tail;
                list->tail = list->tail->bef;
                list->tail->next = NULL;
            }else{
                for(int i=1; i<(choose_tar); i++){
                    tar_ptr = tar_ptr->next;
                }
                tar_ptr->bef->next = tar_ptr->next;
                tar_ptr->next->bef = tar_ptr->bef;                
            }
        }else{
            list->head = NULL;
            list->tail = NULL;
        }
        list->counts--;      
        free(tar_ptr);      
    }

}

void add_node(tNumStorHead *list){
    int input=0;
    int tar_location =0; //choose the action number
    int tar_loc_num=0;
    tNumStorage *new_ptr = (tNumStorage *)malloc (sizeof(tNumStorage)); //new node
    tNumStorage *bef_ptr = NULL; //before node 
    tNumStorage *next_ptr = NULL; //the node after current node

    printf(" Add a number: ");  //input a number to add
    scanf("%d",&input);

    new_ptr->number = input;
    new_ptr->next = NULL;
    new_ptr->bef = NULL;

    if(list->counts == 0){
        list->counts ++;    //list number add 1
        list->head = new_ptr;
        list->tail = new_ptr;   
    }else{
        printf("    Specify a target location: ");
        scanf("%d",&tar_location);
        
        if(tar_location > list->counts || tar_location < 1){  //out of list range
            printf("Out of range, please try again!\n");
            return;
        }else{
            list->counts ++;    //list number add 1
            next_ptr = list->head;
            for(int i=0 ; i<(tar_location) ; ++i){
                bef_ptr = next_ptr;                
                next_ptr = next_ptr->next;
                tar_loc_num = bef_ptr->number;  //bef_ptr目前指向target location
            }

            printf("    1.Before or 2. After the location '%d': ", tar_loc_num);
            scanf("%d", &tar_location);
            printf("\n");
            if(tar_location == 1 || tar_location == 2)
            { 
                if(tar_location == 1){    //Before the location
                    if(!bef_ptr->bef){  //if insert before first number
                        new_ptr->next = list->head;
                        list->head->bef = new_ptr;
                        list->head = new_ptr;
                        return;                          
                    }else if(!next_ptr){   //next為null, insert before the last number
                        bef_ptr->bef->next = new_ptr;
                        new_ptr->bef = bef_ptr->bef;
                        bef_ptr->bef = new_ptr;
                        new_ptr->next = bef_ptr; 
                        return;
                    }else{
                        bef_ptr = bef_ptr->bef; //將bef, next pointer調到欲插入的位置前後
                        next_ptr = next_ptr->bef;
                    }                  
                }else{
                    if(!next_ptr){  //insert after the last number
                        bef_ptr->next = new_ptr;
                        new_ptr->bef = bef_ptr;
                        list->tail = new_ptr;
                        return;
                    }
                }
                new_ptr->next = next_ptr;
                bef_ptr->next = new_ptr;
                new_ptr->bef = bef_ptr;
                next_ptr->bef = new_ptr;
                if(next_ptr->next == NULL){
                    list->tail = next_ptr;
                }
            }else{
                list->counts --;
                printf("Number '%d' is not a correct choose, please try again!\n", tar_location);
                return;
            }
        }
    }
}

void print_list(tNumStorHead *list){
    tNumStorage *node_ptr = list->head;

    printf("    From head --> ");
    while(node_ptr != NULL){
        printf("%d ",node_ptr->number);
        node_ptr = node_ptr->next;
    }
    node_ptr = list->tail;
    printf("\n    From tail --> ");
    while (node_ptr != NULL)
    {
        printf("%d ",node_ptr->number);
        node_ptr = node_ptr->bef;
    }
    printf("\n\n");
}
