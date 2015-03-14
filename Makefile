CXX = clang
FLAGS= -c -g -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic
RM = rm -f
PROG_NAME = calculator

all: ${PROG_NAME}

clean: 
	${RM} ${PROG_NAME} *.o

calc.o: calc.c calc.h
	${CXX} ${FLAGS} calc.c -o $@

parse_tree.o: parse_tree.c parse_tree.h
	${CXX} ${FLAGS} parse_tree.c -o $@

big_num.o: big_num.c big_num.h
	${CXX} ${FLAGS} big_num.c -o $@

main.o: main.c
	${CXX} ${FLAGS} main.c -o $@

${PROG_NAME}: main.o calc.o parse_tree.o big_num.o
	${CXX} -g $^ -o $@
