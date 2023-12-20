
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

int tqueue_enqueue(tQueue *queue, int id, int score, int type){
    tQueueNode *queue_node;
    void *newptr = NULL;
    int mem_location;

    queue_node = (tQueueNode *)malloc(sizeof(tQueueNode));
    our_malloc(type, (void *)&newptr, &mem_location);

    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }
}

int enqueue_node(tQueue *queue, int id, int score, int data_type)
{
    tQueueNode *newptr = NULL;
    tQueueSmall *smallptr = (tQueueSmall *)malloc(sizeof(tQueueSmall));            
    tQueueLarge *largeptr = (tQueueLarge *)malloc(sizeof(tQueueLarge));
    int mem_location;        
    our_malloc ( data_type, (void *)&newptr, &mem_location);
    if (newptr == NULL)
    {
        printf("    Enqueue False!!! \n");
        return 0;
    }else{
        if(data_type == TYPE_SMALL){
            smallptr->id = id;
            smallptr->score = score;
            smallptr->location = mem_location;
            newptr->content = smallptr;
        }else{
            largeptr->id = id;
            largeptr->score[0] = score;
            largeptr->location = mem_location;
            newptr->content = largeptr;
        }
        newptr->data_type = (data_type+1);
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
    if(target->prev){
        target->prev->next = target->next;
    }
    if(target->next){
        target->next->prev = target->prev;
    }
    queue->count--;
    if(target ->data_type == TYPE_SMALL){
        our_free(data_type, ((tQueueSmall *)(target->content))->location);
    }else{
        our_free(data_type, ((tQueueLarge *)(target->content))->location);
    }
}

tQueueNode * find_target_node(tQueue *queue, int id, int data_type)
{
    tQueueNode *tar =  queue->front;

    while(tar != NULL)
    {
        if(tar->data_type == TYPE_SMALL){
            if(id != ((tQueueSmall *)(tar->content))->id || ((tar->data_type-1) != data_type)) {//
                tar = tar->next;
            }else{
                printf("    target type: %d, location: %d, id: %d\n", tar->data_type, ((tQueueSmall *)(tar->content))->location, ((tQueueSmall *)(tar->content))->id);
                if(tar->next != NULL && tar->next->data_type == TYPE_SMALL){
                    printf("    target next type: %d, location: %d, id: %d\n", tar->next->data_type, ((tQueueSmall *)(tar->next->content))->location, ((tQueueSmall *)(tar->next->content))->id);
                }else if (tar->next && tar->next->data_type == TYPE_LARGE){                    
                    printf("    target next type: %d, location: %d, id: %d\n", tar->next->data_type, ((tQueueLarge *)(tar->next->content))->location, ((tQueueLarge *)(tar->next->content))->id);
                }                
                return tar;
            }
        }else{
            if(id != ((tQueueLarge *)(tar->content))->id || ((tar->data_type-1) != data_type)) {//
                tar = tar->next;
            }else{
                printf("    target type: %d, location: %d, id: %d\n", tar->data_type, ((tQueueLarge *)(tar->content))->location, ((tQueueLarge *)(tar->content))->id);
                if(tar->next != NULL && tar->next->data_type == TYPE_SMALL){
                    printf("    target next type: %d, location: %d, id: %d\n", tar->next->data_type, ((tQueueSmall *)(tar->next->content))->location, ((tQueueSmall *)(tar->next->content))->id);
                }else if (tar->next && tar->next->data_type == TYPE_LARGE){                    
                    printf("    target next type: %d, location: %d, id: %d\n", tar->next->data_type, ((tQueueLarge *)(tar->next->content))->location, ((tQueueLarge *)(tar->next->content))->id);
                }                
                return tar;
            }
        }

    }
    return NULL;
}


void print_queue (tQueue *queue)
{
    int i;
    tQueueNode *target = queue->front;

    printf("      type mixed queue: ");    
    for (i = 0; i < queue->count; i++)
    {
        if(target->data_type == TYPE_SMALL){
            printf ("%d,%d(%d,%d) ", ((tQueueSmall *)(target->content))->id, ((tQueueSmall *)(target->content))->score, target->data_type, ((tQueueSmall *)(target->content))->location);
            fflush(stdout);
        }else{
            printf ("%d,%d(%d,%d) ", ((tQueueLarge *)(target->content))->id, ((tQueueLarge *)(target->content))->score[0], target->data_type, ((tQueueLarge *)(target->content))->location);
            fflush(stdout);
        }
        
        target = target->next;
    }
    printf("\n");
}