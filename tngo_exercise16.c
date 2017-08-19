/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 16
 Topic: Sequencing Cards
 FileName: tngo_exercise16.c
 Date: June 10, 2017
 Objective: using of Queue and struct
 Comments:
 
**********************************************/
/*

 This assignment involves in implementing queues and gives you more than average full credit. 
 It deals with sequencing the playing cards after shuffling and distributing the cards. 
 One suit (one color) of cards is dealt to shuffle in any way you like and districute the cards as specified in the instructions. 
 You are expected to write the code for reading the cards from input file in to an array, 
 shuffle the cards in a specific way and display the cards in the desired sequence. 
 You may use the concepts from the Reading section about sequencing the playing cards. 
 Display the shuffled queue. After solving the problem for simpler (normal card sequence) queue, 
 the same concepts can be applied for a different sequence of cards as given in the problem.
 
 Provide the output after the cards from the input file, 
 the sequence of cards after shuffling (or placing) the cards and how you distribute (open) the cards from the shuffled queue
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SUITSIZE 13
#define DECKSIZE 52
#define NUMSUITS 4 
#define MAXQUEUE 50
#define MAXSTACK 50
#define EMPTYQUEUE -1
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0

typedef struct {
    char value[3];
} INPUTDATA;

typedef struct {
    char *face;
    char *suit;
} CARD;

typedef struct stack {
    int top;
    int stackelements[MAXSTACK];
} STACK;

int pop(struct stack *);
void push(struct stack *, int);
int peek(struct stack *);
int isStackEmpty(struct stack *);
void resetStack(struct stack *);

typedef struct queue {
    int front;
    int rear;
    int queueElement[MAXQUEUE];
} QUEUE;

int isEmpty(struct queue *);
int dequeue(struct queue *);
int enqueue(struct queue *, int c);

void fillDeck(CARD *, char *[], char *[]);
void shuffle(CARD *);
void deal(CARD *);
int substitute10byX(int n);


QUEUE* get_cards_in_original_order(INPUTDATA[]);
QUEUE* shuffle_cards_stage1(INPUTDATA[]);
STACK* shuffle_cards_stage2(QUEUE*);
void printQueue(struct queue *);
void printStack(STACK *ps);
void shuffle_cards_stage3(STACK *pq1);


FILE *fp1;  //input file1,2
FILE *fp3;  //output file

int main(int argc, const char *argv[]) {
    const char inputFileName1[] = "trngo_Cards_16_input1.txt";
    const char inputFileName2[] = "trngo_Cards_16_input2.txt";
    const char outputFileName[] = "trngo_Cards_16_output.txt";
    fp3 = fopen(outputFileName, "w");
    
    if (fp3 != NULL) {
        printf("\nSequencing cards simulation program\n");
        fprintf(fp3, "\nSequencing cards simulation program\n");
        INPUTDATA input_data1[SUITSIZE];
        
        int pickDataFile = 0;
        do {
            
            printf("\nChoose data file to simulate sequencing card {1, 2} <<< -1 to quit>>>: ");
            scanf("%d", &pickDataFile);
            printf("\n************************************************************************\n");
            fprintf(fp3, "\nChoose data file to simulate sequencing card {1, 2} <<< -1 to quit>>>: ");
            fprintf(fp3, "%d", pickDataFile);
            fprintf(fp3, "\n************************************************************************\n");
        
            if (pickDataFile == -1) {
                return 0;
            } else if (pickDataFile == 1) {
                fp1 = fopen(inputFileName1, "r");
            } else if (pickDataFile == 2) {
                fp1 = fopen(inputFileName2, "r");
            } else {
                return 0;
            }
            
            for (int i = 0; i < SUITSIZE; i++) {
                memset(input_data1[i].value, 0, sizeof(input_data1[i].value));
            }
        
            if (fp1 != NULL) {
                int i = 0;
                char c;
                char previous_c = ' ';
                while ((c = fgetc(fp1)) != EOF) {
                    if (c == ' ') {
                        previous_c = c;
                        continue;
                    } else {
                        if (previous_c != ' ') {
                            //handle string with value of '10'
                            input_data1[--i].value[1] = c;
                            i++;
                        } else {
                            input_data1[i++].value[0] = c;
                            previous_c = c;
                        }
                    }
                }
            } else {
                printf("\nError opening input file.\n");
                fprintf(fp3, "\nError opening input file.\n");
                return 1;
            }
            //now insert each element of this structure to a queue
            QUEUE* asp0;
            QUEUE* asp1;
            STACK* asp2;
            printf("\nOriginal cards in order:\n");
            fprintf(fp3, "\nOriginal cards in order:\n");
            asp0 = get_cards_in_original_order(input_data1);
            printQueue(asp0);
            //unloading input array to queue: shuffling
            asp1 = shuffle_cards_stage1(input_data1);
            printf("\nAfter first shuffle (Array -> Queue)\n");
            fprintf(fp3, "\nAfter first shuffle (Array -> Queue)\n");
            printQueue(asp1);
            //unloading queue to stack: shuffling
            asp2 = shuffle_cards_stage2(asp1);
            printf("\nAfter second shuffle (Queue -> Stack)\n");
            fprintf(fp3, "\nAfter second shuffle (Queue -> Stack)\n");
            printStack(asp2);
            //unloading from stack to queue: shuffling
            printf("\nNow doing the third shuffle (Stack -> Queue -> Queue)\n");
            fprintf(fp3, "\nNow doing the third shuffle (Stack -> Queue -> Queue)\n");
            shuffle_cards_stage3(asp2);
            fclose(fp1);
        }  while ((pickDataFile == 1) || (pickDataFile == 2));
    } else {
        printf("\nError opening output file.\n");
        fprintf(fp3, "\nError opening output file.\n");
        fclose(fp3);
        return 1;
    }
    fclose(fp1);
    fclose(fp3);
    return 0;
    
}

//load input array to queue just for dispalying it
QUEUE* get_cards_in_original_order(INPUTDATA arrayOfStructs[]) {
    QUEUE* newQueue = (QUEUE*) malloc (sizeof(QUEUE));
    newQueue->front = -1;
    newQueue->rear = -1;
    for (int i = 0; i < SUITSIZE; i++) {
        /* insert a *face* to queue */
        //all cards {2, 3, 4, J, Q, K..} except '10'
        if (arrayOfStructs[i].value[1] == '\0') {
            enqueue(newQueue, arrayOfStructs[i].value[0]);
            //if card is '10'
        } else {
            int digit = (arrayOfStructs[i].value[0] - '0') * 10 + (arrayOfStructs[i].value[1] - '0');
            enqueue(newQueue, substitute10byX(digit));
        }
    }
    return newQueue;
}


