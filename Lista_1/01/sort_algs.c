#include <stdio.h>
#include <stdlib.h>
#include "sort_algs.h"

void Swap(int* a, int* b){
	int swapper;
	swapper = *a;
	*a = *b;
	*b = swapper;
}

void Array_Alloc(int** array, int size){
	(*array) = (int*)calloc(size, sizeof(int));
}

void Array_Fill_Random(int* array, int size){
	int constant = size * 5;
	for(int i = 0; i < size; i++){
		array[i] = rand() % constant;
	}
}

int* Array_Init(int size){
	int* pointer;
	Array_Alloc(&pointer, size);
	Array_Fill_Random(pointer, size);
	return pointer;
}

void Array_Print(int* array, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int* Array_Clip(int* array, int from, int to){
	// "from" and "to" refer to index positions 
	// Example: "from" 0 "to" 9 
	int* clipped_array;
	int size = (to - from) + 1;

	if(size <= 0){
		printf("ERROR: invalid index parameters\n");
		exit(-1);
	}

	Array_Alloc(&clipped_array, size);

	for(int i = 0; i < size; i++){
		clipped_array[i] = array[from + i];
	}

	return clipped_array;
}

void Merge_Sort(int* array, int size){
	if(size == 1){
		return;
	}
	if(size > 1){
		int* first_half = Array_Clip(array, 0, (size/2) - 1);
		int* second_half = Array_Clip(array, size/2, size - 1);
		int subSize_1 = size/2; 
		int subSize_2 = size - size/2;
		int subPointer_1 = 0;
		int subPointer_2 = 0;
		int arrayPointer = 0;
		
		Merge_Sort(first_half, subSize_1);
		Merge_Sort(second_half, subSize_2);

		while(subPointer_1 < subSize_1 && subPointer_2 < subSize_2){
			if(first_half[subPointer_1] <= second_half[subPointer_2]){
				array[arrayPointer] = first_half[subPointer_1];
				subPointer_1++;
			}
			else{
				array[arrayPointer] = second_half[subPointer_2];
				subPointer_2++;
			}
			arrayPointer++;
		}

		if(subPointer_1 == subSize_1){
			for(int i = arrayPointer; i < size; i++){
				array[i] = second_half[subPointer_2];
				subPointer_2++;
			}
		}
		else{
			for(int i = arrayPointer; i < size; i++){
				array[i] = first_half[subPointer_1];
				subPointer_1++;
			}
		}

		free(first_half);
		free(second_half);
		return;
	}
}

void Shell_Sort(int* array, int size){
	int stepSize = 1;
	int i, j, key;

	while(stepSize <= (size - 1)/3){
		stepSize = 3 * stepSize + 1;
	}

	while(stepSize > 0){
		for(j = stepSize; j < size; j++){
			key = array[j];
			i = j;
			while(i - stepSize >= 0 && key <= array[i - stepSize]){
				array[i] = array[i - stepSize];
				i = i - stepSize;
			}
			array[i] = key;
		}
		stepSize = (stepSize - 1)/3;
	}
}

void Quick_Sort_Func(int *array, int start, int end){
	if(end - start < 1){
		return;
	}

	int pivot = end;
	int swap_marker = start - 1;

	for(int i = start; i <= end; i++){
		if(array[i] > array[pivot]){
			continue;
		}
		else{
			swap_marker++;
			if(i > swap_marker){
				Swap(&array[i], &array[swap_marker]);
			}
		}
	}

	Quick_Sort_Func(array, start, swap_marker - 1);
	Quick_Sort_Func(array, swap_marker + 1, end);
}

void Quick_Sort(int* array, int size){
	Quick_Sort_Func(array, 0, size - 1);
}
