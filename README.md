A simple math quiz written in C.

There are currently 4 difficulty levels, all levels will use operands +, -, / and *:

1. Operands are less than 10.
2. Operands are less than 100.
3. One operand is substituted with *x* and the answer is shown. (find *x*)
4. One operand is substituted with *x*, the operator is unknown and the answer is shown. (find *x* and input the missing operand)
5. Squares where base is a less than 10.

In multiplication: 
- the second operand will always be less than 10 (single digit).

In division:
- the answer will always be an integer.
- the first operand will always be greater than 1. Without this, here's a scenario in level 3 where the equation is `1 / x = 0`, in this scenario, *x* could be any integer greater than 1 and the answer for *x* would be correct because the program doesn't use floats.
