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
Node* AddNode(List* list, int data);
Node* AddInList(List* list, int data, int position);
Node* DeleteListHead(List* list);
Node* DeleteListEnd(List* list);
Node* DeleteListData(List* list, int data);
List* DeleteList(List* list);
Node* FindNode(List* list, int data);
void PrintList(List* list);
int ListLength(List* list);

int main()
{
	List* list = NULL;
	list = CreateList(0);

	AddNode(list, 1);
	PrintList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
	puts("");

	AddNode(list, 2);
	AddNode(list, 20);
	PrintList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
	puts("");

	printf("Find node with data 2: %p, Find node with data -100: %p\n", FindNode(list, 2), FindNode(list, -100));
	puts("");

	AddInList(list, 3, 3);
	PrintList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
	puts("");

	list->head = DeleteListHead(list);
	PrintList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
	puts("");

	DeleteListEnd(list);
	list->head = DeleteListData(list, 2);

	PrintList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, ListLength(list));
	puts("");

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
	new_node->next = new_node;

	new_list->head = new_node;
	new_list->end = new_node;
	new_list->size = 1;

	return new_list;
}

Node* AddNode(List* list, int data)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_node->data = data;

	Node* tmp_ptr = list->end;
	new_node->next = list->head;
	tmp_ptr->next = new_node;

	list->end = new_node;
	list->size++;

	return new_node;
}

Node* AddInList(List* list, int data, int position)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_node->data = data;

	Node* tmp_ptr = list->head;
	for (int i = 1; i < position; i++)
	{
		tmp_ptr = tmp_ptr->next;
	}

	new_node->next = tmp_ptr->next;
	tmp_ptr->next = new_node;

	if (position == list->size)
	{
		list->end = new_node;
	}
	list->size++;

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
	list->end->next = tmp_head;
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
	} while (tmp_ptr->next != list->head);

	tmp_previous_ptr->next = list->head;
	free(tmp_ptr);

	list->size--;
	list->end = tmp_previous_ptr;

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
		free(tmp_node);
		list->size--;
	}
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

	while (tmp_ptr->next != list->head)
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

	do
	{
		printf("Data: %d;\n", printed->data);
		printed = printed->next;
	} while (printed != list->head);
}

int ListLength(List* list)
{
	if (list == NULL)
	{
		return -1;
	}

	Node* tmp_ptr = list->head;
	int count = 0;

	do
	{
		tmp_ptr = tmp_ptr->next;
		count++;
	} while (tmp_ptr != list->head);

	return count;
}