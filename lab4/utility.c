/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

// Define your utility functions here, you will likely need to add more...

int alloc_mem(resources res, int size, int Mbytes){
	int allocated;

	int check = 1;

	//loop through memory
	for(int i = allocated ; i < allocated + size; i++){
		if(res->memory[i] == 1){
			check = 0;
			allocated = i;
			break;
		}
	}
	    
	//allocated the memory that is found
	if(check = 1){
		for(int i = allocated; i < allocated + size; i++){
			res->memory[x]=1;
		}
		return allocated;

	}
}

void free_mem(resources res, int address_index, int size){
	for(int i = address_index; i < address + size; i++){
    	res->Mbytes[i] = 0;
	}
}

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
void load_dispatch(char *dispatch_file){	
	FILE *file;
	file = fopen(dispatch_file, "r");	
	char* comma = ", ";
	char* token;

	//the array containing the 8 pieces of data for each process
	int array[8];

	//reading the comma sepparated values from the dispatch list
	if(file != NULL){
		char line[30];
		//read line by line
		while(fgets(line, sizeof line, file) != NULL){
        	token = strtok(line, comma);
        	for(i = 0; i < 8; i++){
            	array[i] = atoi(token);
            	token = strtok(NULL, comma);
			}
		}
    	fclose(file);
	}else{
		printf("Error reading file.")
	}

	process created_process = (process){.arrival_time = array[0], .priority = array[1],
		.processor_time = array[2], .Mbytes = array[3],.printers = array[4],
		.scanners = array[5], .modems = array[6], .cds = array[7],
		.address_index = 0, .suspended = 0};

	//push to process onto the queue
	//push(node_t, created_process);
}

//allocate resources
int alloc_res(resources* res, process* proc){

}

//free resources
void free_res(resources* res, process proc){

	free_mem(res, proc.address_index, proc.Mbytes);

	if(res->scanners == 1){
		res->scanners = 0;
	}

	if(res->modems == 1){
		res->modems = 0;
	}

	int num = proc.printers;
	for(int i = 0; i < 2; i++){
		if(num == 0) break;
		if(res->printers[i] == 1){
			res->printers[i] = 0;
		}
	}

	num = proc.cds;
	for(int i = 0; i < 2; i++){
		if(num == 0) break;
		if(res->cds[i] == 1){
			res->cds[i] = 0;
		}
	}
}
