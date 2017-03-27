/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_

// The amount of available memory
#define MEMORY 1024

// Resources structure containing integers for each resource constraint and an
// array of 1024 for the memory
typedef struct{
	int printers, scanners, modems, cds;
} resources;


// Processes structure containing all of the process details parsed from the 
// input file, should also include the memory address (an index) which indicates
// where in the resources memory array its memory was allocated
typedef struct{
	int arrival_time, priority, processor_time, printers[2],
scanners, modems, cds[2], address_index, pid;
	int Mbytes[1024];
	int suspended;
} process;

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following examples:

// Function to allocate a contiguous chunk of memory in your resources structure
// memory array, always make sure you leave the last 64 values (64 MB) free, should
// return the index where the memory was allocated at
extern int alloc_mem(resources res, int size, int Mbytes);

// Function to free the allocated contiguous chunk of memory in your resources
// structure memory array, should take the resource struct, start index, and 
// size (amount of memory allocated) as arguments
extern void free_mem(resources res, int address_index, int size);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
extern void load_dispatch(char *dispatch_file);

//allocate resources
extern int alloc_res(resources* res, process* proc);
//free resources
extern void free_res(resources* res, process proc);

#endif /* UTILITY_H_ */