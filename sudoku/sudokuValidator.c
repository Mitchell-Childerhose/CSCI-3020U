/*
 * By: Mitchell Childerhose (100553756)
 *     Kevin Lovell (100559665)
 *
 * Course: CSCI3020U Operating Systems
 *
 * Compile with command: make all
 * 
 * Compile/run with commands: clang -std=c99 sudokuValidator.c -lpthread
 *                            ./a.out
 */

#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#define true 1
#define false 0

//The arguments passed to each thread
//row: the puzzle's row
//column: the puzzle's column
//grid: the pointer to the puzzle array
typedef struct{
    int row, column, (* grid)[9];
} args;

//Validates that each 3x3 subgrid in the sudoku puzzle has unique
//values from 1 to 9. Zeroes are empty squares and are ignored
//returns true if subgrids are valid, false if invalid 
//Nine threads use this function, one for each of the subgrids
void* checkSubgrids(void* arg){

    //specifying argument is if type args*
    args* numbers;
    numbers = (args*) arg;
    //getting the row and column values from the struct that is passed
    int rows = numbers->row, columns = numbers->column;
    int current;

    //initialize an array to check the subgrid
    int checked[10] = {0};
    //loop from the starting row to 3 rows after
    for(int i = rows;i < rows + 3;i++){
        //loop from the starting column to 3 columns after
        for(int j = columns;j < columns + 3;j++){
            //checking that there are no repeats in the subgrid
            //and that zeroes are ignored
            current = numbers->grid[i][j];
            if((checked[current] != 0) && (current != 0)){
                return (void*) false;
            }else{
                checked[current]++;
            }
        }
    }

    return (void*) true;
}

//Validates that each row in the sudoku puzzle has unique
//values from 1 to 9. Zeroes are empty squares and are ignored 
//returns true if rows are valid, false if invalid
//The rows_t thread uses this function
void* checkRows(void* arg){

    //specifying argument is if type args*
    args* numbers;
    numbers = (args*) arg;
    //getting the row and column values from the struct that is passed
    int rows = numbers->row, columns = numbers->column; 
    int current;   
    
    //loop through rows of sudoku
    for(int i = rows;i < 9;i++){
        //initialize a row array to check each row
        int r[10] = {0};
        //loop through columns of sudoku
        for(int j = columns;j < 9;j++){
            current = numbers->grid[i][j];
            //checking that there are no repeats in the row
            //and that zeroes are ignored
            if((r[current] != 0) && (current != 0)){
                return (void*) false;
            }else{
                //updating the value that is found
                r[current]++;
            }
        }
    }

    return (void*) true;
}

//Validates that each column in the sudoku puzzle has unique
//values from 1 to 9. Zeroes are empty squares and are ignored
//returns true if columns are valid, false if invalid 
//The columns_t thread uses this function
void* checkColumns(void* arg){

    //specifying argument is if type args*
    args* numbers;
    numbers = (args*) arg;
    //getting the row and column values from the struct that is passed
    int rows = numbers->row, columns = numbers->column;
    int current;

    //loop through columns of sudoku
    for(int i = columns;i < 9;i++){
        //initialize a column array to check each column
        int c[10] = {0};
        for(int j = rows; j < 9; j++){
            current = numbers->grid[j][i];
            //checking that there are no repeats in the column
            //and that zeroes are ignored
            if((c[current] != 0) && (current != 0)){
                return (void*) false;
            }
            else{
                //updating the value that is found
                c[current]++;
            }
        }
    }

    return (void*) true;
}

