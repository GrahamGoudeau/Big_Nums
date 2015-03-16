#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "calc.h"
#include "big_num.h"

const char over_two_num_error[] = "Parse binary exp: "
                                  "more than two numbers on line\n";
 
struct parse_tree_s {
        char value;
        OP_TYPE_e operation;
};

/* Source: "String input and output in C", stackoverflow.com */
char *readline(FILE *file)
{
        size_t size = 80;
        size_t curr = 0;
        char *buffer = malloc(size);
        while (fgets(buffer+curr, size-curr, file)) {
                if (strchr(buffer + curr, '\n')) return buffer;
                curr = size - 1;
                size *= 2;
                char *tmp = realloc(buffer, size);
                buffer = tmp;
        }
        return buffer;
}

bool is_numeric(char c)
{
        return ('0' <= c && c <= '9');
}


char *get_number(char *input, num_index len)
{
        num_index size = len;
        while (is_numeric(input[size]))
                size++;

        /* + 1 for the null terminating character */
        char *new_string = malloc(size - len + 1); //+ 1???
        num_index i;
        for (i = 0; i < (size - len); i++) 
                new_string[i] = input[i + len];

        new_string[i] = 0;

        return new_string;
}

big_num_p evaluate(big_num_p operand1, big_num_p operand2, OP_TYPE_e operator)
{
        switch (operator) {
                case ADD:
                        return add(operand1, operand2);
                default:
                        return operand1;
        }

}

OP_TYPE_e get_operator(char *input)
{
        if (input == NULL) return NIL;
        num_index index = 0;
        OP_TYPE_e operator = NIL;
        while (input[index] != '\n') {
                switch (input[index]) {
                        case '+':
                                if (operator != NIL) return NIL;
                                operator = ADD;
                                break;
                        case '-':
                                if (operator != NIL) return NIL;
                                operator = SUB;
                                break;
                        case '*':
                                if (operator != NIL) return NIL;
                                operator = MULT;
                                break;
                        default:
                                break;
                }
                index++;
        }
        return operator;
}

big_num_p parse_binary_exp(char *input)
{
        num_index len = 0;
        while (is_numeric(input[len])) {
                len++;
        }

        char *first_num = get_number(input, 0);
        big_num_p operand1 = parse_big_num(first_num);
        free(first_num);

        OP_TYPE_e operator = get_operator(input);
        
        /* return first if no or multiple operand symbols */
        if (operator == NIL) return operand1;

        while (!is_numeric(input[len]) && input[len] != '\n')
                len++;

        /* if no second number, return the first */
        if (input[len] == '\n') 
                return operand1;

        char *second_num = get_number(input, len);
        big_num_p operand2 = parse_big_num(second_num);
        free(second_num);
        while (is_numeric(input[len]))
                len++;

        /* ensure input is not erroneous */
        while (input[len] != '\n') {
                if (is_numeric(input[len])) {
                        fprintf(stderr, over_two_num_error);
                        free_big_num(operand1);
                        free_big_num(operand2);
                        return NULL;
                }
                len++;
        }
 
        big_num_p result = evaluate(operand1, operand2, operator);
        free_big_num(operand1);
        free_big_num(operand2);
        return result;
}

