#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Node
{
	int data;
	int key;
	bool color; // 0 - RED // 1 - BLACK
	Node* parent;
	Node* left;
	Node* right;
};

struct RBTree
{
	int size;
	Node* root;
};

RBTree* createRBTree();
Node* insertRBTree(RBTree* tree, int data, int key);
void fixupInsertRBTree(Node* root, Node* node);
void rotaterightRBTree(Node* root, Node* node);
void rotateleftRBTree(Node* root, Node* node);

int main()
{
	RBTree* tree = NULL;
	tree = createRBTree();

	insertRBTree(tree, 0, 0);
	insertRBTree(tree, 1, 2);
	insertRBTree(tree, 2, 2);
	insertRBTree(tree, 3, 3);
	insertRBTree(tree, 4, 4);
	insertRBTree(tree, 5, 5);

	return 0;
}

RBTree* createRBTree()
{
	RBTree* new_tree = (RBTree*)malloc(sizeof(RBTree));
	if (!new_tree)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_tree->size = 0;
	new_tree->root = NULL;

	return new_tree;
}

Node* insertRBTree(RBTree* tree, int data, int key)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_node->data = data;
	new_node->key = key;
	new_node->color = 0;
	new_node->left = new_node->right = new_node->parent = NULL;

	Node* temp_node = tree->root;
	Node* temp_prev_node = tree->root;

	while (temp_node != NULL)
	{
		temp_prev_node = temp_node;
		if (new_node->key <= temp_node->key)
		{
			temp_node = temp_node->left;
		}
		else
		{
			temp_node = temp_node->right;
		}
	}

	if (temp_prev_node == NULL)
	{
		tree->root = new_node;
	}
	else if (new_node->key <= temp_prev_node->key)
	{
		temp_prev_node->left = new_node;
	}
	else
	{
		temp_prev_node->right = new_node;
	}
	tree->size++;

	new_node->parent = temp_prev_node;

	fixupInsertRBTree(tree->root, new_node);
}


void fixupInsertRBTree(Node* root, Node* node)
{
	if (node->parent != NULL) 
	{
		while (node->parent->color == 0)
		{
			if (node->parent = node->parent->parent->left)
			{
				if (node->parent->parent->right->color == 0 && node->parent->parent->right != NULL)
				{
					node->parent->color = 1;
					node->parent->parent->right->color = 1;
					node->parent->parent->color = 0;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						rotaterightRBTree(root, node);
					}

					node->parent->color = 1;
					node->parent->parent->color = 0;
					rotateleftRBTree(root, node->parent->parent);
				}
			}
			else
			{
				if (node->parent->parent->left->color == 0 && node->parent->parent->left != NULL)
				{
					node->parent->color = 1;
					node->parent->parent->left->color = 1;
					node->parent->parent->color = 0;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rotaterightRBTree(root, node);
					}

					node->parent->color = 1;
					node->parent->parent->color = 0;
					rotateleftRBTree(root, node->parent->parent);
				}
			}
		}
	}
	root->color = 1;
}

void rotaterightRBTree(Node* root, Node* node)
{
	Node* temp_node = node->left;

	node->left = temp_node->right;
	if (temp_node->right == NULL)
	{
		temp_node->right->parent = temp_node;
	}

	temp_node->parent == node->parent;
	if (temp_node->parent == NULL)
	{
		root = temp_node;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = temp_node;
	}
	else
	{
		node->parent->right = temp_node;
	}

	temp_node->right = node;
	node->parent = node;
}

void rotateleftRBTree(Node* root, Node* node)
{
	Node* temp_node = node->right;

	node->right = temp_node->left;
	if (temp_node->left == NULL)
	{
		temp_node->left->parent = temp_node;
	}

	temp_node->parent == node->parent;
	if (temp_node->parent == NULL)
	{
		root = temp_node;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = temp_node;
	}
	else
	{
		node->parent->right = temp_node;
	}

	temp_node->left = node;
	node->parent = node;
}