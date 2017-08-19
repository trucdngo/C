
 /********Prologue**********
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 5
 Topic: Pointers
 FileName: tngo_exercise05.c
 Date:April 22, 2017
 Objective: learning basics
 Comments:
 
 **************************
This assignment deals with pointer applications. The pointers, the value at their address, declaration of different pointers 
and their dereferencing is pacticed in this assignment. 
 It very important to know the declaration, referencing and dereferencing the pointers for the following assignments. 
 Give a complete detailed output.
*/


#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a = 25;
    float b = 3.142;
    double c = 1.73217;
    char d[] = "Hello, C Programmers";
    char e = 'x';
    
    int* i_ptr = &a;
    int** i_ptr_ptr = &i_ptr;
    
    printf("value of variable and address of a: %d --- %p\n", a, &a);
    printf("value of variable and address of b: %f --- %p\n", b, &b);
    printf("value of variable and address of c: %f --- %p\n", c, &c);
    printf("value of variable and address of d: %s --- %p\n", d, &d);
    printf("value of variable and address of e: %c --- %p\n", e, &e);
    
    printf("value of pointer to a: %p\n", i_ptr);
    printf("dereference value of pointer of a: %d\n", *i_ptr);
    
    printf("value of pointer to pointer to a: %p\n", i_ptr_ptr);
    printf("dereference value of pointer to pointer of a: %p\n", *i_ptr_ptr);
 }

