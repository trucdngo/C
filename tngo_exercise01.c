
/********Prologue**********
University Of California Extension, Santa Cruz
Advanced C Programming
Instructor: Rajainder A. Yeldandi
Author: Truc Ngo
Assignment: 1
Topic: Convert from temperature from C to F and from F back to C
FileName: tngo_exercise01.c
Date:April 22, 2017
Objective: learning basics
Comments:

**************************/

#include <stdio.h>

// Convert from F degree to C
int F_to_C(int F_Degree) {
    return (F_Degree - 32)*5 / 9;
}
// Convert from C degree to F
int C_to_F(int C_Degree) {
    return (C_Degree * 9/5) + 32;
}

int main(int argc, const char * argv[]) {
    //char name1[] = {"hello"};
    //char name2[] = {'h','h','e','\0'};
    printf("Program to convert temperature\n");
    printf("option 1. Convert from F to C\n");
    printf("option 2. Convert from C to F\n");
    printf("Make your choice: ");
    int choice;
    int degree;
    int converted_degree;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("You picked option 1. Convert from F to C\n");
        printf("What is the Degree in F (?): ");
        scanf("%d", &degree);
        converted_degree = F_to_C(degree);
        printf("Degree in C is: %d\n", converted_degree);
    } else if (choice == 2) {
        printf("You picked option 2. Convert from C to F\n");
        printf("What is the Degree in C (?): ");
        scanf("%d", &degree);
        converted_degree = C_to_F(degree);
        printf("Degree in F is: %d\n", converted_degree);
    } else {
        return 0;
    }
    return 0;
}

 
