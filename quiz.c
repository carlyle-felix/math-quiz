#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void grade(float total);

int main(void) {
    int num1, num2, ans, digits, lvl, op, round, n, score = 0, temp, i;                      

    srand((unsigned) time(NULL));

    printf("Select difficulty [(1) operands < 10 or (2) operands < 100]:  ");
    scanf("%d", &lvl);
    if (lvl == 1) {
        digits = 9;
    } else if (lvl == 2) {
        digits = 99;
    }
    printf("Enter number of rounds: ");
    scanf("%d", &n);

    
    for (round = 0; round < n; round++) {
        op = rand() % 4;
        printf("op: %d\n", op);   // debugging
        if (op == 0) {                                              // Addition
            num1 = rand() % digits;
            num2 = rand() % digits;
            printf("%d + %d =   ", num1, num2);
            scanf("%d", &ans);
            if (ans == num1 + num2){
                printf("Correct!\n");
                score++;
            } else 
                printf("Incorrect, don't give up!\n");
        } else if (op == 1) {                                       // Subtraction
            printf("%d - %d =   ", num1, num2);
            scanf("%d", &ans);
            if (ans == num1 - num2){
                printf("Correct!\n");
                score++;
            } else 
                printf("Incorrect, don't give up!\n");
        } else if (op == 2) {                                       // Multiplication: for lvl 2, Make num2 a single digit
            if (lvl == 2) 
               num2 = num2 % 10;
            printf("%d x %d =   ", num1, num2);
            scanf("%d", &ans);
            if (ans == num1 * num2){
                printf("Correct!\n");
                score++;
            } else 
                printf("Incorrect, don't give up!\n");
        } else if (op == 3) {                                        // Division: Make num1 % num2 == 0 (causing floating point exception)
            if (num1 < num2) {
                temp = num1;
                num1 = num2;
                num2 = temp;
            }
            
            if ( num1 %  num2 != 0) {
                for (i = 0; i < 5; i++) {
                    num1 = rand() % digits;
                    num2 = rand() % digits;

                    if (num1 < num2) {
                        temp = num1;
                        num1 = num2;
                        num2 = temp;
                    } 
                    if ( num1 %  num2 == 0)
                        break;
                }
            }

            if ( num1 %  num2 != 0) {
                round--;
                continue;
            }

            printf("%d / %d =   ", num1, num2);
            scanf("%d", &ans);
            if (ans == num1 / num2){
                printf("Correct!\n");
                score++;
            } else 
                printf("Incorrect, don't give up!\n");
        }
    }
    printf("\nYou got %d out of %d\n", score, n);
    grade((float) score / n * 100);
    
}

void grade(float total) {

    printf("\nGrade:  ");
    switch ((int) total / 10) {
        case 10:    printf("Perfect, A!\n");
                    break;
        case 9:     printf("A\n");
                    break;
        case 8:     printf("B\n");
                    break;
        case 7:     printf("C\n");
                    break;
        case 6:     printf("D\n");
                    break;
        default:    printf("F\n");  
    }
}