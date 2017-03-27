/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

void *push(node_t *tail, process proc){
	node_t *current = tail;

	while(current->next != NULL){
		current = current->next;
	}

	current->next = malloc(sizeof(node_t));
	current->next->proc = proc;
	current->next->next = NULL;
}

process *pop(node_t *tail, process proc){
	node_t * next_node = NULL;

	if (*tail->next == NULL) {
		return NULL;
		}

	//might need to do ->next->next
	next_node = (*tail)->next;
	proc = next_node->proc;
	free(*tail);
	*tail = next_node;
	return &proc;
}