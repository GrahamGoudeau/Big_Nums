#ifndef PARSE_H
#define PARSE_H

#include "big_num.h"

typedef enum {ADD, SUB, MULT, NIL} OP_TYPE_e;

struct parse_tree_s;
typedef struct parse_tree_s *parse_tree_p;

/* the string returned from readline must be freed */
extern char *readline(FILE *file);

/* given input from readline, parse it for two big_nums */
extern big_num_p parse_binary_exp(char *input);

#endif
