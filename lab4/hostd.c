/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here

     process currentProc;
     resources res_avail;

// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    //initialize resources
    res_avail.scanners = 1;
    res_avail.modems = 1;
    res_avail.cds = 2;
    res_avail.printers = 2;

    //create queues
    node_t *dispatch = NULL;
    node_t *queue1 = NULL;
    node_t *queue2 = NULL;
    node_t * queue3 = NULL;

    //allocate memory for queues

    dispatch = malloc(sizeof(node_t));
 	dispatch->next = NULL;
 	queue1 = malloc(sizeof(node_t));
 	queue1 ->next = NULL;
 	queue2 = malloc(sizeof(node_t));
 	queue2 ->next = NULL;
 	queue3 = malloc(sizeof(node_t));
 	queue3 ->next = NULL;

    // Load the dispatchlist

    load_dispatch("dispatchlist");

    // Add each process structure instance to the job dispatch list queue
    

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    while(dispatch->next !=NULL ){
        //Add processes
  
    }
    free(dispatch);


    // Allocate the resources for each process before it's executed

    alloc_res(&res_avail, &currentProc);

    // Execute the process binary using fork and exec




    // Perform the appropriate signal handling / resource allocation and de-alloaction


    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}
