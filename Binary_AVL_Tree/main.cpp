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

struct AVLTree
{
	int size;
	Node* root;
};

AVLTree* createAVLTree();
Node* addAVLTree(AVLTree* tree, Node* sub_tree, int data, int key);
int balanceFactorAVLTree(Node* root);
Node* rotate_rightBalancingAVLTree(Node* root);
Node* rotate_leftBalancingAVLTree(Node* root);
Node* balancingAVLTree(Node* root);
Node* findMinNodeAVLTree(Node* tree);
Node* refindMinNodeAVLTree(Node* tree);
Node* deleteDataByKeyAVLTree(AVLTree* tree, Node* root, int key);
Node* findNodeByKeyAVLTree(Node* tree, int key);
int calculateHeightAVLTree(Node* tree);
int heightAVLTree(Node* tree);
void NLRTravers(Node* tree);
void LNRTravers(Node* tree);
void LRNTravers(Node* tree);
void BFTTraversHelper(Node* tree, int level);
void BFTTravers(Node* tree);
bool deleteAVLTree(Node* root);

int main()
{
	AVLTree* tree = NULL;
	tree = createAVLTree();

	tree->root = addAVLTree(tree, tree->root, 0, 0);
	tree->root = addAVLTree(tree, tree->root, 1, 1);
	tree->root = addAVLTree(tree, tree->root, 2, 2);
	tree->root = addAVLTree(tree, tree->root, 3, 3);
	tree->root = addAVLTree(tree, tree->root, 4, 4);
	tree->root = addAVLTree(tree, tree->root, 5, 5);
	tree->root = addAVLTree(tree, tree->root, 6, 6);

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

	tree->root = deleteDataByKeyAVLTree(tree, tree->root, 5);
	printf("BFTTravers with deleted node with key 5:\n");
	BFTTravers(tree->root);
	printf("\tSize of tree: %d;\n", tree->size);
	puts("");

	printf("Find Node with key 2: %p; Node with key -100: %p;\n", findNodeByKeyAVLTree(tree->root, 2), findNodeByKeyAVLTree(tree->root, -100));
	puts("");

	if (deleteAVLTree(tree->root) == 0)
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

AVLTree* createAVLTree()
{
	AVLTree* new_tree = (AVLTree*)malloc(sizeof(AVLTree));
	if (!new_tree)
	{
		printf("Bad memory allocation! Line: %d!", __LINE__);
		return NULL;
	}

	new_tree->size = 0;
	new_tree->root = NULL;

	return new_tree;
}

Node* addAVLTree(AVLTree* tree, Node* sub_tree, int data, int key)
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
		sub_tree->left = addAVLTree(tree, sub_tree->left, data, key);
	}
	else
	{
		sub_tree->right = addAVLTree(tree, sub_tree->right, data, key);
	}

	return balancingAVLTree(sub_tree);
}

int balanceFactorAVLTree(Node* root)
{
	return heightAVLTree(root->right) - heightAVLTree(root->left);
}

Node* rotate_rightBalancingAVLTree(Node* root)
{
	Node* temp_node = root->left;

	root->left = temp_node->right;
	temp_node->right = root;

	calculateHeightAVLTree(root);
	calculateHeightAVLTree(temp_node);

	return temp_node;
}

Node* rotate_leftBalancingAVLTree(Node* root)
{
	Node* temp_node = root->right;

	root->right = temp_node->left;
	temp_node->left = root;

	calculateHeightAVLTree(root);
	calculateHeightAVLTree(temp_node);

	return temp_node;
}

Node* balancingAVLTree(Node* root)
{
	calculateHeightAVLTree(root);

	int balance_factor = balanceFactorAVLTree(root);

	if (balance_factor == 2)
	{
		if (balanceFactorAVLTree(root->right) < 0)
		{
			root->right = rotate_rightBalancingAVLTree(root->right);
		}
		return rotate_leftBalancingAVLTree(root);
	}
	else if (balance_factor == -2)
	{
		if (balanceFactorAVLTree(root->left) < 0)
		{
			root->left = rotate_leftBalancingAVLTree(root->left);
		}
		return rotate_rightBalancingAVLTree(root);
	}

	return root;
}

Node* findMinNodeAVLTree(Node* tree)
{
	return tree->left ? findMinNodeAVLTree(tree->left) : tree;
}

Node* refindMinNodeAVLTree(Node* tree)
{
	if (!tree->left)
	{
		return tree->right;
	}

	tree->left = refindMinNodeAVLTree(tree->left);

	return balancingAVLTree(tree);
}

Node* deleteDataByKeyAVLTree(AVLTree* tree, Node* root, int key)
{
	if (!root)
	{
		return NULL;
	}

	if (key < root->key)
	{
		root->left = deleteDataByKeyAVLTree(tree, root->left, key);
	}
	else if (key > root->key)
	{
		root->right = deleteDataByKeyAVLTree(tree, root->right, key);
	}
	else
	{
		Node* temp_left = root->left;
		Node* temp_right = root->right;

		free(root);
		tree->size--;

		if (!temp_right)
		{
			return temp_left;
		}

		Node* min_node = findMinNodeAVLTree(temp_right);
		min_node->right = refindMinNodeAVLTree(temp_right);
		min_node->left = temp_left;

		return balancingAVLTree(min_node);
	}

	return balancingAVLTree(root);
}

Node* findNodeByKeyAVLTree(Node* tree, int key)
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
		return findNodeByKeyAVLTree(tree->left, key);
	}
	else if (tree->key < key)
	{
		return findNodeByKeyAVLTree(tree->right, key);
	}
}

int calculateHeightAVLTree(Node* tree)
{
	int left_height = heightAVLTree(tree->left);
	int right_height = heightAVLTree(tree->right);

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

int heightAVLTree(Node* tree)
{
	if (tree)
	{
		return calculateHeightAVLTree(tree);
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
	if (tree == NULL)
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
	int height = heightAVLTree(tree);

	for (int i = 1; i <= height; i++)
	{
		BFTTraversHelper(tree, i);
	}
}

bool deleteAVLTree(Node* root)
{
	if (root) {
		deleteAVLTree(root->left);
		deleteAVLTree(root->right);
		free(root);
		return 0;
	}
	else
	{
		return 1;
	}
}