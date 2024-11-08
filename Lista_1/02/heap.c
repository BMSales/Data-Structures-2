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

void Heap_Reheap_Up(_heap* heap, int index_position){
	int parent_node = 0;
	if(index_position == 0){
			return;
	}

	parent_node = ((index_position + 1)/2) - 1;
	
	if(heap->array[index_position] <= heap->array[parent_node]){
		return;
	}
	else{
		Swap(&heap->array[index_position], &heap->array[parent_node]);
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
	for(int i = heap->size; i > 0; i--){
		Heap_Reheap_Up(heap, i - 1);
	}
}

void Heap_Insert(_heapQueue* heapQueue, int num){
	_heap* heap = heapQueue->heap;

	if(heap->size >= heapQueue->size){
		printf("Heap is full!\n");
		return;
	}
	if(heap->size == 0){
		heap->size++;
		heap->array[0] = num;
		return;
	}
	heap->size++;
	heap->array = (int*)realloc(heap->array, heap->size * sizeof(int));
	heap->array[heap->size - 1] = num;
	Heap_Heapify(heap);
}

void Heap_Remove(_heapQueue* heapQueue){
	_heap* heap = heapQueue->heap;

	if(heap->size == 1){
		heap->array[0] == 0;
		heap->size--;
		return;
	}

	Swap(&heap->array[0], &heap->array[heap->size - 1]);
	heap->size--;
	heap->array = (int*)realloc(heap->array, heap->size * sizeof(int));

	Heap_Reheap_Down(heap, 0);
}

int Key_Gen(){
	int priority = (rand() % 3) + 1;
	static int position_queue[3] = {999, 999, 999}; //Ordem de chegada. 999 chega primeiro, depois 998, 997...
	int key = 0;

	key = priority * 1000 + position_queue[priority - 1];

	if(position_queue[priority - 1] != 0){
		position_queue[priority - 1]--;
		return key;
	}
	else{
		return 0;
	}
}

void Priority_Heap_Insert(_heapQueue* heapQueue){
	int key = Key_Gen();

	Heap_Insert(heapQueue, key);
}

void Priority_Heap_Remove(_heapQueue* heapQueue){
	Heap_Remove(heapQueue);
}


