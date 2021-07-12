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
Node* DeleteListHead(List* list);
Node* DeleteListEnd(List* list);
List* DeleteList(List* list);
Node* FindNode(List* list, int data);
void PrintList(List* list);
int ListLength(List* list);

int main()
{
    List* list = NULL;

    list = CreateList(0);
    srand(time(NULL));

    ListAddEnd(list, 2);

    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    ListAddEnd(list, 3);

    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    list->head = ListAddStart(list, 1);

    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    ListAddAfter(list, 5, 3);

    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    list->head = DeleteListHead(list);
    DeleteListEnd(list);

    PrintList(list);
    printf("List end: %d\n", list->end->data);
    printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
    puts("");

    printf("Find node with data 2: %p, Find node with data -100: %p\n", FindNode(list, 2), FindNode(list, -100));
    puts("");

    list = DeleteList(list);

    PrintList(list);
    if (list != NULL)
    {
        printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list)); // error beacause of unexisting of List
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

    new_node->next = NULL;
    new_node->data = data;

    new_list->head = new_node;
    new_list->end = new_node;
    new_list->size = 1;

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

    Node* tmp_ptr = list->end;

    new_node->data = data;
    new_node->next = NULL;
    tmp_ptr->next = new_node;

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
    new_node->next = list->head;
    list->head = new_node;

    list->size++;

    return list->head;
}

Node* ListAddAfter(List* list, int data, int num_after)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_node->data = data;

    Node* tmp_ptr = list->head;
    Node* tmp_previous_ptr = tmp_ptr;

    int check = 0;
    int check_end = 0;
    if (list->end->data == num_after)
    {
        check_end = 1;
    }

    do
    {
        if (tmp_ptr->data == num_after)
        {
            check = 1;
        }

        tmp_previous_ptr = tmp_ptr;
        tmp_ptr = tmp_ptr->next;

        if (!tmp_ptr)
        {
            break;
        }
    } while (tmp_previous_ptr->data != num_after && tmp_ptr);

    if (check == 1)
    {
        tmp_previous_ptr->next = new_node;
        new_node->next = tmp_ptr;

        list->size++;
        if (check_end == 1)
        {
            list->end = new_node;
        }
    }

    return new_node;
}

Node* DeleteListHead(List* list)
{
    if (list->head == NULL)
    {
        return NULL;
    }

    Node* tmp_head = list->head->next;
    free(list->head);
    list->size--;
    return tmp_head;
}

Node* DeleteListEnd(List* list)
{
    if (list->head == NULL)
    {
        return NULL;
    }

    Node* tmp_ptr = list->head;
    Node* tmp_previous_ptr = tmp_ptr;
    do
    {
        tmp_previous_ptr = tmp_ptr;
        tmp_ptr = tmp_ptr->next;

        if (!tmp_ptr)
        {
            break;
        }
    } while (tmp_ptr->next != NULL);

    tmp_previous_ptr->next = NULL;
    free(tmp_ptr);

    list->size--;
    list->end = tmp_previous_ptr;

    return list->head;
}

List* DeleteList(List* list)
{
    while (list->size != 0)
    {
        list->head = DeleteListEnd(list);
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
        tmp_ptr = tmp_ptr->next;
        if (tmp_ptr->data == data)
        {
            return tmp_ptr;
        }
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