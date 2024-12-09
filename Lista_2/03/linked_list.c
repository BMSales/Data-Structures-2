#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

_LL_node* LinkedList_Allocate(){
	return (_LL_node*)calloc(1, sizeof(_LL_node));
}

_linkedList* LinkedList_Init(){
	return (_linkedList*)calloc(1, sizeof(_linkedList));
}

void LinkedList_Insert(_linkedList* linked_list, void* data){
	_LL_node* new_node = LinkedList_Allocate();

	new_node->data = data;
	new_node->next = linked_list->head;
	linked_list->head = new_node;
	linked_list->size++;
}

void* LinkedList_Pop(_linkedList* linked_list){
	_LL_node* top_node = linked_list->head;
	void* data = NULL;

	if(top_node == NULL){
		return NULL;
	}

	data = top_node->data;
	linked_list->head = top_node->next;
	linked_list->size--;
	free(top_node);
	return data;
}
