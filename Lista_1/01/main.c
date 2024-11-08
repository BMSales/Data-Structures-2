#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort_algs.h"

int main(){
	srand(clock());

	int size = 10000000;
	int* array_raw = Array_Init_Random(size);
	int* array_sort = Array_Init_Empty(size);

	_operations* operations = Operations_Init();
	clock_t start, end;
	float seconds;

	Array_Copy(array_raw, array_sort, size);

	printf("Merge Sort\n");
	start = clock();
	Merge_Sort(array_sort, size, operations);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time in milliseconds: %f\n", 1000 * seconds);
	printf("number of comparisons: %lld\n", operations->comp);
	printf("number of attributions: %lld\n\n", operations->attrib);

	Array_Copy(array_raw, array_sort, size);
	Operations_Reset(operations);

	printf("Quick Sort\n");
	start = clock();
	Quick_Sort(array_sort, size, operations);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time in milliseconds: %f\n", 1000 * seconds);
	printf("number of comparisons: %lld\n", operations->comp);
	printf("number of attributions: %lld\n\n", operations->attrib);

	Array_Copy(array_raw, array_sort, size);
	Operations_Reset(operations);

	printf("Heap Sort\n");
	start = clock();
	Heap_Sort(array_sort, size, operations);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time in milliseconds: %f\n", 1000 * seconds);
	printf("number of comparisons: %lld\n", operations->comp);
	printf("number of attributions: %lld\n\n", operations->attrib);

	Array_Copy(array_raw, array_sort, size);
	Operations_Reset(operations);

	printf("Shell Sort\n");
	start = clock();
	Shell_Sort(array_sort, size, operations);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("time in milliseconds: %f\n", 1000 * seconds);
	printf("number of comparisons: %lld\n", operations->comp);
	printf("number of attributions: %lld\n\n", operations->attrib);

	free(array_raw);
	free(array_sort);
	free(operations);
	return 0;
}
