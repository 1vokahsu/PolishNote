CC=gcc
FLAGS= -Wall -Werror -Wextra -std=c11
PATH_build= ../build/

all:
	$(CC) $(FLAGS) graph.c libs/math_solution.c libs/draw.c libs/support.c libs/kurwa.c libs/stack.c -o $(PATH_build)graph
debuger:
	$(CC) $(FLAGS) -DDEBUGER graph.c libs/math_solution.c libs/draw.c libs/support.c libs/kurwa.c libs/stack.c -o $(PATH_build)Debuger
clean:
	rm -rf ./*.o $(PATH_build)graph

rebuild: clean all