#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "red_black.h"
#include "sort_algs.h"

int main(){
    srand(clock());
    _redBlackTree* tree = RedBlackTree_Init();
    int array_size = 10;
    int* array = Array_Init_Random(array_size);

    for(int i = 0; i < array_size; i++){
        RedBlack_Insert(tree, array[i]);
    }

    Height_Calculate(tree->root);
    printf("TREE HEIGHT: %d\n\n", Height_Return(tree));
    RedBlack_Traversal_Inorder(tree->root);
    RedBlack_Delete(tree);
}
