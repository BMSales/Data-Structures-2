#pragma once

typedef struct _nodeRedBlack{
	int data;
	int color; // 1 is red, 0 is black
	int height;
	struct _nodeRedBlack* left_child;
	struct _nodeRedBlack* right_child;
}_nodeRedBlack;

typedef struct _redBlackTree{
	_nodeRedBlack* root;
}_redBlackTree;

_redBlackTree* RedBlackTree_Init();
void RedBlack_Insert(_redBlackTree* tree, int data);
void RedBlack_Traversal_Inorder(_nodeRedBlack* node);
void RedBlack_Delete(_redBlackTree* tree);

int Height_Calculate(_nodeRedBlack* node);
int Height_Return(_redBlackTree* tree);
