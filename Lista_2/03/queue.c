#include <stdlib.h>
#include "queue.h"

_node_queue* Queue_Node_Allocate(){
	return (_node_queue*)calloc(1, sizeof(_node_queue));
}

_queue* Queue_Init(){
	return (_queue*)calloc(1, sizeof(_queue));
}

void Queue_Insert(_queue* queue, void* data){
	_node_queue* new_node = Queue_Node_Allocate();
	new_node->data = data;

	if(queue->size == 0){
		queue->front = new_node;
		queue->rear = new_node;
	}
	else{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
	queue->size += 1;
}

void* Queue_Remove(_queue* queue){
	if(queue->size == 0){
		return NULL;
	}
	_node_queue* next_front = queue->front->next;
	void* data = queue->front->data;

	free(queue->front);
	queue->size -= 1;
	queue->front = next_front;

	return data;
}

void* Queue_Front_Value(_queue* queue){
	if(queue->size == 0){
		return NULL;
	}

	return (queue->front)->data;
}

int Queue_Size(_queue* queue){
	return queue->size;
}
