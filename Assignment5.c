#include <stdio.h> //necessary libraries
#include <stdlib.h>

int preSet[5] = {1, 2, 3, 4, 5}; //array of predefined inputs


//creating structure for BST node
struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
	int height;
};


//function for creation of new nodes
struct Node* newNode(int data)
{
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return (node);
}


//creating function to get height of node
int height(struct Node* node)
{
	if(node == NULL)
		return 0;
	return node->height;
}


//checks the larger value of two integers
int max(int x, int y)
{
	return (x > y)? x : y;
}


//function to check balance of nodes
int getBalance(struct Node* node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}


//Function for right rotation on nodes
struct Node* rightRotate(struct Node* b)
{
	struct Node* a = b->left;
	struct Node* c = a->right;

	a->right = b;
	b->left = c;

	b->height = max(height(b->left), height(b->right)) +1;
	a->height = max(height(a->left), height(a->right)) +1;

	return a;
}


//Function for left rotation on nodes
struct Node* leftRotate(struct Node* a)
{
	struct Node* b = a->right;
	struct Node* c = b->left;

	b->left = a;
	a->right = c;

	a->height = max(height(a->left), height(a->right)) +1;
	b->height = max(height(b->left), height(b->right)) +1;

	return b;
}


//creation of function for new node insertion
struct Node* insert(struct Node* node, int data)
{
	if (node == NULL)    //recursive insertion and balancing of node
		return(newNode(data));

	if(data < node->data)
		node->left = insert(node->left, data);

		else if (data > node->data)
			node->right = insert(node->right, data);

			else
				return node;


	node->height = 1 + max(height(node->left), height(node->right));


	int balance = getBalance(node);


	if(balance > 1 && data < node->left->data)
		return rightRotate(node);


	if(balance < -1 && data > node->right->data)
		return leftRotate(node);


	if(balance > 1 && data > node->left->data)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}


	if(balance < -1 && data < node->right->data)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

//function that prints out tree in preorder
void preOrder (struct Node* root)
{
	if(root != NULL)
	{
		printf("%d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}


int main()
{
	printf("Preset numbers: "); //printing out original numbers
		for(int i = 0; i < 5; i++)
		{
			printf("%d ", preSet[i]);
		}


	int x = sizeof(preSet)/sizeof(preSet[0]);
		struct Node* root = NULL;

	printf("\nBST in pre-order: "); //printing out BST
		for(int i = 0; i < x; i++)
		{
			root = insert(root, preSet[i]);
			printf("%d ", preSet[i]);
		}

	printf("\nAVL in pre-order: "); //printing out AVL
	preOrder(root);

	return 0;
}

