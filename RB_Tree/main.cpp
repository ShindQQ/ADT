#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

enum color
{
	BLACK,
	RED
};

struct Node
{
	int data;
	int key;
	int height;
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

void swapNodesData(Node*& arg1, Node*& arg2);
void swap(color& arg1, color& arg2);
RBTree* initializeRBTree();
void rotate_leftRBTree(Node*& root, Node*& node);
void rotate_rightRBTree(Node*& root, Node*& node);
void fixInsertRBTree(Node*& root, Node*& new_node);
Node* insertHelperRBTree(Node* root, Node* new_node);
Node* insertRBTree(RBTree* tree, int data, int key);
Node* findMinNodeRBTree(Node* tree);
Node* findNodeByKeyRBTree(Node* tree, int key);
Node* replaceNodeRBTree(Node* node);
Node* checkSibling(Node* node);
void fixDoubleBlack(Node*& root, Node*& node);
void deleteNodeRBTree(Node*& root, Node* node);
Node* deleteDataByKeyRBTree(RBTree* tree, int key);
int calculateHeightRBTree(Node* tree);
int heightRBTree(Node* tree);
void NLRTravers(Node* tree);
void LNRTravers(Node* tree);
void LRNTravers(Node* tree);
void BFTTraversHelper(Node* tree, int level);
bool BFTTravers(Node* tree);
bool deleteRBTree(Node* root);

int main()
{
	RBTree* tree = NULL;
	tree = initializeRBTree();

	clock_t begin = clock();

	insertRBTree(tree, 0, 0);
	insertRBTree(tree, 1, 1);
	insertRBTree(tree, 2, 2);
	insertRBTree(tree, 3, 3);
	insertRBTree(tree, 4, 4);

	clock_t end = clock();

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time spent on inserting 5 nodes: %lf;\n\n", time_spent); // 0.001000

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

	deleteDataByKeyRBTree(tree, 3);
	printf("BFTTravers with deleted node with key 3:\n");
	BFTTravers(tree->root);
	printf("\tSize of tree: %d;\n", tree->size);
	puts("");

	printf("Find Node with key 2: %p; Node with key -100: %p;\n", findNodeByKeyRBTree(tree->root, 2), findNodeByKeyRBTree(tree->root, -100));
	puts("");

	if (deleteRBTree(tree->root) == 0)
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

void swapNodesData(Node*& arg1, Node*& arg2)
{
	int temp_data = arg1->data;
	int temp_key = arg1->key;
	arg1->data = arg2->data;
	arg1->key = arg2->key;
	arg2->data = temp_data;
	arg2->key = temp_key;
}

void swap(color& arg1, color& arg2)
{
	color temp = arg1;
	arg1 = arg2;
	arg2 = temp;
}

RBTree* initializeRBTree()
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

void rotate_leftRBTree(Node*& root, Node*& node)
{
	Node* temp_node = node->right;

	node->right = temp_node->left;
	if (node->right)
	{
		node->right->parent = node;
	}

	temp_node->parent = node->parent;

	if (!node->parent)
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

void rotate_rightRBTree(Node*& root, Node*& node)
{
	Node* temp_node = node->left;

	node->left = temp_node->right;
	if (node->left)
	{
		node->left->parent = node;
	}

	temp_node->parent = node->parent;

	if (!node->parent)
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
	node->parent = temp_node;
}

void fixInsertRBTree(Node*& root, Node*& new_node)
{
	Node* parent_ptr = NULL;
	Node* grand_parent_ptr = NULL;

	while (new_node != root && new_node->color != BLACK && new_node->parent->color == RED)
	{
		parent_ptr = new_node->parent;
		grand_parent_ptr = new_node->parent->parent;

		if (parent_ptr == grand_parent_ptr->left)
		{
			Node* uncle_ptr = grand_parent_ptr->right;

			if (uncle_ptr != NULL && uncle_ptr->color == RED)
			{
				grand_parent_ptr->color = RED;
				parent_ptr->color = BLACK;
				uncle_ptr->color = BLACK;
				new_node = grand_parent_ptr;
			}
			else
			{
				if (new_node == parent_ptr->right)
				{
					rotate_leftRBTree(root, parent_ptr);
					new_node = parent_ptr;
					parent_ptr = new_node->parent;
				}

				rotate_rightRBTree(root, grand_parent_ptr);
				swap(parent_ptr->color, grand_parent_ptr->color);
				new_node = parent_ptr;
			}
		}
		else
		{
			Node* uncle_ptr = grand_parent_ptr->left;

			if (uncle_ptr && uncle_ptr->color == RED)
			{
				grand_parent_ptr->color = RED;
				parent_ptr->color = BLACK;
				uncle_ptr->color = BLACK;
				new_node = grand_parent_ptr;
			}
			else
			{
				if (new_node == parent_ptr->left)
				{
					rotate_rightRBTree(root, parent_ptr);
					new_node = parent_ptr;
					parent_ptr = new_node->parent;
				}

				rotate_leftRBTree(root, grand_parent_ptr);
				swap(parent_ptr->color, grand_parent_ptr->color);
				new_node = parent_ptr;
			}
		}
	}

	root->color = BLACK;
}

Node* insertHelperRBTree(Node* root, Node* new_node)
{
	if (!root)
	{
		return new_node;
	}

	if (new_node->key < root->key)
	{
		root->left = insertHelperRBTree(root->left, new_node);
		root->left->parent = root;
	}
	else
	{
		root->right = insertHelperRBTree(root->right, new_node);
		root->right->parent = root;
	}

	return root;
}

Node* insertRBTree(RBTree* tree, int data, int key)
{
	if (!tree)
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
	new_node->left = new_node->right = new_node->parent = NULL;
	new_node->color = RED;
	new_node->height = 1;

	tree->root = insertHelperRBTree(tree->root, new_node);

	tree->size++;

	fixInsertRBTree(tree->root, new_node);

	return tree->root;
}

Node* findMinNodeRBTree(Node* tree)
{
	if (!tree)
	{
		return NULL;
	}

	Node* temp_node = tree;

	while (temp_node->left)
	{
		temp_node = temp_node->left;
	}

	return temp_node;
}

Node* findNodeByKeyRBTree(Node* tree, int key)
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
		return findNodeByKeyRBTree(tree->left, key);
	}
	else if (tree->key < key)
	{
		return findNodeByKeyRBTree(tree->right, key);
	}
}

Node* replaceNodeRBTree(Node* node)
{
	if (node->left&& node->right)
	{
		return findMinNodeRBTree(node->right);
	}
	else if (!node->left&& !node->right)
	{
		return NULL;
	}
	else if (node->left)
	{
		return node->left;
	}
	else
	{
		return node->right;
	}
}

Node* checkSibling(Node* node)
{
	if (!node->parent)
	{
		return NULL;
	}
	else if (node == node->parent->left)
	{
		return node->parent->right;
	}
	else
	{
		return node->parent->left;
	}
}

void fixDoubleBlack(Node*& root, Node*& node)
{
	if (node == root)
	{
		return;
	}

	Node* sibling = checkSibling(node);
	Node* parent = node->parent;

	if (!sibling)
	{
		fixDoubleBlack(root, parent);
	}
	else
	{
		if (sibling->color == RED)
		{
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling == sibling->parent->left)
			{
				rotate_rightRBTree(root, parent);
			}
			else
			{
				rotate_leftRBTree(root, parent);
			}
			fixDoubleBlack(root, node);
		}
		else
		{
			if ((sibling->left && sibling->left->color == RED) ||
				(sibling->right && sibling->right->color == RED))
			{
				if (sibling->left && sibling->left->color == RED)
				{
					if (sibling == sibling->parent->left)
					{
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rotate_rightRBTree(root, parent);
					}
					else
					{
						sibling->left->color = parent->color;
						rotate_rightRBTree(root, sibling);
						rotate_leftRBTree(root, parent);
					}
				}
				else
				{
					if (sibling->left)
					{
						if (sibling == sibling->parent->left)
						{
							sibling->left->color = parent->color;
							rotate_leftRBTree(root, sibling);
							rotate_rightRBTree(root, parent);
						}
						else
						{
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rotate_leftRBTree(root, parent);
						}
					}
				}
				parent->color = BLACK;
			}
			else
			{
				sibling->color = RED;
				if (parent->color == BLACK)
				{
					fixDoubleBlack(root, parent);
				}
				else
				{
					parent->color = BLACK;
				}
			}
		}
	}
}

