#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "interact.h"

enum operator_symbol symbol;

int main(void) {
    int num1, num2, level = 0, digits = 0, round, num_rounds, score, quiz_ans, user_ans;
    char choice = 'R';
    
    srand((unsigned) time(NULL));

    while(choice == 'R' || choice == 'N') {
        
        if (choice == 'N') level += 1;
        else {
            printf("\ndifficulty:\n(1) Operands < 10\n(2) Operands < 100\n(3) One operand is x and operands < 10\n(4) One operator is x, operand unkown and operands < 100\n(5) Squares, base < 10\nSelect:  ");
            scanf("%d", &level);
        }
        
        // difficulty digits 
        if (level == 1 || level == 3 || level == 5) {                             // Numbers should never be zero, add 1 when calling rand()
            digits = 8;
        } else if (level == 2 || level == 4) {
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
            if (symbol == MULTIPLY) {                                                  // Multiplication: for levels 2, 3 and 4: Make num2 a single digit
                num2 %= 10;
            } else if (symbol == DIVIDE) {                                           // Division: Make num1 % num2 == 0
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

            quiz_ans = level < 5 ? calc(num1, num2) : power(num1, 2);
            user_ans = interact(level, round, num1, num2);       
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

