/********Prologue**********
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 2
 Topic: reading inputs and calculate average, maximum value and minimum value
 FileName: tngo_exercise02.c
 Date:April 22, 2017
 Objective: learning basics (Loops)
 Comments:
 
 **************************/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int score, min = 0, max = 0;
    int counter = 0;
    float sum = 0, score_avg = 0;
    printf("Keep entering scores.  Enter -1 to stop: \n");
    scanf("%d", &score);
    while(score != -1) {
        printf("You entered: %d\n", score);
        if (score > max)
            max = score;
        if (score < min)
            min = score;
        counter += 1;
        sum += score;
        printf("Keep entering scores.  Enter -1 to stop: \n");
        scanf("%d", &score);
    }
    score_avg = sum / counter;
    printf("Max score is: %d\n", max);
    printf("Min score is: %d\n", min);
    printf("Sum is: %.2f\n", sum);
    printf("Average is: %.2f\n", score_avg);
    return 0;
}





