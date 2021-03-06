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

struct List
{
	int size;
	Node* head;
	Node* end;
};

List* createList(int data);
Node* addNode(List* list, int data);
Node* addInList(List* list, int data, int position);
Node* deleteListHead(List* list);
Node* deleteListEnd(List* list);
Node* deleteListData(List* list, int data);
List* deleteList(List* list);
Node* findNode(List* list, int data);
void printList(List* list);
int listLength(List* list);
bool checkListExist(List* list);
List* reverseCycledList(List* list);

int main()
{
	List* list = NULL;
	list = createList(0);

	addNode(list, 1);
	printList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
	puts("");

	addNode(list, 2);
	addNode(list, 20);

	list->head = deleteListHead(list);
	printList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
	puts("");

	printf("Find node with data 2: %p, Find node with data -100: %p\n", findNode(list, 2), findNode(list, -100));
	puts("");

	addInList(list, 3, 3);
	printList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
	puts("");

	reverseCycledList(list);
	printf("Reversed List:\n");
	printList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
	puts("");

	list->head = deleteListHead(list);
	printList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
	puts("");

	deleteListEnd(list);
	deleteListData(list, 2);

	printList(list);
	printf("List end: %d\n", list->end->data);
	printf("Size of list: %d, Function size of list: %d;\n", list->size, listLength(list));
	puts("");
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
	new_node->next = new_node;

	new_list->head = new_node;
	new_list->end = new_node;
	new_list->size = 1;

	return new_list;
}

Node* addNode(List* list, int data)
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

	Node* tmp_ptr = list->end;
	new_node->next = list->head;
	tmp_ptr->next = new_node;

	list->end = new_node;
	list->size++;

	return new_node;
}

Node* addInList(List* list, int data, int position)
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

Node* deleteListHead(List* list)
{
	if (checkListExist(list) || list->size == 0)
	{
		return NULL;
	}

	Node* tmp_head = list->head->next;
	free(list->head);

	list->size--;
	list->end->next = tmp_head;

	return tmp_head;
}

Node* deleteListEnd(List* list)
{
	if (checkListExist(list) || list->size == 0)
	{
		return NULL;
	}

	Node* tmp_ptr = list->head;
	Node* previous_tmp_node = tmp_ptr;
	do
	{
		previous_tmp_node = tmp_ptr;
		tmp_ptr = tmp_ptr->next;

		if (!tmp_ptr)
		{
			break;
		}
	} while (tmp_ptr->next != list->head);

	previous_tmp_node->next = list->head;
	free(tmp_ptr);

	list->size--;
	list->end = previous_tmp_node;

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

	Node* tmp_node = list->head;
	Node* previous_tmp_node = tmp_node;

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

List* deleteList(List* list)
{
	if (checkListExist(list))
	{
		return NULL;
	}

	while (list->size != 0)
	{
		list->head = deleteListEnd(list);
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

	if (list->head->data == data)
	{
		return list->head;
	}

	Node* tmp_ptr = list->head;
	
	while (tmp_ptr->next != list->head)
	{
		if (tmp_ptr->next->data == data)
		{
			return tmp_ptr;
		}
		tmp_ptr = tmp_ptr->next;
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

	do
	{
		printf("Data: %d;\n", printed->data);
		printed = printed->next;
	} while (printed != list->head);
}

int listLength(List* list)
{
	if (checkListExist(list))
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

List* reverseCycledList(List* list)
{
	if (checkListExist(list))
	{
		return NULL;
	} 

	Node* previous_node = NULL;
	Node* current_node = list->head;
	Node* next_node = NULL;
	Node* new_tail_node = list->head;

	do
	{
		next_node = current_node->next;
		current_node->next = previous_node;
		previous_node = current_node;
		current_node = next_node;
	} while (current_node != list->head);

	list->head->next = previous_node;
	list->head = previous_node;
	list->end = new_tail_node;

	return list;
}