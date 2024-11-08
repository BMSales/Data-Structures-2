#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main(){
	srand(clock());
	_heapQueue* queue = Heap_Queue_Init(7);

	for(int i = 0; i < queue->size; i++){
		Priority_Heap_Insert(queue);
	}

	Heap_Print(queue->heap);

	Priority_Heap_Remove(queue);

	Heap_Print(queue->heap);
}
