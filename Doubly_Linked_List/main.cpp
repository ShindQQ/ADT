#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Node
{
    int data;
    Node* next;
    Node* previous;
};

struct List
{
    int size;
    Node* head;
    Node* end;
};

List* createList(int data);
Node* listAddEnd(List* list, int data);
Node* listAddStart(List* list, int data);
Node* listAddAfter(List* list, int data, int num_after);
Node* deleteListEnd(List* list);
Node* deleteListHead(List* list);
Node* deleteListData(List* list, int data);
List* deleteList(List* list);
Node* findNode(List* list, int data);
void printList(List* list);
int listLength(List* list);
bool checkListExist(List* list);
List* reverseDoublyLinkedList(List* list);

int main()
{
    List* list = NULL;
    list = createList(0);

    listAddEnd(list, 1);
    printList(list);
    printf("List end: %d\n", list->end->data);
    puts("");

    listAddEnd(list, 2);
    printList(list);
    printf("List end: %d\n", list->end->data);
    puts("");

    listAddAfter(list, 20, 2);
    listAddEnd(list, 200);
    printList(list);
    printf("List end: %d\n", list->end->data);
    puts("");

    list->head = listAddStart(list, 10);
    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    reverseDoublyLinkedList(list);
    printf("Reversed List:\n");
    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    deleteListEnd(list);
    list->head = deleteListHead(list);
    list->head = deleteListData(list, 1);

    printList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
    puts("");

    printf("Find node with data 20: %p, Find node with data -100: %p\n", findNode(list, 20), findNode(list, -100));

    list = deleteList(list);
    printList(list);
    if (list != NULL)
    {
        printf("%d %d", list->head, list->size); // error beacause of unexisting of List
    }
    return 0;
}

List* createList(int data)
{
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->data = data;
    new_node->previous = NULL;
    new_node->next = NULL;

    new_list->size = 1;
    new_list->head = new_node;
    new_list->end = new_list->head;

    return new_list;
}

Node* listAddEnd(List* list, int data)
{
    if (checkListExist(list))
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

    Node* temp_last = list->end;
    Node* temp_ptr = temp_last->next;

    temp_last->next = new_node;
    new_node->next = temp_ptr;
    new_node->previous = temp_last;

    if (temp_ptr != NULL)
    {
        temp_ptr->previous = new_node;
    }

    list->size++;
    list->end = new_node;

    return new_node;
}

Node* listAddStart(List* list, int data)
{
    if (checkListExist(list))
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

    if (list->size == 0)
    {
        new_node->previous = new_node;
        new_node->next = NULL;
    }
    else
    {
        list->head->previous = new_node;
        new_node->next = list->head;
        new_node->previous = NULL;
    }

    list->size++;

    return new_node;
}

Node* listAddAfter(List* list, int data, int num_after)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* current = list->head;
    while (current->data != num_after)
    {
        if (current->next == NULL)
        {
            return NULL;
        }

        current = current->next;
    }

    Node* temp_ptr = list->end;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }
    new_node->data = data;

    if (current == temp_ptr)
    {
        new_node->next = NULL;
        temp_ptr = new_node;
    }
    else
    {
        new_node->next = current->next;
        current->next->previous = new_node;
    }

    new_node->previous = current;
    current->next = new_node;

    int check_end = 0;
    if (list->end->data == num_after)
    {
        check_end = 1;
    }

    if (check_end == 1)
    {
        list->end = new_node;
    }

    list->size++;

    return new_node;
}

Node* deleteListEnd(List* list)
{
    if (checkListExist(list) || list->size == 0)
    {
        return NULL;
    }

    Node* temp_node = list->end;
    Node* deleting = temp_node;

    if (list->head->next == NULL)
    {
        list->head = NULL;
    }
    else
    {
        temp_node->previous->next = NULL;
    }

    temp_node = temp_node->previous;

    list->size--;
    list->end = temp_node;

    free(deleting);

    return temp_node;
}

Node* deleteListHead(List* list)
{
    if (checkListExist(list) || list->size == 0)
    {
        return NULL;
    }

    Node* temp_node = list->head;
    Node* temp_ptr = list->end;

    if (list->head->next == NULL)
    {
        temp_ptr = NULL;
    }
    else
    {
        list->head->next->previous = NULL;
    }

    list->head = list->head->next;
    list->size--;

    free(temp_node);

    return list->head;
}

Node* deleteListData(List* list, int data)
{
    if (checkListExist(list) || list->size == 0)
    {
        return NULL;
    }
    else if (findNode(list, data) == NULL)
    {
        return NULL;
    }

    Node* temp_node = list->head;
    Node* previous_tmp_node = temp_node;

    if (data == list->head->data)
    {
        list->head = deleteListHead(list);
    }
    else if (data == list->end->data)
    {
        deleteListEnd(list);
    }
    else
    {
        while (temp_node->data != data)
        {
            previous_tmp_node = temp_node;
            temp_node = temp_node->next;
        }
        previous_tmp_node->next = temp_node->next;
        temp_node->next->previous = previous_tmp_node;
        free(temp_node);
        list->size--;
    }

    return list->head;
}

List* deleteList(List* list)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    while (list->size != 0)
    {
        list->head = deleteListHead(list);
    }

    free(list);

    return NULL;
}

Node* findNode(List* list, int data)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* temp_ptr = list->head;

    while (temp_ptr != NULL)
    {
        if (temp_ptr->data == data)
        {
            return temp_ptr;
        }
        temp_ptr = temp_ptr->next;
    }

    return NULL;
}

void printList(List* list)
{
    if (checkListExist(list) || list->size == 0)
    {
        return;
    }

    Node* printed = list->head;

    while (printed != NULL)
    {
        printf("Data: %d;\n", printed->data);
        printed = printed->next;
    }
}

int listLength(List* list)
{
    if (checkListExist(list))
    {
        return -1;
    }

    Node* temp_ptr = list->head;
    int count = 0;

    while (temp_ptr != NULL)
    {
        temp_ptr = temp_ptr->next;
        count++;
    }

    return count;
}

bool checkListExist(List* list)
{
    if (list == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

List* reverseDoublyLinkedList(List* list)
{
    if (checkListExist(list))
    {
        return NULL;
    }

    Node* temp_node = NULL;
    Node* current_node = list->head;
    Node* new_tail_node = list->head;

    while (current_node != NULL)
    {
        temp_node = current_node->previous;
        current_node->previous = current_node->next;
        current_node->next = temp_node;
        current_node = current_node->previous;
    }

    if (temp_node != NULL)
    {
        list->head = temp_node->previous;
    }

    list->end = new_tail_node;

    return list;
}
