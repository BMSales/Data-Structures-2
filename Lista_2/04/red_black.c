#include <stdio.h>
#include <stdlib.h>
#include "red_black.h"

#define RED 1
#define BLACK 0

 _nodeRedBlack* NodeRedBlack_Allocate(){
    return (_nodeRedBlack*)calloc(1, sizeof(_nodeRedBlack));
}

_redBlackTree* RedBlackTree_Init(){
    return (_redBlackTree*)calloc(1, sizeof(_redBlackTree));
}

_nodeRedBlack* NodeRedBlack_Create(int data){
    _nodeRedBlack* new_node = NodeRedBlack_Allocate();
    new_node->data = data;
    new_node->color = RED;
    return new_node;
}

_nodeRedBlack* RedBlack_Rotate_Left(_nodeRedBlack* node){
    _nodeRedBlack* child = node->right_child;
    _nodeRedBlack* childLeft = child->left_child;
 
    child->left_child = node;
    node->right_child = childLeft;
 
    return child;
}
 
_nodeRedBlack* RedBlack_Rotate_Right(_nodeRedBlack* node){
    _nodeRedBlack* child = node->left_child;
    _nodeRedBlack* childRight =  child->right_child;
 
    child->right_child = node;
    node->left_child = childRight;

    return child;
}
 
int Is_Red(_nodeRedBlack* node){
    if (node == NULL){ 
       return 0;
    }
    return (node->color == RED);
}
 
void Swap_Colors(_nodeRedBlack* node_a, _nodeRedBlack* node_b){
    int color = node_a->color;
    node_a->color = node_b->color;
    node_b->color = color;
}
 
_nodeRedBlack* RedBlack_Insert_Func(_nodeRedBlack* node, int data){
    if(node == NULL){
        return NodeRedBlack_Create(data);
    }
    if (data < node->data){
        node->left_child = RedBlack_Insert_Func(node->left_child, data);
    }
    else if (data > node->data){
        node->right_child = RedBlack_Insert_Func(node->right_child, data);
    }
    else{
        return node;
    }

    // case 1.
    // when right child is Red but left child is
    // Black or doesn't exist.
    if (Is_Red(node->right_child) && !Is_Red(node->left_child)){
        node = RedBlack_Rotate_Left(node);
        Swap_Colors(node, node->left_child);
    }
 
    // case 2
    // when left child as well as left grand child in Red
    if (Is_Red(node->left_child) && Is_Red(node->left_child->left_child)){
        node = RedBlack_Rotate_Right(node);
        Swap_Colors(node, node->right_child);
    }

    // case 3
    // when both left and right child are Red in color.
    if (Is_Red(node->left_child) && Is_Red(node->right_child)){
        node->color = !node->color;
        node->left_child->color = BLACK;
        node->right_child->color = BLACK; 
    }
 
    return node;
}

void RedBlack_Insert(_redBlackTree* tree, int data){
    if (tree->root == NULL) {
        tree->root = NodeRedBlack_Create(data);
        tree->root->color = BLACK;
        return;
    }
    tree->root = RedBlack_Insert_Func(tree->root, data);
    tree->root->color = BLACK;
}
 
void RedBlack_Traversal_Inorder(_nodeRedBlack* node){
    if(node != NULL){
        RedBlack_Traversal_Inorder(node->left_child);
        printf("current node: %d\n", node->data);
        printf("current color: %d\n", node->color);
        printf("current height: %d\n\n", node->height);
        RedBlack_Traversal_Inorder(node->right_child); 
    }
}

void RedBlack_Delete_Func(_nodeRedBlack* node){
    if(node != NULL){
        RedBlack_Delete_Func(node->left_child);
        RedBlack_Delete_Func(node->right_child);
        free(node);
    }
}

void RedBlack_Delete(_redBlackTree* tree){
    RedBlack_Delete_Func(tree->root);
    free(tree);
}

int Height_Calculate(_nodeRedBlack* node) {
	if(node == NULL){
		return -1;
	}

	int left_height = Height_Calculate(node->left_child);
	int right_height = Height_Calculate(node->right_child);

	node->height = (left_height > right_height ? left_height : right_height) + 1;
	return node->height;
}

