/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 9
 Topic: Queue
 FileName: tngo_exercise09.c
 Date: May 9, 2017
 Objective: using Array of Structure and Queue
 Comments:
 
 **********************************************/
/*
 This assignment deals with queues implementation with Enque and Deque operations. 
 The input is given in the assignment, create an input file to read the input by the program. 
 Your program will write the output to an output file. Follow the instructions carefully.
 
 In the output, you need to specify as what action you are taking with each of the input read or 
 what is the value of the item that is taken out of the queue. 
 At each step you should show what is left in the queue. 
 Finally, what is left in the queue after reading all the input?
 
 */


#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUE 10
#define EMPTYQUEUE -1
#define TRUE 1
#define FALSE 0

//struture to hold data read-out from input file
typedef struct {
    char inputDataStructChar;
    int inputDataStructValue;
} inputData;

typedef struct queue {
    int front, rear;
    int queueElement[MAXQUEUE];
} CHQUEUE;

int isEmpty(struct queue *);
int dequeue(struct queue *);
int enqueue(struct queue *, int c);
void printQueue(struct queue *);
FILE *fp1;
FILE *fp2;


int main(int argc, const char *argv[]) {
    const char outputFileName[] = "trngo_Queue_09_output.txt";
    inputData inputDataStructure[MAXQUEUE];
    int counter = 0;
    char c;
    if (argc > 2) {
        printf("\nToo many arguments supplied!\n");
        fprintf(fp2, "\nToo many arguments supplied!\n");
    } else if (argc == 2) {
        fp1 = fopen(argv[1], "r");
        fp2 = fopen(outputFileName, "w");
        if (fp1 != NULL && fp2 != NULL) {
            int charCounter = 0;
            while ((c = fgetc(fp1)) != EOF) {
                //for enqueue
                if (c == 'E') {
                    counter = charCounter;
                    inputDataStructure[counter].inputDataStructChar = c;
                    inputDataStructure[counter].inputDataStructValue = 0;
                    ++charCounter;
                    //for dequeue
                } else if (c == 'D') {
                    counter = charCounter;
                    inputDataStructure[counter].inputDataStructChar = c;
                    inputDataStructure[counter].inputDataStructValue = -1;
                    ++counter;
                    ++charCounter;
                } else {
                    int temp = inputDataStructure[counter].inputDataStructValue * 10;
                    int temp2 = c - '0';
                    inputDataStructure[counter].inputDataStructValue = temp + temp2;
                }
            }
        } else {
            printf("File %s could not be opened", argv[1]);
            fprintf(fp2, "File %s could not be opened", argv[1]);
        }
        fclose(fp1);
    } else {
        printf("\nOne argument is expected!\n");
        fprintf(fp2, "\nOne argument is expected!\n");
    }
    
    
    printf("Reading Input File: %s\n", argv[1]);
    printf("Choice: ");
    fprintf(fp2, "Reading Input File: %s\n", argv[1]);
    fprintf(fp2, "Choice: ");
    for (int i = 0; i <= counter; i++) {
        printf("%3c ", inputDataStructure[i].inputDataStructChar);
        fprintf(fp2, "%3c ", inputDataStructure[i].inputDataStructChar);
    }
    printf("\n");
    printf("Data:   ");
    fprintf(fp2, "\n");
    fprintf(fp2, "Data:   ");
    for (int i = 0; i <= counter; i++) {
        char tempValue = ' ';
        int temp = inputDataStructure[i].inputDataStructValue;
        if (temp != -1) {
            printf("%3d ", inputDataStructure[i].inputDataStructValue);
            fprintf(fp2, "%3d ", inputDataStructure[i].inputDataStructValue);
        } else {
            printf("%3c ", tempValue);
            fprintf(fp2, "%3c ", tempValue);
        }
    }
    printf("\n");
    fprintf(fp2, "\n");
    
    CHQUEUE alphaqueue;
    CHQUEUE *asp = &alphaqueue;
    alphaqueue.front = alphaqueue.rear = -1;
    //send data to queue for simulation
    for (int i = 0; i <= counter; i++) {
        if (inputDataStructure[i].inputDataStructChar == 'E') {
            enqueue(asp, inputDataStructure[i].inputDataStructValue);
            printf("\nAfter Enqueue: %d\n", inputDataStructure[i].inputDataStructValue);
            fprintf(fp2, "\nAfter Enqueue: %d\n", inputDataStructure[i].inputDataStructValue);
            printQueue(asp);
        } else if (inputDataStructure[i].inputDataStructChar == 'D') {
            int dequeueValue = dequeue(asp);
            printf("\nAfter Dequeue: %d\n", dequeueValue);
            fprintf(fp2, "\nAfter Dequeue: %d\n", dequeueValue);
            printQueue(asp);
        }
    }
    printf("\nEnd of Simulation for queue.\n");
    fprintf(fp2, "\nEnd of Simulation for queue.\n");
    fclose(fp2);
    return 0;
}


