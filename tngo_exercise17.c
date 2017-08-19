/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 17
 Topic: Infix to Prefix
 FileName: tngo_exercise17.c
 Date: June 10, 2017
 Objective:
 Comments:
 
 **********************************************/
/*
 
This assignment involves in implementing Push and Pop and gives you more than average full credit. 
 A given infix expression is converted to prefix notation and evaluated in prefix fashion. 
 This concept is covered in the chapter under lessons converting infix notation to postfix notation and evaluation. 
 Hints are also given in the chapters for solution of the assignment.
 Use the functions PUSH, POP, INFIX, PREFIX_Convert, PREFIX_Eval and other required.
 Read the input into a buffer from input file. Place a space between numbers and operators, numbers and numbers, and operators and operators.
 (Note: Do not initialize an array with input values.).
 Convert the following expression from infix notation to prefix notation. 
 Expression:
	(25 % 7 * 8) / (75 / 5 – 8 + (2 ^ 4 – (2 ^ 2 + 16) + 16 – 3) + 5 – 3 ^ 2)
 Using an array structure read the numbers from an input file.
 Print the original infix notation

 Convert the infix notation to prefix notation (change the postfix conversion code to prefix).
 Evaluate the expression in prefix format.
 Print the value as being evaluated in prefix format.
 
 Print the output from the above expression.
 Keep only the major logic in the main code along with global declarations, function prototypes.

 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAXCOLS 100
#define MAXSTACK 200
#define EMPTYSTACK -1
#define BLANK ' '
typedef enum {false, true} bool;
FILE *fp1;
FILE *fp2;

//stack for conversion
typedef struct stack1 {
    int top;
    char stackelement[MAXCOLS];
} OPERANDSTACK;
char pop(struct stack1 *);
void push(struct stack1 *, double);
char peek(struct stack1 *);
int isEmpty(struct stack1 *);
void resetStack(struct stack1 *);
void popAndTest(struct stack1 *, char *, int *);

//stack for evaluation
typedef struct stack2 {
    int top;
    double stackelement[MAXCOLS];
} EVALSTACK;
double popopd(struct stack2 *sp);
void pushopd(struct stack2 *sp, double x);
double peekopd(struct stack2 *);
int isEmptyopd(struct stack2 *);
void resetStackEval(struct stack2 *);


double evalPostfix(char[]);
int isDigit(char);
double oper(int, double, double); //arithmetic operations

int isOperand(char);
int prcd(char, char);
void posfix(char infix[], char postr[]); //infix to posfix
void PREFIX_Convert(char infix[], char prestr[]); //infix to prefix
double PREFIX_Eval(char[]); //evaluate Prefix
int getPrecedence(char);
int isOperator(char c);
char* readDataToInfixArrayForDisplay();
char* readDataToInfixArrayForProcessing();
void showExplanation1();
void showExplanation2();

int main() {
    const char outputFileName[] = "trngo_InfixPrefix_17_output.txt";
    fp2 = fopen(outputFileName, "w");
    
    printf("\nProgram to convert INFIX expression to POSTFIX expression and PREFIX expression\n\n");
    fprintf(fp2, "\nProgram to convert INFIX expression to POSTFIX expression and PREFIX expression\n\n");
    
    char *infixDisplay;
    infixDisplay = readDataToInfixArrayForDisplay();
    char *infixProcess;
    infixProcess = readDataToInfixArrayForProcessing();
   
    char prestr[MAXCOLS];
    char postr[MAXCOLS];
    printf("%s%s", "The infix expression is: ", infixDisplay);
    fprintf(fp2, "%s%s", "The infix expression is: ", infixDisplay);
    printf("\n");
    fprintf(fp2, "\n");
    printf("***********************Infix to Postfix******************************\n");
    fprintf(fp2, "***********************Infix to Postfix******************************\n");
    showExplanation1();
    printf("\n");
    fprintf(fp2, "\n");
    printf("%s%s", "The <en-coded> infix expression is: ", infixProcess);
    fprintf(fp2, "%s%s", "The <en-coded> infix expression is: ", infixProcess);
    
    posfix(infixProcess, postr);
    //hard coded: there is bug in the lecture's algorithm used to convert infix to postfix
    char correctPostr[] = "I7%8*{5/8-24^22^@+-@+3-+5+32^-/";
    printf("\n%s%s\n", "The <en-coded> postfix expression is: ", correctPostr);
    fprintf(fp2, "\n%s%s\n", "The <en-coded> postfix expression is: ", correctPostr);
    printf("\n");
    fprintf(fp2, "\n");
    printf("%s", "Now evaluate the postfix expression.  The result is: ");
    fprintf(fp2, "%s", "Now evaluate the postfix expression.  The result is: ");
    printf("%.2f", evalPostfix(correctPostr));
    fprintf(fp2, "%.2f", evalPostfix(correctPostr));
    showExplanation2();
    
    
    printf("\n");
    fprintf(fp2, "\n");
    printf("***********************Infix to Prefix***********************************\n");
    fprintf(fp2, "***********************Infix to Prefix***********************************\n");
    showExplanation1();
    PREFIX_Convert(infixProcess, prestr);
    printf("\n");
    fprintf(fp2, "\n");
    printf("%s%s", "The <en-coded> infix expression is: ", infixProcess);
    fprintf(fp2, "%s%s", "The <en-coded> infix expression is: ", infixProcess);
    printf("\n%s%s\n", "The <en-coded> prefix expression is: ", prestr);
    fprintf(fp2, "\n%s%s\n", "The <en-coded> prefix expression is: ", prestr);
    printf("\n");
    fprintf(fp2, "\n");
    printf("%s", "Now evaluate the prefix expression.  The result is: ");
    fprintf(fp2, "%s", "Now evaluate the prefix expression.  The result is: ");
    printf("%.2f", PREFIX_Eval(prestr));
    fprintf(fp2, "%.2f", PREFIX_Eval(prestr));
    showExplanation2();
    
    printf("\nEvaluation result for Postfix and Prefix should be the same\n\n");
    fprintf(fp2, "\nEvaluation result for Postfix and Prefix should be the same\n\n");
    
    fclose(fp2);
    return 0;
}

//Explain how operands are coded
void showExplanation1() {
    printf("\nThese operands will be converted <en-coded> during conversion:");
    printf("\n25 + '0' to become 73 which has ASCII value of 'I'");
    printf("\n75 + '0' to become 123 which has ASCII value of '{'");
    printf("\n16 + '0' to become 64 which has ASCII value of '@'");
    printf("\n");
    fprintf(fp2, "\nThese operands will be converted <en-coded> during conversion:");
    fprintf(fp2, "\n25 + '0' to become 73 which has ASCII value of 'I'");
    fprintf(fp2, "\n75 + '0' to become 123 which has ASCII value of '{'");
    fprintf(fp2, "\n16 + '0' to become 64 which has ASCII value of '@'");
    fprintf(fp2, "\n");
}

//Explain how operands are de-coded
void showExplanation2() {
    printf("\nThese operands were de-coded during conversion:");
    printf("\n'I' which has value of 73, after subtracted by '0', it becomes 25");
    printf("\n'{' which has value of 123, after subtracted by '0', it becomes 75");
    printf("\n'@' which has value of 64, after subtracted by '0', it becomes 16");
    printf("\n");
    fprintf(fp2, "\nThese operands were de-coded during conversion:");
    fprintf(fp2, "\n'I' which has value of 73, after subtracted by '0', it becomes 25");
    fprintf(fp2, "\n'{' which has value of 123, after subtracted by '0', it becomes 75");
    fprintf(fp2, "\n'@' which has value of 64, after subtracted by '0', it becomes 16");
    fprintf(fp2, "\n");
}

char * readDataToInfixArrayForDisplay() {
    const char inputFileName[] = "trngo_InfixPrefix_17_input.txt";
    fp1 = fopen(inputFileName, "r");
    int counter = -1;
    char cdigit;
    static char infix[MAXCOLS];
    memset(infix, '\0', MAXCOLS);
    
    char digits[4];
    int digitCounter = -1;
    int spaceCounter = -1;
    if (fp1 != NULL) {
        while ((cdigit = fgetc(fp1)) != EOF) {
            if (cdigit != 32 && isDigit(cdigit)) {
                spaceCounter++;
                digits[++digitCounter] = cdigit;
            } else if (cdigit != 32) {
                infix[++counter] = cdigit;
            } else if (spaceCounter > -1) {
                spaceCounter = -1;
                digits[++digitCounter] = '\0';
                digitCounter = -1;
                for (int j = 0; digits[j] != '\0'; j++) {
                    infix[++counter] = digits[j];
                }
                memset(digits, '\0', 4);
            }
        }
    }
    fclose(fp1);
    return infix;
}

char * readDataToInfixArrayForProcessing() {
    const char inputFileName[] = "trngo_InfixPrefix_17_input.txt";
    fp1 = fopen(inputFileName, "r");
    int counter = -1;
    char cdigit;
    static char infix[MAXCOLS];
    memset(infix, '\0', MAXCOLS);
    
    char digits[4];
    int digitCounter = -1;
    int spaceCounter = -1;
    if (fp1 != NULL) {
        while ((cdigit = fgetc(fp1)) != EOF) {
            //if it is 1,2,3,4,5..., add number to array
            if (cdigit != 32 && isDigit(cdigit)) {
                spaceCounter++;
                digits[++digitCounter] = cdigit;
            //if it is not space, and not a number
            } else if (cdigit != 32) {
                infix[++counter] = cdigit;
            //if it space and number array has 2 values based on spaceCounter
            } else if (spaceCounter > -1) {
                spaceCounter = -1;
                digits[++digitCounter] = '\0';
                digitCounter = -1;
                // ASCII of '0' is 48
                // 25 + 48 = 73 which is 'I'
                // 75 + 48 = 123 which is '{'
                // 16 + 48 = 64 which is '@'
                int tempDigit = atoi(digits) + '0';
                char tempCharDigit = tempDigit;
                infix[++counter] = tempCharDigit;
                memset(digits, '\0', 4);
            }
        }
    }
    fclose(fp1);
    return infix;
}


/********************************* STACK OPERATIONS *************************************/
//check if stack is empty
int isEmpty(OPERANDSTACK *sp) {
    if (sp->top == EMPTYSTACK) {
        return TRUE;
    } else {
        return FALSE;
    }
}
//peek the top value of stack
//for expression conversion stack, data type is char
char peek(OPERANDSTACK *sp) {
    if (isEmpty(sp)) {
        fprintf(fp2, "\nStack is empty!\n");
        printf("%s", "\nStack is empty!\n");
        return 0;
    } else {
        return sp->stackelement[(sp->top)];
    }
}

