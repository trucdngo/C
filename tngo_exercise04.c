/*
********Prologue**********
 University Of California Extension, Santa Cruz
 Advanced C Programming
 Instructor: Rajainder A. Yeldandi
 Author: Truc Ngo
 Assignment: 4
 Topic: Student & Class Grading
 FileName: tngo_exercise04.c
 Date:April 22, 2017
 Objective: learning basics
 Comments:
 
 **************************
 
 Use functions exclusively. follow the instructions in problem statement. Source has to be .c type and input and output can be screen shot or redirected file.
 
 Students have to divide the input test scores among 4, 5 or 6 student scores (one number only). Prompt the user to give the number of students for the scores to read. There are 60 input scores which need to be divided among the number of students entered by the user. Find the statistics for each student , as well as all the students separately. Assign the student number by calling a function and using a static variable initialized to 1000 and student number incremented to next value. The function passes a student number to the calling routine.
 
 Do not use any array or pointers or buffer. The statistics for each student and the combined students with variables only. Print the number of students chosen, the statistics for each student along with their assigned student id. Finally print the statistics for all students combined.
 
 This assignment is for practice only, you can verify your compiler, input and output submittals along wth the prologue. No grade will be given for this assignment.
 
**************************/

#include <stdio.h>
int main(int argc, const char * argv[]) {
    const int total_scores = 60;
    printf("Student Score Program\n");
    printf("How many students are there in your class?\n");
    int num_of_students = 0;
    while (1) {
        scanf("%d", &num_of_students);
        if (num_of_students > 0 && num_of_students < 7) {
            break;
        }
    }
    float class_sum = 0.0;
    int class_min = 32000;
    int class_max = 0;
    int class_score_counter = 0;
    for (int i = 0; i < num_of_students; i++) {
        float student_sum = 0.0;
        int student_max = 0;
        int student_min = 32000;
        int student_score_counter = 0;
        printf("Enter scores for students #%d\n", i + 1);
        int score = 0;
        for (int j = 0; j < total_scores / num_of_students; j++) {
            printf("Score %d = ", j);
            scanf("%d", &score);
            student_min = (student_min < score) ? student_min : score;
            student_max = (score >= student_max) ? score : student_max;
            student_sum += score;
            student_score_counter += 1;
            
            class_min = (class_min < score) ? class_min : score;
            class_max = (score >= class_max) ? score : class_max;
            class_sum += score;
            class_score_counter += 1;
            continue;
        }
        printf("___Student%d___\n", i+1);
        printf("Minimum score = %d \n", student_min);
        printf("Maximum score = %d \n", student_max);
        printf("Average score = %.2f \n", student_sum / student_score_counter);
        printf("\n");
    }
    printf("*** Class data ***\n");
    printf("Minimum score of class = %d \n", class_min);
    printf("Maximum score of class = %d \n", class_max);
    printf("Average score of class = %.2f \n", class_sum / class_score_counter);
}


