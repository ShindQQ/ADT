#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define FULLNESS_LIMIT 0.6
#define EXPANSION_SIZE 10
#define HASHING_CONST 7

struct Node
{
    int data;
    int key;
};

struct HashTable
{
    Node* HT;
    int size;
    int fullness;
    int deleted_elements;
};

int hashing1(int key, int size);
int hashing2(int key);
HashTable* initializeHashTable(int size);
int insertHashTable(HashTable*& table, int key, int data);
HashTable* recizeHashTable(HashTable* table, int new_size);
int deleteNodeByKeyHashTable(HashTable* table, int key);
bool printHashTable(HashTable* table);
int findNodeHashTable(HashTable* table, int key);
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
    printf("Current size of HashTable: %d;\nCurrent fullness of HashTable: %d;\nCurrent deleted elements of HashTable: %d;\n", table->size, table->fullness, table->deleted_elements);
    puts("");

    printf("Remove Node with key 5:\n");
    deleteNodeByKeyHashTable(table, 5);

    printHashTable(table);
    printf("Current size of HashTable: %d;\nCurrent fullness of HashTable: %d;\nCurrent deleted elements of HashTable: %d;\n", table->size, table->fullness, table->deleted_elements);
    puts("");

    printf("Find Node with key 10: %d; Node with key -100: %d;\n", table->HT[findNodeHashTable(table, 10)].key, table->HT[findNodeHashTable(table, -100)].key);
    puts("");

    table = deleteHashTable(table);
    if (table)
    {
        printHashTable(table);
        printf("Current size of HashTable: %d;\nCurrent fullness of HashTable: %d;\n", table->size, table->fullness);
        puts("");
    }

    return 0;
}

int hashing1(int key, int size)
{
    return key % size;
}

int hashing2(int key)
{
    return abs(HASHING_CONST - (key % HASHING_CONST));
}

HashTable* initializeHashTable(int size)
{
    HashTable* new_table = (HashTable*)malloc(sizeof(HashTable));
    if (!new_table)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    new_table->HT = (Node*)malloc(sizeof(Node) * size);
    if (!new_table->HT)
    {
        printf("Bad memory allocation! Line: %d!", __LINE__);
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        new_table->HT[i].key = INT_MIN;
    }

    new_table->size = size;
    new_table->fullness = 0;
    new_table->deleted_elements = 0;

    return new_table;
}

int insertHashTable(HashTable*& table, int key, int data)
{
    if (!table)
    {
        return -2;

    }

    int hash_index1 = hashing1(key, table->size);

    if ((table->fullness + table->deleted_elements + 1) >= int((double)table->size * FULLNESS_LIMIT))
    {
        table = recizeHashTable(table, table->size + EXPANSION_SIZE);
    }

    if (table->HT[hash_index1].key == key)
    {
        table->HT[hash_index1].data = data;
        return 0;
    }

    if (table->HT[hash_index1].key != INT_MIN)
    {
        int hash_index2 = hashing2(key);
        int i = 1;

        while (1) 
        {

            int found_index = (hash_index1 + i * hash_index2) % table->size;

            if (table->HT[hash_index1].key == key)
            {
                table->HT[found_index].data = data;
                return 0;
            }
            else if (table->HT[found_index].key == INT_MIN) 
            {
                table->HT[found_index].key = key;
                table->HT[found_index].data = data;
                break;
            }

            i++;
        }
    }
    else
    {
        table->HT[hash_index1].key = key;
        table->HT[hash_index1].data = data;
    }

    table->fullness++;

    return 0;
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
        if (table->HT[i].key != INT_MIN)
        {
            insertHashTable(new_table, table->HT[i].key, table->HT[i].data);
        }
    }

    deleteHashTable(table);

    return new_table;
}

int deleteNodeByKeyHashTable(HashTable* table, int key)
{
    if (!table)
    {
        return -1;
    }

    int hash_index = findNodeHashTable(table, key);

    if (hash_index > -1)
    {
        table->HT[hash_index].key = INT_MAX;
        table->HT[hash_index].data = INT_MAX;
        table->fullness--;
        table->deleted_elements++;

        return 0;
    }
    else
    {
        return 1;
    }
}

bool printHashTable(HashTable* table)
{
    if (!table)
    {
        return 1;
    }

    for (int i = 0; i < table->size; i++)
    {
        printf("[%d]Key: %d; Data: %d\n", i, table->HT[i].key, table->HT[i].data);
        puts("");
    }

    return 0;
}

int findNodeHashTable(HashTable* table, int key)
{
    int hash_index1 = hashing1(key, table->size);
    int hash_index2 = hashing2(key);
    int i = 0;
    int found_index = 0;

    while (table->HT[found_index].key != key)
    {
        found_index = (hash_index1 + i * hash_index2) % table->size;

        if (i > table->size)
        {
            return -1;
        }
        else if (table->HT[found_index].key == key)
        {
            return found_index;
        }

        i++;
    }
}

HashTable* deleteHashTable(HashTable* table)
{
    free(table->HT);
    free(table);

    return NULL;
}