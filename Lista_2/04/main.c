#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "red_black.h"
#include "sort_algs.h"

int main(){
    srand(clock());
    _redBlackTree* tree = RedBlackTree_Init();
    int* array = Array_Init_Random(10000);

    for(int i = 0; i < 10000; i++){
        RedBlack_Insert(tree, array[i]);
    }

    Height_Calculate(tree->root);
    RedBlack_Traversal_Inorder(tree->root);
    RedBlack_Delete(tree);
}
