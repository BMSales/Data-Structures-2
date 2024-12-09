#pragma once

typedef struct _node{
	int data;
	int height;
	int balance;
	struct _node* left_child;
	struct _node* right_child;
}_node;

typedef struct _binaryTree{
	int size;
	_node* root;
}_binaryTree;

_binaryTree* BinaryTree_Init();

int Height_Return(_node* node);
int Height_Calculate(_node* node);
void BinaryTree_Insert(_binaryTree* tree, int num);
void Binary_Search(_binaryTree* tree, int num);
void AVL_Insert(_binaryTree* tree, int num);
void Binary_Traversal_Inorder(_node* node);
void Binary_Traversal_Preorder(_node* node);
void Binary_Traversal_Postorder(_node* node);
