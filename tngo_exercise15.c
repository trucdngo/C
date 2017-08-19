/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 15
 Topic: Hashing
 FileName: tngo_exercise15.c
 Date: Jun 14, 2017
 Objective:
 Comments:
 
 **********************************************/
/*
 This assignment involves in implementing hashing and hash table and gives you average full credit.
 Create and add a link node to the hash table as you read the input from file.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ASIZE 40
#define FALSE 0
#define TRUE 1
typedef enum {false, true} bool;
FILE *fp1;
FILE *fp2;
int* importData();
void print_data(int* arrayPtr);



int main() {
    const char outputFileName[] = "trngo_sorting_12_output.txt";
    fp2 = fopen(outputFileName, "w");
    int* data = malloc(sizeof(int) * ASIZE);
    data = importData();
    printf("\nDisplaying original data:\n");
    fprintf(fp2, "\nDisplaying original data:\n");
    
    fclose(fp2);
    return 0;
    
}

//print data
void print_data(int* arrayPtr) {
    for (int i = 0; i < ASIZE; i++) {
        printf("%d ", arrayPtr[i]);
        fprintf(fp2, "%d ", arrayPtr[i]);
    }
    printf("\n");
    fprintf(fp2, "\n");
}

int* importData() {
    const char inputFileName[] = "trngo_sorting_12_input.txt";
    fp1 = fopen(inputFileName, "r");
    char cdigit;
    char digits[4];
    int digitCounter = -1;
    int readNumberCounter = -1;
    static int intArray[ASIZE];
    printf("\nimporting data from file to array...");
    fprintf(fp2, "\nimporting data from file to array...");
    if (fp1 != NULL) {
        while ((cdigit = fgetc(fp1)) != EOF) {
            if (cdigit != 44) {
                digits[++digitCounter] = cdigit;
            } else {
                ++readNumberCounter;
                digitCounter = -1;
                int intValue = atoi(digits);
                intArray[readNumberCounter] = intValue;
                memset(digits, '\0', 4);
            }
        }
    }
    fclose(fp1);
    return intArray;
}