//main function reads data from the puzzle.txt file
//stores values in grid[9][9] array
int main(void) {

    int grid[9][9];
    FILE *file = fopen("puzzle.txt", "r");

    //getting each element of the 9x9 grid
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            int num;
            if(fscanf(file, " %d", &num) != 1)
                puts("Invalid txt file.");
            else
                grid[i][j] = num;

            //printf("%d ", grid[i][j]);        
        }

        //printf("\n");
    }

    fclose(file);
    
    //allocating memory block for each thread of the
    //10 threads that will be created
    args* args1 = (args*)malloc(sizeof(args));
    args* args2 = (args*)malloc(sizeof(args));
    args* args3 = (args*)malloc(sizeof(args));
    args* args4 = (args*)malloc(sizeof(args));
    args* args5 = (args*)malloc(sizeof(args));
    args* args6 = (args*)malloc(sizeof(args));
    args* args7 = (args*)malloc(sizeof(args));
    args* args8 = (args*)malloc(sizeof(args));
    args* args9 = (args*)malloc(sizeof(args));
    args* arsg10 = (args*)malloc(sizeof(args));

    //initialize grids for check rows and columns
    args1->row = 0;
    args1->column = 0;
    args1->grid = grid;   

    //intialize subgrids
    args2->row = 0; args2->column = 0; args2->grid = grid;    
    args3->row = 0; args3->column = 3; args3->grid = grid;    
    args4->row = 0; args4->column = 6; args4->grid = grid;    
    args5->row = 3; args5->column = 0; args5->grid = grid;    
    args6->row = 3; args6->column = 3; args6->grid = grid;    
    args7->row = 3; args7->column = 6; args7->grid = grid;    
    args8->row = 6; args8->column = 0; args8->grid = grid;    
    args9->row = 6; args9->column = 3; args9->grid = grid;    
    arsg10->row = 6; arsg10->column = 6; arsg10->grid = grid;

    //initializing threads for each check
    pthread_t rows_t, columns_t, t1, t2, t3, t4, t5, t6, t7, t8, t9;
    
    //thread creation for each check
    //one thread to check rows, one thread to check columns
    //9 threads to check the subgrids
    pthread_create(&rows_t, NULL, checkRows, (args*)args1);
    pthread_create(&columns_t, NULL, checkColumns, (args*)args1);
    pthread_create(&t1, NULL, checkSubgrids, (args*)args2);
    pthread_create(&t2, NULL, checkSubgrids, (args*)args3);
    pthread_create(&t3, NULL, checkSubgrids, (args*)args4);
    pthread_create(&t4, NULL, checkSubgrids, (args*)args5);
    pthread_create(&t5, NULL, checkSubgrids, (args*)args6);
    pthread_create(&t6, NULL, checkSubgrids, (args*)args7);
    pthread_create(&t7, NULL, checkSubgrids, (args*)args8);
    pthread_create(&t8, NULL, checkSubgrids, (args*)args9);
    pthread_create(&t9, NULL, checkSubgrids, (args*)arsg10);

    //return of each thread
    void *rows_return, *cols_return, *sg1_return, *sg2_return,
         *sg3_return, *sg4_return, *sg5_return, *sg6_return,
         *sg7_return, *sg8_return, *sg9_return;

    //wait for termination of threads, 2nd parameter is return value
    pthread_join(rows_t, &rows_return);
    pthread_join(columns_t, &cols_return);
    pthread_join(t1, &sg1_return);
    pthread_join(t2, &sg2_return);
    pthread_join(t3, &sg3_return);
    pthread_join(t4, &sg4_return);
    pthread_join(t5, &sg5_return);
    pthread_join(t6, &sg6_return);
    pthread_join(t7, &sg7_return);
    pthread_join(t8, &sg8_return);
    pthread_join(t9, &sg9_return);

    //Of any of the threads return false,
    //the sudoku puzzle is invalid. Otherwise, it is valid.
    if((long)rows_return == false || (long)cols_return == false
        || (long)sg1_return == false || (long)sg2_return == false
        || (long)sg3_return == false || (long)sg4_return == false
        || (long)sg5_return == false || (long)sg6_return == false
        || (long)sg7_return == false || (long)sg8_return == false 
        || (long)sg9_return == false ) {
        puts("invalid");
    }
    else {
        puts("valid");
    }

    
    return 0;
}