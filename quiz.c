#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

char operator(int operator);
void grade(float total);
bool evaluate(int num1, int num2, int operator);

int main(void) {
    int num1, num2, digits, lvl, op, round, n, score = 0, temp, i, result;

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
        num1 = rand() % digits;
        num2 = rand() % digits;
        
        if (op == 0 && lvl == 2)                                       // Multiplication: for lvl 2, Make num2 a single digit
            num2 = num2 % 10;
        else if (op == 1) {                                            // Division: Make num1 % num2 == 0
            for (i = 0; num1 % num2 != 0 && i < 5; i++) {
                num1 = rand() % digits;
                num2 = rand() % digits;

                if (num1 < num2) {
                    temp = num1;
                    num1 = num2;
                    num2 = temp;
                }
            }

            if ( i == 5) {
                round--;
                continue;
            }
        }
        printf("%d %c %d = ", num1, operator(op), num2);
        result = evaluate(num1, num2, op);
        if (result)
            score++;
    }        
    printf("\nYou got %d out of %d.\n", score, n);
    grade((float) score / n * 100);
}

void grade(float total) {

    switch ((int) total / 10) {
    case 10:
        printf("Grade: Perfect, A!\n");
        break;
    case 9:
        printf("Grade: A\n");
        break;
    case 8:
        printf("Grade: B\n");
        break;
    case 7:
        printf("Grade: C\n");
        break;
    case 6:
        printf("Grade: D\n");
        break;
    default:
        printf("Grade: F\n");
    }
}

bool evaluate(int num1, int num2, int operator) {
    
    int quiz_ans, user_ans;
    
    switch (operator) {
    case 0:
        quiz_ans = num1 * num2;
        break;
    case 1:
        quiz_ans = num1 / num2;
        break;
    case 2:
        quiz_ans = num1 + num2;
        break;
    case 3:
        quiz_ans = num1 - num2;
        break;
    }
    
    scanf("%d", &user_ans);
    if (quiz_ans == user_ans) {
        printf("Correct!\n");
        return true;
    } else {
        printf("Incorrect, don't give up!\n");
        return false;
    }
}

char operator(int operator) {

    switch (operator) {
    case 0:
        return 'x';
    case 1:
        return '/';
    case 2:
        return '+';
    case 3:
        return '-';
    }
}