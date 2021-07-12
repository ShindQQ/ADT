#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>

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

List* CreateList(int data);
Node* ListAddEnd(List* list, int data);
Node* ListAddStart(List* list, int data);
Node* ListAddAfter(List* list, int data, int num_after);
Node* DeleteListEnd(List* list);
Node* DeleteListHead(List* list);
Node* DeleteListData(List* list, int data);
List* DeleteList(List* list);
Node* FindNode(List* list, int data);
void PrintList(List* list);
int ListLength(List* list);

int main()
{
    List* list = NULL;
    list = CreateList(0);

    ListAddEnd(list, 1);
    PrintList(list);
    printf("List end: %d\n", list->end->data);
    puts("");

    ListAddEnd(list, 2);
    PrintList(list);
    printf("List end: %d\n", list->end->data);
    puts("");

    ListAddAfter(list, 20, 2);
    ListAddEnd(list, 200);
    PrintList(list);
    printf("List end: %d\n", list->end->data);
    puts("");

    list->head = ListAddStart(list, 10);
    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    DeleteListEnd(list);
    list->head = DeleteListHead(list);
    list->head = DeleteListData(list, 1);

    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    printf("Find node with data 1: %p, Find node with data -100: %p\n", FindNode(list, 1), FindNode(list, -100));

    list = DeleteList(list);
    PrintList(list);
    if (list != NULL)
    {
        printf("%d %d", list->head, list->size); // error beacause of unexisting of List
    }
    return 0;
}

List* CreateList(int data)
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

Node* ListAddEnd(List* list, int data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->data = data;

    Node* tmp_last = list->end;

    Node* tmp_ptr = tmp_last->next;
    tmp_last->next = new_node;
    new_node->next = tmp_ptr;
    new_node->previous = tmp_last;
    if (tmp_ptr != NULL)
    {
        tmp_ptr->previous = new_node;
    }
    list->size++;
    list->end = new_node;
    return new_node;
}

Node* ListAddStart(List* list, int data)
{
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
    }

    list->size++;
    return new_node;
}

Node* ListAddAfter(List* list, int data, int num_after)
{
    Node* current = list->head;
    while (current->data != num_after)
    {
        if (current->next == NULL)
        {
            return NULL;
        }

        current = current->next;
    }

    Node* tmp_ptr = list->end;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }
    new_node->data = data;

    if (current == tmp_ptr)
    {
        new_node->next = NULL;
        tmp_ptr = new_node;
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

Node* DeleteListEnd(List* list)
{
    Node* tmp_node = list->end;
    Node* deleting = tmp_node;

    if (list->head->next == NULL)
    {
        list->head = NULL;
    }
    else
    {
        tmp_node->previous->next = NULL;
    }

    tmp_node = tmp_node->previous;
    list->size--;
    list->end = tmp_node;
    free(deleting);
    return tmp_node;
}

Node* DeleteListHead(List* list)
{
    Node* tmp_node = list->head;

    Node* tmp_ptr = list->end;

    if (list->head->next == NULL)
    {
        tmp_ptr = NULL;
    }
    else
    {
        list->head->next->previous = NULL;
    }

    list->head = list->head->next;
    list->size--;

    free(tmp_node);
    return list->head;
}

Node* DeleteListData(List* list, int data)
{
    if (FindNode(list, data) == NULL)
    {
        return NULL;
    }

    Node* tmp_node = list->head;
    Node* previous_tmp_node = tmp_node;

    if (data == list->head->data)
    {
        list->head = DeleteListHead(list);
    }
    else if (data == list->end->data)
    {
        DeleteListEnd(list);
    }
    else
    {
        while (tmp_node->data != data)
        {
            previous_tmp_node = tmp_node;
            tmp_node = tmp_node->next;
        }
        previous_tmp_node->next = tmp_node->next;
        tmp_node->next->previous = previous_tmp_node;
        free(tmp_node);
        list->size--;
    }
    return list->head;
}

List* DeleteList(List* list)
{
    while (list->size != 0)
    {
        list->head = DeleteListHead(list);
    }
    free(list);
    return NULL;
}

Node* FindNode(List* list, int data)
{
    if (list->head == NULL)
    {
        return NULL;
    }

    Node* tmp_ptr = list->head;

    while (tmp_ptr->next != NULL)
    {
        if (tmp_ptr->data == data)
        {
            return tmp_ptr;
        }
        tmp_ptr = tmp_ptr->next;
    }
    return NULL;
}

void PrintList(List* list)
{
    if (list == NULL)
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

int ListLength(List* list)
{
    if (list == NULL)
    {
        return -1;
    }

    Node* tmp_ptr = list->head;
    int count = 0;

    while (tmp_ptr != NULL)
    {
        tmp_ptr = tmp_ptr->next;
        count++;
    }

    return count;
}