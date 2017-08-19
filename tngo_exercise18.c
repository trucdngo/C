/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 18
 Topic: Long Integer
 FileName: tngo_exercise18.c
 Date: Jun 1, 2017
 Objective:
 Comments:
 
 **********************************************/
/*
 Read the input from an input file. 
 The output should show how the links in the list structure are constructed for list 1 and list 2. 
 Where result list is constructed, show how the links in the result list are constructed. 
 Finally show the result output with leading zeros taken care.
 
 Read the following two long integer inputs from an input file in the same order. (Note: Do not assign an array
 with input values.)
 
 List 1:
 954680325257568512973371196238845129776544789456
 
 List 2:
 64324564257936835497210698463523456234
 
 Print the long integer sum of the two list structures from the result list
 Print the two lists in linked list formation with space between the numbers from each link
 Print the result list with numbers from each link with spaces in between.
 
 http://www.javascripter.net/math/calculators/100digitbigintcalculator.htm
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
FILE *fp1;
FILE *fp2;
FILE *fp3;


typedef struct listnode {
    int data;
    struct listnode * nextptr;
} LISTNODE;

typedef LISTNODE *listNodePtr1, *listNodePtr2, *listNodePtr3;

void insert(listNodePtr1 *, int);
void printList(listNodePtr3);
void printResultStringAsLinkedList(listNodePtr3);

int main() {
    const char inputFileName1[] = "trngo_LongInt_18_input1.txt";
    const char inputFileName2[] = "trngo_LongInt_18_input2.txt";
    const char outputFileName[] = "trngo_LongInt_18_output.txt";
    
    fp1 = fopen(inputFileName1, "r");
    fp2 = fopen(inputFileName2, "r");
    fp3 = fopen(outputFileName, "w");
    
    listNodePtr1 startPtr1 = NULL;
    listNodePtr2 startPtr2 = NULL;
    listNodePtr3 startPtr3 = NULL;
    int idigit;
    char cdigit;
    char intArray[5];
    memset(intArray, '\0', 5);
    if (fp1 != NULL && fp3 != NULL) {
        int dCounter = 0;
        
        //count how many zero-digit for file #1
        while ((idigit = fgetc(fp1)) != EOF) {
            dCounter++;
        }
        int numbersOfZero = (dCounter % 4 != 0) ? (4 - (dCounter % 4)) : 0;
        printf("Number of zeros for first Node of Linked-list for integer 1 = %d\n", numbersOfZero);
        fprintf(fp3, "Number of zeros for first Node of Linked-list for integer 1 = %d\n", numbersOfZero);
        rewind(fp1);
        dCounter = -1;
        int innerCounter = -1;
        int intValue = 0;
        //update linked-list for data file #1
        while ((cdigit = fgetc(fp1)) != EOF) {
            if (numbersOfZero > 0 && (innerCounter != (3-numbersOfZero))) {
                intArray[++innerCounter] = cdigit;
                if (innerCounter == (3-numbersOfZero)) {
                  int intValue = atoi(intArray);
                  insert(&startPtr1, intValue);
                  memset(intArray, '\0', 5);
                  numbersOfZero = 0;
                }
            } else {
                intArray[++dCounter] = cdigit;
                if (dCounter == 3) {
                    intValue = atoi(intArray);
                    insert(&startPtr1, intValue);
                    dCounter = -1;
                    memset(intArray, '\0', 5);
                }
            }
        } //end while loop
    } //end if
    fclose(fp1);
    
    memset(intArray, '\0', 5);
    if (fp2 != NULL && fp3 != NULL) {
        int dCounter = 0;
        
        //count how many zero-digit for file #2
        while ((idigit = fgetc(fp2)) != EOF) {
            dCounter++;
        }
        int numbersOfZero = (dCounter % 4 != 0) ? (4 - (dCounter % 4)) : 0;
        printf("Number of zeros for first Node of Linked-list for integer 2 = %d\n", numbersOfZero);
        fprintf(fp3, "Number of zeros for first Node of Linked-list for integer 2 = %d\n", numbersOfZero);
        rewind(fp2);
        dCounter = -1;
        int innerCounter = -1;
        int intValue = 0;
        //update linked-list for data file #2
        while ((cdigit = fgetc(fp2)) != EOF) {
            if (numbersOfZero > 0 && (innerCounter != (3-numbersOfZero))) {
                intArray[++innerCounter] = cdigit;
                if (innerCounter == (3-numbersOfZero)) {
                    int intValue = atoi(intArray);
                    insert(&startPtr2, intValue);
                    memset(intArray, '\0', 5);
                    numbersOfZero = 0;
                }
            } else {
                intArray[++dCounter] = cdigit;
                if (dCounter == 3) {
                    intValue = atoi(intArray);
                    insert(&startPtr2, intValue);
                    dCounter = -1;
                    memset(intArray, '\0', 5);
                }
            }
        } //end while loop
    } //end if
    fclose(fp2);
    
    printf("\nInteger 1 as linked-list (in reversed order)\n");
    fprintf(fp3, "\nInteger 1 as linked-list (in reversed order)\n");
    printList(startPtr1);
    printf("Integer 2 as linked-list (in reversed order)\n");
    fprintf(fp3, "Integer 2 as linked-list (in reversed order)\n");
    printList(startPtr2);
    
    //adding two linked list
    int carriedOver = 0;
    int number = 0;
    int total = 0;
    while (startPtr1 != NULL && startPtr2 != NULL) {
        int value1 = startPtr1->data;
        int value2 = startPtr2->data;
        total = value1 + value2 + carriedOver;
        carriedOver = total / 10000;
        number = total % 10000;
        insert(&startPtr3, number);
        printf("\nAdding nodes %d and %d and insert this < SUM > to the new linked-list\n", value1, value2);
        fprintf(fp3, "\nAdding nodes %d and %d and insert this < SUM > to the new linked-list\n", value1, value2);
        printList(startPtr3);
        startPtr1 = startPtr1->nextptr;
        startPtr2 = startPtr2->nextptr;
    }
    //while list 1 is longer than list2
    while (startPtr1 != NULL && startPtr2 == NULL) {
        total = startPtr1->data + carriedOver;
        carriedOver = total / 10000;
        number = total % 10000;
        insert(&startPtr3, number);
        printList(startPtr3);
        startPtr1 = startPtr1->nextptr;
    }
    //while list 2 is longer than list1
    while (startPtr1 == NULL && startPtr2 != NULL) {
        total = startPtr2->data + carriedOver;
        carriedOver = total / 10000;
        number = total % 10000;
        insert(&startPtr3, number);
        printList(startPtr3);
        startPtr2 = startPtr2->nextptr;
    }
    //print linked-list as string
    printList(startPtr3);
    printf("Sum of two integers:\n");
    fprintf(fp3, "Sum of two integers:\n");
    printResultStringAsLinkedList(startPtr3);
    fclose(fp3);
}


void insert(listNodePtr1 *sptr, int value) {
    listNodePtr1 newPtr = (listNodePtr1) malloc (sizeof(LISTNODE));
    // form the new Node
    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextptr = NULL;
        newPtr->nextptr = *sptr;
        *sptr = newPtr;
    } else {
        printf("\n%c not inserted.  No memory is available\n", value);
        fprintf(fp3, "\n%c not inserted.  No memory is available\n", value);
    }
}

void printList(listNodePtr3 startPtr) {
    if (startPtr == NULL) {
        printf("\nList is Empty.\n\n");
        fprintf(fp3, "\nList is Empty.\n\n");
    } else {
        while (startPtr != NULL) {
            printf("%d --> ", startPtr->data);
            fprintf(fp3, "%d --> ", startPtr->data);
            startPtr = startPtr->nextptr;
        }
        printf("NULL\n\n");
        fprintf(fp3, "NULL\n\n");
    }
}

void printResultStringAsLinkedList(listNodePtr3 startPtr) {
    int count = 0;
    int data = 0;;
    if (startPtr == NULL) {
        printf("\nList is Empty.\n");
        fprintf(fp3, "\nList is Empty.\n\n");
    } else {
        while (startPtr != NULL) {
            data = startPtr->data;
            int data2 = data;
            while(data != 0)
            {
                data = data / 10;
                ++count;
            }
            //if data for linked-list node is just 0
            if (data2 == 0) {
                printf("%s", "0000");
                fprintf(fp3, "%s", "0000");
            //if data for linked-list node is {1, 2, 3} digits, then fill the rest with zeros
            } else if (count < 4) {
                int lessThan4 = 4 - count;
                for (int i = 1; i <= lessThan4; i++) {
                    printf("%d", 0);
                    fprintf(fp3, "%d", 0);
                }
                printf("%d", startPtr->data);
                fprintf(fp3, "%d", startPtr->data);
                
            } else {
                printf("%d", startPtr->data);
                fprintf(fp3, "%d", startPtr->data);
            }
            count = 0;
            startPtr = startPtr->nextptr;
        }
    }
    printf("\n");
    fprintf(fp3, "\n");
}

