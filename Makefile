mquiz: quiz.o interact.o
	gcc -o mquiz quiz.o interact.o

quiz.o: quiz.c interact.h operator.h
	gcc -c quiz.c

interact.o: interact.c interact.h operator.h
	gcc -c interact.c