/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 10
 Topic: Tower Of Hanoi
 FileName: tngo_exercise10.c
 Date: May 9, 2017
 Objective: Learning Recursive
 Comments:
 
 **********************************************/
/*
 This assignment deals with Recursion implementation.
 You are required to prompt the user to give the number of disks to be placed on the target post from the initial post using the auxilary post. 
 Three outputs are expected for this assignment, with 4, 5 and 6 disks by prompting the user to specify the number disks within the range.
 Your program will use files and write output to an output file. 
 The input will be read from user prompt. 
 Write some nice prompt to the user to enter an appropriate input.
 All three outputs have to be in one file. 
 The assignment requires each disk placement to any post and also the final move of every disk to the target disk.
 
 Identfy each final move of any disc to Peg C
*/

// Output is sent to File instead of stdio Screen
#include <stdio.h>

FILE *pFile;
int base_to_the_n(int base, int n);
void moveDisc(int nDiscs, char sourceA, char destinationC, char tempB, int totalNumberOfDiscs, int halfStackMarker, int nextFinalDisc);
void moveDiscA_B(int nDiscs, char sourceA, char destinationC, char tempB, int totalNumberOfDiscs, int halfStackMarker, int nextFinalDisc);


 For column A with 4 discs
 Peg A  =>   Peg C
 1               1
 2               2
 3               3
 4               4
 

int main(int argc, const char * argv[]) {
    
    int numberOfDiscs = -1;
    pFile = fopen("trngo_TowerOfHanoi_output.txt", "w");
    do {
        if (pFile == NULL) {
            printf("error opening file");
        } else {
            fprintf(pFile, "\n\n%s\n", "Simulation of Tower Of Hanoi");
            fprintf(pFile, "%s\n", "Smallest disc stays on top");
            printf("Enter number if discs (-1 to quit): ");
            fprintf(pFile, "%s", "Enter number of discs (-1 to quit):");
            scanf("%d", &numberOfDiscs);
            fprintf(pFile, "%d", numberOfDiscs);
            fprintf(pFile, "\n\n");
            
            if (numberOfDiscs == -1) {
                break;
            }
            int totalNumberOfDiscs = numberOfDiscs;
            moveDisc(numberOfDiscs, 'A', 'C', 'B', totalNumberOfDiscs, 0, numberOfDiscs);
            //fprintf(pFile, "%c\n", ' ');
            //fprintf(pFile, "Numbers of disc movement = %d\n", base_to_the_n(2, numberOfDiscs) - 1);
            //fprintf(pFile, "%c\n", ' ');
        }
    } while(numberOfDiscs != -1);
    fclose(pFile);
}


//move disc from Column A to Column C
void moveDisc(int nDiscs, char sourceA, char destinationC, char tempB, int totalNumberOfDiscs, int halfStackMarker, int nextFinalDisc) {
    if ((nDiscs == 1) && (nextFinalDisc == 1) && (halfStackMarker == 1)) {
        fprintf(pFile, "Move disc %d from Column %c to %c <Final Move> \n", nDiscs, sourceA, destinationC);
        return;
    } else if (nDiscs == 1) {
        fprintf(pFile, "Move disc %d from Column %c to %c\n", nDiscs, sourceA, destinationC);
        return;
    } else {
        //move n-1 discs from Column-A to auxilary Column-B
        int t = nDiscs-1;
        moveDiscA_B(t, sourceA, tempB, destinationC, totalNumberOfDiscs, halfStackMarker, nextFinalDisc);
        if (t == (totalNumberOfDiscs - 1)) {
            halfStackMarker = 1;
        }
        if ((destinationC == 'C') && (halfStackMarker == 1) && (nextFinalDisc == nDiscs)) {
            fprintf(pFile, "Move disc %d from Column %c to %c <Final Move> \n", nDiscs, sourceA, destinationC);
            nextFinalDisc = nDiscs - 1;
        } else {
            fprintf(pFile, "Move disc %d from Column %c to %c\n", nDiscs, sourceA, destinationC);
        }
        //move n-1 discs from auxilary Column-B back to Column-C with Column-A as auxiliary
        moveDisc(t, tempB, destinationC, sourceA, totalNumberOfDiscs, halfStackMarker, nextFinalDisc);
    }
}

//move disc from Column A to Column B
void moveDiscA_B(int nDiscs, char sourceA, char destinationC, char tempB, int totalNumberOfDiscs, int halfStackMarker, int nextFinalDisc) {
    if (nDiscs == 1) {
        fprintf(pFile, "Move disc %d from Column %c to %c\n", nDiscs, sourceA, destinationC);
        return;
    } else {
        //move n-1 discs from Column-A to auxilary Column-B
        moveDiscA_B(nDiscs-1, sourceA, tempB, destinationC, totalNumberOfDiscs, halfStackMarker, nextFinalDisc);
        fprintf(pFile, "Move disc %d from Column %c to %c\n", nDiscs, sourceA, destinationC);
        //move n-1 discs from auxilary Column-B back to Column-C with Column-A as auxiliary
        moveDisc(nDiscs-1, tempB, destinationC, sourceA, totalNumberOfDiscs, halfStackMarker, nextFinalDisc);
    }
}


//2^3 = 8
//base_to_the_n(2, 3) = 8
int base_to_the_n(int base, int n) {
    int number = 1;
    for (int i = 0; i < n; i++) {
        number *= base;
    }
    return number;
}


