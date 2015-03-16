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
        
        free_big_num(operand1);
}
