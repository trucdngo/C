/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 11
 Topic: Linked List
 FileName: tngo_exercise11.c
 Date: June 4, 2017
 Objective:
 Comments:
 
 **********************************************/
/*
 Follow the instructions in the assignment. Create an input file with the input given in the assignment. 
 Do not read the input to a buffer in the program, read one input at a time from the file. Write output to an output file.
 
 This assignment deals with linear linked list. 
 Read the input from the input file, do not initialize an array with input numbers.
 Create and add the link to the list as you read the input. 
 Give the output after each task with a header explaining the task.
 Prompt the user for deleting the entries from the list and output after each deletion. 
 Follow the order in which the deletion to be processed as given in the assignment.
 Please do not intialize an array for deleting the entries.
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fp1;
FILE *fp2;

typedef struct listnode {
    int data;
    struct listnode * nextptr;
} LISTNODE;

typedef LISTNODE *listNodePtr;

void insert(listNodePtr *, int);
char delete(listNodePtr *, char);
int isEmpty(listNodePtr);
void printList(listNodePtr);
void instructions(void);
void  reverseLinkedList(listNodePtr *);

int main() {
    const char inputFileName[] = "trngo_LikedList_11_input.txt";
    const char outputFileName[] = "trngo_LikedList_11_output.txt";
    listNodePtr startPtr = NULL;
    int choice;
    int item;
    char cdigit;
    char keystroke;
    char digits[5];
    int digitCounter = -1;
    fp1 = fopen(inputFileName, "r");
    fp2 = fopen(outputFileName, "w");
    if (fp1 != NULL && fp2 != NULL) {
        printf("\nPopulating Linked-list...\n");
        fprintf(fp2, "\nPopulating Linked-list...\n");
        while ((cdigit = fgetc(fp1)) != EOF) {
            if (cdigit != 32) {
                digits[++digitCounter] = cdigit;
            } else {
                digitCounter = -1;
                int intValue = atoi(digits);
                insert(&startPtr, intValue);
                memset(digits, '\0', 5);
            }
        }
        printList(startPtr);
        instructions();
        scanf("%d%c", &choice, &keystroke);
        fprintf(fp2, "%d\n", choice);
        while (choice != 3) {
            switch(choice)
            {
                case 1:
                    reverseLinkedList(&startPtr);
                    printList(startPtr);
                    break;
                case 2:
                    if (!isEmpty(startPtr)) {
                        printf("Enter number to be deleted: ");
                        fprintf(fp2, "Enter number to be deleted: ");
                        scanf("\n%d", &item);
                        fprintf(fp2, "%d", item);
                        if (delete(&startPtr, item)) {
                            printf("\n%d is deleted\n", item);
                            fprintf(fp2, "\n%d is deleted\n", item);
                            printList(startPtr);
                            break;
                        } else {
                            printf("\n%d not found.\n", item);
                            fprintf(fp2, "\n%d not found.\n", item);
                            break;
                        }
                            
                    } else {
                        printf("List is empty.\n\n");
                        fprintf(fp2, "List is empty.\n\n");
                        break;
                                
                    }
                case 3:
                    fclose(fp1);
                    fclose(fp2);
                    exit (1);
                default:
                    fclose(fp1);
                    fclose(fp2);
                    printf("\nInvalid Choice.\n");
                    fprintf(fp2, "\nInvalid Choice.\n");
                    exit (1);
            }
            instructions();
            scanf("%d%c", &choice, &keystroke);
            fprintf(fp2, "%d\n", choice);
        } // end While
    }// end If
    fclose(fp1);
    fclose(fp2);
}

void reverseLinkedList(listNodePtr *sptr) {
    listNodePtr currNode, nextNode, loopNode;
    currNode = *sptr;
    nextNode = (*sptr)->nextptr;
    (*sptr)->nextptr = NULL;
    while (nextNode != NULL) {
        loopNode = nextNode->nextptr;
        nextNode->nextptr = currNode;
        currNode = nextNode;
        nextNode = loopNode;
    }
    *sptr = currNode;
}

void instructions(void) {
    printf("1> to reverse the Linked-list.\n");
    printf("2> to delete an element from the list.\n");
    printf("3> to end.\n");
    printf("\nEnter your choice: ");
    
    fprintf(fp2, "1> to reverse the Linked-list.\n");
    fprintf(fp2, "2> to delete an element from the list.\n");
    fprintf(fp2, "3> to end.\n");
    fprintf(fp2, "\nEnter your choice: ");
}

int isEmpty(listNodePtr sptr) {
    return (sptr == NULL);
}
                        

void insert(listNodePtr *sptr, int value) {
    listNodePtr newPtr = (listNodePtr) malloc (sizeof(LISTNODE));
    // form the new Node
    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextptr = NULL;
        newPtr->nextptr = *sptr;
        *sptr = newPtr;
    } else {
        printf("\n%c not inserted.  No memory is available\n", value);
        fprintf(fp2, "\n%c not inserted.  No memory is available\n", value);
    }
}

char delete(listNodePtr *sptr, char value) {
    listNodePtr prevPtr, currPtr, tempPtr;
    // if the first node is the one that will be deleted
    if (value == (*sptr)->data) {
        tempPtr = *sptr;
        *sptr = (*sptr)->nextptr;
        free(tempPtr);
        return (value);
    // if the first node is not the node to be deleted, then traverse the link-list
    } else {
        prevPtr = *sptr;
        currPtr = (*sptr)->nextptr;
    }
    // traverse the list until the match is found
    while ((currPtr != NULL) && (currPtr->data != value)) {
        prevPtr = currPtr;
        currPtr = currPtr->nextptr;
    }
    if (currPtr != NULL) {
        tempPtr = currPtr;
        prevPtr->nextptr = currPtr->nextptr;
        currPtr = currPtr->nextptr;
        free(tempPtr);
        return(value);
    }
    return ('\0');
}

void printList(listNodePtr startPtr) {
    if (startPtr == NULL) {
        printf("\nList is Empty.\n\n");
        fprintf(fp2, "\nList is Empty.\n\n");
    } else {
        while (startPtr != NULL) {
            printf("%d --> ", startPtr->data);
            fprintf(fp2, "%d --> ", startPtr->data);
            startPtr = startPtr->nextptr;
        }
        printf("NULL\n\n");
        fprintf(fp2, "NULL\n\n");
    }
}



