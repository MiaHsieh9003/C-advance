
#include "queue.h"
#include "space.h"


tQueue* createQueue(void){    
    tQueue *queue;
    queue=(tQueue *) malloc (sizeof(tQueue));

    if (queue)
    {
        queue->front=NULL;
        queue->rear=NULL;  
        queue->count=0;
    }

    return queue;
}

int enqueue_node(tQueue *queue, int id, int score, int data_type)
{
    tQueueNode *newptr = NULL;
    int mem_location;
    our_malloc ( data_type+1, (void *)&newptr, &mem_location);
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }else{
        newptr->id = id;
        newptr->score = score;
        newptr->data_type = data_type;
        newptr->location = mem_location;
        // printf("new loc:%d\n",newptr->location);
        newptr->next = NULL;

        if(queue->rear == NULL){
            newptr->prev = NULL;
            queue->front = newptr;
            queue->rear = newptr;
            // queue->count = 1;
            queue->rear->next = NULL;
        }else{
            queue->rear->next = newptr;
            newptr->prev = queue->rear;
            queue->rear = newptr;
            queue->rear->next = NULL;
        }
        queue->count++;
    }
    
    return 1;
}

void dequeue_node(tQueue *queue, tQueueNode *target, int data_type)
{
    if(queue->front == target){
        queue->front = target->next;
    }
    if(queue->rear == target){
        queue->rear = target->prev;
    }
    if(target->prev != NULL){
        target->prev->next = target->next;
    }
    if(target->next != NULL){
        target->next->prev = target->prev;
    }
    queue->count--;
    our_free(data_type, target->location);
}

tQueueNode * find_target_node(tQueue *queue, int id, int data_type)
{
    tQueueNode *tar =  queue->front;

    while(tar != NULL)
    {
        if(id != tar->id || ((tar->data_type) != data_type)) {//
            tar = tar->next;
        }else{
            return tar;
        }
    }
    return NULL;
}


void print_queue (tQueue *queue)
{
    int i;
    tQueueNode *target = queue->front;

    printf("      queue content: ");    
    for (i = 0; i < queue->count; i++)
    {
        printf ("%d(%d) ", target->id, target->location);
        target = target->next;
    }
    printf("\n");
}