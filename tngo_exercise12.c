/********Prologue******************************
 
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 12
 Topic: Sorting
 FileName: tngo_exercise12.c
 Date: Jun 14, 2017
 Objective:
 Comments:
 
 **********************************************/
/*
This assignment deals with different sort routines. 
 You are expected to implement 4 simple sort routines and 3 advanced sort routines. 
 You will prompt the user to select one of the simple sort routines and one of the advanced sort routines. 
 Your output should consists of 2 selections of one simple sort routine and one advanced sort routine.
 
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
void print_menu();

void bubble_sort(int*in, int asize);
void insertion_sort(int*, int asize);
void shell_sort(int*, int asize, int incrmnts[], int numinc);
void selection_sort(int*, int asize);

void quick_sort(int*, int lowerBound, int asize);
void partition(int x[], int lb, int ub, int pj);
void heap_sort(int*, int asize);
void merge_sort(int*, int asize);


int main() {
    const char outputFileName[] = "trngo_sorting_12_output.txt";
    fp2 = fopen(outputFileName, "w");
    int* data = malloc(sizeof(int) * ASIZE);
    int choice;
    print_menu();
    while ((choice = getchar()) != 10) {
        switch(choice) {
            case 'B':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                bubble_sort(data, ASIZE);
                printf("\nBubble Sort:");
                fprintf(fp2, "\nBubble Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            case 'I':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                insertion_sort(data, ASIZE);
                printf("\nInsertion Sort:");
                fprintf(fp2, "\nInsertion Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            case 'L':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                int incrmnts[] = {5, 3, 1};
                int numinc = 3;
                shell_sort(data, ASIZE, incrmnts, numinc);
                printf("\nShell Sort:");
                fprintf(fp2, "\nShell Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            case 'S':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                selection_sort(data, ASIZE);
                printf("\nSelection Sort:");
                fprintf(fp2, "\nSelection Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            case 'Q':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                quick_sort(data, -1, ASIZE);
                printf("\nQuick Sort:");
                fprintf(fp2, "\nQuick Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            case 'H':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                heap_sort(data, ASIZE);
                printf("\nHeap Sort:");
                fprintf(fp2, "\nHeap Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            case 'M':
                fprintf(fp2, "%c", choice);
                data = importData();
                printf("\nDisplaying original data:\n");
                fprintf(fp2, "\nDisplaying original data:\n");
                print_data(data);
                merge_sort(data, ASIZE);
                printf("\nMerge Sort:");
                fprintf(fp2, "\nMerge Sort:");
                printf("\nShowing data after sorted...\n");
                fprintf(fp2, "\nShowing data after sorted...\n");
                print_data(data);
                print_menu();
                choice = getchar();
                continue;
            default:
                break;
        }
    }
    fclose(fp2);
    return 0;

}

void print_menu() {
    printf("\nChoose B. for Bubble Sort");
    printf("\nChoose I. for Insertion Sort");
    printf("\nChoose L. for Shell Sort");
    printf("\nChoose S. for Selection Sort");
    printf("\nChoose Q. for Quick Sort");
    printf("\nChoose H. for Heap Sort");
    printf("\nChoose M. for Merge Sort");
    printf("\n(Hit ENTER to QUIT!)");
    printf("\n*** Select a sorting algorithm: ");
    
    fprintf(fp2, "\nChoose B. for Bubble Sort");
    fprintf(fp2,"\nChoose I. for Insertion Sort");
    fprintf(fp2,"\nChoose L. for Shell Sort");
    fprintf(fp2,"\nChoose S. for Selection Sort");
    fprintf(fp2,"\nChoose Q. for Quick Sort");
    fprintf(fp2,"\nChoose H. for Heap Sort");
    fprintf(fp2,"\nChoose M. for Merge Sort");
    fprintf(fp2,"\n(Hit ENTER to QUIT!)");
    fprintf(fp2,"\n*** Select a sorting algorithm: ");
}


//merge sort
void merge_sort(int* x, int n) {
    int aux[n];
    int i, j, k, L1, L2, size, u1, u2;
    size = 1;
    while (size < n) {
        L1 = 0;
        k = 0;
        while (L1 + size < n) {
            L2 = L1 + size;
            u1 = L2 - 1;
            u2 = (L2+size-1<n) ? L2+size-1 : n-1;
            u1 = L2 -1;
            for(i = L1, j = L2; i <= u1 && j <= u2; k++) {
                if (x[i] <= x[j]) {
                    aux[k] = x[i++];
                } else {
                    aux[k] = x[j++];
                }
            }
            for(;i<=u1; k++) {
                aux[k] = x[i++];
            }
            for(;j<=u2; k++) {
                aux[k] = x[j++];
            }
            L1 = u2 + 1;
        }
        for (i = L1; k < n; i++) {
            aux[k++] = x[i];
        }
        for (i=0; i<n; i++) {
            x[i] = aux[i];
        }
        size *= 2;
    }
}



//heap sort
void heap_sort(int* x, int asize) {
    int i, elt, ch, pa, ivalue;
    for (i = 1; i < asize; i++) {
        elt = x[i];
        ch = i;
        pa = (ch - 1) / 2;
        while (ch > 0 && x[pa] < elt) {
            x[ch] = x[pa];
            ch = pa;
            pa = (ch - 1) / 2;
        }
        x[ch] = elt;
    }
    for (i = asize-1; i>0; i--) {
        ivalue = x[i];
        x[i] = x[0];
        pa = 0;
        if (i == 1) {
            ch = -1;
        } else {
            ch = 1;
        }
        if (i>2 && x[2] > x[1]) {
            ch = 2;
        }
        while (ch >= 0 && ivalue < x[ch]) {
            x[pa] = x[ch];
            pa = ch;
            ch = 2*pa + 1;
            if (ch + 1 <= i-1 && x[ch] < x[ch + 1]) {
                ch = ch + 1;
            }
            if (ch > i-1) {
                ch = -1;
            }
        }
        x[pa] = ivalue;
    }
}


//quick sort
void quick_sort(int* arrPtr, int lowerBound, int asize) {
    if (lowerBound > asize) {
        return;
    }
    int j;
    partition(arrPtr, lowerBound, asize, j);
    quick_sort(arrPtr, lowerBound, j-1);
    quick_sort(arrPtr, j+1, asize);
}

void partition(int x[], int lb, int ub, int pj) {
    int a, down, temp, up;
    a = x[lb];
    up = ub;
    down = lb;
    while (down < up) {
        while (x[down] <= a && down < ub) {
            down++;
        }
        while (x[up] > a) {
            up--;
        }
        if (down < up) {
            temp = x[down];
            x[down] = x[up];
            x[up] = temp;
        }
    }
    x[lb] = x[up];
    x[up] = a;
    pj = up;
}

//selection sort
void selection_sort(int* arrPtr, int asize) {
    int i, j;
    int min, temp;
    for (i = 0; i < asize-1; i++) {
        min = i;
        for (j = i + 1; j < asize; j++) {
            if (arrPtr[j] < arrPtr[min]) {
                min = j;
            }
        }
        temp = arrPtr[i];
        arrPtr[i] = arrPtr[min];
        arrPtr[min] = temp;

    }
}

//shell sort
void shell_sort(int arrPtr[], int asize, int incrmnts[], int numinc) {
    int incr, j, k, span, y;
    for (incr = 0; incr < numinc; incr++) {
        span = incrmnts[incr];
        for (j = span; j < asize; j++) {
            y = arrPtr[j];
            for (k=j-span;k>=0 && y<arrPtr[k];k -= span) {
                arrPtr[k + span] = arrPtr[k];
            }
            arrPtr[k + span] = y;
        }
    }
    
}

//insertion sort
void insertion_sort(int arrPtr[], int asize) {
    int i, k, y;
    for (k = 1; k < asize; k++) {
        y = arrPtr[k];
        for (i = k-1; i >= 0 && (y < arrPtr[i]); i--) {
            arrPtr[i+1] = arrPtr[i];
        }
        arrPtr[i+1] = y;
    }
}

//bubble sort
void bubble_sort(int* arrPtr, int asize) {
    for (int i = 1; i <= asize - 1; i++) {
        for (int j = 0; j <= asize - 2; j++) {
            if (arrPtr[j] > arrPtr[j+1]) {
                int temp = 0;
                temp = arrPtr[j];
                arrPtr[j] = arrPtr[j+1];
                arrPtr[j+1] = temp;
            }
        }
    }
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
