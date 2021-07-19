#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


enum color
{
	BLACK,
	RED
};

struct Node
{
	int data;
	int key;
	color color;
	Node* parent;
	Node* left;
	Node* right;
};

struct RBTree
{
	int size;
	Node* root;
};

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

void rotate_leftRBTree(Node* root, Node* node)
{
	Node* temp_node = node->right;

	node->right = temp_node->left;
	if (temp_node->left != NULL)
	{
		temp_node->left->parent = node;
	}

	if (node->parent == NULL)
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
	node->parent = temp_node;
}

void rotate_rightRBTree(Node* root, Node* node)
{
	Node* temp_node = node->left;

	node->left = temp_node->right;
	if (temp_node->right != NULL)
	{
		temp_node->right->parent = node;
	}

	if (node->parent == NULL)
	{
		root = temp_node;
	}
	else if (node == node->parent->right)
	{
		node->parent->right = temp_node;
	}
	else
	{
		node->parent->left = temp_node;
	}

	temp_node->right = node;
	node->parent = temp_node;
}

Node* fixInsertRBTree(Node* root, Node* new_node)
{
	while (new_node->parent != NULL && new_node->parent->color == RED)
	{
		if (new_node->parent == new_node->parent->parent->left)
		{
			Node* temp_node = new_node->parent->parent->right;
			if (temp_node != NULL && temp_node->color == RED)
			{
				new_node->parent->color = BLACK;
				temp_node->color = RED;
				new_node->parent->parent->color = BLACK;
			}
			else if (new_node == new_node->parent->right)
			{
				new_node = new_node->parent;
				rotate_leftRBTree(root, new_node);
			}
			new_node->parent->color = BLACK;
			new_node->parent->parent->color = RED;
			rotate_rightRBTree(root, new_node->parent->parent);
		}
		else
		{
			Node* temp_node = new_node->parent->parent->left;
			if (temp_node != NULL && temp_node->color == RED)
			{
				new_node->parent->color = BLACK;
				temp_node->color = RED;
				new_node->parent->parent->color = BLACK;
			}
			else if (new_node == new_node->parent->left)
			{
				new_node = new_node->parent;
				rotate_rightRBTree(root, new_node);
			}
			new_node->parent->color = BLACK;
			new_node->parent->parent->color = RED;
			rotate_leftRBTree(root, new_node->parent->parent);
		}
	}
	root->color = BLACK;
	return root;
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
	new_node->left = new_node->right = NULL;
	new_node->color = RED;


	Node* temp_node = tree->root;
	Node* previous_temp_node = NULL;

	while (temp_node != NULL)
	{
		previous_temp_node = temp_node;
		if (temp_node->key < new_node->key)
		{
			temp_node = temp_node->right;
		}
		else
		{
			temp_node = temp_node->left;
		}
	}

	new_node->parent = previous_temp_node;
	if (previous_temp_node == NULL)
	{
		tree->root = new_node;
	}
	else
	{
		if (previous_temp_node->key < new_node->key)
		{
			previous_temp_node->right = new_node;
		}
		else
		{
			previous_temp_node->left = new_node;
		}
	}

	tree->size++;

	return fixInsertRBTree(tree->root, new_node);
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

int main()
{
	RBTree* tree = NULL;
	tree = createRBTree();
	insertRBTree(tree, 0, 0);
	insertRBTree(tree, 1, 1);
	insertRBTree(tree, 2, 2);
	NLRTravers(tree->root);
	return 0;
}