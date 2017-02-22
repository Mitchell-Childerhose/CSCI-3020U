/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

using namespace std;

// Put macros or constants here using #define
#define BUFFER_LEN 256
extern char **environ;

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };

    char PWD[BUFFER_LEN] = { 0 }; 

 
    // if (getcwd(PWD, sizeof(PWD)) != NULL)
    //    fprintf(stdout, "Current working dir: %s\n", cwd);
    // else
    //    perror("getcwd() error");
    // return 0;

    // Parse the commands provided using argc and arg
    const char s[2] = " ";
    char *token;

    DIR *d = opendir(arg);
    struct dirent *dir;
    int i = 1;
    char *strings = *environ;            

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        printf("%s\n", buffer);

        //removing new line character
        if(buffer[strlen(buffer)-1] == '\n'){
            buffer[strlen(buffer)-1] = '\0';
        }

        //putting first input into command
        token = strtok(buffer, s);
        strcpy(command, token);

        //putting rest into arg is not null
        token = strtok(NULL, "");
        if (token !=NULL){
            strcpy(arg, token);
        }
        
        printf("Command: %s\n", command);
        printf("Arg: %s\n", arg);


        // Perform string tokenization to get the command and argument

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
           chdir(arg);  
           PWD = *getcwd(arg, sizeof(arg));   
        }

        // other commands here...
        else if (strcmp(command, "clr") == 0){
            system("clear");
        }

        else if (strcmp(command, "dir") == 0){
            if (d){
                while ((dir = readdir(d)) != NULL){
                    printf("%s\n", dir->d_name);
                }

                closedir(d);
            }
        }

        else if (strcmp(command, "environ") == 0){
            for (; strings; i++){
                printf("%s\n", strings);
                strings = *(environ+i);
            }
        }

        else if (strcmp(command, "echo") == 0){
            printf("%s\n", arg);
        }

        else if (strcmp(command, "help") == 0){
            
        }

        else if (strcmp(command, "pause") == 0){
            cin.get();
        }        
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

        token = strtok(NULL, s);

    }
    return EXIT_SUCCESS;
}