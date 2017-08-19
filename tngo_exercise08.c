/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 8
 Topic: Infix Expression validation
 FileName: tngo_exercise08.c
 Date: May 6, 2017
 Objective: Stacks
 Comments:
 
 **********************************************/
/*  
 Assignment 8 deals with stacks and stack implementation.
 In the output you are expected show each input and what decision you are making in parsing the string, 
 whether you are stacking the element or throwing it away (ignoring).
 Every input, every stacking and every unstacking has to be documented about the element.
 You may follow the algorithm in the course material for implementation. 
 An input file needs to be created with the input given in the assignment.
 Output will be written to an output file from your program. Follow the instructions carefully. 
 Your program has to analyze whether the given string is valid or not.
 In the output you need to mention as what input is read and what action is taken, whether the program
 is ignoring or placing it on the stack or examine the extracted symbol.
 
 Read input from INPUT file and read write output to OUTPUT file
 
*/



#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 100
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0

typedef struct stack {
    int top;
    char stackelement[MAXSTACK];
} CHSTACK;

int isEmpty (struct stack *);
int pop (struct stack *);
int push (struct stack *, char c);
int peek (struct stack *);
FILE *pFile1, *pFile2;

int main(int argc, const char * argv[]) {
    char readInTextString[100];
    CHSTACK alphastack, *asp;
    alphastack.top = EMPTYSTACK;
    asp = &alphastack;
    
    pFile1 = fopen("trngo_stackSimulation_08_input.txt", "r");
    //inputString = "{x+(y-[a+b])*c-[(d+e)]}/(h-(j-(k-[l-n])))"
    pFile2 = fopen("trngo_stackSimulation_08_output.txt", "w");
    char stringValue;
    int charCounter = 0;
    
    fprintf(pFile2, "\nUsing stack to validate an infix expression\n");
    printf("\nUsing stack to validate an infix expression\n");
    
    if ((pFile1 != NULL) && (pFile2 != NULL)) {
        while ((stringValue = fgetc(pFile1)) != EOF) {
            readInTextString[charCounter++] = stringValue;
            if (isEmpty(asp) && (stringValue == '{' || stringValue == '[' || stringValue == '(')) {
                fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                printf("\nPush a symbol onto the stack: %c", stringValue);
                push(asp, stringValue);
            } else {
                char token = peek(asp);
                switch (stringValue)
                {
                    case '{':
                        fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                        printf("\nPush a symbol onto the stack: %c", stringValue);
                        push(asp, stringValue);
                        continue;
                    case '[':
                        fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                        printf("\nPush a symbol onto the stack: %c", stringValue);
                        push(asp, stringValue);
                        continue;
                    case '(':
                        fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                        printf("\nPush a symbol onto the stack: %c", stringValue);
                        push(asp, stringValue);
                        continue;
                    case '}':
                        if (token == '{') {
                            fprintf(pFile2, "\n>>>Examine extracted symbol: %c", stringValue);
                            printf("\n>>>Examine extracted symbol: %c", stringValue);
                            fprintf(pFile2, "\nPop a symbol off the stack: %c", token);
                            printf("\nPop a symbol off the stack: %c", token);
                            pop(asp);
                        } else {
                            fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                            printf("\nPush a symbol onto the stack: %c", stringValue);
                            push(asp, stringValue);
                        }
                        continue;
                    case ')':
                        if (token == '(') {
                            fprintf(pFile2, "\n>>>Examine extracted symbol: %c", stringValue);
                            printf("\n>>>Examine extracted symbol: %c", stringValue);
                            fprintf(pFile2, "\nPop a symbol off the stack: %c", token);
                            printf("\nPop a symbol off the stack: %c", token);
                            pop(asp);
                        } else {
                            fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                            printf("\nPush a symbol onto the stack: %c", stringValue);
                            push(asp, stringValue);
                        }
                        continue;
                    case ']':
                        if (token == '[') {
                            fprintf(pFile2, "\n>>>Examine extracted symbol: %c", stringValue);
                            printf("\n>>>Examine extracted symbol: %c", stringValue);
                            fprintf(pFile2, "\nPop a symbol off the stack: %c", token);
                            printf("\nPop a symbol off the stack: %c", token);
                            pop(asp);
                        } else {
                            fprintf(pFile2, "\nPush a symbol onto the stack: %c", stringValue);
                            printf("\nPush a symbol onto the stack: %c", stringValue);
                            push(asp, stringValue);
                        }
                        continue;
                    default:
                        fprintf(pFile2, "\n>>>Examine extracted symbol: %c", stringValue);
                        printf("\n>>>Examine extracted symbol: %c", stringValue);
                        continue;
                } //end switch
            } //end if
        } //end while
    } //end if
    fclose(pFile1);
    
    
    printf("\n\nFor this expression: \n");
    fprintf(pFile2, "\n\nFor this expression: \n");
    for(int i = 0; readInTextString[i] != '\0'; i++) {
        fprintf(pFile2, "%c", readInTextString[i]);
        printf("%c", readInTextString[i]);
    }
    printf("\n");
    if (isEmpty(asp)) {
        fprintf(pFile2, "\nSince stack is now empty, this is a valid infix expression.\n\n");
        printf("\nSince stack is now empty, this is a valid infix expression.\n\n");
    } else {
        fprintf(pFile2, "\n\nSince stack is now not Empty, this is NOT a valid infix expression.\n\n");
        printf("\n\nSince stack is now not Empty, this is NOT a valid infix expression.\n\n");
    }
    fclose(pFile2);
    return 0;
    
}

//peek the top value of stack
int peek(CHSTACK *ps) {
    if (isEmpty(ps)) {
        fprintf(pFile2, "\nStack is empty!\n");
        printf("%s", "\nStack is empty!\n");
        return 0;
    } else {
        return ps->stackelement[(ps->top)];
    }
}

