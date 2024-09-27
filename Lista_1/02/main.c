#include "heap.h"

int main(){
	_heapQueue* queue = Heap_Queue_Init(100);

	for(int i = 0; i < queue->size; i++){
		Heap_Priority_Queue(queue);
	}

	Heap_Print(queue->heap);
}