//arrayOfStructs is input array; each element is a struct to store an array of characters
//load input array to a queue and shuffle this queue
QUEUE* shuffle_cards_stage1(INPUTDATA arrayOfStructs[]) {
    QUEUE* newQueue = (QUEUE*) malloc (sizeof(QUEUE));
    newQueue->front = -1;
    newQueue->rear = -1;
    for (int i = (SUITSIZE-1); i >= 0; i--) {
        
        /* insert a *face* to queue */
        //all cards {2, 3, 4, J, Q, K..} except '10'
        if (arrayOfStructs[i].value[1] == '\0') {
            enqueue(newQueue, arrayOfStructs[i].value[0]);
        //if card is '10'
        } else {
            int digit = (arrayOfStructs[i].value[0] - '0') * 10 + (arrayOfStructs[i].value[1] - '0');
            enqueue(newQueue, substitute10byX(digit));
        }
        
        //remove the first element from the front
        int faceValue = 0;
        faceValue = dequeue(newQueue);
        //insert removed element to the rear
        enqueue(newQueue, faceValue);
    }
    return (newQueue);
}

//load queue to a stack
STACK* shuffle_cards_stage2(QUEUE* qptr) {
    STACK* newStack = (STACK*) malloc (sizeof(STACK));
    newStack->top = -1;
    //dequeue from front of queue and push to top of stack1
    for (int i = qptr->front; i <= qptr->rear; i++) {
        int faceValue = 0;
        faceValue = dequeue(qptr);
        push(newStack, faceValue);
    }
    return (newStack);
}

