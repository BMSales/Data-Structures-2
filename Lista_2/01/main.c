#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h"
#include "sort_algs.h"

int main(){
	srand(clock());
	_binaryTree* binary_tree = BinaryTree_Init();
	_binaryTree* avl_tree = BinaryTree_Init();
	int* array = Array_Init_Random(10000);
	int random_number = rand() % 50001;
	
	for(int i = 0; i < 10000; i++){
		BinaryTree_Insert(binary_tree, array[i]);
		AVL_Insert(avl_tree, array[i]);
	}

	Height_Calculate(binary_tree->root);
	printf("binary tree height: %d\n", Height_Return(binary_tree->root));
	printf("AVL tree height: %d\n", Height_Return(avl_tree->root));
	Binary_Search(binary_tree, random_number);
	Binary_Search(avl_tree, random_number);
}