//check if the stack is empty
int isEmpty(CHSTACK *ps) {
    if (ps->top == EMPTYSTACK) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//push an item to the stack
int push(CHSTACK *ps, char c) {
    if (ps->top == MAXSTACK-1) {
        fprintf(pFile2, "Stack overflow!");
        printf("%s", "Stack overflow!");
        exit(1);
    } else {
        ps->stackelement[++(ps->top)] = c;
    }
    return 0;
}

//pop the top item off the stack
int pop(CHSTACK *ps) {
    if (isEmpty(ps)) {
        fprintf("%s", "\nStack is empty!\n");
        printf("%s", "\nStack is empty!\n");
        exit(1);
    } else {
        return ps->stackelement[(ps->top)--];
    }
}

*/
//************************** BACK UP 2 *********************************
/*
#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 100
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0

typedef struct stack {
    int top;
    char stackelement[MAXSTACK];
} CHSTACK;

int isEmpty (struct stack *);
int pop (struct stack *);
int push (struct stack *, char c);
int peek (struct stack *);


int main(int argc, const char * argv[]) {
    CHSTACK alphastack, *asp;
    alphastack.top = EMPTYSTACK;
    asp = &alphastack;

    char inputString[] = "{x+(y-[a+b])*c-[(d+e)]}/(h-(j-(k-[l-n])))";
    for (int i = 0; inputString[i] != '\0'; i++) {
        char stringValue = inputString[i];
        if (isEmpty(asp) && (inputString[i] == '{' || inputString[i] == '[' || inputString[i] == '(')) {
            printf("\nPush a symbol onto the stack: %c", stringValue);
            push(asp, stringValue);
        } else {
            char token = peek(asp);
            switch (stringValue)
            {
                case '{':
                    printf("\nPush a symbol onto the stack: %c", stringValue);
                    push(asp, stringValue);
                    continue;
                case '[':
                    printf("\nPush a symbol onto the stack: %c", stringValue);
                    push(asp, stringValue);
                    continue;
                case '(':
                    printf("\nPush a symbol onto the stack: %c", stringValue);
                    push(asp, stringValue);
                    continue;
                case '}':
                    if (token == '{') {
                        printf("\n>>>Examine extracted symbol: %c", stringValue);
                        printf("\nPop a symbol off the stack: %c", token);
                        pop(asp);
                    } else {
                        printf("\nPush a symbol onto the stack: %c", stringValue);
                        push(asp, stringValue);
                    }
                    continue;
                case ')':
                    if (token == '(') {
                        printf("\n>>>Examine extracted symbol: %c", stringValue);
                        printf("\nPop a symbol off the stack: %c", token);
                        pop(asp);
                    } else {
                        printf("\nPush a symbol onto the stack: %c", stringValue);
                        push(asp, stringValue);
                    }
                    continue;
                case ']':
                    if (token == '[') {
                        printf("\n>>>Examine extracted symbol: %c", stringValue);
                        printf("\nPop a symbol off the stack: %c", token);
                        pop(asp);
                    } else {
                        printf("\nPush a symbol onto the stack: %c", stringValue);
                        push(asp, stringValue);
                    }
                    continue;
                default:
                    printf("\n>>>Examine extracted symbol: %c", stringValue);
                    continue;
            }
        }
    }
    
    printf("\n\nFor this expression: \n");
    for(int i = 0; i < (sizeof(inputString) / sizeof(inputString[0])); i++) {
        printf("%c", inputString[i]);
    }
    
    if (isEmpty(asp)) {
        printf("\nSince stack is now Empty.  This is a valid infix expression.\n");
    } else {
        printf("\n\nSince stack is now not Empty.  This is NOT a valid infix expression.\n");
    }
    return 0;
    
}

//peek the top value of stack
int peek(CHSTACK *ps) {
    if (isEmpty(ps)) {
        printf("%s", "\nStack is empty!\n");
        return 0;
    } else {
        return ps->stackelement[(ps->top)];
    }
}

//check if the stack is empty
int isEmpty(CHSTACK *ps) {
    if (ps->top == EMPTYSTACK) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//push an item to the stack
int push(CHSTACK *ps, char c) {
    if (ps->top == MAXSTACK-1) {
        printf("%s", "Stack overflow!");
        exit(1);
    } else {
        ps->stackelement[++(ps->top)] = c;
    }
    return 0;
}

//pop the top item off the stack
int pop(CHSTACK *ps) {
    if (isEmpty(ps)) {
        printf("%s", "\nStack is empty!\n");
        exit(1);
    } else {
        return ps->stackelement[(ps->top)--];
    }
}

*/


//******************* BACK UP 1 ************************
/*
 char seq, keystroke;
 for (int i = 0; i < MAXSTACK; i++) {
     printf("\nEnter the next char in seq: ");
     scanf("%c%c", &seq, &keystroke);
     printf("\nPush a value onto a stack: %c", seq);
     push(asp, seq);
 }

 for (int i = 0; i < MAXSTACK; i++) {
     char ch = pop(asp);
     printf("\nPop a value out of stack: %c", ch);
 }
 
 char inputString[] = "{x+(y-[a+b])*c-[(d+e)]}/(h-(j-(k-[l-n])))";
 for (int i = 0; inputString[i] != '\0'; i++) {
     printf("\nPush a value onto a stack: %c", inputString[i]);
     push(asp, inputString[i]);
 }
 for (int i = 0; i < MAXSTACK; i++) {
     char ch = pop(asp);
     printf("\nPop a value out of stack: %c", ch);
 }
 printf("\nEnd of stack.\n");
 





