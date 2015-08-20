CXX = clang
OPTIM = -O0
FLAGS= -c -g ${OPTIM} -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic
RM = rm -fv
PROG_NAME = big_num_test_suite

all: ${PROG_NAME}

clean:
	${RM} ${PROG_NAME} *.o

big_num.o: big_num.c big_num.h
	${CXX} ${FLAGS} big_num.c -o $@

main.o: main.c
	${CXX} ${FLAGS} main.c -o $@

${PROG_NAME}: main.o big_num.o
	${CXX} -g $^ -o $@