//load stack to a queue and shuffle it
void shuffle_cards_stage3(STACK *stack) {
    QUEUE* pq1 = (QUEUE*) malloc (sizeof(QUEUE));
    QUEUE* pq2 = (QUEUE*) malloc (sizeof(QUEUE));
    pq1->front = -1;
    pq1->rear = -1;
    pq2->front = -1;
    pq2->rear = -1;
    
    //load stack to queue pq1
    for (int i = stack->top; i>=0; i--) {
        int tempStackValue = pop(stack);
        enqueue(pq1, tempStackValue);
    }
    
    while (!isEmpty(pq1) && (pq1->front != pq1->rear)) {
        int topCard = dequeue(pq1);
        enqueue(pq1, topCard);
        printf("\nShuffle cards...\n");
        fprintf(fp3, "\nShuffle cards...\n");
        //ASCII code of 'X' is 88
        if (topCard == 88) {
            topCard = 10;
            printf("\nRemove card: (%d)", topCard);
            printf(", then Insert card (%d) to the rear", topCard);
            fprintf(fp3, "\nRemove card: (%d)", topCard);
            fprintf(fp3, ", then Insert card (%d) to the rear", topCard);
        } else {
            printf("\nRemove card: (%c)", topCard);
            printf(", then Insert card (%c) to the rear", topCard);
            fprintf(fp3, "\nRemove card: (%c)", topCard);
            fprintf(fp3, ", then Insert card (%c) to the rear", topCard);
        }
        
        printQueue(pq1);
        int nextTopCard = dequeue(pq1);
        enqueue(pq2, nextTopCard);
    
        //ASCII code of 'X' is 88
        if (nextTopCard == 88) {
            nextTopCard = 10;
            printf("\n***** Then remove card (%d) and show this card on table *****", nextTopCard);
            fprintf(fp3, "\n*** Then remove card (%d) and show this card on table *****", nextTopCard);
        } else {
            printf("\n***** Then remove card (%c) and show this card on table *****", nextTopCard);
            fprintf(fp3, "\n*** Then remove card (%c) and show this card on table *****", nextTopCard);
        }
        printQueue(pq2);
    }
    //last card in input queue
    int topCard = dequeue(pq1);
    int oldTopCard = 0;
    if (topCard == 88) {
        oldTopCard = 88;
        topCard = 10;
        printf("\n(%d) is the last card. Remove card: (%d) from deck", topCard, topCard);
        fprintf(fp3, "\n(%d) is the last card. Remove card: (%d) from deck", topCard, topCard);
    } else {
        oldTopCard = topCard;
        printf("\n(%c) is the last card. Remove card: (%c) from deck", topCard, topCard);
        fprintf(fp3, "\n(%c) is the last card. Remove card: (%c) from deck", topCard, topCard);
    }
    enqueue(pq2, oldTopCard);
    if (topCard == 10) {
        printf("\n***** Show this card (%d) on table", topCard);
        fprintf(fp3, "\n***** Show this card (%d) on table", topCard);
    } else {
        printf("\n***** Show this card (%c) on table", topCard);
        fprintf(fp3, "\n***** Show this card (%c) on table", topCard);
    }
    printQueue(pq2);
    free(pq1);
    free(pq2);
}



//substitute 10 by 'X' - structure only handle character
int substitute10byX(int n) {
    if (n == 10) {
        return 88;
    } else {
        return n;
    }
}

