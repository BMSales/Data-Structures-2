#pragma once

typedef struct _operations{
	long long comp;
	long long attrib;
}_operations;

_operations* Operations_Init();
void Operations_Reset(_operations* operations);

int* Array_Init_Empty(int size);
int* Array_Init_Random(int size);
void Array_Copy(int* array_1, int* array_2, int size);
void Array_Print(int* array, int size);

void Merge_Sort(int* array, int size, _operations* operations);
void Shell_Sort(int* array, int size, _operations* operations);
void Quick_Sort(int* array, int size, _operations* operations);
void Heap_Sort(int* array, int size, _operations* operations);