void deleteNodeRBTree(Node*& root, Node* node)
{
	Node* temp_node = replaceNodeRBTree(node);

	bool color_black = ((temp_node == NULL || temp_node->color == BLACK) && (node->color == BLACK));

	Node* parent = node->parent;

	if (!temp_node)
	{
		if (node == root)
		{
			root = NULL;
		}
		else
		{
			if (color_black)
			{
				fixDoubleBlack(root, node);
			}
			else
			{
				if (checkSibling(node) != NULL)
				{
					checkSibling(node)->color = RED;
				}
			}

			if (node == node->parent->left)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
		}

		free(temp_node);
		return;
	}

	if (!node->left || !node->right)
	{
		if (node == root)
		{
			node->data = temp_node->data;
			node->key = temp_node->key;
			node->left = node->right = NULL;
			free(temp_node);
		}
		else
		{
			if (node == node->parent->left)
			{
				parent->left = temp_node;
			}
			else
			{
				parent->right = temp_node;
			}

			free(node);
			temp_node->parent = parent;

			if (color_black)
			{
				fixDoubleBlack(root, temp_node);
			}
			else
			{
				temp_node->color = BLACK;
			}
		}
		return;
	}

	swapNodesData(temp_node, node);
	deleteNodeRBTree(root, temp_node);
}

Node* deleteDataByKeyRBTree(RBTree* tree, int key)
{
	if (!tree->root)
	{
		return NULL;
	}

	Node* deleting = findNodeByKeyRBTree(tree->root, key);

	if (!deleting)
	{
		return NULL;
	}

	deleteNodeRBTree(tree->root, deleting);

	tree->size--;

	return tree->root;
}

int calculateHeightRBTree(Node* tree)
{
	int left_height = heightRBTree(tree->left);
	int right_height = heightRBTree(tree->right);

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

int heightRBTree(Node* tree)
{
	if (tree)
	{
		return calculateHeightRBTree(tree);
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
		printf("Key: %d; Data: %d; Color: %d;\n", tree->key, tree->data, tree->color);
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
		printf("Key: %d; Data: %d; Color: %d;\n", tree->key, tree->data, tree->color);
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
		printf("Key: %d; Data: %d; Color: %d;\n", tree->key, tree->data, tree->color);
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
		printf("Key: %d; Data: %d; Color: %d;\n", tree->key, tree->data, tree->color);
	}
	else if (level > 1)
	{
		BFTTraversHelper(tree->left, level - 1);
		BFTTraversHelper(tree->right, level - 1);
	}
}

bool BFTTravers(Node* tree)
{
	if (!tree)
	{
		return 1;
	}

	int height = heightRBTree(tree);

	for (int i = 1; i <= height; i++)
	{
		BFTTraversHelper(tree, i);
	}

	return 0;
}

bool deleteRBTree(Node* root)
{
	if (root) {
		deleteRBTree(root->left);
		deleteRBTree(root->right);
		free(root);
		return 0;
	}
	else
	{
		return 1;
	}
}