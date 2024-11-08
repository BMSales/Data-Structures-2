#pragma once

typedef struct {
	int size;
	int* array;
}_heap;

typedef struct {
	int size; //limite de tamanho da heap
	_heap* heap;
}_heapQueue;

_heap* Heap_Init();
void Heap_Insert(_heapQueue* heap, int num);
void Heap_Print(_heap* heap);

_heapQueue* Heap_Queue_Init(int size);
void Priority_Heap_Insert(_heapQueue* heap);
void Priority_Heap_Remove(_heapQueue* heap);
