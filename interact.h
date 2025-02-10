#ifndef INTERACT_H
#define INTERACT_H

enum operator_symbol {MULTIPLY, DIVIDE, ADD, SUBTRACT};

int calc(int num1, int num2);
int power(int base, int exp);
int interact(int level, int round, int num1, int num2);

#endif