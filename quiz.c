 // Author: Carlyle Felix
 // This math quiz was written with the basics I've learned to date.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

char operator(int operator);
int calc(int num1, int num2, int operator);
char input(void);
int power(int base, int exp);

int main(void) {
    int num1, num2, quiz_ans, user_ans, digits = 0, lvl, sym, round, n, score, i, x;
    char choice = 'Y';

    srand((unsigned) time(NULL));

    while(choice == 'Y') {
        
        printf("\ndifficulty:\n(1) Operands < 10\n(2) Operands < 100\n(3) One operand is x and operands < 10\n(4) One operator is x, operand unkown and operands < 100\n(5) Squares, base < 10\nSelect:  ");
        scanf("%d", &lvl);
        
        // difficulty specifics 
        if (lvl == 1 || lvl == 3 || lvl == 5) {                                                   // Numbers should never be zero, add 1 when calling rand()
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
            if (lvl == 5){
                quiz_ans = power(num1, 2);                                                              // Only use ^2 for now (Author is aware of a pow() function available in math.h)
                printf("%d² = ", num1);
                scanf("%d", &user_ans);
            } else {
                sym = rand() % 4;
                num2 = rand() % digits + 1;
                
                // operator specifics  
                if (sym == 0) {                                                                         // Multiplication: for levels 2, 3 and 4: Make num2 a single digit
                    num2 %= 10;
                } else if (sym == 1) {                                                                   // Division: Make num1 % num2 == 0
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

                // level specifics
                if (lvl > 2) {
                    quiz_ans = calc(num1, num2, sym);
                    
                    switch (lvl) {
                    case 3:
                        if (rand() % 2 == 0) {
                            printf("\n%d.  x %c %d = %d\n", round + 1, operator(sym), num2, quiz_ans);
                            printf("    x = ");
                            scanf("%d", &num1);
                        } else {   
                            printf("\n%d.  %d %c x = %d\n", round + 1, num1, operator(sym), quiz_ans);
                            printf("    x = ");
                            scanf("%d", &num2);
                        }
                        user_ans = calc(num1, num2, sym);
                        break;

                    case 4:
                        if (rand() % 2 == 0) {
                            printf("\n%d.  x ? %d = %d\n", round + 1, num2, quiz_ans);
                            printf("    x = ");
                            scanf("%d", &num1);
                            printf("    Operator: ");
                            sym = (int) input();
                        } else {
                            printf("\n%d.  %d ? x = %d\n", round + 1, num1, quiz_ans);
                            printf("    Operator: ");
                            sym = (int) input();
                            printf("    x = ");
                            scanf("%d", &num2);
                        }
                        user_ans = calc(num1, num2, sym);
                        break;
                    }       
                } else {
                    printf("\n%d.  %d %c %d = ", round + 1, num1, operator(sym), num2);
                    scanf("%d", &user_ans);
                    quiz_ans = calc(num1, num2, sym);
                }
            }
            if (quiz_ans == user_ans) {
                printf("    Correct!\n");
                score++;
            } else {
                printf("    Incorrect, don't give up!\n");
            }
        }        
        printf("\nYou got %d out of %d.\n", score, n);

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

int calc(int num1, int num2, int operator) {                                                    // ASCII conversions

    switch (operator) {
    case 0: case 42:
        return num1 * num2;
    case 1: case 47:
        return num1 / num2;
    case 2: case 43:
        return num1 + num2;
    case 3: case 45:
        return num1 - num2;
    }
}

int power(int base, int exp) {

    if (base == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    }

    return base * power(base, exp - 1);
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

char input(void) {
    
    while (getchar() == '\n') {
        return getchar();
    }
}