// Author: Carlyle Felix
// This math quiz was written with the basics I've learned to date.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// function prototypes
char operator(int operator);
int calc(int num1, int num2);
int input(void);
int power(int base, int exp);
int interact(int level, int round, int num1, int num2);

// externel variables
int symbol;

int main(void) {
    int num1, num2, lvl = 0, digits = 0, round, num_rounds, score, quiz_ans, user_ans;
    char choice = 'R';

    srand((unsigned) time(NULL));

    while(choice == 'R' || choice == 'N') {
        
        if (choice == 'N') lvl += 1;
        else {
            printf("\ndifficulty:\n(1) Operands < 10\n(2) Operands < 100\n(3) One operand is x and operands < 10\n(4) One operator is x, operand unkown and operands < 100\n(5) Squares, base < 10\nSelect:  ");
            scanf("%d", &lvl);
        }
        
        // difficulty digits 
        if (lvl == 1 || lvl == 3 || lvl == 5) {                             // Numbers should never be zero, add 1 when calling rand()
            digits = 8;
        } else if (lvl == 2 || lvl == 4) {
            digits = 98;
        } else {
            printf("We're not there yet!\n");
            return 0;
        }

        printf("\nEnter number of rounds: ");
        scanf("%d", &num_rounds);

        // start quiz
        for (score = 0, round = 1; round <= num_rounds; round++) {
            
            // generate random numbers and operator
            num1 = rand() % digits + 1;
            num2 = rand() % digits + 1;
            symbol = rand() % 4;                                               
            
            // operator specifics  
            if (symbol == 0) {                                                  // Multiplication: for levels 2, 3 and 4: Make num2 a single digit
                num2 %= 10;
            } else if (symbol == 1) {                                           // Division: Make num1 % num2 == 0
                int i;
                for (i = 0; num1 % num2 != 0 && i < 5 || num1 == 0; i++) {  
                    num1 = (rand() % (digits - 1)) + 2;                         // If num1 = 1, in level 3 it could be that 1 / x = 0: here, x could be any number and the answer would                                                       
                    num2 = rand() % digits + 1;                                 //                                                     be correct, since we're not dealing with floats.
                    
                    if (num1 < num2) {
                        int temp = num1;
                        num1 = num2;
                        num2 = temp;
                    }
                }
                if (num1 % num2 != 0 ) {
                    round--;
                    continue;
                }
            }

            quiz_ans = lvl < 5 ? calc(num1, num2) : power(num1, 2);
            user_ans = interact(lvl, round, num1, num2);       
            if (quiz_ans == user_ans) {
                printf("    Correct!\n");
                score++;
            } else {
                printf("    Incorrect, don't give up!\n");
            }
        }        
        printf("\nYou got %d out of %d.\n", score, num_rounds);

        // restart or quit
        while((choice = toupper(getchar())) != 'R' && choice != 'N') {

            if (choice == 'Q') {
                break;
            } else {
                printf("\n(R)estart quiz | (N)ext difficulty level | (Q)uit\n\nSelect: ");
            }
        }
    }
    return 0;
}

 // caclucate answers, use ASCII conversions when operator was given by user
int calc(int num1, int num2) {    

    switch (symbol) {
        case 0: case 42:    return num1 * num2;
        case 1: case 47:    return num1 / num2;
        case 2: case 43:    return num1 + num2;
        case 3: case 45:    return num1 - num2;
    }
    exit(EXIT_FAILURE);
}

// calculate powers
int power(int base, int exp) {

    if (base == 0)      return 0;
    else if (exp == 0)  return 1;

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
    exit(EXIT_FAILURE);
}

// return user input operators to main
int input(void) {
    char ch;

    while ((ch = (char) getchar()) != '*' && ch != '/' && ch != '+' && ch != '-') {
            if (ch == '\n' || ch == ' ')
                continue;
            else
                printf("    Invalid operator, try again: ");
            
    }    
    return (int) ch;
}

// Print equations and collect user input
int interact(int level, int round, int num1, int num2) {

    int user_ans, method = rand() % 2;

    symbol = (int) operator(symbol);
    
    switch(level) {
        case 1: case 2:     
            printf("\n%d.  %d %c %d = ", round, num1, symbol, num2);
            scanf("%d", &user_ans);
            return user_ans;

        case 3:             
            if (method == 1) {
                printf("\n%d.  x %c %d = %d\n", round, symbol, num2, calc(num1, num2));
                printf("    x = ");
                scanf(" %d", &num1);
            } else {
                printf("\n%d.  %d %c x = %d\n", round, num1, symbol, calc(num1, num2));
                printf("    x = ");
                scanf(" %d", &num2);
            }
            break;

        case 4: 
            if (method == 1) {
                printf("\n%d.  x ? %d = %d\n", round, num2, calc(num1, num2));
                printf("    x = ");
                scanf(" %d", &num1);
                printf("    Operator: ");
                symbol = (int) input();
            } else { 
                printf("\n%d.  %d ? x = %d\n", round, num1, calc(num1, num2));
                printf("    Operator: ");
                symbol = (int) input();
                printf("    x = ");
                scanf(" %d", &num2);
            }
            break;

        case 5:
            printf("%d² = ", num1);
            scanf(" %d", &user_ans);
            return user_ans; 
    }
    return calc(num1, num2);
}