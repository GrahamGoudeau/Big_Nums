CXX = clang
FLAGS= -c -g -O0 -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic
RM = rm -f
PROG_NAME = calculator

all: ${PROG_NAME}

clean: 
	${RM} ${PROG_NAME} *.o

calc.o: calc.c calc.h
	${CXX} ${FLAGS} calc.c -o $@

parse.o: parse.c parse.h
	${CXX} ${FLAGS} parse.c -o $@

big_num.o: big_num.c big_num.h
	${CXX} ${FLAGS} big_num.c -o $@

main.o: main.c
	${CXX} ${FLAGS} main.c -o $@

${PROG_NAME}: main.o calc.o parse.o big_num.o
	${CXX} -g $^ -o $@
