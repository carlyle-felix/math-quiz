#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char operator(int operator);
void grade(float total);
int calc(int num1, int num2, int operator);

int main(void) {
    int num1, num2, quiz_ans, user_ans, digits = 0, lvl, sym, round, n, score = 0, temp, i, x;

    srand((unsigned) time(NULL));

    printf("difficulty:\n(1) Operands < 10\n(2) Operands < 100\n(3) One operand is x\nSelect:  ");
    scanf("%d", &lvl);

    if (lvl == 1) {
        digits = 9;
    } else if (lvl == 2 || lvl == 3) {
        digits = 99;
    } else {
        printf("We're not there yet.\n");
        return 0;
    }

    printf("Enter number of rounds: ");
    scanf("%d", &n);

    for (round = 0; round < n; round++) {
        sym = rand() % 4;
        num1 = rand() % digits;
        num2 = rand() % digits;
        
        if (sym == 0 && lvl == 2 || sym == 0 && lvl == 3)                                       // Multiplication: for lvl 2, Make num2 a single digit
            num2 = num2 % 10;
        else if (sym == 1) {                                                                   // Division: Make num1 % num2 == 0
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

        if (lvl == 3) {
            quiz_ans = calc(num1, num2, sym);
            
            if (rand() % 2 == 0) {
                printf("\n%d.  x %c %d = %d\n", round + 1, operator(sym), num2, quiz_ans);
                printf("    x = ");
                scanf("%d", &num1);
            } else {
                num2 = 'x';    
                printf("\n%d.  %d %c x = %d\n", round + 1, num1, operator(sym), quiz_ans);
                printf("    x = ");
                scanf("%d", &num2);
            }
            user_ans = calc(num1, num2, sym);

        } else {
            printf("\n%d.  %d %c %d = ", round + 1, num1, operator(sym), num2);
            scanf("%d", &user_ans);
            quiz_ans = calc(num1, num2, sym);
        }

        if (quiz_ans == user_ans) {
            printf("    Correct!\n");
            score++;
        } else
            printf("    Incorrect, don't give up!\n");
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

int calc(int num1, int num2, int operator) {

    switch (operator) {
    case 0:
        return num1 * num2;
    case 1:
        return num1 / num2;
    case 2:
        return num1 + num2;
    case 3:
        return num1 - num2;
    }
}

char operator(int operator) {

    switch (operator) {
    case 0:
        return '*';
    case 1:
        return '/';
    case 2:
        return '+';
    case 3:
        return '-';
    }
}