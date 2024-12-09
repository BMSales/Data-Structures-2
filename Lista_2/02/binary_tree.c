#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "linked_list.h"

_node* Node_Allocate(){
	_node* node = (_node*)calloc(1, sizeof(_node));
	node->left_child = NULL;
	node->right_child = NULL;
	return node;
}

_binaryTree* BinaryTree_Init(){
	_binaryTree* binaryTree = (_binaryTree*)calloc(1, sizeof(_binaryTree));
	binaryTree->root = Node_Allocate();
	return binaryTree;
}



int Height_Calculate(_node* node) {
	if(node == NULL){
		return -1;
	}

	int left_height = Height_Calculate(node->left_child);
	int right_height = Height_Calculate(node->right_child);

	node->height = (left_height > right_height ? left_height : right_height) + 1;
	node->balance = left_height - right_height;
	return node->height;
}

int Height_Return(_node* node){
	if(node == NULL){
		return -1;
	}
	return node->height;
}

void BinaryTree_Insert(_binaryTree* tree, int num){
	_node* current_node = tree->root;
	_node* previous_node = tree->root;
	_node* new_node = Node_Allocate();
	new_node->data = num;

	if(tree->size == 0){
		current_node->data = num;
		tree->size++;
		return;
	}

	tree->size++;
	while(1){
		if(current_node == NULL){
			if(num < previous_node->data){
				previous_node->left_child = new_node;
				break;
			}
			else{
				previous_node->right_child = new_node;
				break;
			}
		}
		previous_node = current_node;
		current_node = num < current_node->data ? current_node->left_child : current_node->right_child;
	}
}
void Binary_Search(_binaryTree* tree, int num){
	_node* current_node = tree->root;
	printf("STARTING SEARCH: %d\n", num);
	while(1){
		if(current_node == NULL){
			printf("not found\n\n");
			break;
		}

		printf("current node: %d\n", current_node->data);
		printf("height: %d\n", current_node->height);
		printf("balance: %d\n\n", current_node->balance);
		if(num == current_node->data){
			printf("found: %d\n\n", current_node->data);
			break;
		}

		current_node = num < current_node->data ? current_node->left_child : current_node->right_child;
	}
}

void Binary_Traversal_Inorder(_node* node){
	if(node == NULL){
		return;
	}
	Binary_Traversal_Inorder(node->left_child);
	printf("current node: %d\n", node->data);
	printf("height: %d\n", node->height);
	printf("balance: %d\n\n", node->balance);
	Binary_Traversal_Inorder(node->right_child);
}

void Binary_Traversal_Preorder(_node* node){
	if(node == NULL){
		return;
	}
	printf("current node: %d\n", node->data);
	printf("height: %d\n", node->height);
	printf("balance: %d\n\n", node->balance);
	Binary_Traversal_Preorder(node->left_child);
	Binary_Traversal_Preorder(node->right_child);
}

void Binary_Traversal_Postorder(_node* node){
	if(node == NULL){
		return;
	}
	Binary_Traversal_Postorder(node->left_child);
	Binary_Traversal_Postorder(node->right_child);
	printf("current node: %d\n", node->data);
	printf("height: %d\n", node->height);
	printf("balance: %d\n\n", node->balance);
}

void AVL_Rotation_LL(_node* node_1, _node* node_2, _node* previous_node, _binaryTree* tree){
	node_1->left_child = node_2->right_child;
	node_2->right_child = node_1;
	
	if(previous_node != NULL){
		if(previous_node->left_child == node_1){
			previous_node->left_child = node_2;
		}
		else{
			previous_node->right_child = node_2;
		}
	}
	else{
		tree->root = node_2;
	}
}

void AVL_Rotation_RR(_node* node_1, _node* node_2, _node* previous_node, _binaryTree* tree){
	node_1->right_child = node_2->left_child;
	node_2->left_child = node_1;
	
	if(previous_node != NULL){
		if(previous_node->left_child == node_1){
			previous_node->left_child = node_2;
		}
		else{
			previous_node->right_child = node_2;
		}
	}
	else{
		tree->root = node_2;
	}
}

void AVL_Rotation_LR(_node* node_1, _node* node_2, _node* previous_node, _binaryTree* tree){
	_node* node_3 = node_2->right_child;

	node_1->left_child = node_3;
	node_2->right_child = node_3->left_child;
	node_3->left_child = node_2;

	AVL_Rotation_LL(node_1, node_3, previous_node, tree);
}

void AVL_Rotation_RL(_node* node_1, _node* node_2, _node* previous_node, _binaryTree* tree){
	_node* node_3 = node_2->left_child;

	node_1->right_child = node_3;
	node_2->left_child = node_3->right_child;
	node_3->right_child = node_2;

	AVL_Rotation_RR(node_1, node_3, previous_node, tree);
}

void AVL_Rotation(_binaryTree* tree, _node** aux_array){
	int rotation = 0;

	if(aux_array[0]->left_child == aux_array[1]){
		rotation++;
		if(aux_array[1]->left_child == aux_array[2]){
			rotation++;
		}
	}
	else if(aux_array[0]->right_child == aux_array[1]){
		rotation--;
		if(aux_array[1]->right_child == aux_array[2]){
			rotation--;
		}
	}

	switch(rotation){
		case 2:
			AVL_Rotation_LL(aux_array[0], aux_array[1], aux_array[3], tree);
			break;
		case 1:
			AVL_Rotation_LR(aux_array[0], aux_array[1], aux_array[3], tree);
			break;
		case -2:
			AVL_Rotation_RR(aux_array[0], aux_array[1], aux_array[3], tree);
			break;
		case -1:
			AVL_Rotation_RL(aux_array[0], aux_array[1], aux_array[3], tree);
			break;
	}
}

void AVL_Insert(_binaryTree* tree, int num){
	_node* current_node = tree->root;
	_node* previous_node = tree->root;
	_node* new_node = NULL;
	_node** aux_array = (_node**)calloc(1, sizeof(_node*));
	_linkedList* stack = LinkedList_Init();

	if(tree->size == 0){
		current_node->data = num;
		tree->size++;
		return;
	}

	while(1){
		if(current_node == NULL){
			new_node = Node_Allocate();
			new_node->data = num;
			LinkedList_Insert(stack, new_node);
			if(num < previous_node->data){
				previous_node->left_child = new_node;
				break;
			}
			else{
				previous_node->right_child = new_node;
				break;
			}
		}
		LinkedList_Insert(stack, current_node);
		previous_node = current_node;
		current_node = num < current_node->data ? current_node->left_child : current_node->right_child;
	}

	tree->size++;
	Height_Calculate(tree->root);

	while(1){
		aux_array[2] = aux_array[1];
		aux_array[1] = aux_array[0];
		aux_array[0] = (_node*)LinkedList_Pop(stack);
		if(aux_array[0] == NULL){
			return;
		}
		if(abs(aux_array[0]->balance) > 1){
			aux_array[3] = (_node*)LinkedList_Pop(stack);
			AVL_Rotation(tree, aux_array);
			Height_Calculate(tree->root);
			return;
		}
	}
}
