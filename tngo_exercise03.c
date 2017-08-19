/*
 ********Prologue**********
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 3
 Topic: Array Manipulation
 FileName: tngo_exercise03.c
 Date:April 22, 2017
 Objective: learning basics
 Comments:
 
 **************************/

 
#include <stdio.h>

// Print array
void printArray(int arrayName[], int arraySize) {
    printf("index\tvalue\n");
    for (int i = 0; i < arraySize; i++) {
        printf("%3d\t\t", i);
        printf("%3d\n", arrayName[i]);
    }
}
// Print array in reverse order
void printArrayReverseOrder(int arrayName[], int arraySize) {
    printf("index\tvalue\n");
    for (int i = arraySize - 1; i >= 0; i--) {
        printf("%3d\t\t", i);
        printf("%3d\n", arrayName[i]);
    }
}

// sort array inline - using bubble sort
// sort in ascending order - from smallest to biggest
void sortArray(int arrayName[], int arraySize) {
    int temp, i, j;
    for (i = 0 ; i < arraySize - 1; i++) {
        for (j = 0 ; j < arraySize - i - 1; j++) {
            if (arrayName[j] > arrayName[j+1]) {
                temp = arrayName[j];
                arrayName[j] = arrayName[j+1];
                arrayName[j+1] = temp;
            }
        }
    }
}

// return index value of first-matched element in array
// return -1 if element is not in array
int getIndexOfElement(int arrayName[], int arraySize, int arrayElementValue) {
    for (int i=0; i <arraySize; i++) {
        if (arrayName[i] == arrayElementValue) {
            return i;
        }
    }
    return -1;
}


int main(int argc, const char * argv[]) {
    const int SIZE = 40;
    int number_array[SIZE];
    int number;
    int index = 0;
    while(index < SIZE) {
        printf("Enter in 40 numbers.  Hit Enter after each number. \n");
        scanf("%d", &number);
        number_array[index] = number;
        index += 1;
    }
    printArray(number_array, SIZE);
    printf("Array in reverse order \n");
    printArrayReverseOrder(number_array, SIZE);
    sortArray(number_array, SIZE);
    printf("Array after being sorted in ascending order \n");
    printArray(number_array, SIZE);
    
    printf("-1 to stop.  Print index for array element with value:\n");
    int array_value;
    scanf("%d", &array_value);
    while(array_value != -1) {
        int array_index = getIndexOfElement(number_array, SIZE, array_value);
        if (array_index != -1) {
            printf("array element %d has index of %d\n", array_value, array_index);
        } else if (array_index == -1) {
            printf("array element %d is not in array\n", array_value);
        }
        printf("-1 to stop.  Print index for array element with value:\n");
        scanf("%d", &array_value);
    }
    return 0;
}
 


