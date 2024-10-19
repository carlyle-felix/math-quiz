 // Author: Carlyle Felix
 // This math quiz was written with the basics I've learned to date.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// function prototypes
char operator(int operator);
int calc();
char input(void);
int power(int base, int exp);
void interact(int round);

// externel variables
int num1, num2, lvl, sym, quiz_ans, user_ans;

int main(void) {
    int digits = 0, round, n, score, i, x;
    char choice = 'Y';

    srand((unsigned) time(NULL));

    while(choice == 'Y') {
        
        printf("\ndifficulty:\n(1) Operands < 10\n(2) Operands < 100\n(3) One operand is x and operands < 10\n(4) One operator is x, operand unkown and operands < 100\n(5) Squares, base < 10\nSelect:  ");
        scanf("%d", &lvl);
        
        // difficulty specifics 
        if (lvl == 1 || lvl == 3 || lvl == 5) {                    // Numbers should never be zero, add 1 when calling rand()
            digits = 8;
        } else if (lvl == 2 || lvl == 4) {
            digits = 98;
        } else {
            printf("We're not there yet!\n");
            return 0;
        }

        printf("Enter number of rounds: ");
        scanf("%d", &n);

        score = 0;
        // start quiz
        for (round = 0; round < n; round++) {
            num1 = rand() % digits + 1;
            num2 = rand() % digits + 1;
            sym = operator(rand() % 4);                                       // generate random operator
                    
            // operator specifics  
            if (sym == 0) {                                         // Multiplication: for levels 2, 3 and 4: Make num2 a single digit
                num2 %= 10;
            } else if (sym == 1) {                                  // Division: Make num1 % num2 == 0
                for (i = 0; num1 % num2 != 0 && i < 5; i++) {
                    num1 = rand() % digits + 1;
                    num2 = rand() % digits + 1;
                    
                    if (num1 < num2) {
                        int temp = num1;
                        num1 = num2;
                        num2 = temp;
                    }
                }
                if (num1 % num2 != 0) {
                    round--;
                    continue;
                }
            }

            interact(round);  
                 
            if (quiz_ans == user_ans) {
                printf("    Correct!\n");
                score++;
            } else {
                printf("    Incorrect, don't give up!\n");
            }
        }        
        printf("\nYou got %d out of %d.\n", score, n);

        // restart or quit
        while((choice = toupper(getchar())) != 'Y') {

            if (choice == 'N') {
                break;
            } else {
                printf("\nStart new quiz? (Y/N)\nSelect: ");
            }
        }
    }
    return 0;
}

 // caclucate answers, use ASCII conversions when operator was given by user
int calc() {                                                   

    switch (sym) {
        case 0: case 42:    return num1 * num2;
        case 1: case 47:    return num1 / num2;
        case 2: case 43:    return num1 + num2;
        case 3: case 45:    return num1 - num2;
    }
}

// calculate powers
int power(int base, int exp) {

    if (base == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    }

    return base * power(base, exp - 1);
}

// return operator from random number provided by main
char operator(int operator) {

    switch (operator) {
        case 0: return '*';
        case 1: return '/';
        case 2: return '+';
        case 3: return '-';
    }
}

// return user input operators to main
char input(void) {
    
    while (getchar() == '\n') {
        return getchar();
    }
}

void interact(int round) {

    int method = rand() % 2;

    quiz_ans = lvl < 5 ? calc() : power(num1, 2);
    switch(lvl) {
        case 1: case 2:     
            printf("\n%d.  %d %c %d = ", round + 1, num1, sym, num2);
            scanf("%d", &user_ans);
            return;

        case 3:             
            if (method) {
                printf("\n%d.  x %c %d = %d\n", round + 1, sym, num2, calc());
                printf("    x = ");
                scanf("%d", &num1);
            } else {
                printf("\n%d.  %d %c x = %d\n", round + 1, num1, sym, calc());
                printf("    x = ");
                scanf("%d", &num2);
            }
            break;

        case 4: 
            if (method) {
                printf("\n%d.  x ? %d = %d\n", round + 1, num2, calc());
                printf("    x = ");
                scanf("%d", &num1);
                printf("    Operator: ");
                sym = (int) input();
            } else { 
                printf("\n%d.  %d ? x = %d\n", round + 1, num1, calc());
                printf("    Operator: ");
                sym = (int) input();
                printf("    x = ");
                scanf("%d", &num2);
            }
            break;

        case 5:
            printf("%d² = ", num1);
            scanf("%d", &user_ans);
            return; 
    }
    user_ans = calc();
}