#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h"
#include "sort_algs.h"

int main(){
	srand(clock());
	_binaryTree* binary_tree = BinaryTree_Init();
	_binaryTree* avl_tree = BinaryTree_Init();
	int* array = Array_Init_Random(10);
	
	for(int i = 0; i < 10; i++){
		BinaryTree_Insert(binary_tree, array[i]);
		AVL_Insert(avl_tree, array[i]);
	}

	Height_Calculate(binary_tree->root);

	printf("-IN ORDER TRAVERSAL-\n");
	printf("BINARY TREE:\n");
	Binary_Traversal_Inorder(binary_tree->root);
	printf("AVL TREE:\n");
	Binary_Traversal_Inorder(avl_tree->root);

	printf("-PRE ORDER TRAVERSAL-\n");
	printf("BINARY TREE:\n");
	Binary_Traversal_Preorder(binary_tree->root);
	printf("AVL TREE:\n");
	Binary_Traversal_Preorder(avl_tree->root);

	printf("-POST ORDER TRAVERSAL-\n");
	printf("BINARY TREE:\n");
	Binary_Traversal_Postorder(binary_tree->root);
	printf("AVL TREE:\n");
	Binary_Traversal_Postorder(avl_tree->root);
}