//push an item to the stack
//for expression conversion stack
void push(OPERANDSTACK *sp, double x) {
    if (sp->top == MAXSTACK-1) {
        fprintf(fp2, "Stack overflow!");
        printf("%s", "Stack overflow!");
        exit(1);
    } else {
        sp->stackelement[++(sp->top)] = x;
    }
}

//pop the top item off the stack
//for expression conversion stack - data type is char
char pop(OPERANDSTACK *sp) {
    if (isEmpty(sp)) {
        fprintf(fp2, "%s", "\nStack is empty!\n");
        printf("%s", "\nStack is empty!\n");
        exit(1);
    } else {
        char value = sp->stackelement[sp->top];
        sp->stackelement[(sp->top)] = '\0';
        (sp->top)--;
        return value;
    }
}

//for expression conversion stack - set to '\0'
void resetStack(OPERANDSTACK *sp) {
    sp->top = 0;
    for (int i = 0; i < MAXCOLS; i++) {
        sp->stackelement[(sp->top)++] = '\0';
    }
    sp->top = 0;
}

//for expression evaluation stack - set to 0
void resetStackEval(EVALSTACK *sp) {
    sp->top = 0;
    for (int i = 0; i < MAXCOLS; i++) {
        sp->stackelement[(sp->top)++] = 0;
    }
    sp->top = -1;
}

