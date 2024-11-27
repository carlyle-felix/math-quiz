#include <stdio.h>
#include <stdlib.h>
#include "interact.h"

char operator(int operator);
int input(void);

extern int symbol;

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

// calculate powers
int power(int base, int exp) {

    if (base == 0)      return 0;
    else if (exp == 0)  return 1;

    return base * power(base, exp - 1);
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