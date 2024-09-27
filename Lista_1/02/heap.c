#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void Swap(int* a, int* b){
	int swapper;
	swapper = *a;
	*a = *b;
	*b = swapper;
}

_heap* Heap_Init(){
	_heap* heap = (_heap*)calloc(1, sizeof(_heap));
	heap->size = 0;
	heap->array = (int*)calloc(1, sizeof(int));
	return heap;
}

_heapQueue* Heap_Queue_Init(int size){
	_heapQueue* heapQueue = (_heapQueue*)calloc(1, sizeof(_heapQueue));
	heapQueue->size = size;
	heapQueue->heap = Heap_Init();
	return heapQueue;
}

void Heap_Print(_heap* heap){
	for(int i = 0; i < heap->size; i++){
		printf("%d ", heap->array[i]);
	}
	printf("\n\n");
}

void Heap_Reheap_Up(_heap* heap, int position){
	int parent_node = (position - 1)/2;
	if(parent_node == 0){
		return;
	}
	else if(heap->array[position] <= heap->array[parent_node]){
		return;
	}
	else{
		Swap(&heap->array[position], &heap->array[parent_node]);
		Heap_Reheap_Up(heap, parent_node);
	}
}

void Heap_Reheap_Down(_heap* heap, int parent_node){
int largest = parent_node;
	int left_child = parent_node * 2 + 1;
	int right_child = parent_node * 2 + 2;

	if(left_child < heap->size){
		if(heap->array[largest] < heap->array[left_child]){
			largest = left_child;
		}
	}

	if(right_child < heap->size){
		if(heap->array[largest] < heap->array[right_child]){
			largest = right_child;
		}
	}

	if(largest != parent_node){
		Swap(&heap->array[largest], &heap->array[parent_node]);
		Heap_Reheap_Down(heap, largest);
	}
}

void Heap_Heapify(_heap* heap){
	for(int i = heap->size - 1; i > 0; i--){
		Heap_Reheap_Up(heap, i);
	}
}

void Heap_Insert(_heap* heap, int num){
	if(heap->size == 0){
		heap->size++;
		heap->array[0] = num;
		return;
	}
	heap->size++;
	heap->array = (int*)realloc(heap->array, heap->size * sizeof(int));
	heap->array[heap->size - 1] = num;
	Heap_Reheap_Up(heap, heap->size - 1);
}

void Heap_Priority_Queue(_heapQueue* heapQueue){
	int queue_size = heapQueue->size;
	int heap_size = heapQueue->heap->size;

	if(heap_size >= queue_size){
		printf("Queue is full!\n");
		return;
	}

	Heap_Insert(heapQueue->heap, queue_size - heap_size);
}
