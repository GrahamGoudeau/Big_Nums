#include <stdlib.h>
#include <stdio.h>
#include "parse_tree.h"
#include "calc.h"

struct parse_tree_s {
        char value;
        OP_TYPE_e operation;
};

/*
         Source: "String input and output in C", stackoverflow.com 
        size_t size = 80;
        size_t curr = 0;
        char *buffer = malloc(size);
        while (fgets(buffer + curr, size - curr, 
*/

