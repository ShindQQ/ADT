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

struct Stack
{
	int size;
	Node* top;
};

Stack* createStack();
Node* addInStack(Stack* stack, int data);
int deleteStackTop(Stack* stack);
Stack* deleteStack(Stack* stack);
void printStack(Stack* stack);
int stackLength(Stack* stack);
bool checkStackExist(Stack* stack);
Stack* reverseStack(Stack* stack);

int main()
{
	Stack* stack = NULL;
	stack = createStack();

	addInStack(stack, 0);
	addInStack(stack, 1);
	addInStack(stack, 2);

	printStack(stack);
	printf("Stack top: %d\n", stack->top->data);
	printf("Size of stack: %d, Function size of list: %d;\n", stack->size, stackLength(stack));
	puts("");

	reverseStack(stack);
	printf("Reversed Stack:\n");
	printStack(stack);
	printf("Stack top: %d\n", stack->top->data);
	printf("Size of queue: %d, Function size of list: %d;\n", stack->size, stackLength(stack));
	puts("");

	printf("Deleted data from head: %d;\n", deleteStackTop(stack));
	printStack(stack);
	printf("Stack top: %d\n", stack->top->data);
	printf("Size of stack: %d, Function size of list: %d;\n", stack->size, stackLength(stack));
	puts("");

	stack = deleteStack(stack);
	printStack(stack);
	if (stack != NULL)
	{
		printf("Stack top: %d\n", stack->top->data);
		printf("Size of stack: %d, Function size of list: %d;\n", stack->size, stackLength(stack));
		puts("");
	}

	return 0;
}

Stack* createStack()
{
	Stack* new_stack = (Stack*)malloc(sizeof(Stack));
	if (!new_stack)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_stack->top = NULL;
	new_stack->size = 0;

	return new_stack;
}

Node* addInStack(Stack* stack, int data)
{
	if (checkStackExist(stack))
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

	new_node->next = stack->top;

	stack->size++;
	stack->top = new_node;

	return new_node;
}

int deleteStackTop(Stack* stack)
{
	if (checkStackExist(stack) || stack->size == 0)
	{
		return NULL;
	}

	int data_from_top = stack->top->data;
	Node* temp_deleting = stack->top;

	stack->top = stack->top->next;
	free(temp_deleting);
	stack->size--;

	return data_from_top;
}

Stack* deleteStack(Stack* stack)
{
	if (checkStackExist(stack))
	{
		return NULL;
	}

	while (stack->size != 0)
	{
		deleteStackTop(stack);
	}
	free(stack);

	return NULL;
}

void printStack(Stack* stack)
{
	if (checkStackExist(stack) || stack->size == 0)
	{
		return;
	}

	Node* printed = stack->top;

	do
	{
		printf("Data: %d;\n", printed->data);
		printed = printed->next;
	} while (printed != NULL);
}

int stackLength(Stack* stack)
{
	if (checkStackExist(stack))
	{
		return -1;
	}

	Node* temp_ptr = stack->top;
	int count = 0;

	do
	{
		temp_ptr = temp_ptr->next;
		count++;
	} while (temp_ptr != NULL);

	return count;
}

bool checkStackExist(Stack* stack)
{
	if (stack == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Stack* reverseStack(Stack* stack)
{
	if (checkStackExist(stack))
	{
		return NULL;
	}

	Node* previous_node = NULL;
	Node* current_node = stack->top;
	Node* next_node = NULL;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		current_node->next = previous_node;
		previous_node = current_node;
		current_node = next_node;
	}

	stack->top = previous_node;

	return stack;
}