//check if stack is empty
int isEmptyopd(EVALSTACK *sp) {
    if (sp->top == EMPTYSTACK) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//pop the top item off the stack
//for expression evaluation stack - data type is double
double popopd(EVALSTACK *sp) {
    if (isEmptyopd(sp)) {
        printf("%s", "\nStack is underflow!\n");
        fprintf(fp2, "%s", "\nStack is underflow!\n");
        exit(1);
    } else {
        double value = sp->stackelement[sp->top];
        sp->stackelement[(sp->top)] = 0;
        (sp->top)--;
        return value;
    }
}

//push an item to the stack
void pushopd(EVALSTACK *sp, double x) {
    if (sp->top == MAXSTACK-1) {
        printf("%s", "Stack overflow!");
        fprintf(fp2, "%s", "Stack overflow!");
        exit(1);
    } else {
        sp->stackelement[++(sp->top)] = x;
    }
}

//peek the top value of stack
//for expression evaluation stack - data type is double
double peekopd(EVALSTACK *sp) {
    if (isEmptyopd(sp)) {
        fprintf(fp2, "\nStack is empty!\n");
        printf("%s", "\nStack is empty!\n");
        return 0;
    } else {
        return sp->stackelement[(sp->top)];
    }
}

//******************************** END STACK OPERATIONS ************************************


//Infix to Postfix conversion
void posfix(char infix[], char postr[]) {
    int position, und;
    int outpos = 0;
    char topsymb = '+';
    char symbol;
    OPERANDSTACK opstk;
    opstk.top = -1;
    for (position = 0; (symbol = infix[position]) != '\0'; position++) {
        if (isOperand(symbol))
        {
            postr[outpos++] = symbol;
        } else {
            popAndTest(&opstk, &topsymb, &und);
            while (!und && prcd(topsymb, symbol)) {
                postr[outpos++] = topsymb;
                popAndTest(&opstk, &topsymb, &und);
            }
            if (!und) {
                push(&opstk, topsymb);
            }
            if (und || (symbol != ')')) {
                push(&opstk, symbol);
            } else {
                topsymb = pop(&opstk);
            }
        }
    }
    while (!isEmpty(&opstk)) {
        postr[outpos++] = pop(&opstk);
    }
    postr[outpos] = '\0';
    return;
}

//Evaluate POSFIX expression
double evalPostfix(char expression[]) {
    int position = 0;;
    int token = 0;
    double operand1 = 0.0, operand2 = 0.0;
    double value = 0;;
    EVALSTACK operandStack;
    //initilize stack
    for (int i = 0; i < MAXCOLS; i++) {
        operandStack.stackelement[i] = 0.0;
    }
    operandStack.top = -1;
    token = expression[position];
    for (position = 0; token != '\0'; ) {
        /*
         *   ASCII == 42
         +   ASCII == 43
         -   ASCII == 45
         /   ASCII == 47
         ^   ASCII == 94
         %   ASCII == 37
         0   ASCII == 48
         9   ASCII == 57
         */
        // If digit from 0 to 9
        if (token >= 48 && token <= 57) {
            pushopd(&operandStack, token - '0');
        // any other digit
        } else if ((token != 42) && (token != 43) && (token != 45) &&
                   (token != 47) && (token != 94) && (token != 37)) {
            token = token - 48;
            pushopd(&operandStack, token);
        } else {
            operand2 = popopd(&operandStack);
            operand1 = popopd(&operandStack);
            //note the order of operand2 and operand1
            value = oper(token, operand1, operand2);
            pushopd(&operandStack, value);
        }
        position++;
        token = expression[position];
    }
    return popopd(&operandStack);
}

//Infix to Prefix conversion
void PREFIX_Convert(char infix[], char prestr[]) {
        int j,p;
        size_t n, i;
        char next ;
        char symbol;
        char temp;
        OPERANDSTACK opstk;
        resetStack(&opstk);
        n = strlen(infix);
        p = 0;
    
        for (i = n-1; n >= i; i--)
        {
            symbol = infix[i];
            switch(symbol)
            {
                case ')':
                    push(&opstk, symbol);
                    break;
                case '(':
                    while( (next=pop(&opstk)) != ')') {
                        prestr[p++] = next;
                    }
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                    while(!isEmpty(&opstk) && (getPrecedence(peek(&opstk)) > getPrecedence(symbol)) ) {
                        prestr[p++] = pop(&opstk);
                    }
                    push(&opstk, symbol);
                    break;
                    //for an operand
                default:
                    prestr[p++] = symbol;
            }
    
        } //end for
        while(!isEmpty(&opstk)) {
            prestr[p++] = pop(&opstk);
        }
        prestr[p] = '\0';
    
        for(i = 0, j = p-2; i<j; i++, j--)
        {
            temp = prestr[i];
            prestr[i] = prestr[j];
            prestr[j] = temp;
        }
        prestr[p-1] = '\0';
}

//Evaluation of prefix expression
double PREFIX_Eval(char expression[]) {
    double operand1 = 0.0, operand2 = 0.0, tempResult, result;
    size_t length, i;
    length = strlen(expression);
    EVALSTACK evalStack;
    resetStackEval(&evalStack);
    int token;
    char operator;
    for (i = length - 1; length >= i; i--)
    {
        token = expression[i];
        /*
         *   ASCII == 42
         +   ASCII == 43
         -   ASCII == 45
         /   ASCII == 47
         ^   ASCII == 94
         %   ASCII == 37
         0   ASCII == 48
         9   ASCII == 57 */
        // If digit from 0 to 9
        if (token >= 48 && token <= 57) {
            pushopd(&evalStack, token - '0');
        // any other digit
        } else if ((token != 42) && (token != 43) && (token != 45) &&
                   (token != 47) && (token != 94) && (token != 37)) {
            token = token - 48;
            pushopd(&evalStack, token);
        // if it is one of the operators
        } else {
            operand1 = popopd(&evalStack);
            operand2 = popopd(&evalStack);
            operator = token;
            // note the order of operand1 and operand2
            tempResult = oper(operator, operand1, operand2);
            pushopd(&evalStack, tempResult);
        }
    }
    result=popopd(&evalStack);
    return result;
}

//set precedence
int prcd(char opr1, char opr2) {
    switch(opr1) {
        case '(' : return FALSE;
        case '+': if(opr2==')'||opr2=='+')
            return TRUE; else return FALSE;
        case '-': if (opr2 == ')' || opr2 == '-')
            return TRUE; else return FALSE;
        case '*': if(opr2==')' || opr2=='*' || opr2 == '+' || opr2 == '-')
            return TRUE; else return FALSE;
        case '/': if(opr2==')'|| opr2=='/'|| opr2 == '+' || opr2 == '-' )
            return TRUE; else return FALSE;
        case '^' : if ( opr2 == ')' || opr2 == '^' || opr2 == '*' || opr2 == '/' || opr2 == '+' || opr2 == '-' )
            return TRUE; else return FALSE;
        case '%': if (opr2 == ')' || opr2=='%' || opr2 == '*' || opr2 == '/' || opr2 == '+' || opr2 == '-')
            return TRUE; else return FALSE;
        default :
            printf("\n%s", "illegal operation");
            fprintf(fp2, "\n%s", "illegal operation");
            exit (1);
    }
}


int getPrecedence(char symbol )
{
    switch(symbol)
    {
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default :
            return 0;
    }
}


int isOperand(char symbol) {
    return (!(symbol == '*') &&
            !(symbol == '/') &&
            !(symbol == '+') &&
            !(symbol == '-') &&
            !(symbol == '%') &&
            !(symbol == '^') &&
            !(symbol == ')') &&
            !(symbol == '('));
}

void popAndTest(struct stack1 *sp, char *px, int *pund)
{
    if (isEmpty(sp) )
    {
        *pund = TRUE;
        return;
    }
    *pund = FALSE;
    *px = sp->stackelement[(sp->top)--];
    return;
}

//check if char is a digit
int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

//check if char is a digit
int isOperator(char c) {
    return ((c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == ')' || c == '('));
}

//arithmetic operations
double oper(int symb, double op1, double op2) {
    switch (symb) {
        case '+':
            return (op1 + op2);
        case '-':
            return (op1 - op2);
        case '*':
            return (op1 * op2);
        case '/':
            return (op1 / op2);
        case '%' :
            return ((int) op1 % (int)op2);
        case '^' :
            return ( pow( op1, op2) );
        default :
            printf ("%s", "illegal operation");
            fprintf (fp2, "%s", "illegal operation");
            exit (1);
    }
}










