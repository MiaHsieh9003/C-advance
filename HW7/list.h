// HW7 112598031 謝天心

#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>

// define node 
typedef struct num_storage{
    int number;
    struct num_storage *next;    
    struct num_storage *bef;    
}tNumStorage;

// define head
typedef struct num_stor_head{
    int counts;
    struct num_storage *head;
    struct num_storage *tail;
}tNumStorHead;

tNumStorHead* initial_list(tNumStorHead *list);
void list_print(tNumStorHead *list);
void list_add_node(tNumStorHead *list,tNumStorage *tar_ptr, tNumStorage *new_ptr, int tar_location);
void list_del_node(tNumStorHead *list, int choose_tar);

#endif
