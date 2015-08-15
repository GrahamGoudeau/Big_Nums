#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <stdbool.h>

struct big_num_s;
typedef struct big_num_s *big_num_p;

/* parse a single big_num from string input with null terminating character;
 * expects all-numeric input; if non-numeric input received,
 * prints error to stderr and calls exit(1).  Can accept bases
 */
big_num_p parse_big_num(char *input);

/* print a big_num in standard format; no newline character after the number */
void print_big_num(big_num_p num);

void free_big_num(big_num_p num);

/* Arithmetic functions return new big_num_p with result of calculation
 * They have the form add(op1, op2) = op1 + op2 and sub(op1, op2) = op1 - op2
 */
big_num_p add(big_num_p operand1, big_num_p operand2);
big_num_p subtract(big_num_p operand1, big_num_p operand2);


/* true if operand1 <= operand2, false otherwise */
bool leq(big_num_p operand1, big_num_p operand2);

/* check if operand1 == operand2 */
bool eq(big_num_p operand1, big_num_p operand2);

/* has behavior: for (i = start; i != end; i += incr) {loop_body()}
 * can accept positive or negative increments
 */
void for_loop(big_num_p start, big_num_p incr, big_num_p end,
                     void loop_body(big_num_p i, void *cl), void *cl);

void print_all_info(big_num_p);
#endif
