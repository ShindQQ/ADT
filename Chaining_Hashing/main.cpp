#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define FULLNESS_LIMIT 0.6
#define EXPANSION_SIZE 10

struct Node
{
	int data;
	int key;
	Node* next;
};

struct HashTable
{
	Node* HT;
	int size;
	int fullness;
	int filled_blocks;
	double average_fullness;
};

int hashing(int key, int size);
HashTable* initializeHashTable(int size);
HashTable* recizeHashTable(HashTable* table, int new_size);
Node* insertHashTable(HashTable*& table, int key, int data);
bool deleteNodeByKeyHashTable(HashTable* table, int key);
bool printHashTable(HashTable* table);
Node* findNodeHashTable(HashTable* table, int key);
HashTable* deleteHashTable(HashTable* table);

int main()
{
	HashTable* table = NULL;
	table = initializeHashTable(10);

	insertHashTable(table, 0, 0);
	insertHashTable(table, 10, 10);
	insertHashTable(table, 1, 1);
	insertHashTable(table, 2, 2);
	insertHashTable(table, 3, 3);
	insertHashTable(table, 4, 4);
	insertHashTable(table, 5, 5);


	printf("Current HashTable:\n");
	printHashTable(table);
	printf("Current size of HashTable: %d;\nCurrent fullness of HashTable: %d;\nCurrent N of filled blocks of HashTable: %d;\n", table->size, table->fullness, table->filled_blocks);
	puts("");

	printf("Remove Node with key 5:\n");
	deleteNodeByKeyHashTable(table, 5);

	printHashTable(table);
	printf("Current size of HashTable: %d;\nCurrent fullness of HashTable: %d;\nCurrent N of filled blocks of HashTable: %d;\n", table->size, table->fullness, table->filled_blocks);
	puts("");

	printf("Find Node with key 10: %p; Node with key -100: %p;\n", findNodeHashTable(table, 10), findNodeHashTable(table, -100));
	puts("");

	table = deleteHashTable(table);
	if (table)
	{
		printHashTable(table);
		printf("Current size of HashTable: %d;\nCurrent fullness of HashTable: %d;\nCurrent N of filled blocks of HashTable: %d;\n", table->size, table->fullness, table->filled_blocks);
		puts("");
	}

	return 0;
}

int hashing(int key, int size)
{
	return key % size;
}

HashTable* initializeHashTable(int size)
{
	HashTable* new_table = (HashTable*)malloc(sizeof(HashTable) * size);
	if (!new_table)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	for (int i = 0; i < size; i++)
	{
		new_table[i].HT = NULL;
	}

	new_table->size = size;
	new_table->fullness = 0;
	new_table->filled_blocks = 0;
	new_table->average_fullness = 0;

	return new_table;
}

HashTable* recizeHashTable(HashTable* table, int new_size)
{
	if (!table)
	{
		return NULL;
	}

	HashTable* new_table = initializeHashTable(new_size);

	for (int i = 0; i < table->size; i++)
	{
		while (table[i].HT)
		{
			insertHashTable(new_table, table[i].HT->key, table[i].HT->data);
			deleteNodeByKeyHashTable(table, table[i].HT->key);
		}
	}

	table = deleteHashTable(table);

	return new_table;
}

Node* insertHashTable(HashTable*& table, int key, int data)
{
	if (!table)
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
	new_node->key = key;

	int hash_index = hashing(key, table->size);

	Node* temp_node = table[hash_index].HT;

	while (temp_node)
	{
		if (temp_node->key == key)
		{
			temp_node->data = data;
			return temp_node;
		}
		temp_node = temp_node->next;
	}

	if (!temp_node)
	{
		table->filled_blocks++;
	}

	new_node->next = table[hash_index].HT;
	table[hash_index].HT = new_node;

	table->fullness++;
	table->average_fullness = double(table->fullness) / double(table->size);

	if (table->average_fullness > FULLNESS_LIMIT)
	{
		table = recizeHashTable(table, table->size + EXPANSION_SIZE);
	}

	return new_node;
}

bool deleteNodeByKeyHashTable(HashTable* table, int key)
{
	if (!table)
	{
		return 1;
	}

	int hash_index = hashing(key, table->size);

	if (!table[hash_index].HT)
	{
		return 1;
	}

	Node* temp_current = table[hash_index].HT;
	Node* temp_previous = temp_current;

	while (temp_current && temp_current->key != key)
	{
		temp_previous = temp_current;
		temp_current = temp_current->next;
	}

	if (!temp_current)
	{
		return 1;
	}

	if (table[hash_index].HT == temp_current)
	{
		temp_previous = table[hash_index].HT->next;
		free(temp_current);
		table[hash_index].HT = temp_previous;
	}
	else if (!temp_current->next)
	{
		free(temp_current);
		temp_previous->next = NULL;
		table->filled_blocks--;
	}
	else
	{
		temp_previous = temp_current->next;
		free(temp_current);
	}

	table->fullness--;
	table->average_fullness = double(table->fullness) / double(table->size);

	return 0;
}

bool printHashTable(HashTable* table)
{
	if (!table)
	{
		return 1;
	}

	Node* temp_node;
	for (int i = 0; i < table->size; i++)
	{
		if (!table[i].HT)
		{
			continue;
		}

		temp_node = table[i].HT;
		printf("%d: %p;\t\n", i, table[i].HT);

		while (temp_node)
		{
			printf("Key: %d; Data: %d\n", temp_node->key, temp_node->data);
			temp_node = temp_node->next;
		}
		puts("");
	}

	return 0;
}

Node* findNodeHashTable(HashTable* table, int key)
{
	if (!table)
	{
		return NULL;
	}
	Node* temp_node = table[hashing(key, table->size)].HT;

	if (!temp_node)
	{
		return NULL;
	}

	while (temp_node)
	{
		if (temp_node->key == key)
		{
			return temp_node;
		}
		temp_node = temp_node->next;
	}
}

HashTable* deleteHashTable(HashTable* table)
{
	for (int i = 0; i < table->size; i++)
	{
		free(table[i].HT);
	}

	free(table);

	return NULL;
}