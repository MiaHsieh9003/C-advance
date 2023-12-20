#include "stack.h"

tStack *create_stack(void)
{
   tStack * stack = (tStack *)malloc(sizeof(tStack));
   stack->count = 0;
   stack->head = NULL;
   return stack;
}

void handle_push_operation(tStack *stack_ptr)
{
    int score=0;
    tNode *nodePtr = (tNode *)malloc(sizeof(tNode));
    if(stack_ptr->count != N){
        printf("  handle_push_operation(): enter score value: ");
        scanf("%d", &score);
        nodePtr->data_ptr->loc = 0;
        get_score_space(&(nodePtr->data_ptr));
        printf("hih\n");
        nodePtr->next  = NULL;
        if(stack_ptr->head == NULL){
            stack_ptr->head = nodePtr;
            stack_ptr->count++;
        }else{
            nodePtr->data_ptr->score = score;
            nodePtr->data_ptr->used=1;
            nodePtr->data_ptr->loc = stack_ptr->count;
            nodePtr->next = stack_ptr->head;
            stack_ptr->head = nodePtr;
            get_score_space(&(nodePtr->data_ptr));
            stack_ptr->count++;
        }
    } else { 
	    printf ("[Error]  handle_push_operation(): space full \n");
    }
    return; 
}

void handle_pop_operation(tStack *stack_ptr)
{
    tNode *nodeTemp;
	if(stack_ptr->count == 0){
	    printf ("[Error]  handle_pop_operation(): nothing in stack = \n");
    }else{
        nodeTemp = stack_ptr->head;
        for(int i=2; i<stack_ptr->count; i++){
            nodeTemp = nodeTemp->next;
        }
	  printf("  handle_pop_operation(): poped value: %d\n", nodeTemp->next->data_ptr->score);
	  return_score_space(nodeTemp->next->data_ptr->loc);
      free(nodeTemp->next);
      stack_ptr->count--;
    }	  
}

void print_stack_content(tStack *stack_ptr)
{   
    tNode *curNode;
    printf("   print_stack_content(): stack items -> ");
    curNode = stack_ptr->head;
    for(int i=1;i<stack_ptr->count;i++){
        printf("%d(%d)\n", curNode->data_ptr->score, curNode->data_ptr->loc);
    }
}

