#ifndef PARSE_H
#define PARSE_H

struct parse_tree_s;
typedef struct parse_tree_s *parse_tree_p;

extern char *readline(FILE *file);
extern void parse_binary_exp(char *input);
#endif
