#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "calc.h"
#include "big_num.h"

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

/*
char *get_character(char *input, num_index len)
{
        num_index size = len;
        while (is_numeric(input[size]))
                size++;

        char new_string[size - len];
        num_index i;
        for (i = 0; i < (size - len); i++) 
                new_string[i] = input[i + len];

        new_string[i] = 0;

        return new_string;
}
*/

void parse_binary_exp(char *input)
{
        num_index len = 0;
        while (is_numeric(input[len])) {
                len++;
        }

        /* + 1 for the null terminating character */
        char first_num[len + 1];
        num_index i;
        for (i = 0; i < len; i++) {
                first_num[i] = input[i];
        }
        first_num[i] = 0;

        big_num_p operand1 = parse_big_num(first_num);
        OP_TYPE_e operator;
        while (!is_numeric(input[len]) && input[len] != '\n') {
                switch (input[len]) {
                        case '+':
                                operator = ADD;
                                break;
                        case '-':
                                operator = SUB;
                                break;
                        case '*':
                                operator = MULT;
                                break;
                        default:
                                break;
                }
                len++;
        }
        if (input[len] == '\n') return;

        num_index second_start = len;
        while (is_numeric(input[len])) 
                len++;

        char second_num[(len - second_start) + 1];
        for (i = 0; i < len - second_start; i++)
                //if (input[i + second_start] != '\n')
                        second_num[i] = input[i + second_start];

        second_num[i] = 0;
        big_num_p operand2 = parse_big_num(second_num);
        
        print_big_num(operand2);
        fprintf(stdout, "\n");
        free_big_num(operand1);
        free_big_num(operand2);
}
