/********Prologue**********
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 7
 Topic: Playing Chess (N Queens)
 FileName: tngo_exercise07.c
 Date: May 9, 2017
 Objective: Learning Recursive
 Comments:
 
 **************************
The solution requires to prompt the user to place the queen in any column of the first row. 
The program is required to place queen in remaining rows unattacked by other queens successively.
It is incorrect solution to place queens in the first row in a loop. 
Output will be written by your program directly to an output file. 
Input will be read by prompting the user to enter the first queen column. 
User's input is given in the assignment pdf file, there will be some unacceptable input to be taken care.

You need to submit eight solutions of queen placement in the first row as given in the input of the assignment problem. 
Prompt the user for placing the first queen (row 1) in any column and your program should be able to place the remaining 7 queens
without attacking each other.
Please do not place the queen column numbers in an array and run the program.
There will be one solution of the chess board per one user input.

Hint: The best way to solve this problem is to run the code as given in chapter 23 with break points to understand how the logic. 
Next step is to modify the code to make it work as desired. The user is prompted to place a queen in the first row any column. 
Your  The user may place the queen or quit as the choice is given. 
The order in which the user will place the code from standard input is given in the problem.

*/


#include <stdio.h>
#define BOARDSIZE 8
#define DIAGONAL (2 * BOARDSIZE - 1)
#define DOWNOFFSET 7
#define FALSE 0
#define TRUE 1
typedef enum {false, true} bool;
void writeBoard(void);
void clearBoard(void);
void addQueen(void);
int queencol[BOARDSIZE];   // queen column
bool colfree[BOARDSIZE];   // is column free
bool upfree[DIAGONAL ];    // up diagonal free
bool downfree[DIAGONAL ];  // down diagonal free
int queencount = -1;       // row queen is placed
int numsol = 0;            // number of solutions found
FILE *pFile1;

int main (void) {
    
    pFile1 = fopen("trngo_NQueens_07_output.txt", "w");
    printf("\nStarting N-Queens Program:\n");
    fprintf(pFile1, "\nStarting N-Queens Program:\n");
    if (pFile1 != NULL) {
        int QueenPosition;
        printf("\nEnter -1 to exit\n");
        printf("Place the first Queen row in any column[0 to 7]: ");
        fprintf(pFile1, "\nEnter -1 to exit\n");
        fprintf(pFile1, "Place the first Queen row in any column[0 to 7]: ");
        scanf("%d", &QueenPosition);
        fprintf(pFile1, "%d", QueenPosition);
        if (QueenPosition == -1) {
            return 0;
        } else {
            while ((QueenPosition != -1) && (QueenPosition >= 0)) {
               if (QueenPosition > 7) {
                    printf("\n%d is invalid Queen position.", QueenPosition);
                    printf("\nEnter -1 to exit\n");
                    printf("Place the first Queen row in any column[0 to 7]: ");
                    fprintf(pFile1, "\n%d is invalid Queen position.", QueenPosition);
                    fprintf(pFile1, "\nEnter -1 to exit\n");
                    fprintf(pFile1, "Place the first Queen row in any column[0 to 7]: ");
                    scanf("%d", &QueenPosition);
                    fprintf(pFile1, "%d", QueenPosition);
                }
                clearBoard();
                queencol[++queencount] = QueenPosition;
                colfree[QueenPosition] = FALSE;
                upfree[queencount + QueenPosition] = FALSE;
                downfree[queencount - QueenPosition + DOWNOFFSET] = FALSE;
                addQueen();
                printf("\nEnter -1 to exit\n");
                printf("Place the first Queen row in any column[0 to 7]: ");
                fprintf(pFile1, "\nEnter -1 to exit\n");
                fprintf(pFile1, "Place the first Queen row in any column[0 to 7]: ");
                scanf("%d", &QueenPosition);
                fprintf(pFile1, "%d", QueenPosition);
            } // end while
        } //end else
    } //end if
    fclose(pFile1);
    return 0;
}

void addQueen (void) {
    int col; // column being tried for the queen
    queencount++;
    for (col = 0; col < BOARDSIZE; col++) {
        if (colfree[col] && upfree[queencount + col] && downfree[queencount - col + DOWNOFFSET]) {
            // put the queen in position (queencount, col)
            queencol[queencount] = col;
            colfree[col] = FALSE;
            upfree[queencount + col] = FALSE;
            downfree[queencount - col + DOWNOFFSET] = FALSE;
            if (queencount == BOARDSIZE - 1) { // terminal condition
                printf("\n%d Queen Solution: %d \n\n", 8, ++numsol);
                fprintf(pFile1, "\n%d Queen Solution: %d \n\n", 8, numsol);
                writeBoard();
            } else
                addQueen(); // recursive call
            if (queencount - 1 < 0)
                continue;
            colfree[col] = TRUE; // backtrack queen
            upfree[queencount - 1 + col] = TRUE;
            downfree[queencount - 1 - col + DOWNOFFSET] = TRUE;
            queencount--;
        }
    }
}

//prints the output of N queens placement
void writeBoard(void)
{
    int col;
    static int qcount = 0;
    for (col = 0; col < BOARDSIZE; col++) {
        if(queencol[qcount] == col) {
            printf("Q ");
            fprintf(pFile1,"Q ");
        } else {
            printf("* ");
            fprintf(pFile1,"* ");
        }
    }
    printf("\n\n");
    fprintf(pFile1,"\n\n");
    if (qcount++ < BOARDSIZE - 1)
        writeBoard();
    qcount = 0;
}

void clearBoard(void) {
    for (int i = 0; i < BOARDSIZE; i++) {
        colfree[i] = TRUE;
        queencol[i] = -1;
    }
    for (int j = 0; j < DIAGONAL; j++) {
        upfree[j] = TRUE;
        downfree[j] = TRUE;
    }
    queencount = -1;
}