//check if the queue is empty
int isEmpty(CHQUEUE *ps) {
    if ((ps->front == EMPTYQUEUE) && (ps->rear == EMPTYQUEUE)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//enqueue: insert item to the rear-ending side of the queue
//front of queue ---> [0,1,2,3,4,5,6,7,8,9] <--- rear of queue
int enqueue(CHQUEUE *ps, int c) {
    //check for overflow condition
    if (ps->rear == MAXQUEUE-1) {
        printf("%s", "Queue overflow!");
        fprintf(fp2, "%s", "Queue overflow!");
        exit(1);
    } else {
        (ps->rear)++;
    }
    //check if front pointer catches up with rear pointer
    //note that (ps->rear) is now increased by one after post increasement
    if (ps->front == ps->rear) {
        printf("%s", "Queue overflow!");
        fprintf(fp2, "%s", "Queue overflow!");
        //insert codes to reset queue here
        exit(1);
    } else {
        if (ps->front == EMPTYQUEUE) {
            ps->front = EMPTYQUEUE + 1;
        }
        ps->queueElement[(ps->rear)] = c;
    }
    return 0;
}

//remove item from front of the queue
//front of queue ---> [0,1,2,3,4,5,6,7,8,9] <--- rear of queue
int dequeue(CHQUEUE *ps) {
    int indexOfnumberToBeRemovedFromQueue, valueOfNumberToBeRemoved = -1;
    if (isEmpty(ps)) {
        printf("%s", "\nQueue underflow\n");
        fprintf(fp2, "%s", "\nQueue underflow\n");
        exit(1);
    }
    if ((ps->front == MAXQUEUE) || (ps->front > ps->rear)) {
        ps->front = -1;
        ps->rear = -1;
        valueOfNumberToBeRemoved = -9999;
    } else {
        indexOfnumberToBeRemovedFromQueue = ps->front;
        valueOfNumberToBeRemoved = ps->queueElement[indexOfnumberToBeRemovedFromQueue];
        ps->queueElement[indexOfnumberToBeRemovedFromQueue] = -1;
        (ps->front)++;
    }
    return valueOfNumberToBeRemoved;
}

void printQueue(CHQUEUE *ps) {
    if (isEmpty(ps)) {
        fprintf(fp2, "%s", "\nQueue is Empty\n");
        printf("%s", "\nQueue is Empty\n");
    } else {
        for (int i = ps->front; i <= ps->rear; i++) {
            // if it is rear element, do not print arrow
            if (i == ps->rear) {
                fprintf(fp2, "%4d ", i);
                printf("%4d ", i);
            } else {
                fprintf(fp2, "%4d <-", i);
                printf("%4d <-", i);
            }
        }
        fprintf(fp2, "\n");
        printf("\n");
        for (int i = ps->front; i <= ps->rear; i++) {
            // if it is rear element, do not print arrow
            if (i == ps->rear) {
                fprintf(fp2, "%4d ", ps->queueElement[i]);
                printf("%4d ", ps->queueElement[i]);
            } else {
                fprintf(fp2, "%4d <-", ps->queueElement[i]);
                printf("%4d <-", ps->queueElement[i]);
            }
        }
    }
    fprintf(fp2, "\n");
    printf("\n");
}

