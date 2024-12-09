#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h"
#include "sort_algs.h"

int main(){
	srand(clock());
	_binaryTree* avl_tree = BinaryTree_Init();
	
	AVL_Insert(avl_tree, 70);
	AVL_Insert(avl_tree, 60);
	AVL_Insert(avl_tree, 80);
	AVL_Insert(avl_tree, 50);
	AVL_Insert(avl_tree, 65);
	AVL_Insert(avl_tree, 75);
	AVL_Insert(avl_tree, 85);
	AVL_Insert(avl_tree, 45);
	AVL_Insert(avl_tree, 55);
	AVL_Insert(avl_tree, 90);

	Binary_Traversal_Levelorder(avl_tree);
}