//check if the queue is empty
int isEmpty(QUEUE *ps) {
    if ((ps->front == EMPTYQUEUE) && (ps->rear == EMPTYQUEUE)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//enqueue: insert item to the rear-ending side of the queue
//front of queue ---> [0,1,2,3,4,5,6,7,8,9] <--- rear of queue
int enqueue(QUEUE *ps, int c) {
    //check for overflow condition
    if (ps->rear == MAXQUEUE-1) {
        printf("%s", "Queue overflow!");
        fprintf(fp3, "%s", "Queue overflow!");
        exit(1);
    } else {
        (ps->rear)++;
    }
    //check if front pointer catches up with rear pointer
    //note that (ps->rear) is now increased by one after post increasement
    if ((ps->front == -1) && (ps->rear == -1)) {
        printf("%s", "Queue overflow!");
        fprintf(fp3, "%s", "Queue overflow!");
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
int dequeue(QUEUE *ps) {
    int indexOfnumberToBeRemovedFromQueue, valueOfNumberToBeRemoved = -1;
    if (isEmpty(ps)) {
        printf("%s", "\nQueue underflow\n");
        fprintf(fp3, "%s", "\nQueue underflow\n");
        exit(1);
    }
    if ((ps->front == MAXQUEUE) || (ps->front > ps->rear)) {
        ps->front = 0;
        ps->rear = 0;
        valueOfNumberToBeRemoved = -1;
    } else {
        indexOfnumberToBeRemovedFromQueue = ps->front;
        valueOfNumberToBeRemoved = ps->queueElement[indexOfnumberToBeRemovedFromQueue];
        //reset value
        ps->queueElement[indexOfnumberToBeRemovedFromQueue] = -1;
        (ps->front)++;
    }
    return valueOfNumberToBeRemoved;
}

void printQueue(QUEUE *ps) {
    fprintf(fp3, "\n");
    printf("\n");
    if (isEmpty(ps)) {
        fprintf(fp3, "%s", "\nQueue is Empty\n");
        printf("%s", "\nQueue is Empty\n");
    } else {
        //print index
        for (int i = ps->front; i <= ps->rear; i++) {
            // print label
            if (i == ps->front) {
                printf("%s", "index: ");
                fprintf(fp3, "%s", "index: ");
            }
            // print values
            // if it is rear element, do not print arrow
            if (i == ps->rear) {
                fprintf(fp3, "%3d", i);
                printf("%3d", i);
            } else {
                fprintf(fp3, "%3d<-", i);
                printf("%3d<-", i);
            }
        }
        fprintf(fp3, "\n");
        printf("\n");
        //print value
        for (int i = ps->front; i <= ps->rear; i++) {
            // if it is rear element, do not print arrow
            // print label
            if (i == ps->front) {
                printf("%s", "value: ");
                fprintf(fp3, "%s", "value: ");
            }
            // print values
            if (i == ps->rear) {
                if ((ps->queueElement[i]) == 'X') {
                    fprintf(fp3, "%3d", 10);
                    printf("%3d", 10);
                } else {
                    fprintf(fp3, "%3c", ps->queueElement[i]);
                    printf("%3c", ps->queueElement[i]);
                }
                
            } else {
                if ((ps->queueElement[i]) == 'X') {
                    fprintf(fp3, "%3d<-", 10);
                    printf("%3d<-", 10);
                } else {
                    fprintf(fp3, "%3c<-", ps->queueElement[i]);
                    printf("%3c<-", ps->queueElement[i]);
                }
            }
        }
    }
    fprintf(fp3, "\n");
    printf("\n");
}


void printStack(STACK *ps) {
    fprintf(fp3, "\n");
    printf("\n");
    if (isStackEmpty(ps)) {
        fprintf(fp3, "%s", "\nStack is Empty\n");
        printf("%s", "\nStack is Empty\n");
    } else {
        //print index
        for (int i = ps->top; i >=0; i--) {
            // print label
            if (i == ps->top) {
                printf("%s", "index: ");
                fprintf(fp3, "%s", "index: ");
            }
            if (i == 0) {
                fprintf(fp3, "%3d", i);
                printf("%3d", i);
            } else {
                fprintf(fp3, "%3d<-", i);
                printf("%3d<-", i);
            }
        }
        fprintf(fp3, "\n");
        printf("\n");
        //print value
        for (int i = ps->top; i >= 0; i--) {
            // if it is at bottom of stack, do not print arrow
            // print label
            if (i == ps->top) {
                printf("%s", "value: ");
                fprintf(fp3, "%s", "value: ");
            }
            // print values
            if (i == 0) {
                if ((ps->stackelements[i]) == 'X') {
                    fprintf(fp3, "%3d", 10);
                    printf("%3d", 10);
                } else {
                    fprintf(fp3, "%3c", ps->stackelements[i]);
                    printf("%3c", ps->stackelements[i]);
                }
                
            } else {
                if ((ps->stackelements[i]) == 'X') {
                    fprintf(fp3, "%3d<-", 10);
                    printf("%3d<-", 10);
                } else {
                    fprintf(fp3, "%3c<-", ps->stackelements[i]);
                    printf("%3c<-", ps->stackelements[i]);
                }
            }
        }
    }
    fprintf(fp3, "\n");
    printf("\n");
}


//check if stack is empty
int isStackEmpty(STACK *sp) {
    if (sp->top == EMPTYSTACK) {
        return TRUE;
    } else {
        return FALSE;
    }
}
//peek the top value of stack
//for expression conversion stack, data type is char
int peek(STACK *sp) {
    if (isStackEmpty(sp)) {
        fprintf(fp3, "\nStack is empty!\n");
        printf("%s", "\nStack is empty!\n");
        return 0;
    } else {
        return sp->stackelements[(sp->top)];
    }
}

//push an item to the stack
//for expression conversion stack
void push(STACK *sp, int x) {
    if (sp->top == MAXSTACK-1) {
        printf("%s", "Stack overflow!");
        fprintf(fp3, "Stack overflow!");
        exit(1);
    } else {
        sp->stackelements[++(sp->top)] = x;
    }
}

//pop the top item off the stack
//for expression conversion stack - data type is char
int pop(STACK *sp) {
    if (isStackEmpty(sp)) {
        printf("%s", "\nStack is empty!\n");
        fprintf(fp3, "%s", "\nStack is empty!\n");
        exit(1);
    } else {
        char value = sp->stackelements[sp->top];
        sp->stackelements[(sp->top)] = 0;
        (sp->top)--;
        return value;
    }
}

//for expression conversion stack - set to 0
void resetStack(STACK *sp) {
    sp->top = 0;
    for (int i = 0; i < MAXSTACK; i++) {
        sp->stackelements[(sp->top)++] = 0;
    }
    sp->top = 0;
}



