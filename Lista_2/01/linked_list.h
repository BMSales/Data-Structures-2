#pragma once

typedef struct _LL_node{
	void* data;
	struct _LL_node* next;
}_LL_node;

typedef struct _linkedList{
	int size;
	struct _LL_node* head;
}_linkedList;

_linkedList* LinkedList_Init();
void LinkedList_Insert(_linkedList* linked_list, void* data);
void* LinkedList_Pop(_linkedList* linked_list);
