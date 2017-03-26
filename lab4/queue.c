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

void *push(node_t *tail, proc process){
	node_t *current = tail;

	while(current->next != NULL){
		current = current->next;
	}

	current->next = malloc(sizeof(node_t));
	current->next->process = process;
	current->next->next = NULL;
}

proc *pop(node_t *tail, proc process){
    node_t * next_node = NULL;

    if (*tail->next == NULL) {
        return NULL;
    }

    //might need to do ->next->next
    next_node = (*tail)->next;
    process = next_node->process;
    free(*tail);
    *tail = next_node;
    return &process;
}