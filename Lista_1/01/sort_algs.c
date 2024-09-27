#include <stdio.h>
#include <stdlib.h>
#include "sort_algs.h"

void Swap(int* a, int* b){
	int swapper;
	swapper = *a;
	*a = *b;
	*b = swapper;
}

_operations* Operations_Init(){
	return (_operations*)calloc(1, sizeof(_operations));
}

void Operations_Reset(_operations* operations){
	operations->comp = 0;
	operations->attrib = 0;
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

int* Array_Init_Empty(int size){
	int* pointer;
	Array_Alloc(&pointer, size);
	return pointer;
}

int* Array_Init_Random(int size){
	int* pointer;
	Array_Alloc(&pointer, size);
	Array_Fill_Random(pointer, size);
	return pointer;
}

void Array_Copy(int* array_1, int* array_2, int size){
	for(int i = 0; i < size; i++){
		array_2[i] = array_1[i];
	}
}

void Array_Print(int* array, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int* Array_Clip(int* array, int from, int to, _operations* operations){
	// "from" and "to" refer to index positions 
	// Example: "from" 0 "to" 9 
	int* clipped_array;
	int size = (to - from) + 1;
	operations->attrib++;

	if(size <= 0){
		printf("ERROR: invalid index parameters\n");
		exit(-1);
	}

	Array_Alloc(&clipped_array, size);

	for(int i = 0; i < size; i++){
		clipped_array[i] = array[from + i];
		operations->attrib++;
	}

	return clipped_array;
}

void Merge_Sort(int* array, int size, _operations* operations){

	if(size == 1){
		return;
	}

	if(size > 1){
		int* first_half = Array_Clip(array, 0, (size/2) - 1, operations);
		int* second_half = Array_Clip(array, size/2, size - 1, operations);
		int subSize_1 = size/2; 
		int subSize_2 = size - size/2;
		int subPointer_1 = 0;
		int subPointer_2 = 0;
		int arrayPointer = 0;
		
		Merge_Sort(first_half, subSize_1, operations);
		Merge_Sort(second_half, subSize_2, operations);

		while(subPointer_1 < subSize_1 && subPointer_2 < subSize_2){

			operations->comp++;
			if(first_half[subPointer_1] <= second_half[subPointer_2]){
				operations->attrib++;
				array[arrayPointer] = first_half[subPointer_1];
				subPointer_1++;
			}
			else{
				operations->attrib++;
				array[arrayPointer] = second_half[subPointer_2];
				subPointer_2++;
			}
			arrayPointer++;
		}

		if(subPointer_1 == subSize_1){
			for(int i = arrayPointer; i < size; i++){
				operations->attrib++;
				array[i] = second_half[subPointer_2];
				subPointer_2++;
			}
		}
		else{
			for(int i = arrayPointer; i < size; i++){
				operations->attrib++;
				array[i] = first_half[subPointer_1];
				subPointer_1++;
			}
		}

		free(first_half);
		free(second_half);
		return;
	}
}

void Shell_Sort(int* array, int size, _operations* operations){
	int stepSize = 1;
	int i, j, key;

	while(stepSize <= (size - 1)/3){
		operations->attrib++;
		stepSize = 3 * stepSize + 1;
	}

	while(stepSize > 0){
		for(j = stepSize; j < size; j++){
			operations->attrib += 2;
			key = array[j];
			i = j;
			while(i - stepSize >= 0 && key <= array[i - stepSize]){
				operations->comp += 2;
				operations->attrib += 2;
				array[i] = array[i - stepSize];
				i = i - stepSize;
			}
			operations->attrib++;
			array[i] = key;
		}
		operations->attrib++;
		stepSize = (stepSize - 1)/3;
	}
}

void Quick_Sort_Func(int* array, int start, int end, _operations* operations){
	if(end - start < 1){
		return;
	}

	int pivot = end;
	int swap_marker = start - 1;

	for(int i = start; i <= end; i++){
		operations->comp++;
		if(array[i] > array[pivot]){
			continue;
		}
		else{
			swap_marker++;
			operations->comp++;
			if(i > swap_marker){
				operations->attrib++;
				Swap(&array[i], &array[swap_marker]);
			}
		}
	}

	Quick_Sort_Func(array, start, swap_marker - 1, operations);
	Quick_Sort_Func(array, swap_marker + 1, end, operations);
}

void Quick_Sort(int* array, int size, _operations* operations){
	Quick_Sort_Func(array, 0, size - 1, operations);
}

void Heap_Reheap_Down(int* array, int position, int size, _operations* operations){
	int largest = position;
	int left_child = position * 2 + 1;
	int right_child = position * 2 + 2;

	operations->comp++;
	if(left_child < size && array[largest] < array[left_child]){
			largest = left_child;
	}

	operations->comp++;
	if(right_child < size && array[largest] < array[right_child]){
			largest = right_child;
	}

	if(largest != position){
		operations->attrib++;
		Swap(&array[largest], &array[position]);
		Heap_Reheap_Down(array, largest, size, operations);
	}
}

void Heap_Heapify(int* array, int size, _operations* operations){
	for(int i = size/2 - 1; i >= 0; i--){
		Heap_Reheap_Down(array, i, size, operations);
	}
}

void Heap_Sort(int* array, int size, _operations* operations){

	Heap_Heapify(array, size, operations);

	for(int i = size - 1; i > 0; i--){
		operations->attrib++;
		Swap(&array[0], &array[i]);
		Heap_Reheap_Down(array, 0, i, operations);
	}
}
