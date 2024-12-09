#pragma once

typedef struct _node_queue{
	void* data;
	struct _node_queue* next;
}_node_queue;

typedef struct _queue{
	int size;
	struct _node_queue* front;
	struct _node_queue* rear;
}_queue;

_queue* Queue_Init();
void Queue_Insert(_queue* queue, void* data);
void* Queue_Remove(_queue* queue);
void* Queue_Front_Value(_queue* queue);
int Queue_Size(_queue* queue);
