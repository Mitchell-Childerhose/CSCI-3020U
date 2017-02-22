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
 #include <sys/stat.h>

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
    char arg[BUFFER_LEN] = {};  
    char PWD[BUFFER_LEN]; 

 
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
    struct stat st;          

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        //printf("%s\n", buffer);

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
        
        //printf("Command: %s\n", command);
        //printf("Arg: %s\n", arg);

        // Perform string tokenization to get the command and argument

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {  
            //if directory inputted does not exist
            if(stat(arg,&st) != 0){
                printf("Error: The directory does not exist.\n");
            //else change directory and update PWD
            }else{
                chdir(arg);
                getcwd(PWD, sizeof(arg));
            }

            //if arguement not given, print working directory
            if(strlen(arg) == 0){
                printf("%s\n",PWD);
            }

            //resetting arg so "cd" works is used multiple times
            arg[0] = 0;                         
        }

        // other commands here...
        else if (strcmp(command, "pwd") == 0){
            system("pwd");
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
            printf("Commands:\n"
                "cd <directory> - Change the current default directory to <directory>\n"
                "clr - Clear the screen\n"
                "dir <directory> - List the contents of directory <directory>\n"
                "environ - List all the environment strings\n"
                "echo <comment> - Display <comment> on the display followed by a new line\n"
                "help - Display the user manual using the more filter\n"
                "pause - Pause operation of the shell until 'Enter' is pressed\n"
                "quit - Quit the shell");
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