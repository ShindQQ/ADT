#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Node
{
	int data;
	Node* next;
};

struct Queue
{
	int size;
	Node* head;
	Node* end;
};

Queue* createQueue();
Node* addQueue(Queue* queue, int data);
int deleteQueueHead(Queue* queue);
Queue* deleteQueue(Queue* queue);
void printQueue(Queue* queue);
int queueLength(Queue* queue);
bool checkQueueExist(Queue* queue);
Queue* reverseQueue(Queue* queue);

int main()
{
	Queue* queue = NULL;
    queue = createQueue();

    addQueue(queue, 0);
    addQueue(queue, 1);
    addQueue(queue, 2);

    printQueue(queue);
    printf("Queue end: %d\n", queue->end->data);
    printf("Size of queue: %d, Function size of list: %d;\n", queue->size, queueLength(queue));
    puts("");

    reverseQueue(queue);
    printf("Reversed Queue:\n");
    printQueue(queue);
    printf("Queue end: %d\n", queue->end->data);
    printf("Size of queue: %d, Function size of list: %d;\n", queue->size, queueLength(queue));
    puts("");

    printf("Deleted data from head: %d;\n", deleteQueueHead(queue));
    printQueue(queue);
    printf("Queue end: %d\n", queue->end->data);
    printf("Size of queue: %d, Function size of list: %d;\n", queue->size, queueLength(queue));
    puts("");

    queue = deleteQueue(queue);
    printQueue(queue);
    if (queue != NULL)
    {
        printf("Queue end: %d\n", queue->end->data);
        printf("Size of queue: %d, Function size of list: %d;\n", queue->size, queueLength(queue));
        puts("");
    }
	return 0;
}

Queue* createQueue()
{
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));
    if (!new_queue)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_queue->head = new_queue->end = NULL;
    new_queue->size = 0;

    return new_queue;
}

Node* addQueue(Queue* queue, int data)
{
    if (checkQueueExist(queue))
    {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (queue->head)
    {
        queue->end->next = new_node;
    }
    queue->size++;
    queue->end = new_node;

    if (!queue->head)
    {
        queue->head = queue->end;
    }

    return new_node;
}

int deleteQueueHead(Queue* queue)
{
    if (checkQueueExist(queue) || queue->size == 0)
    {
        return NULL;
    }

    int data_from_head = queue->head->data;
    Node* temp_deleting = queue->head;

    queue->head = queue->head->next;
    free(temp_deleting);
    queue->size--;

    return data_from_head;
}

Queue* deleteQueue(Queue* queue)
{
    if (checkQueueExist(queue))
    {
        return NULL;
    }

    while (queue->size != 0)
    {
        deleteQueueHead(queue);
    }

    free(queue);

    return NULL;
}

void printQueue(Queue* queue)
{
    if (checkQueueExist(queue) || queue->size == 0)
    {
        return;
    }

    Node* printed = queue->head;

    do
    {
        printf("Data: %d;\n", printed->data);
        printed = printed->next;
    } while (printed != NULL);
}

int queueLength(Queue* queue)
{
    if (checkQueueExist(queue))
    {
        return -1;
    }

    Node* temp_ptr = queue->head;
    int count = 0;

    do
    {
        temp_ptr = temp_ptr->next;
        count++;
    } while (temp_ptr != NULL);

    return count;
}

bool checkQueueExist(Queue* queue)
{
    if (queue == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Queue* reverseQueue(Queue* queue)
{
    if (checkQueueExist(queue))
    {
        return NULL;
    }

    Node* previous_node = NULL;
    Node* current_node = queue->head;
    Node* next_node = NULL;
    Node* new_tail_node = queue->head;

    while (current_node != NULL)
    {
        next_node = current_node->next;
        current_node->next = previous_node;
        previous_node = current_node;
        current_node = next_node;
    }

    queue->head = previous_node;
    queue->end = new_tail_node;

    return queue;
}