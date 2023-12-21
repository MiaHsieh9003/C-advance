#include "main.h"
#include "queue.h"
#include "space.h"


int main (void)
{
    tQueue *queue;
    int operation;
    tQueueNode *target_node;
    int id, score=0, ret, type=0;
    queue = createQueue();

    while (1)
    {

        printf("\nWhich type you are going to operate? \n");
        printf("1. Add an item\n");
        printf("2. Remove an item with a specific Id\n");
        
        scanf("%d", &operation);
        
        if (operation == 1)
        {
            printf("    Enter id: ");
            scanf("%d", &id);
            printf("    specify data type (units) you want: ");
            scanf("%d", &type);
            ret = enqueue_node(queue, id, score, type);
          
            if (ret == 0)
            {
                printf("    Cannot enter to the queue\n");
            }
            print_buffer_status();
        }
        else if (operation == 2)
        {
            printf ("  Enter an ID to remove ");
            scanf("%d", &id);
            target_node = find_target_node(queue, id);
            if (target_node == NULL)
            {
                printf ("    Cannot find the target node \n");
            }
            else
            {
                dequeue_node(queue, target_node);
            }
            print_buffer_status();

        }
        else 
        {
            printf ("    No such operation \n");   
        }
        print_queue(queue);
    }

}
