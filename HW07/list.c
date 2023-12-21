#include "list.h"

tNumStorHead* initial_list(tNumStorHead *list){
    list->counts = 0;
    list->head = NULL;
    list->tail = NULL;
}

void list_print(tNumStorHead *list){
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

void list_add_node(tNumStorHead *list,tNumStorage *tar_ptr, tNumStorage *new_ptr, int tar_location){

    if(tar_location == 1){    //Before the location
        if(!tar_ptr->bef){  //if insert before first number
            new_ptr->next = list->head;
            list->head->bef = new_ptr;
            list->head = new_ptr;             
        }else if(!tar_ptr->next){   //所在next為null, insert before the last number
            tar_ptr->bef->next = new_ptr;
            new_ptr->bef = tar_ptr->bef;
            tar_ptr->bef = new_ptr;
            new_ptr->next = tar_ptr; 
        }else{        
            new_ptr->next = tar_ptr;   //將new number加入bef之前
            tar_ptr->bef->next = new_ptr;
            new_ptr->bef = tar_ptr->bef;   //將bef, next pointer分別指到欲插入的位置前後
            tar_ptr->bef = new_ptr;
        }                  
    }else{  // After the location
            if(!tar_ptr->next){
                list->tail = new_ptr;
            }else{
                tar_ptr->next->bef = new_ptr;
                new_ptr->next = tar_ptr->next;
            }
            tar_ptr->next = new_ptr;
            new_ptr->bef = tar_ptr;        
    }
      
}

void list_del_node(tNumStorHead *list,int choose_tar){
    tNumStorage *tar_ptr; //target node to delete

    tar_ptr = list->head;
    if(list->counts > 1){
        if(choose_tar == 1){    //delete first number
            list->head = list->head->next;
            list->head->bef = NULL;
        }else if(choose_tar == list->counts){   //delete the last number
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
    }else{  //counts == 0
        list->head = NULL;
        list->tail = NULL;
    }
    list->counts--;      
    free(tar_ptr);          

}
