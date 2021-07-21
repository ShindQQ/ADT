#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Node
{
	int data;
	int key;
	int height;
	Node* left;
	Node* right;
};

struct SearchTree
{
	int size;
	Node* root;
};

SearchTree* createSearchTree();
Node* insertSearchTree(SearchTree* tree, Node* sub_tree, int data, int key);
int calculateHeightSearchTree(Node* tree);
int heightSearchTree(Node* tree);
void NLRTravers(Node* tree);
void LNRTravers(Node* tree);
void LRNTravers(Node* tree);
void BFTTraversHelper(Node* tree, int level);
void BFTTravers(Node* tree);
Node* findMinNodeSearchTree(Node* tree);
Node* deleteDataByKeySearchTree(SearchTree* tree, Node* root, int key);
Node* findNodeByKeySearchTree(Node* tree, int key);
bool deleteSearchTree(Node* root);

int main()
{
	SearchTree* tree = NULL;
	tree = createSearchTree();

	insertSearchTree(tree, tree->root, 5, 5);
	insertSearchTree(tree, tree->root, 3, 3);
	insertSearchTree(tree, tree->root, 2, 2);
	insertSearchTree(tree, tree->root, 4, 4);
	insertSearchTree(tree, tree->root, 7, 7);
	insertSearchTree(tree, tree->root, 6, 6);
	insertSearchTree(tree, tree->root, 8, 8);

	printf("NLRTravers:\n");
	NLRTravers(tree->root);
	printf("Size of tree: %d;\n", tree->size);
	puts("");

	printf("LNRTravers:\n");
	LNRTravers(tree->root);
	printf("\tSize of tree: %d;\n", tree->size);
	puts("");

	printf("LRNTravers:\n");
	LRNTravers(tree->root);
	printf("\tSize of tree: %d;\n", tree->size);
	puts("");

	printf("BFTTravers:\n");
	BFTTravers(tree->root);
	printf("\tSize of tree: %d;\n", tree->size);
	puts("");

	deleteDataByKeySearchTree(tree, tree->root, 5);
	printf("BFTTravers with deleted node with key 5:\n");
	BFTTravers(tree->root);
	printf("\tSize of tree: %d;\n", tree->size);
	puts("");

	printf("Find Node with key 2: %p; Node with key -100: %p;\n", findNodeByKeySearchTree(tree->root, 2), findNodeByKeySearchTree(tree->root, -100));
	puts("");

	if (deleteSearchTree(tree->root) == 0)
	{
		free(tree);
		tree = NULL;
	}

	if (tree)
	{
		printf("LRNTravers:\n");
		LRNTravers(tree->root);
		printf("\tSize of tree: %d;\n", tree->size);
		puts("");
	}

	return 0;
}

SearchTree* createSearchTree()
{
	SearchTree* new_tree = (SearchTree*)malloc(sizeof(SearchTree));
	if (!new_tree)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_tree->size = 0;
	new_tree->root = NULL;

	return new_tree;
}

Node* insertSearchTree(SearchTree* tree, Node* sub_tree, int data, int key)
{
	if (!sub_tree)
	{
		sub_tree = (Node*)malloc(sizeof(Node));
		if (!sub_tree)
		{
			printf("Bad memory allocation! Line: %d!", __LINE__);
			return NULL;
		}

		sub_tree->data = data;
		sub_tree->key = key;
		sub_tree->left = sub_tree->right = NULL;
		sub_tree->height = 1;

		if (tree->size == 0)
		{
			tree->root = sub_tree;
		}
		tree->size++;

		return sub_tree;
	}

	if (sub_tree->key == key)
	{
		sub_tree->data = data;
	}
	else if (sub_tree->key > key)
	{
		sub_tree->left = insertSearchTree(tree, sub_tree->left, data, key);
	}
	else
	{
		sub_tree->right = insertSearchTree(tree, sub_tree->right, data, key);
	}

	return sub_tree;
}

int calculateHeightSearchTree(Node* tree)
{
	int left_height = heightSearchTree(tree->left);
	int right_height = heightSearchTree(tree->right);

	if (left_height > right_height)
	{
		tree->height = left_height + 1;
	}
	else
	{
		tree->height = right_height + 1;
	}

	return tree->height;
}

int heightSearchTree(Node* tree)
{
	if (tree)
	{
		return calculateHeightSearchTree(tree);
	}
	else
	{
		return 0;
	}
}

void NLRTravers(Node* tree)
{
	if (tree)
	{
		printf("Key: %d; Data: %d;\n", tree->key, tree->data);
		NLRTravers(tree->left);
		NLRTravers(tree->right);
	}

	return;
}

void LNRTravers(Node* tree)
{
	if (tree)
	{
		LNRTravers(tree->left);
		printf("Key: %d; Data: %d;\n", tree->key, tree->data);
		LNRTravers(tree->right);
	}

	return;
}

void LRNTravers(Node* tree)
{
	if (tree)
	{
		LRNTravers(tree->left);
		LRNTravers(tree->right);
		printf("Key: %d; Data: %d;\n", tree->key, tree->data);
	}

	return;
}

void BFTTraversHelper(Node* tree, int level)
{
	if (!tree)
	{
		return;
	}

	if (level == 1)
	{
		printf("Key: %d; Data: %d;\n", tree->key, tree->data);
	}
	else if (level > 1)
	{
		BFTTraversHelper(tree->left, level - 1);
		BFTTraversHelper(tree->right, level - 1);
	}
}

void BFTTravers(Node* tree)
{
	int height = heightSearchTree(tree);

	for (int i = 1; i <= height; i++)
	{
		BFTTraversHelper(tree, i);
	}
}

Node* findMinNodeSearchTree(Node* tree)
{
	Node* temp_node = tree;

	while (temp_node->left)
	{
		temp_node = temp_node->left;
	}

	return temp_node;
}

Node* deleteDataByKeySearchTree(SearchTree* tree, Node* root, int key)
{
	if (!root)
	{
		return NULL;
	}

	if (key < root->key)
	{
		root->left = deleteDataByKeySearchTree(tree, root->left, key);
	}
	else if (key > root->key)
	{
		root->right = deleteDataByKeySearchTree(tree, root->right, key);
	}
	else
	{
		Node* temp = NULL;
		if (!root->left)
		{
			temp = root->right;
			free(root);
			tree->size--;
			return temp;
		}
		else if (!root->right)
		{
			temp = root->left;
			free(root);
			tree->size--;
			return temp;
		}
		else
		{
			temp = findMinNodeSearchTree(root->right);
			root->key = temp->key;
			root->data = temp->data;
			root->right = deleteDataByKeySearchTree(tree, root->right, temp->key);
		}
	}

	return root;
}

Node* findNodeByKeySearchTree(Node* tree, int key)
{
	if (!tree)
	{
		return NULL;
	}

	if (tree->key == key)
	{
		return tree;
	}
	else if (tree->key > key)
	{
		return findNodeByKeySearchTree(tree->left, key);
	}
	else if (tree->key < key)
	{
		return findNodeByKeySearchTree(tree->right, key);
	}
}

bool deleteSearchTree(Node* root)
{
	if (root) {
		deleteSearchTree(root->left);
		deleteSearchTree(root->right);
		free(root);
		return 0;
	}
	else
	{
		return 1;
	}
}