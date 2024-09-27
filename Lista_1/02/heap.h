#pragma once

typedef struct {
	int size;
	int* array;
}_heap;

typedef struct {
	int size;
	_heap* heap;
}_heapQueue;

_heap* Heap_Init();
void Heap_Insert(_heap* heap, int num);
void Heap_Print(_heap* heap);

_heapQueue* Heap_Queue_Init(int size);
void Heap_Priority_Queue(_heapQueue* heap);
